/* dbmanager.c
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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glib.h>
#include <sqlite3.h>
#include "dbmanager.h"
#include "calendarevent.h"

/**
 * @brief Creates a CalendarEvent struct from an SQLite query result.
 * @param stmt An SQLite prepared statement.
 * @return A new CalendarEvent struct, or NULL on failure.
 */
static CalendarEvent* create_event_from_query(sqlite3_stmt *stmt) {
    CalendarEvent* event = g_object_new(CALENDAR_TYPE_EVENT, NULL);
    
    calendar_event_set_eventid(event, sqlite3_column_int(stmt, 0));
    calendar_event_set_summary(event, (const gchar*)sqlite3_column_text(stmt, 1));
    calendar_event_set_location(event, (const gchar*)sqlite3_column_text(stmt, 2));
    calendar_event_set_description(event, (const gchar*)sqlite3_column_text(stmt, 3));
    calendar_event_set_start_year(event, sqlite3_column_int(stmt, 4));
    calendar_event_set_start_month(event, sqlite3_column_int(stmt, 5));
    calendar_event_set_start_day(event, sqlite3_column_int(stmt, 6));
    calendar_event_set_start_hour(event, sqlite3_column_int(stmt, 7));
    calendar_event_set_start_min(event, sqlite3_column_int(stmt, 8));
    calendar_event_set_end_year(event, sqlite3_column_int(stmt, 9));
    calendar_event_set_end_month(event, sqlite3_column_int(stmt, 10));
    calendar_event_set_end_day(event, sqlite3_column_int(stmt, 11));
    calendar_event_set_end_hour(event, sqlite3_column_int(stmt, 12));
    calendar_event_set_end_min(event, sqlite3_column_int(stmt, 13));
    calendar_event_set_is_yearly(event, sqlite3_column_int(stmt, 14));
    calendar_event_set_is_allday(event, sqlite3_column_int(stmt, 15));
    calendar_event_set_is_priority(event, sqlite3_column_int(stmt, 16));
    
    return event;
}

/**
 * @brief Checks if a file exists.
 * @param filename The name of the file to check.
 * @return TRUE if the file exists, FALSE otherwise.
 */
static gboolean db_file_exist(const gchar *filename) {
    return g_file_test(filename, G_FILE_TEST_EXISTS);
}

/**
 * @brief Creates the events table in the database if it doesn't exist.
 * @param db A pointer to the SQLite database connection.
 * @return 0 on success, 1 on failure.
 */
static int db_create_events_table(sqlite3 *db) {
    const char *sql = "CREATE TABLE IF NOT EXISTS events ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "summary TEXT NOT NULL,"
                      "location TEXT,"
                      "description TEXT,"
                      "start_year INTEGER,"
                      "start_month INTEGER,"
                      "start_day INTEGER,"
                      "start_hour INTEGER,"
                      "start_min INTEGER,"
                      "end_year INTEGER,"
                      "end_month INTEGER,"
                      "end_day INTEGER,"
                      "end_hour INTEGER,"
                      "end_min INTEGER,"
                      "is_yearly INTEGER,"
                      "is_allday INTEGER,"
                      "is_priority INTEGER);";
    
    char *err_msg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        g_critical("Failed to create table: %s", err_msg);
        sqlite3_free(err_msg);
        return 1;
    }
    return 0;
}

/**
 * @brief Opens a connection to an SQLite database.
 * @param db_filename The name of the database file.
 * @return A pointer to the database handle, or NULL on failure.
 */
sqlite3* db_open(const char *db_filename) {
    sqlite3 *db_handle;
    int rc = sqlite3_open(db_filename, &db_handle);
    if (rc != SQLITE_OK) {
        g_critical("Cannot open database: %s", sqlite3_errmsg(db_handle));
        sqlite3_close(db_handle);
        return NULL;
    }

    if (db_create_events_table(db_handle) != 0) {
        g_critical("Failed to create database table.");
        sqlite3_close(db_handle);
        return NULL;
    }

    return db_handle;
}

/**
 * @brief Closes the database connection.
 * @param db A pointer to the database handle.
 * @return void
 */
void db_close(sqlite3 *db) {
    if (db) {
        sqlite3_close(db);
        g_print("Database connection closed.\n");
    }
}

/**
 * @brief Inserts a new event into the database.
 * @param db A pointer to the database handle.
 * @param event A pointer to the CalendarEvent struct to insert.
 * @return The ID of the inserted row on success, -1 on failure.
 */
