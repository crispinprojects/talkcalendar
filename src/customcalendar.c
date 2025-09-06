/* customcalendar.c
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

//====================================================================
// GTK4  Month View Calendar
// Author: Alan Crispin <crispinalan@gmail.com>
// Date: July 2025
// Month View Calendar with tooltips for the Talk Calendar Project
//====================================================================
#include <glib.h>
#include <pango/pango.h>
#include "customcalendar.h"

// Static month names, no allocation needed
static const char *monthname[] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

// declarations
void custom_calendar_select_day(CustomCalendar *calendar, guint dday, guint month, guint year);
void custom_calendar_button_press(GtkGestureClick *gesture, int n_press, double x, double y, gpointer user_data);
void custom_calendar_goto_dmy(CustomCalendar *calendar, int day, int month, int year);
static void update_date_labels(CustomCalendar *calendar);
static void update_day_grid(CustomCalendar *calendar);
static void setup_css_providers(CustomCalendar *calendar);
static void update_css_providers(CustomCalendar *calendar);

// signals
enum
{
    DAY_SELECTED_SIGNAL,
    PREV_MONTH_SIGNAL,
    NEXT_MONTH_SIGNAL,
    PREV_YEAR_SIGNAL,
    NEXT_YEAR_SIGNAL,
    LAST_SIGNAL
};

static guint custom_calendar_signals[LAST_SIGNAL] = {0};

typedef struct _CustomCalendarClass CustomCalendarClass;
typedef struct _CustomCalendarPrivate CustomCalendarPrivate;

/**
 * @brief The main structure for the CustomCalendar widget.
 */
struct _CustomCalendar
{
    GtkWidget widget; //parent
    GtkWidget *header; //navigation header
    GtkWidget *btn_next_month;
    GtkWidget *month_label;
    GtkWidget *btn_prev_month;
    GtkWidget *date_label;
    GtkWidget *btn_next_year;
    GtkWidget *year_label;
    GtkWidget *btn_prev_year;

    GtkWidget *grid; //calendar grid layout
    GtkWidget *monday_label;
    GtkWidget *tuesday_label;
    GtkWidget *wednesday_label;
    GtkWidget *thursday_label;
    GtkWidget *friday_label;
    GtkWidget *saturday_label;
    GtkWidget *sunday_label;
    GtkWidget *day_number_labels[6][7];
    GDateTime *date;
    int day;
    int month;
    int year;
    int day_month[6][7];
    int days[6][7];
    gchar** tooltip_array;
    int num_marked_days;
    int marked_day[32];
    const gchar* today_colour;
    const gchar* event_colour;
    gboolean show_tooltips;
    GtkCssProvider *provider_today;
    GtkCssProvider *provider_event;
    GtkCssProvider *provider_none_month_day;
    GtkCssProvider *provider_frame;
};

/**
 * @brief The class structure for CustomCalendar, 
 * including virtual function pointers for signals.
 */
struct _CustomCalendarClass
{
    GtkWidgetClass parent_class;
    void (*day_selected)(GtkCalendar *calendar);
    void (*prev_month)(GtkCalendar *calendar);
    void (*next_month)(GtkCalendar *calendar);
    void (*prev_year)(GtkCalendar *calendar);
    void (*next_year)(GtkCalendar *calendar);
};

// Defines the GObject type for CustomCalendar
G_DEFINE_TYPE(CustomCalendar, custom_calendar, GTK_TYPE_WIDGET)

/**
 * @brief Property identifiers for CustomCalendar.
 */
enum {
    PROP_0,
    PROP_TODAYCOLOUR,
    PROP_EVENTCOLOUR,
    PROP_SHOWTOOLTIPS,
    LAST_PROP
};

static GParamSpec *properties[LAST_PROP];

/**
 * @brief Sets the color for today's date in the calendar.
 * @param self The CustomCalendar instance.
 * @param colour_str The color string (e.g., "rgb(221,160,221)").
 */
void custom_calendar_set_today_colour(CustomCalendar *self, const gchar* colour_str)
{
    if (g_strcmp0(self->today_colour, colour_str) != 0) {
        g_free((gchar*)self->today_colour);
        self->today_colour = g_strdup(colour_str);
        update_css_providers(self);
    }
}
/**
 * @brief Gets the color for today's date.
 * @param self The CustomCalendar instance.
 * @return The color string.
 */
const gchar* custom_calendar_get_today_colour(CustomCalendar *self){
    return self->today_colour;
}
/**
 * @brief Sets the color for event days.
 * @param self The CustomCalendar instance.
 * @param colourname The color string.
 */
