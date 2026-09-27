/* customcalendar.c
 *
 * Copyright 2026 Alan Crispin <crispinalan@gmail.com>
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
// Author: Alan Crispin
// Date: July 2025 (updated Sept 2026)
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
 * @brief The main structure definition for the CustomCalendar widget instance.
 * 
 * This structure maintains the state data, child layout hierarchy elements, 
 * day arrays, color configs, and active CSS styling providers for the calendar instance.
 */
struct _CustomCalendar
{
    GtkWidget parent_instance;              /**< The parent GtkWidget instance layout. */

    /* Sub-Layout Elements: Header Navigation */
    GtkWidget *header;                      /**< Box container layout mapping the top navigation bar. */
    GtkWidget *btn_next_month;              /**< Iconic button navigation tracking forward one month page. */
    GtkWidget *month_label;                 /**< Context label text displaying the active written month. */
    GtkWidget *btn_prev_month;              /**< Iconic button navigation tracking backward one month page. */
    GtkWidget *date_label;                  /**< Context label tracking auxiliary numeric system date markers. */
    GtkWidget *btn_next_year;               /**< Iconic button navigation tracking forward one calendar year. */
    GtkWidget *year_label;                  /**< Context label text displaying the active numeric four-digit year. */
    GtkWidget *btn_prev_year;               /**< Iconic button navigation tracking backward one calendar year. */

    /* Sub-Layout Elements: Calendar Grid */
    GtkWidget *grid;                        /**< Core GtkGrid layout structuring the daily matrix fields. */
    GtkWidget *monday_label;                /**< Weekday label mapping pointer tracking Monday header columns. */
    GtkWidget *tuesday_label;               /**< Weekday label mapping pointer tracking Tuesday header columns. */
    GtkWidget *wednesday_label;             /**< Weekday label mapping pointer tracking Wednesday header columns. */
    GtkWidget *thursday_label;              /**< Weekday label mapping pointer tracking Thursday header columns. */
    GtkWidget *friday_label;                /**< Weekday label mapping pointer tracking Friday header columns. */
    GtkWidget *saturday_label;              /**< Weekday label mapping pointer tracking Saturday header columns. */
    GtkWidget *sunday_label;                /**< Weekday label mapping pointer tracking Sunday header columns. */
    GtkWidget *day_number_labels[6][7];    /**< Matrix map containing label pointers displaying individual date numeric keys. */

    /* Chronological Processing Tracking State */
    GDateTime *date;                        /**< Core unreffable date tracking context window instance. */
    int day;                                /**< Active target numerical calendar selected day integer. */
    int month;                              /**< Active target numerical calendar selected month integer. */
    int year;                               /**< Active target numerical calendar selected year integer. */
    int day_month[6][7];                    /**< Matrix mapping showing chronological day associations across layout grids. */
    int days[6][7];                         /**< Matrix mapping containing calculated month day integers (allows negatives/overflows for padding). */

    /* Internal Data Matrix Maps & Array States */
    gchar** tooltip_array;                  /**< Owned heap array of allocated strings (`g_new`/`g_free`) storing tooltip popups for days 1-31. */
    int num_marked_days;                    /**< Counter keeping track of the total number of standard active calendar event markers. */
    int marked_day[32];                     /**< Boolean integer flags array identifying indices tracking active standard events. */
    int num_notable_days;                   /**< Counter keeping track of the total number of active holiday calendar notable markers. */
    int notable_day[32];                    /**< Boolean integer flags array identifying indices tracking active holiday markers. */

    /* Custom Configurable Styling Properties (Owned Heap Memory Strings) */
    const gchar* today_colour;              /**< Target string property spec holding CSS markup for the active current date box. */
    const gchar* event_colour;              /**< Target string property spec holding CSS markup for structural event boxes. */
    const gchar* notable_colour;            /**< Target string property spec holding CSS markup for identifying calendar holidays. */
    gboolean show_tooltips;                 /**< Flag state identifying whether hover popup operations are visible. */