int db_insert_event(sqlite3 *db, CalendarEvent* event) {
    const char *sql = "INSERT INTO events (summary, location, description, start_year, start_month, "
                      "start_day, start_hour, start_min, end_year, end_month, end_day, end_hour, "
                      "end_min, is_yearly, is_allday, is_priority) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        g_warning("Failed to prepare statement: %s", sqlite3_errmsg(db));
        return -1;
    }
    
    sqlite3_bind_text(stmt, 1, calendar_event_get_summary(event), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, calendar_event_get_location(event), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, calendar_event_get_description(event), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 4, calendar_event_get_start_year(event));
    sqlite3_bind_int(stmt, 5, calendar_event_get_start_month(event));
    sqlite3_bind_int(stmt, 6, calendar_event_get_start_day(event));
    sqlite3_bind_int(stmt, 7, calendar_event_get_start_hour(event));
    sqlite3_bind_int(stmt, 8, calendar_event_get_start_min(event));
    sqlite3_bind_int(stmt, 9, calendar_event_get_end_year(event));
    sqlite3_bind_int(stmt, 10, calendar_event_get_end_month(event));
    sqlite3_bind_int(stmt, 11, calendar_event_get_end_day(event));
    sqlite3_bind_int(stmt, 12, calendar_event_get_end_hour(event));
    sqlite3_bind_int(stmt, 13, calendar_event_get_end_min(event));
    sqlite3_bind_int(stmt, 14, calendar_event_get_is_yearly(event));
    sqlite3_bind_int(stmt, 15, calendar_event_get_is_allday(event));
    sqlite3_bind_int(stmt, 16, calendar_event_get_is_priority(event));

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        g_warning("Failed to execute statement: %s", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }
    sqlite3_finalize(stmt);
    return sqlite3_last_insert_rowid(db);
}

/**
 * @brief Deletes an event from the database by its ID.
 * @param db A pointer to the database handle.
 * @param id The ID of the event to delete.
 * @return 0 on success, 1 on failure.
 */
int db_delete_event(sqlite3 *db, int id) {
    sqlite3_stmt *stmt;
    const char *sql = "DELETE FROM events WHERE id = ?";
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
        g_warning("Failed to prepare statement: %s", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_bind_int(stmt, 1, id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        g_warning("Failed to execute statement: %s", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 1;
    }

    sqlite3_finalize(stmt);
    return 0;
}

int db_delete_event_by_details(sqlite3 *db, const gchar* summary, gint year, gint month, gint day) {
    sqlite3_stmt *stmt;
    const char *sql = "DELETE FROM events WHERE summary = ? AND start_year = ? AND start_month = ? AND start_day = ?";
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
        g_warning("Failed to prepare statement: %s", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_bind_text(stmt, 1, summary, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, year);
    sqlite3_bind_int(stmt, 3, month);
    sqlite3_bind_int(stmt, 4, day);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        g_warning("Failed to execute statement: %s", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 1;
    }

    sqlite3_finalize(stmt);
    return 0;
}

int db_delete_all_events(sqlite3 *db) {
    const char *sql = "DELETE FROM events";
    char *err_msg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        g_warning("Failed to delete all events: %s", err_msg);
        sqlite3_free(err_msg);
        return 1;
    }
    return 0;
}

/**
 * @brief Retrieves a single event from the database by its ID.
 * @param db A pointer to the database handle.
 * @param id The ID of the event to retrieve.
 * @return A new CalendarEvent struct on success, NULL if not found or on failure.
 */
CalendarEvent* db_get_event_by_id(sqlite3 *db, int id) {
    const char *sql = "SELECT id, summary, location, description, start_year, start_month, "
                      "start_day, start_hour, start_min, end_year, end_month, end_day, end_hour, "
                      "end_min, is_yearly, is_allday, is_priority FROM events WHERE id = ?";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        g_warning("Failed to prepare statement: %s", sqlite3_errmsg(db));
        return NULL;
    }
    sqlite3_bind_int(stmt, 1, id);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        CalendarEvent* event = create_event_from_query(stmt);
        sqlite3_finalize(stmt);
        return event;
    }
    sqlite3_finalize(stmt);
    return NULL;
}


//======================================================================

GArray* db_get_all_events_year_month_day(sqlite3 *db, int year, int month, int day) {
    const char *sql = "SELECT id, summary, location, description, start_year, start_month, "
                      "start_day, start_hour, start_min, end_year, end_month, end_day, end_hour, "
                      "end_min, is_yearly, is_allday, is_priority FROM events WHERE (start_year = ? OR is_yearly = 1) AND start_month = ? AND start_day = ? ORDER BY start_hour, start_min asc";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        g_warning("Failed to prepare statement: %s", sqlite3_errmsg(db));
        return NULL;
    }
    sqlite3_bind_int(stmt, 1, year);
    sqlite3_bind_int(stmt, 2, month);
    sqlite3_bind_int(stmt, 3, day);

    GArray *events_array = g_array_new(FALSE, FALSE, sizeof(CalendarEvent*));
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        CalendarEvent* event = create_event_from_query(stmt);
        g_array_append_vals(events_array, &event, 1);
    }
    sqlite3_finalize(stmt);
    return events_array;
}


/**
 * @brief Retrieves all events from the database 
 * @param db A pointer to the database handle.
 * @return GArray containing all events
 */