void custom_calendar_set_event_colour(CustomCalendar *self, const gchar* colourname)
{
    if (g_strcmp0(self->event_colour, colourname) != 0) {
        g_free((gchar*)self->event_colour);
        self->event_colour = g_strdup(colourname);
        update_css_providers(self);
    }
}

/**
 * @brief Gets the color for event days.
 * @param self The CustomCalendar instance.
 * @return The color string.
 */
const gchar* custom_calendar_get_event_colour(CustomCalendar *self){
    return self->event_colour;
}

/**
 * @brief Sets whether to show tooltips.
 * @param self The CustomCalendar instance.
 * @param show_tooltips Boolean to show/hide tooltips.
 */
void custom_calendar_set_show_tooltips(CustomCalendar *self, gboolean show_tooltips)
{
    self->show_tooltips = show_tooltips;
}

/**
 * @brief Sets a property on the object.
 * @param object The GObject instance.
 * @param prop_id The property ID.
 * @param value The value to set.
 * @param pspec The parameter specification.
 */
static void custom_calendar_set_property(GObject *object,
                                         guint prop_id,
                                         const GValue *value,
                                         GParamSpec *pspec)
{
    CustomCalendar *self = (CustomCalendar *)object;

    switch (prop_id)
    {
        case PROP_TODAYCOLOUR:
            custom_calendar_set_today_colour(self, g_value_get_string(value));
            break;
        case PROP_EVENTCOLOUR:
            custom_calendar_set_event_colour(self, g_value_get_string(value));
            break;
        case PROP_SHOWTOOLTIPS:
            custom_calendar_set_show_tooltips(self, g_value_get_boolean(value));
            break;

        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
            break;
    }
}

/**
 * @brief Gets a property from the object.
 * @param object The GObject instance.
 * @param prop_id The property ID.
 * @param value The value to get.
 * @param pspec The parameter specification.
 */
static void custom_calendar_get_property(GObject *object,
                                         guint prop_id,
                                         GValue *value,
                                         GParamSpec *pspec)
{
    CustomCalendar *self = (CustomCalendar *)object;

    switch (prop_id)
    {
        case PROP_TODAYCOLOUR:
            g_value_set_string(value, custom_calendar_get_today_colour(self));
            break;
        case PROP_EVENTCOLOUR:
            g_value_set_string(value, custom_calendar_get_event_colour(self));
            break;
        case PROP_SHOWTOOLTIPS:
            g_value_set_boolean(value, custom_calendar_get_show_tooltips(self));
            break;

        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
            break;
    }
}
/**
 * @brief Frees resources when the object is disposed.
 * @param object The GObject instance.
 */
static void custom_calendar_dispose(GObject *object)
{
    CustomCalendar *calendar = CUSTOM_CALENDAR(object);
    g_clear_pointer(&calendar->date, g_date_time_unref);
    g_clear_pointer(&calendar->header, gtk_widget_unparent);
    g_clear_pointer(&calendar->grid, gtk_widget_unparent);
    g_clear_pointer(&calendar->provider_today, g_object_unref);
    g_clear_pointer(&calendar->provider_event, g_object_unref);
    g_clear_pointer(&calendar->provider_none_month_day, g_object_unref);
    g_clear_pointer(&calendar->provider_frame, g_object_unref);

    for (int i = 0; i < 32; i++) {
        g_free(calendar->tooltip_array[i]);
    }
    g_clear_pointer(&calendar->tooltip_array, g_free);

    G_OBJECT_CLASS(custom_calendar_parent_class)->dispose(object);
}


/**
 * @brief Class initialization function.
 * @param klass The CustomCalendarClass instance.
 */
