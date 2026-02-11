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


struct _CalendarEvent
{
    GObject parent_instance; //parent
    gint    eventid; //field
    gchar* summary; //field
    gchar* location; //field
    gchar* description; //field

    gint    startyear; //field
    gint    startmonth; //field
    gint    startday; //field
    gint    starthour; //field
    gint    startmin; //field

    gint    endyear; //field
    gint    endmonth; //field
    gint    endday; //field
    gint    endhour; //field
    gint    endmin; //field

    gint    isyearly; //field
    gint    isallday; //field   
    gint    ispriority; //field  
};

G_DEFINE_TYPE (CalendarEvent, calendar_event, G_TYPE_OBJECT);
//G_DEFINE_FINAL_TYPE(CalendarEvent, calendar_event, G_TYPE_OBJECT)
//======================================================================
/**
 * @brief Initialize the CalendarEvent object.
 * @param self The CalendarEvent instance.
 */
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
 * @brief Get the instance properties.
 * @param object The GObject instance.
 * @param prop_id The property ID.
 * @param value The value to get.
 * @param pspec The parameter specification.
 */
static void calendar_event_get_property(GObject *object,
                                        guint   prop_id,
                                        GValue  *value,
                                        GParamSpec *pspec)
{
    CalendarEvent *self =(CalendarEvent *)object;

    switch (prop_id)
    {
        case PROP_EVENTID:
             g_value_set_int(value, calendar_event_get_eventid(self)); //boxing
            break;
        case PROP_SUMMARY:
            g_value_set_string(value, calendar_event_get_summary(self)); //boxing
            break;
         case PROP_LOCATION:
            g_value_set_string(value, calendar_event_get_location(self)); //boxing
            break;
         case PROP_DESCRIPTION:
            g_value_set_string(value, calendar_event_get_description(self)); //boxing
            break;
         case PROP_STARTYEAR:
             g_value_set_int(value, calendar_event_get_start_year(self)); //boxing
            break;
          case PROP_STARTMONTH:
             g_value_set_int(value, calendar_event_get_start_month(self)); //boxing
            break;
         case PROP_STARTDAY:
             g_value_set_int(value, calendar_event_get_start_day(self)); //boxing
            break;
         case PROP_STARTHOUR:
             g_value_set_int(value, calendar_event_get_start_hour(self)); //boxing
            break;
        case PROP_STARTMIN:
             g_value_set_int(value, calendar_event_get_start_min(self)); //boxing
            break;

         case PROP_ENDYEAR:
             g_value_set_int(value, calendar_event_get_end_year(self)); //boxing
            break;
          case PROP_ENDMONTH:
             g_value_set_int(value, calendar_event_get_end_month(self)); //boxing
            break;
         case PROP_ENDDAY:
             g_value_set_int(value, calendar_event_get_end_day(self)); //boxing
            break;
         case PROP_ENDHOUR:
             g_value_set_int(value, calendar_event_get_end_hour(self)); //boxing
            break;
        case PROP_ENDMIN:
             g_value_set_int(value, calendar_event_get_end_min(self)); //boxing
            break;

         case PROP_ISYEARLY:
             g_value_set_int(value, calendar_event_get_is_yearly(self)); //boxing
            break;
          case PROP_ISALLDAY:
             g_value_set_int(value, calendar_event_get_is_allday(self)); //boxing
            break;                     
         case PROP_ISPRIORITY:
             g_value_set_int(value, calendar_event_get_is_priority(self)); //boxing
            break;
    }
}

/**
 * @brief Set the instance properties.
 * @param self The CalendarEvent instance.
 * @param prop_id The property ID.
 * @param value The value to set.
 * @param pspec The parameter specification.
 */
static void calendar_event_set_property(GObject *object,
                                        guint   prop_id,
                                        const GValue  *value,
                                        GParamSpec *pspec)
{
    CalendarEvent *self =(CalendarEvent *)object;

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

    }
}

