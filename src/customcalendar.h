/***************************************************************************
 *   Author Alan Crispin                                                   *
 *   crispinalan@gmail.com                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation.                                         *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 ***************************************************************************/

/*
GTK4 simple month view calendar which uses a grid of day labels 
*/

#pragma once

#include <gtk/gtk.h>

#include <stdio.h>

G_BEGIN_DECLS

#define CUSTOM_TYPE_CALENDAR (custom_calendar_get_type ())
#define CUSTOM_CALENDAR(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), CUSTOM_TYPE_CALENDAR, CustomCalendar))
#define CUSTOM_IS_CALENDAR(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CUSTOM_TYPE_CALENDAR))

typedef struct _CustomCalendar	 CustomCalendar;

GtkWidget *custom_calendar_new (void);

GDK_AVAILABLE_IN_ALL GType	custom_calendar_get_type(void) G_GNUC_CONST;

GDK_AVAILABLE_IN_ALL void custom_calendar_mark_day(CustomCalendar *calendar,  guint day);
GDK_AVAILABLE_IN_ALL void  custom_calendar_unmark_day (CustomCalendar *calendar,guint day);
GDK_AVAILABLE_IN_ALL void custom_calendar_reset_marks (CustomCalendar *calendar);
GDK_AVAILABLE_IN_ALL gboolean  custom_calendar_get_day_is_marked (CustomCalendar *calendar, guint day);

GDK_AVAILABLE_IN_ALL void custom_calendar_set_day_str(CustomCalendar *calendar, int day, char* title);
GDK_AVAILABLE_IN_ALL void custom_calendar_initialise_eventday_array(CustomCalendar *calendar);

GDK_AVAILABLE_IN_ALL void custom_calendar_set_tooltip_str(CustomCalendar *calendar, int day, char* title);
GDK_AVAILABLE_IN_ALL void custom_calendar_initialise_tooltip_array(CustomCalendar *calendar);

GDK_AVAILABLE_IN_ALL void custom_calendar_mark_holiday(CustomCalendar *calendar,  guint day);
GDK_AVAILABLE_IN_ALL void  custom_calendar_unmark_holiday(CustomCalendar *calendar,guint day);
GDK_AVAILABLE_IN_ALL void custom_calendar_reset_holidays (CustomCalendar *calendar);

GDK_AVAILABLE_IN_ALL void custom_calendar_set_holiday_str(CustomCalendar *calendar, int day, char* title);
GDK_AVAILABLE_IN_ALL void custom_calendar_initialise_holiday_array(CustomCalendar *calendar);

GDK_AVAILABLE_IN_ALL void custom_calendar_goto_today (CustomCalendar *calendar);
GDK_AVAILABLE_IN_ALL void custom_calendar_update (CustomCalendar *calendar);

GDK_AVAILABLE_IN_ALL int custom_calendar_get_day(CustomCalendar *calendar);
GDK_AVAILABLE_IN_ALL int custom_calendar_get_month(CustomCalendar *calendar);
GDK_AVAILABLE_IN_ALL int custom_calendar_get_year(CustomCalendar *calendar);

//properties

void custom_calendar_set_today_colour(CustomCalendar *self, const gchar* colourname);
const gchar* custom_calendar_get_today_colour(CustomCalendar *self);

void custom_calendar_set_event_colour(CustomCalendar *self, const gchar* colourname);
const gchar* custom_calendar_get_event_colour(CustomCalendar *self);

void custom_calendar_set_holiday_colour(CustomCalendar *self, const gchar* colourname);
const gchar* custom_calendar_get_holiday_colour(CustomCalendar *self);


void custom_calendar_set_show_tooltips(CustomCalendar *self, gboolean show_tooltips);
gboolean custom_calendar_get_show_tooltips(CustomCalendar *self);

//not public
static void custom_calendar_select_day (CustomCalendar *calendar, guint day, guint month, guint year);
static void callbk_next_month(CustomCalendar *calendar);
static void callbk_prev_month(CustomCalendar *calendar);
static void callbk_next_year(CustomCalendar *calendar);
static void callbk_prev_year(CustomCalendar *calendar);


G_DEFINE_AUTOPTR_CLEANUP_FUNC(CustomCalendar, g_object_unref)

G_END_DECLS
