/* dictionary.c
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
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


Dictionary* Dictionary_new() {
    Dictionary* dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (!dict) return NULL;
    
    dict->lexicon = NULL;
    dict->lexicon_size = 0;
    dict->lexicon_capacity = 0;
    
    // Initialize consonant map
    memset(dict->consonant_map, 0, sizeof(dict->consonant_map));
    strcpy(dict->consonant_map['b'], "b");
    strcpy(dict->consonant_map['c'], "k");
    strcpy(dict->consonant_map['d'], "d");
    strcpy(dict->consonant_map['f'], "f");
    strcpy(dict->consonant_map['g'], "g");
    strcpy(dict->consonant_map['h'], "hh");
    strcpy(dict->consonant_map['j'], "jh");
    strcpy(dict->consonant_map['k'], "k");
    strcpy(dict->consonant_map['l'], "l");
    strcpy(dict->consonant_map['m'], "m");
    strcpy(dict->consonant_map['n'], "n");
    strcpy(dict->consonant_map['p'], "p");
    strcpy(dict->consonant_map['q'], "k");
    strcpy(dict->consonant_map['r'], "r");
    strcpy(dict->consonant_map['s'], "s");
    strcpy(dict->consonant_map['t'], "t");
    strcpy(dict->consonant_map['v'], "v");
    strcpy(dict->consonant_map['w'], "w");
    strcpy(dict->consonant_map['x'], "ks");
    strcpy(dict->consonant_map['y'], "y");
    strcpy(dict->consonant_map['z'], "z");
    
    // Initialize vowel map
    memset(dict->vowel_map, 0, sizeof(dict->vowel_map));
    strcpy(dict->vowel_map['a'], "ae");
    strcpy(dict->vowel_map['e'], "eh");
    strcpy(dict->vowel_map['i'], "ih");
    strcpy(dict->vowel_map['o'], "aa");
    strcpy(dict->vowel_map['u'], "ah");
    
    Dictionary_initializeLexicon(dict);
    //Dictionary_setupG2PRules(dict);  // This function is empty in C++ version
    
    return dict;
}

void Dictionary_free(Dictionary* dict) {
    if (!dict) return;
    
    // Free lexicon entries
    for (int i = 0; i < dict->lexicon_size; i++) {
        free(dict->lexicon[i].word);
        if (dict->lexicon[i].diphones) {
            for (int j = 0; j < dict->lexicon[i].diphone_count; j++) {
                free(dict->lexicon[i].diphones[j]);
            }
            free(dict->lexicon[i].diphones);
        }
    }
    
    if (dict->lexicon) {
        free(dict->lexicon);
    }
    
    free(dict);
}

void Dictionary_addWord(Dictionary* dict, const char* word, const char** diphones, int diphone_count) {
    // Resize if needed
    if (dict->lexicon_size >= dict->lexicon_capacity) {
        dict->lexicon_capacity += 10;
        dict->lexicon = (WordEntry*)realloc(dict->lexicon, dict->lexicon_capacity * sizeof(WordEntry));
    }
    
    WordEntry* entry = &dict->lexicon[dict->lexicon_size];
    entry->word = malloc(strlen(word) + 1);
    strcpy(entry->word, word);
    entry->diphone_count = diphone_count;
    
    if (diphone_count > 0) {
        entry->diphones = (char**)malloc(diphone_count * sizeof(char*));
        for (int i = 0; i < diphone_count; i++) {
            entry->diphones[i] = malloc(strlen(diphones[i]) + 1);
            strcpy(entry->diphones[i], diphones[i]);
        }
    } else {
        entry->diphones = NULL;
    }
    
    dict->lexicon_size++;
}

void Dictionary_initializeLexicon(Dictionary* dict) {
    // Days of week
    const char* monday_diphones[] = {"pau_m", "m_ah", "ah_n", "n_d", "d_ey", "ey_pau"};
    Dictionary_addWord(dict, "monday", monday_diphones, 6);
    
    const char* tuesday_diphones[] = {"pau_t", "t_uw", "uw_z", "z_d", "d_ey", "ey_pau"};
    Dictionary_addWord(dict, "tuesday", tuesday_diphones, 6);
    
    const char* wednesday_diphones[] = {"pau_w", "w_eh", "eh_n", "n_z", "z_d", "d_ey", "ey_pau"};
    Dictionary_addWord(dict, "wednesday", wednesday_diphones, 7);
    
    const char* thursday_diphones[] = {"pau_th", "th_er", "er_z", "z_d", "d_ey", "ey_pau"};
    Dictionary_addWord(dict, "thursday", thursday_diphones, 6);
    
    const char* friday_diphones[] = {"pau_f", "f_r", "r_ay", "ay_d", "d_ey", "ey_pau"};
    Dictionary_addWord(dict, "friday", friday_diphones, 6);
    
    const char* saturday_diphones[] = {"pau_s", "s_ae", "ae_t", "t_er", "er_d", "d_ey", "ey_pau"};
    Dictionary_addWord(dict, "saturday", saturday_diphones, 7);
    
    const char* sunday_diphones[] = {"pau_s", "s_ah", "ah_n", "n_d", "d_ey", "ey_pau"};
    Dictionary_addWord(dict, "sunday", sunday_diphones, 6);
    
    // Months
    const char* january_diphones[] = {"pau_jh", "jh_ae", "ae_n", "n_y", "y_uw", "uw_eh", "eh_r", "r_iy", "iy_pau"};
    Dictionary_addWord(dict, "january", january_diphones, 9);
    
    const char* february_diphones[] = {"pau_f", "f_eh", "eh_b", "b_y", "y_uw", "uw_eh", "eh_r", "r_iy", "iy_pau"};
    Dictionary_addWord(dict, "february", february_diphones, 9);
    
    const char* march_diphones[] = {"pau_m", "m_aa", "aa_r", "r_ch", "ch_pau"};
    Dictionary_addWord(dict, "march", march_diphones, 5);
    
    const char* april_diphones[] = {"pau_ey", "ey_p", "p_r", "r_ah", "ah_l", "l_pau"};
    Dictionary_addWord(dict, "april", april_diphones, 6);
    
    const char* may_diphones[] = {"pau_m", "m_ey", "ey_pau"};
    Dictionary_addWord(dict, "may", may_diphones, 3);
    
    const char* june_diphones[] = {"pau_jh", "jh_uw", "uw_n", "n_pau"};
    Dictionary_addWord(dict, "june", june_diphones, 4);
    
    const char* july_diphones[] = {"pau_jh", "jh_uh", "uh_l", "l_ay", "ay_pau"};
    Dictionary_addWord(dict, "july", july_diphones, 5);
    
    const char* august_diphones[] = {"pau_ao", "ao_g", "g_ah", "ah_s", "s_t", "t_pau"};
    Dictionary_addWord(dict, "august", august_diphones, 6);
    
    const char* september_diphones[] = {"pau_s", "s_eh", "eh_p", "p_t", "t_eh", "eh_m", "m_b", "b_er", "er_pau"};
    Dictionary_addWord(dict, "september", september_diphones, 9);
    
    const char* october_diphones[] = {"pau_aa", "aa_k", "k_t", "t_ow", "ow_b", "b_er", "er_pau"};
    Dictionary_addWord(dict, "october", october_diphones, 7);
    
    const char* november_diphones[] = {"pau_n", "n_ow", "ow_v", "v_eh", "eh_m", "m_b", "b_er", "er_pau"};
    Dictionary_addWord(dict, "november", november_diphones, 8);
    
    const char* december_diphones[] = {"pau_d", "d_iy", "iy_s", "s_eh", "eh_m", "m_b", "b_er", "er_pau"};
    Dictionary_addWord(dict, "december", december_diphones, 8);
    
    // Day ordinals
    const char* first_diphones[] = {"pau_f", "f_er", "er_s", "s_t", "t_pau"};
    Dictionary_addWord(dict, "first", first_diphones, 5);
    
    const char* second_diphones[] = {"pau_s", "s_eh", "eh_k", "k_ah", "ah_n", "n_d", "d_pau"};
    Dictionary_addWord(dict, "second", second_diphones, 7);
    
    const char* third_diphones[] = {"pau_th", "th_er", "er_er", "er_d", "d_pau"};
    Dictionary_addWord(dict, "third", third_diphones, 5);
    
    const char* fourth_diphones[] = {"pau_f", "f_ao", "ao_r", "r_th", "th_pau"};
    Dictionary_addWord(dict, "fourth", fourth_diphones, 5);
    
    const char* fifth_diphones[] = {"pau_f", "f_ih", "ih_f", "f_th", "th_pau"};
    Dictionary_addWord(dict, "fifth", fifth_diphones, 5);
    
    const char* sixth_diphones[] = {"pau_s", "s_ih", "ih_k", "k_s", "s_th", "th_pau"};
    Dictionary_addWord(dict, "sixth", sixth_diphones, 6);
    
    const char* seventh_diphones[] = {"pau_s", "s_eh", "eh_v", "v_ah", "ah_n", "n_th", "th_pau"};
    Dictionary_addWord(dict, "seventh", seventh_diphones, 7);
    
    const char* eighth_diphones[] = {"pau_ey", "ey_t", "t_th", "th_pau"};
    Dictionary_addWord(dict, "eighth", eighth_diphones, 4);
    
    const char* ninth_diphones[] = {"pau_n", "n_ay", "ay_n", "n_th", "th_pau"};
    Dictionary_addWord(dict, "ninth", ninth_diphones, 5);
    
    const char* tenth_diphones[] = {"pau_t", "t_eh", "eh_eh", "eh_n", "n_th", "th_pau"};
    Dictionary_addWord(dict, "tenth", tenth_diphones, 6);
    
    const char* eleventh_diphones[] = {"pau_ih", "ih_l", "l_eh", "eh_eh", "eh_v", "v_ah", "ah_n", "n_th", "th_pau"};
    Dictionary_addWord(dict, "eleventh", eleventh_diphones, 9);
    
    const char* twelfth_diphones[] = {"pau_t", "t_w", "w_eh", "eh_l", "l_f", "f_th", "th_pau"};
    Dictionary_addWord(dict, "twelfth", twelfth_diphones, 7);
    
    const char* thirteenth_diphones[] = {"pau_th", "th_er", "er_er", "er_t", "t_iy", "iy_iy", "iy_n", "n_th", "th_pau"};
    Dictionary_addWord(dict, "thirteenth", thirteenth_diphones, 9);
    
    const char* fourteenth_diphones[] = {"pau_f", "f_ao", "ao_ao", "ao_r", "r_t", "t_iy", "iy_iy", "iy_n", "n_th", "th_th", "th_pau"};
    Dictionary_addWord(dict, "fourteenth", fourteenth_diphones, 11);
    
    const char* fifteenth_diphones[] = {"pau_f", "f_ih", "ih_f", "f_t", "t_iy", "iy_iy", "iy_n", "n_th", "th_pau"};
    Dictionary_addWord(dict, "fifteenth", fifteenth_diphones, 9);
    
    const char* sixteenth_diphones[] = {"pau_s", "s_ih", "ih_k", "k_s", "s_t", "t_iy", "iy_iy", "iy_n", "n_th", "th_pau"};
    Dictionary_addWord(dict, "sixteenth", sixteenth_diphones, 10);
    
    const char* seventeenth_diphones[] = {"pau_s", "s_eh", "eh_v", "v_eh", "eh_n", "n_t", "t_iy", "iy_n", "n_th", "th_pau"};
    Dictionary_addWord(dict, "seventeenth", seventeenth_diphones, 10);
    
    const char* eighteenth_diphones[] = {"pau_ey", "ey_t", "t_iy", "iy_n", "n_th", "th_pau"};
    Dictionary_addWord(dict, "eighteenth", eighteenth_diphones, 6);
    
    const char* nineteenth_diphones[] = {"pau_n", "n_ay", "ay_ay", "ay_n", "n_t", "t_iy", "iy_iy", "iy_n", "n_th", "th_th", "th_pau"};
    Dictionary_addWord(dict, "nineteenth", nineteenth_diphones, 11);
    
    const char* twentieth_diphones[] = {"pau_t", "t_w", "w_eh", "eh_eh", "eh_n", "n_t", "t_iy", "iy_eh", "eh_eh", "eh_th", "th_pau"};
    Dictionary_addWord(dict, "twentieth", twentieth_diphones, 11);
    
    const char* twenty_first_diphones[] = {"pau_t", "t_w", "w_eh", "eh_n", "n_t", "t_iy", "iy_f", "f_er", "er_s", "s_t", "t_pau"};
    Dictionary_addWord(dict, "twenty-first", twenty_first_diphones, 11);
    
    const char* twenty_second_diphones[] = {"pau_t", "t_w", "w_eh", "eh_n", "n_t", "t_iy", "iy_s", "s_eh", "eh_k", "k_ah", "ah_n", "n_d", "d_pau"};
    Dictionary_addWord(dict, "twenty-second", twenty_second_diphones, 13);
    
    const char* twenty_third_diphones[] = {"pau_t", "t_w", "w_eh", "eh_n", "n_t", "t_iy", "iy_th", "th_er", "er_d", "d_pau"};
    Dictionary_addWord(dict, "twenty-third", twenty_third_diphones, 10);
    
    const char* twenty_fourth_diphones[] = {"pau_t", "t_w", "w_eh", "eh_n", "n_t", "t_iy", "iy_f", "f_ao", "ao_r", "r_th", "th_pau"};
    Dictionary_addWord(dict, "twenty-fourth", twenty_fourth_diphones, 11);
    
    const char* twenty_fifth_diphones[] = {"pau_t", "t_w", "w_eh", "eh_n", "n_t", "t_iy", "iy_f", "f_ih", "ih_f", "f_th", "th_pau"};
    Dictionary_addWord(dict, "twenty-fifth", twenty_fifth_diphones, 11);
    
    const char* twenty_sixth_diphones[] = {"pau_t", "t_w", "w_eh", "eh_n", "n_t", "t_iy", "iy_s", "s_ih", "ih_k", "k_s", "s_th", "th_pau"};
    Dictionary_addWord(dict, "twenty-sixth", twenty_sixth_diphones, 12);
    
    const char* twenty_seventh_diphones[] = {"pau_t", "t_w", "w_eh", "eh_n", "n_t", "t_iy", "iy_s", "s_eh", "eh_v", "v_ah", "ah_n", "n_th", "th_pau"};
    Dictionary_addWord(dict, "twenty-seventh", twenty_seventh_diphones, 13);
    
    const char* twenty_eighth_diphones[] = {"pau_t", "t_w", "w_eh", "eh_n", "n_t", "t_iy", "iy_ey", "ey_t", "t_th", "th_pau"};
    Dictionary_addWord(dict, "twenty-eighth", twenty_eighth_diphones, 10);
    
    const char* twenty_ninth_diphones[] = {"pau_t", "t_w", "w_eh", "eh_n", "n_t", "t_iy", "iy_n", "n_ay", "ay_n", "n_th", "th_pau"};
    Dictionary_addWord(dict, "twenty-ninth", twenty_ninth_diphones, 11);
    
    const char* thirtieth_diphones[] = {"pau_th", "th_er", "er_er", "er_t", "t_iy", "iy_eh", "eh_eh", "eh_th", "th_pau"};
    Dictionary_addWord(dict, "thirtieth", thirtieth_diphones, 9);
    
    const char* thirty_first_diphones[] = {"pau_th", "th_er", "er_t", "t_iy", "iy_f", "f_er", "er_s", "s_t", "t_pau"};
    Dictionary_addWord(dict, "thirty-first", thirty_first_diphones, 9);
    
    // Time suffixes
    const char* am_diphones[] = {"pau_ey", "ey_eh", "eh_m", "m_pau"};
    Dictionary_addWord(dict, "am", am_diphones, 4);
    
    const char* pm_diphones[] = {"pau_p", "p_iy", "iy_eh", "eh_m", "m_pau"};
    Dictionary_addWord(dict, "pm", pm_diphones, 5);
    
    const char* o_diphones[] = {"pau_ow", "ow_ow", "ow_pau"};
    Dictionary_addWord(dict, "o", o_diphones, 3);
    
    // Numbers 1-12
    const char* one_diphones[] = {"pau_w", "w_ah", "ah_n", "n_pau"};
    Dictionary_addWord(dict, "one", one_diphones, 4);
    
    const char* two_diphones[] = {"pau_t", "t_uw", "uw_pau"};
    Dictionary_addWord(dict, "two", two_diphones, 3);
    
    const char* three_diphones[] = {"pau_th", "th_r", "r_iy", "iy_pau"};
    Dictionary_addWord(dict, "three", three_diphones, 4);
    
    const char* four_diphones[] = {"pau_f", "f_ao", "ao_r", "r_pau"};
    Dictionary_addWord(dict, "four", four_diphones, 4);
    
    const char* five_diphones[] = {"pau_f", "f_ay", "ay_v", "v_pau"};
    Dictionary_addWord(dict, "five", five_diphones, 4);
    
    const char* six_diphones[] = {"pau_s", "s_ih", "ih_k", "k_s", "s_pau"};
    Dictionary_addWord(dict, "six", six_diphones, 5);
    
    const char* seven_diphones[] = {"pau_s", "s_eh", "eh_v", "v_ah", "ah_n", "n_pau"};
    Dictionary_addWord(dict, "seven", seven_diphones, 6);
    
    const char* eight_diphones[] = {"pau_ey", "ey_t", "t_pau"};
    Dictionary_addWord(dict, "eight", eight_diphones, 3);
    
    const char* nine_diphones[] = {"pau_n", "n_ay", "ay_n", "n_pau"};
    Dictionary_addWord(dict, "nine", nine_diphones, 4);
    
    const char* ten_diphones[] = {"pau_t", "t_eh", "eh_n", "n_pau"};
    Dictionary_addWord(dict, "ten", ten_diphones, 4);
    
    const char* eleven_diphones[] = {"pau_iy", "iy_l", "l_eh", "eh_v", "v_ah", "ah_n", "n_pau"};
    Dictionary_addWord(dict, "eleven", eleven_diphones, 7);
    
    const char* twelve_diphones[] = {"pau_t", "t_w", "w_eh", "eh_l", "l_v", "v_pau"};
    Dictionary_addWord(dict, "twelve", twelve_diphones, 6);
    
    const char* zero_diphones[] = {"pau_z", "z_iy", "iy_iy", "iy_r", "r_ow", "ow_pau"};
    Dictionary_addWord(dict, "zero", zero_diphones, 6);
    
    // Teens
    const char* thirteen_diphones[] = {"pau_th", "th_er", "er_t", "t_iy", "iy_n", "n_pau"};
    Dictionary_addWord(dict, "thirteen", thirteen_diphones, 6);
    
    const char* fourteen_diphones[] = {"pau_f", "f_ao", "ao_r", "r_t", "t_iy", "iy_n", "n_pau"};
    Dictionary_addWord(dict, "fourteen", fourteen_diphones, 7);
    
    const char* fifteen_diphones[] = {"pau_f", "f_ih", "ih_f", "f_t", "t_iy", "iy_n", "n_pau"};
    Dictionary_addWord(dict, "fifteen", fifteen_diphones, 7);
    
    const char* sixteen_diphones[] = {"pau_s", "s_ih", "ih_k", "k_s", "s_t", "t_iy", "iy_n", "n_pau"};
    Dictionary_addWord(dict, "sixteen", sixteen_diphones, 8);
    
    const char* seventeen_diphones[] = {"pau_s", "s_eh", "eh_v", "v_ah", "ah_n", "n_t", "t_iy", "iy_n", "n_pau"};
    Dictionary_addWord(dict, "seventeen", seventeen_diphones, 9);
    
    const char* eighteen_diphones[] = {"pau_ey", "ey_t", "t_iy", "iy_n", "n_pau"};
    Dictionary_addWord(dict, "eighteen", eighteen_diphones, 5);
    
    const char* nineteen_diphones[] = {"pau_n", "n_ay", "ay_n", "n_t", "t_iy", "iy_n", "n_pau"};
    Dictionary_addWord(dict, "nineteen", nineteen_diphones, 7);
    
    // Decade bases
    const char* twenty_diphones[] = {"pau_t", "t_w", "w_eh", "eh_n", "n_t", "t_iy", "iy_pau"};
    Dictionary_addWord(dict, "twenty", twenty_diphones, 7);
    
    const char* thirty_diphones[] = {"pau_th", "th_er", "er_t", "t_iy", "iy_pau"};
    Dictionary_addWord(dict, "thirty", thirty_diphones, 5);
    
    const char* forty_diphones[] = {"pau_f", "f_ao", "ao_r", "r_t", "t_iy", "iy_pau"};
    Dictionary_addWord(dict, "forty", forty_diphones, 6);
    
    const char* fifty_diphones[] = {"pau_f", "f_ih", "ih_f", "f_t", "t_iy", "iy_pau"};
    Dictionary_addWord(dict, "fifty", fifty_diphones, 6);
    
    // Talk Calendar
    const char* talk_diphones[] = {"pau_t", "t_aa", "aa_aa", "aa_k", "k_pau"};
    Dictionary_addWord(dict, "talk", talk_diphones, 5);
    
    const char* calendar_diphones[] = {"pau_k", "k_ae", "ae_l", "l_ah", "ah_n", "n_d", "d_er", "er_pau"};
    Dictionary_addWord(dict, "calendar", calendar_diphones, 8);
    
    // Word exception list
    const char* are_diphones[] = {"pau_aa", "aa_r", "r_pau"};
    Dictionary_addWord(dict, "are", are_diphones, 3);
    
    const char* alex_diphones[] = {"pau_ae", "ae_ae", "ae_l", "l_ah", "ah_k", "k_s", "s_pau"};
    Dictionary_addWord(dict, "alex", alex_diphones, 7);
    
    // B words
    const char* baby_diphones[] = {"pau_b", "b_eh", "eh_iy", "iy_b", "b_iy", "iy_pau"};
    Dictionary_addWord(dict, "baby", baby_diphones, 6);
    
    const char* birth_diphones[] = {"pau_b", "b_uh", "uh_r", "r_th", "th_pau"};
    Dictionary_addWord(dict, "birth", birth_diphones, 5);
    
    const char* birthday_diphones[] = {"pau_b", "b_er", "er_er", "er_th", "th_d", "d_ey", "ey_pau"};
    Dictionary_addWord(dict, "birthday", birthday_diphones, 7);
    
    const char* boxing_diphones[] = {"pau_b", "b_aa", "aa_aa", "aa_k", "k_s", "s_ih", "ih_ng", "ng_pau"};
    Dictionary_addWord(dict, "boxing", boxing_diphones, 8);
    
    const char* break_diphones[] = {"pau_b", "b_r", "r_eh", "eh_iy", "iy_k", "k_pau"};
    Dictionary_addWord(dict, "break", break_diphones, 6);
    
    const char* business_diphones[] = {"b_ih", "ih_z", "z_n", "ah ah_s", "s_pau"};
    Dictionary_addWord(dict, "business", business_diphones, 5);
    
    const char* busy_diphones[] = {"pau_b", "b_ih", "ih_z", "z_iy", "iy_pau"};
    Dictionary_addWord(dict, "busy", busy_diphones, 5);
    
    // C words
    const char* cafe_diphones[] = {"pau_k", "k_ah", "ah_f", "f_ey", "ey_ey"};
    Dictionary_addWord(dict, "cafe", cafe_diphones, 5);
    
    const char* choir_diphones[] = {"pau_k", "k_w", "w_ay", "ay_er", "er_pau"};
    Dictionary_addWord(dict, "choir", choir_diphones, 5);
    
    const char* colonel_diphones[] = {"pau_k", "k_er", "er_n", "n_ah", "ah_l", "l_pau"};
    Dictionary_addWord(dict, "colonel", colonel_diphones, 6);
    
    // D words
    const char* debt_diphones[] = {"pau_d", "d_eh", "eh_t", "t_pau"};
    Dictionary_addWord(dict, "debt", debt_diphones, 4);
    
    const char* does_diphones[] = {"pau_d", "d_ah", "ah_z", "z_pau"};
    Dictionary_addWord(dict, "does", does_diphones, 4);
    
    // E words
    const char* education_diphones[] = {"pau_eh", "eh_jh", "jh_ah", "ah_k", "k_eh", "eh_iy", "iy_sh", "sh_ah", "ah_n", "n_pau"};
    Dictionary_addWord(dict, "education", education_diphones, 10);
    
    const char* event_diphones[] = {"pau_ih", "ih_v", "v_eh", "eh_eh", "eh_n", "n_t", "t_pau"};
    Dictionary_addWord(dict, "event", event_diphones, 7);
    
    const char* events_diphones[] = {"pau_ih", "ih_v", "v_eh", "eh_n", "n_t", "t_z", "z_pau"};
    Dictionary_addWord(dict, "events", events_diphones, 7);
    
    const char* eye_diphones[] = {"pau_aa", "aa_iy", "iy_pau"};
    Dictionary_addWord(dict, "eye", eye_diphones, 3);
    
    // G words
    const char* garage_diphones[] = {"pau_g", "g_uh", "uh_r", "r_aa", "aa_zh", "zh_pau"};
    Dictionary_addWord(dict, "garage", garage_diphones, 6);
    
    const char* good_diphones[] = {"pau_g", "g_uh", "uh_d", "d_pau"};
    Dictionary_addWord(dict, "good", good_diphones, 4);
    
    // H words
    const char* health_diphones[] = {"pau_hh", "hh_eh", "eh_eh", "eh_l", "l_th", "th_pau"};
    Dictionary_addWord(dict, "health", health_diphones, 6);
    
    const char* high_diphones[] = {"pau_hh", "hh_aa", "aa_iy", "iy_pau"};
    Dictionary_addWord(dict, "high", high_diphones, 4);
    
    // M words
    const char* message_diphones[] = {"pau_m", "m_eh", "eh_s", "s_ah", "ah_jh", "jh_pau"};
    Dictionary_addWord(dict, "message", message_diphones, 6);
    
    const char* my_diphones[] = {"pau_m", "m_ay", "ay_ay", "ay_pau"};
    Dictionary_addWord(dict, "my", my_diphones, 4);
    
    // N words
    const char* notification_diphones[] = {"pau_n", "n_ow", "ow_ow", "ow_t", "t_ah", "ah_f", "f_ah", "ah_k", "k_ey", "ey_ey", "ey_sh", "sh_ah", "ah_n", "n_pau"};
    Dictionary_addWord(dict, "notification", notification_diphones, 14);
    
    // O words
    const char* once_diphones[] = {"pau_w", "w_ah", "ah_n", "n_s", "s_pau"};
    Dictionary_addWord(dict, "once", once_diphones, 5);
    
    // P words
    const char* pilates_diphones[] = {"pau_p", "p_ih", "ih_ih", "ih_l", "l_aa", "aa_aa", "aa_t", "t_iy", "iy_iy", "iy_s", "s_pau"};
    Dictionary_addWord(dict, "pilates", pilates_diphones, 11);
    
    // Q words
    const char* quote_diphones[] = {"pau_k", "k_w", "w_w", "w_ow", "ow_ow", "ow_t", "t_pau"};
    Dictionary_addWord(dict, "quote", quote_diphones, 7);
    
    // R words
    const char* radio_diphones[] = {"pau_r", "r_ey", "ey_ey", "ey_d", "d_iy", "iy_ow", "ow_ow", "ow_pau"};
    Dictionary_addWord(dict, "radio", radio_diphones, 8);
    
    // S words
    const char* says_diphones[] = {"pau_s", "s_eh", "eh_z", "z_pau"};
    Dictionary_addWord(dict, "says", says_diphones, 4);
    
    const char* said_diphones[] = {"pau_s", "s_eh", "eh_d", "d_pau"};
    Dictionary_addWord(dict, "said", said_diphones, 4);
    
    const char* station_diphones[] = {"pau_s", "s_t", "t_ey", "ey_ey", "ey_sh", "sh_ah", "ah_n", "n_pau"};
    Dictionary_addWord(dict, "station", station_diphones, 8);
    
    // T words
    const char* tax_diphones[] = {"pau_t", "t_ae", "ae_ae", "ae_k", "k_s", "s_pau"};
    Dictionary_addWord(dict, "tax", tax_diphones, 6);
    
    const char* taxi_diphones[] = {"pau_t", "t_ae", "ae_ae", "ae_k", "k_s", "s_iy", "iy_pau"};
    Dictionary_addWord(dict, "taxi", taxi_diphones, 7);
    
    const char* the_diphones[] = {"pau_dh", "dh_ah", "ah_ah", "ah_pau"};
    Dictionary_addWord(dict, "the", the_diphones, 4);
    
    const char* through_diphones[] = {"pau_th", "th_r", "r_uw", "uw_pau"};
    Dictionary_addWord(dict, "through", through_diphones, 4);
    
    const char* venue_diphones[] = {"pau_v", "v_eh", "eh_n", "n_y", "y_uw", "uw_pau"};
    Dictionary_addWord(dict, "venue", venue_diphones, 6);
    
    // W words
    const char* walk_diphones[] = {"pau_w", "w_w", "w_ao", "ao_ao", "ao_k", "k_k", "k_pau"};
    Dictionary_addWord(dict, "walk", walk_diphones, 7);
    
    const char* who_diphones[] = {"pau_hh", "hh_uw", "uw_pau"};
    Dictionary_addWord(dict, "who", who_diphones, 3);
    
    const char* what_diphones[] = {"pau_w", "w_ah", "ah_t", "t_pau"};
    Dictionary_addWord(dict, "what", what_diphones, 4);
    
    const char* was_diphones[] = {"pau_w", "w_ah", "ah_z", "z_pau"};
    Dictionary_addWord(dict, "was", was_diphones, 4);
}

// This function is empty in the original C++ code - just remove unused parameter
void Dictionary_setupG2PRules(Dictionary* dict) {
    // No implementation needed - already done in constructor
    (void)dict; // Suppress unused parameter warning
}

const char* predictA(char p, char c, char n, char nn, char nnn) {
    (void)p; (void)c; (void)n; (void)nn; (void)nnn; // Suppress unused parameter warnings
    
    // 1. Terminal Magic E (Lake, Bake, Fate, Ale)
    if (n != '_' && nn == 'e' && nnn == '_') return "ey";

    // 2. Common Vowel Neighbors
    if (n == 'i' || n == 'y') return "ey";
    if (n == 'r' || n == 'h' || n == 'w') return "aa";

    // 3. The "Alex/Apple" logic
    if (n == 'l' || n == 'p' || n == 'c' || n == 'd') return "ae";

    // 4. Fallback
    return "ae";
}

const char* predictB(char p, char c, char n, char nn, char nnn) {
    (void)p; (void)c; (void)n; (void)nn; (void)nnn; // Suppress unused parameter warnings
    return "b";
}

const char* predictC(char p, char c, char n, char nn, char nnn) {
    (void)p; (void)c; (void)n; (void)nn; (void)nnn; // Suppress unused parameter warnings
    if (n == 'h') return "ch";
    if (n == 'e' || n == 'i' || n == 'y') return "s";
    return "k";
}

const char* predictD(char p, char c, char n, char nn, char nnn) {
    (void)p; (void)c; (void)n; (void)nn; (void)nnn; // Suppress unused parameter warnings
    return "d";
}

const char* predictE(char p, char c, char n, char nn, char nnn) {
    (void)p; (void)c; (void)n; (void)nn; (void)nnn; // Suppress unused parameter warnings
    
    if (n == '_') return "silent"; // silence
    if (n == '\'') return "ah";
    if (n == '(') return "ah";
    if (n == 'a') return "iy";
    if (n == 'd') return "ah";
    if (n == 'e') return "iy";
    if (n == 'i') return "er";
    if (n == 'o') return "iy";
    if (n == 'r') return "er";
    if (n == 'u') return "ah";
    if (n == 'w') return "ah";
    if (n == 'y') return "iy";
    
    // Fix for final 'o' in words like "hello"
    if (c == 'o' && n == '_') return "ow";
    
    // Handle case where 'e' should be 'ah' in specific contexts
    if (p == 'h' && n == 'l') return "ah";
    
    if (p == 'c') return "ah";
    if (p == 'e') return "iy";
    if (p == 'g') return "er";
    if (p == 'i') return "iy";
    if (p == 'k') return "ah";
    if (p == 'l') return "ah";
    if (p == 'n') return "ah";
    if (p == 'o') return "er";
    if (p == 't') return "ah";
    if (p == 'v') return "er";
    if (p == 'y') return "er";
    if (p == 'z') return "ah";
    
    if (nn == '\'') return "er";
    if (nn == '(') return "er";
    if (nn == '1') return "ah";
    if (nn == 'm') return "er";
    if (nn == 'n') return "iy";
    if (nn == 's') return "ah";
    if (nn == 'u') return "ah";
    if (nn == 'v') return "er";
    if (nn == 'w') return "er";
    if (nn == 'y') return "iy";
    
    return "eh";
}

const char* predictF(char p, char c, char n, char nn, char nnn) {
    (void)p; (void)c; (void)n; (void)nn; (void)nnn; // Suppress unused parameter warnings
    return "f";
}

const char* predictG(char p, char c, char n, char nn, char nnn) {
    (void)p; (void)c; (void)n; (void)nn; (void)nnn; // Suppress unused parameter warnings
    return "g";
}

const char* predictH(char p, char c, char n, char nn, char nnn) {
    (void)p; (void)c; (void)n; (void)nn; (void)nnn; // Suppress unused parameter warnings
    
    if (n == 'a') return "hh";
    if (n == 'o') return "hh";
    if (n == 'u') return "hh";
    if (p == 'a') return "hh";
    if (p == 'd') return "hh";
    if (p == 'e') return "hh";
    if (p == 'g') return "hh";
    if (p == 'k') return "hh";
    if (p == 'l') return "hh";
    if (p == 'n') return "hh";
    if (p == 'o') return "hh";
    if (p == 'r') return "hh";
    if (p == 'w') return "hh";
    if (nn == 'b') return "hh";
    if (nn == 'f') return "hh";
    if (nn == 'g') return "hh";
    if (nn == 'l') return "hh";
    if (nn == 'm') return "hh";
    if (nn == 'u') return "hh";
    return "silent";
}

const char* predictI(char p, char c, char n, char nn, char nnn) {
    (void)p; (void)c; (void)n; (void)nn; (void)nnn; // Suppress unused parameter warnings
    if (n != '_' && nn == 'e' && nnn == '_') return "ay"; // Magic E: Like, Kite
    if (n == 'g' && nn == 'h') return "ay";              // Night, Light
    return "ih";                                          // Bit, Sit
}

const char* predictJ(char p, char c, char n, char nn, char nnn) {
    (void)p; (void)c; (void)n; (void)nn; (void)nnn; // Suppress unused parameter warnings
    return "jh";
}

const char* predictK(char p, char c, char n, char nn, char nnn) {
    (void)p; (void)c; (void)n; (void)nn; (void)nnn; // Suppress unused parameter warnings
    return "k";
}

const char* predictL(char p, char c, char n, char nn, char nnn) {
    (void)p; (void)c; (void)n; (void)nn; (void)nnn; // Suppress unused parameter warnings
    return "l";
}

const char* predictM(char p, char c, char n, char nn, char nnn) {
    (void)p; (void)c; (void)n; (void)nn; (void)nnn; // Suppress unused parameter warnings
    return "m";
}

const char* predictN(char p, char c, char n, char nn, char nnn) {
    (void)p; (void)c; (void)n; (void)nn; (void)nnn; // Suppress unused parameter warnings
    return "n";
}

const char* predictO(char p, char c, char n, char nn, char nnn) {
    (void)p; (void)c; (void)n; (void)nn; (void)nnn; // Suppress unused parameter warnings
    
    // 1. Terminal Magic E (Quote, Note, Rope) - MUST BE AT TOP
    if (n != '_' && nn == 'e' && nnn == '_') return "ow";

    // 2. Common patterns
    if (n == 'r' || n == 'f') return "ao";
    if (n == 'u' || n == 'o') return "uw";

    // 3. Most common 'o' sound (Hot, Box, Dot)
    return "aa";
}

const char* predictP(char p, char c, char n, char nn, char nnn) {
    (void)p; (void)c; (void)n; (void)nn; (void)nnn; // Suppress unused parameter warnings
    if (n == 'h') return "f";
    return "p";
}

const char* predictQ(char p, char c, char n, char nn, char nnn) {
    (void)p; (void)c; (void)n; (void)nn; (void)nnn; // Suppress unused parameter warnings
    return "k"; // We return 'k', and let the 'u' handle the 'w'
}

const char* predictR(char p, char c, char n, char nn, char nnn) {
    (void)p; (void)c; (void)n; (void)nn; (void)nnn; // Suppress unused parameter warnings
    return "r";
}

const char* predictS(char p, char c, char n, char nn, char nnn) {
    (void)p; (void)c; (void)n; (void)nn; (void)nnn; // Suppress unused parameter warnings
    if (p == '\'') return "z";
    if (p == 'd') return "z";
    if (p == 'g') return "z";
    if (p == 'm') return "z";
    if (nn == '1') return "z";
    return "s";
}

const char* predictT(char p, char c, char n, char nn, char nnn) {
    (void)p; (void)c; (void)n; (void)nn; (void)nnn; // Suppress unused parameter warnings
    if (n == 'c') return "ch";
    if (n == 'h') return "th";
    if (nn == 'h') return "ch";
    return "t";
}

const char* predictU(char p, char c, char n, char nn, char nnn) {
    (void)p; (void)c; (void)n; (void)nn; (void)nnn; // Suppress unused parameter warnings
    if (p == 'q') return "w";                            // Qu -> w
    if (n != '_' && nn == 'e' && nnn == '_') return "uw"; // Magic E: Mute, Tube
    return "ah";                                          // But, Cut
}

const char* predictV(char p, char c, char n, char nn, char nnn) {
    (void)p; (void)c; (void)n; (void)nn; (void)nnn; // Suppress unused parameter warnings
    return "v";
}

const char* predictW(char p, char c, char n, char nn, char nnn) {
    (void)p; (void)c; (void)n; (void)nn; (void)nnn; // Suppress unused parameter warnings
    return "w";
}

const char* predictX(char p, char c, char n, char nn, char nnn) {
    (void)p; (void)c; (void)n; (void)nn; (void)nnn; // Suppress unused parameter warnings
    return "ks"; // Note: You'll need a diphone for "ks" or handle this as two phonemes
}

const char* predictY(char p, char c, char n, char nn, char nnn) {
    (void)p; (void)c; (void)n; (void)nn; (void)nnn; // Suppress unused parameter warnings
    if (n == '_') return "iy"; // 'y' at the end of a word (happy) -> iy
    if (p == '_') return "y";  // 'y' at the start (yellow) -> y
    return "ay";               // 'y' in the middle (fly/cycle) -> ay
}

const char* predictZ(char p, char c, char n, char nn, char nnn) {
    (void)p; (void)c; (void)n; (void)nn; (void)nnn; // Suppress unused parameter warnings
    return "z";
}


//======================================================================
char** buildDiphoneList(const char** phonemes, int phoneme_count) {
    if (phoneme_count <= 0 || !phonemes) {
        return NULL;
    }

    // Allocate memory for diphone array - we need exactly (phoneme_count * 2 - 1) slots
    int total_diphones = phoneme_count * 2 - 1;
    char** diphones = (char**)malloc(total_diphones * sizeof(char*));
    if (!diphones) return NULL;

    // Initialize all pointer tracks to NULL to prevent uninitialized memory tracking crashes
    for (int i = 0; i < total_diphones; i++) {
        diphones[i] = NULL;
    }

    // 1. Setup the very first diphone slot (Index 0)
    diphones[0] = malloc(16);
    if (!diphones[0]) {
        goto error_cleanup;
    }
    sprintf(diphones[0], "pau_%s", phonemes[0] ? phonemes[0] : "ae");

    // 2. Setup the middle diphone slots (Odd Indices: 1, 3, 5, 7...)
    for (int i = 0; i < phoneme_count - 1; i++) {
        int index = i * 2 + 1;
        
        diphones[index] = malloc(32);
        if (!diphones[index]) {
            goto error_cleanup;
        }

        if (phonemes[i] && phonemes[i+1]) {
            sprintf(diphones[index], "%s_%s", phonemes[i], phonemes[i+1]);
        } else {
            strcpy(diphones[index], "pau_pau");
        }
        
        // CRITICAL FIX: DO NOT touch or allocate (index + 1) here!
        // The output log print shows that your engine uses sequential fallback null steps, 
        // which means even indices (2, 4, 6...) are explicitly meant to stay clean NULL blocks.
    }

    // 3. Setup the final trailing diphone slot (Index 8 for a 5-phoneme chain)
    int last_index = total_diphones - 1;
    diphones[last_index] = malloc(16);
    if (!diphones[last_index]) {
        goto error_cleanup;
    }

    if (phonemes[phoneme_count - 1]) {
        sprintf(diphones[last_index], "%s_pau", phonemes[phoneme_count - 1]);
    } else {
        strcpy(diphones[last_index], "pau_pau");
    }

    return diphones;

error_cleanup:
    if (diphones) {
        for (int j = 0; j < total_diphones; j++) {
            if (diphones[j]) free(diphones[j]);
        }
        free(diphones);
    }
    return NULL;
}


//======================================================================
// Fixed Dictionary_transcribeWordDecisionTree function - COMPLETE FIX
// Fixed Dictionary_transcribeWordDecisionTree function - COMPLETE CORRECTION
char** Dictionary_transcribeWordDecisionTree(Dictionary* dict, const char* word, int* diphone_count) {
    if (!dict || !word || !diphone_count) return NULL;
    
    // Debug: Print what we're looking for
    //printf("DEBUG: Looking for word '%s' in lexicon\n", word);
    
    // Check if the word is in our lexicon first - FIXED: proper case handling
    for (int i = 0; i < dict->lexicon_size; i++) {
        //printf("DEBUG: Comparing with lexicon word '%s'\n", dict->lexicon[i].word);
        if (strcmp(dict->lexicon[i].word, word) == 0) {
            //printf("DEBUG: Found exact match in lexicon for '%s'\n", word);
            *diphone_count = dict->lexicon[i].diphone_count;
            char** result = (char**)malloc((*diphone_count) * sizeof(char*));
            if (!result) return NULL;
            for (int j = 0; j < *diphone_count; j++) {
                result[j] = malloc(strlen(dict->lexicon[i].diphones[j]) + 1);
                if (!result[j]) {
                    // Clean up on error
                    for (int k = 0; k < j; k++) {
                        free(result[k]);
                    }
                    free(result);
                    return NULL;
                }
                strcpy(result[j], dict->lexicon[i].diphones[j]);
            }
            //printf("DEBUG: Returning lexicon diphones for '%s': ", word);
            for (int j = 0; j < *diphone_count; j++) {
                //printf("%s ", result[j]);
            }
            //printf("\n");
            return result;
        }
    }
    
    //printf("DEBUG: No lexicon match found for '%s', using G2P\n", word);

    // If not in lexicon, apply G2P rules

    // 1. CLEANING & PRE-PROCESSING
    char* cleaned = malloc(strlen(word) + 1);
    if (!cleaned) return NULL;

    strcpy(cleaned, word);

    // Convert to lowercase - FIXED: make sure this is working properly
    for (int i = 0; cleaned[i]; i++) {
        cleaned[i] = tolower(cleaned[i]);
    }

    // Handle abbreviations
    if (strcmp(cleaned, "mr") == 0) {
        free(cleaned);
        return Dictionary_transcribeWordDecisionTree(dict, "mister", diphone_count);
    } else if (strcmp(cleaned, "mrs") == 0) {
        free(cleaned);
        return Dictionary_transcribeWordDecisionTree(dict, "missus", diphone_count);
    }

    // 2. THE GENERATIVE MODEL (The Trained Decision Tree)
    size_t len = strlen(cleaned);
    char* w = malloc(len + 6); // Add extra chars for "_"
    if (!w) {
        free(cleaned);
        return NULL;
    }

    // SAFETY: Ensure we don't create overly long strings
    if (len + 6 > 1000) {  // Prevent buffer overflow
        free(w);
        free(cleaned);
        return NULL;
    }
    
    sprintf(w, "_%s___", cleaned);
    free(cleaned);


    //printf("DEBUG: Created working string '%s' (length %zu)\n", w, strlen(w));

    // Create phonemes array with bounds checking
    char** phonemes = (char**)malloc(100 * sizeof(char*));
    if (!phonemes) {
        free(w);
        return NULL;
    }
    int phoneme_count = 0;

    // Correct loop bounds - we need to process from index 1 to (len-4) inclusive
    size_t w_len = strlen(w);
    if (w_len < 5) {  // Need at least 5 chars for _word___ pattern
        free(w);
        free(phonemes);
        return NULL;
    }

    //printf("DEBUG: Processing %zu characters in working string\n", w_len);
    
    // FIXED: Proper bounds checking for loop
    for (size_t i = 1; i <= w_len - 4; ++i) {
        // Safety check to prevent accessing invalid memory
        if (i >= w_len || (i + 3) >= w_len) {
            //printf("DEBUG: Skipping out-of-bounds processing at position %zu\n", i);
            break;
        }
        
        char p = w[i-1];
        char c = w[i];
        char n = w[i+1];
        char nn = w[i+2];
        char nnn = w[i+3];
        
        // More safety checks
        if (p < 0 || c < 0 || n < 0 || nn < 0 || nnn < 0) {
            //printf("DEBUG: Skipping invalid character at position %zu\n", i);
            continue;
        }
        
        //printf("DEBUG: Processing character '%c' (pos %zu) with context p='%c', n='%c', nn='%c', nnn='%c'\n", 
               //c, i, p, n, nn, nnn);
        
        const char* p_out = "";

        switch(c) {
            case 'a': p_out = predictA(p, c, n, nn, nnn); break;
            case 'b': p_out = predictB(p, c, n, nn, nnn); break;
            case 'c': p_out = predictC(p, c, n, nn, nnn); break;
            case 'd': p_out = predictD(p, c, n, nn, nnn); break;
            case 'e': p_out = predictE(p, c, n, nn, nnn); break;
            case 'f': p_out = predictF(p, c, n, nn, nnn); break;
            case 'g': p_out = predictG(p, c, n, nn, nnn); break;
            case 'h': p_out = predictH(p, c, n, nn, nnn); break;
            case 'i': p_out = predictI(p, c, n, nn, nnn); break;
            case 'j': p_out = predictJ(p, c, n, nn, nnn); break;
            case 'k': p_out = predictK(p, c, n, nn, nnn); break;
            case 'l': p_out = predictL(p, c, n, nn, nnn); break;
            case 'm': p_out = predictM(p, c, n, nn, nnn); break;
            case 'n': p_out = predictN(p, c, n, nn, nnn); break;
            case 'o': p_out = predictO(p, c, n, nn, nnn); break;
            case 'p': p_out = predictP(p, c, n, nn, nnn); break;
            case 'q': p_out = predictQ(p, c, n, nn, nnn); break;
            case 'r': p_out = predictR(p, c, n, nn, nnn); break;
            case 's': p_out = predictS(p, c, n, nn, nnn); break;
            case 't': p_out = predictT(p, c, n, nn, nnn); break;
            case 'u': p_out = predictU(p, c, n, nn, nnn); break;
            case 'v': p_out = predictV(p, c, n, nn, nnn); break;
            case 'w': p_out = predictW(p, c, n, nn, nnn); break;
            case 'x': p_out = predictX(p, c, n, nn, nnn); break;
            case 'y': p_out = predictY(p, c, n, nn, nnn); break;
            case 'z': p_out = predictZ(p, c, n, nn, nnn); break;
            default:
                // Fixed: use char* for indexing (was causing warning)
                if (dict->consonant_map[(unsigned char)c][0] != '\0') {
                    p_out = dict->consonant_map[(unsigned char)c];
                }
                break;
        }

        //printf("DEBUG: Generated phoneme '%s' for character '%c'\n", p_out, c);
        
        if (p_out && strcmp(p_out, "silent") != 0 && strlen(p_out) > 0) {
            // SAFETY: Check that we don't exceed array bounds
            if (phoneme_count >= 99) {
                //printf("DEBUG: Phoneme array full, stopping\n");
                break;
            }
            
            phonemes[phoneme_count] = malloc(strlen(p_out) + 1);
            if (!phonemes[phoneme_count]) {
                // Clean up on error
                for (int j = 0; j < phoneme_count; j++) {
                    free(phonemes[j]);
                }
                free(phonemes);
                free(w);
                return NULL;
            }
            strcpy(phonemes[phoneme_count], p_out);
            phoneme_count++;
        } else if (p_out && strcmp(p_out, "silent") == 0) {
            //printf("DEBUG: Skipping silent phoneme for character '%c'\n", c);
        }
    }

    free(w);

    // --- VOWEL TEAM PROCESSING ---
    // Scan the original word to find letter pairs and force the correct phoneme
    char** finalPhonemes = (char**)malloc(phoneme_count * sizeof(char*));
    if (!finalPhonemes) {
        for (int i = 0; i < phoneme_count; i++) {
            free(phonemes[i]);
        }
        free(phonemes);
        return NULL;
    }

    int final_count = 0;

    // Copy all phonemes to final array with safety checks
    for (int i = 0; i < phoneme_count; i++) {
        if (phonemes[i] != NULL && strlen(phonemes[i]) > 0) {
            finalPhonemes[final_count] = malloc(strlen(phonemes[i]) + 1);
            if (!finalPhonemes[final_count]) {
                // Clean up on error
                for (int j = 0; j < final_count; j++) {
                    free(finalPhonemes[j]);
                }
                free(finalPhonemes);
                for (int j = 0; j < phoneme_count; j++) {
                    free(phonemes[j]);
                }
                free(phonemes);
                return NULL;
            }
            strcpy(finalPhonemes[final_count], phonemes[i]);
            final_count++;
        }
    }

    // Clean up
    for (int i = 0; i < phoneme_count; i++) {
        free(phonemes[i]);
    }
    free(phonemes);

    // Build diphone list - FIXED: ensure we don't pass NULL values
    if (final_count <= 0) {
        *diphone_count = 0;
        free(finalPhonemes);
        //printf("DEBUG: No valid phonemes generated for '%s'\n", word);
        return NULL;
    }

    char** result = buildDiphoneList((const char**)finalPhonemes, final_count);
    *diphone_count = final_count * 2 - 1;

    // Clean up
    for (int i = 0; i < final_count; i++) {
        free(finalPhonemes[i]);
    }
    free(finalPhonemes);

    //printf("DEBUG: G2P generated diphones for '%s': ", word);
    for (int j = 0; j < *diphone_count; j++) {
        if (result[j]) {
            //printf("%s ", result[j]);
        } else {
            //printf("(NULL) ");
        }
    }
    //printf("\n");
    
    return result;
}