/**
 * @brief Class initialization function.
 * @param klass The CalendarEventClass instance.
 */
static void calendar_event_class_init (CalendarEventClass *klass)
{
    //make class constructor static meaning not available outside this class

    GObjectClass *object_class =G_OBJECT_CLASS(klass);

    //override these
    object_class->get_property = calendar_event_get_property;
    object_class->set_property = calendar_event_set_property;

    //properties
    properties[PROP_EVENTID] =
    g_param_spec_int("eventid",
                     "eventid",
                     "The event id",
                     0,G_MAXINT,0,
                     G_PARAM_READWRITE);


    properties[PROP_SUMMARY] =
    g_param_spec_string("summary",
                        "Summary",
                        "The event summary",
                        NULL,
                        (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));


    properties[PROP_LOCATION] =
    g_param_spec_string("location",
                        "Location",
                        "The event location",
                        NULL,
                        (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

    properties[PROP_DESCRIPTION] =
    g_param_spec_string("description",
                        "Description",
                        "The event description",
                        NULL,
                        (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

    properties[PROP_STARTYEAR] =
    g_param_spec_int("startyear",
                     "startyear",
                     "The event start year",
                     0,G_MAXINT,0,
                     G_PARAM_READWRITE);

    properties[PROP_STARTMONTH] =
    g_param_spec_int("startmonth",
                     "startmonth",
                     "The event start month",
                     0,G_MAXINT,0,
                     G_PARAM_READWRITE);

    properties[PROP_STARTDAY] =
    g_param_spec_int("startday",
                     "startday",
                     "The event start day",
                     0,G_MAXINT,0,
                     G_PARAM_READWRITE);

    properties[PROP_STARTHOUR] =
    g_param_spec_int("starthour",
                     "starthour",
                     "The event start hour",
                     0,G_MAXINT,0,
                     G_PARAM_READWRITE);

    properties[PROP_STARTMIN] =
    g_param_spec_int("startmin",
                     "startmin",
                     "The event start minute",
                     0,G_MAXINT,0,
                     G_PARAM_READWRITE);

    properties[PROP_ENDYEAR] =
    g_param_spec_int("endyear",
                     "endyear",
                     "The event end year",
                     0,G_MAXINT,0,
                     G_PARAM_READWRITE);

    properties[PROP_ENDMONTH] =
    g_param_spec_int("endmonth",
                     "endmonth",
                     "The event end month",
                     0,G_MAXINT,0,
                     G_PARAM_READWRITE);

    properties[PROP_ENDDAY] =
    g_param_spec_int("endday",
                     "endday",
                     "The event end day",
                     0,G_MAXINT,0,
                     G_PARAM_READWRITE);

    properties[PROP_ENDHOUR] =
    g_param_spec_int("endhour",
                     "endhour",
                     "The event end hour",
                     0,G_MAXINT,0,
                     G_PARAM_READWRITE);

    properties[PROP_ENDMIN] =
    g_param_spec_int("endmin",
                     "endmin",
                     "The event end minute",
                     0,G_MAXINT,0,
                     G_PARAM_READWRITE);

    properties[PROP_ISYEARLY] =
    g_param_spec_int("isyearly",
                     "isyearly",
                     "The event repeats yearly",
                     0,G_MAXINT,0,
                     G_PARAM_READWRITE);

    properties[PROP_ISALLDAY] =
    g_param_spec_int("isallday",
                     "isallday",
                     "This is an all day event",
                     0,G_MAXINT,0,
                     G_PARAM_READWRITE);
 		
    properties[PROP_ISPRIORITY] =
    g_param_spec_int("ispriority",
                     "ispriority",
                     "The event has high priority",
                     0,G_MAXINT,0,
                     G_PARAM_READWRITE);
     
    g_object_class_install_properties(object_class, LAST_PROP, properties);
}
//======================================================================
static void calendar_event_init (CalendarEvent *self)
{  
	//leave empty
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
