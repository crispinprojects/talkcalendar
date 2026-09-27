/* calendarevent.c
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
#include "calendarevent.h"

/**
 * @brief The main structure definition for the CalendarEvent object instance.
 * 
 * This object serves as a pure data model tracking all metadata associated with 
 * a single scheduled appointment or reminder item. Because it inherits from GObject 
 * directly, it handles no rendering logic but manages owned heap strings that must 
 * be cleanly freed on destruction.
 */
struct _CalendarEvent
{
    GObject parent_instance;    /**< The parent GObject instance layout structure. */
    
    /* Identification Mapping Keys */
    gint    eventid;            /**< Unique database primary key identifier for the event entry. */
    
    /* Textual Event Properties (Owned Heap Memory Strings) */
    gchar*  summary;            /**< Brief title string representing the event header. */
    gchar*  location;           /**< Optional physical address or venue description string. */
    gchar*  description;        /**< Long-form optional detailed notes text block string. */
    
    /* Chronological Structure Elements: Start Boundaries */
    gint    startyear;          /**< Four-digit starting calendar year integer. */
    gint    startmonth;         /**< Starting numeric month integer value (1-12). */
    gint    startday;           /**< Starting day of the month integer value (1-31). */
    gint    starthour;          /**< Starting hour component matching a 24-hour cycle (0-23). */
    gint    startmin;           /**< Starting minute timestamp component offset (0-59). */
    
    /* Chronological Structure Elements: End Boundaries */
    gint    endyear;            /**< Four-digit terminal target year integer. */
    gint    endmonth;           /**< Terminal target numeric month integer value (1-12). */
    gint    endday;             /**< Terminal target day of the month integer value (1-31). */
    gint    endhour;            /**< Terminal hour component matching a 24-hour cycle (0-23). */
    gint    endmin;             /**< Terminal minute timestamp component offset (0-59). */
    
    /* Boolean Processing Directives (Mapped to C Bit integers) */
    gint    isyearly;           /**< Evaluation flag evaluating to TRUE if this item recurs every calendar year cycle. */
    gint    isallday;           /**< Evaluation flag evaluating to TRUE if this event skips raw hourly timestamp checks. */
    gint    ispriority;         /**< Evaluation flag evaluating to TRUE if this event commands higher display prominence rules. */
};

G_DEFINE_TYPE (CalendarEvent, calendar_event, G_TYPE_OBJECT);


enum {
    PROP_0,
    PROP_EVENTID,
    PROP_SUMMARY,
    PROP_LOCATION,
    PROP_DESCRIPTION,
    PROP_STARTYEAR,
    PROP_STARTMONTH,
    PROP_STARTDAY,
    PROP_STARTHOUR,
    PROP_STARTMIN,
    PROP_ENDYEAR,
    PROP_ENDMONTH,
    PROP_ENDDAY,
    PROP_ENDHOUR,
    PROP_ENDMIN,
    PROP_ISYEARLY,
    PROP_ISALLDAY,   
    PROP_ISPRIORITY,  
    LAST_PROP
};
static GParamSpec *properties[LAST_PROP];

/**
 * @brief Intercepts and processes property read requests for a CalendarEvent instance.
 * 
 * This internal GObject engine callback maps public `g_object_get()` requests to the 
 * respective data accessor functions. For string-type properties (`summary`, `location`, 
 * and `description`), it utilizes `g_value_set_static_string` to expose thread-safe, 
 * copy-free read access to internal buffers without incurring additional allocation overhead.
 *
 * @param object  The generic GObject pointer (cast internally to CalendarEvent).
 * @param prop_id The property identification token assigned during class_init.
 * @param value   The destination GValue container where property contents are boxed.
 * @param pspec   The metadata parameter specification tracking this property field.
 * 
 * @return void
 */