    /* Dynamic CSS Application Layout Providers */
    GtkCssProvider *provider_today;         /**< Reference tracked style stylesheet context map for current date highlights. */
    GtkCssProvider *provider_event;         /**< Reference tracked style stylesheet context map for active standard events. */
    GtkCssProvider *provider_notable;       /**< Reference tracked style stylesheet context map for active holiday items. */
    GtkCssProvider *provider_none_month_day;/**< Reference tracked style stylesheet context map dimming non-active padding days. */
    GtkCssProvider *provider_frame;         /**< Reference tracked style stylesheet context map tracing cell perimeter borders. */

    /* Heap Text Suffix Property String */
    gchar *notable_date_suffix;             /**< Dynamic owned holiday suffix string appended to text labels (e.g., "Holiday"). */
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
    PROP_NOTABLECOLOUR,
    PROP_SHOWTOOLTIPS,
    LAST_PROP
};

static GParamSpec *properties[LAST_PROP];

/**
 * @brief Sets the color for today's date in the calendar.
 * @param self The CustomCalendar instance.
 * @param colour_str The color string (e.g., "rgb(221,160,221)").
 */

void custom_calendar_set_today_colour (CustomCalendar *self, const gchar* colour_str)
{
    g_return_if_fail(CUSTOM_IS_CALENDAR(self));
    
    if (g_strcmp0(self->today_colour, colour_str) != 0) {
        g_free((gchar*)self->today_colour);
        // Duplicate safely here, but ensure the GObject property installation matches
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
void custom_calendar_set_event_colour (CustomCalendar *self, const gchar* colourname)
{
    g_return_if_fail(CUSTOM_IS_CALENDAR(self));
    
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

void custom_calendar_set_notable_colour (CustomCalendar *self, const gchar* colourname)
{
    g_return_if_fail(CUSTOM_IS_CALENDAR(self));
    
    if (g_strcmp0(self->notable_colour, colourname) != 0) {
        g_free((gchar*)self->notable_colour);
        self->notable_colour = g_strdup(colourname);
        update_css_providers(self);
    }
}
/**
 * @brief Gets the color for event days.
 * @param self The CustomCalendar instance.
 * @return The color string.
 */
const gchar* custom_calendar_get_notable_colour(CustomCalendar *self){
    return self->notable_colour;
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
 * @brief Sets a property on the CustomCalendar instance.
 * 
 * This function is an internal GObject override callback. It intercepts requests 
 * from g_object_set() or UI builder declarations, parses the generic GValue into 
 * the appropriate raw C type, and routes it to the matching public widget setter method.
 *
 * @param object  The generic GObject instance (cast internally to CustomCalendar).
 * @param prop_id The numeric identifier assigned to the property in class_init.
 * @param value   The generic GValue containing the input data wrapper.
 * @param pspec   The metadata parameter specification describing the property.
 * 
 * @return void
 */
static void custom_calendar_set_property(GObject *object,
                                         guint prop_id,
                                         const GValue *value,
                                         GParamSpec *pspec)
{
    CustomCalendar *self = CUSTOM_CALENDAR(object);

    switch (prop_id)
    {
        case PROP_TODAYCOLOUR:
            custom_calendar_set_today_colour(self, g_value_get_string(value));
            break;
        case PROP_EVENTCOLOUR:
            custom_calendar_set_event_colour(self, g_value_get_string(value));
            break;
        case PROP_NOTABLECOLOUR:
            custom_calendar_set_notable_colour(self, g_value_get_string(value));
            break;
        case PROP_SHOWTOOLTIPS:
            custom_calendar_set_show_tooltips(self, g_value_get_boolean(value));
            break;

        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
            break;
    }
}

/**
 * @brief Gets a property value from the CustomCalendar instance.
 * 
 * This function is an internal GObject override callback. It intercepts requests 
 * from g_object_get(), fetches the current value via the public widget getter method, 
 * and boxes it safely inside the provided GValue container.
 *
 * @param object  The generic GObject instance (cast internally to CustomCalendar).
 * @param prop_id The numeric identifier assigned to the property in class_init.
 * @param value   The destination GValue container where the output will be packed.
 * @param pspec   The metadata parameter specification describing the property.
 * 
 * @return void
 */
static void custom_calendar_get_property(GObject *object,
                                         guint prop_id,
                                         GValue *value,
                                         GParamSpec *pspec)
{
    CustomCalendar *self = CUSTOM_CALENDAR(object);

    switch (prop_id)
    {
        case PROP_TODAYCOLOUR:
            g_value_set_string(value, custom_calendar_get_today_colour(self));
            break;
        case PROP_EVENTCOLOUR:
            g_value_set_string(value, custom_calendar_get_event_colour(self));
            break;
        case PROP_NOTABLECOLOUR:
            g_value_set_string(value, custom_calendar_get_notable_colour(self));
            break;
        case PROP_SHOWTOOLTIPS:
            g_value_set_boolean(value, custom_calendar_get_show_tooltips(self));
            break;
        
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
            break;
    }
}

/**
 * @brief Releases object references and unparents child widgets.
 * 
 * This method may be called multiple times during the object's destruction phase.
 * It is responsible for safely breaking references to other GObjects (such as style providers),
 * clearing managed time instances, and breaking the widget tree mapping by unparenting 
 * child layouts.
 *
 * @param object The GObject instance undergoing resource disposal.
 * 
 * @return void
 */
static void custom_calendar_dispose(GObject *object)
{
    CustomCalendar *calendar = CUSTOM_CALENDAR(object);

    // 1. Disconnect style providers from the global display surface context
    GdkDisplay *display = gdk_display_get_default();
    if (display) {
        if (calendar->provider_today) {
            gtk_style_context_remove_provider_for_display(display, GTK_STYLE_PROVIDER(calendar->provider_today));
        }
        if (calendar->provider_event) {
            gtk_style_context_remove_provider_for_display(display, GTK_STYLE_PROVIDER(calendar->provider_event));
        }
        if (calendar->provider_notable) {
            gtk_style_context_remove_provider_for_display(display, GTK_STYLE_PROVIDER(calendar->provider_notable));
        }
        if (calendar->provider_none_month_day) {
            gtk_style_context_remove_provider_for_display(display, GTK_STYLE_PROVIDER(calendar->provider_none_month_day));
        }
        if (calendar->provider_frame) {
            gtk_style_context_remove_provider_for_display(display, GTK_STYLE_PROVIDER(calendar->provider_frame));
        }
    }

    // 2. Clear referenced objects safely (handles multiple invocations gracefully)
    g_clear_pointer(&calendar->date, g_date_time_unref);
    g_clear_pointer(&calendar->provider_today, g_object_unref);
    g_clear_pointer(&calendar->provider_event, g_object_unref);
    g_clear_pointer(&calendar->provider_notable, g_object_unref);
    g_clear_pointer(&calendar->provider_none_month_day, g_object_unref);
    g_clear_pointer(&calendar->provider_frame, g_object_unref);

    // 3. Unparent child layout widgets safely to break widget tree hierarchy
    g_clear_pointer(&calendar->header, gtk_widget_unparent);
    g_clear_pointer(&calendar->grid, gtk_widget_unparent);
    
    // Always chain up to the parent class's dispose handler
    G_OBJECT_CLASS(custom_calendar_parent_class)->dispose(object);
}

/**
 * @brief Performs final heap memory deallocation before object destruction.
 * 
 * This method is guaranteed to run exactly once at the end of the lifecycle.
 * It tears down raw data structures, free loops, and dynamic heap properties
 * that cannot be safely processed inside a multi-pass dispose environment.
 *
 * @param object The GObject instance undergoing terminal finalisation.
 * 
 * @return void
 */
static void custom_calendar_finalize(GObject *object)
{
    CustomCalendar *calendar = CUSTOM_CALENDAR(object);

    // 1. Free internal raw heap properties
    g_free((gchar *)calendar->today_colour);
    g_free((gchar *)calendar->event_colour);
    g_free((gchar *)calendar->notable_colour);
    g_free((gchar *)calendar->notable_date_suffix);

    // 2. Free internal tooltip data matrices safely
    if (calendar->tooltip_array) {
        for (int i = 0; i < 32; i++) {
            g_free(calendar->tooltip_array[i]);
        }
        g_free(calendar->tooltip_array);
        calendar->tooltip_array = NULL;
    }

    // Always chain up to the parent class's finalize handler
    G_OBJECT_CLASS(custom_calendar_parent_class)->finalize(object);
}

/**
 * @brief Class initialization function for the CustomCalendar widget.
 * 
 * Configures the class-wide structures, hooks up base object lifecycle handlers,
 * registers custom widget properties, and creates application signals.
 * 
 * ### Overridden Methods
 * - `dispose`: Releases reference-counted objects and detaches style providers.
 * - `finalize`: Frees internal raw heap buffers and strings.
 * - `set_property` / `get_property`: Accessor interfaces for GObject properties.
 * 
 * ### Registered Properties
 * - `todaycolour` (string): CSS background color string for the active date box.
 * - `eventcolour` (string): CSS background color string highlighting standard event rows.
 * - `notablecolour` (string): CSS color string dedicated to identifying calendar holiday markers.
 * - `showtooltips` (boolean): Flag indicating whether hovering elements spawns data info text.
 * 
 * ### Registered Signals
 * - `day-selected`: Dispatched when a day block is activated by a pointer action.
 * - `next-month` / `prev-month`: Emitted when swapping chronological boundaries horizontally.
 * - `next-year` / `prev-year`: Emitted when updating yearly calendar intervals.
 *
 * @param klass A pointer to the CustomCalendarClass definition layout.
 * 
 * @return void
 */
static void custom_calendar_class_init(CustomCalendarClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(klass);

    // 1. Map core lifecycle virtual method pointers
    object_class->dispose = custom_calendar_dispose;
    object_class->finalize = custom_calendar_finalize;
    object_class->set_property = custom_calendar_set_property;
    object_class->get_property = custom_calendar_get_property;

    // 2. Define custom properties
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
    
    properties[PROP_NOTABLECOLOUR] =
        g_param_spec_string("notablecolour",
                            "notablecolour",
                            "colour string for notable date",
                            "rgb(211,21,21)",
                            (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

    properties[PROP_SHOWTOOLTIPS] =
        g_param_spec_boolean("showtooltips",
                             "showtooltips",
                             "sets if calendar has tooltips",
                             TRUE,
                             G_PARAM_READWRITE);

    g_object_class_install_properties(object_class, LAST_PROP, properties);

    // 3. Register layout runtime and notification signals
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

    // 4. Declare standard layout manager for custom positioning loops
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
        // Safe check: Free the previous text memory block if one was active
        if (calendar->tooltip_array[i] != NULL) {
            g_free(calendar->tooltip_array[i]);
        }
        // Initialize to NULL. No heap allocations are wasted on empty cells!
        calendar->tooltip_array[i] = NULL;
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
        
        // If old_tooltip_str is NULL, there is no text yet. Perform a clean copy!
        if (old_tooltip_str == NULL) {
            calendar->tooltip_array[day] = g_strdup(tooltip_str);
        } else {
            // Only concatenate with a newline if previous event text already exists
            calendar->tooltip_array[day] = g_strconcat(old_tooltip_str, "\n", tooltip_str, NULL);
            g_free(old_tooltip_str); // Free the intermediate step
        }
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
 * @brief Resets all notable days.
 * @param calendar The CustomCalendar instance.
 */
void custom_calendar_reset_notables(CustomCalendar *calendar)
{
    g_return_if_fail(CUSTOM_IS_CALENDAR(calendar));

    for (int i = 0; i < 32; i++){
        calendar->notable_day[i] = FALSE;
    }
    calendar->num_notable_days = 0;
}
/**
 * @brief Marks a specific day as being notable.
 * @param calendar The CustomCalendar instance.
 * @param day The day number (1-31).
 */
void custom_calendar_mark_notable(CustomCalendar *calendar, guint day)
{
    g_return_if_fail(CUSTOM_IS_CALENDAR(calendar));

    if (day >= 1 && day <= 31)
    {
        calendar->notable_day[day] = TRUE;
        calendar->num_notable_days++;
    }
}
/**
 * @brief Unmarks a specific notable day.
 * @param calendar The CustomCalendar instance.
 * @param day The day number (1-31).
 */
void custom_calendar_unmark_notable(CustomCalendar *calendar, guint day)
{
    g_return_if_fail(CUSTOM_IS_CALENDAR(calendar));

    if (day >= 1 && day <= 31)
    {
        calendar->notable_day[day] = FALSE;
        calendar->num_notable_days--;
    }
}
/**
 * @brief Checks if a day is notable.
 * @param calendar The CustomCalendar instance.
 * @param day The day number (1-31).
 * @return TRUE if the day is notable, FALSE otherwise.
 */
gboolean custom_calendar_get_day_is_notable(CustomCalendar *calendar, guint day)
{
    if (day >= 1 && day <= 31)
        return calendar->notable_day[day];
    return FALSE;
}

/**
 * @brief Determines the day of the week for a given date.
 * @param day The day of the month.
 * @param month The month (1-12).
 * @param year The year.
 * @return A static read-only string literal pointer. DO NOT FREE THIS RESULT!
 */
static const char* get_day_of_week(int day, int month, int year)
{
    const char* weekday_str = "unknown";
    GDate* day_date = g_date_new_dmy(day, month, year);
    
    if (day_date) {
        GDateWeekday weekday = g_date_get_weekday(day_date);
        switch(weekday)
        {
            case G_DATE_MONDAY:    weekday_str = "Monday";    break;
            case G_DATE_TUESDAY:   weekday_str = "Tuesday";   break;
            case G_DATE_WEDNESDAY: weekday_str = "Wednesday"; break;
            case G_DATE_THURSDAY:  weekday_str = "Thursday";  break;
            case G_DATE_FRIDAY:    weekday_str = "Friday";    break;
            case G_DATE_SATURDAY:  weekday_str = "Saturday";  break;
            case G_DATE_SUNDAY:    weekday_str = "Sunday";    break;
            default: break;
        }
        g_date_free(day_date);
    }
    // Optimized: Return the raw static literal pointer directly (no g_strdup heap allocations)
    return weekday_str; 
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
/**
 * @brief Instance initialization function for a CustomCalendar object.
 * 
 * Sets up individual instance state data properties, defaults colors on the heap, 
 * binds standard single-click controller gestures, builds internal structural layout trees,
 * and sets the target focus map.
 * 
 * This function functions closely to a standard object constructor in C++ or Qt frameworks.
 *
 * @param calendar A pointer to the newly allocated CustomCalendar instance.
 * 
 * @return void
 */
static void custom_calendar_init(CustomCalendar *calendar)
{
    GtkWidget *widget = GTK_WIDGET(calendar);
    
    // 1. Initialise core date variables and internal string placeholders
    calendar->notable_date_suffix = NULL;
    calendar->day = 0;
    calendar->month = 0;
    calendar->year = 0;
    calendar->show_tooltips = TRUE;
    
    // 2. Allocate the 32-element pointer array tracking custom hover labels
    calendar->tooltip_array = g_new(gchar*, 32);
    for (int i = 0; i < 32; i++) {
        calendar->tooltip_array[i] = NULL;
    }
    custom_calendar_initialise_tooltip_array(calendar);
    
    // 3. Duplicate fallback default color formatting specs on the heap
    calendar->today_colour = g_strdup("rgb(221,160,221)");   // plum
    calendar->event_colour = g_strdup("rgb(211,211,211)");   // light grey
    calendar->notable_colour = g_strdup("rgb(211,21,21)");   // redish
    setup_css_providers(calendar);

    // 4. Configure widget interaction focus flags
    gtk_widget_set_focusable(widget, TRUE);

    // 5. Establish gesture tracking handlers for processing click events
    GtkGesture *gesture = gtk_gesture_click_new();
    g_signal_connect(gesture, "pressed", G_CALLBACK(custom_calendar_button_press), calendar);
    gtk_widget_add_controller(widget, GTK_EVENT_CONTROLLER(gesture));

    // 6. Build the layout navigation sub-header box layout map
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

    // Assemble the sub-components within the layout header container box
    gtk_box_append(GTK_BOX(calendar->header), calendar->btn_prev_month);
    gtk_box_append(GTK_BOX(calendar->header), calendar->month_label);
    gtk_box_append(GTK_BOX(calendar->header), calendar->btn_next_month);
    gtk_box_append(GTK_BOX(calendar->header), calendar->date_label);
    gtk_box_append(GTK_BOX(calendar->header), calendar->btn_prev_year);
    gtk_box_append(GTK_BOX(calendar->header), calendar->year_label);
    gtk_box_append(GTK_BOX(calendar->header), calendar->btn_next_year);

    // 7. Initialise the core date-grid mapping matrix
    calendar->grid = gtk_grid_new();
    gtk_widget_set_hexpand(calendar->grid, TRUE);
    gtk_widget_set_vexpand(calendar->grid, TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(calendar->grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(calendar->grid), TRUE);

    // Populate day of the week header markers (Row 0)
    const char *weekdays[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    for (int i = 0; i < 7; i++) {
        GtkWidget *label = gtk_label_new(weekdays[i]);
        gtk_grid_attach(GTK_GRID(calendar->grid), label, i, 0, 1, 1);
    }

    // Populate the 6x7 matrix of date cell string widgets (Rows 1 to 6)
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

    // 8. Auto-populate configuration constraints using local timezone context
    GDateTime *now = g_date_time_new_now_local();
    calendar->year = g_date_time_get_year(now);
    calendar->month = g_date_time_get_month(now);
    calendar->day = g_date_time_get_day_of_month(now);
    custom_calendar_select_day(calendar, calendar->day, calendar->month, calendar->year);
    g_date_time_unref(now);

    // 9. Attach children to parent widget layout tree context explicitly
    GtkLayoutManager *box_layout = gtk_widget_get_layout_manager(widget);
    gtk_orientable_set_orientation(GTK_ORIENTABLE(box_layout), GTK_ORIENTATION_VERTICAL);
    gtk_box_layout_set_spacing(GTK_BOX_LAYOUT(box_layout), 2);
    
    gtk_widget_set_parent(calendar->header, widget);
    gtk_widget_set_parent(calendar->grid, widget);
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
    const char* weekday_str = get_day_of_week(calendar->day, calendar->month, calendar->year);
    char* date_str = NULL;
    
    // If a notable date suffix is active, append it to the end of the text label
    if (calendar->notable_date_suffix && strlen(calendar->notable_date_suffix) > 0) {
        date_str = g_strdup_printf(" %s %d %s %d - %s",
                                   weekday_str, calendar->day, monthname[calendar->month - 1],
                                   calendar->year, calendar->notable_date_suffix);
    } else {
        date_str = g_strdup_printf(" %s %d %s %d",
                                   weekday_str, calendar->day, monthname[calendar->month - 1],
                                   calendar->year);
    }
    
    PangoAttrList *bold_attr = pango_attr_list_new();
    pango_attr_list_insert(bold_attr, pango_attr_weight_new(PANGO_WEIGHT_BOLD));
    gtk_label_set_attributes(GTK_LABEL(calendar->date_label), bold_attr);
    gtk_label_set_label(GTK_LABEL(calendar->date_label), date_str);
    pango_attr_list_unref(bold_attr);
    
    gtk_label_set_label(GTK_LABEL(calendar->month_label), monthname[calendar->month - 1]);
    
    char* year_str = g_strdup_printf("%d", calendar->year);
    gtk_label_set_label(GTK_LABEL(calendar->year_label), year_str);
    
    g_free(date_str);
    g_free(year_str);
}
/**
 * @brief Sets or updates the suffix string displayed next to notable calendar dates.
 * 
 * This function updates the suffix string stored within the CustomCalendar instance.
 * It safely frees any previously allocated suffix, duplicates the new string if it 
 * is not NULL, and immediately triggers a visual refresh of the calendar labels 
 * to reflect the changes on the screen.
 *
 * @param calendar A pointer to the CustomCalendar instance. Must be a valid calendar object.
 * @param suffix   A null-terminated string representing the text suffix to apply (e.g., "st", "nd", "Holidays"), 
 *                 or NULL to clear the current suffix.
 * 
 * @return void
 */
void custom_calendar_set_notable_date_suffix(CustomCalendar *calendar, const char *suffix)
{
    g_return_if_fail(CUSTOM_IS_CALENDAR(calendar));
    
    // Safe memory balance replacement loop
    g_free(calendar->notable_date_suffix);
    calendar->notable_date_suffix = suffix ? g_strdup(suffix) : NULL;
    
    // Trigger an immediate labels refresh pass to paint the modifications on screen
    update_date_labels(calendar);
}

/**
 * @brief Regenerates and updates the calendar day grid with correct text, styles, and tooltips.
 * 
 * This core engine function handles drawing the daily calendar grid. It performs the following steps:
 * 1. Determines the current real-world date to match against the active page view.
 * 2. Clears previous CSS styling classes (`today`, `event`, `notable`, `none-month-day`) from cell label widgets.
 * 3. Calculates grid positioning offsets using a Monday-first layout configuration.
 * 4. Iterates over the 6x7 grid matrix to assign numerical text values.
 * 5. Appends text formatting strings and custom hover tooltips based on event states.
 * 6. Computes and renders dimmed text indicators for day boxes extending into the previous or next month.
 *
 * @param calendar A pointer to the active CustomCalendar instance.
 * 
 * @return void
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
            gtk_widget_remove_css_class(label, "notable");
            gtk_widget_remove_css_class(label, "none-month-day");
            gtk_widget_add_css_class(label, "calframe");

            // Populate calendar->days for all grid cells
            calendar->days[y][x] = aday;

            if (aday > 0 && aday <= days_in_month) {
                char* day_num_str = NULL;
                if (aday == today_day && calendar->month == today_month && calendar->year == today_year) {
                    gtk_widget_add_css_class(label, "today");
                    day_num_str = g_strdup_printf("<u><b>%d</b></u>", aday);                    
                } else if (calendar->marked_day[aday]) {
                    gtk_widget_add_css_class(label, "event");
                    day_num_str = g_strdup_printf("<i><b>%d</b></i><b>*</b>", aday);
                } else if (calendar->notable_day[aday]) {
                    gtk_widget_add_css_class(label, "notable"); 
                    day_num_str = g_strdup_printf("%d", aday);                                      
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
 * @brief Dynamic CSS stylesheet generation and runtime display attachment.
 * 
 * Compiles runtime string definitions for CSS rules utilizing the widget's configurable 
 * colour hex strings (`today_colour`, `event_colour`, `notable_colour`). The compiled 
 * style sheets are registered directly onto the global fallback display context loop.
 * 
 * ### Applied CSS State Selectors:
 * - `label.today`: Sets background highlights for the active current date box.
 * - `label.event`: Modifies rows containing valid user schedule payloads.
 * - `label.notable`: Colors visual anchors identifying marked holiday nodes.
 * - `label.none-month-day`: Dims calendar boxes extending into adjacent months.
 * - `label.calframe`: Generates basic border layout boundaries between cells.
 *
 * @param calendar A pointer to the target CustomCalendar instance to initialize.
 * 
 * @return void
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
        
    gchar* notable_provider_str = g_strdup_printf("label.notable {background-image: none; background-color: %s;}", calendar->notable_colour);
    calendar->provider_notable = gtk_css_provider_new();
    gtk_css_provider_load_from_string(calendar->provider_notable, notable_provider_str);
    gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(calendar->provider_notable), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_free(notable_provider_str);

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
 * @brief Updates the existing CSS providers with new colour strings dynamically.
 * 
 * This function handles changes to the widget's colour properties at runtime. 
 * Instead of allocating new provider handles, it reuses the pre-existing fields 
 * (`provider_today`, `provider_event`, and `provider_notable`) and hot-swaps their 
 * stylesheets using updated colour formatting values. 
 * 
 * Once the styles are loaded into the provider engine, it invokes an internal 
 * layout update request to force the widget to paint the new colours onto the display screen.
 *
 * @param calendar A pointer to the active CustomCalendar instance.
 * 
 * @return void
 */
static void update_css_providers(CustomCalendar *calendar)
{
    gchar* today_provider_str = g_strdup_printf("label.today {background-image: none; background-color: %s;}", calendar->today_colour);
    gtk_css_provider_load_from_string(calendar->provider_today, today_provider_str);
    g_free(today_provider_str);

    gchar* event_provider_str = g_strdup_printf("label.event {background-image: none; background-color: %s;}", calendar->event_colour);
    gtk_css_provider_load_from_string(calendar->provider_event, event_provider_str);
    g_free(event_provider_str);
    
    gchar* notable_provider_str = g_strdup_printf("label.notable {background-image: none; background-color: %s;}", calendar->notable_colour);
    gtk_css_provider_load_from_string(calendar->provider_notable, notable_provider_str);
    g_free(notable_provider_str);

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
 * @brief Coordinates pointer clicks on the calendar layout matrix to select days.
 * 
 * This callback intercepts coordinate click markers via a GtkGestureClick event controller. 
 * It utilizes the GTK4 layout picking API to locate which specific day label widget was clicked, 
 * queries its grid row/column mapping, and updates the object's active day, month, and year values.
 * 
 * If a user clicks a padded day belonging to the previous or next month page, the function 
 * dynamically adjusts the month and year boundaries before triggering selection redraws. 
 * Finally, it requests widget keyboard focus and broadcasts the `day-selected` signal.
 *
 * @param gesture  The gesture controller tracking pointer operations.
 * @param n_press  The click count multiplier (e.g., single vs double click).
 * @param x        The relative X coordinate pixel matching the cursor target location.
 * @param y        The relative Y coordinate pixel matching the cursor target location.
 * @param user_data A generic callback context pointer cast internally to CustomCalendar.
 * 
 * @return void
 */
void custom_calendar_button_press(GtkGestureClick *gesture, int n_press, double x, double y, gpointer user_data)
{
    CustomCalendar *calendar = user_data;
    GtkWidget *widget = GTK_WIDGET(calendar);
    
    // Query which widget child layer occupies this absolute layout coordinate boundary
    GtkWidget *label = gtk_widget_pick(widget, x, y, GTK_PICK_DEFAULT);

    int row_number = -1, col_number = -1;
    int number_of_columns = 7;
    int number_of_rows = 6;

    // Map the picked label widget pointer back to its internal coordinate indices
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

    // Abort early if the user clicked outside the target date label zones (e.g., padding/margins)
    if (row_number == -1 || col_number == -1) {
        return;
    }

    int day_clicked = calendar->days[row_number][col_number];
    int days_in_month = g_date_get_days_in_month(calendar->month, calendar->year);

    if (day_clicked <= 0) {
        // Case A: User clicked a trailing block tracking back to the previous month page view
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
        // Case B: User clicked a leading block extending into the upcoming month page view
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
        // Case C: Standard click fell within the limits of the current active month view
        calendar->day = day_clicked;
    }

    // Force focus onto the calendar widget to handle keyboard operations correctly
    if (!gtk_widget_has_focus(widget)) {
        gtk_widget_grab_focus(widget);
    }

    // Trigger visual state refreshes and notify the application lifecycle layer
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
