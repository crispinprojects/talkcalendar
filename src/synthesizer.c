#include "synthesizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <glib.h>  // Include GLib for GArray support

// Write WAV header to file
void write_wav_header(FILE* file, int data_size) {
    fwrite("RIFF", 1, 4, file);
    int fileSize = 36 + data_size;
    fwrite(&fileSize, sizeof(int), 1, file);

    fwrite("WAVEfmt ", 1, 8, file);
    int fmtSize = 16;
    fwrite(&fmtSize, sizeof(int), 1, file);

    short format = 1; // PCM
    fwrite(&format, sizeof(short), 1, file);

    short channels = 1; // Mono
    fwrite(&channels, sizeof(short), 1, file);

    int sampleRate = 16000;
    fwrite(&sampleRate, sizeof(int), 1, file);

    int byteRate = sampleRate * 2;
    fwrite(&byteRate, sizeof(int), 1, file);

    short blockAlign = 2;
    fwrite(&blockAlign, sizeof(short), 1, file);

    short bps = 16;
    fwrite(&bps, sizeof(short), 1, file);

    fwrite("data", 1, 4, file);
    fwrite(&data_size, sizeof(int), 1, file);
}

// Function to apply triangle windowing for smooth transitions
void apply_triangle_window(int16_t* buffer, int frame_size, int half_frame) {
    for (int i = 0; i < frame_size; i++) {
        float window;
        if (i < half_frame)
            window = (float)i / half_frame;
        else
            window = (float)(frame_size - i) / half_frame;
        
        // Apply window to the sample (multiply by window factor)
        int32_t sample = buffer[i];
        int32_t windowed_sample = (int32_t)(sample * window);
        buffer[i] = (int16_t)windowed_sample;
    }
}

