/* wavcat.h
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

#ifndef WAVCAT_H
#define WAVCAT_H

#include <stdio.h>
#include <stdint.h>  //integer bit types int16_t int32_t etc.
#include <stdlib.h> //for malloc
#include <string.h> //for strlen strncpy etc.
#include "diphone.h"


typedef struct _WaveHeader_t {
    char chunkID[4];            // 1-4      RIFF
    int32_t chunkSize;          // 5-8
    char format[4];             // 9-12     WAVE
    char subchunkID[4];         // 13-16    fmt
    int32_t subchunkSize;       // 17-20
    uint16_t audioFormat;       // 21-22    PCM = 1
    uint16_t numChannels;       // 23-24
    int32_t sampleRate;         // 25-28
    int32_t bytesPerSecond;     // 29-32
    uint16_t blockAlign;        // 33-34
    uint16_t bitDepth;          // 35-36    16bit support only
    char dataID[4];             // 37-40    data
    int32_t dataSize;           // 41-44
} WaveHeader_t;

typedef struct _WaveData_t {
    int16_t *samples;
    int32_t sampleRate;
    uint16_t bitDepth;
    size_t size;
} WaveData_t;

void write_little_endian(unsigned int word, int num_bytes, FILE* wav_file);
void write_wav_header(FILE* wav_file, int32_t num_samples, int32_t sample_rate, uint16_t num_channels, uint16_t bit_depth);
void merge_and_amplify_wav_files(char *merge_filename, int num_files, DiphoneEntry* diphones[],int32_t sample_rate, float amplification, float tempo_factor);

WaveData_t* read_wav_from_memory(const unsigned char* wav_data, size_t data_size);

#endif // WAVCAT_H
