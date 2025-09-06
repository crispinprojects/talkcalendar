/* wavplay.c
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


/***************************************************************************
 * Alsa player 
 * Author: crispinalan@gmail.com
 ***************************************************************************/

#include "wavplay.h"
#include <alsa/asoundlib.h> // Add the include here


/**
 * @brief play a WAV file
 * @param file to play
 */
void wavplay(char *file) {
	
	//printf("wavplay: reading file: %s\n", file);	
	int rc;	
	char * buffer;
  	int buffer_size;
  	int periods_per_buffer;

  	snd_pcm_t *handle;
  	snd_pcm_hw_params_t *params;
  	snd_pcm_uframes_t frames;

  	unsigned int channels;
  	unsigned int rate;

	wav_header * wav_header_info;

  	FILE * fp;

    // Open wav file to read
	fp = fopen(file, "rb");

	if (fp == NULL)
	{
		printf("ERROR: file does not exist, or cannot be opened.\n");
		return;
	}
	
	wav_header_info = malloc(44);

	fread(wav_header_info, 1, 44, fp);
    	
    // Assign wav file variables 
	channels = wav_header_info->number_of_channels;
	rate = wav_header_info->sample_rate;	
	//periods_per_buffer = 1; 
	periods_per_buffer = 2; 

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

  	if ((rc = snd_pcm_hw_params_set_channels_near(handle, params, &channels)) < 0)
  	{
  		printf("ERROR: Cannot set number of channels. %s\n", snd_strerror(rc));
  	}
	//printf("set PCM rate: %u\n",rate);
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
		printf("Playback ERROR: Can't get period size. %s\n", snd_strerror(rc));
	}
	
	//printf("Frames: %lu\n", frames);

	if ((rc = snd_pcm_hw_params_get_channels(params, &channels)) < 0)
	{
		printf("Playback ERROR: Can't get channel number. %s\n", snd_strerror(rc));
	}

	if ((rc = snd_pcm_hw_params_get_rate(params, &rate, 0)) < 0)
	{
		printf("ERROR: Cannot get rate. %s\n", snd_strerror(rc));
	}

	// Free parameters
	snd_pcm_hw_params_free(params);


	// Create buffer
  	buffer_size = frames * periods_per_buffer * channels * sizeof(int16_t); /* 2 bytes/sample, 2 channels */
  	buffer = (char *) malloc(buffer_size);
  	
  
  	// New and improved while loop to read and write to the device
	size_t read_bytes;
	size_t frames_to_write;
	size_t total_frames_read;
	size_t total_frames_written;

	while ((read_bytes = fread(buffer, 1, buffer_size, fp)) > 0)
	{
		total_frames_read = read_bytes / (channels * sizeof(int16_t));
		total_frames_written = 0;
		while (total_frames_written < total_frames_read)
		{
			frames_to_write = total_frames_read - total_frames_written;
			rc = snd_pcm_writei(handle, buffer + total_frames_written * channels * sizeof(int16_t), frames_to_write);

			if (rc < 0)
			{
				rc = snd_pcm_recover(handle, rc, 0);
				if (rc < 0)
				{
					printf("ERROR: Can't write to PCM device. %s\n", snd_strerror(rc));
					break;
				}
			}

			total_frames_written += rc;
		}
	}
  	 
  	//printf("Alsa device is now draining...\n");
  	snd_pcm_drain(handle);

  	//printf("closing connections as play done.\n");
  	snd_pcm_close(handle);

  	free(wav_header_info);
  	free(buffer);
  	fclose(fp);
}
