/* synthesizer.h
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
#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

#include "dictionary.h"
#include "diphone.h"
#include <stdio.h>
#include <stdint.h>

// Function prototypes
void write_wav_header(FILE* file, int data_size);
void apply_triangle_window(int16_t* buffer, int frame_size, int half_frame);
void synthesizer_vocoder(const char* text, FILE* output_file, Dictionary* dict, float tempo);
void vocoder(const char** diphones, int diphone_count, float tempoFactor, int* output_size);

#endif // SYNTHESIZER_H
