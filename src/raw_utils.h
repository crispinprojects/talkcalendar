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
// Very basic voice processor and raw file player

#ifndef RAWUTILS_H
#define RAWUTILS_H

#define ALSA_PCM_NEW_HW_PARAMS_API

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <alsa/asoundlib.h>
#include <stdint.h>
	
void set_sample_rate(unsigned int sample_rate);
void save_raw_file(char* file_path, unsigned char *data, unsigned int data_len);
void voice_amp(char* file_path, int gain);
void voice_echo(char* file_path, int gain, int echo_level, int echo_delay);
void voice_ring(char* file_path, int gain, float ring_level, float ring_freq);
void raw_player(char* file_path);  
int* resample(int *data_in, unsigned int num_samples);

#endif //RAWPLAY_H