static void calendar_event_get_property(GObject *object,
                                        guint   prop_id,
                                        GValue  *value,
                                        GParamSpec *pspec)
{
    CalendarEvent *self = (CalendarEvent *)object;

    switch (prop_id)
    {
        case PROP_EVENTID:
            g_value_set_int(value, calendar_event_get_eventid(self));
            break;
        case PROP_SUMMARY:
            // Use static string setters to pass the reference without duplicating memory on the heap!
            g_value_set_static_string(value, calendar_event_get_summary(self));
            break;
        case PROP_LOCATION:
            // Use static string setters to pass the reference without duplicating memory on the heap!
            g_value_set_static_string(value, calendar_event_get_location(self));
            break;
        case PROP_DESCRIPTION:
            // Use static string setters to pass the if-bounds reference without duplicating memory on the heap!
            g_value_set_static_string(value, calendar_event_get_description(self));
            break;
        case PROP_STARTYEAR:
            g_value_set_int(value, calendar_event_get_start_year(self));
            break;
        case PROP_STARTMONTH:
            g_value_set_int(value, calendar_event_get_start_month(self));
            break;
        case PROP_STARTDAY:
            g_value_set_int(value, calendar_event_get_start_day(self));
            break;
        case PROP_STARTHOUR:
            g_value_set_int(value, calendar_event_get_start_hour(self));
            break;
        case PROP_STARTMIN:
            g_value_set_int(value, calendar_event_get_start_min(self));
            break;
        case PROP_ENDYEAR:
            g_value_set_int(value, calendar_event_get_end_year(self));
            break;
        case PROP_ENDMONTH:
            g_value_set_int(value, calendar_event_get_end_month(self));
            break;
        case PROP_ENDDAY:
            g_value_set_int(value, calendar_event_get_end_day(self));
            break;
        case PROP_ENDHOUR:
            g_value_set_int(value, calendar_event_get_end_hour(self));
            break;
        case PROP_ENDMIN:
            g_value_set_int(value, calendar_event_get_end_min(self));
            break;
        case PROP_ISYEARLY:
            g_value_set_int(value, calendar_event_get_is_yearly(self));
            break;
        case PROP_ISALLDAY:
            g_value_set_int(value, calendar_event_get_is_allday(self));
            break;                     
        case PROP_ISPRIORITY:
            g_value_set_int(value, calendar_event_get_is_priority(self));
            break;
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
            break;
    }
}

/**
 * @brief Intercepts and processes property write requests for a CalendarEvent instance.
 * 
 * This internal GObject engine callback maps standard `g_object_set()` requests to the 
 * respective data mutator/setter functions. For string inputs (`summary`, `location`, 
 * and `description`), the values extracted from the generic GValue are safely passed 
 * downstream, where your class setters handle copying or string duplicating routines.
 *
 * @param object  The generic GObject pointer (cast internally to CalendarEvent).
 * @param prop_id The property identification token assigned during class_init.
 * @param value   The source GValue container holding the input payload.
 * @param pspec   The metadata parameter specification tracking this property field.
 * 
 * @return void
 */
