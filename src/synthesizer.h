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
#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

#include <QObject>
#include <QVector>
#include <QStringList>
#include <QFile>
#include <QProcess>
#include <QCoreApplication>
//#include <QHash>
//#include <QMessageBox>
#include <QStandardPaths>

#include "dictionary.h"

class Synthesizer : public QObject
{
    Q_OBJECT
public:
    explicit Synthesizer(QObject *parent = nullptr);

    // The main vocoder logic
    QVector<int16_t> vocoder(const QStringList &diphones, float tempoFactor);

    void speak(const QString &text, Dictionary *dict, float tempo);

    // Bluetooth speaker flag
    void setBluetoothEnabled(bool enabled);
    bool getBluetoothEnabled() const;

    // Check if bluez-alsa-utils is installed
    static bool isBlueZAlsaInstalled();
    // File handling and playback
    void saveAndPlay(const QVector<int16_t> &buffer);

signals:
    void bluetoothStatusChanged(bool enabled);

private:
    // Internal helper for WAV files
    void writeWavHeader(QFile *file, int dataSize);
    QProcess* m_audioProcess = nullptr;
    bool  bluetoothEnabled = false;  // Default to false
};

#endif // SYNTHESIZER_H
