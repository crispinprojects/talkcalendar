/* rawplayer.c
 *
 * Copyright 2025 Alan Crispin <crispinalan@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */
#include "rawplayer.h"

#define CHANNELS 1 //voice is mono
#define BUF_SIZE  8192 //raw player
#define PERIODS    1 //raw player
#define BITS_PER_SAMPLE 16 // 16 bit resolution

unsigned int sample_rate=16000;

int* time_scaler(int *data_in, int data_in_size, int frame_size, int hop_size);

//======================================================================
int convert_bitsize(unsigned int in, int bps)
{
        const unsigned int max = (1 << (bps-1)) - 1;
        int result=in;
        if(in >max) result =in-(max<<1);
        else result =in;
        return result;       
}
//======================================================================
void set_sample_rate(unsigned int rate)
{
	sample_rate =rate;	
	//printf("set_sample_sample_rate: sample sample_rate = %u\n", sample_rate);
}
//======================================================================
void save_raw_file(char* file_path, unsigned char *data, unsigned int data_len)
{
		
	FILE* f = fopen(file_path, "w");
    fwrite(data, data_len, 1, f);
    fclose(f); 
}


//======================================================================
// Voice amp
// file_path: 	file path to raw file to be processed
// gain:		voice amplification factor
//======================================================================

void voice_amp(char* file_path, int gain)
{
	
	long num_samples =5000; //default	
	unsigned int bits_per_samp =16;	
	unsigned char buf;
	
	//Open raw file to read
	FILE* audio_file = fopen(file_path, "rb");

	if (audio_file == NULL)
	{
		printf("ERROR: file does not exist, or cannot be opened.\n");
		return;
	}
	//find file size and number of samples		
	fseek(audio_file, 0, SEEK_END); //goto end of file
	long file_size = ftell(audio_file); //get position of the file pointer 
	rewind(audio_file); //go to top	
	num_samples=file_size*2;
	//use calloc to zero data arrays
	int *data = (int *) calloc(num_samples, sizeof(int));
		
	//load data and echo data
	for (int i=0; i < num_samples; i++) {		
        
        unsigned int tmp = 0;
		for (int j=0; j != bits_per_samp; j+=8) {
			fread(&buf, 1, 1, audio_file);
			tmp += buf << j;
		}
	       
        data[i] = convert_bitsize(tmp, bits_per_samp);               
    }  
    
    //amp data    
    for (int i=0; i < num_samples; i++) {
        data[i] = gain*data[i];
    }  
    
    //resample data using averging  
    int *data_resampled = resample(data,num_samples);
    //write resampled processed voice data to file
	FILE* f = fopen(file_path, "w");	
    fwrite(data_resampled, num_samples/2, 1, f);
    fclose(f); 
    fclose(audio_file);  
    free(data);   
    free(data_resampled);	
}

//======================================================================

// Resample: 	convert input data with N samples to output data with N/2 samples
// data_in: 	pointer to input data array to be resampled
// num_samples:	number of samples of input data array
// output: 		pointer to resampled data array (averaging used) 

//======================================================================

int * resample(int *data_in, unsigned int num_samples)
{
	int j=0;
	
	int *data_out= (int *) calloc(num_samples/2, sizeof(int)); 
	
	//for (int i=0; i < num_samples-1; (i=i+2))
	
	for (int i=0; i < num_samples-1; i++)
	{	
		
		if(i % 2 == 0) //i is even
		{
		int sample1 =data_in[i];
		int sample2 =data_in[i+1];
		data_out[j] =(sample1+sample2)/2; //average
		j=j+1;			
		}
		
    }
	return data_out;
}


