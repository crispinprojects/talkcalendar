/* wavplay.h
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


/***********************************************************************
 * Alsa player 
 * Author: crispinalan@gmail.com
 ***********************************************************************/
 
 
#ifndef WAVPLAY_H
#define WAVPLAY_H

#define ALSA_PCM_NEW_HW_PARAMS_API

#include <stdint.h>

// wav files
// https://wavefilegem.com/how_wave_files_work.html
// wav specification
// https://sites.google.com/site/musicgapi/technical-documents/wav-file-format
// wav header structure
typedef struct WaveHeader 
{
    char RIFF_marker[4];
    uint32_t file_size;
    char filetype_header[4];
    char format_marker[4];
    uint32_t data_header_length;
    uint16_t format_type;
    uint16_t number_of_channels;
    uint32_t sample_rate;
    uint32_t bytes_per_second;
    uint16_t bytes_per_frame;
    uint16_t bits_per_sample;
} wav_header;


void wavplay(char* file);  //char pointer type


#endif //WAVPLAY_H
