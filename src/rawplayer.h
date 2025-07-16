/* rawplayer.h
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
// Very basic voice processor and raw file player

#ifndef RAWPLAYER_H
#define RAWPLAYER_H

#define ALSA_PCM_NEW_HW_PARAMS_API

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <alsa/asoundlib.h>
#include <stdint.h>
	
void set_sample_rate(unsigned int rate);
void save_raw_file(char* file_path, unsigned char *data, unsigned int data_len);
void raw_player(char* file_path);  

void voice_amp(char* file_path, int gain); 
int* resample(int *data_in, unsigned int num_samples);

#endif //RAWPLAYER_H
