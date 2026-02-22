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
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QObject>
#include <QMap>
#include <QStringList>
#include <QDate>

class Dictionary : public QObject
{
    Q_OBJECT
public:
    explicit Dictionary(QObject *parent = nullptr);

    void init();
    void initializeMappings();
    QString getTimePhrase(int hour, int minute, bool isAllDay);
    QString getDatePhrase(const QDate &date);
    QString getOrdinalStr(int day);
    QString getCardinalStr(int number);
    bool contains(const QString &word) const;
    QStringList getDiphones(const QString &word) const;
    QStringList convertToDiphones(const QString& word);

private:

    QMap<QString, QStringList> m_data;
    QMap<QChar, QString> m_consonantMap;
    QMap<QString, QString> m_vowelClusterMap;
    QMap<QChar, QString> m_vowelMap;

    bool isVowel(QChar c) const;
    QString getPhoneticSound(QChar c) const;
    QStringList buildDiphoneList(const QStringList& phonemes);

    // signals:
};

#endif // DICTIONARY_H

