/* wavcat.c
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
#define _GNU_SOURCE
#include "wavcat.h"
#include <math.h>
#include <stdint.h>
#include <string.h>

/**
 * @brief Reads raw WAV data from an in-memory array.
 * @param wav_data A pointer to the raw WAV data.
 * @param data_size The size of the raw data.
 * @return A new WaveData_t struct containing the samples, or NULL on failure.
 */
WaveData_t* read_wav_from_memory(const unsigned char* wav_data, size_t data_size) {
    if (wav_data == NULL || data_size == 0) {
        return NULL;
    }

    size_t num_samples = (data_size - 44) / sizeof(int16_t);
    int16_t* samples = (int16_t*)malloc(num_samples * sizeof(int16_t));
    if (samples == NULL) {
        return NULL;
    }

    memcpy(samples, wav_data + 44, num_samples * sizeof(int16_t));

    WaveData_t* wave_data = (WaveData_t*)malloc(sizeof(WaveData_t));
    if (wave_data == NULL) {
        free(samples);
        return NULL;
    }
    wave_data->samples = samples;
    wave_data->size = num_samples;
    return wave_data;
}

/**
 * @brief Clamps a float value to the range of a 16-bit integer.
 * @param value The float value to clamp.
 * @return The clamped 16-bit integer.
 */
static int16_t clamp_to_int16(float value) {
    if (value > 32767.0f) {
        return 32767;
    }
    if (value < -32768.0f) {
        return -32768;
    }
    return (int16_t)value;
}

/**
 * @brief Writes a little-endian word to a file.
 * @param word The word to write.
 * @param num_bytes The number of bytes to write.
 * @param wav_file The file pointer.
 */
void write_little_endian(unsigned int word, int num_bytes, FILE* wav_file) {
    unsigned char buf;
    while (num_bytes > 0) {
        buf = word & 0xFF;
        fwrite(&buf, 1, 1, wav_file);
        num_bytes--;
        word >>= 8;
    }
}


/**
 * @brief Writes a WAV header to a file.
 * @param wav_file The file pointer.
 * @param num_samples The number of samples.
 * @param sample_rate The sample rate.
 * @param num_channels The number of channels.
 * @param bit_depth The bit depth.
 */
void write_wav_header(FILE* wav_file, int32_t num_samples, int32_t sample_rate, uint16_t num_channels, uint16_t bit_depth) {
    // RIFF chunk
    fwrite("RIFF", 1, 4, wav_file);
    write_little_endian(36 + num_samples * num_channels * (bit_depth / 8), 4, wav_file);
    fwrite("WAVE", 1, 4, wav_file);

    // fmt chunk
    fwrite("fmt ", 1, 4, wav_file);
    write_little_endian(16, 4, wav_file); // Subchunk1Size
    write_little_endian(1, 2, wav_file);  // AudioFormat (1=PCM)
    write_little_endian(num_channels, 2, wav_file);
    write_little_endian(sample_rate, 4, wav_file);
    write_little_endian(sample_rate * num_channels * (bit_depth / 8), 4, wav_file); // ByteRate
    write_little_endian(num_channels * (bit_depth / 8), 2, wav_file); // BlockAlign
    write_little_endian(bit_depth, 2, wav_file);

    // data chunk
    fwrite("data", 1, 4, wav_file);
    write_little_endian(num_samples * num_channels * (bit_depth / 8), 4, wav_file);
}

/**
 * @brief Finds the best overlap between two segments of audio data.
 * @param input_samples A pointer to the audio data.
 * @param current_pos The starting position of the current segment.
 * @param overlap_len The length of the overlap.
 * @param search_range The range to search for the best overlap.
 * @param input_size The total size of the audio data.
 * @return The best overlap position.
 */
static int find_best_overlap(int16_t* input_samples, int current_pos, int overlap_len, int search_range, int input_size) {
    int search_start = current_pos - search_range;
    if (search_start < 0) {
        search_start = 0;
    }
    
    int best_match_pos = current_pos;
    float max_corr = -1.0f;
    
    int target_segment_start = current_pos;

    // Check if the target segment itself is valid
    if (target_segment_start + overlap_len > input_size) {
        return current_pos;
    }

    // The maximum possible starting position for a valid search segment
    int search_end = current_pos + search_range;
    if (search_end + overlap_len > input_size) {
        search_end = input_size - overlap_len;
    }
    if (search_end < search_start) {
        search_end = search_start;
    }
    
    for (int search_pos = search_start; search_pos <= search_end; search_pos++) {
        
        float corr = 0.0f;
        float energy1 = 0.0f;
        float energy2 = 0.0f;
        
        for (int i = 0; i < overlap_len; i++) {
            float s1 = (float)input_samples[target_segment_start + i];
            float s2 = (float)input_samples[search_pos + i];
            
            corr += s1 * s2;
            energy1 += s1 * s1;
            energy2 += s2 * s2;
        }

        if (energy1 > 0.0f && energy2 > 0.0f) {
            float normalized_corr = corr / sqrtf(energy1 * energy2);
            if (normalized_corr > max_corr) {
                max_corr = normalized_corr;
                best_match_pos = search_pos;
            }
        }
    }
    
    return best_match_pos;
}

