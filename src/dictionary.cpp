/*
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
 * SPDX-License-Identifier: GNU Lesser General Public License v2.1
 */
#include "dictionary.h"
#include <qdatetime.h>

Dictionary::Dictionary(QObject *parent)
    : QObject{parent}
{
    initializeLexicon();
    setupG2PRules();
}

/**
 * @brief Populates the internal lexicon with pre-defined diphone sequences.
 * @details This handles common calendar words, months and numbers
 *  to ensure 100% accuracy for the most frequent terms.
 */
void Dictionary::initializeLexicon() {
    if (!m_data.isEmpty()) return; // Only do this once!

    //days of week
    m_data["monday"] = {"pau_m", "m_ah", "ah_n", "n_d", "d_ey", "ey_pau"};
    m_data["tuesday"] = {"pau_t", "t_uw", "uw_z", "z_d", "d_ey", "ey_pau"};
    m_data["wednesday"] = {"pau_w", "w_eh", "eh_n", "n_z", "z_d", "d_ey", "ey_pau"};
    m_data["thursday"] = {"pau_th", "th_er", "er_z", "z_d", "d_ey", "ey_pau"};
    m_data["friday"] = {"pau_f", "f_r", "r_ay", "ay_d", "d_ey", "ey_pau"};
    m_data["saturday"] = {"pau_s", "s_ae", "ae_t", "t_er", "er_d", "d_ey", "ey_pau"};
    m_data["sunday"] = {"pau_s", "s_ah", "ah_n", "n_d", "d_ey", "ey_pau"};
    //months
    m_data["january"] = {"pau_jh", "jh_ae", "ae_n", "n_y", "y_uw", "uw_eh", "eh_r", "r_iy", "iy_pau"};
    m_data["february"] = {"pau_f", "f_eh", "eh_b", "b_y", "y_uw", "uw_eh", "eh_r", "r_iy", "iy_pau"};
    //m_data["february"] = {"pau_f", "f_eh", "eh_b", "b_r", "r_uw", "uw_eh", "eh_r", "r_iy", "iy_pau"};
    m_data["march"] = {"pau_m", "m_aa", "aa_r", "r_ch", "ch_pau"};
    m_data["april"] = {"pau_ey", "ey_p", "p_r", "r_ah", "ah_l", "l_pau"};
    m_data["may"] = {"pau_m", "m_ey", "ey_pau"};
    m_data["june"] = {"pau_jh", "jh_uw", "uw_n", "n_pau"};
    m_data["july"] = {"pau_jh", "jh_uh", "uh_l", "l_ay", "ay_pau"};
    m_data["august"] = {"pau_ao", "ao_g", "g_ah", "ah_s", "s_t", "t_pau"};
    m_data["september"] = {"pau_s", "s_eh", "eh_p", "p_t", "t_eh", "eh_m", "m_b", "b_er", "er_pau"};
    m_data["october"] = {"pau_aa", "aa_k", "k_t", "t_ow", "ow_b", "b_er", "er_pau"};
    m_data["november"] = {"pau_n", "n_ow", "ow_v", "v_eh", "eh_m", "m_b", "b_er", "er_pau"};
    m_data["december"] = {"pau_d", "d_iy", "iy_s", "s_eh", "eh_m", "m_b", "b_er", "er_pau"};
    //day ordinals
    m_data["first"] = {"pau_f", "f_er", "er_s", "s_t", "t_pau"};
    m_data["second"] = {"pau_s", "s_eh", "eh_k", "k_ah", "ah_n", "n_d", "d_pau"};
    m_data["third"] = {"pau_th", "th_er", "er_er", "er_d", "d_pau"};

    m_data["fourth"] = {"pau_f", "f_ao", "ao_r", "r_th", "th_pau"};
    m_data["fifth"] = {"pau_f", "f_ih", "ih_f", "f_th", "th_pau"};
    m_data["sixth"] = {"pau_s", "s_ih", "ih_k", "k_s", "s_th", "th_pau"};
    m_data["seventh"] = {"pau_s", "s_eh", "eh_v", "v_ah", "ah_n", "n_th", "th_pau"};
    m_data["eighth"] = {"pau_ey", "ey_t", "t_th", "th_pau"};
    m_data["ninth"] = {"pau_n", "n_ay", "ay_n", "n_th", "th_pau"};
    m_data["tenth"] = {"pau_t", "t_eh", "eh_eh", "eh_n", "n_th", "th_pau"};
    m_data["eleventh"] = {"pau_ih", "ih_l", "l_eh", "eh_eh", "eh_v", "v_ah", "ah_n", "n_th", "th_pau"};
    m_data["twelfth"] = {"pau_t", "t_w", "w_eh", "eh_l", "l_f", "f_th", "th_pau"};
    m_data["thirteenth"] = {"pau_th", "th_er", "er_er", "er_t", "t_iy", "iy_iy", "iy_n", "n_th", "th_pau"};
    m_data["fourteenth"] = {"pau_f", "f_ao", "ao_ao", "ao_r", "r_t", "t_iy", "iy_iy", "iy_n", "n_th", "th_th", "th_pau"};
    m_data["fifteenth"] = {"pau_f", "f_ih", "ih_f", "f_t", "t_iy", "iy_iy", "iy_n", "n_th", "th_pau"};
    m_data["sixteenth"] = {"pau_s", "s_ih", "ih_k", "k_s", "s_t", "t_iy", "iy_iy", "iy_n", "n_th", "th_pau"};
    m_data["seventeenth"]= {"pau_s", "s_eh", "eh_v", "v_eh", "eh_n", "n_t", "t_iy", "iy_n", "n_th", "th_pau"};
    m_data["eighteenth"] = {"pau_ey", "ey_t", "t_iy", "iy_n", "n_th", "th_pau"};
    m_data["nineteenth"] = {"pau_n", "n_ay", "ay_ay", "ay_n", "n_t", "t_iy", "iy_iy", "iy_n", "n_th", "th_th", "th_pau"};
    m_data["twentieth"] = {"pau_t", "t_w", "w_eh", "eh_eh", "eh_n", "n_t", "t_iy", "iy_eh", "eh_eh", "eh_th", "th_pau"};
    m_data["twenty-first"] = {"pau_t", "t_w", "w_eh", "eh_n", "n_t", "t_iy", "iy_f", "f_er", "er_s", "s_t", "t_pau"};
    m_data["twenty-second"] = {"pau_t", "t_w", "w_eh", "eh_n", "n_t", "t_iy", "iy_s", "s_eh", "eh_k", "k_ah", "ah_n", "n_d", "d_pau"};;
    m_data["twenty-third"] = {"pau_t", "t_w", "w_eh", "eh_n", "n_t", "t_iy", "iy_th", "th_er", "er_d", "d_pau"};
    m_data["twenty-fourth"] = {"pau_t", "t_w", "w_eh", "eh_n", "n_t", "t_iy", "iy_f", "f_ao", "ao_r", "r_th", "th_pau"};
    m_data["twenty-fifth"] = {"pau_t", "t_w", "w_eh", "eh_n", "n_t", "t_iy","iy_f" , "f_ih", "ih_f", "f_th", "th_pau"};
    m_data["twenty-sixth"] = {"pau_t", "t_w", "w_eh", "eh_n", "n_t", "t_iy","iy_s" , "s_ih", "ih_k", "k_s", "s_th", "th_pau"};
    m_data["twenty-seventh"] = {"pau_t", "t_w", "w_eh", "eh_n", "n_t", "t_iy", "iy_s", "s_eh", "eh_v", "v_ah", "ah_n", "n_th", "th_pau"};
    m_data["twenty-eighth"] =  {"pau_t", "t_w", "w_eh", "eh_n", "n_t", "t_iy","iy_ey", "ey_t", "t_th", "th_pau"};
    m_data["twenty-ninth"] = {"pau_t", "t_w", "w_eh", "eh_n", "n_t", "t_iy", "iy_n", "n_ay", "ay_n", "n_th", "th_pau"};
    m_data["thirtieth"] = {"pau_th", "th_er", "er_er", "er_t", "t_iy", "iy_eh", "eh_eh", "eh_th", "th_pau"};
    m_data["thirty-first"] = {"pau_th", "th_er", "er_t", "t_iy","iy_f", "f_er", "er_s", "s_t", "t_pau"};


    // The Time Suffixes
    m_data["am"] = {"pau_ey", "ey_eh", "eh_m", "m_pau"};
    m_data["pm"] = {"pau_p", "p_iy", "iy_eh", "eh_m", "m_pau"};
    m_data["o"]  = {"pau_ow", "ow_ow", "ow_pau"};

    // Numbers 1-12 (Essential for Hours)
    m_data["one"]   = {"pau_w", "w_ah", "ah_n", "n_pau"};
    m_data["two"]   = {"pau_t", "t_uw", "uw_pau"};
    m_data["three"] = {"pau_th", "th_r", "r_iy", "iy_pau"};
    m_data["four"]  = {"pau_f", "f_ao", "ao_r", "r_pau"};
    m_data["five"]  = {"pau_f", "f_ay", "ay_v", "v_pau"};
    m_data["six"]   = {"pau_s", "s_ih", "ih_k", "k_s", "s_pau"};
    m_data["seven"] = {"pau_s", "s_eh", "eh_v", "v_ah", "ah_n", "n_pau"};
    m_data["eight"] = {"pau_ey", "ey_t", "t_pau"};
    m_data["nine"]  = {"pau_n", "n_ay", "ay_n", "n_pau"};
    m_data["ten"]   = {"pau_t", "t_eh", "eh_n", "n_pau"};
    m_data["eleven"]= {"pau_iy", "iy_l", "l_eh", "eh_v", "v_ah", "ah_n", "n_pau"};
    m_data["twelve"]= {"pau_t", "t_w", "w_eh", "eh_l", "l_v", "v_pau"};

    m_data["zero"] = {"pau_z", "z_iy", "iy_iy", "iy_r", "r_ow", "ow_pau"};

    // --- Teens ---
    m_data["thirteen"] = {"pau_th", "th_er", "er_t", "t_iy", "iy_n", "n_pau"};
    m_data["fourteen"] = {"pau_f", "f_ao", "ao_r", "r_t", "t_iy", "iy_n", "n_pau"};
    m_data["fifteen"]  = {"pau_f", "f_ih", "ih_f", "f_t", "t_iy", "iy_n", "n_pau"};
    m_data["sixteen"]  = {"pau_s", "s_ih", "ih_k", "k_s", "s_t", "t_iy", "iy_n", "n_pau"};
    m_data["seventeen"]= {"pau_s", "s_eh", "eh_v", "v_ah", "ah_n", "n_t", "t_iy", "iy_n", "n_pau"};
    m_data["eighteen"] = {"pau_ey", "ey_t", "t_iy", "iy_n", "n_pau"};
    m_data["nineteen"] = {"pau_n", "n_ay", "ay_n", "n_t", "t_iy", "iy_n", "n_pau"};

    // --- Decade Bases ---
    m_data["twenty"] = {"pau_t", "t_w", "w_eh", "eh_n", "n_t", "t_iy", "iy_pau"};
    m_data["thirty"]   = {"pau_th", "th_er", "er_t", "t_iy", "iy_pau"};
    m_data["thirty"] = {"pau_th", "th_er", "er_t", "t_iy"};
    m_data["forty"]    = {"pau_f", "f_ao", "ao_r", "r_t", "t_iy", "iy_pau"};
    m_data["fifty"]    = {"pau_f", "f_ih", "ih_f", "f_t", "t_iy", "iy_pau"};
    //TODO
    //m_data["eightieth"] = {"pau_eh", "ey_ey", "ey_t", "t_iy", "iy_ih", "ih_th", "th_pau"};
    //m_data["eighty"] = {"pau_eh", "eh_iy", "iy_t", "t_iy", "iy_pau"};
    //m_data["hundred"] = {"pau_hh", "hh_ah", "ah_n", "n_d", "d_r", "r_ah", "ah_d", "d_pau"};
    //m_data["hundredth"] = {"pau_hh", "hh_ah", "ah_n", "n_d", "d_r", "r_ah", "ah_d", "d_th", "th_pau"};
    //AM/PM
    m_data["am"]   = {"pau_ey", "ey_eh", "eh_m", "m_pau"};
    m_data["pm"]   = {"pau_p", "p_iy", "iy_eh", "eh_m", "m_pau"};
    m_data["o"]    = {"pau_ow", "ow_ow", "ow_pau"};

    //Talk Calendar
    m_data["talk"] = {"pau_t", "t_aa", "aa_aa", "aa_k", "k_pau"};
    m_data["calendar"] = {"pau_k", "k_ae", "ae_l", "l_ah", "ah_n", "n_d", "d_er", "er_pau"};

    //word exception list
    //A words
    m_data["are"] = {"pau_aa", "aa_r", "r_pau"};
    //m_data["alex"] = {"pau_ae", "ae_l", "l_ah", "ah_ks", "ks_pau"}; // Force 'ae' instead of 'ey'
     m_data["alex"] = {"pau_ae", "ae_ae", "ae_l", "l_ah", "ah_k", "k_s", "s_pau"};
    //B words
    m_data["baby"] = {"pau_b", "b_eh", "eh_iy", "iy_b", "b_iy", "iy_pau"};
    m_data["birth"] = {"pau_b", "b_uh", "uh_r", "r_th", "th_pau"};
    m_data["birthday"] = {"pau_b", "b_er", "er_er", "er_th", "th_d", "d_ey", "ey_pau"};
    m_data["boxing"] = {"pau_b", "b_aa", "aa_aa", "aa_k", "k_s", "s_ih", "ih_ng", "ng_pau"};
    m_data["break"] = {"pau_b", "b_r", "r_eh", "eh_iy", "iy_k", "k_pau"};
    m_data["business"] = {"b_ih", "ih_z", "z_n", "ah ah_s", "s_pau"};    
    m_data["busy"] = {"pau_b", "b_ih", "ih_z", "z_iy", "iy_pau"};


    //C words
    m_data["cafe"] = {"pau_k", "k_ah", "ah_f", "f_ey", "ey_ey"};
    m_data["choir"] = {"pau_k", "k_w", "w_ay", "ay_er", "er_pau"};
    m_data["colonel"] = {"pau_k", "k_er", "er_n", "n_ah", "ah_l", "l_pau"};

    // D words
    m_data["debt"] = {"pau_d", "d_eh", "eh_t", "t_pau"};
    m_data["does"] = {"pau_d", "d_ah", "ah_z", "z_pau"};

    //E words
    m_data["education"] = {"pau_eh", "eh_jh", "jh_ah", "ah_k", "k_eh", "eh_iy", "iy_sh", "sh_ah", "ah_n", "n_pau"};
    m_data["event"] = {"pau_ih", "ih_v", "v_eh", "eh_eh", "eh_n", "n_t", "t_pau"};
    m_data["events"] = {"pau_ih", "ih_v", "v_eh", "eh_n", "n_t", "t_z", "z_pau"};
    m_data["eye"] = {"pau_aa", "aa_iy", "iy_pau"};

    //G words
    m_data["garage"] = {"pau_g", "g_uh", "uh_r", "r_aa", "aa_zh", "zh_pau"};
    m_data["good"] = {"pau_g", "g_uh", "uh_d", "d_pau"};

    //H words
    m_data["health"] = {"pau_hh", "hh_eh", "eh_eh", "eh_l", "l_th", "th_pau"};
    m_data["high"] = {"pau_hh", "hh_aa", "aa_iy", "iy_pau"};

    //M words
    m_data["message"] = {"pau_m", "m_eh", "eh_s", "s_ah", "ah_jh", "jh_pau"};
    m_data["my"] = {"pau_m", "m_ay", "ay_ay", "ay_pau"};
    //N words
    m_data["notification"] = {"pau_n", "n_ow", "ow_ow", "ow_t", "t_ah", "ah_f", "f_ah", "ah_k", "k_ey", "ey_ey", "ey_sh", "sh_ah", "ah_n", "n_pau"};

    // O words
    m_data["once"] = {"pau_w", "w_ah", "ah_n", "n_s", "s_pau"};

    //P words
    m_data["pilates"] = {"pau_p", "p_ih", "ih_ih", "ih_l", "l_aa", "aa_aa", "aa_t", "t_iy", "iy_iy", "iy_s", "s_pau"};
    //Q words
    m_data["quote"] = {"pau_k", "k_w", "w_w", "w_ow", "ow_ow", "ow_t", "t_pau"};
    //R words
    m_data["radio"] = {"pau_r", "r_ey", "ey_ey", "ey_d", "d_iy", "iy_ow", "ow_ow", "ow_pau"};

    // S words
    m_data["says"] = {"pau_s", "s_eh", "eh_z", "z_pau"};
    m_data["said"] = {"pau_s", "s_eh", "eh_d", "d_pau"};
    m_data["station"] = {"pau_s", "s_t", "t_ey", "ey_ey", "ey_sh", "sh_ah", "ah_n", "n_pau"};

    //T words
    m_data["tax"] = {"pau_t", "t_ae", "ae_ae", "ae_k", "k_s", "s_pau"};
    m_data["taxi"] = {"pau_t", "t_ae", "ae_ae", "ae_k", "k_s", "s_iy", "iy_pau"};
    m_data["the"] = {"pau_dh", "dh_ah", "ah_ah", "ah_pau"};
    m_data["through"] = {"pau_th", "th_r", "r_uw", "uw_pau"};

    m_data["venue"] = {"pau_v", "v_eh", "eh_n", "n_y", "y_uw", "uw_pau"};

    // W words
    m_data["walk"] = {"pau_w", "w_w", "w_ao", "ao_ao", "ao_k", "k_k", "k_pau"};
    m_data["who"] = {"pau_hh", "hh_uw", "uw_pau"};
    m_data["what"] = {"pau_w", "w_ah", "ah_t", "t_pau"};
    m_data["was"] = {"pau_w", "w_ah", "ah_z", "z_pau"};

    //m_data["you"] = {"pau_y", "y_uw", "uw_uw", "uw_pau"};

}

