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

    //void loadLexicon();
    //void setupG2PRules();
    void initializeLexicon();
    void setupG2PRules();
    QString getTimePhrase(int hour, int minute, bool isAllDay);
    QString getDatePhrase(const QDate &date);
    QString getOrdinalStr(int day);
    QString getCardinalStr(int number);

    QStringList transcribeWordDecisionTree(const QString& word);




    //bool contains(const QString &word) const;
    //QStringList getDiphones(const QString &word) const;
    //QStringList transcribeWord(const QString& word);

private:

    QMap<QString, QStringList> m_data;
    QMap<QChar, QString> m_consonantMap;
    QMap<QString, QString> m_vowelClusterMap;
    QMap<QChar, QString> m_vowelMap;

    QStringList buildDiphoneList(const QStringList& phonemes);

    //Decision tree
    //c=current, p=previous, n=next nn=nextnext nnn=nextnextnext
    // nn and nnn are LOOK-AHEAD

    QString predictA(QChar p, QChar c, QChar n, QChar nn, QChar nnn);
    QString predictB(QChar p, QChar c, QChar n, QChar nn, QChar nnn);
    QString predictC(QChar p, QChar c, QChar n, QChar nn, QChar nnn);
    QString predictD(QChar p, QChar c, QChar n, QChar nn, QChar nnn);
    QString predictE(QChar p, QChar c, QChar n, QChar nn, QChar nnn);
    QString predictF(QChar p, QChar c, QChar n, QChar nn, QChar nnn);
    QString predictG(QChar p, QChar c, QChar n, QChar nn, QChar nnn);
    QString predictH(QChar p, QChar c, QChar n, QChar nn, QChar nnn);
    QString predictI(QChar p, QChar c, QChar n, QChar nn, QChar nnn);
    QString predictJ(QChar p, QChar c, QChar n, QChar nn, QChar nnn);
    QString predictK(QChar p, QChar c, QChar n, QChar nn, QChar nnn);
    QString predictL(QChar p, QChar c, QChar n, QChar nn, QChar nnn);
    QString predictM(QChar p, QChar c, QChar n, QChar nn, QChar nnn);
    QString predictN(QChar p, QChar c, QChar n, QChar nn, QChar nnn);
    QString predictO(QChar p, QChar c, QChar n, QChar nn, QChar nnn);
    QString predictP(QChar p, QChar c, QChar n, QChar nn, QChar nnn);
    QString predictQ(QChar p, QChar c, QChar n, QChar nn, QChar nnn);
    QString predictR(QChar p, QChar c, QChar n, QChar nn, QChar nnn);
    QString predictS(QChar p, QChar c, QChar n, QChar nn, QChar nnn);
    QString predictT(QChar p, QChar c, QChar n, QChar nn, QChar nnn);
    QString predictU(QChar p, QChar c, QChar n, QChar nn, QChar nnn);
    QString predictV(QChar p, QChar c, QChar n, QChar nn, QChar nnn);
    QString predictW(QChar p, QChar c, QChar n, QChar nn, QChar nnn);
    QString predictX(QChar p, QChar c, QChar n, QChar nn, QChar nnn);
    QString predictY(QChar p, QChar c, QChar n, QChar nn, QChar nnn);
    QString predictZ(QChar p, QChar c, QChar n, QChar nn, QChar nnn);

    // signals:
};

#endif // DICTIONARY_H