/**
 * @brief Merges and amplifies multiple WAV files into a single WAV file.
 * @param merge_filename The name of the output WAV file.
 * @param num_diphones The number of diphones to merge.
 * @param diphone_entries An array of DiphoneEntry pointers.
 * @param sample_rate The sample rate.
 * @param amplification The amplification factor.
 * @param tempo_factor The tempo factor.
 */
void merge_and_amplify_wav_files(char *merge_filename, int num_diphones, DiphoneEntry* diphone_entries[], int32_t sample_rate, float amplification, float tempo_factor) {
    if (num_diphones <= 0) {
        return;
    }

    int16_t* merged_data = NULL;
    int32_t merged_data_size = 0;

    // First, merge all diphones into a single, contiguous input buffer.
    int32_t total_input_size = 0;
    for (int i = 0; i < num_diphones; i++) {
        total_input_size += diphone_entries[i]->size / sizeof(int16_t);
    }

    // Allocate the full buffer and initialize all bytes to zero
    int16_t* input_samples = (int16_t*)calloc(total_input_size, sizeof(int16_t));
    if (input_samples == NULL) {
        fprintf(stderr, "Memory allocation failed for combined input buffer.\n");
        return;
    }

    // Populate the entire buffer with valid data
    int current_input_pos_write = 0;
    for (int i = 0; i < num_diphones; i++) {
        WaveData_t* current_data = read_wav_from_memory(diphone_entries[i]->data, diphone_entries[i]->size);
        if (current_data == NULL) continue;
        
        memcpy(input_samples + current_input_pos_write, current_data->samples, current_data->size * sizeof(int16_t));
        current_input_pos_write += current_data->size;
        
        free(current_data->samples);
        free(current_data);
    }

    // Now, we know input_samples is fully populated and we can begin the processing loop
    const int FRAME_SIZE = 1024;
    const int OVERLAP_SAMPLES = 256; 
    const int SEARCH_RANGE = 256; 
    
    int analysis_step = FRAME_SIZE - OVERLAP_SAMPLES;
    int synthesis_step = (int)((float)analysis_step / tempo_factor);
    if (synthesis_step <= 0) synthesis_step = 1;

    merged_data_size = (int32_t)((float)total_input_size / tempo_factor) + FRAME_SIZE; 
    merged_data = (int16_t*)calloc(merged_data_size, sizeof(int16_t));
    if (merged_data == NULL) {
        fprintf(stderr, "Initial memory allocation failed!\n");
        free(input_samples);
        return;
    }

    int current_input_pos = 0;
    int current_output_pos = 0;

    while (current_input_pos < total_input_size) {
        int analysis_pos = current_input_pos;
        int analysis_len = FRAME_SIZE;

        if (analysis_pos + analysis_len > total_input_size) {
            analysis_len = total_input_size - analysis_pos;
        }

        if (analysis_len <= 0) break;
        
        int best_overlap_pos = find_best_overlap(input_samples, analysis_pos, OVERLAP_SAMPLES, SEARCH_RANGE, total_input_size);
        
        for (int j = 0; j < analysis_len; j++) {
            int input_idx = best_overlap_pos + j;
            if (input_idx >= total_input_size) break;
            
            float new_sample_float = (float)input_samples[input_idx] * amplification;
            
            float fade_in_factor = 1.0f;
            float fade_out_factor = 1.0f;

            if (j < OVERLAP_SAMPLES) {
                fade_in_factor = 0.5f * (1.0f - cosf(M_PI * (float)j / OVERLAP_SAMPLES));
                fade_out_factor = 0.5f * (1.0f + cosf(M_PI * (float)j / OVERLAP_SAMPLES));
            } else {
                fade_in_factor = 1.0f;
                fade_out_factor = 0.0f;
            }
            
            if (current_output_pos + j < merged_data_size) {
                float existing_sample_float = (float)merged_data[current_output_pos + j];
                
                float blended_sample_float = existing_sample_float * fade_out_factor + new_sample_float * fade_in_factor;
                
                merged_data[current_output_pos + j] = clamp_to_int16(blended_sample_float);
            }
        }
        
        current_input_pos += analysis_step;
        current_output_pos += synthesis_step;

        if (current_output_pos + FRAME_SIZE >= merged_data_size) {
            int32_t old_size = merged_data_size;
            merged_data_size += FRAME_SIZE;
            merged_data = (int16_t*)realloc(merged_data, merged_data_size * sizeof(int16_t));
            if (merged_data == NULL) {
                fprintf(stderr, "Memory reallocation failed!\n");
                free(input_samples);
                return;
            }
            memset(merged_data + old_size, 0, (merged_data_size - old_size) * sizeof(int16_t));
        }
    }
    
    FILE* wav_file = fopen(merge_filename, "wb");
    if (wav_file == NULL) {
        fprintf(stderr, "Error opening file for writing: %s\n", merge_filename);
        free(merged_data);
        free(input_samples);
        return;
    }

    write_wav_header(wav_file, current_output_pos, sample_rate, 1, 16);
    fwrite(merged_data, sizeof(int16_t), current_output_pos, wav_file);
    fclose(wav_file);
    
    double duration_seconds = (double)current_output_pos / sample_rate;

    free(merged_data);
    free(input_samples);
}