//======================================================================
// Raw Player
// file_path: 	file path to raw file to played
//======================================================================
void raw_player(char *file_path) {
	    
    int rc;	
	char * buffer;
  	int buffer_size;
  	int periods_per_buffer;

  	snd_pcm_t *handle;
  	snd_pcm_hw_params_t *params;
  	snd_pcm_uframes_t frames;

  	unsigned int channels;
  	
	//printf("rawplayer: reading file: %s\n", file_path);
   
  	channels=CHANNELS;
  	//printf("channels = %u\n", channels);  	
  	//printf("sample sample_rate = %u\n", sample_rate);
  	periods_per_buffer = PERIODS; 
  	//printf("periods per buffer = %d\n", periods_per_buffer);
	buffer_size=BUF_SIZE;
	//printf("buffer size = %d\n", buffer_size);
	
  	FILE * fp;

    // Open raw file to read
	fp = fopen(file_path, "rb");

	if (fp == NULL)
	{
		printf("ERROR: file does not exist, or cannot be opened.\n");
		return;
	}
	
  	// Open PCM device for playback
  	if ((rc = snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0)) < 0) 
  	{
    	printf("ERROR: Cannot open pcm device. %s\n", snd_strerror(rc));
  	}
    
  	// Allocate hardware parameters
  	if ((rc = snd_pcm_hw_params_malloc(&params)) < 0)
  	{
  		printf("ERROR: Cannot allocate hardware parameters. %s\n", snd_strerror(rc));
  	}
    
  	// Initialize parameters with default values
  	if ((rc = snd_pcm_hw_params_any(handle, params)) < 0)
  	{
  		printf("ERROR: Cannot initialize hardware parameters. %s\n", snd_strerror(rc));
  	}

  	// Setting hardware parameters
  	if ((rc = snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0)
  	{
  		printf("ERROR: Cannot set interleaved mode. %s\n", snd_strerror(rc));
  	}
	 
	//printf("set PCM encoding format: S16_LE\n");
  	
  	if ((rc = snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE)) < 0)
  	{
  		printf("ERROR: Cannot set PCM format. %s\n", snd_strerror(rc));
  	}
	
	//printf("set PCM channels: %u\n",channels);
  	
  	if ((rc = snd_pcm_hw_params_set_channels_near(handle, params, &channels)) < 0)
  	{
  		printf("ERROR: Cannot set number of channels. %s\n", snd_strerror(rc));
  	}
	
	//printf("set PCM sample_rate: %u\n",sample_rate);
 	
 	if ((rc = snd_pcm_hw_params_set_rate_near(handle, params, &sample_rate, 0)) < 0)
 	{
 		printf("ERROR: Cannot set plyabck sample_rate. %s\n", snd_strerror(rc));
 	}

 	if ((rc = snd_pcm_hw_params(handle, params)) < 0)
 	{
 		printf("ERROR: Cannot set hardware parameters. %s\n", snd_strerror(rc));
 	}

 	// Get hardware parameters
 	if ((rc = snd_pcm_hw_params_get_period_size(params, &frames, 0)) < 0)
	{
		printf("Playback ERROR: Cannot get period size. %s\n", snd_strerror(rc));
	}
	
	//printf("Frames: %lu\n", frames);

	if ((rc = snd_pcm_hw_params_get_channels(params, &channels)) < 0)
	{
		printf("Playback ERROR: Cannot get channel number %s\n", snd_strerror(rc));
	}

	if ((rc = snd_pcm_hw_params_get_rate(params, &sample_rate, 0)) < 0)
	{
		printf("ERROR: Cannot get sample_rate %s\n", snd_strerror(rc));
	}

	// Free parameters
	snd_pcm_hw_params_free(params);

	// Create buffer
  	buffer_size = frames * periods_per_buffer * channels * sizeof(int16_t); /* 2 bytes/sample, 2 channels */
  	//printf("buffer size = %d\n",buffer_size);
  	
  	buffer = (char *) malloc(buffer_size);

  	// Send data to ALSA
 	while (rc = fread(buffer, 1, periods_per_buffer * frames * channels * sizeof(int16_t), fp) != 0)
 	{
    	rc = snd_pcm_writei(handle, buffer, frames * periods_per_buffer);
    	if (rc == -EPIPE) 
    	{
      		fprintf(stderr, "underrun occurred\n");
      		snd_pcm_prepare(handle);
    	} 
    	else if (rc < 0) 
    	{
      		printf("ERROR: Cannot write to playback device. %s\n", strerror(rc));
    	}
  	}

  	//printf("ALSA device is now draining...\n");
  	snd_pcm_drain(handle);

  	//printf("closing connections as raw player finished\n");
  	snd_pcm_close(handle);

  	free(buffer);
  	fclose(fp);

}

//======================================================================
