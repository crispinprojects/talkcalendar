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
#include "dispatcher.h"
#include <qdebug.h>

Dispatcher::Dispatcher(QObject *parent)
    : QObject{parent}
{

    speechProcess = new QProcess();
    speechProcessName = "espeak";
}


//----------------------------------------------------------
//espeak dispatcher
//----------------------------------------------------------
void Dispatcher::stop() {

    if (speechProcess->state() == QProcess::Running ) {

        speechProcess->terminate();
        qDebug()<<"speechProcess terminated with exit code = "<< speechProcess->exitCode();
    }
}

void Dispatcher::eSpeaker(const QString &text) {
    stop();

    // Find whichever engine the user has installed
    QString executable = QStandardPaths::findExecutable("espeak-ng");
    if (executable.isEmpty()) {
        executable = QStandardPaths::findExecutable("espeak");
    }

    if (executable.isEmpty()) {
        qDebug() << "Speech engine (espeak or espeak-ng) not found.";
        return;
    }

    // espeak arguments
    int amplitude = 80;
    int pitch = 50;
    int speed = 180;
    int wordgap = 4;
    QString voiceName = "-ven+m7";

    QStringList arguments;
    arguments << voiceName
              << "-s" << QString::number(speed)
              << "-g" << QString::number(wordgap)
              << "-p" << QString::number(pitch)
              << "-a" << QString::number(amplitude)
              << text;

    speechProcessName = executable;
    speechProcess->start(speechProcessName, arguments);
}
