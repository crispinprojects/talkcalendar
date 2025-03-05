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

//====================================================================
// GTK4  month view calendar with tooltips
// Author: Alan Crispin <crispinalan@gmail.com> 
// Date: February 2025
//====================================================================

#include "customcalendar.h"

// locals (day and month names do not change)
static char *dayname[7];
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
	GtkWidget *btn_next_month;
	GtkWidget *btn_prev_month;
	GtkWidget *btn_next_year;
	GtkWidget *btn_prev_year;
	GtkWidget *grid;
	GtkWidget *day_name_labels[7];
	GtkWidget *day_number_labels[6][7];
	GDateTime *date;
	GtkWidget *month_year_label;
	int day;
	int month;
	int year;
	int day_month[6][7];
	int days[6][7];	
	char *eventday_array[32];
	char *tooltip_array[32];	
	int num_marked_days;
	int marked_day[32];
	char *holiday_array[32];
	int num_marked_holidays;
	int marked_holiday[32];
	const gchar* today_colour;
	const gchar* event_colour;
	const gchar* holiday_colour;
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
    PROP_HOLIDAYCOLOUR, 
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
        case PROP_HOLIDAYCOLOUR:
            custom_calendar_set_holiday_colour(self, g_value_get_string(value));
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
    case PROP_HOLIDAYCOLOUR:
      g_value_set_string(value, custom_calendar_get_holiday_colour(self));
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
	g_clear_pointer(&calendar->grid, gtk_widget_unparent);
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
     
    properties[PROP_HOLIDAYCOLOUR] =
    g_param_spec_string("holidaycolour",
                        "holidaycolour",
                        "colour string for a holiday",
                        "blue",
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

void custom_calendar_reset_holidays(CustomCalendar *calendar)
{
	g_return_if_fail(CUSTOM_IS_CALENDAR(calendar));

	// day 0 not used but set to zero
	//  array size 32 array index [0,1,.....31]

	for (int i = 0; i < 32; i++){		
		calendar->marked_holiday[i] = FALSE;
	}
	
	calendar->num_marked_holidays = 0;
}

//======================================================================

void custom_calendar_mark_holiday(CustomCalendar *calendar, guint day)
{
	g_return_if_fail(CUSTOM_IS_CALENDAR(calendar));
	
	if (day >= 1 && day <= 31)
	{
		calendar->marked_holiday[day] = TRUE;
		calendar->num_marked_holidays++;
	}	
}
//======================================================================
void custom_calendar_unmark_holiday(CustomCalendar *calendar, guint day)
{
	g_return_if_fail(CUSTOM_IS_CALENDAR(calendar));	

	if (day >= 1 && day <= 31)
	{
		calendar->marked_holiday[day] = FALSE;
		calendar->num_marked_holidays--;
	}
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


void custom_calendar_initialise_holiday_array(CustomCalendar *calendar)
{
	
     calendar->holiday_array[0]=""; //day0 has zero index
     calendar->holiday_array[1]=""; //day1 
     calendar->holiday_array[2]="";
     calendar->holiday_array[3]="";
     calendar->holiday_array[4]="";
     calendar->holiday_array[5]="";
     calendar->holiday_array[6]="";
     calendar->holiday_array[7]="";
     calendar->holiday_array[8]="";
     calendar->holiday_array[9]="";
     
     calendar->holiday_array[10]=""; 
     calendar->holiday_array[11]=""; 
     calendar->holiday_array[12]="";
     calendar->holiday_array[13]="";
     calendar->holiday_array[14]="";
     calendar->holiday_array[15]="";
     calendar->holiday_array[16]="";
     calendar->holiday_array[17]="";
     calendar->holiday_array[18]="";
     calendar->holiday_array[19]="";
     
     calendar->holiday_array[20]=""; 
     calendar->holiday_array[21]=""; 
     calendar->holiday_array[22]="";
     calendar->holiday_array[23]="";
     calendar->holiday_array[24]="";
     calendar->holiday_array[25]="";
     calendar->holiday_array[26]="";
     calendar->holiday_array[27]="";
     calendar->holiday_array[28]="";
     calendar->holiday_array[29]="";
     
     calendar->holiday_array[30]="";
     calendar->holiday_array[31]="";
     
}
//=====================================================================

void custom_calendar_set_holiday_str(CustomCalendar *calendar, int day, char* title)
{
	//g_return_if_fail(CUSTOM_IS_CALENDAR(calendar));
	
	
	if (day >= 1 && day <= 31)
	{		
		calendar->holiday_array[day]=title;
	}
	
}


//======================================================================
static int setup_monthname()
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
	
	gtk_widget_set_focusable(widget, TRUE);		
	setup_monthname();	
	custom_calendar_initialise_eventday_array(calendar);
	custom_calendar_initialise_holiday_array(calendar);
    //custom_calendar_reset_marks(calendar);
	int week_start = 0; // local
	
	//Set colour defaults to prevent theme parser error
	//Is this the right place to intialise? (more research needed)		
	calendar->today_colour="rgb(173,216,230)";
	calendar->event_colour="rgb(222,184,135)";	
	calendar->holiday_colour="rgb(102,205,170)";
	calendar->show_tooltips =1;	//true
		
	
	int n_cols = 7;
	int n_rows = 8;
	GtkWidget *button;
	GtkGesture *gesture;

	gesture = gtk_gesture_click_new();
	g_signal_connect(gesture, "pressed", G_CALLBACK(custom_calendar_button_press), calendar);
	gtk_widget_add_controller(GTK_WIDGET(calendar), GTK_EVENT_CONTROLLER(gesture));
	
	PangoAttrList *attr;
	attr = pango_attr_list_new();	
	pango_attr_list_insert(attr, pango_attr_weight_new(PANGO_WEIGHT_BOLD));
	
	
	calendar->btn_next_month = gtk_button_new_with_label (">");
	gtk_widget_set_tooltip_text(GTK_WIDGET(calendar->btn_next_month), "Next Month");		
	g_signal_connect_swapped(calendar->btn_next_month, "clicked", G_CALLBACK(callbk_next_month), calendar);
		
	calendar->btn_next_year=gtk_button_new_with_label (">>");	
	gtk_widget_set_tooltip_text(GTK_WIDGET(calendar->btn_next_year), "Next Year");
	g_signal_connect_swapped(calendar->btn_next_year, "clicked", G_CALLBACK(callbk_next_year), calendar);
	
	calendar->btn_prev_month=gtk_button_new_with_label ("<");
	gtk_widget_set_tooltip_text(GTK_WIDGET(calendar->btn_prev_month), "Previous Month");
	g_signal_connect_swapped(calendar->btn_prev_month, "clicked", G_CALLBACK(callbk_prev_month), calendar);

	calendar->btn_prev_year =gtk_button_new_with_label ("<<");
	gtk_widget_set_tooltip_text(GTK_WIDGET(calendar->btn_prev_year), "Previous Year");
	g_signal_connect_swapped(calendar->btn_prev_year, "clicked", G_CALLBACK(callbk_prev_year), calendar);

	GtkWidget *label_my = gtk_label_new("month-year"); //label month year
	gtk_label_set_attributes(GTK_LABEL(label_my), attr);
	gtk_widget_set_hexpand(label_my, TRUE);
	//gtk_widget_set_vexpand(label_my, TRUE);	
	calendar->month_year_label = label_my;

	calendar->grid = gtk_grid_new();
	//gtk_widget_set_hexpand(calendar->grid, TRUE);
	//gtk_widget_set_vexpand(calendar->grid, TRUE);
	gtk_grid_set_row_homogeneous(GTK_GRID(calendar->grid), TRUE);
	gtk_grid_set_column_homogeneous(GTK_GRID(calendar->grid), TRUE);

	gtk_grid_attach(GTK_GRID(calendar->grid), calendar->btn_prev_year, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(calendar->grid), calendar->btn_prev_month, 1, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(calendar->grid), calendar->month_year_label, 2, 0, 3, 1);
	gtk_grid_attach(GTK_GRID(calendar->grid), calendar->btn_next_month, 5, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(calendar->grid), calendar->btn_next_year, 6, 0, 1, 1);
	
	// Grid is 7 days

	/*
	 - -*------------------------------------
	 0  | 1  | 2  | 3   | 4  | 5  | 6  |
	 Mon Tue  Wed  Thu  Fri  Sat  Sun

	 */
	 //Pango week days
		
	
	
		
	GtkWidget *weekday_label= gtk_label_new("Mon");
	gtk_label_set_attributes(GTK_LABEL(weekday_label), attr);
	gtk_grid_attach(GTK_GRID(calendar->grid),weekday_label,0,1,1,1);
	weekday_label= gtk_label_new("Tue");
	gtk_label_set_attributes(GTK_LABEL(weekday_label), attr);
	gtk_grid_attach(GTK_GRID(calendar->grid),weekday_label,1,1,1,1);
	weekday_label= gtk_label_new("Wed");
	gtk_label_set_attributes(GTK_LABEL(weekday_label), attr);
	gtk_grid_attach(GTK_GRID(calendar->grid),weekday_label,2,1,1,1);
	weekday_label= gtk_label_new("Thu");
	gtk_label_set_attributes(GTK_LABEL(weekday_label), attr);
	gtk_grid_attach(GTK_GRID(calendar->grid),weekday_label,3,1,1,1);
	weekday_label= gtk_label_new("Fri");
	gtk_label_set_attributes(GTK_LABEL(weekday_label), attr);
	gtk_grid_attach(GTK_GRID(calendar->grid),weekday_label,4,1,1,1);
	weekday_label= gtk_label_new("Sat");
	gtk_label_set_attributes(GTK_LABEL(weekday_label), attr);
	gtk_grid_attach(GTK_GRID(calendar->grid),weekday_label,5,1,1,1);
	weekday_label= gtk_label_new("Sun");
	gtk_label_set_attributes(GTK_LABEL(weekday_label), attr);
	gtk_grid_attach(GTK_GRID(calendar->grid),weekday_label,6,1,1,1);
		
	pango_attr_list_unref(attr);
	
	// initialise
	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			GtkWidget *label = gtk_label_new("");			
			
			gtk_widget_set_hexpand(label, TRUE);
			gtk_widget_set_vexpand(label, TRUE);			
			
			//PangoAttrList *attr;
			//attr = pango_attr_list_new();
			//pango_attr_list_insert(attr, pango_attr_weight_new(PANGO_WEIGHT_BOLD));			
			//gtk_label_set_attributes(GTK_LABEL(label), attr);
			//pango_attr_list_unref(attr);
			
			gtk_grid_attach(GTK_GRID(calendar->grid), label, x, y + 2, 1, 1);
			calendar->day_number_labels[y][x] = label; // initialise
		}
	}

	// get local date at startup
	GDateTime *now;
	now = g_date_time_new_now_local();
	calendar->year = g_date_time_get_year(now);
	calendar->month = g_date_time_get_month(now);
	calendar->day = g_date_time_get_day_of_month(now);	
	custom_calendar_select_day(calendar, calendar->day, calendar->month, calendar->year);
	g_date_time_unref(now); // freeit quick before it leaks

	gtk_widget_set_hexpand(calendar->grid, TRUE);
	gtk_widget_set_vexpand(calendar->grid, TRUE);
	gtk_widget_set_parent(calendar->grid, GTK_WIDGET(calendar));
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
	int first_day_month = first_day_of_month(calendar->month, calendar->year);
	int week_start = 1; // start week on a Monday
	int remainder = (first_day_of_month(calendar->month, calendar->year) - week_start + 7) % 7;
	aday = 1 - remainder; // day with offset
	int n_cols = 7;
	int n_rows = 8;
	bool today_flag=FALSE;
	
	int days_in_month = g_date_get_days_in_month(calendar->month, calendar->year);
		
	gchar *month_year_str = "";
	gchar *year_str = g_strdup_printf("%d", calendar->year);
	gchar *month_str = monthname[calendar->month - 1];
	month_year_str = g_strconcat(month_year_str, " ", month_str, " ", year_str, NULL);
	
	gtk_label_set_label(GTK_LABEL(calendar->month_year_label), month_year_str);
	
	calendar->btn_next_month = gtk_button_new_with_label ("Next Month >");
	gtk_widget_set_tooltip_text(GTK_WIDGET(calendar->btn_next_month), "Next Month");		
	g_signal_connect_swapped(calendar->btn_next_month, "clicked", G_CALLBACK(callbk_next_month), calendar);
	
		
	GDate *today_date;
	today_date = g_date_new();
	g_date_set_time_t(today_date, time(NULL));
	int today_day = g_date_get_day(today_date);
	int today_month = g_date_get_month(today_date);
	int today_year = g_date_get_year(today_date);
	g_date_free(today_date); // freeit quick before it leaks
		
	
	const gchar* today_colour_str=calendar->today_colour;
	const gchar* event_colour_str=calendar->event_colour;
	const gchar* holiday_colour_str=calendar->holiday_colour;
		
	//providers
	
	gchar* today_provider_str="label.today {background-image: none; background-color: ";	
	today_provider_str= g_strconcat(today_provider_str,today_colour_str,";}", NULL);	
	
	//testing
	//gchar* today_provider_str = "label.today {background-image: none; background-color: rgb(224,27,36);}";
		
	gchar* event_provider_str="label.event {background-image: none; background-color: ";	
	event_provider_str= g_strconcat(event_provider_str,event_colour_str,";}", NULL);	
	
	gchar* holiday_provider_str="label.holiday {background-image: none; background-color: ";	
	holiday_provider_str= g_strconcat(holiday_provider_str,holiday_colour_str,";}", NULL);	
	
	GtkCssProvider *provider_today; //today provider
	provider_today = gtk_css_provider_new ();
	gtk_css_provider_load_from_data (provider_today, today_provider_str,-1); //Debian 12 Bookworm GTK4.8
	//gtk_css_provider_load_from_string(provider_today, today_provider_str); //Debian 13 Trixie GTK 4.17
	gtk_style_context_add_provider_for_display (gdk_display_get_default (), GTK_STYLE_PROVIDER (provider_today), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
		
	GtkCssProvider *provider_event; //event provider
	provider_event = gtk_css_provider_new ();
	gtk_css_provider_load_from_data (provider_event,event_provider_str,-1); //depreciated
	//gtk_css_provider_load_from_string (provider_event,event_provider_str);
	gtk_style_context_add_provider_for_display (gdk_display_get_default (), GTK_STYLE_PROVIDER (provider_event), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
		
	GtkCssProvider *provider_holiday; //holiday provider
	provider_holiday = gtk_css_provider_new ();
	gtk_css_provider_load_from_data (provider_holiday,holiday_provider_str,-1);	
	//gtk_css_provider_load_from_string(provider_holiday,holiday_provider_str);	
	gtk_style_context_add_provider_for_display (gdk_display_get_default (), GTK_STYLE_PROVIDER (provider_holiday), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	
	// reset labels
	for (int y = 0; y < 6; y++)
		for (int x = 0; x < 7; x++)
		{
			gtk_label_set_label(GTK_LABEL(calendar->day_number_labels[y][x]), "");
		
			//reset providers
			gtk_widget_remove_css_class (GTK_WIDGET(calendar->day_number_labels[y][x]), "today");
			gtk_widget_remove_css_class (GTK_WIDGET(calendar->day_number_labels[y][x]), "event");
			gtk_widget_remove_css_class (GTK_WIDGET(calendar->day_number_labels[y][x]), "holiday");			
			//always use frame
			gtk_widget_add_css_class (GTK_WIDGET(calendar->day_number_labels[y][x]), "frame");			
		}
		
	gchar *aday_str = "";
	//gchar *tooltip_str = "";
	// update day labels
	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 7; x++)
		{
			
			if (aday > 0 && aday <= days_in_month)
			{
				calendar->days[y][x] = aday;		
								
				char* day_num_str=g_strdup_printf("%i", aday);
				
				char* holiday_str =calendar->holiday_array[aday];
				
				char* title_str =calendar->eventday_array[aday];
			
				aday_str = g_strconcat(aday_str ,day_num_str, NULL);
				char* tooltip_str ="";
				
				if(calendar->show_tooltips==1)
				{
				tooltip_str =calendar->tooltip_array[aday];				
				gtk_widget_set_tooltip_text(GTK_WIDGET(calendar->day_number_labels[y][x]), tooltip_str);
			    }
			    else{
			    tooltip_str ="";
				gtk_widget_set_tooltip_text(GTK_WIDGET(calendar->day_number_labels[y][x]), tooltip_str);
				}
				
				gtk_label_set_label(GTK_LABEL(calendar->day_number_labels[y][x]), aday_str);
										
					//if today					
					if (aday == today_day && calendar->month == today_month && calendar->year == today_year)
					{												
						gtk_widget_add_css_class (GTK_WIDGET(calendar->day_number_labels[y][x]), "today");
								
					} //today
					else
					{
						if (calendar->marked_day[aday]) //event day
						{
							gtk_widget_add_css_class (GTK_WIDGET(calendar->day_number_labels[y][x]), "event");
						}
												
						if (calendar->marked_holiday[aday])
						{
						gtk_widget_add_css_class (GTK_WIDGET(calendar->day_number_labels[y][x]), "holiday");
						}
						
					} //else not today
										
					//if ((calendar->marked_day[aday]) 
					    //&& (aday != today_day) 
					    //&& (calendar->month != today_month)
					    //&& (calendar->year != today_year))					
					//{
						//gtk_widget_add_css_class (GTK_WIDGET(calendar->day_number_labels[y][x]), "event");
					//}
					
						
			} //<days_in_month
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

static void callbk_next_month(CustomCalendar *calendar)
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

static void callbk_prev_month(CustomCalendar *calendar)
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
static void callbk_next_year(CustomCalendar *calendar)
{
	calendar->year = calendar->year + 1;
	calendar->month = calendar->month;
	calendar->day = 1;
	custom_calendar_select_day(calendar, calendar->day, calendar->month, calendar->year);	
	g_signal_emit(calendar, custom_calendar_signals[NEXT_YEAR_SIGNAL], 0);
}
//======================================================================
static void callbk_prev_year(CustomCalendar *calendar)
{
	calendar->year = calendar->year - 1;
	calendar->month = calendar->month;
	calendar->day = 1;
	custom_calendar_select_day(calendar, calendar->day, calendar->month, calendar->year);
	g_signal_emit(calendar, custom_calendar_signals[PREV_YEAR_SIGNAL], 0);
}
//======================================================================
static void custom_calendar_button_press(GtkGestureClick *gesture, int n_press, double x, double y, gpointer user_data)
{
	CustomCalendar *calendar = user_data;
	GtkWidget *widget = GTK_WIDGET(calendar);
	GtkWidget *label;
	int row = -1, col = -1;
	int ix, iy;
	int day_month;
	int aday;
	
	int days_in_month = g_date_get_days_in_month(calendar->month, calendar->year);			
	int first_day_month = first_day_of_month(calendar->month, calendar->year);
	
	int week_start = 1; // start week on a Monday
	int remainder = (first_day_of_month(calendar->month, calendar->year) - week_start + 7) % 7;
	
	aday = 1 - remainder; // day with offset
	
	label = gtk_widget_pick(widget, x, y, GTK_PICK_DEFAULT); //create label as pick widget
	
	for (iy = 0; iy < 6; iy++) {
		for (ix = 0; ix < 7; ix++)
		{
			if (aday > 0 && aday <= days_in_month)	{				
			if (label == calendar->day_number_labels[iy][ix]){
				row = iy;
				col = ix;
			} //picker label			
		    } //if aday	
		    aday = aday + 1;
		}//ix
		
	}//iy
		
	// aday range should prevent critical assertion error
	// critical g_date_time_get_day_of_week: assertion 'datetime != NULL' failed	

	if (row == -1 || col == -1) return; //something is wrong return

	day_month = calendar->day_month[row][col];
	aday = calendar->days[row][col];	
	calendar->day = aday;	
	
	if (!gtk_widget_has_focus(widget))
		gtk_widget_grab_focus(widget);


	//final check to see that day is in a valid range before calling select day	
    if((calendar->day<1) || (calendar->day>days_in_month)) calendar->day=1;
    
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
//======================================================================
void custom_calendar_set_holiday_colour(CustomCalendar *self, const gchar* colourname)
{
	self->holiday_colour =colourname;		
}
//======================================================================
const gchar* custom_calendar_get_holiday_colour(CustomCalendar *self){
	
	return self->holiday_colour;
}
//======================================================================