GArray* db_get_all_events(sqlite3 *db) {
    const char *sql = "SELECT id, summary, location, description, start_year, start_month, "
                      "start_day, start_hour, start_min, end_year, end_month, end_day, end_hour, "
                      "end_min, is_yearly, is_allday, is_priority FROM events ORDER BY start_year, start_month, start_day, start_hour, start_min";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        g_warning("Failed to prepare statement: %s", sqlite3_errmsg(db));
        return NULL;
    }

    GArray *events_array = g_array_new(FALSE, FALSE, sizeof(CalendarEvent*));
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        CalendarEvent* event = create_event_from_query(stmt);
        g_array_append_vals(events_array, &event, 1);
    }
    sqlite3_finalize(stmt);
    return events_array;
}


/**
 * @brief Updates an existing event in the database.
 * @param db A pointer to the database handle.
 * @param event A pointer to the CalendarEvent struct with updated information.
 * @return 0 on success, 1 on failure.
 */
int db_update_event(sqlite3 *db, CalendarEvent* event) {
    const char *sql = "UPDATE events SET summary = ?, location = ?, description = ?, start_year = ?, "
                      "start_month = ?, start_day = ?, start_hour = ?, start_min = ?, end_year = ?, "
                      "end_month = ?, end_day = ?, end_hour = ?, end_min = ?, is_yearly = ?, "
                      "is_allday = ?, is_priority = ? WHERE id = ?";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        g_warning("Failed to prepare statement: %s", sqlite3_errmsg(db));
        return -1;
    }
    
    sqlite3_bind_text(stmt, 1, calendar_event_get_summary(event), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, calendar_event_get_location(event), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, calendar_event_get_description(event), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 4, calendar_event_get_start_year(event));
    sqlite3_bind_int(stmt, 5, calendar_event_get_start_month(event));
    sqlite3_bind_int(stmt, 6, calendar_event_get_start_day(event));
    sqlite3_bind_int(stmt, 7, calendar_event_get_start_hour(event));
    sqlite3_bind_int(stmt, 8, calendar_event_get_start_min(event));
    sqlite3_bind_int(stmt, 9, calendar_event_get_end_year(event));
    sqlite3_bind_int(stmt, 10, calendar_event_get_end_month(event));
    sqlite3_bind_int(stmt, 11, calendar_event_get_end_day(event));
    sqlite3_bind_int(stmt, 12, calendar_event_get_end_hour(event));
    sqlite3_bind_int(stmt, 13, calendar_event_get_end_min(event));
    sqlite3_bind_int(stmt, 14, calendar_event_get_is_yearly(event));
    sqlite3_bind_int(stmt, 15, calendar_event_get_is_allday(event));
    sqlite3_bind_int(stmt, 16, calendar_event_get_is_priority(event));
    sqlite3_bind_int(stmt, 17, calendar_event_get_eventid(event));

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        g_warning("Failed to execute statement: %s", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }
    sqlite3_finalize(stmt);
    return 0;
}


/**
 * @brief Retrieves all events from the database that match the given criteria.
 * @param db A pointer to the database handle.
 * @param summary The summary to search for (can be NULL for any).
 * @param location The location to search for (can be NULL for any).
 * @return A GArray of CalendarEvent structs. The array and its contents must be freed by the caller.
 */

GArray* db_get_events_by_search(sqlite3 *db, const gchar* summary, const gchar* location) {
    GString *sql_builder = g_string_new("SELECT id, summary, location, description, start_year, start_month, "
                                        "start_day, start_hour, start_min, end_year, end_month, end_day, end_hour, "
                                        "end_min, is_yearly, is_allday, is_priority FROM events WHERE 1=1");
    
    if (summary) {
        g_string_append(sql_builder, " AND summary LIKE ?");
    }
    if (location) {
        g_string_append(sql_builder, " AND location LIKE ?");
    }
    
    g_string_append(sql_builder, " ORDER BY start_year, start_month, start_day, start_hour, start_min");

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, sql_builder->str, -1, &stmt, NULL);
    g_string_free(sql_builder, TRUE);

    if (rc != SQLITE_OK) {
        g_warning("Failed to prepare statement: %s", sqlite3_errmsg(db));
        return NULL;
    }
    
    int param_index = 1;
    if (summary) {
        gchar* like_summary = g_strdup_printf("%%%s%%", summary);
        sqlite3_bind_text(stmt, param_index++, like_summary, -1, SQLITE_TRANSIENT);
        g_free(like_summary);
    }
    if (location) {
        gchar* like_location = g_strdup_printf("%%%s%%", location);
        sqlite3_bind_text(stmt, param_index++, like_location, -1, SQLITE_TRANSIENT);
        g_free(like_location);
    }

    GArray *events_array = g_array_new(FALSE, FALSE, sizeof(CalendarEvent*));
    
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        CalendarEvent* event = create_event_from_query(stmt);
        g_array_append_vals(events_array, &event, 1);
    }

    if (rc != SQLITE_DONE) {
        g_warning("Failed to execute search: %s", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    return events_array;
}


