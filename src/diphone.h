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
#ifndef DIPHONE_H
#define DIPHONE_H

#include <QString>

// The structure is fine as is
typedef struct {
    const char* name;
    const unsigned char* data;
    const unsigned int size;
} DiphoneEntry;


class Diphone {
public:
    Diphone();
    // This function finds the entry in the table
    static DiphoneEntry* findDiphoneEntry(const char* diphoneStr);

private:
    // We only declare that the table exists somewhere else
    static const DiphoneEntry diphone_table[];
    static const unsigned int diphoneTableSize;
};

#endif
