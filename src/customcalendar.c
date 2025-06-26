/* customcalendar.c
 *
 * Copyright 2025 Alan Crispin
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

//====================================================================
// GTK4  Month View Calendar 
// Author: Alan Crispin <crispinalan@gmail.com> 
// Date: JUne 2025
// Month View Calendar for the Talk Calendar Project
// Features: tooltips and day event titles
//====================================================================
#include <glib.h>

#include "customcalendar.h"

static char *monthname[12];

// declarations
static void custom_calendar_select_day(CustomCalendar *calendar, guint dday, guint month, guint year);
static void custom_calendar_button_press(GtkGestureClick *gesture, int n_press, double x, double y, gpointer user_data);

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

//======================================================================
struct _CustomCalendar
{
// GtkWidget parent_instance;
GtkWidget widget;

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
char *eventday_array[32];
char *tooltip_array[32];	
int num_marked_days;
int marked_day[32];

const gchar* today_colour;
const gchar* event_colour;

gboolean show_tooltips;	

};

//=====================================================================

struct _CustomCalendarClass
{
GtkWidgetClass parent_class;
void (*day_selected)(GtkCalendar *calendar);
void (*prev_month)(GtkCalendar *calendar);
void (*next_month)(GtkCalendar *calendar);
void (*prev_year)(GtkCalendar *calendar);
void (*next_year)(GtkCalendar *calendar);
};

G_DEFINE_TYPE(CustomCalendar, custom_calendar, GTK_TYPE_WIDGET)

//======================================================================
//define properties
enum {
PROP_0,
PROP_TODAYCOLOUR, 
PROP_EVENTCOLOUR,     
PROP_SHOWTOOLTIPS,         
LAST_PROP
};

static GParamSpec *properties[LAST_PROP];

//======================================================================
static void custom_calendar_set_property(GObject *object,
guint   prop_id,
const GValue  *value,
GParamSpec *pspec)
{
CustomCalendar *self =(CustomCalendar *)object;    

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
//}
}
//======================================================================
static void custom_calendar_get_property(GObject *object,
guint         prop_id,
GValue       *value,
GParamSpec   *pspec)
{
CustomCalendar *self =(CustomCalendar *)object;

switch (prop_id)
{
case PROP_TODAYCOLOUR:
g_value_set_string(value, custom_calendar_get_today_colour(self));
break;
case PROP_EVENTCOLOUR:
g_value_set_string(value, custom_calendar_get_event_colour(self));
break;

case PROP_SHOWTOOLTIPS:
//g_value_set_boolean (value, calendar->frame);
g_value_set_boolean  (value, custom_calendar_get_show_tooltips(self));
break;

default:
G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
break; 

}
}
//======================================================================
static void custom_calendar_dispose(GObject *object)
{
CustomCalendar *calendar = CUSTOM_CALENDAR(object);
g_clear_pointer (&calendar->date, g_date_time_unref);
g_clear_pointer (&calendar->header, gtk_widget_unparent);
g_clear_pointer (&calendar->grid, gtk_widget_unparent);

G_OBJECT_CLASS(custom_calendar_parent_class)->dispose(object);
}
//======================================================================
static void custom_calendar_class_init(CustomCalendarClass *klass)
{
GObjectClass *object_class =G_OBJECT_CLASS(klass);

GtkWidgetClass *widget_class;
widget_class = (GtkWidgetClass *)klass;

object_class->dispose = custom_calendar_dispose;

//properies	
//override these
object_class->set_property = custom_calendar_set_property;
object_class->get_property = custom_calendar_get_property;

//properties
properties[PROP_TODAYCOLOUR] =
g_param_spec_string("todaycolour",
"todaycolour",
"colour string for today",
"red",
(G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

properties[PROP_EVENTCOLOUR] =
g_param_spec_string("eventcolour",
"eventcolour",
"colour string for an event",
"brown",
(G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));


properties[PROP_SHOWTOOLTIPS] =
g_param_spec_boolean("showtooltips",
"showtooltips",
"sets if calendar has tooltips",
TRUE, 
(G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));


g_object_class_install_properties(object_class, LAST_PROP, properties);                  

//Signals emitted on user actions

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
//======================================================================

GtkWidget *custom_calendar_new(void)
{
return g_object_new(CUSTOM_TYPE_CALENDAR, NULL);
}
//======================================================================

void custom_calendar_initialise_eventday_array(CustomCalendar *calendar)
{

calendar->eventday_array[0]=""; //day0 has zero index
calendar->eventday_array[1]=""; //day1 
calendar->eventday_array[2]="";
calendar->eventday_array[3]="";
calendar->eventday_array[4]="";
calendar->eventday_array[5]="";
calendar->eventday_array[6]="";
calendar->eventday_array[7]="";
calendar->eventday_array[8]="";
calendar->eventday_array[9]="";

calendar->eventday_array[10]=""; 
calendar->eventday_array[11]=""; 
calendar->eventday_array[12]="";
calendar->eventday_array[13]="";
calendar->eventday_array[14]="";
calendar->eventday_array[15]="";
calendar->eventday_array[16]="";
calendar->eventday_array[17]="";
calendar->eventday_array[18]="";
calendar->eventday_array[19]="";

calendar->eventday_array[20]=""; 
calendar->eventday_array[21]=""; 
calendar->eventday_array[22]="";
calendar->eventday_array[23]="";
calendar->eventday_array[24]="";
calendar->eventday_array[25]="";
calendar->eventday_array[26]="";
calendar->eventday_array[27]="";
calendar->eventday_array[28]="";
calendar->eventday_array[29]="";

calendar->eventday_array[30]="";
calendar->eventday_array[31]="";

}
//=====================================================================

void custom_calendar_set_day_str(CustomCalendar *calendar, int day, char* title)
{
//g_return_if_fail(CUSTOM_IS_CALENDAR(calendar));

char* day_titles=calendar->eventday_array[day];
day_titles =g_strconcat(day_titles,"\n",title,NULL);

if (day >= 1 && day <= 31)
{
//calendar->eventday_array[day]=title;
calendar->eventday_array[day]=day_titles;
}	
}

//======================================================================

void custom_calendar_initialise_tooltip_array(CustomCalendar *calendar)
{

calendar->tooltip_array[0]=""; //day0 has zero index
calendar->tooltip_array[1]=""; //day1 
calendar->tooltip_array[2]="";
calendar->tooltip_array[3]="";
calendar->tooltip_array[4]="";
calendar->tooltip_array[5]="";
calendar->tooltip_array[6]="";
calendar->tooltip_array[7]="";
calendar->tooltip_array[8]="";
calendar->tooltip_array[9]="";

calendar->tooltip_array[10]=""; 
calendar->tooltip_array[11]=""; 
calendar->tooltip_array[12]="";
calendar->tooltip_array[13]="";
calendar->tooltip_array[14]="";
calendar->tooltip_array[15]="";
calendar->tooltip_array[16]="";
calendar->tooltip_array[17]="";
calendar->tooltip_array[18]="";
calendar->tooltip_array[19]="";

calendar->tooltip_array[20]=""; 
calendar->tooltip_array[21]=""; 
calendar->tooltip_array[22]="";
calendar->tooltip_array[23]="";
calendar->tooltip_array[24]="";
calendar->tooltip_array[25]="";
calendar->tooltip_array[26]="";
calendar->tooltip_array[27]="";
calendar->tooltip_array[28]="";
calendar->tooltip_array[29]="";

calendar->tooltip_array[30]="";
calendar->tooltip_array[31]="";

}
//=====================================================================

void custom_calendar_set_tooltip_str(CustomCalendar *calendar, int day, char* tooltip_str)
{
//g_return_if_fail(CUSTOM_IS_CALENDAR(calendar));

char* tooltip_strs=calendar->tooltip_array[day];
tooltip_strs =g_strconcat(tooltip_strs,"\n",tooltip_str,NULL);

if (day >= 1 && day <= 31)
{
calendar->tooltip_array[day]=tooltip_strs;
}	
}
//======================================================================

void custom_calendar_reset_marks(CustomCalendar *calendar)
{
g_return_if_fail(CUSTOM_IS_CALENDAR(calendar));

// day 0 not used but set to zero
//  array size 32 array index [0,1,.....31]

for (int i = 0; i < 32; i++){
calendar->marked_day[i] = FALSE;		
}

calendar->num_marked_days = 0;	
}
//======================================================================
void custom_calendar_mark_day(CustomCalendar *calendar, guint day)
{
g_return_if_fail(CUSTOM_IS_CALENDAR(calendar));

if (day >= 1 && day <= 31)
{
calendar->marked_day[day] = TRUE;
calendar->num_marked_days++;
}	
}
//======================================================================
void custom_calendar_unmark_day(CustomCalendar *calendar, guint day)
{
g_return_if_fail(CUSTOM_IS_CALENDAR(calendar));	

if (day >= 1 && day <= 31)
{
calendar->marked_day[day] = FALSE;
calendar->num_marked_days--;
}
}
//======================================================================
gboolean custom_calendar_get_day_is_marked(CustomCalendar *calendar, guint day)
{
if (day >= 1 && day <= 31)
return calendar->marked_day[day];

return FALSE;
}
//======================================================================

//======================================================================
char* get_day_of_week(int day, int month, int year) 
{

char* weekday_str="";
GDate* day_date;
day_date = g_date_new_dmy(day, month, year);
GDateWeekday weekday =g_date_get_weekday(day_date);


switch(weekday)
{
case G_DATE_MONDAY:
weekday_str="Monday";
break;
case G_DATE_TUESDAY:
weekday_str="Tuesday";
break;
case G_DATE_WEDNESDAY:
weekday_str="Wednesday";
break;
case G_DATE_THURSDAY:
weekday_str="Thursday";
break;
case G_DATE_FRIDAY:
weekday_str="Friday";
break;
case G_DATE_SATURDAY:
weekday_str="Saturday";
break;
case G_DATE_SUNDAY:
weekday_str="Sunday";
break;
default:
weekday_str="unknown";
}//switch

return weekday_str;
}
//======================================================================
static void setup_monthname()
{
int i;
for (i = 0; i < 12; i++)
{	
switch (i)
{
case 0:
monthname[i] = g_strdup("January");
break;
case 1:
monthname[i] = g_strdup("Feburary");
break;
case 2:
monthname[i] = g_strdup("March");
break;
case 3:
monthname[i] = g_strdup("April");
break;
case 4:
monthname[i] = g_strdup("May");
break;
case 5:
monthname[i] = g_strdup("June");
break;
case 6:
monthname[i] = g_strdup("July");
break;
case 7:
monthname[i] = g_strdup("August");
break;
case 8:
monthname[i] = g_strdup("September");
break;
case 9:
monthname[i] = g_strdup("October");
break;
case 10:
monthname[i] = g_strdup("November");
break;
case 11:
monthname[i] = g_strdup("December");
break;
default:
monthname[i] = g_strdup("Month");
}
}
}
//======================================================================

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
year + (year / 4)) %
7;
}
//=====================================================================
static void custom_calendar_init(CustomCalendar *calendar)
{

GtkWidget *widget = GTK_WIDGET(calendar);

calendar->day = 0;
calendar->month = 0;
calendar->year = 0;
//Set colour defaults	
calendar->today_colour="rgb(221,160,221)"; //plum
calendar->event_colour="rgb(211,211,211)"; //light grey

gtk_widget_set_focusable(widget, TRUE);		
setup_monthname();	
custom_calendar_initialise_eventday_array(calendar);	
custom_calendar_initialise_tooltip_array(calendar);

calendar->show_tooltips =1;	//true

GtkGesture *gesture;

gesture = gtk_gesture_click_new();
g_signal_connect(gesture, "pressed", G_CALLBACK(custom_calendar_button_press), calendar);
gtk_widget_add_controller(GTK_WIDGET(calendar), GTK_EVENT_CONTROLLER(gesture));

calendar->header = g_object_new (GTK_TYPE_BOX,"css-name", "header", NULL);

calendar->btn_next_month = gtk_button_new_from_icon_name("pan-end-symbolic");
gtk_button_set_can_shrink(GTK_BUTTON(calendar->btn_next_month),TRUE); //from gtk4.12 		
gtk_widget_set_tooltip_text(calendar->btn_next_month, "Next Month");
g_signal_connect_swapped(calendar->btn_next_month, "clicked", G_CALLBACK(callbk_next_month), calendar);

calendar->btn_next_year = gtk_button_new_from_icon_name("pan-end-symbolic");
gtk_button_set_can_shrink(GTK_BUTTON(calendar->btn_next_year),TRUE);	
gtk_widget_set_tooltip_text(calendar->btn_next_year, "Next Year");
g_signal_connect_swapped(calendar->btn_next_year, "clicked", G_CALLBACK(callbk_next_year), calendar);

calendar->btn_prev_month = gtk_button_new_from_icon_name("pan-start-symbolic");
gtk_button_set_can_shrink(GTK_BUTTON(calendar->btn_prev_month),TRUE);	
gtk_widget_set_tooltip_text(calendar->btn_prev_month, "Previous Month");
g_signal_connect_swapped(calendar->btn_prev_month, "clicked", G_CALLBACK(callbk_prev_month), calendar);

calendar->btn_prev_year = gtk_button_new_from_icon_name("pan-start-symbolic");
gtk_button_set_can_shrink(GTK_BUTTON(calendar->btn_prev_year),TRUE);	
gtk_widget_set_tooltip_text(calendar->btn_prev_year, "Previous Year");
g_signal_connect_swapped(calendar->btn_prev_year, "clicked", G_CALLBACK(callbk_prev_year), calendar);

GtkWidget *label_month = gtk_label_new("month");
gtk_widget_set_hexpand(label_month, TRUE); //not vertical just horizontal		
calendar->month_label = label_month;

GtkWidget *label_year = gtk_label_new("year");
gtk_widget_set_hexpand(label_year, TRUE);
calendar->year_label = label_year;

GtkWidget *label_date = gtk_label_new("date"); //date label
gtk_widget_set_hexpand(label_date, TRUE);		
calendar->date_label = label_date;

gtk_box_append(GTK_BOX(calendar->header), calendar->btn_prev_month);
gtk_box_append(GTK_BOX(calendar->header), calendar->month_label);
gtk_box_append(GTK_BOX(calendar->header), calendar->btn_next_month);

gtk_box_append(GTK_BOX(calendar->header), calendar->date_label);

gtk_box_append(GTK_BOX(calendar->header), calendar->btn_prev_year);
gtk_box_append(GTK_BOX(calendar->header), calendar->year_label);
gtk_box_append(GTK_BOX(calendar->header), calendar->btn_next_year);


//GRID

// Grid is 7 days

//
//- -------------------------------------
//0  | 1  | 2  | 3   | 4  | 5  | 6  |
//Mon Tue  Wed  Thu  Fri  Sat  Sun

//

calendar->grid = gtk_grid_new();
gtk_widget_set_hexpand(calendar->grid, TRUE);
gtk_widget_set_vexpand(calendar->grid, TRUE);
gtk_grid_set_row_homogeneous(GTK_GRID(calendar->grid), TRUE);
gtk_grid_set_column_homogeneous(GTK_GRID(calendar->grid), TRUE);

calendar->monday_label= gtk_label_new("Mon");		
gtk_grid_attach(GTK_GRID(calendar->grid),calendar->monday_label,0,0,1,1);	
calendar->tuesday_label= gtk_label_new("Tue");		
gtk_grid_attach(GTK_GRID(calendar->grid),calendar->tuesday_label,1,0,1,1);		
calendar->wednesday_label= gtk_label_new("Wed");	
gtk_grid_attach(GTK_GRID(calendar->grid),calendar->wednesday_label,2,0,1,1);	
calendar->thursday_label= gtk_label_new("Thu");		
gtk_grid_attach(GTK_GRID(calendar->grid),calendar->thursday_label,3,0,1,1);	
calendar->friday_label= gtk_label_new("Fri");		
gtk_grid_attach(GTK_GRID(calendar->grid),calendar->friday_label,4,0,1,1);	
calendar->saturday_label= gtk_label_new("Sat");		
gtk_grid_attach(GTK_GRID(calendar->grid),calendar->saturday_label,5,0,1,1);	
calendar->sunday_label= gtk_label_new("Sun");

gtk_grid_attach(GTK_GRID(calendar->grid),calendar->sunday_label,6,0,1,1);

// initialise
for (int y = 0; y < 6; y++)
{
for (int x = 0; x < 7; x++)
{

//GtkWidget *label = gtk_label_new("");				
GtkWidget *label = g_object_new (GTK_TYPE_LABEL,"css-name", "label", NULL);		

gtk_widget_set_hexpand(label, TRUE);
gtk_widget_set_vexpand(label, TRUE);
gtk_widget_add_css_class(label,"day_number");	

gtk_grid_attach(GTK_GRID(calendar->grid), label, x, y+1, 1, 1);
calendar->day_number_labels[y][x] = label; // initialise
}
}
gtk_widget_set_hexpand(calendar->grid, TRUE);
gtk_widget_set_vexpand(calendar->grid, TRUE);



// get local date at startup
GDateTime *now;
now = g_date_time_new_now_local();
calendar->year = g_date_time_get_year(now);
calendar->month = g_date_time_get_month(now);
calendar->day = g_date_time_get_day_of_month(now);	
custom_calendar_select_day(calendar, calendar->day, calendar->month, calendar->year);
g_date_time_unref(now); // freeit quick before it leaks

GtkLayoutManager *box_layout;
box_layout = gtk_widget_get_layout_manager (GTK_WIDGET (calendar));
gtk_orientable_set_orientation (GTK_ORIENTABLE (box_layout), GTK_ORIENTATION_VERTICAL);
gtk_box_layout_set_spacing (GTK_BOX_LAYOUT (box_layout), 2);
gtk_widget_set_parent (calendar->header, GTK_WIDGET (calendar));
gtk_widget_set_parent (calendar->grid, GTK_WIDGET (calendar));

}
//======================================================================
int custom_calendar_get_day(CustomCalendar *calendar)
{
return calendar->day;
}
//======================================================================

int custom_calendar_get_month(CustomCalendar *calendar)
{
return calendar->month;
}
//======================================================================
int custom_calendar_get_year(CustomCalendar *calendar)
{
return calendar->year;
}
//======================================================================
static void custom_calendar_select_day(CustomCalendar *calendar, guint dday, guint month, guint year)
{

int aday = 0;
//int first_day_month = first_day_of_month(calendar->month, calendar->year);
int week_start = 1; // start week on a Monday
int remainder = (first_day_of_month(calendar->month, calendar->year) - week_start + 7) % 7;
aday = 1 - remainder; // day with offset

int days_in_month = g_date_get_days_in_month(calendar->month, calendar->year);

gchar *date_str = "";
gchar *weekday_str=get_day_of_week(calendar->day, calendar->month, calendar->year);
gchar *day_num_str = g_strdup_printf("%d", calendar->day);
gchar *year_str = g_strdup_printf("%d", calendar->year);
gchar *month_str = monthname[calendar->month - 1];
date_str = g_strconcat(date_str, " ",weekday_str," ",day_num_str, " ", month_str, " ", year_str, NULL);

//date label
PangoAttrList *bold_attr;
bold_attr = pango_attr_list_new();	
pango_attr_list_insert(bold_attr, pango_attr_weight_new(PANGO_WEIGHT_BOLD));
gtk_label_set_attributes(GTK_LABEL(calendar->date_label), bold_attr);
gtk_label_set_label(GTK_LABEL(calendar->date_label), date_str);		
pango_attr_list_unref(bold_attr);	

gtk_label_set_label(GTK_LABEL(calendar->month_label), month_str);
gtk_label_set_label(GTK_LABEL(calendar->year_label), year_str);

GDate *today_date;
today_date = g_date_new();
g_date_set_time_t(today_date, time(NULL));
int today_day = g_date_get_day(today_date);
int today_month = g_date_get_month(today_date);
int today_year = g_date_get_year(today_date);
g_date_free(today_date); // freeit quick before it leaks

//providers
gchar* today_provider_str="label.today {background-image: none; background-color: ";	
today_provider_str= g_strconcat(today_provider_str,calendar->today_colour,";}", NULL);	

GtkCssProvider *provider_today; //today colour provider
provider_today = gtk_css_provider_new ();gtk_css_provider_load_from_string(provider_today, today_provider_str); //Fedoar 40 GTK 4.14
gtk_style_context_add_provider_for_display (gdk_display_get_default (), GTK_STYLE_PROVIDER (provider_today), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

gchar* event_provider_str="label.event {background-image: none; background-color: ";	
event_provider_str= g_strconcat(event_provider_str,calendar->event_colour,";}", NULL);	

GtkCssProvider *provider_event; //event colour provider
provider_event = gtk_css_provider_new ();
gtk_css_provider_load_from_string (provider_event,event_provider_str);
gtk_style_context_add_provider_for_display (gdk_display_get_default (), GTK_STYLE_PROVIDER (provider_event), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);


// reset labels
for (int y = 0; y < 6; y++)
for (int x = 0; x < 7; x++)
{
gtk_label_set_label(GTK_LABEL(calendar->day_number_labels[y][x]), "");
gtk_label_set_use_markup(GTK_LABEL(calendar->day_number_labels[y][x]), TRUE);
//reset providers
gtk_widget_remove_css_class (GTK_WIDGET(calendar->day_number_labels[y][x]), "today");
gtk_widget_remove_css_class (GTK_WIDGET(calendar->day_number_labels[y][x]), "event");

gtk_widget_add_css_class (GTK_WIDGET(calendar->day_number_labels[y][x]), "frame");
}

gchar *aday_str = "";	
//char *aday_markup_str = "";

// update day labels
for (int y = 0; y < 6; y++)
{
for (int x = 0; x < 7; x++)
{ 

if (aday > 0 && aday <= days_in_month)
{
calendar->days[y][x] = aday;

char* day_num_str="";				
char* tooltip_str ="";


//if today					
if (aday == today_day && calendar->month == today_month && calendar->year == today_year)
{												
gtk_widget_add_css_class (GTK_WIDGET(calendar->day_number_labels[y][x]), "today");
day_num_str = g_strdup_printf("%s%d%s", "<u><b>", aday, "</b></u>");		
} //today
else
{


if (calendar->marked_day[aday]) //event day
{
gtk_widget_add_css_class (GTK_WIDGET(calendar->day_number_labels[y][x]), "event");
day_num_str = g_strdup_printf("%s%d%s%s", "<i><b>", aday, "</b></i>", "<b>*</b>");

//day_num_str=g_strdup_printf("%i", aday);
}
else
{
day_num_str=g_strdup_printf("%i", aday);
}												


} //else not today

if(calendar->show_tooltips==1)
{
tooltip_str =calendar->tooltip_array[aday];
gtk_widget_set_tooltip_text(GTK_WIDGET(calendar->day_number_labels[y][x]), tooltip_str);
}
else{
tooltip_str ="";
gtk_widget_set_tooltip_text(GTK_WIDGET(calendar->day_number_labels[y][x]), tooltip_str);
}

char* title_str =calendar->eventday_array[aday];
//aday_str = g_strconcat(aday_str ,day_num_str,"\n ",title_str, NULL);
aday_str = g_strconcat(aday_str ,day_num_str,title_str, NULL);
gtk_label_set_label(GTK_LABEL(calendar->day_number_labels[y][x]), aday_str);


}
aday = aday + 1;
aday_str = "";
} //for x
} //for y


}

//======================================================================
void custom_calendar_goto_today(CustomCalendar *calendar)
{	
GDateTime *today;
today = g_date_time_new_now_local();
calendar->year = g_date_time_get_year(today);
calendar->month = g_date_time_get_month(today);
calendar->day = g_date_time_get_day_of_month(today);
custom_calendar_select_day(calendar, calendar->day, calendar->month, calendar->year);
g_date_time_unref(today);
}

//======================================================================

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
//======================================================================

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
//======================================================================
void callbk_next_year(CustomCalendar *calendar)
{
calendar->year = calendar->year + 1;
calendar->month = calendar->month;
calendar->day = 1;
custom_calendar_select_day(calendar, calendar->day, calendar->month, calendar->year);	
g_signal_emit(calendar, custom_calendar_signals[NEXT_YEAR_SIGNAL], 0);
}
//======================================================================
void callbk_prev_year(CustomCalendar *calendar)
{
calendar->year = calendar->year - 1;
calendar->month = calendar->month;
calendar->day = 1;
custom_calendar_select_day(calendar, calendar->day, calendar->month, calendar->year);
g_signal_emit(calendar, custom_calendar_signals[PREV_YEAR_SIGNAL], 0);
}
//======================================================================

//======================================================================
static void custom_calendar_button_press(GtkGestureClick *gesture, int n_press, double x, double y, gpointer user_data)
{
CustomCalendar *calendar = user_data;
GtkWidget *widget = GTK_WIDGET(calendar);
GtkWidget *label;
int row_number = -1, col_number = -1;
int ix, iy;
//int day_month;
//int aday =1;

int days_in_month = g_date_get_days_in_month(calendar->month, calendar->year);			
//int first_day_month = first_day_of_month(calendar->month, calendar->year);

int week_start = 1; // start week on a Monday
int remainder = (first_day_of_month(calendar->month, calendar->year) - week_start + 7) % 7;

int offset = 1 - remainder; // day with offset say -2
//g_print("offset = %d\n",offset);

int number_of_columns=7; //seven days
int number_of_rows = 6;

label = gtk_widget_pick(widget, x, y, GTK_PICK_DEFAULT); //create label as pick widget

for (iy = 0; iy < number_of_rows; iy++) {
for (ix = 0; ix < number_of_columns; ix++)
{
//if (aday > 0 && aday <= days_in_month)	{				
if (label == calendar->day_number_labels[iy][ix]){
row_number = iy;
col_number = ix;
} //picker label
}//ix		
}//iy

if (row_number == -1 || col_number == -1) return; //something is wrong return

int index = (row_number * number_of_columns) + col_number;

//example row_number =1  number_of_columns = 7 and col =3
// index = 1*7+3 

int offset_index = index+offset;
//example if index =3 and offset -2 then index =1

if (offset_index <=0)
{		
calendar->day =1;	
callbk_prev_month(calendar);
}	
else if (offset_index >days_in_month)
{			
calendar->day =1;
callbk_next_month(calendar);	
}
else
{
int aday = calendar->days[row_number][col_number];	
calendar->day = aday;
}

//check if in day range
if(calendar->day <=0 || calendar->day >days_in_month)
{
//g_print("calendar->day %d out of range so reset\n",calendar->day);
calendar->day=1;
}

//g_print("day_month = %d\n",day_month);	
if (!gtk_widget_has_focus(widget))
gtk_widget_grab_focus(widget);


//final check to see that day is in a valid range before calling select day	
if((calendar->day<1) || (calendar->day>days_in_month)) calendar->day=1;

//g_print("calendar->day = %d\n",calendar->day);
//g_print("calendar->month = %d\n",calendar->month);
//g_print("calendar->year = %d\n",calendar->year);

custom_calendar_select_day(calendar, calendar->day, calendar->month, calendar->year);	
g_signal_emit(calendar, custom_calendar_signals[DAY_SELECTED_SIGNAL], 0);
}
//======================================================================
void custom_calendar_update(CustomCalendar *calendar)
{
g_return_if_fail(CUSTOM_IS_CALENDAR(calendar));
custom_calendar_select_day(calendar, calendar->day, calendar->month, calendar->year);
}
//======================================================================
//properties

//======================================================================
gboolean custom_calendar_get_show_tooltips(CustomCalendar *self)
{

return self->show_tooltips;
}
//======================================================================
void custom_calendar_set_show_tooltips(CustomCalendar *self, gboolean show_tooltips)
{
self->show_tooltips=show_tooltips;
//g_print("custom calendar: show_tooltips = %d\n", self->show_tooltips);	
}
//======================================================================
//======================================================================
void custom_calendar_set_today_colour(CustomCalendar *self, const gchar* colour_str)
{
self->today_colour =colour_str;	

}
//======================================================================
const gchar* custom_calendar_get_today_colour(CustomCalendar *self){

return self->today_colour;
}
//======================================================================
void custom_calendar_set_event_colour(CustomCalendar *self, const gchar* colourname)
{
self->event_colour =colourname;		
}
//======================================================================
const gchar* custom_calendar_get_event_colour(CustomCalendar *self){

return self->event_colour;
}
//=====================================================================
