/* dbmanager.h
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

#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <sqlite3.h>
#include <glib.h>
#include "calendarevent.h"

// Initializes and creates the database file and schema.
// Returns an SQLite database handle. The caller is responsible for closing it.
sqlite3* db_open(const char *db_filename);

// Closes the database connection.
void db_close(sqlite3 *db);

// Inserts an event into the database.
// Returns the id of the new event on success, or -1 on failure.
int db_insert_event(sqlite3 *db, CalendarEvent* event);

// Deletes a specific event by its ID.
int db_delete_event(sqlite3 *db, int id);

// Deletes a specific event by its summary and date.
int db_delete_event_by_details(sqlite3 *db, const gchar* summary, gint year, gint month, gint day);

// Deletes all events from the database.
int db_delete_all_events(sqlite3 *db);

// Retrieves a specific event by its ID.
// The caller is responsible for unrefing the returned CalendarEvent object.
CalendarEvent* db_get_event_by_id(sqlite3 *db, int id);

// Retrieves all events for a specific day.
// The caller is responsible for freeing the GArray and the CalendarEvent objects within it.
GArray* db_get_all_events_year_month_day(sqlite3 *db, int year, int month, int day);


// Retrieves all events from the database.
// The caller is responsible for freeing the GArray and the CalendarEvent objects within it.
GArray* db_get_all_events(sqlite3 *db);

// Updates an existing event in the database.
// Returns 0 on success, or -1 on failure.
int db_update_event(sqlite3 *db, CalendarEvent* event);

// Retrieves a list of events matching a summary or location.
// The caller is responsible for freeing the GArray and the CalendarEvent objects within it.
GArray* db_get_events_by_search(sqlite3 *db, const gchar* summary, const gchar* location);

#endif // DBMANAGER_H