// The synthesizer_vocoder with overlap-add logic
void synthesizer_vocoder(const char* text, FILE* output_file, Dictionary* dict, float tempo) {
    //printf("Speaking: %s\n", text);
 
    // Use GArray for words - this is the only change from original
    GArray* words = g_array_new(FALSE, FALSE, sizeof(char*));
 
    // Split text into words using GLib string functions for safety (replacing strtok)
    gchar** word_tokens = g_strsplit(text, " ", 0);
    if (word_tokens) {
        int i;
        for (i = 0; word_tokens[i] != NULL; i++) {
            // Skip empty tokens
            if (strlen(word_tokens[i]) > 0) {
                char* lower_word = g_ascii_strdown(word_tokens[i], -1);
                g_array_append_val(words, lower_word);
            }
        }
        g_strfreev(word_tokens);
    }
 
    // Create a fixed-size output buffer like in the original
    const int MAX_SAMPLES = 1000000;
    int16_t* output_buffer = malloc(MAX_SAMPLES * sizeof(int16_t));
    if (output_buffer == NULL) {
        //printf("Failed to allocate output buffer\n");
        g_array_free(words, TRUE);
        return;
    }
 
    // Initialize the entire buffer with zeros - this is CRITICAL
    memset(output_buffer, 0, MAX_SAMPLES * sizeof(int16_t));
 
    int output_size = 0;
    const int FRAME_SIZE = 160;
    const int analysis_step = 80;
    int synthesis_step = (int)(analysis_step / tempo);
    int currentOutStart = 0;
 
    // Process each word using GArray iteration
    for (int i = 0; i < words->len; i++) {
        char* current_word = g_array_index(words, char*, i);
 
        int diphone_count = 0; // Initialize to zero safely
        char** diphones = Dictionary_transcribeWordDecisionTree(dict, current_word, &diphone_count);
 
        if (diphones) {
            //printf("Found diphones for %s: ", current_word);
            for (int j = 0; j < diphone_count; j++) {
                //printf("%s ", diphones[j] ? diphones[j] : "(null)");
            }
            //printf("\n");
 
            int first_diphone = 1;
 
            for (int j = 0; j < diphone_count; j++) {
                if (!diphones[j] || strlen(diphones[j]) == 0) continue; // Skip null or empty entries
 
                char* diphone_name = diphones[j];
                //printf(" Processing diphone: %s\n", diphone_name);
 
                DiphoneEntry* dentry = find_diphone_entry(diphone_name);
                if (dentry) {
                    //printf(" Found diphone data: size=%u\n", dentry->size);
 
                    const int16_t* source = (const int16_t*)(dentry->data + 44);
                    int sourceSamples = (dentry->size - 44) / sizeof(int16_t);
 
                    if (sourceSamples <= 0) {
                        //printf(" Invalid diphone data size\n");
                        continue;
                    }
 
                    int currentIn = 0;
                    int currentOut = currentOutStart;
 
                    if (first_diphone) {
                        int samples_to_copy = sourceSamples;
                        if (currentOut + samples_to_copy > MAX_SAMPLES) {
                            //printf("Output buffer overflow\n");
                            break;
                        }
 
                        for (int k = 0; k < samples_to_copy; k++) {
                            if (currentOut + k < MAX_SAMPLES) {
                                output_buffer[currentOut + k] = source[k];
                            } else {
                                //printf("Buffer overflow at index %d\n", currentOut + k);
                                break;
                            }
                        }
                        currentOutStart = currentOut + samples_to_copy;
                        first_diphone = 0;
                    } else {
                        while (currentIn + FRAME_SIZE < sourceSamples) {
                            if (currentOut + FRAME_SIZE > output_size) {
                                int new_size = currentOut + FRAME_SIZE + 1000;
                                if (new_size > MAX_SAMPLES) {
                                    //printf("Buffer size exceeded\n");
                                    break;
                                }
                                output_size = new_size;
                            }
 
                            for (int k = 0; k < FRAME_SIZE; ++k) {
                                float window;
                                int half_frame = FRAME_SIZE / 2;
                                if (k < half_frame)
                                    window = (float)k / half_frame;
                                else
                                    window = (float)(FRAME_SIZE - k) / half_frame;
 
                                int32_t currentSample = output_buffer[currentOut + k];
                                int32_t newSample = (int32_t)(source[currentIn + k] * window);
                                int32_t combined = currentSample + newSample;
 
                                if (combined > 32767) combined = 32767;
                                if (combined < -32768) combined = -32768;
 
                                output_buffer[currentOut + k] = (int16_t)combined;
                            }
 
                            currentIn += analysis_step;
                            currentOut += synthesis_step;
                        }
                        currentOutStart = currentOut - synthesis_step;
                    }
                } else {
                    //printf(" Diphone not found: %s\n", diphone_name);
                }
            }
 
            // CLEANUP BLOCK: Safely unmap elements without trailing array corruption bugs
            for (int j = 0; j < diphone_count; j++) {
                if (diphones[j] != NULL) {
                    free(diphones[j]);
                    diphones[j] = NULL; // Zero out immediately to block subsequent passes
                }
            }
            free(diphones);
        } else {
            //printf("Word not found in dictionary: %s\n", current_word);
        }
    }
 
    // Write the final audio data to file
    int total_samples = currentOutStart;
    if (total_samples > 0) {
        fwrite("RIFF", 1, 4, output_file);
        int fileSize_pos = ftell(output_file);
        int dummy_fileSize = 0;
        fwrite(&dummy_fileSize, sizeof(int), 1, output_file);
 
        fwrite("WAVEfmt ", 1, 8, output_file);
        int fmtSize = 16;
        fwrite(&fmtSize, sizeof(int), 1, output_file);
 
        short format = 1; // PCM
        fwrite(&format, sizeof(short), 1, output_file);
 
        short channels = 1; // Mono
        fwrite(&channels, sizeof(short), 1, output_file);
 
        int sampleRate = 16000;
        fwrite(&sampleRate, sizeof(int), 1, output_file);
 
        int byteRate = sampleRate * 2;
        fwrite(&byteRate, sizeof(int), 1, output_file);
 
        short blockAlign = 2;
        fwrite(&blockAlign, sizeof(short), 1, output_file);
 
        short bps = 16;
        fwrite(&bps, sizeof(short), 1, output_file);
 
        fwrite("data", 1, 4, output_file);
        int data_size_pos = ftell(output_file);
        int dummy_data_size = 0;
        fwrite(&dummy_data_size, sizeof(int), 1, output_file);
 
        fwrite(output_buffer, sizeof(int16_t), total_samples, output_file);
 
        int current_pos = ftell(output_file);
        fseek(output_file, fileSize_pos, SEEK_SET);
        int final_file_size = current_pos - 8;
        fwrite(&final_file_size, sizeof(int), 1, output_file);
 
        fseek(output_file, data_size_pos, SEEK_SET);
        int final_data_size = total_samples * sizeof(int16_t);
        fwrite(&final_data_size, sizeof(int), 1, output_file);
 
        //printf("Audio saved to out.wav\n");
    } else {
       // printf("No audio data generated\n");
    }
 
    free(output_buffer);
 
    // Cleanup words GArray cleanly matching GLib requirements
    for (int i = 0; i < words->len; i++) {
        char* word = g_array_index(words, char*, i);
        g_free(word);
    }
    g_array_free(words, TRUE);
}