static void calendar_event_set_property(GObject *object,
                                        guint   prop_id,
                                        const GValue  *value,
                                        GParamSpec *pspec)
{
    CalendarEvent *self = (CalendarEvent *)object;

    switch (prop_id)
    {
        case PROP_EVENTID:
            calendar_event_set_eventid(self, g_value_get_int(value));
            break;
        case PROP_SUMMARY:
            calendar_event_set_summary(self, g_value_get_string(value));
            break;
        case PROP_LOCATION:
            calendar_event_set_location(self, g_value_get_string(value));
            break;
        case PROP_DESCRIPTION:
            calendar_event_set_description(self, g_value_get_string(value));
            break;
        case PROP_STARTYEAR:
            calendar_event_set_start_year(self, g_value_get_int(value));
            break;
        case PROP_STARTMONTH:
            calendar_event_set_start_month(self, g_value_get_int(value));
            break;
        case PROP_STARTDAY:
            calendar_event_set_start_day(self, g_value_get_int(value));
            break;
        case PROP_STARTHOUR:
            calendar_event_set_start_hour(self, g_value_get_int(value));
            break;
        case PROP_STARTMIN:
            calendar_event_set_start_min(self, g_value_get_int(value));
            break;
        case PROP_ENDYEAR:
            calendar_event_set_end_year(self, g_value_get_int(value));
            break;
        case PROP_ENDMONTH:
            calendar_event_set_end_month(self, g_value_get_int(value));
            break;
        case PROP_ENDDAY:
            calendar_event_set_end_day(self, g_value_get_int(value));
            break;
        case PROP_ENDHOUR:
            calendar_event_set_end_hour(self, g_value_get_int(value));
            break;
        case PROP_ENDMIN:
            calendar_event_set_end_min(self, g_value_get_int(value));
            break;
        case PROP_ISYEARLY:
            calendar_event_set_is_yearly(self, g_value_get_int(value));
            break;
        case PROP_ISALLDAY:
            calendar_event_set_is_allday(self, g_value_get_int(value));
            break;                  
        case PROP_ISPRIORITY:
            calendar_event_set_is_priority(self, g_value_get_int(value));
            break; 
        default:
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
            break;
    }
}


/**
 * @brief Performs final heap memory deallocation before a CalendarEvent object is destroyed.
 * 
 * This function functions as the explicit instance destructor for the data model. 
 * It is guaranteed by GObject to execute exactly once when the reference count drops to zero. 
 * It cleanly clears and frees the heap-allocated string properties (`summary`, `location`, 
 * and `description`) using safe pointer wiping to prevent memory leaks, before chaining up 
 * to the parent class's finalize handler.
 *
 * @param object The GObject instance undergoing terminal finalisation.
 * 
 * @return void
 */
static void calendar_event_finalize(GObject *object)
{
    CalendarEvent *self = (CalendarEvent *)object;
    
    // Safely clear and deallocate dynamic heap string buffers
    g_clear_pointer(&self->summary, g_free);
    g_clear_pointer(&self->location, g_free);
    g_clear_pointer(&self->description, g_free);

    // Hand execution over to the parent object destructor
    G_OBJECT_CLASS(calendar_event_parent_class)->finalize(object);
}


/**
 * @brief Class initialization function for the CalendarEvent data model.
 * 
 * Configures the class-wide structures, overrides base GObject lifecycle handlers, 
 * and registers all data properties required to describe a calendar event. This function 
 * executes exactly once when the class type is first referenced at runtime.
 * 
 * ### Overridden Methods
 * - `get_property`: Intercepts property value read requests.
 * - `set_property`: Intercepts property value write requests.
 * - `finalize`: Cleans up dynamic heap string buffers during object destruction.
 * 
 * ### Installed Properties
 * - `eventid` (integer): Database identifier.
 * - `summary` (string): Title/headline text of the event.
 * - `location` (string): Venue or physical coordinates text.
 * - `description` (string): Detailed body notes or description text.
 * - `startyear` / `endyear` (integer): Boundary years for the event lifespan.
 * - `startmonth` / `endmonth` (integer): Boundary months (1-12).
 * - `startday` / `endday` (integer): Boundary days (1-31).
 * - `starthour` / `endhour` (integer): Boundary hours (0-23).
 * - `startmin` / `endmin` (integer): Boundary minutes (0-59).
 * - `isyearly` (integer): Flag tracking annual recurrence definitions.
 * - `isallday` (integer): Flag indicating time-agnostic daily boundaries.
 * - `ispriority` (integer): Flag sorting display precedence hierarchy.
 *
 * @param klass A pointer to the CalendarEventClass layout structure.
 * 
 * @return void
 */