/**
 * @brief Sets up the core Grapheme-to-Phoneme (G2P) mapping rules.
 * @details Initializes maps for basic consonants
 */
void Dictionary::setupG2PRules() {
    // Basic Consonants (every letter must be accounted for)
    m_consonantMap['b'] = "b";  m_consonantMap['c'] = "k";  m_consonantMap['d'] = "d";
    m_consonantMap['f'] = "f";  m_consonantMap['g'] = "g";  m_consonantMap['h'] = "hh";
    m_consonantMap['j'] = "jh"; m_consonantMap['k'] = "k";  m_consonantMap['l'] = "l";
    m_consonantMap['m'] = "m";  m_consonantMap['n'] = "n";  m_consonantMap['p'] = "p";
    m_consonantMap['q'] = "k";  m_consonantMap['r'] = "r";  m_consonantMap['s'] = "s";
    m_consonantMap['t'] = "t";  m_consonantMap['v'] = "v";  m_consonantMap['w'] = "w";
    m_consonantMap['x'] = "ks"; m_consonantMap['y'] = "y";  m_consonantMap['z'] = "z";
}


QStringList Dictionary::buildDiphoneList(const QStringList& phonemes)
{
    QStringList result;
    if (phonemes.isEmpty()) return result;
    result << "pau_" + phonemes.first();
    for (int i = 0; i < phonemes.size() - 1; ++i) {
        result << phonemes[i] + "_" + phonemes[i+1];
    }
    result << phonemes.last() + "_pau";
    return result;
}

