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
    setupG2PRules(); // Fill the maps FIRST
    loadLexicon();               // Then generate the dictionary
}

/**
 * @brief Sets up the core Grapheme-to-Phoneme (G2P) mapping rules.
 * @details Initializes maps for basic consonants, vowel clusters (teams),
 * and R-controlled vowels used by the transcription engine.
 */
void Dictionary::setupG2PRules() {
    // Basic Consonants (Every letter must be accounted for)
    m_consonantMap['b'] = "b";  m_consonantMap['c'] = "k";  m_consonantMap['d'] = "d";
    m_consonantMap['f'] = "f";  m_consonantMap['g'] = "g";  m_consonantMap['h'] = "hh";
    m_consonantMap['j'] = "jh"; m_consonantMap['k'] = "k";  m_consonantMap['l'] = "l";
    m_consonantMap['m'] = "m";  m_consonantMap['n'] = "n";  m_consonantMap['p'] = "p";
    m_consonantMap['q'] = "k";  m_consonantMap['r'] = "r";  m_consonantMap['s'] = "s";
    m_consonantMap['t'] = "t";  m_consonantMap['v'] = "v";  m_consonantMap['w'] = "w";
    m_consonantMap['x'] = "ks"; m_consonantMap['y'] = "y";  m_consonantMap['z'] = "z";

    // Key Clusters
    m_vowelClusterMap["th"] = "th"; // Default unvoiced
    m_vowelClusterMap["sh"] = "sh";
    m_vowelClusterMap["ch"] = "ch";
    m_vowelClusterMap["ng"] = "ng";
    m_vowelClusterMap["ph"] = "f";   // Fix for "phone"

    // Vowels
    m_vowelClusterMap["ee"] = "iy";
    m_vowelClusterMap["ea"] = "iy"; // Tea, Meet
    m_vowelClusterMap["oo"] = "uw"; // Book (often 'uh' but 'uw' is safer)
    m_vowelClusterMap["ay"] = "ey"; // Day
    m_vowelClusterMap["ai"] = "ey"; // Rain
    m_vowelClusterMap["ow"] = "ow"; // Slow
    m_vowelClusterMap["ou"] = "aw"; // Out (You might need an 'aw' sample)

    // R-controlled vowels (These help "anniversary" and "reminder")
    m_vowelClusterMap["er"] = "er";
    m_vowelClusterMap["ir"] = "er";
    m_vowelClusterMap["ur"] = "er";
    m_vowelClusterMap["ar"] = "aa";
    m_vowelClusterMap["or"] = "ao";
}

bool Dictionary::isVowel(QChar c) const {
    QString vowels = "aeiouy";
    return vowels.contains(c.toLower());
}

QString Dictionary::getPhoneticSound(QChar c) const {

    QChar lowerC = c.toLower();

    // Check consonants map first!
    if (m_consonantMap.contains(lowerC)) return m_consonantMap[lowerC];

    // Handle specific characters manually if not in map
    if (lowerC == 'w') return "w";
    if (lowerC == 'h') return "hh";
    if (lowerC == 'y') return "iy";

    // Vowels
    if (lowerC == 'a') return "ae";
    if (lowerC == 'e') return "eh";
    if (lowerC == 'i') return "ih";
    if (lowerC == 'o') return "ow"; // Changed from 'aa' to 'ow' (better for "hello")
    if (lowerC == 'u') return "ah";

    return "pau"; // Fallback
}



/**
 * @brief The primary Rule-Based Grapheme-to-Phoneme (G2P) engine.
 * @param word The input string to be synthesized.
 * @return A QStringList containing the generated diphone sequence.
 * @details This method applies a multi-pass approach: exception lookup,
 * cluster identification, magic-e logic, and finally diphone building.
 */