static void calendar_event_class_init (CalendarEventClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS(klass);

    object_class->get_property = calendar_event_get_property;
    object_class->set_property = calendar_event_set_property;    
    
    // Override and register the finalize destruction routine
    object_class->finalize     = calendar_event_finalize;

    properties[PROP_EVENTID] =
    g_param_spec_int("eventid", "eventid", "The event id", 0, G_MAXINT, 0, G_PARAM_READWRITE);

    properties[PROP_SUMMARY] =
    g_param_spec_string("summary", "Summary", "The event summary", NULL, (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

    properties[PROP_LOCATION] =
    g_param_spec_string("location", "Location", "The event location", NULL, (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

    properties[PROP_DESCRIPTION] =
    g_param_spec_string("description", "Description", "The event description", NULL, (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

    properties[PROP_STARTYEAR] =
    g_param_spec_int("startyear", "startyear", "The event start year", 0, G_MAXINT, 0, G_PARAM_READWRITE);

    properties[PROP_STARTMONTH] =
    g_param_spec_int("startmonth", "startmonth", "The event start month", 0, G_MAXINT, 0, G_PARAM_READWRITE);

    properties[PROP_STARTDAY] =
    g_param_spec_int("startday", "startday", "The event start day", 0, G_MAXINT, 0, G_PARAM_READWRITE);

    properties[PROP_STARTHOUR] =
    g_param_spec_int("starthour", "starthour", "The event start hour", 0, G_MAXINT, 0, G_PARAM_READWRITE);

    properties[PROP_STARTMIN] =
    g_param_spec_int("startmin", "startmin", "The event start minute", 0, G_MAXINT, 0, G_PARAM_READWRITE);

    properties[PROP_ENDYEAR] =
    g_param_spec_int("endyear", "endyear", "The event end year", 0, G_MAXINT, 0, G_PARAM_READWRITE);

    properties[PROP_ENDMONTH] =
    g_param_spec_int("endmonth", "endmonth", "The event end month", 0, G_MAXINT, 0, G_PARAM_READWRITE);

    properties[PROP_ENDDAY] =
    g_param_spec_int("endday", "endday", "The event end day", 0, G_MAXINT, 0, G_PARAM_READWRITE);

    properties[PROP_ENDHOUR] =
    g_param_spec_int("endhour", "endhour", "The event end hour", 0, G_MAXINT, 0, G_PARAM_READWRITE);

    properties[PROP_ENDMIN] =
    g_param_spec_int("endmin", "endmin", "The event end minute", 0, G_MAXINT, 0, G_PARAM_READWRITE);

    properties[PROP_ISYEARLY] =
    g_param_spec_int("isyearly", "isyearly", "The event repeats yearly", 0, G_MAXINT, 0, G_PARAM_READWRITE);

    properties[PROP_ISALLDAY] =
    g_param_spec_int("isallday", "isallday", "This is an all day event", 0, G_MAXINT, 0, G_PARAM_READWRITE);

    properties[PROP_ISPRIORITY] =
    g_param_spec_int("ispriority", "ispriority", "The event has high priority", 0, G_MAXINT, 0, G_PARAM_READWRITE); 

    g_object_class_install_properties(object_class, LAST_PROP, properties);
}

/**
 * @brief Instance initialization function for a CalendarEvent object.
 * 
 * Serves as the instance-level constructor. Because GObject guarantees all instance 
 * structures are zero-filled out-of-the-box (`NULL` pointers and numerical zeroes), 
 * no explicit variable population is required here.
 *
 * @param self A pointer to the newly allocated CalendarEvent instance.
 * 
 * @return void
 */
static void calendar_event_init (CalendarEvent *self)
{
    /* Intentionally left empty as zero-allocation initialization is handled by GObject */
}


/**
 * @brief Finalize the CalendarEvent object.
 * @param object The GObject instance.
 */
static void calendar_event_dispose(GObject *object)
{
    CalendarEvent *self = CALENDAR_EVENT(object);
    g_clear_pointer(&self->summary, g_free);
    g_clear_pointer(&self->location, g_free);
    g_clear_pointer(&self->description, g_free);
    G_OBJECT_CLASS(calendar_event_parent_class)->dispose(object);
}

/**
 * @brief Get the event ID.
 * @param self The CalendarEvent instance.
 * @return The event ID.
 */
gint calendar_event_get_eventid(CalendarEvent *self){
    return self->eventid;
}

/**
 * @brief Set the event ID.
 * @param self The CalendarEvent instance.
 * @param eventid The unique ID of the event.
 */
void calendar_event_set_eventid(CalendarEvent *self, gint event_id)
{
    self->eventid =event_id;
}

/**
 * @brief Get the summary of the event.
 * @param self The CalendarEvent instance.
 * @return The summary of the event.
 */
const gchar* calendar_event_get_summary(CalendarEvent *self){
    return self->summary;
}

/**
 * @brief Set the summary of the event.
 * @param self The CalendarEvent instance.
 * @param summary The summary to set.
 */
void calendar_event_set_summary(CalendarEvent *self, const gchar* summary)
{
    if(g_strcmp0(summary, self->summary))
    { //check not the same
        g_free(self->summary);
        self->summary =g_strdup(summary);
    }
}

/**
 * @brief Get the location of the event.
 * @param self The CalendarEvent instance.
 * @return The location of the event.
 */
const gchar* calendar_event_get_location(CalendarEvent *self){
    return self->location;
}

/**
 * @brief Set the location of the event.
 * @param self The CalendarEvent instance.
 * @param location The location to set.
 */
void calendar_event_set_location(CalendarEvent *self, const gchar* location)
{
    if(g_strcmp0(location, self->location))
    { //check not the same
        g_free(self->location);
        self->location =g_strdup(location);
    }
}

/**
 * @brief Get the description of the event.
 * @param self The CalendarEvent instance.
 * @return The description of the event.
 */
const gchar* calendar_event_get_description(CalendarEvent *self){

    return self->description;

}

/**
 * @brief Set the description of the event.
 * @param self The CalendarEvent instance.
 * @param description The description to set.
 */
void calendar_event_set_description(CalendarEvent *self, const gchar* description){

    if(g_strcmp0(description, self->description))
    { //check not the same
        g_free(self->description);
        self->description =g_strdup(description);
    }

}

/**
 * @brief Get the start year.
 * @param self The CalendarEvent instance.
 * @return The start year.
 */
gint calendar_event_get_start_year(CalendarEvent *self){
    return self->startyear;
}

/**
 * @brief Set the start year.
 * @param self The CalendarEvent instance.
 * @param start_year The start year to set.
 */
void calendar_event_set_start_year(CalendarEvent *self, gint start_year)
{
    self->startyear =start_year;
}

/**
 * @brief Get the start month.
 * @param self The CalendarEvent instance.
 * @return The start month.
 */
gint calendar_event_get_start_month(CalendarEvent *self){
    return self->startmonth;
}

/**
 * @brief Set the start month.
 * @param self The CalendarEvent instance.
 * @param start_month The start month to set.
 */
void calendar_event_set_start_month(CalendarEvent *self, gint start_month)
{
    self->startmonth =start_month;
}

/**
 * @brief Get the start day.
 * @param self The CalendarEvent instance.
 * @return The start day.
 */
gint calendar_event_get_start_day(CalendarEvent *self){
    return self->startday;
}

/**
 * @brief Set the start day.
 * @param self The CalendarEvent instance.
 * @param start_day The start day to set.
 */
void calendar_event_set_start_day(CalendarEvent *self, gint start_day)
{
    self->startday =start_day;
}

/**
 * @brief Get the start hour.
 * @param self The CalendarEvent instance.
 * @return The start hour.
 */
gint calendar_event_get_start_hour(CalendarEvent *self){
    return self->starthour;
}

/**
 * @brief Set the start hour.
 * @param self The CalendarEvent instance.
 * @param start_hour The start hour to set.
 */
void calendar_event_set_start_hour(CalendarEvent *self, gint start_hour)
{
    self->starthour =start_hour;
}

/**
 * @brief Get the start minute.
 * @param self The CalendarEvent instance.
 * @return The start minute.
 */
gint calendar_event_get_start_min(CalendarEvent *self){
    return self->startmin;
}

/**
 * @brief Set the start minute.
 * @param self The CalendarEvent instance.
 * @param start_min The start minute to set.
 */
void calendar_event_set_start_min(CalendarEvent *self, gint start_min)
{
    self->startmin =start_min;
}

/**
 * @brief Get the end year.
 * @param self The CalendarEvent instance.
 * @return The end year.
 */
gint calendar_event_get_end_year(CalendarEvent *self){
    return self->endyear;
}

/**
 * @brief Set the end year.
 * @param self The CalendarEvent instance.
 * @param end_year The end year to set.
 */
void calendar_event_set_end_year(CalendarEvent *self, gint end_year)
{
    self->endyear =end_year;
}

/**
 * @brief Get the end month.
 * @param self The CalendarEvent instance.
 * @return The end month.
 */
gint calendar_event_get_end_month(CalendarEvent *self){
    return self->endmonth;
}

/**
 * @brief Set the end month.
 * @param self The CalendarEvent instance.
 * @param end_month The end month to set.
 */
void calendar_event_set_end_month(CalendarEvent *self, gint end_month)
{
    self->endmonth =end_month;
}

/**
 * @brief Get the end day.
 * @param self The CalendarEvent instance.
 * @return The end day.
 */
gint calendar_event_get_end_day(CalendarEvent *self){
    return self->endday;
}

/**
 * @brief Set the end day.
 * @param self The CalendarEvent instance.
 * @param end_day The end day to set.
 */
void calendar_event_set_end_day(CalendarEvent *self, gint end_day)
{
    self->endday =end_day;
}

/**
 * @brief Get the end hour.
 * @param self The CalendarEvent instance.
 * @return The end hour.
 */
gint calendar_event_get_end_hour(CalendarEvent *self){
    return self->endhour;
}

/**
 * @brief Set the end hour.
 * @param self The CalendarEvent instance.
 * @param end_hour The end hour to set.
 */
void calendar_event_set_end_hour(CalendarEvent *self, gint end_hour)
{
    self->endhour =end_hour;
}

/**
 * @brief Get the end minute.
 * @param self The CalendarEvent instance.
 * @return The end minute.
 */
gint calendar_event_get_end_min(CalendarEvent *self){
    return self->endmin;
}

/**
 * @brief Set the end minute.
 * @param self The CalendarEvent instance.
 * @param end_min The end minute to set.
 */
void calendar_event_set_end_min(CalendarEvent *self, gint end_min)
{
    self->endmin =end_min;
}

/**
 * @brief Get whether the event is yearly.
 * @param self The CalendarEvent instance.
 * @return The yearly status of the event.
 */
gint calendar_event_get_is_yearly(CalendarEvent *self){
    return self->isyearly;
}
/**
 * @brief Set whether the event is yearly.
 * @param self The CalendarEvent instance.
 * @param is_yearly The yearly status to set.
 */
void calendar_event_set_is_yearly(CalendarEvent *self, gint is_yearly)
{
    self->isyearly =is_yearly;
}
/**
 * @brief Get whether the event is all-day.
 * @param self The CalendarEvent instance.
 * @return The all-day status of the event.
 */
gint calendar_event_get_is_allday(CalendarEvent *self){
    return self->isallday;
}

/**
 * @brief Set whether the event is all-day.
 * @param self The CalendarEvent instance.
 * @param is_allday The all-day status to set.
 */
void calendar_event_set_is_allday(CalendarEvent *self, gint is_allday)
{
    self->isallday =is_allday;
}

/**
 * @brief Get whether the event is a priority.
 * @param self The CalendarEvent instance.
 * @return The priority status of the event.
 */
gint calendar_event_get_is_priority(CalendarEvent *self){
    return self->ispriority;
}

/**
 * @brief Set whether the event is a priority.
 * @param self The CalendarEvent instance.
 * @param is_priority The priority status to set.
 */
void calendar_event_set_is_priority(CalendarEvent *self, gint is_priority)
{
    self->ispriority =is_priority;
}