//predictA to predictZ are learned decision tree model
QString Dictionary::predictA(QChar p, QChar c, QChar n, QChar nn, QChar nnn) {
    // 1. Terminal Magic E (Lake, Bake, Fate, Ale)
    if (n != '_' && nn == 'e' && nnn == '_') return "ey";

    // 2. Common Vowel Neighbors (handled mostly by post-processor, but good for backup)
    if (n == 'i' || n == 'y') return "ey";
    if (n == 'r' || n == 'h' || n == 'w') return "aa";

    // 3. The "Alex/Apple" logic
    if (n == 'l' || n == 'p' || n == 'c' || n == 'd') return "ae";

    // 4. Fallback
    return "ae";
}


QString Dictionary::predictB(QChar p, QChar c, QChar n, QChar nn, QChar nnn) {
    return "b";
}

QString Dictionary::predictC(QChar p, QChar c, QChar n, QChar nn, QChar nnn) // Added nn
{
    if (n == 'h') return "ch";
    if (n == 'e' || n == 'i' || n == 'y') return "s";
    return "k";
}


QString Dictionary::predictD(QChar p, QChar c, QChar n, QChar nn, QChar nnn) {
    return "d";
}

QString Dictionary::predictE(QChar p, QChar c, QChar n, QChar nn, QChar nnn) {
    if (n == '_') return "silent"; // <--- Add this at the VERY TOP
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

QString Dictionary::predictF(QChar p, QChar c, QChar n, QChar nn, QChar nnn) {
    return "f";
}

QString Dictionary::predictG(QChar p, QChar c, QChar n, QChar nn, QChar nnn) {
    return "g";
}

QString Dictionary::predictH(QChar p, QChar c, QChar n, QChar nn, QChar nnn) {
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

QString Dictionary::predictI(QChar p, QChar c, QChar n, QChar nn, QChar nnn) {
    if (n != '_' && nn == 'e' && nnn == '_') return "ay"; // Magic E: Like, Kite
    if (n == 'g' && nn == 'h') return "ay";              // Night, Light
    return "ih";                                          // Bit, Sit
}

QString Dictionary::predictJ(QChar p, QChar c, QChar n, QChar nn, QChar nnn) {
    return "jh";
}

QString Dictionary::predictK(QChar p, QChar c, QChar n, QChar nn, QChar nnn) {
    return "k";
}

QString Dictionary::predictL(QChar p, QChar c, QChar n, QChar nn, QChar nnn) {
    return "l";
}

QString Dictionary::predictM(QChar p, QChar c, QChar n, QChar nn, QChar nnn) {
    return "m";
}

QString Dictionary::predictN(QChar p, QChar c, QChar n, QChar nn, QChar nnn) {
    return "n";
}

QString Dictionary::predictO(QChar p, QChar c, QChar n, QChar nn, QChar nnn) {
    // 1. Terminal Magic E (Quote, Note, Rope) - MUST BE AT TOP
    if (n != '_' && nn == 'e' && nnn == '_') return "ow";

    // 2. Common patterns
    if (n == 'r' || n == 'f') return "ao";
    if (n == 'u' || n == 'o') return "uw";

    // 3. Most common 'o' sound (Hot, Box, Dot)
    return "aa";
}

QString Dictionary::predictP(QChar p, QChar c, QChar n, QChar nn, QChar nnn)
{
    if (n == 'h') return "f";
    return "p";
}

QString Dictionary::predictQ(QChar p, QChar c, QChar n, QChar nn, QChar nnn) {
    return "k"; // We return 'k', and let the 'u' handle the 'w'
}



QString Dictionary::predictR(QChar p, QChar c, QChar n, QChar nn, QChar nnn) {
    return "r";
}

QString Dictionary::predictS(QChar p, QChar c, QChar n, QChar nn, QChar nnn) {
    if (p == '\'') return "z";
    if (p == 'd') return "z";
    if (p == 'g') return "z";
    if (p == 'm') return "z";
    if (nn == '1') return "z";
    return "s";
}

QString Dictionary::predictT(QChar p, QChar c, QChar n, QChar nn, QChar nnn) {
    if (n == 'c') return "ch";
    if (n == 'h') return "th";
    if (nn == 'h') return "ch";
    return "t";
}


QString Dictionary::predictU(QChar p, QChar c, QChar n, QChar nn, QChar nnn) {
    if (p == 'q') return "w";                            // Qu -> w
    if (n != '_' && nn == 'e' && nnn == '_') return "uw"; // Magic E: Mute, Tube
    return "ah";                                          // But, Cut
}
QString Dictionary::predictV(QChar p, QChar c, QChar n, QChar nn, QChar nnn) {
    return "v";
}

QString Dictionary::predictW(QChar p, QChar c, QChar n, QChar nn, QChar nnn) {
    return "w";
}

QString Dictionary::predictX(QChar p, QChar c, QChar n, QChar nn, QChar nnn) {
    return "ks"; // Note: You'll need a diphone for "ks" or handle this as two phonemes
}

QString Dictionary::predictY(QChar p, QChar c, QChar n, QChar nn, QChar nnn) {
    if (n == '_') return "iy"; // 'y' at the end of a word (happy) -> iy
    if (p == '_') return "y";  // 'y' at the start (yellow) -> y
    return "ay";               // 'y' in the middle (fly/cycle) -> ay
}


QString Dictionary::predictZ(QChar p, QChar c, QChar n, QChar nn, QChar nnn) {
    return "z";
}


/**
 * @brief Grapheme-to-Phoneme (G2P) model.
 * @param word The input string to be synthesized.
 * @return A QStringList containing the generated diphone sequence.
 * @details manual diphone sequence lookup, followed by trained decision tree model.
 */
QStringList Dictionary::transcribeWordDecisionTree(const QString& word)
{
    // 1. CLEANING & PRE-PROCESSING
    QString cleaned = word.toLower().trimmed();
    if (cleaned.isEmpty()) return QStringList();

    // Handle abbreviations
    if (cleaned == "mr") cleaned = "mister";
    else if (cleaned == "mrs") cleaned = "missus";

    // 2. THE GOLDEN EXCEPTIONS (The Hand-Crafted "Perfect" sounds)
    // Check your manual overrides first.

    if (m_data.contains(cleaned)) {
        return m_data[cleaned];
        //return buildDiphoneList(m_data[cleaned]);
    }

    // 3. THE GENERATIVE MODEL (The Trained Decision Tree)

    QString w = "_" + cleaned + "___";
    QStringList phonemes;

    for (int i = 1; i < w.length() - 3; ++i) {
        QChar p   = w[i-1];
        QChar c   = w[i];
        QChar n   = w[i+1];
        QChar nn  = w[i+2];
        QChar nnn = w[i+3];
        QString p_out = "";

        switch(c.toLatin1()) {
        case 'a': p_out = predictA(p, c, n, nn,nnn); break;
        case 'b': p_out = predictB(p, c, n, nn,nnn); break;
        case 'c': p_out = predictC(p, c, n, nn,nnn); break;
        case 'd': p_out = predictD(p, c, n, nn,nnn); break;
        case 'e': p_out = predictE(p, c, n, nn,nnn); break;
        case 'f': p_out = predictF(p, c, n, nn,nnn); break;
        case 'g': p_out = predictG(p, c, n, nn,nnn); break;
        case 'h': p_out = predictH(p, c, n, nn,nnn); break;
        case 'i': p_out = predictI(p, c, n, nn,nnn); break;
        case 'j': p_out = predictJ(p, c, n, nn,nnn); break;
        case 'k': p_out = predictK(p, c, n, nn,nnn); break;
        case 'l': p_out = predictL(p, c, n, nn,nnn); break;
        case 'm': p_out = predictM(p, c, n, nn,nnn); break;
        case 'n': p_out = predictN(p, c, n, nn,nnn); break;
        case 'o': p_out = predictO(p, c, n, nn,nnn); break;
        case 'p': p_out = predictP(p, c, n, nn,nnn); break;
        case 'q': p_out = predictQ(p, c, n, nn,nnn); break;
        case 'r': p_out = predictR(p, c, n, nn,nnn); break;
        case 's': p_out = predictS(p, c, n, nn,nnn); break;
        case 't': p_out = predictT(p, c, n, nn,nnn); break;
        case 'u': p_out = predictU(p, c, n, nn,nnn); break;
        case 'v': p_out = predictV(p, c, n, nn,nnn); break;
        case 'w': p_out = predictW(p, c, n, nn,nnn); break;
        case 'x': p_out = predictX(p, c, n, nn,nnn); break;
        case 'y': p_out = predictY(p, c, n, nn,nnn); break;
        case 'z': p_out = predictZ(p, c, n, nn,nnn); break;
        default:
            if (m_consonantMap.contains(c)) p_out = m_consonantMap[c];
            break;
        }

        if (!p_out.isEmpty() && p_out != "silent") {
            phonemes << p_out;
        }
    }
    // ---  VOWEL TEAM ---
    // scan the original word to find letter pairs and force the correct phoneme
    QStringList finalPhonemes;
    for (int i = 0; i < cleaned.length(); ++i) {
        QString pair = cleaned.mid(i, 2);

        if (pair == "ee" || pair == "ea") {
            finalPhonemes << "iy"; // Queen, Eat
            i++; // Skip the next letter
        } else if (pair == "oa") {
            finalPhonemes << "ow"; // Boat, Joan
            i++;
        } else if (pair == "ai") {
            finalPhonemes << "ey"; // Rain
            i++;
        } else if (pair == "oo") {
            finalPhonemes << "uw"; // Moon
            i++;
        } else if (pair == "th") {
            finalPhonemes << "th"; // Thin
            i++;
        } else if (pair == "sh") {
            finalPhonemes << "sh"; // Ship
            i++;
        } else {
            // If no pair, use the phoneme predicted by the tree
            // Note: This logic assumes 'phonemes' list matches 'cleaned' string length
            if (i < phonemes.size()) finalPhonemes << phonemes[i];
        }
    }
    phonemes = finalPhonemes;

    // 4. CLEAN-UP (Deduplication)
    for (int i = 0; i < phonemes.size() - 1; ++i) {
        if (phonemes[i] == phonemes[i+1]) {
            phonemes.removeAt(i);
            i--;
        }
    }

    //return buildDiphoneList(phonemes);
    QStringList result = buildDiphoneList(phonemes);
    //qDebug() << "Word:" << word << "Phonemes:" << phonemes;
    return result;
}

/**
 * @brief Normalizes an integer day into its ordinal word form.
 * @param day The day of the month (1-31).
 * @return A string such as "first", "second", etc.
 */
QString Dictionary::getOrdinalStr(int day)
{
    static const QStringList ordinals = {
        "", // 0 (ignored)
        "first", "second", "third", "fourth", "fifth",
        "sixth", "seventh", "eighth", "ninth", "tenth",
        "eleventh", "twelfth", "thirteenth", "fourteenth", "fifteenth",
        "sixteenth", "seventeenth", "eighteenth", "nineteenth", "twentieth",
        "twenty-first", "twenty-second", "twenty-third", "twenty-fourth", "twenty-fifth",
        "twenty-sixth", "twenty-seventh", "twenty-eighth", "twenty-ninth", "thirtieth",
        "thirty-first"
    };

    if (day >= 1 && day <= 31) {
        return ordinals[day];
    }

    return ""; // Return empty if date is invalid
}

/**
 * @brief Converts an integer day into its cardinal word form for speech
 * @param number The number (1-59) as 59 minutes
 * @return A string such as "one", "two", etc.
 */
QString Dictionary::getCardinalStr(int number)
{
    static const QStringList cardinals = {
        "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
        "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen",
        "eighteen", "nineteen", "twenty", "twenty one", "twenty two", "twenty three",
        "twenty four", "twenty five", "twenty six", "twenty seven", "twenty eight",
        "twenty nine", "thirty", "thirty one", "thirty two", "thirty three",
        "thirty four", "thirty five", "thirty six", "thirty seven", "thirty eight",
        "thirty nine", "forty", "forty one", "forty two", "forty three", "forty four",
        "forty five", "forty six", "forty seven", "forty eight", "forty nine", "fifty",
        "fifty one", "fifty two", "fifty three", "fifty four", "fifty five",
        "fifty six", "fifty seven", "fifty eight", "fifty nine"
    };

    if (number >= 1 && number <= 59) {
        return cardinals[number];
    }

    return ""; // Return empty if date is invalid
}

/**
 * @brief Converts a QDate.
 * @return A formatted string like "tuesday twenty-fourth february"
 */
QString Dictionary::getDatePhrase(const QDate &date)
{
    QString dayName = date.toString("dddd").toLower();
    QString monthName = date.toString("MMMM").toLower();
    int day = date.day();

    QString ordinalStr = getOrdinalStr(day);

    QString datePhrase="";
    datePhrase.append(dayName);
    datePhrase.append(" ");
    datePhrase.append(ordinalStr);
    datePhrase.append(" ");
    datePhrase.append(monthName);
    datePhrase.append(" ");

    return datePhrase;
}

/**
 * @brief Converts a 24-hour time into a natural language phrase.
 * @param hour The hour (0-23).
 * @param minute The minute (0-59).
 * @param isAllDay Flag to bypass time generation for all-day events.
 * @return A formatted string like "ten o five am".
 */
QString Dictionary::getTimePhrase(int hour, int minute, bool isAllDay)
{
    //if (isAllDay) return "all day";
    if (isAllDay) return "";

    QString timePhrase = "";

    int hour12 = (hour == 0 || hour == 12) ? 12 : hour % 12;
    QString ampm = (hour < 12) ? "am" : "pm";
    // add hour words
    timePhrase.append(getCardinalStr(hour12));
    timePhrase.append(" ");

    if (minute == 0) {
        timePhrase.append(ampm);
        timePhrase.append(" ");
    } else if (minute < 10) {
        timePhrase.append(" o ");
        timePhrase.append(getCardinalStr(minute));
        timePhrase.append(" ");
        timePhrase.append(ampm);
        timePhrase.append(" ");

    } else {
        timePhrase.append(getCardinalStr(minute));
        timePhrase.append(" ");
        timePhrase.append(ampm);
        timePhrase.append(" ");
    }

    return timePhrase;
}