QStringList Dictionary::transcribeWord(const QString& word)
{
    QString cleaned = word.toLower().trimmed();
    if (cleaned.isEmpty()) return QStringList();

    //QString cleaned = word.toLower().trimmed();
    if (cleaned == "postoffice") {
        QStringList part1 = transcribeWord("post");
        QStringList part2 = transcribeWord("office");
        return part1 + part2; // Combine the results
    }


    // Then split the string and process each word separately.

    // --- 1. THE GOLDEN EXCEPTIONS (Irregular words that break all rules) ---
    static QMap<QString, QStringList> exceptions;
    if (exceptions.isEmpty()) {

        //A words;
        exceptions["all"] = {"ao", "l"};
        //B words
        exceptions["baby"] = {"b", "eh", "iy", "b", "iy"};
        exceptions["break"] = {"b", "r", "ey", "ey", "k"}; // Irregular 'ea'
        exceptions["business"] = {"b", "ih", "z", "n", "ah", "s"};
        //C words
        exceptions["cafe"] = {"k", "ae", "f", "ey"}; // Force the E to be heard
        //D words
        //E words
        exceptions["education"] = {"eh","jh","ah","k","eh","iy","sh","ah","n"};
        exceptions["eye"] = {"ay"};
        //F words
        //G words
        exceptions["garage"] = {"g", "ae", "r", "aa", "aa", "jh"};
        exceptions["good"] = {"g", "uh", "d"};
        //H words
        exceptions["hage"] = {"hh", "ey", "g"}; // test word to sound like Hague
        exceptions["have"] = {"hh", "ae", "v"};      // 'Have' doesn't follow Magic E
        exceptions["health"] = {"hh", "eh", "l", "th"};
        exceptions["high"] = {"hh", "ay"};
        //I words
        //exceptions["information"] = {"ih", "n","f","uh","r", "m","eh","iy", "sh","ah","n"};
        exceptions["insurance"] = {"ih", "n", "sh", "er", "ae", "n", "s"};
        exceptions["is"] = {"ih", "z"};          // Fixes "is" (z sound)
        //J words
        exceptions["jeweler"] = {"jh", "uw","ah","l","uh","r"};
        //K words
        //L words
        //M mords
        exceptions["message"] = {"m", "eh", "s", "ih", "jh"};
        //exceptions["my"] = {"m", "ay"};
        //N words
        exceptions["notable"] = {"n", "ao","uh","t","ah", "b", "ah","l"};
        exceptions["notification"] = {"n", "ow","ow","t","ah", "f", "ah","k", "ey","ey","sh","ah","n"};
        //O words
        exceptions["of"] = {"ah", "v"};
        exceptions["off"] = {"ao", "f"};
        exceptions["office"] = {"ao", "f", "ih", "s"};
        exceptions["orchestra"] = {"ao", "k", "eh", "s", "t", "r", "ae"};
        //P words
        exceptions["pilates"] = {"p", "ih", "l", "aa", "t", "iy", "s"};
        exceptions["premier"] = {"p", "r", "eh", "m", "iy", "er"};
        exceptions["present"] = {"p", "r", "eh", "z", "eh", "n", "t"};
        exceptions["purchase"] = {"p", "er", "ch", "ah", "s"};

        //Q words
        //R words
        exceptions["radio"] = {"r", "ey", "d", "iy", "ow"};
        //S words
        exceptions["school"] = {"s", "k", "uw", "l"};
        exceptions["seminar"] = {"s", "eh", "eh", "m", "ah", "n","aa","aa","r", "r"};
        exceptions["society"] = {"s", "ow", "s", "ay", "ay", "ih","t","iy"};
        exceptions["special"] = {"s", "p", "eh", "sh", "ao", "l"};
        exceptions["station"] = {"s", "t", "ey", "ey", "sh", "ah", "n"};
        //T words
        exceptions["tax"] = {"t", "ae","ae","k","s"};
        exceptions["taxi"] = {"t", "ae","ae","k","s","iy"};
        exceptions["the"] = {"dh", "ah"};
        exceptions["travelodge"] = {"t", "r", "ae", "v", "eh", "l", "l", "ao", "jh"}; // Treated as two parts
        //U words
        //exceptions["uncle"] = {"ah", "ng", "k", "ah", "l"};
        //V words
        exceptions["venue"] = {"v", "eh", "n", "y", "uw"};
        //W words
        exceptions["walk"] = {"w", "ao", "k"};
        exceptions["water"] = {"w", "ao", "t", "er"};
        //X words
        //Y words
        exceptions["you"] = {"y", "uw"};
        //Z words
    }
    if (exceptions.contains(cleaned)) return buildDiphoneList(exceptions[cleaned]);

    // --- 2. ABBREVIATIONS ---
    if (cleaned == "mr") cleaned = "mister";
    else if (cleaned == "mrs") cleaned = "missus";

    QStringList phonemes;
    for (int i = 0; i < cleaned.length(); ++i) {
        QChar current = cleaned[i];
        QString two = cleaned.mid(i, 2);
        QString three = cleaned.mid(i, 3);
        QString four = cleaned.mid(i, 4);
        QChar next = (i + 1 < cleaned.length()) ? cleaned[i + 1] : QChar();
        QChar afterNext = (i + 2 < cleaned.length()) ? cleaned[i + 2] : QChar();

        // --- A. START OF WORD RULES ---
        // if (i == 0 && current == 'u' && !isVowel(next.toLatin1())) {
        //     phonemes << "y" << "uw"; continue; // Fixes: User, University
        // }

        // --- A. START OF WORD RULES ---
        // Only use "y-uw" if it looks like "User", "Unit", "Use"
        // (U + Consonant + Vowel)
        if (i == 0 && current == 'u' && !isVowel(next.toLatin1()) && isVowel(afterNext.toLatin1())) {
            phonemes << "y" << "uw";
            continue;
        }

        // --- B. LONG CLUSTERS (4 & 3 letters) ---
        if (four == "tion" || four == "sion") { phonemes << "sh" << "ah" << "n"; i += 3; continue; }
        if (three == "igh") { phonemes << "ay" << "ay"; i += 2; continue; }

        // --- C. CONSONANT CLUSTERS ---
        if (two == "ph") { phonemes << "f"; i++; continue; }
        if (two == "th") { phonemes << "th"; i++; continue; }
        if (two == "sh") { phonemes << "sh"; i++; continue; }
        if (two == "ch") { phonemes << "ch"; i++; continue; }
        if (two == "qu") { phonemes << "k" << "w"; i++; continue; }
        if (two == "dg") { phonemes << "jh"; i++; continue; }

        // --- D. VOWEL TEAMS ---
        if (two == "oa") { phonemes << "ow" << "ow"; i++; continue; }
        if (two == "ee" || two == "ea") { phonemes << "iy" << "iy"; i++; continue; }
        if (two == "oo") { phonemes << "uh"; i++; continue; } // Short 'oo' for 'good'

        // --- E. SPECIAL CONTEXTS (W, X, Y) ---
        if (current == 'w' && next == 'a') { phonemes << "w" << "ao"; i++; continue; }
        if (current == 'x') { phonemes << "k" << "s"; continue; }
        if (current == 'y') {
            if (i == cleaned.length() - 1) {
                if (cleaned.length() <= 3) phonemes << "ay" << "ay"; // my
                else phonemes << "iy"; // baby
            } else { phonemes << "y"; }
            continue;
        }

        // --- F. MAGIC E (e.g., Phone, Home, Quote) ---
        if (isVowel(current.toLatin1()) && !next.isNull() && !isVowel(next.toLatin1()) && afterNext == 'e') {
            if (current == 'a') phonemes << "ey";
            else if (current == 'i') phonemes << "ay";
            else if (current == 'o') phonemes << "ow";
            else if (current == 'u') phonemes << "uw";
            else phonemes << getPhoneticSound(current.toLatin1());
            continue;
        }

        // --- G. SOFT C / G ---
        if (current == 'c' && (next == 'e' || next == 'i' || next == 'y')) { phonemes << "s"; continue; }
        if (current == 'g' && (next == 'e' || next == 'i' || next == 'y')) { phonemes << "jh"; continue; }

        // --- H. SILENT E ---
        if (i == cleaned.length() - 1 && current == 'e' && cleaned.length() > 3) continue;

        // --- I. DEFAULT ---
        phonemes << getPhoneticSound(current.toLatin1());
    }

    // Deduplicate and Duration logic...

    // --- 4. DEDUPLICATE CONSONANTS ONLY ---
    QStringList cleanPhonemes;
    for (int i = 0; i < phonemes.size(); ++i) {
        if (i > 0 && phonemes[i] == phonemes[i-1] && !isVowelPhoneme(phonemes[i])) continue;
        cleanPhonemes << phonemes[i];
    }

    QStringList result = buildDiphoneList(cleanPhonemes);
    qDebug() << "Word:" << word << "Phonemes:" << cleanPhonemes;
    return result;


    //return buildDiphoneList(cleanPhonemes);
}

/**
 * @brief Determines if a specific phoneme string represents a vowel sound.
 * @param p The phoneme string (e.g., "ae", "iy").
 * @return True if the phoneme is a vowel.
 */
bool Dictionary::isVowelPhoneme(const QString& p)
{
    static QStringList vowels = {"ae", "ey", "iy", "ow", "uw", "ay", "aa", "ah", "uh", "ao", "oy", "aw"};
    return vowels.contains(p);
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
    qDebug() << result; //Keep for debugging
    return result;
}

/**
 * @brief Populates the internal lexicon with pre-defined diphone sequences.
 * @details This handles common calendar words, months and numbers
 *  to ensure 100% accuracy for the most frequent terms.
 */
void Dictionary::loadLexicon() {
    m_data.clear();
    //Phonetic Word Dictionary: A database of words with their diphone transcriptions
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
    //m_data["third"] = {"pau_th", "th_er", "er_d", "d_pau"};
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

}



bool Dictionary::contains(const QString &word) const {
    return m_data.contains(word);
}

QStringList Dictionary::getDiphones(const QString &word) const {
    return m_data.value(word, QStringList()); // Returns empty list if not found
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