static void custom_calendar_class_init(CustomCalendarClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    GtkWidgetClass *widget_class;
    widget_class = (GtkWidgetClass *)klass;

    object_class->dispose = custom_calendar_dispose;

    object_class->set_property = custom_calendar_set_property;
    object_class->get_property = custom_calendar_get_property;

    properties[PROP_TODAYCOLOUR] =
        g_param_spec_string("todaycolour",
                            "todaycolour",
                            "colour string for today",
                            "rgb(221,160,221)",
                            (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

    properties[PROP_EVENTCOLOUR] =
        g_param_spec_string("eventcolour",
                            "eventcolour",
                            "colour string for an event",
                            "rgb(211,211,211)",
                            (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

    properties[PROP_SHOWTOOLTIPS] =
        g_param_spec_boolean("showtooltips",
                             "showtooltips",
                             "sets if calendar has tooltips",
                             TRUE,
                             G_PARAM_READWRITE);

    g_object_class_install_properties(object_class, LAST_PROP, properties);

    custom_calendar_signals[DAY_SELECTED_SIGNAL] =
        g_signal_new("day-selected",
                     G_OBJECT_CLASS_TYPE(object_class),
                     G_SIGNAL_RUN_FIRST,
                     G_STRUCT_OFFSET(CustomCalendarClass, day_selected),
                     NULL, NULL,
                     NULL,
                     G_TYPE_NONE, 0);

    custom_calendar_signals[NEXT_MONTH_SIGNAL] =
        g_signal_new("next-month",
                     G_OBJECT_CLASS_TYPE(object_class),
                     G_SIGNAL_RUN_FIRST,
                     G_STRUCT_OFFSET(CustomCalendarClass, next_month),
                     NULL, NULL,
                     NULL,
                     G_TYPE_NONE, 0);

    custom_calendar_signals[PREV_MONTH_SIGNAL] =
        g_signal_new("prev-month",
                     G_OBJECT_CLASS_TYPE(object_class),
                     G_SIGNAL_RUN_FIRST,
                     G_STRUCT_OFFSET(CustomCalendarClass, prev_month),
                     NULL, NULL,
                     NULL,
                     G_TYPE_NONE, 0);

    custom_calendar_signals[NEXT_YEAR_SIGNAL] =
        g_signal_new("next-year",
                     G_OBJECT_CLASS_TYPE(object_class),
                     G_SIGNAL_RUN_FIRST,
                     G_STRUCT_OFFSET(CustomCalendarClass, next_year),
                     NULL, NULL,
                     NULL,
                     G_TYPE_NONE, 0);

    custom_calendar_signals[PREV_YEAR_SIGNAL] =
        g_signal_new("prev-year",
                     G_OBJECT_CLASS_TYPE(object_class),
                     G_SIGNAL_RUN_FIRST,
                     G_STRUCT_OFFSET(CustomCalendarClass, prev_year),
                     NULL, NULL,
                     NULL,
                     G_TYPE_NONE, 0);

    gtk_widget_class_set_layout_manager_type(widget_class, GTK_TYPE_BOX_LAYOUT);
}

/**
 * @brief Creates a new CustomCalendar widget.
 * @return A new CustomCalendar instance.
 */
GtkWidget *custom_calendar_new(void)
{
    return g_object_new(CUSTOM_TYPE_CALENDAR, NULL);
}

/**
 * @brief Initializes all tooltip strings to empty strings.
 * @param calendar The CustomCalendar instance.
 */
void custom_calendar_initialise_tooltip_array(CustomCalendar *calendar)
{
    for (int i = 0; i < 32; i++)
    {
        g_free(calendar->tooltip_array[i]);
        calendar->tooltip_array[i] = g_strdup("");
    }
}

/**
 * @brief Appends a new tooltip string to a specific day's tooltip.
 * @param calendar The CustomCalendar instance.
 * @param day The day number (1-31).
 * @param tooltip_str The string to append.
 */
void custom_calendar_set_tooltip_str(CustomCalendar *calendar, int day, char* tooltip_str)
{
    if (day >= 1 && day <= 31)
    {
        char* old_tooltip_str = calendar->tooltip_array[day];
        calendar->tooltip_array[day] = g_strconcat(old_tooltip_str, "\n", tooltip_str, NULL);
        g_free(old_tooltip_str);
    }
}

/**
 * @brief Gets whether tooltips are shown.
 * @param self The CustomCalendar instance.
 * @return Boolean value.
 */
gboolean custom_calendar_get_show_tooltips(CustomCalendar *self)
{
    return self->show_tooltips;
}

/**
 * @brief Resets all marked days.
 * @param calendar The CustomCalendar instance.
 */
 void custom_calendar_reset_marks(CustomCalendar *calendar)
{
    g_return_if_fail(CUSTOM_IS_CALENDAR(calendar));

    for (int i = 0; i < 32; i++){
        calendar->marked_day[i] = FALSE;
    }
    calendar->num_marked_days = 0;
}

/**
 * @brief Marks a specific day as having an event.
 * @param calendar The CustomCalendar instance.
 * @param day The day number (1-31).
 */
void custom_calendar_mark_day(CustomCalendar *calendar, guint day)
{
    g_return_if_fail(CUSTOM_IS_CALENDAR(calendar));

    if (day >= 1 && day <= 31)
    {
        calendar->marked_day[day] = TRUE;
        calendar->num_marked_days++;
    }
}

/**
 * @brief Unmarks a specific day.
 * @param calendar The CustomCalendar instance.
 * @param day The day number (1-31).
 */
void custom_calendar_unmark_day(CustomCalendar *calendar, guint day)
{
    g_return_if_fail(CUSTOM_IS_CALENDAR(calendar));

    if (day >= 1 && day <= 31)
    {
        calendar->marked_day[day] = FALSE;
        calendar->num_marked_days--;
    }
}

/**
 * @brief Checks if a day is marked.
 * @param calendar The CustomCalendar instance.
 * @param day The day number (1-31).
 * @return TRUE if the day is marked, FALSE otherwise.
 */
gboolean custom_calendar_get_day_is_marked(CustomCalendar *calendar, guint day)
{
    if (day >= 1 && day <= 31)
        return calendar->marked_day[day];
    return FALSE;
}

/**
 * @brief Determines the day of the week for a given date.
 * @param day The day of the month.
 * @param month The month (1-12).
 * @param year The year.
 * @return A newly allocated string with the weekday name.
 */
static char* get_day_of_week(int day, int month, int year)
{
    char* weekday_str = "unknown";
    GDate* day_date = g_date_new_dmy(day, month, year);
    if (day_date) {
        GDateWeekday weekday = g_date_get_weekday(day_date);
        switch(weekday)
        {
            case G_DATE_MONDAY: weekday_str = "Monday"; break;
            case G_DATE_TUESDAY: weekday_str = "Tuesday"; break;
            case G_DATE_WEDNESDAY: weekday_str = "Wednesday"; break;
            case G_DATE_THURSDAY: weekday_str = "Thursday"; break;
            case G_DATE_FRIDAY: weekday_str = "Friday"; break;
            case G_DATE_SATURDAY: weekday_str = "Saturday"; break;
            case G_DATE_SUNDAY: weekday_str = "Sunday"; break;
            default: break;
        }
        g_date_free(day_date);
    }
    return g_strdup(weekday_str);
}

/**
 * @brief Calculates the first day of the month.
 * @param month The month (1-12).
 * @param year The year.
 * @return An integer representing the first day of the month (0=Sunday, 1=Monday...).
 */
static int first_day_of_month(int month, int year)
{
    if (month < 3)
    {
        month += 12;
        year--;
    }
    int century = year / 100;
    year = year % 100;
    return (((13 * (month + 1)) / 5) +
            (century / 4) + (5 * century) +
            year + (year / 4)) % 7;
}


/**
 * @brief Initializes the CustomCalendar widget.
 * @param calendar The CustomCalendar instance.
 */
static void custom_calendar_init(CustomCalendar *calendar)
{
    GtkWidget *widget = GTK_WIDGET(calendar);

    calendar->day = 0;
    calendar->month = 0;
    calendar->year = 0;
    calendar->show_tooltips = TRUE;
    calendar->tooltip_array = g_new(gchar*, 32);
    for (int i=0; i<32; i++) {
        calendar->tooltip_array[i] = NULL;
    }
    
    custom_calendar_initialise_tooltip_array(calendar);
    
    // Set colour defaults and initialize CSS providers
    calendar->today_colour = g_strdup("rgb(221,160,221)"); //plum
    calendar->event_colour = g_strdup("rgb(211,211,211)"); //light grey
    setup_css_providers(calendar);

    gtk_widget_set_focusable(widget, TRUE);

    GtkGesture *gesture = gtk_gesture_click_new();
    g_signal_connect(gesture, "pressed", G_CALLBACK(custom_calendar_button_press), calendar);
    gtk_widget_add_controller(GTK_WIDGET(calendar), GTK_EVENT_CONTROLLER(gesture));

    calendar->header = g_object_new(GTK_TYPE_BOX, "css-name", "header", NULL);

    calendar->btn_next_month = gtk_button_new_from_icon_name("pan-end-symbolic");
    gtk_button_set_can_shrink(GTK_BUTTON(calendar->btn_next_month), TRUE);
    gtk_widget_set_tooltip_text(calendar->btn_next_month, "Next Month");
    g_signal_connect_swapped(calendar->btn_next_month, "clicked", G_CALLBACK(callbk_next_month), calendar);

    calendar->btn_next_year = gtk_button_new_from_icon_name("pan-end-symbolic");
    gtk_button_set_can_shrink(GTK_BUTTON(calendar->btn_next_year), TRUE);
    gtk_widget_set_tooltip_text(calendar->btn_next_year, "Next Year");
    g_signal_connect_swapped(calendar->btn_next_year, "clicked", G_CALLBACK(callbk_next_year), calendar);

    calendar->btn_prev_month = gtk_button_new_from_icon_name("pan-start-symbolic");
    gtk_button_set_can_shrink(GTK_BUTTON(calendar->btn_prev_month), TRUE);
    gtk_widget_set_tooltip_text(calendar->btn_prev_month, "Previous Month");
    g_signal_connect_swapped(calendar->btn_prev_month, "clicked", G_CALLBACK(callbk_prev_month), calendar);

    calendar->btn_prev_year = gtk_button_new_from_icon_name("pan-start-symbolic");
    gtk_button_set_can_shrink(GTK_BUTTON(calendar->btn_prev_year), TRUE);
    gtk_widget_set_tooltip_text(calendar->btn_prev_year, "Previous Year");
    g_signal_connect_swapped(calendar->btn_prev_year, "clicked", G_CALLBACK(callbk_prev_year), calendar);

    calendar->month_label = gtk_label_new("month");
    gtk_widget_set_hexpand(calendar->month_label, TRUE);
    gtk_widget_set_vexpand(calendar->month_label, FALSE);

    calendar->year_label = gtk_label_new("year");
    gtk_widget_set_hexpand(calendar->year_label, TRUE);
    gtk_widget_set_vexpand(calendar->year_label, FALSE);

    calendar->date_label = gtk_label_new("date");
    gtk_widget_set_hexpand(calendar->date_label, TRUE);
    gtk_widget_set_vexpand(calendar->date_label, FALSE);

    gtk_box_append(GTK_BOX(calendar->header), calendar->btn_prev_month);
    gtk_box_append(GTK_BOX(calendar->header), calendar->month_label);
    gtk_box_append(GTK_BOX(calendar->header), calendar->btn_next_month);
    gtk_box_append(GTK_BOX(calendar->header), calendar->date_label);
    gtk_box_append(GTK_BOX(calendar->header), calendar->btn_prev_year);
    gtk_box_append(GTK_BOX(calendar->header), calendar->year_label);
    gtk_box_append(GTK_BOX(calendar->header), calendar->btn_next_year);

    // GRID
    calendar->grid = gtk_grid_new();
    gtk_widget_set_hexpand(calendar->grid, TRUE);
    gtk_widget_set_vexpand(calendar->grid, TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(calendar->grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(calendar->grid), TRUE);

    const char *weekdays[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    for (int i = 0; i < 7; i++) {
        GtkWidget *label = gtk_label_new(weekdays[i]);
        gtk_grid_attach(GTK_GRID(calendar->grid), label, i, 0, 1, 1);
    }
    calendar->monday_label = gtk_grid_get_child_at(GTK_GRID(calendar->grid), 0, 0);
    calendar->tuesday_label = gtk_grid_get_child_at(GTK_GRID(calendar->grid), 1, 0);
    calendar->wednesday_label = gtk_grid_get_child_at(GTK_GRID(calendar->grid), 2, 0);
    calendar->thursday_label = gtk_grid_get_child_at(GTK_GRID(calendar->grid), 3, 0);
    calendar->friday_label = gtk_grid_get_child_at(GTK_GRID(calendar->grid), 4, 0);
    calendar->saturday_label = gtk_grid_get_child_at(GTK_GRID(calendar->grid), 5, 0);
    calendar->sunday_label = gtk_grid_get_child_at(GTK_GRID(calendar->grid), 6, 0);

    for (int y = 0; y < 6; y++)
    {
        for (int x = 0; x < 7; x++)
        {
            GtkWidget *label = gtk_label_new("");
            gtk_widget_set_hexpand(label, TRUE);
            gtk_widget_set_vexpand(label, TRUE);
            gtk_grid_attach(GTK_GRID(calendar->grid), label, x, y + 1, 1, 1);
            calendar->day_number_labels[y][x] = label;
        }
    }

    GDateTime *now = g_date_time_new_now_local();
    calendar->year = g_date_time_get_year(now);
    calendar->month = g_date_time_get_month(now);
    calendar->day = g_date_time_get_day_of_month(now);
    custom_calendar_select_day(calendar, calendar->day, calendar->month, calendar->year);
    g_date_time_unref(now);

    GtkLayoutManager *box_layout = gtk_widget_get_layout_manager(GTK_WIDGET(calendar));
    gtk_orientable_set_orientation(GTK_ORIENTABLE(box_layout), GTK_ORIENTATION_VERTICAL);
    gtk_box_layout_set_spacing(GTK_BOX_LAYOUT(box_layout), 2);
    gtk_widget_set_parent(calendar->header, GTK_WIDGET(calendar));
    gtk_widget_set_parent(calendar->grid, GTK_WIDGET(calendar));
}


/**
 * @brief Gets the current day.
 * @param calendar The CustomCalendar instance.
 * @return The current day of the month.
 */
int custom_calendar_get_day(CustomCalendar *calendar)
{
    return calendar->day;
}

/**
 * @brief Gets the current month.
 * @param calendar The CustomCalendar instance.
 * @return The current month (1-12).
 */
int custom_calendar_get_month(CustomCalendar *calendar)
{
    return calendar->month;
}

/**
 * @brief Gets the current year.
 * @param calendar The CustomCalendar instance.
 * @return The current year.
 */
int custom_calendar_get_year(CustomCalendar *calendar)
{
    return calendar->year;
}

/**
 * @brief Updates the date labels in the header.
 * @param calendar The CustomCalendar instance.
 */
static void update_date_labels(CustomCalendar *calendar)
{
    char* weekday_str = get_day_of_week(calendar->day, calendar->month, calendar->year);
    char* date_str = g_strdup_printf(" %s %d %s %d",
                                     weekday_str,
                                     calendar->day,
                                     monthname[calendar->month - 1],
                                     calendar->year);

    PangoAttrList *bold_attr = pango_attr_list_new();
    pango_attr_list_insert(bold_attr, pango_attr_weight_new(PANGO_WEIGHT_BOLD));
    gtk_label_set_attributes(GTK_LABEL(calendar->date_label), bold_attr);
    gtk_label_set_label(GTK_LABEL(calendar->date_label), date_str);
    pango_attr_list_unref(bold_attr);

    gtk_label_set_label(GTK_LABEL(calendar->month_label), monthname[calendar->month - 1]);
    char* year_str = g_strdup_printf("%d", calendar->year);
    gtk_label_set_label(GTK_LABEL(calendar->year_label), year_str);

    g_free(weekday_str);
    g_free(date_str);
    g_free(year_str);
}

/**
 * @brief Updates the day grid with correct day numbers, formatting, and tooltips.
 * @param calendar The CustomCalendar instance.
 */
static void update_day_grid(CustomCalendar *calendar)
{
    GDate* today_date = g_date_new();
    g_date_set_time_t(today_date, time(NULL));
    int today_day = g_date_get_day(today_date);
    int today_month = g_date_get_month(today_date);
    int today_year = g_date_get_year(today_date);
    g_date_free(today_date);

    int days_in_month = g_date_get_days_in_month(calendar->month, calendar->year);
    int week_start = 1; // start week on a Monday
    int remainder = (first_day_of_month(calendar->month, calendar->year) - week_start + 7) % 7;
    int aday = 1 - remainder;

    for (int y = 0; y < 6; y++) {
        for (int x = 0; x < 7; x++) {
            GtkWidget *label = calendar->day_number_labels[y][x];
            gtk_label_set_label(GTK_LABEL(label), "");
            gtk_label_set_use_markup(GTK_LABEL(label), TRUE);
            gtk_widget_remove_css_class(label, "today");
            gtk_widget_remove_css_class(label, "event");
            gtk_widget_remove_css_class(label, "none-month-day");
            gtk_widget_add_css_class(label, "calframe");

            // Fix: Populate calendar->days for all grid cells
            calendar->days[y][x] = aday;

            if (aday > 0 && aday <= days_in_month) {
                char* day_num_str = NULL;
                if (aday == today_day && calendar->month == today_month && calendar->year == today_year) {
                    gtk_widget_add_css_class(label, "today");
                    day_num_str = g_strdup_printf("<u><b>%d</b></u>", aday);
                } else if (calendar->marked_day[aday]) {
                    gtk_widget_add_css_class(label, "event");
                    day_num_str = g_strdup_printf("<i><b>%d</b></i><b>*</b>", aday);
                } else {
                    day_num_str = g_strdup_printf("%d", aday);
                }

                if (calendar->show_tooltips) {
                    gtk_widget_set_tooltip_text(label, calendar->tooltip_array[aday]);
                } else {
                    gtk_widget_set_tooltip_text(label, NULL);
                }
                gtk_label_set_label(GTK_LABEL(label), day_num_str);
                g_free(day_num_str);
            } else {
                gtk_widget_add_css_class(label, "none-month-day");
                char* label_str = NULL;
                if (aday <= 0) {
                    int prev_month = calendar->month - 1;
                    int prev_year = calendar->year;
                    if (prev_month < 1) { prev_month = 12; prev_year--; }
                    int days_in_prev_month = g_date_get_days_in_month(prev_month, prev_year);
                    int prev_month_day = days_in_prev_month + aday;
                    label_str = g_strdup_printf("<i>%d</i>", prev_month_day);
                } else {
                    int next_month_day = aday - days_in_month;
                    label_str = g_strdup_printf("<i>%d</i>", next_month_day);
                }
                gtk_label_set_label(GTK_LABEL(label), label_str);
                g_free(label_str);
            }
            aday++;
        }
    }
}

/**
 * @brief Sets up the initial CSS providers for styling.
 * @param calendar The CustomCalendar instance.
 */
static void setup_css_providers(CustomCalendar *calendar)
{
    gchar* today_provider_str = g_strdup_printf("label.today {background-image: none; background-color: %s;}", calendar->today_colour);
    calendar->provider_today = gtk_css_provider_new();
    gtk_css_provider_load_from_string(calendar->provider_today, today_provider_str);
    gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(calendar->provider_today), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_free(today_provider_str);

    gchar* event_provider_str = g_strdup_printf("label.event {background-image: none; background-color: %s;}", calendar->event_colour);
    calendar->provider_event = gtk_css_provider_new();
    gtk_css_provider_load_from_string(calendar->provider_event, event_provider_str);
    gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(calendar->provider_event), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_free(event_provider_str);

    const gchar* none_month_day_str = "label.none-month-day{background-image: none; font-weight: 100; opacity: 0.6;}";
    calendar->provider_none_month_day = gtk_css_provider_new();
    gtk_css_provider_load_from_string(calendar->provider_none_month_day, none_month_day_str);
    gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(calendar->provider_none_month_day), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    const gchar* frame_str = "label.calframe{background-image: none; border: 1px solid lightgrey;}";
    calendar->provider_frame = gtk_css_provider_new();
    gtk_css_provider_load_from_string(calendar->provider_frame, frame_str);
    gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(calendar->provider_frame), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

/**
 * @brief Updates the CSS providers with new color strings.
 * @param calendar The CustomCalendar instance.
 */
static void update_css_providers(CustomCalendar *calendar)
{
    gchar* today_provider_str = g_strdup_printf("label.today {background-image: none; background-color: %s;}", calendar->today_colour);
    gtk_css_provider_load_from_string(calendar->provider_today, today_provider_str);
    g_free(today_provider_str);

    gchar* event_provider_str = g_strdup_printf("label.event {background-image: none; background-color: %s;}", calendar->event_colour);
    gtk_css_provider_load_from_string(calendar->provider_event, event_provider_str);
    g_free(event_provider_str);

    // After updating the providers, force a redraw
    custom_calendar_update(calendar);
}

/**
 * @brief Selects a new day, month, and year and updates the calendar view.
 * @param calendar The CustomCalendar instance.
 * @param dday The day to select.
 * @param month The month to select.
 * @param year The year to select.
 */
void custom_calendar_select_day(CustomCalendar *calendar, guint dday, guint month, guint year)
{
    update_date_labels(calendar);
    update_day_grid(calendar);
}

/**
 * @brief Jumps to a specific date.
 * @param calendar The CustomCalendar instance.
 * @param day The day to go to.
 * @param month The month to go to.
 * @param year The year to go to.
 */
void custom_calendar_goto_dmy(CustomCalendar *calendar, int day, int month, int year)
{
    calendar->year = year;
    calendar->month = month;
    calendar->day = day;
    custom_calendar_select_day(calendar, calendar->day, calendar->month, calendar->year);
}

/**
 * @brief Jumps to today's date.
 * @param calendar The CustomCalendar instance.
 */
void custom_calendar_goto_today(CustomCalendar *calendar)
{
    GDateTime *today = g_date_time_new_now_local();
    calendar->year = g_date_time_get_year(today);
    calendar->month = g_date_time_get_month(today);
    calendar->day = g_date_time_get_day_of_month(today);
    custom_calendar_select_day(calendar, calendar->day, calendar->month, calendar->year);
    g_date_time_unref(today);
}

/**
 * @brief Callback for the next month button.
 * @param calendar The CustomCalendar instance.
 */
void callbk_next_month(CustomCalendar *calendar)
{
    calendar->month = calendar->month + 1;
    calendar->day = 1;
    if (calendar->month >= 13)
    {
        calendar->month = 1;
        calendar->year = calendar->year + 1;
        calendar->day = 1;
    }
    custom_calendar_select_day(calendar, calendar->day, calendar->month, calendar->year);
    g_signal_emit(calendar, custom_calendar_signals[NEXT_MONTH_SIGNAL], 0);
}

/**
 * @brief Callback for the previous month button.
 * @param calendar The CustomCalendar instance.
 */
void callbk_prev_month(CustomCalendar *calendar)
{
    calendar->month = calendar->month - 1;
    calendar->day = 1;
    if (calendar->month < 1)
    {
        calendar->month = 12;
        calendar->year = calendar->year - 1;
        calendar->day = 1;
    }
    custom_calendar_select_day(calendar, calendar->day, calendar->month, calendar->year);
    g_signal_emit(calendar, custom_calendar_signals[PREV_MONTH_SIGNAL], 0);
}

/**
 * @brief Callback for the next year button.
 * @param calendar The CustomCalendar instance.
 */
void callbk_next_year(CustomCalendar *calendar)
{
    calendar->year = calendar->year + 1;
    calendar->month = calendar->month;
    calendar->day = 1;
    custom_calendar_select_day(calendar, calendar->day, calendar->month, calendar->year);
    g_signal_emit(calendar, custom_calendar_signals[NEXT_YEAR_SIGNAL], 0);
}

/**
 * @brief Callback for the previous year button.
 * @param calendar The CustomCalendar instance.
 */
void callbk_prev_year(CustomCalendar *calendar)
{
    calendar->year = calendar->year - 1;
    calendar->month = calendar->month;
    calendar->day = 1;
    custom_calendar_select_day(calendar, calendar->day, calendar->month, calendar->year);
    g_signal_emit(calendar, custom_calendar_signals[PREV_YEAR_SIGNAL], 0);
}

/**
 * @brief Handles button press events on the calendar grid.
 * @param gesture The GtkGestureClick object.
 * @param n_press The number of presses.
 * @param x The x-coordinate of the press.
 * @param y The y-coordinate of the press.
 * @param user_data A pointer to the CustomCalendar instance.
 */
void custom_calendar_button_press(GtkGestureClick *gesture, int n_press, double x, double y, gpointer user_data)
{
    CustomCalendar *calendar = user_data;
    GtkWidget *widget = GTK_WIDGET(calendar);
    GtkWidget *label = gtk_widget_pick(widget, x, y, GTK_PICK_DEFAULT);

    int row_number = -1, col_number = -1;
    int number_of_columns = 7;
    int number_of_rows = 6;

    for (int iy = 0; iy < number_of_rows; iy++) {
        for (int ix = 0; ix < number_of_columns; ix++) {
            if (label == calendar->day_number_labels[iy][ix]){
                row_number = iy;
                col_number = ix;
                break;
            }
        }
        if (row_number != -1) break;
    }

    if (row_number == -1 || col_number == -1) {
        return;
    }

    int day_clicked = calendar->days[row_number][col_number];
    int days_in_month = g_date_get_days_in_month(calendar->month, calendar->year);

    if (day_clicked <= 0) {
        int prev_month = calendar->month - 1;
        int prev_year = calendar->year;
        if (prev_month < 1) {
            prev_month = 12;
            prev_year--;
        }
        int days_in_prev_month = g_date_get_days_in_month(prev_month, prev_year);
        int day_prev_month = days_in_prev_month + day_clicked;
        
        calendar->day = day_prev_month;
        calendar->month = prev_month;
        calendar->year = prev_year;
    } else if (day_clicked > days_in_month) {
        int next_month = calendar->month + 1;
        int next_year = calendar->year;
        if (next_month >= 13) {
            next_month = 1;
            next_year++;
        }
        int day_next_month = day_clicked - days_in_month;
        
        calendar->day = day_next_month;
        calendar->month = next_month;
        calendar->year = next_year;
    } else {
        calendar->day = day_clicked;
    }

    if (!gtk_widget_has_focus(widget)) {
        gtk_widget_grab_focus(widget);
    }

    custom_calendar_select_day(calendar, calendar->day, calendar->month, calendar->year);
    g_signal_emit(calendar, custom_calendar_signals[DAY_SELECTED_SIGNAL], 0);
}

/**
 * @brief Forces the calendar to update and redraw itself.
 * @param calendar The CustomCalendar instance.
 */
void custom_calendar_update(CustomCalendar *calendar)
{
    g_return_if_fail(CUSTOM_IS_CALENDAR(calendar));
    custom_calendar_select_day(calendar, calendar->day, calendar->month, calendar->year);
}
