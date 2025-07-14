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

#pragma once

#include <gtk/gtk.h>
#include <glib/gstdio.h>  //needed for g_mkdir
#include <math.h>  //compile with -lm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#include "calendarevent.h"

const char * get_db_path(void);
void db_create_events_table(void);
int db_insert_event(CalendarEvent *event);
void db_update_event(CalendarEvent *event, int id);
void db_delete_event(CalendarEvent *event);

int db_get_number_of_rows_all(void);
int db_get_number_of_rows_month_year(int month, int year);
int db_get_number_of_rows_year_month_day(int year, int month, int day);
int db_get_number_of_isyearly_events_month(int month);
int db_get_id(CalendarEvent *evt);

void db_get_event(int index, CalendarEvent *event);
void db_get_all_events(GArray *evt_arry);

void db_get_all_events_year_month(GArray *evt_arry, int year, int month);

//void db_get_all_multiday_events_year_month(GArray *evt_arry, int year, int month);
void db_get_all_enddate_events_year_month(GArray *evt_arry, int year, int month);

void db_get_upcoming_events(GArray *evt_arry, int year, int month, int from ,int to);

void db_get_all_events_year_month_day(GArray *evt_arry, int year, int month, int day);

void db_get_isyearly_events_month(GArray *evt_arry, int month);
void db_get_isyearly_events_day(GArray *evt_arry, int month, int day);

void db_delete_row(int id);
void db_delete_all(void);
void db_reset_sequence(void);


