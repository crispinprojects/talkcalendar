#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <stdint.h>

// Structure to hold word entries
typedef struct {
    char* word;
    char** diphones;  // Array of diphone strings
    int diphone_count;
} WordEntry;

// Structure for the dictionary
typedef struct {
    WordEntry* lexicon;
    int lexicon_size;
    int lexicon_capacity;
    
    // Consonant mapping table
    char consonant_map[256][10];
    
    // Vowel mappings
    char vowel_map[256][10];
} Dictionary;

// Function prototypes
Dictionary* Dictionary_new();
void Dictionary_free(Dictionary* dict);
char** Dictionary_transcribeWordDecisionTree(Dictionary* dict, const char* word, int* diphone_count);
void Dictionary_initializeLexicon(Dictionary* dict);
//void Dictionary_setupG2PRules(Dictionary* dict);

// Individual prediction functions - we'll keep these for now
const char* predictA(char p, char c, char n, char nn, char nnn);
const char* predictB(char p, char c, char n, char nn, char nnn);
const char* predictC(char p, char c, char n, char nn, char nnn);
const char* predictD(char p, char c, char n, char nn, char nnn);
const char* predictE(char p, char c, char n, char nn, char nnn);
const char* predictF(char p, char c, char n, char nn, char nnn);
const char* predictG(char p, char c, char n, char nn, char nnn);
const char* predictH(char p, char c, char n, char nn, char nnn);
const char* predictI(char p, char c, char n, char nn, char nnn);
const char* predictJ(char p, char c, char n, char nn, char nnn);
const char* predictK(char p, char c, char n, char nn, char nnn);
const char* predictL(char p, char c, char n, char nn, char nnn);
const char* predictM(char p, char c, char n, char nn, char nnn);
const char* predictN(char p, char c, char n, char nn, char nnn);
const char* predictO(char p, char c, char n, char nn, char nnn);
const char* predictP(char p, char c, char n, char nn, char nnn);
const char* predictQ(char p, char c, char n, char nn, char nnn);
const char* predictR(char p, char c, char n, char nn, char nnn);
const char* predictS(char p, char c, char n, char nn, char nnn);
const char* predictT(char p, char c, char n, char nn, char nnn);
const char* predictU(char p, char c, char n, char nn, char nnn);
const char* predictV(char p, char c, char n, char nn, char nnn);
const char* predictW(char p, char c, char n, char nn, char nnn);
const char* predictX(char p, char c, char n, char nn, char nnn);
const char* predictY(char p, char c, char n, char nn, char nnn);
const char* predictZ(char p, char c, char n, char nn, char nnn);

// Helper functions
char** buildDiphoneList(const char** phonemes, int phoneme_count);
void Dictionary_addWord(Dictionary* dict, const char* word, const char** diphones, int diphone_count);

#endif // DICTIONARY_H
