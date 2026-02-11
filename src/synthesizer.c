/* synthesizer.c
 *
 * Copyright 2026 Alan Crispin <crispinalan@gmail.com>
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
#include "synthesizer.h"

// Standard IMA ADPCM step table
static const int step_table[89] = {
    7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 19, 21, 23, 25, 28, 31, 34, 37, 41, 45,
    50, 55, 60, 66, 73, 80, 88, 97, 107, 118, 130, 143, 157, 173, 190, 209, 230,
    253, 279, 307, 337, 371, 408, 449, 494, 544, 598, 658, 724, 796, 876, 963,
    1060, 1166, 1282, 1411, 1552, 1707, 1878, 2066, 2272, 2499, 2749, 3024, 3327,
    3660, 4026, 4428, 4871, 5358, 5894, 6484, 7132, 7845, 8630, 9493, 10442, 11487,
    12635, 13899, 15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794, 32767
};

static const int index_table[16] = {
    -1, -1, -1, -1, 2, 4, 6, 8, -1, -1, -1, -1, 2, 4, 6, 8
};

// State for the decoder
int predicted_sample = 0;
int step_index = 0;

int16_t decode_adpcm_nibble(uint8_t nibble) {
    int step = step_table[step_index];
    int diff = step >> 3;
    if (nibble & 4) diff += step;
    if (nibble & 2) diff += step >> 1;
    if (nibble & 1) diff += step >> 2;
    
    if (nibble & 8) predicted_sample -= diff;
    else predicted_sample += diff;

    // Clamp to 16-bit range
    if (predicted_sample > 32767) predicted_sample = 32767;
    else if (predicted_sample < -32768) predicted_sample = -32768;

    // Update step index
    step_index += index_table[nibble];
    if (step_index < 0) step_index = 0;
    if (step_index > 88) step_index = 88;

    return (int16_t)predicted_sample;
}

void write_wav_header(FILE* f, int num, int rate) {
    int size = 36 + num * 2, br = rate * 2;
    uint16_t ch = 1, fmt = 1, bits = 16, align = 2;
    fwrite("RIFF", 1, 4, f); fwrite(&size, 4, 1, f); fwrite("WAVEfmt ", 1, 8, f);
    uint32_t csz = 16; fwrite(&csz, 4, 1, f); fwrite(&fmt, 2, 1, f);
    fwrite(&ch, 2, 1, f); fwrite(&rate, 4, 1, f); fwrite(&br, 4, 1, f);
    fwrite(&align, 2, 1, f); fwrite(&bits, 2, 1, f); fwrite("data", 1, 4, f);
    int dsz = num * 2; fwrite(&dsz, 4, 1, f);
}
