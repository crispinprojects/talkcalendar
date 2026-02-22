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


#include "synthesizer.h"
#include "diphone.h" // Needed for DiphoneEntry and finding diphones
#include <cmath>
//#include <algorithm>

Synthesizer::Synthesizer(QObject *parent) : QObject(parent) {

}



void Synthesizer::speak(const QString &text, Dictionary *dict, float tempo) {
    QStringList words = text.toLower().split(" ", Qt::SkipEmptyParts);
    QStringList allDiphones;

    for (const QString &word : words) {
        if (dict->contains(word)) {
            // Use manual overrides if they exist
            allDiphones.append(dict->getDiphones(word));
        } else {
            // otherwise autogenerate word diphone sequences on the fly
            allDiphones.append(dict->convertToDiphones(word));
        }
    }
    if (!allDiphones.isEmpty()) {
        QVector<int16_t> audio = vocoder(allDiphones, tempo);
        saveAndPlay(audio);
    }
}

// This the OLA algorithm is acting as the vocoder
// taking "information" (the diphones) and generating the final audio samples
QVector<int16_t> Synthesizer::vocoder(const QStringList &diphones, float tempoFactor) {
    QVector<int16_t> output;
    const int FRAME_SIZE = 160;
    const int analysis_step = 80;
    int synthesis_step = static_cast<int>(analysis_step / tempoFactor);
    int currentOutStart = 0;

    for (const QString &name : diphones) {
        DiphoneEntry* entry = Diphone::findDiphoneEntry(name.toUtf8().constData());
        if (!entry) continue;

        const int16_t* source = reinterpret_cast<const int16_t*>(entry->data + 44);
        int sourceSamples = (entry->size - 44) / sizeof(int16_t);

        int currentIn = 0;
        int currentOut = currentOutStart;

        while (currentIn + FRAME_SIZE < sourceSamples) {
            if (currentOut + FRAME_SIZE > output.size()) {
                output.resize(currentOut + FRAME_SIZE, 0);
            }

            for (int i = 0; i < FRAME_SIZE; ++i) {
                // TRIANGLE WINDOW:
                // Fade in for the first half, Fade out for the second half
                float window;
                if (i < FRAME_SIZE / 2)
                    window = (float)i / (FRAME_SIZE / 2);
                else
                    window = (float)(FRAME_SIZE - i) / (FRAME_SIZE / 2);

                int32_t currentSample = output[currentOut + i];
                // Apply the window to the source to smooth the edges
                int32_t newSample = static_cast<int32_t>(source[currentIn + i] * window);

                int32_t combined = currentSample + newSample;
                output[currentOut + i] = static_cast<int16_t>(qBound(-32768, combined, 32767));
            }

            currentIn += analysis_step;
            currentOut += synthesis_step;
        }
        // the next diphone must overlap with the end of the last one
        currentOutStart = currentOut - synthesis_step;
    }

    // Normalization logic
    if (output.isEmpty()) return output;
    int16_t maxVal = 0;
    for (int16_t sample : output) {
        if (std::abs(sample) > maxVal) maxVal = std::abs(sample);
    }

    if (maxVal > 0) {
        float scaleFactor = 29500.0f / maxVal;
        for (int i = 0; i < output.size(); ++i) {
            int32_t amplified = static_cast<int32_t>(output[i] * scaleFactor);
            output[i] = static_cast<int16_t>(qBound(-32768, amplified, 32767));
        }
    }
    return output;
}


void Synthesizer::saveAndPlay(const QVector<int16_t> &buffer) {
    // Stop any currently playing audio
    if (m_audioProcess && m_audioProcess->state() == QProcess::Running) {
        m_audioProcess->kill();
        m_audioProcess->waitForFinished();
    }

    QString path = QCoreApplication::applicationDirPath() + "/diphone_out.wav";
    QFile file(path);

    if (file.open(QIODevice::WriteOnly)) {
        writeWavHeader(&file, buffer.size() * sizeof(int16_t));
        file.write(reinterpret_cast<const char*>(buffer.data()), buffer.size() * sizeof(int16_t));
        file.close();

        // Start new playback
        m_audioProcess = new QProcess(this);
        m_audioProcess->start("aplay", {path});
    }
}

void Synthesizer::writeWavHeader(QFile *file, int dataSize) {
    file->write("RIFF", 4);
    int fileSize = 36 + dataSize;
    file->write(reinterpret_cast<char*>(&fileSize), 4);
    file->write("WAVEfmt ", 8);
    int fmtSize = 16;
    file->write(reinterpret_cast<char*>(&fmtSize), 4);
    short format = 1; // PCM
    file->write(reinterpret_cast<char*>(&format), 2);
    short channels = 1; // Mono
    file->write(reinterpret_cast<char*>(&channels), 2);
    int sampleRate = 16000;
    file->write(reinterpret_cast<char*>(&sampleRate), 4);
    int byteRate = sampleRate * 2;
    file->write(reinterpret_cast<char*>(&byteRate), 4);
    short blockAlign = 2;
    file->write(reinterpret_cast<char*>(&blockAlign), 2);
    short bps = 16;
    file->write(reinterpret_cast<char*>(&bps), 2);
    file->write("data", 4);
    file->write(reinterpret_cast<char*>(&dataSize), 4);
}


