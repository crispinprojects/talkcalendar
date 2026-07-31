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
