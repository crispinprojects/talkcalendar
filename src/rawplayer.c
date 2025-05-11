/***************************************************************************
 *   Author Alan Crispin                                                   *
 *   crispinalan@gmail.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation.                                         *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 ***************************************************************************/

//See: Introduction to Sound Programming with ALSA by Jeff Tranter
// https://www.linuxjournal.com/article/6735?page=0,1
 
#include "rawplayer.h"

#define CHANNELS 1
#define FRAMES 4096
//#define SAMPLERATE 14000
#define BUF_SIZE    8192
#define PERIODS    1


unsigned int rate=16000;

void set_sample_rate(unsigned int sample_rate)
{
	rate =sample_rate;	
	//printf("set_sample_rate: sample rate = %u\n", rate);
}

void rawplay(char *file) {
	
    int debug_info=0;
    
    int rc;	
	char * buffer;
  	int buffer_size;
  	int periods_per_buffer;

  	snd_pcm_t *handle;
  	snd_pcm_hw_params_t *params;
  	snd_pcm_uframes_t frames;

  	unsigned int channels;
  	
	
	if(debug_info) printf("rawplayer: reading file: %s\n", file);
   
  	channels=CHANNELS;
  	if(debug_info) printf("channels = %u\n", channels);
  	//rate = SAMPLERATE;
  	if(debug_info) printf("sample rate = %u\n", rate);
  	periods_per_buffer = PERIODS; 
  	if(debug_info) printf("periods per buffer = %d\n", periods_per_buffer);
	buffer_size=BUF_SIZE;
	if(debug_info) printf("buffer size = %d\n", buffer_size);
	
  	FILE * fp;

    // Open raw file to read
	fp = fopen(file, "rb");

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
	if(debug_info) printf("set PCM encoding format: S16_LE\n");
  	if ((rc = snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE)) < 0)
  	{
  		printf("ERROR: Cannot set PCM format. %s\n", snd_strerror(rc));
  	}
	if(debug_info) printf("set PCM channels: %u\n",channels);
  	if ((rc = snd_pcm_hw_params_set_channels_near(handle, params, &channels)) < 0)
  	{
  		printf("ERROR: Cannot set number of channels. %s\n", snd_strerror(rc));
  	}
	if(debug_info) printf("set PCM rate: %u\n",rate);
 	if ((rc = snd_pcm_hw_params_set_rate_near(handle, params, &rate, 0)) < 0)
 	{
 		printf("ERROR: Cannot set plyabck rate. %s\n", snd_strerror(rc));
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
	
	if(debug_info) printf("Frames: %lu\n", frames);

	if ((rc = snd_pcm_hw_params_get_channels(params, &channels)) < 0)
	{
		printf("Playback ERROR: Cannot get channel number %s\n", snd_strerror(rc));
	}

	if ((rc = snd_pcm_hw_params_get_rate(params, &rate, 0)) < 0)
	{
		printf("ERROR: Cannot get rate %s\n", snd_strerror(rc));
	}

	// Free parameters
	snd_pcm_hw_params_free(params);

	// Create buffer
  	buffer_size = frames * periods_per_buffer * channels * sizeof(int16_t); /* 2 bytes/sample, 2 channels */
  	if(debug_info) printf("buffer size = %d\n",buffer_size);
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

  	if(debug_info) printf("ALSA device is now draining...\n");
  	snd_pcm_drain(handle);

  	if(debug_info) printf("closing connections as raw player finished\n");
  	snd_pcm_close(handle);

  	free(buffer);
  	fclose(fp);

}
