/* main.c
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
#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gstdio.h>  //needed for g_mkdir
#include <stdio.h>
#include <ctype.h>

#include <stdlib.h>
#include <string.h>

#include "calendarevent.h"
#include "dbmanager.h"
#include "customcalendar.h"
//speaking
#include "dictionary.h"

// Global database handle
static sqlite3 *db_handle = NULL;


// File and directory names for configuration
#define CONFIG_DIRNAME "talkcalendar"
#define CONFIG_FILENAME "talkcalendar-083"

static char * m_config_file = NULL;
//======================================================================
// Function prototypes for configuration handling
static void config_load_default(void);
static void config_read(void);
static void config_write(void);
void config_initialize(void);

//======================================================================

static void callbk_new_event(GSimpleAction *action, GVariant *parameter,  gpointer user_data);
static void callbk_edit_event(GSimpleAction *action, GVariant *parameter,  gpointer user_data);
static void callbk_delete_event(GSimpleAction *action, GVariant *parameter,  gpointer user_data);
static void callbk_delete_all(GSimpleAction *action, GVariant *parameter,  gpointer user_data);

static void callbk_dropdown_summary(GtkDropDown* self, gpointer user_data);


// Function prototypes for export/import functionality
static void callbk_export(GSimpleAction *action, GVariant *parameter, gpointer user_data);
static void file_save_response (GObject *source, GAsyncResult *result, void *user_data);
void export_file(char *file_name);
static void callbk_import(GSimpleAction *action, GVariant *parameter, gpointer user_data);
void import_ical_file(gpointer user_data);
static void file_open_response (GObject *source, GAsyncResult *result, void *user_data);

//shutdown
// Forward declaration of the close runner helper function
static void handle_final_dialog_response(GObject *source_object, GAsyncResult *res, gpointer user_data);

// Function prototypes for custom calendar functionality
static void callbk_calendar_home(GSimpleAction * action, GVariant *parameter, gpointer user_data);
static void callbk_calendar_day_selected(CustomCalendar *calendar, gpointer user_data);
static void callbk_calendar_next_month(CustomCalendar *calendar, gpointer user_data);
static void callbk_calendar_prev_month(CustomCalendar *calendar, gpointer user_data); 
static void callbk_calendar_next_year(CustomCalendar *calendar, gpointer user_data); 
static void callbk_calendar_prev_year(CustomCalendar *calendar, gpointer user_data);

static void set_notables_on_calendar(CustomCalendar *calendar);
static void set_tooltips_on_calendar(CustomCalendar *calendar);
static const char* get_notable_date_text(int year, int month, int day);

int  get_total_number_of_events(void); 
int get_number_of_day_events(void);

// Function prototypes for search functionality
static void callbk_search(GSimpleAction *action, GVariant *parameter, gpointer user_data);
static void callbk_search_events(GtkButton *button, gpointer user_data);
static void callbk_jump_to_search_date(GtkListBox *listbox, GtkListBoxRow *row, gpointer user_data);
static void search_events_summary(const char* search_str, GtkWidget *main_window);
static void search_events_location(const char* search_str, GtkWidget *main_window);

//Function prototypes for timer alarm
static gboolean update_time_label(gpointer data);
static void callbk_alarm_times(GSimpleAction* action, GVariant *parameter,gpointer user_data);
static void callbk_set_alarm_time(GtkButton *button, gpointer  user_data);
static void callbk_spin_alarm_hour(GtkSpinButton *button, gpointer user_data);
static void callbk_spin_alarm_min(GtkSpinButton *button, gpointer user_data);

// Function prototypes for Easter calculation
GDate* calculate_easter(gint year);
static void callbk_calc_easter(GtkButton *button, gpointer user_data);
static void callbk_easter(GSimpleAction *action, GVariant *parameter,  gpointer user_data);

static void callbk_preferences(GSimpleAction* action, GVariant *parameter,gpointer user_data);

static void callbk_about(GSimpleAction * action, GVariant *parameter, gpointer user_data);
static void callbk_info(GSimpleAction *action, GVariant *parameter,  gpointer user_data);

static void callbk_speak(GSimpleAction* action, GVariant *parameter,gpointer user_data);
static void callbk_speaktime(GSimpleAction * action, GVariant *parameter, gpointer user_data);
static void speak_events();
static void speak_time(gint hour, gint min);

//Notable dates
//static void append_notable_date_speech(GString *speak_gstr, int month, int day);
static void append_notable_date_speech(GString *speak_gstr, int year, int month, int day);

GArray*  get_upcoming_array(int upcoming_days);

//voice talker functions
unsigned char *rawcat(unsigned char *arrys[], unsigned int arry_size[], int arry_count);
unsigned int get_merge_size(unsigned int sizes_arry[], int arry_size);

static void play_speak_str(char* speak_str);

static void task_callbk(GObject *gobject,GAsyncResult *res,  gpointer  user_data);

static void play_audio_async (GTask *task,
                          gpointer object,
                          gpointer task_data,
                          GCancellable *cancellable);

static void speak_time(gint hour, gint min);

static char* get_cardinal_string(int number);

static char *ignore_first_zero(char *input);
static gchar* sanitize_text(const gchar* input);

// Function prototypes fto update store
static void update_store(CustomCalendar *calendar, gpointer user_data);
static void callbk_listview (GtkListView *list, guint position, gpointer unused);
static void callbk_setup_listitem (GtkListItemFactory *factory,GtkListItem *list_item);
static void callbk_bind_listitem (GtkListItemFactory *factory, GtkListItem *list_item);

static GMenu *create_menu(const GtkApplication *app); 

char* get_time_str(int hour, int min);

static void callbk_pane_position_changed(GObject *gobject, GParamSpec *pspec, gpointer user_data);

static int m_pane_position = 300; // Default fallback pixel boundary

// Local static exit gate flag. Requires zero heap allocations.
static gboolean app_is_exiting = FALSE;

// Talk preferences
static gboolean m_talk =TRUE;
static gboolean m_talk_at_startup =TRUE;
static gboolean m_talk_time =TRUE;
static gboolean m_talk_event_number=FALSE;
static gboolean m_talk_upcoming=FALSE;
static int m_upcoming_days=7; 
static int m_talk_rate=16000;
static gchar* m_raw_file ="/tmp/textout.raw";

static gboolean m_reset_preferences=FALSE;

//listview preferences
static gboolean m_12hour_format=TRUE; //am pm hour format
static gboolean m_use_end_time=FALSE;
//window size preferences
static int m_window_width=800;
static int m_window_height=600;

static gboolean m_notable_dates = TRUE; // Default to enabled on startup

//calendar preferences
static gboolean m_show_tooltips=TRUE;
static gboolean m_is_dark_theme = FALSE; //global theme variable

static char *m_todaycolour = NULL;
static char *m_eventcolour = NULL;
static char *m_notablecolour = NULL;

static int m_talk_priority=0; //TODO

static int m_start_year=0;
static int m_start_month=0;
static int m_start_day=0;

gboolean m_talking=FALSE; //gtask

//Timer
//static gboolean continue_timer = TRUE;
static int m_alarm_hour=0;
static int m_alarm_min=0;
static gboolean m_alarm_on=TRUE;

static char* m_file_name="talkcalendar.ical"; //import default

// Array of GActionEntry objects for application-level actions
const GActionEntry app_actions[] = {  
	{ "speaktime", callbk_speaktime}, 
	{ "home", callbk_calendar_home}, 
	{ "newevent", callbk_new_event},
	{ "editevent", callbk_edit_event},  
	{ "deleteevent", callbk_delete_event},
	{ "info", callbk_info},
	{ "preferences", callbk_preferences} 
};

const char * const month_strs[] = { 
	"January",	
	"February",	
	"March",
	"April",	
	"May",  
	"June", 
	"July", 
	"August", 
	"September",
	"October", 
	"November",
	"December",		 
	NULL };

//=====================================================================

const char * const events[] = { 
	"Activity",	//0
	"Anniversary",	 //1
	"Appointment",//2
	"Birthday",	//3
	"Cafe",  //4
	"Car", //5
	"Delivery", //6
	"Dentist", //7
	"Doctor", //8
	"Driver", //9
	"Family", //10
	"Funeral",	//11
	"Holiday",//12
	"Hospital",	//13
	"Medical", //14
	"Meeting", //15
	"Meetup", //16
	"Memo",//17
	"Party",//18
	"Payment",//19
	"Project",	//20
	"Reminder", //21
	"Restaurant", //22
	"Sport", //23
	"Task", //24
	"Television", //25
	"Theatre",	//26	
	"Travel",  //27
	"Visit",//28
	"Walk",//29
	"Work", //30
	NULL };

const char* m_summary ="Activity";

//===========================================================
static guint get_dropdown_position_summary(const gchar* summary)
{
	
	guint position=0;
	gchar* summary_lower= g_ascii_strdown(summary,-1);
		
	if (g_strcmp0(summary_lower,"activity")==0) {
	position=0;
	}
	if (g_strcmp0(summary_lower,"anniversary")==0) {
	position=1;
	}	
	if (g_strcmp0(summary_lower,"appointment")==0) {
	position=2;
	}
	if (g_strcmp0(summary_lower,"birthday")==0) {
	position=3;
	}
	
	if (g_strcmp0(summary_lower,"cafe")==0) {
	position=4;
	}
	if (g_strcmp0(summary_lower,"car")==0) {
	position=5;
	}
	if (g_strcmp0(summary_lower,"delivery")==0) {
	position=6;
	}
	if (g_strcmp0(summary_lower,"dentist")==0) {
	position=7;
	}
	if (g_strcmp0(summary_lower,"doctor")==0) {
	position=8;
	}
	if (g_strcmp0(summary_lower,"driver")==0) {
	position=9;
	}
	if (g_strcmp0(summary_lower,"family")==0) {
	position=10;
	}
	if (g_strcmp0(summary_lower,"funeral")==0) {
	position=11;
	}
	if (g_strcmp0(summary_lower,"holiday")==0) {
	position=12;
	}			
	if (g_strcmp0(summary_lower,"hospital")==0) {
	position=13;
	}
	if (g_strcmp0(summary_lower,"medical")==0) {
	position=14;
	}
	if (g_strcmp0(summary_lower,"meeting")==0) {
	position=15;
	}
	if (g_strcmp0(summary_lower,"meetup")==0) {
	position=16;
	}
	if (g_strcmp0(summary_lower,"memo")==0) {
	position=17;
	}
	if (g_strcmp0(summary_lower,"party")==0) {
	position=18;
	}	
	if (g_strcmp0(summary_lower,"payment")==0) {
	position=19;
	}	
	if (g_strcmp0(summary_lower,"project")==0) {
	position=20;
	}
	if (g_strcmp0(summary_lower,"reminder")==0) {
	position=21;
	}
	if (g_strcmp0(summary_lower,"restaurant")==0) {
	position=22;
	}
	if (g_strcmp0(summary_lower,"sport")==0) {
	position=23;
	}
	if (g_strcmp0(summary_lower,"task")==0) {
	position=24;
	}
	if (g_strcmp0(summary_lower,"television")==0) {
	position=25;
	}
	if (g_strcmp0(summary_lower,"theatre")==0) {
	position=26;
	}
	if (g_strcmp0(summary_lower,"travel")==0) {
	position=27;
	}	
	if (g_strcmp0(summary_lower,"visit")==0) {
	position=28;
	}	
	if (g_strcmp0(summary_lower,"walk")==0) {
	position=29;
	}	
	if (g_strcmp0(summary_lower,"work")==0) {
	position=30;
	}	
	return position;
}

//======================================================================
// Save load config file
//======================================================================

/**
 * @brief Loads the default configuration values into global variables.
 */
static void config_load_default()
{
    m_talk = TRUE;
    m_talk_at_startup = FALSE;
    m_talk_event_number = FALSE;
    m_talk_upcoming = FALSE;
    m_upcoming_days = 7;
    m_talk_rate = 16000;

    m_12hour_format = TRUE;
    m_use_end_time = FALSE;
    m_show_tooltips = TRUE;
    m_is_dark_theme = FALSE;
    m_notable_dates = TRUE;
        
	m_alarm_hour = 8;  // Default to 8 AM
	m_alarm_min  = 0;  // Default to 00 minutes
	m_alarm_on   = FALSE; // Keep the alarm switch turned off by default


    // literal pointers: Always duplicate defaults onto the heap!
    g_free(m_todaycolour);
    m_todaycolour = g_strdup("rgb(141,166,141)");
    
    g_free(m_eventcolour);
    m_eventcolour = g_strdup("rgb(217,230,217)");
    
    g_free(m_notablecolour); 
    m_notablecolour = g_strdup("rgb(245,245,220)");//beige  
    //m_notablecolour="rgb(245,245,220)";//beige  
    //m_notablecolour = g_strdup("rgb(222,184,135)");
    
    m_window_width = 800;
    m_window_height = 600;
    
    m_pane_position = 300;
}


/**
 * @brief Reads configuration values from the global config file into global variables.
 */
static void config_read()
{
    GKeyFile *kf = g_key_file_new();
    if (!g_key_file_load_from_file(kf, m_config_file, G_KEY_FILE_NONE, NULL)) {
        g_key_file_free(kf);
        return;
    }
    m_talk = g_key_file_get_boolean(kf, "calendar_settings", "talk", NULL);
    m_talk_at_startup = g_key_file_get_boolean(kf, "calendar_settings", "talk_startup", NULL);
    m_talk_event_number = g_key_file_get_boolean(kf, "calendar_settings", "talk_event_number", NULL);
    m_talk_upcoming = g_key_file_get_boolean(kf, "calendar_settings", "talk_upcoming", NULL);
    m_upcoming_days = g_key_file_get_integer(kf, "calendar_settings", "upcoming_days", NULL);
    m_talk_rate = g_key_file_get_integer(kf, "calendar_settings", "talk_rate", NULL);
    m_12hour_format = g_key_file_get_boolean(kf, "calendar_settings", "hour_format", NULL);
    m_use_end_time = g_key_file_get_boolean(kf, "calendar_settings", "show_end_time", NULL);
    m_show_tooltips = g_key_file_get_boolean(kf, "calendar_settings", "show_tooltips", NULL);
    m_is_dark_theme = g_key_file_get_boolean(kf, "calendar_settings", "dark_theme", NULL);
    
    m_notable_dates = g_key_file_get_boolean(kf, "calendar_settings", "notable_dates", NULL);

        
	m_alarm_hour = g_key_file_get_integer(kf, "calendar_settings", "alarm_hour", NULL);
	m_alarm_min  = g_key_file_get_integer(kf, "calendar_settings", "alarm_min", NULL);
	m_alarm_on   = g_key_file_get_boolean(kf, "calendar_settings", "alarm_on", NULL);

    // Secure intermediate assignments safely via temporary tracking pointers
    gchar *today_tmp = g_key_file_get_string(kf, "calendar_settings", "todaycolour", NULL);
    if (today_tmp) {
        g_free(m_todaycolour);
        m_todaycolour = today_tmp;
    }
    gchar *event_tmp = g_key_file_get_string(kf, "calendar_settings", "eventcolour", NULL);
    if (event_tmp) {
        g_free(m_eventcolour);
        m_eventcolour = event_tmp;
    }
    
    
    gchar *notable_tmp = g_key_file_get_string(kf, "calendar_settings", "notablecolour", NULL);
    if (notable_tmp) {
        g_free(m_notablecolour);
        m_notablecolour = notable_tmp;
    }
    
    m_window_width = g_key_file_get_integer(kf, "calendar_settings", "window_width", NULL);
    m_window_height = g_key_file_get_integer(kf, "calendar_settings", "window_height", NULL);  
    
    m_pane_position = g_key_file_get_integer(kf, "calendar_settings", "pane_position", NULL);
	if (m_pane_position <= 0) m_pane_position = 300; // Fallback check
      
    g_key_file_free(kf);
}

//======================================================================

/**
 * @brief Writes the current global configuration values to a GKeyFile.
 */
void config_write()
{
	
	GKeyFile * kf = g_key_file_new();
	//talk general	
	g_key_file_set_boolean(kf, "calendar_settings", "talk", m_talk);	
	g_key_file_set_boolean(kf, "calendar_settings", "talk_startup", m_talk_at_startup);
	
	g_key_file_set_boolean(kf, "calendar_settings", "talk_event_number", m_talk_event_number);
	
	g_key_file_set_boolean(kf, "calendar_settings", "talk_upcoming", m_talk_upcoming);
	g_key_file_set_integer(kf, "calendar_settings", "upcoming_days", m_upcoming_days);
	g_key_file_set_integer(kf, "calendar_settings", "talk_rate", m_talk_rate);	
		
	//listview
	g_key_file_set_boolean(kf, "calendar_settings", "hour_format", m_12hour_format);
	g_key_file_set_boolean(kf, "calendar_settings", "show_end_time", m_use_end_time);
	
	//calendar
	g_key_file_set_boolean(kf, "calendar_settings", "show_tooltips", m_show_tooltips);
	g_key_file_set_boolean(kf, "calendar_settings", "dark_theme", m_is_dark_theme);
	
	g_key_file_set_string(kf, "calendar_settings", "todaycolour", m_todaycolour);
	g_key_file_set_string(kf, "calendar_settings", "eventcolour", m_eventcolour);
	g_key_file_set_string(kf, "calendar_settings", "notablecolour", m_notablecolour);	
	
	g_key_file_set_boolean(kf, "calendar_settings", "notable_dates", m_notable_dates);

	
	//alarm	
	g_key_file_set_integer(kf, "calendar_settings", "alarm_hour", m_alarm_hour);
	g_key_file_set_integer(kf, "calendar_settings", "alarm_min", m_alarm_min);
	g_key_file_set_boolean(kf, "calendar_settings", "alarm_on", m_alarm_on);

		
	//window size	
	g_key_file_set_integer(kf, "calendar_settings", "window_width", m_window_width);
	g_key_file_set_integer(kf, "calendar_settings", "window_height", m_window_height); 
	g_key_file_set_integer(kf, "calendar_settings", "pane_position", m_pane_position);

	
	gsize length;
	gchar * data = g_key_file_to_data(kf, &length, NULL);
	g_file_set_contents(m_config_file, data, -1, NULL);
	g_free(data);
	g_key_file_free(kf);
}
//======================================================================
/**
 * @brief Initializes the configuration, creating a default file if none exists.
 */
void config_initialize()
{
	gchar *config_dir = g_build_filename(g_get_user_config_dir(), CONFIG_DIRNAME, NULL);
	m_config_file = g_build_filename(config_dir, CONFIG_FILENAME, NULL);
	
	// Make sure config directory exists
	if (!g_file_test(config_dir, G_FILE_TEST_IS_DIR))
	// If a config file doesn't exist, create one with defaults
	g_mkdir(config_dir, 0777);
	// otherwise read the existing one
	if (!g_file_test(m_config_file, G_FILE_TEST_EXISTS))
	{
	config_load_default();
	config_write();
	}
	else
	{
	config_read();
	}	
	g_free(config_dir);
}
//======================================================================

/**
 * @brief Gets a formatted time string (e.g., "10:30" or "10:30 am").
 * @param hour The hour.
 * @param min The minute.
 * @return A newly allocated time string. The caller is responsible for freeing this.
 */
char* get_time_str(int hour, int min)
{
    char *hour_str = NULL;
    char *min_str = NULL;
    const char *ampm_str = "";
    char *result_time_str = NULL;

    if (m_12hour_format)
    {
        if (hour == 0) // 12am midnight
        {
            ampm_str = "am ";
            hour_str = g_strdup_printf("%d", 12);
        }
        else if (hour >= 13 && hour <= 23)
        {
            ampm_str = "pm ";
            hour_str = g_strdup_printf("%d", hour - 12);
        }
        else if (hour == 12)
        {
            ampm_str = "pm ";
            hour_str = g_strdup_printf("%d", hour);
        }
        else // 1am to 11am
        {
            ampm_str = "am ";
            hour_str = g_strdup_printf("%d", hour);
        }
    }
    else // 24-hour format
    {
        hour_str = g_strdup_printf("%02d", hour);
    }

    min_str = g_strdup_printf("%02d", min);

    // Build the final target string cleanly in one pass to avoid overwriting pointers
    if (m_12hour_format)
    {
        result_time_str = g_strconcat(hour_str, ":", min_str, " ", ampm_str, NULL);
    }
    else
    {
        result_time_str = g_strconcat(hour_str, ":", min_str, " ", NULL);
    }

    // Clean up temporary formatting heap buffers used in this local step
    g_free(hour_str);
    g_free(min_str);

    // The caller is responsible for freeing this returned string using g_free()
    return result_time_str;
}

/**
 * @brief Gets the string representation of a day of the week.
 * @param day The day of the month.
 * @param month The month.
 * @param year The year.
 * @return A string representing the day of the week.
 */
static char* get_day_of_week(int day, int month, int year) 
{
    char* weekday_str = "";
    GDate* day_date = g_date_new_dmy(day, month, year);
    
    if (day_date) {
        GDateWeekday weekday = g_date_get_weekday(day_date);
        switch(weekday)
        {
            case G_DATE_MONDAY:    weekday_str = "monday";    break;
            case G_DATE_TUESDAY:   weekday_str = "tuesday";   break;
            case G_DATE_WEDNESDAY: weekday_str = "wednesday"; break;
            case G_DATE_THURSDAY:  weekday_str = "thursday";  break;
            case G_DATE_FRIDAY:    weekday_str = "friday";    break;
            case G_DATE_SATURDAY:  weekday_str = "saturday";  break;
            case G_DATE_SUNDAY:    weekday_str = "sunday";    break;
            default:               weekday_str = "unknown";   break;
        }
        // Clean up the object context immediately before returning!
        g_date_free(day_date);
    }
    return weekday_str;
}

/**
 * @brief Gets the string name of a month.
 * @param month The month number.
 * @return The name of the month as a string.
 */
char* get_month_string(int month) {

	char* result ="";
	
	switch(month) {
	case 1:
		result = "january";
		break;
	case 2:
		result = "february";
		break;
	case 3:
		result= "march";
		break;
	case 4:
		result = "april";
		break;
	case 5:
		result ="may";
		break;
	case 6:
		result = "june";
		break;
	case 7:
		result ="july";
		break;
	case 8:
		result ="august";
		break;
	case 9:
		result= "september";
		break;
	case 10:
		result = "october";
		break;
	case 11:
		result = "november";
		break;
	case 12:
		result = "december";
		break;
	default:
		result = "unknown";
	}
	return result;
}

/**
 * @brief Gets the ordinal string for a day number (e.g., "first", "second").
 * @param day The day number.
 * @return the ordinal string.
 */
static char* get_day_number_ordinal_string(int day) 
{

	char* day_str ="";

	switch (day) {
		case 1:
		day_str="first";
		break;
		case 2:
		day_str="second";
		break;
		case 3:
		day_str="third";
		break;
		case 4:
		day_str="fourth";
		break;
		case 5:
		day_str="fifth";
		break;
		case 6:
		day_str="sixth";
		break;
		case 7:
		day_str="seventh";
		break;
		case 8:
		day_str="eighth";
		break;
		case 9:
		day_str="ninth";
		break;
		case 10:
		day_str="tenth";
		break;
		case 11:
		day_str="eleventh";
		break;
		case 12:
		day_str="twelfth";
		break;
		case 13:
		day_str="thirteenth";
		break;
		case 14:
		day_str="fourteenth";
		break;
		case 15:
		day_str="fifteenth";

		break;
		case 16:
		day_str="sixteenth";
		break;
		case 17:
		day_str="seventeenth";
		break;
		case 18:
		day_str="eighteenth";
		break;
		case 19:
		day_str="nineteenth";
		break;
		case 20:
		day_str="twentieth"; //twentieth
		break;
		case 21:
		day_str="twenty first";
		break;
		case 22:
		day_str="twenty second";
		break;
		case 23:
		day_str="twenty third";
		break;
		case 24:
		day_str="twenty fourth";
		break;
		case 25:
		day_str="twenty fifth";
		break;
		case 26:
		day_str="twenty sixth";
		break;
		case 27:
		day_str="twenty seventh";
		break;
		case 28:
		day_str="twenty eighth";
		break;
		case 29:
		day_str="twenty ninth";
		break;
		case 30:
		day_str="thirtieth";
		break;
		case 31:
		day_str="thirty first";
		break;
		default:
		//Unknown day ordinal
		day_str="unknown";
		break;
	  } //day switch
	return day_str;
}

/**
 * @brief Gets the cardinal string for a day number (e.g., "one", "tow").
 * @param day The day number.
 * @return the cardinal string.
 */
static char* get_cardinal_string(int number)
{
	char* result ="zero";
     switch(number)
     {
         case 0:
          result = "zero";
          break;
         case 1:
		 result ="one";
		 break;
		 case 2:
		 result ="two";
		 break;
		 case 3:
		 result = "three";
		 break;
		 case 4:
		 result ="four";
		 break;
		 case 5:
		 result ="five";
		 break;
		 case 6:
		 result ="six";
		 break;
		 case 7:
		 result ="seven";
		 break;
		 case 8:
		 result="eight";
		 break;
		 case 9:
		 result="nine";
		 break;
		 case 10:
		 result="ten";
		 break;
		 case 11:
		 result="eleven";
		 break;
		 case 12:
		 result="twelve";
		 break;
		 case 13:
		 result="thirteen";
		 break;
		 case 14:
		 result ="fourteen";
		 break;
		 case 15:
		 result ="fifteen";
		 break;
		 case 16:
		 result="sixteen";
		 break;
		 case 17:
		 result="seventeen";
		 break;
		 case 18:
		 result="eighteen";
		 break;
		 case 19:
		 result="nineteen";
		 break;
		 case 20:
		 result ="twenty";
		 break;
		 case 21:
		 result="twenty one";
		 break;
		 case 22:
		 result="twenty two";
		 break;
		 case 23:
		 result="twenty three";
		 break;
		 case 24:
		 result="twenty four";
		 break;
		 case 25:
		 result="twenty five";
		 break;
		 case 26:
		 result="twenty six";
		 break;
		 case 27:
		 result="twenty seven";
		 break;
		 case 28:
		 result="twenty eight";
		 break;
		 case 29:
		 result="twenty nine";
		 break;
		 case 30:
		 result="thirty";
		 break;
		 case 31:
		 result="thirty one";
		 break;
		 case 32:
		 result="thirty two";
		 break;
		 case 33:
		 result="thirty three";
		 break;
		 case 34:
		 result="thirtyfour";
		 break;
		 case 35:
		 result="thirty five";
		 break;
		 case 36:
		 result="thirty six";
		 break;
		 case 37:
		 result="thirty seven";
		 break;
		 case 38:
		 result="thirty eight";
		 break;
		 case 39:
		 result="thirty nine";
		 break;
		 case 40:
		 result="forty";
		 break;
		 case 41:
		 result="forty one";
		 break;
		 case 42:
		 result="forty two";
		 break;
		 case 43:
		 result="forty three";
		 break;
		 case 44:
		 result="forty four";
		 break;
		 case 45:
		 result="forty five";
		 break;
		 case 46:
		 result="forty six";
		 break;
		 case 47:
		 result="forty seven";
		 break;
		 case 48:
		 result="forty eight";
		 break;
		 case 49:
		 result="forty nine";
		 break;
		 case 50:
		 result="fifty";
		 break;
		 case 51:
		 result="fifty one";
		 break;
		 case 52:
		 result="fifty two";
		 break;
		 case 53:
		 result="fifty three";
		 break;
		 case 54:
		 result="fifty four";
		 break;
		 case 55:
		 result="fifty five";
		 break;
		 case 56:
		 result="fifty six";
		 break;
		 case 57:
		 result="fifty seven";
		 break;
		 case 58:
		 result="fifty eight";
		 break;
		 case 59:
		 result="fifty nine";
		 break;  
         default:
           g_print ("default: number is: %i\n", number);
	 }//switch start hour
	return result;
}

//======================================================================
/**
 * @brief Removes the leading '0' from a string, if present.
 * @param input The input string.
 * @return The modified string, which is a pointer to the second character if the first was '0'.
 */
static char *ignore_first_zero(char *input)
{    
	int len = strlen(input); 
	if(len > 0)
	{
	gunichar fc = g_utf8_get_char(input);
	if (fc == '0')
	{ 	
	input++;	
	} // if
	}
	return input;
}

/**
 * @brief santizes text for speech synthesizer and insertion into database
 * removes all punctuation except letters and spaces
 * @param input_text The null-terminated string to sanitize.
 * @return A new, dynamically allocated string with forbidden characters removed,
 *  or NULL if the input is NULL or memory allocation fails.
 */
static gchar* sanitize_text(const gchar* input)
{
    // Function to sanitize text by removing all punctuation except letters and spaces
    if (!input) return NULL;    
    // Create a copy of the input string
    gchar *sanitized = g_strdup(input);
    gsize len = strlen(sanitized);    
    // Remove all punctuation marks from the text (keep letters, numbers, and spaces)
    gchar *write_ptr = sanitized;
    const gchar *read_ptr = sanitized;
    
    while (*read_ptr) {
        if (isalpha(*read_ptr) || isdigit(*read_ptr) || isspace(*read_ptr)) {
            // Keep letters, digits, and spaces
            *write_ptr = *read_ptr;
            write_ptr++;
        }
        read_ptr++;
    }
    
    // Null terminate the string
    *write_ptr = '\0';
    
    // Trim leading and trailing whitespace
    gchar *start = sanitized;
    while (isspace(*start)) {
        start++;
    }
    
    // Trim trailing whitespace
    gchar *end = write_ptr - 1;
    while (end > start && isspace(*end)) {
        *end = '\0';
        end--;
    }
    
    // Handle case where string becomes empty
    if (start >= write_ptr) {
        sanitized[0] = '\0';
        return sanitized;
    }
    
    // If we need to shift the string to remove leading whitespace
    if (start > sanitized) {
        memmove(sanitized, start, strlen(start) + 1);
    }
    
    return sanitized;
}

/**
 * @brief checks if a file exists
 * @param the file name.
 * @return boolean TRUE if exists
 */
gboolean file_exists(const char *file_name)
{
    FILE *file;
    file = fopen(file_name, "r");
    if (file){       
        fclose(file);
        return TRUE; //file exists return 1
    }
    return FALSE; //file does not exist
}

/**
 * @brief This function plays the speak string.
 */
static void play_speak_str(char* speak_str)
{ 
    if (!speak_str || strlen(speak_str) == 0) return;

    GList *speak_word_list = NULL; 
    gchar** word_str = g_strsplit (speak_str, " ", 0); // splits string on space
    if (!word_str) return;

    int j = 0; 
    while (word_str[j] != NULL) {
        g_strstrip(word_str[j]); // Ensure no trailing hidden spaces remain
        if (strlen(word_str[j]) > 0) {
            char* word = g_ascii_strdown(word_str[j], -1); // Allocates string block
            speak_word_list = g_list_append(speak_word_list, word); 
        }
        j++;
    } 

    // Protect against empty sequences
    if (!speak_word_list) {
        g_strfreev(word_str);
        return;
    } 

    // Appending the fallback token cleanly without breaking list head references
    if (g_list_length(speak_word_list) == 1) {
        speak_word_list = g_list_append(speak_word_list, g_strdup("space"));
    } 

    gint word_number = g_list_length(speak_word_list); 
    
    // Statically allocated pointers layout arrays
    unsigned char *word_arrays[word_number]; 
    unsigned int word_arrays_sizes[word_number]; 

    // Process matching maps onto voice3 static arrays
    get_words_array(speak_word_list, word_number, word_arrays, word_arrays_sizes); 

    // Concatenate files using raw audio utilities
    unsigned char *data = rawcat(word_arrays, word_arrays_sizes, word_number); 
    unsigned int data_len = get_merge_size(word_arrays_sizes, word_number); 

    if (data) {
        FILE* f = fopen(m_raw_file, "w");
        if (f) {
            fwrite(data, data_len, 1, f);
            fclose(f); 
        } 
        // free data array as no longer needed once written to disk.
        free(data); 
    }

    // spin up the independent audio hardware thread
    GTask* task = g_task_new(NULL, NULL, task_callbk, NULL);
    g_task_run_in_thread(task, play_audio_async); 
    g_object_unref(task); 

    // --- CLEANUP SECTION --- 
    // Free data strings inside list nodes to clear string allocations completely
    for (GList *l = speak_word_list; l != NULL; l = l->next) {
        if (l->data) {
            g_free(l->data);
            l->data = NULL;
        }
    }
    // Free list structure nodes
    g_list_free(speak_word_list); 
    
    // Free the string array allocated by g_strsplit
    g_strfreev(word_str); 
}

/**
 * @brief This function is the speech completion callback. 
 * @param source_object The GObject that initiated the task (unused).
 * @param result The GAsyncResult object, which is a GTask in this case.
 * @param user_data pointer to the user data passed to g_task_new (unsued)
 */ 
static void task_callbk(GObject *gobject,GAsyncResult *res,  gpointer  user_data)
{		
    m_talking=FALSE; 
   
}

/**
 * @brief background thread managed by GTask for playing speech
 * @param task The GTask object.
 * @param source_object The GObject that initiated the task (unused).
 * @param task_data A pointer to the AudioTaskData structure.
 * @param cancellable A GCancellable object (unused).
 */
static void play_audio_async (GTask *task,
                              gpointer object,
                              gpointer task_data,
                              GCancellable *cancellable)
{
    m_talking = TRUE; // stop any new speaking 
 
    gchar *m_sample_rate_str = g_strdup_printf("%i", m_talk_rate); 
    gchar *sample_rate_str = "-r "; 
    
    // Capture concat cleanly to avoid dropping the pointer reference link
    gchar *full_rate_param = g_strconcat(sample_rate_str, m_sample_rate_str, NULL); 
    gchar * command_str ="aplay -c 1 -f S16_LE";
    //gchar *command_str = "aplay -c 1 -f U8";
    gchar *full_command = g_strconcat(command_str, " ", full_rate_param, " ", m_raw_file, NULL); 
    
    system(full_command); 
 
    // --- Clear all concatenated audio thread overhead ---
    g_free(m_sample_rate_str);
    g_free(full_rate_param);
    g_free(full_command);
    
    g_task_return_boolean(task, TRUE);
}

/**
 * @brief Concatenates an array of raw binary byte buffers into a single allocated heap memory block.
 * 
 * This highly optimized utility function calculates the combined sizing requirements for a 
 * collection of contiguous byte sequences and allocates a unified block on the heap. It uses 
 * standard high-performance memcpy() blocks instead of manual element-by-element loops to 
 * transfer data at near-hardware speeds, making it ideal for processing large datasets.
 * 
 * @note The caller assumes complete ownership of the returned pointer and is fully 
 *       responsible for releasing it via standard free() to prevent memory leaks.
 *
 * @param arrys      An array of pointers pointing to individual input byte buffers.
 * @param arry_size  An array containing the precise sizes (in bytes) of each sub-buffer in @p arrys.
 * @param arry_count The total number of distinct buffers passed inside the collection array.
 * 
 * @return A pointer to the newly allocated concatenated byte array, or NULL if @p arry_count is less than 2.
 */
unsigned char *rawcat(unsigned char *arrys[], unsigned int arry_size[], int arry_count) {    
    if (arry_count < 2 || arrys == NULL || arry_size == NULL) {
        return NULL;    
    }

    unsigned int total_samples = 0;
    for (int c = 0; c < arry_count; c++) {  
        total_samples += arry_size[c]; 
    }        

    // Guard against allocating an empty block if all buffer sizes happen to be zero
    if (total_samples == 0) {
        return NULL;
    }

    unsigned char *data = (unsigned char*)malloc(total_samples * sizeof(unsigned char));
    if (data == NULL) {
        return NULL; // System out-of-memory protection fallback
    }

    unsigned int offset = 0;
    for (int k = 0; k < arry_count; k++) {
        // Skip empty source arrays securely without breaking the destination offset map
        if (arry_size[k] == 0 || arrys[k] == NULL) {
            continue;
        }

        // Copy the entire buffer instantly at hardware vector speeds
        memcpy(data + offset, arrys[k], arry_size[k]);
        
        offset += arry_size[k];
    }

    return data;
}

/**
 * @brief Calculates the total aggregate size of multiple memory buffers combined.
 * 
 * This helper function iterates through an array of buffer sizes and accumulates 
 * their values to compute the total size required for a merged array allocation. 
 * It is commonly used as a pre-allocation step before invoking functions like rawcat().
 *
 * @param sizes_arry An array containing the individual sizes (in bytes or samples) of each buffer.
 * @param arry_size  The total number of size elements stored within @p sizes_arry.
 * 
 * @return The sum total of all size counts tracked inside the array.
 */
unsigned int get_merge_size(unsigned int sizes_arry[], int arry_size) {	
	unsigned int total_samples=0;
	for (int i = 0; i < arry_size; i++) 
	{  
    unsigned int count =sizes_arry[i]; 
    total_samples=total_samples+count;	
    }
	return total_samples;
}

/**
 * @brief Callback function for getting m_summary from dropdown .
 * @param GtkDropDown the dropdown
 * @param user_data
 */
static void callbk_dropdown_summary(GtkDropDown* self, gpointer user_data)
{	
	m_summary = gtk_string_object_get_string (GTK_STRING_OBJECT (gtk_drop_down_get_selected_item (self)));	
}


/**
 * @brief Callback function for the "Add Event" button.
 * It retrieves data from dialog widgets, sanitizes it, and inserts a new event into the database.
 * @param button The GtkButton that triggered the callback.
 * @param user_data A pointer to the GListStore.
 */
static void callbk_add_new_event(GtkButton *button, gpointer user_data)
{	
	
	g_return_if_fail(GTK_IS_BUTTON(button));
	GListStore *store =user_data;	
	GtkWidget *dialog = g_object_get_data(G_OBJECT(button), "dialog-key");	
	GtkWidget *window = g_object_get_data(G_OBJECT(button), "button-add-window-key");
	GtkWidget *calendar = g_object_get_data(G_OBJECT(button), "button-add-calendar-key");		
	GtkWidget *label_date =g_object_get_data(G_OBJECT(window), "window-label-date-key");
			
	int start_day =GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "day-key"));
	int start_month =GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "month-key"));
	int start_year =GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "year-key"));
	
	int end_day =start_day;
	int end_month =start_month;
	int end_year =start_year;
			
	GtkWidget *entry_description = g_object_get_data(G_OBJECT(button), "entry-description-key");
	GtkWidget *entry_location = g_object_get_data(G_OBJECT(button), "entry-location-key");
	
	GtkWidget *spin_button_day= g_object_get_data(G_OBJECT(button), "spin-day-key");
	GtkWidget *spin_button_month= g_object_get_data(G_OBJECT(button), "spin-month-key");
	GtkWidget *spin_button_year= g_object_get_data(G_OBJECT(button), "spin-year-key");
	
	GtkWidget *spin_button_start_hour = g_object_get_data(G_OBJECT(button), "spin-start-hour-key");
	GtkWidget *spin_button_start_min = g_object_get_data(G_OBJECT(button), "spin-start-min-key");
	GtkWidget *spin_button_end_hour = g_object_get_data(G_OBJECT(button), "spin-end-hour-key");
	GtkWidget *spin_button_end_min = g_object_get_data(G_OBJECT(button), "spin-end-min-key");
		
	GtkEntryBuffer *buffer_summary;	
	GtkEntryBuffer *buffer_description;
	GtkEntryBuffer *buffer_location;	
		
	GtkWidget *check_button_allday = g_object_get_data(G_OBJECT(button), "check-button-allday-key");
	GtkWidget *check_button_isyearly = g_object_get_data(G_OBJECT(button), "check-button-isyearly-key");
	GtkWidget *check_button_priority = g_object_get_data(G_OBJECT(button), "check-button-priority-key");
			
    //m_summary set by dropdown
		
	buffer_description = gtk_entry_get_buffer(GTK_ENTRY(entry_description));
	const char* description = gtk_entry_buffer_get_text(buffer_description);	
	char* clean_description = sanitize_text(description);
	
	buffer_location = gtk_entry_get_buffer(GTK_ENTRY(entry_location));
	const char* location = gtk_entry_buffer_get_text(buffer_location);
	location = gtk_entry_buffer_get_text(buffer_location);	
	char* clean_location = sanitize_text(location);
	
	int start_hour= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_start_hour));
	int start_min= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_start_min));
	int end_hour= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_end_hour));
	int end_min= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_end_min));
	
	int is_allday = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_allday));	
	int is_yearly = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_isyearly));	
	int is_priority = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_priority));
	
	CalendarEvent *new_event= g_object_new(CALENDAR_TYPE_EVENT,0);
		
	g_object_set(new_event, "summary", g_strdup(m_summary), NULL);
	g_object_set(new_event, "location", g_strdup(clean_location), NULL);
	g_object_set(new_event, "description", g_strdup(clean_description), NULL);
	g_object_set(new_event, "startyear", start_year, NULL);
	g_object_set(new_event, "startmonth", start_month, NULL);
	g_object_set(new_event, "startday", start_day, NULL);
	g_object_set(new_event, "starthour", start_hour, NULL);
	g_object_set(new_event, "startmin", start_min, NULL);
	g_object_set(new_event, "endyear", end_year, NULL); // to do
	g_object_set(new_event, "endmonth", end_month, NULL);
	g_object_set(new_event, "endday", end_day, NULL);
	g_object_set(new_event, "endhour", end_hour, NULL);
	g_object_set(new_event, "endmin", end_min, NULL);
	g_object_set(new_event, "isyearly", is_yearly, NULL);
	g_object_set(new_event, "isallday", is_allday, NULL);			
	g_object_set(new_event, "ispriority", is_priority, NULL);
	
	//insert event into database
	int new_id = db_insert_event(db_handle, new_event);
    if (new_id != -1) {
        //g_print("Successfully appended new event with ID: %d\n", new_id);
    } else {
        g_warning("Failed to append new event.\n");
    }
    g_object_unref(new_event);
	    
    if (clean_location != NULL) {
       
        // free the memory that was allocated by the function
        // to prevent a memory leak.
        free(clean_location);
        clean_location = NULL; // Best practice to set the pointer to NULL after freeing.
    }
    
    if (clean_description != NULL) {
       
        //free the memory that was allocated by the function
        // to prevent a memory leak.
        free(clean_description);
        clean_description = NULL; // Best practice to set the pointer to NULL after freeing.
    }
		
	set_tooltips_on_calendar(CUSTOM_CALENDAR(calendar));		
	custom_calendar_update (CUSTOM_CALENDAR(calendar));
	update_store(CUSTOM_CALENDAR(calendar), store);		
	gtk_window_destroy(GTK_WINDOW(dialog));
}

/**
 * @brief Callback function to create and show a new event dialog.
 * @param action The GSimpleAction that triggered the callback.
 * @param parameter The GVariant parameter (unused).
 * @param user_data A pointer to the GListStore.
 */
static void callbk_new_event(GSimpleAction *action, GVariant *parameter,  gpointer user_data)
{	
	GListStore *store =user_data;  //gpointer is the store
	GtkWidget *window = g_object_get_data(G_OBJECT(store), "store-window-key");
	GtkWidget *calendar = g_object_get_data(G_OBJECT(store), "store-calendar-key");
		
	g_print("Date is : %d-%d-%d \n", m_start_day, m_start_month,m_start_year);
	char* day_str = g_strdup_printf("%d",m_start_day);
	char* month_str = g_strdup_printf("%d",m_start_month);
	char* year_str = g_strdup_printf("%d",m_start_year);
	char* date_str="";
	date_str= g_strconcat(date_str, day_str, "-",month_str, "-",year_str, NULL);
	
	GtkWidget *dialog;
	GtkWidget *button_add_event;	
	GtkWidget *grid;
	GtkWidget *label_date;	
	GtkWidget *label_summary;
	
	GtkWidget *dropdown_summary;
		
	GtkWidget *label_description;
	GtkWidget *entry_description;	
	GtkWidget *label_location;
	GtkWidget *entry_location;
	
	GtkWidget *label_spacer1;
	GtkWidget *label_spacer2;
	GtkWidget *label_spacer3;
	GtkWidget *label_spacer4;
		
	// Check buttons
	GtkWidget *check_button_allday;	
	GtkWidget *check_button_isyearly;
	GtkWidget *check_button_priority;
	
	GtkWidget *label_start_time;
	GtkWidget *spin_button_start_hour;	
	GtkWidget *spin_button_start_min;
	//end time
	GtkWidget *label_end_time;
	GtkWidget *spin_button_end_hour;	
	GtkWidget *spin_button_end_min;	
	
	dialog = gtk_window_new(); 
	gtk_window_set_title(GTK_WINDOW(dialog), "New Event");
	
	label_date =gtk_label_new("");
	gtk_label_set_text(GTK_LABEL(label_date), date_str);
	
	
	//time spin adjustments	
	GtkAdjustment *adjustment_start_hour = gtk_adjustment_new(1.00, 0.0, 23.00, 1.0, 1.0, 0.0);
	GtkAdjustment *adjustment_start_min= gtk_adjustment_new(0.00, 0.0, 59.00, 1.0, 1.0, 0.0);
	
	GtkAdjustment *adjustment_end_hour = gtk_adjustment_new(1.00, 0.0, 23.00, 1.0, 1.0, 0.0);
	GtkAdjustment *adjustment_end_min = gtk_adjustment_new(0.00, 0.0, 59.00, 1.0, 1.0, 0.0);
	
	label_spacer1 = gtk_label_new("");
	label_spacer2 = gtk_label_new("");
	label_spacer3 = gtk_label_new("");
	label_spacer4 = gtk_label_new("");
	
	button_add_event = gtk_button_new_with_label ("Add Event");

	g_signal_connect (GTK_BUTTON (button_add_event),"clicked", G_CALLBACK (callbk_add_new_event),store);
	g_object_set_data(G_OBJECT(button_add_event), "button-add-window-key",window);
	g_object_set_data(G_OBJECT(button_add_event), "button-add-calendar-key",calendar);
		
	grid = gtk_grid_new();	
	gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	//Times
	//start time
	label_start_time =gtk_label_new("Start Time: ");
	spin_button_start_hour = gtk_spin_button_new(adjustment_start_hour, 1.0, 0);
	spin_button_start_min = gtk_spin_button_new(adjustment_start_min, 1.0, 0);
	//end time
	label_end_time =gtk_label_new("End Time: ");		
	spin_button_end_hour = gtk_spin_button_new(adjustment_end_hour, 1.0, 0);
	spin_button_end_min = gtk_spin_button_new(adjustment_end_min, 1.0, 0);
	
	//Summary dropdown		
	label_summary = gtk_label_new("Summary: ");	
	dropdown_summary =gtk_drop_down_new_from_strings(events);    
    g_signal_connect(GTK_DROP_DOWN(dropdown_summary), "notify::selected", G_CALLBACK(callbk_dropdown_summary), NULL);
		
	//description
	label_description = gtk_label_new("Description: ");
	entry_description = gtk_entry_new();
	gtk_entry_set_has_frame(GTK_ENTRY(entry_description),TRUE); 
	gtk_entry_set_max_length(GTK_ENTRY(entry_description), 100);
	
	//location
	label_location = gtk_label_new("Location: ");
	entry_location = gtk_entry_new();
	gtk_entry_set_has_frame(GTK_ENTRY(entry_location),TRUE); 
	gtk_entry_set_max_length(GTK_ENTRY(entry_location), 100);
	
	// check buttons
	check_button_allday = gtk_check_button_new_with_label("Is All Day");	
	check_button_isyearly = gtk_check_button_new_with_label("Is Yearly");
	check_button_priority = gtk_check_button_new_with_label("Is High Priority");
	
	g_object_set_data(G_OBJECT(button_add_event), "day-key",GINT_TO_POINTER(m_start_day));
	g_object_set_data(G_OBJECT(button_add_event), "month-key",GINT_TO_POINTER(m_start_month));
	g_object_set_data(G_OBJECT(button_add_event), "year-key",GINT_TO_POINTER(m_start_year));
	
	g_object_set_data(G_OBJECT(button_add_event), "dialog-key",dialog);
	g_object_set_data(G_OBJECT(button_add_event), "window-key",window);

	g_object_set_data(G_OBJECT(button_add_event), "entry-location-key", entry_location);	
	g_object_set_data(G_OBJECT(button_add_event), "entry-description-key", entry_description);
			
	g_object_set_data(G_OBJECT(button_add_event), "spin-start-hour-key", spin_button_start_hour);
	g_object_set_data(G_OBJECT(button_add_event), "spin-start-min-key", spin_button_start_min);
	g_object_set_data(G_OBJECT(button_add_event), "spin-end-hour-key", spin_button_end_hour);
	g_object_set_data(G_OBJECT(button_add_event), "spin-end-min-key", spin_button_end_min);
	
	g_object_set_data(G_OBJECT(button_add_event), "check-button-allday-key", check_button_allday);	
	g_object_set_data(G_OBJECT(button_add_event), "check-button-isyearly-key", check_button_isyearly);
	g_object_set_data(G_OBJECT(button_add_event), "check-button-priority-key", check_button_priority);
	
	gtk_grid_attach(GTK_GRID(grid), label_date, 1, 1, 1, 1);
	
	gtk_grid_attach(GTK_GRID(grid), label_summary, 1, 2, 1, 1);

	gtk_grid_attach(GTK_GRID(grid), dropdown_summary, 2, 2, 1, 1);
	
	gtk_grid_attach(GTK_GRID(grid), label_description, 1, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), entry_description, 2, 3, 3, 1);
	
	gtk_grid_attach(GTK_GRID(grid), label_location, 1, 4, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), entry_location, 2, 4, 3, 1);
	
	gtk_grid_attach(GTK_GRID(grid), label_spacer1,       1, 5, 3, 1);
		
	//start time
	gtk_grid_attach(GTK_GRID(grid), label_start_time,       1, 6, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), spin_button_start_hour,  2, 6, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), spin_button_start_min,   3, 6, 1, 1);
	//end time
	gtk_grid_attach(GTK_GRID(grid), label_end_time,        1, 7, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), spin_button_end_hour,  2, 7, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), spin_button_end_min,   3, 7, 1, 1);
	
	gtk_grid_attach(GTK_GRID(grid), label_spacer2,       1, 8, 3, 1);
	
	gtk_grid_attach(GTK_GRID(grid), check_button_allday,        1, 9, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), check_button_isyearly,      2, 9, 1, 1);  
	gtk_grid_attach(GTK_GRID(grid), check_button_priority,      3, 9, 1, 1);
	
	gtk_grid_attach(GTK_GRID(grid), label_spacer4,       1, 10, 3, 1);
	
	gtk_grid_attach(GTK_GRID(grid), button_add_event,  1, 11, 4, 1);
	
	g_free(day_str);
    g_free(month_str);
    g_free(year_str);
    g_free(date_str); 
    
	gtk_window_set_child (GTK_WINDOW (dialog), grid);	
	gtk_window_present(GTK_WINDOW(dialog));	
}

/**
 * @brief Callback function for the "Update Event" button.
 * It retrieves data from dialog widgets, sanitizes it, and updates an existing event in the database.
 * @param button The GtkButton that triggered the callback.
 * @param user_data A pointer to the CalendarEvent object to be updated.
 */
static void callbk_update_event(GtkButton *button, gpointer user_data)
{
	
	CalendarEvent *selectedevent =user_data; //user_data is selectedevent (not store)
	
	GtkWidget *dialog = g_object_get_data(G_OBJECT(button), "dialog-key");
	GtkWidget *window = g_object_get_data(G_OBJECT(button), "window-key");
	GtkWidget *calendar = g_object_get_data(G_OBJECT(button), "calendar-key");
	GListStore *store =g_object_get_data(G_OBJECT(button), "store-key");
	GtkWidget *label_date =g_object_get_data(G_OBJECT(window), "window-label-date-key");
		
	int start_day =GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "day-key"));
	int start_month =GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "month-key"));
	int start_year =GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "year-key"));
	
	//multiday not currently supported
	int end_day=start_day;
	int end_month=start_month;
	int end_year=start_year;
	
	GtkWidget *entry_description = g_object_get_data(G_OBJECT(button), "entry-description-key");
	GtkWidget *entry_location = g_object_get_data(G_OBJECT(button), "entry-location-key");
	
	GtkWidget *spin_button_day= g_object_get_data(G_OBJECT(button), "spin-day-key");
	GtkWidget *spin_button_month= g_object_get_data(G_OBJECT(button), "spin-month-key");
	GtkWidget *spin_button_year= g_object_get_data(G_OBJECT(button), "spin-year-key");
	
	GtkWidget *spin_button_start_hour = g_object_get_data(G_OBJECT(button), "spin-start-hour-key");
	GtkWidget *spin_button_start_min = g_object_get_data(G_OBJECT(button), "spin-start-min-key");
	GtkWidget *spin_button_end_hour = g_object_get_data(G_OBJECT(button), "spin-end-hour-key");
	GtkWidget *spin_button_end_min = g_object_get_data(G_OBJECT(button), "spin-end-min-key");
		
	GtkEntryBuffer *buffer_description;
	GtkEntryBuffer *buffer_location;	
		
	GtkWidget *check_button_allday = g_object_get_data(G_OBJECT(button), "check-button-allday-key");
	GtkWidget *check_button_isyearly = g_object_get_data(G_OBJECT(button), "check-button-isyearly-key");
	GtkWidget *check_button_priority = g_object_get_data(G_OBJECT(button), "check-button-priority-key");
	
	//m_summary set by dropdown
	
	buffer_description = gtk_entry_get_buffer(GTK_ENTRY(entry_description));
	const char* description = gtk_entry_buffer_get_text(buffer_description);
	char* clean_description = sanitize_text(description);
	
	buffer_location = gtk_entry_get_buffer(GTK_ENTRY(entry_location));
	const char* location = gtk_entry_buffer_get_text(buffer_location);
	location = gtk_entry_buffer_get_text(buffer_location);
	char* clean_location = sanitize_text(location);
		
	int start_hour= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_start_hour));
	int start_min= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_start_min));
	int end_hour= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_end_hour));
	int end_min= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_end_min));
	
	int is_allday = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_allday));	
	int is_yearly = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_isyearly));
	int is_priority = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_priority));
	
	// Now, update properties of the event object in memory 
    
    calendar_event_set_summary(selectedevent, g_strdup(m_summary));   
    calendar_event_set_location(selectedevent,  g_strdup(clean_location));
    calendar_event_set_description(selectedevent, g_strdup(clean_description));
	calendar_event_set_start_year(selectedevent, start_year);
	calendar_event_set_start_month(selectedevent, start_month);
	calendar_event_set_start_day(selectedevent, start_day);
	calendar_event_set_start_hour(selectedevent, start_hour);
	calendar_event_set_start_min(selectedevent, start_min);
	calendar_event_set_end_year(selectedevent, end_year);
	calendar_event_set_end_month(selectedevent, end_month);
	calendar_event_set_end_day(selectedevent, end_day);
	calendar_event_set_end_hour(selectedevent, end_hour);
	calendar_event_set_end_min(selectedevent, end_min);
	calendar_event_set_is_yearly(selectedevent, is_yearly);
	calendar_event_set_is_allday(selectedevent, is_allday);
	calendar_event_set_is_priority(selectedevent, is_priority);
	
	int selected_event_id = calendar_event_get_eventid(selectedevent);	
    if (db_update_event(db_handle, selectedevent) == 0) {		
        //g_print("Successfully updated event with ID: %d\n", selected_event_id);
    } else {
        g_warning("Failed to update event with ID: %d\n", selected_event_id);
    }
            
    if (clean_location != NULL) {
              
        // prevent a memory leak.
        free(clean_location);
        clean_location = NULL; // Best practice to set the pointer to NULL after freeing.
    }
    
    if (clean_description != NULL) {
               
        //prevent a memory leak.
        free(clean_description);
        clean_description = NULL; // Best practice to set the pointer to NULL after freeing.
    }
		
	set_tooltips_on_calendar(CUSTOM_CALENDAR(calendar));
	custom_calendar_update (CUSTOM_CALENDAR(calendar));
	update_store(CUSTOM_CALENDAR(calendar), store);		
	gtk_window_destroy(GTK_WINDOW(dialog));
}

/**
 * @brief Callback function to create and show a dialog to edit a selected event.
 * @param action The GSimpleAction that triggered the callback.
 * @param parameter The GVariant parameter (unused).
 * @param user_data A pointer to the GtkSingleSelection.
 */
static void callbk_edit_event(GSimpleAction *action, GVariant *parameter,  gpointer user_data)
{	
	//g_print("callbk edit event\n");
		
    GtkSingleSelection *selection=user_data; //user_data is a selectedeven (not store)
	GListModel *model = gtk_single_selection_get_model(selection);
    GListStore *store = G_LIST_STORE(model); 
    CalendarEvent* selectedevent = gtk_single_selection_get_selected_item (GTK_SINGLE_SELECTION(selection));
	
	
    if (selectedevent == NULL) {
        g_print("No event selected.\n");
        return;
    }

    // Get the ID directly from the selected event object
    int event_id_to_update = calendar_event_get_eventid(selectedevent);
	
	GtkWidget *window = g_object_get_data(G_OBJECT(selection), "selection-window-key");
	GtkWidget *calendar = g_object_get_data(G_OBJECT(selection), "selection-calendar-key");
	
	char* id_key_str =g_strdup_printf("%d",event_id_to_update);
	
	const char *summary = calendar_event_get_summary(CALENDAR_EVENT(selectedevent));
	const char *description = calendar_event_get_description(CALENDAR_EVENT(selectedevent));
	const char  *location =calendar_event_get_location(CALENDAR_EVENT(selectedevent));
	
	int start_day =calendar_event_get_start_day(CALENDAR_EVENT(selectedevent));
	int start_month =calendar_event_get_start_month(CALENDAR_EVENT(selectedevent));
	int start_year =calendar_event_get_start_year(CALENDAR_EVENT(selectedevent));
	char* day_str =g_strdup_printf("%d",start_day);
	char* month_str =g_strdup_printf("%d",start_month);
	char* year_str =g_strdup_printf("%d",start_year);
	
	int start_hour =calendar_event_get_start_hour(CALENDAR_EVENT(selectedevent));
	int start_min = calendar_event_get_start_min(CALENDAR_EVENT(selectedevent));
	int end_hour =calendar_event_get_end_hour(CALENDAR_EVENT(selectedevent));
	int end_min = calendar_event_get_end_min(CALENDAR_EVENT(selectedevent));
	
	int is_allday = calendar_event_get_is_allday(CALENDAR_EVENT(selectedevent));	
	int is_yearly = calendar_event_get_is_yearly(CALENDAR_EVENT(selectedevent));	
	int is_priority = calendar_event_get_is_priority(CALENDAR_EVENT(selectedevent));
	
	char *des_loc_str="";
	char *time_str = "";
	char* display_str="id =";
	
	display_str =g_strconcat(display_str,id_key_str," ", day_str, "-",month_str,"-",year_str, "\n",NULL);
	
	time_str =get_time_str(start_hour,start_min);
	display_str = g_strconcat(display_str, time_str, summary, " ",description, " ",location, NULL);
		
	GtkWidget *dialog;
	GtkWidget *button_update;	
	GtkWidget *grid;
	GtkWidget *label_date;	
	
	GtkWidget *label_summary;
	GtkWidget *dropdown_summary;
	
	GtkWidget *label_description;
	GtkWidget *entry_description;	
	GtkWidget *label_location;
	GtkWidget *entry_location;
	
	GtkWidget *label_spacer1;
	GtkWidget *label_spacer2;
	GtkWidget *label_spacer3;
	GtkWidget *label_spacer4;
		
	// Check buttons
	GtkWidget *check_button_allday;	
	GtkWidget *check_button_isyearly;
	GtkWidget *check_button_priority;
	
	GtkWidget *label_start_time;
	GtkWidget *spin_button_start_hour;	
	GtkWidget *spin_button_start_min;
	//end time
	GtkWidget *label_end_time;
	GtkWidget *spin_button_end_hour;	
	GtkWidget *spin_button_end_min;	
		
	dialog = gtk_window_new(); 
	gtk_window_set_title(GTK_WINDOW(dialog), "Update Event");
	
	char* date_str="";
	date_str= g_strconcat(date_str, day_str, "-",month_str, "-",year_str, NULL);
	
	label_date =gtk_label_new("");
	gtk_label_set_text(GTK_LABEL(label_date), date_str);
	
	//time spin adjustments
	
	GtkAdjustment *adjustment_start_hour = gtk_adjustment_new(1.00, 0.0, 23.00, 1.0, 1.0, 0.0);
	GtkAdjustment *adjustment_start_min= gtk_adjustment_new(0.00, 0.0, 59.00, 1.0, 1.0, 0.0);
	
	GtkAdjustment *adjustment_end_hour = gtk_adjustment_new(1.00, 0.0, 23.00, 1.0, 1.0, 0.0);
	GtkAdjustment *adjustment_end_min = gtk_adjustment_new(0.00, 0.0, 59.00, 1.0, 1.0, 0.0);
	
	label_spacer1 = gtk_label_new("");
	label_spacer2 = gtk_label_new("");
	label_spacer3 = gtk_label_new("");
	label_spacer4 = gtk_label_new("");
	
	//button UPDATE
	button_update = gtk_button_new_with_label ("Update Selected Event");
    g_signal_connect (GTK_BUTTON (button_update),"clicked", G_CALLBACK (callbk_update_event), selectedevent);
	
	g_object_set_data(G_OBJECT(button_update), "dialog-key",dialog);
	g_object_set_data(G_OBJECT(button_update), "window-key",window);
	g_object_set_data(G_OBJECT(button_update), "calendar-key",calendar);
	g_object_set_data(G_OBJECT(button_update), "store-key",store);
	
	grid = gtk_grid_new();	
	gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	//Times
	//start time
	label_start_time =gtk_label_new("Start Time: ");
	spin_button_start_hour = gtk_spin_button_new(adjustment_start_hour, 1.0, 0);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_start_hour), start_hour);
	spin_button_start_min = gtk_spin_button_new(adjustment_start_min, 1.0, 0);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_start_min), start_min);
	//end time
	label_end_time =gtk_label_new("End Time: ");		
	spin_button_end_hour = gtk_spin_button_new(adjustment_end_hour, 1.0, 0);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_end_hour), end_hour);
	spin_button_end_min = gtk_spin_button_new(adjustment_end_min, 1.0, 0);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_end_min), end_min);
	
	GtkEntryBuffer *buffer_summary;
	GtkEntryBuffer *buffer_location;
	GtkEntryBuffer *buffer_description;
         
    //Summary	
	label_summary = gtk_label_new("Summary: ");
	dropdown_summary =gtk_drop_down_new_from_strings(events);    
	g_signal_connect(GTK_DROP_DOWN(dropdown_summary), "notify::selected", G_CALLBACK(callbk_dropdown_summary), NULL);	
	guint position=0;	
	//g_print("m_summary = %s\n",m_summary);
	position = get_dropdown_position_summary(summary);
	//g_print("dropdown position = %d\n",position);	
	gtk_drop_down_set_selected(GTK_DROP_DOWN(dropdown_summary),position);
    	
	//description
	label_description = gtk_label_new("Description: ");
	entry_description = gtk_entry_new();
	gtk_entry_set_has_frame(GTK_ENTRY(entry_description),TRUE); 
	gtk_entry_set_max_length(GTK_ENTRY(entry_description), 100);
	buffer_description = gtk_entry_buffer_new(description, -1); // show description
    gtk_entry_set_buffer(GTK_ENTRY(entry_description), buffer_description);
	
	//location
	label_location = gtk_label_new("Location: ");
	entry_location = gtk_entry_new();
	gtk_entry_set_has_frame(GTK_ENTRY(entry_location),TRUE); 
	gtk_entry_set_max_length(GTK_ENTRY(entry_location), 100);
	buffer_location = gtk_entry_buffer_new(location, -1); // show location
	gtk_entry_set_buffer(GTK_ENTRY(entry_location), buffer_location);

	// check buttons
	check_button_allday = gtk_check_button_new_with_label("Is All Day");
	gtk_check_button_set_active(GTK_CHECK_BUTTON(check_button_allday), is_allday);	
	check_button_isyearly = gtk_check_button_new_with_label("Is Yearly");
	gtk_check_button_set_active(GTK_CHECK_BUTTON(check_button_isyearly), is_yearly);
	check_button_priority = gtk_check_button_new_with_label("Is High Priority");
	gtk_check_button_set_active(GTK_CHECK_BUTTON(check_button_priority), is_priority);
	
	g_object_set_data(G_OBJECT(button_update), "day-key",GINT_TO_POINTER(start_day));
	g_object_set_data(G_OBJECT(button_update), "month-key",GINT_TO_POINTER(start_month));
	g_object_set_data(G_OBJECT(button_update), "year-key",GINT_TO_POINTER(start_year));
		
	g_object_set_data(G_OBJECT(button_update), "entry-location-key", entry_location);	
	g_object_set_data(G_OBJECT(button_update), "entry-description-key", entry_description);
		
	g_object_set_data(G_OBJECT(button_update), "spin-start-hour-key", spin_button_start_hour);
	g_object_set_data(G_OBJECT(button_update), "spin-start-min-key", spin_button_start_min);
	g_object_set_data(G_OBJECT(button_update), "spin-end-hour-key", spin_button_end_hour);
	g_object_set_data(G_OBJECT(button_update), "spin-end-min-key", spin_button_end_min);
		
	g_object_set_data(G_OBJECT(button_update), "check-button-allday-key", check_button_allday);	
	g_object_set_data(G_OBJECT(button_update), "check-button-isyearly-key", check_button_isyearly);
	g_object_set_data(G_OBJECT(button_update), "check-button-priority-key", check_button_priority);
	
	gtk_grid_attach(GTK_GRID(grid), label_date, 1, 1, 1, 1);
		
	gtk_grid_attach(GTK_GRID(grid), label_summary, 1, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), dropdown_summary, 2, 2, 1, 1);
	
	gtk_grid_attach(GTK_GRID(grid), label_description, 1, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), entry_description, 2, 3, 3, 1);
	
	gtk_grid_attach(GTK_GRID(grid), label_location, 1, 4, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), entry_location, 2, 4, 3, 1);
	
	gtk_grid_attach(GTK_GRID(grid), label_spacer1,       1, 5, 3, 1);
		
	//start time
	gtk_grid_attach(GTK_GRID(grid), label_start_time,       1, 6, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), spin_button_start_hour,  2, 6, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), spin_button_start_min,   3, 6, 1, 1);
	//end time
	gtk_grid_attach(GTK_GRID(grid), label_end_time,        1, 7, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), spin_button_end_hour,  2, 7, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), spin_button_end_min,   3, 7, 1, 1);
	
	gtk_grid_attach(GTK_GRID(grid), label_spacer2,       1, 8, 3, 1);
	
	gtk_grid_attach(GTK_GRID(grid), check_button_allday,        1, 9, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), check_button_isyearly,      2, 9, 1, 1);  
	gtk_grid_attach(GTK_GRID(grid), check_button_priority,      3, 9, 1, 1);
	
	gtk_grid_attach(GTK_GRID(grid), label_spacer4,       	1, 10, 3, 1);
	
	gtk_grid_attach(GTK_GRID(grid), button_update,  		1, 11, 4, 1);
	
	g_free(day_str);
    g_free(month_str);
    g_free(year_str);
    g_free(date_str);
		
	gtk_window_set_child (GTK_WINDOW (dialog), grid);	
	gtk_window_present(GTK_WINDOW(dialog));
	
}

/**
 * @brief Callback function to delete a selected event from the database.
 * @param action The GSimpleAction that triggered the callback.
 * @param parameter The GVariant parameter (unused).
 * @param user_data A pointer to the GtkSingleSelection.
 */
static void callbk_delete_event(GSimpleAction *action, GVariant *parameter,  gpointer user_data)
{	
	GtkSingleSelection *selection=user_data;
	GListModel *model = gtk_single_selection_get_model(selection);
    GListStore *store = G_LIST_STORE(model); 
    CalendarEvent* selectedevent = gtk_single_selection_get_selected_item (GTK_SINGLE_SELECTION(selection));
   
    if (selectedevent == NULL) {
        //g_print("No event selected.\n");
        return;
    }
       
	GtkWidget *calendar = g_object_get_data(G_OBJECT(selection), "selection-calendar-key");
	GtkWidget *label_date =g_object_get_data(G_OBJECT(selection), "selection-label-key");	

    // Get the ID directly from the selected event object
    int event_id_to_delete = calendar_event_get_eventid(selectedevent);

    if (db_delete_event(db_handle, event_id_to_delete) == 0) {
       //g_print("Successfully removed event with ID: %d\n", event_id_to_delete);
    } else {
        g_warning("Failed to remove event with ID: %d\n", event_id_to_delete);
    }
	set_tooltips_on_calendar(CUSTOM_CALENDAR(calendar));     
	custom_calendar_update (CUSTOM_CALENDAR(calendar));	
	update_store(CUSTOM_CALENDAR(calendar), store);
	
}

//======================================================================
//Delete all (danger zone) -ask for confirmation
//======================================================================
static void callbk_confirm_delete_all(GtkButton *button, gpointer  user_data)
{	
	GtkWindow *window =user_data;	
	GtkWidget *calendar =g_object_get_data(G_OBJECT(window), "window-calendar-key");
	GtkWidget *label_date =g_object_get_data(G_OBJECT(window), "window-label-date-key");
	GListStore *store =g_object_get_data(G_OBJECT(window), "window-store-key");
	GtkWidget *dialog = g_object_get_data(G_OBJECT(button), "dialog-key");

	if (db_delete_all_events(db_handle) == 0) 
	{
		//g_print("Successfully removed all events.\n");
	} else 
	{
		g_warning("Failed to remove all events.\n");
	}

	g_list_store_remove_all(G_LIST_STORE(store));
	set_tooltips_on_calendar(CUSTOM_CALENDAR(calendar));
	custom_calendar_update (CUSTOM_CALENDAR(calendar));

	gtk_window_destroy(GTK_WINDOW(dialog));
}


/**
 * @brief Callback function to delete all events from the database.
 * @param action The GSimpleAction that triggered the callback.
 * @param parameter The GVariant parameter (unused).
 * @param user_data A pointer to the GtkWindow (to get Calendar etc)
 */
static void callbk_delete_all(GSimpleAction *action, GVariant *parameter,  gpointer user_data)
{
	GtkWidget *window =user_data;
	GtkWidget *dialog;
	GtkWidget *box;
	GtkWidget *button_confirm;
	GtkWidget *label_confirm;
	
	dialog =gtk_window_new(); //gtk_dialog_new_with_buttons to be deprecated gtk4.10
	
	gtk_window_set_title (GTK_WINDOW (dialog), "Delete All");
	gtk_window_set_default_size(GTK_WINDOW(dialog),350,100);
	
	box =gtk_box_new(GTK_ORIENTATION_VERTICAL,1);
	gtk_window_set_child (GTK_WINDOW (dialog), box);
	
	button_confirm = gtk_button_new_with_label ("Delete All");
	g_signal_connect (button_confirm, "clicked", G_CALLBACK (callbk_confirm_delete_all), window);
	
	label_confirm = gtk_label_new("Pressing Delete All\n will clear database");
	
	g_object_set_data(G_OBJECT(button_confirm), "dialog-key",dialog);
	
	gtk_box_append(GTK_BOX(box), label_confirm);	
	gtk_box_append(GTK_BOX(box), button_confirm);
	gtk_window_present (GTK_WINDOW (dialog));
}

//======================================================================
//Export/Import ical
//======================================================================


/**
 * @brief Callback for the file save response after an export operation.
 * @param source The GObject that initiated the save operation.
 * @param result The GAsyncResult object.
 * @param user_data A pointer to the GtkFileChooserDialog.
 */
static void file_save_response (GObject *source, GAsyncResult *result, void *user_data)
{

	GtkFileDialog *dialog = GTK_FILE_DIALOG (source);  
	
	GFile *file;
	file = gtk_file_dialog_save_finish (dialog, result, NULL);
	if (file)
	{	 
	char *file_name = g_file_get_path(file);	  
	export_file(file_name);
	}
}

void export_file(char *file_name) 
{
    GFile *file = NULL;
    GFileOutputStream *file_stream = NULL;
    GDataOutputStream *data_stream = NULL;
    GError *err = NULL;
    GArray* all_events = NULL;
    
    // Validate input
    if (!file_name || strlen(file_name) == 0) {
        g_warning("Invalid file name provided");
        return;
    }
    
    // Create file and stream
    file = g_file_new_for_path(file_name);
    file_stream = g_file_replace(file, NULL, TRUE, G_FILE_CREATE_NONE, NULL, &err);
    
    if (file_stream == NULL) {        
        g_warning("Error opening file %s: %s", file_name, err->message);
        g_error_free(err);
        g_object_unref(file);
        return;
    }

    data_stream = g_data_output_stream_new(G_OUTPUT_STREAM(file_stream));
    
    // Get all events
    all_events = db_get_all_events(db_handle);
    
    if (all_events && all_events->len > 0) {
        // Write VCALENDAR header
        g_data_output_stream_put_string(data_stream, "BEGIN:VCALENDAR\n", NULL, NULL);
        g_data_output_stream_put_string(data_stream, "VERSION:2.0\n", NULL, NULL);
        g_data_output_stream_put_string(data_stream, "PRODID:-//Talk Calendar v0.7//EN\n", NULL, NULL);

        // Process each event
        for (guint i = 0; i < all_events->len; ++i) {
            CalendarEvent* event = g_array_index(all_events, CalendarEvent*, i);
            
            if (!event) continue;
            
            // Get event properties with proper error handling
            gint event_id = 0;
            gchar *summary_str = NULL;
            gchar *location_str = NULL;
            gchar *description_str = NULL;
            
            gint start_year = 0, start_month = 0, start_day = 0, start_hour = 0, start_min = 0, start_seconds = 0;
            gint end_year = 0, end_month = 0, end_day = 0, end_hour = 0, end_min = 0, end_seconds = 0;
            gint is_yearly = 0, is_allday = 0, is_priority = 0;
            
            // Get all properties
            g_object_get(event, 
                        "eventid", &event_id,
                        "summary", &summary_str,
                        "location", &location_str,
                        "description", &description_str,
                        "startyear", &start_year,
                        "startmonth", &start_month,
                        "startday", &start_day,
                        "starthour", &start_hour,
                        "startmin", &start_min,
                        "endyear", &end_year,
                        "endmonth", &end_month,
                        "endday", &end_day,
                        "endhour", &end_hour,
                        "endmin", &end_min,
                        "isyearly", &is_yearly,
                        "isallday", &is_allday,
                        "ispriority", &is_priority,
                        NULL);
            
            // Format date/time components
            gchar *start_day_str = g_strdup_printf("%02d", start_day);
            gchar *start_month_str = g_strdup_printf("%02d", start_month);
            gchar *start_year_str = g_strdup_printf("%d", start_year);
            gchar *start_hour_str = g_strdup_printf("%02d", start_hour);
            gchar *start_min_str = g_strdup_printf("%02d", start_min);
            gchar *start_sec_str = g_strdup_printf("%02d", start_seconds);
            
            gchar *end_day_str = g_strdup_printf("%02d", end_day);
            gchar *end_month_str = g_strdup_printf("%02d", end_month);
            gchar *end_year_str = g_strdup_printf("%d", end_year);
            gchar *end_hour_str = g_strdup_printf("%02d", end_hour);
            gchar *end_min_str = g_strdup_printf("%02d", end_min);
            gchar *end_sec_str = g_strdup_printf("%02d", end_seconds);
            
            // Format priority
            gchar *priority_str = is_priority ? "PRIORITY:1\n" : "PRIORITY:0\n";
            
            // Build DTSTART and DTEND strings
            gchar *dtstart_str = g_strdup_printf("DTSTART:%s%s%sT%s%s%s\n",
                                               start_year_str, start_month_str, start_day_str,
                                               start_hour_str, start_min_str, start_sec_str);
            
            gchar *dtend_str = g_strdup_printf("DTEND:%s%s%sT%s%s%s\n",
                                             end_year_str, end_month_str, end_day_str,
                                             end_hour_str, end_min_str, end_sec_str);
            
            // Write event components
            g_data_output_stream_put_string(data_stream, "BEGIN:VEVENT\n", NULL, NULL);
            g_data_output_stream_put_string(data_stream, dtstart_str, NULL, NULL);
            g_data_output_stream_put_string(data_stream, dtend_str, NULL, NULL);
            
            if (location_str && strlen(location_str) > 0) {
                gchar *loc_line = g_strdup_printf("LOCATION:%s\n", location_str);
                g_data_output_stream_put_string(data_stream, loc_line, NULL, NULL);
                g_free(loc_line);
            }
            
            if (summary_str && strlen(summary_str) > 0) {
                gchar *sum_line = g_strdup_printf("SUMMARY:%s\n", summary_str);
                g_data_output_stream_put_string(data_stream, sum_line, NULL, NULL);
                g_free(sum_line);
            }
            
            if (description_str && strlen(description_str) > 0) {
                gchar *desc_line = g_strdup_printf("DESCRIPTION:%s\n", description_str);
                g_data_output_stream_put_string(data_stream, desc_line, NULL, NULL);
                g_free(desc_line);
            }
            
            g_data_output_stream_put_string(data_stream, priority_str, NULL, NULL);
            
            gchar *allday_str = is_allday ? "X-ISALLDAY:1\n" : "X-ISALLDAY:0\n";
            g_data_output_stream_put_string(data_stream, allday_str, NULL, NULL);
            
            if (is_yearly) {
                gchar *recurrence_str = g_strdup_printf("RRULE:FREQ=YEARLY;INTERVAL=1;BYMONTH=%s;BYMONTHDAY=%s\n",
                                                      start_month_str, start_day_str);
                g_data_output_stream_put_string(data_stream, recurrence_str, NULL, NULL);
                g_free(recurrence_str);
            }
            
            g_data_output_stream_put_string(data_stream, "END:VEVENT\n", NULL, NULL);
            
            // Clean up loops strings
            g_free(start_day_str); g_free(start_month_str); g_free(start_year_str);
            g_free(start_hour_str); g_free(start_min_str); g_free(start_sec_str);
            g_free(end_day_str); g_free(end_month_str); g_free(end_year_str);
            g_free(end_hour_str); g_free(end_min_str); g_free(end_sec_str);
            g_free(dtstart_str); g_free(dtend_str);
            
            if (summary_str) g_free(summary_str);
            if (location_str) g_free(location_str);
            if (description_str) g_free(description_str);
            
            // Fix: REMOVED g_object_unref(event) to stop object deletion out of working engine memory!
        }
        
        g_data_output_stream_put_string(data_stream, "END:VCALENDAR\n", NULL, NULL);
    } else {
        g_warning("Failed to retrieve events or no events found.");
    }
    
    // Unified outer array cleanup handler block to prevent path leaks
    if (all_events) {
        // If your database code was updated in the previous step to set an array clear function, 
        // use g_array_unref(all_events). If you haven't altered dbmanager.c yet, use the loop-free free command:
        g_array_free(all_events, TRUE);
    }
    
    if (data_stream) g_object_unref(data_stream);
    if (file_stream) g_object_unref(file_stream);
    if (file) g_object_unref(file);
}


//======================================================================
//Export ical
//======================================================================

/**
 * @brief Callback for the export action, which opens a file chooser dialog.
 * @param action The GSimpleAction that triggered the callback.
 * @param parameter The GVariant parameter (unused).
 * @param user_data A pointer to the GtkWindow.
 */
static void callbk_export(GSimpleAction *action, GVariant *parameter,  gpointer user_data)
{
	GtkWidget *window = user_data;
	
	GtkFileDialog *dialog; //export file dialog
	dialog = gtk_file_dialog_new(); 
	gtk_file_dialog_set_title (dialog,"Export ical calendar file");  
	gtk_file_dialog_set_initial_name (dialog, "talkcalendar.ical");
	
	GtkFileFilter* filefilter1 = gtk_file_filter_new();
	gtk_file_filter_add_suffix(filefilter1,"ical");
	gtk_file_filter_set_name(filefilter1,"ical");
	
	GtkFileFilter *filefilter2 = gtk_file_filter_new();
	gtk_file_filter_add_suffix(filefilter2,"ics");
	gtk_file_filter_set_name(filefilter2,"ics");
	
	GtkFileFilter *filefilter3 = gtk_file_filter_new();
	gtk_file_filter_add_suffix(filefilter3,"ifb");
	gtk_file_filter_set_name(filefilter3,"ifb");
	
	GtkFileFilter *filefilter4 = gtk_file_filter_new();
	gtk_file_filter_add_suffix(filefilter4,"icalendar");
	gtk_file_filter_set_name(filefilter4,"icalendar");
	
	GtkFileFilter* filefilter5 = gtk_file_filter_new();
	gtk_file_filter_add_suffix(filefilter5,"txt");
	gtk_file_filter_set_name(filefilter5,"Text");
	
	GListStore* liststore = g_list_store_new (GTK_TYPE_FILE_FILTER);
	g_list_store_append(liststore, filefilter1);
	g_list_store_append(liststore, filefilter2);
	g_list_store_append(liststore, filefilter3);
	g_list_store_append(liststore, filefilter4);
	g_list_store_append(liststore, filefilter5);	
	
	gtk_file_dialog_set_filters(dialog,G_LIST_MODEL(liststore));    
	gtk_file_dialog_save(dialog, NULL, NULL, file_save_response, NULL); //no longer signal based
	g_object_set_data(G_OBJECT(dialog), "dialog-window-key",window);	
	g_object_unref (dialog);
}	


//======================================================================
// Single pass
//======================================================================

/**
 * Helper function to parse iCal date strings (YYYYMMDD or YYYYMMDDTHHMMSS)
 * handles variable lengths safely.
 */
static void parse_ical_date(const char *date_str, int *y, int *m, int *d, int *h, int *min) {
    if (!date_str || strlen(date_str) < 8) return;

    // Initialize with zero
    *y = *m = *d = *h = *min = 0;

    // Extract Year (first 4 chars)
    char buf[5];
    snprintf(buf, sizeof(buf), "%.4s", date_str);
    *y = g_ascii_strtoll(buf, NULL, 10);

    // Extract Month (chars 4-6)
    if (strlen(date_str) >= 6) {
        snprintf(buf, sizeof(buf), "%.2s", date_str + 4);
        *m = g_ascii_strtoll(buf, NULL, 10);
    }

    // Extract Day (chars 6-8)
    if (strlen(date_str) >= 8) {
        snprintf(buf, sizeof(buf), "%.2s", date_str + 6);
        *d = g_ascii_strtoll(buf, NULL, 10);
    }

    // Extract Time (if present, starts at index 9 after 'T')
    const char *t_ptr = strchr(date_str, 'T');
    if (t_ptr) {
        t_ptr++; // Move past 'T'
        if (strlen(t_ptr) >= 2) {
            snprintf(buf, sizeof(buf), "%.2s", t_ptr);
            *h = g_ascii_strtoll(buf, NULL, 10);
        }
        if (strlen(t_ptr) >= 4) {
            snprintf(buf, sizeof(buf), "%.2s", t_ptr + 2);
            *min = g_ascii_strtoll(buf, NULL, 10);
        }
    }
}

/**
 * @brief Imports events from an iCal file using a single-pass efficient parser.
 */


void import_ical_file(gpointer user_data) 
{       
    GtkWidget *window = user_data; 
    GtkWidget *calendar = g_object_get_data(G_OBJECT(window), "window-calendar-key");
    GListStore *store = g_object_get_data(G_OBJECT(window), "window-store-key");
    GtkWidget *label_date = g_object_get_data(G_OBJECT(window), "window-label-date-key");
    
    GFile *file = g_file_new_for_path(m_file_name);
    GError *error = NULL;
    GFileInputStream *file_stream = g_file_read(file, NULL, &error);
    if (!file_stream) {
        g_warning("CRITICAL: Unable to open file %s: %s", m_file_name, error ? error->message : "Unknown error");
        if (error) g_error_free(error);
        g_object_unref(file);
        return;
    }
    
    GDataInputStream *input_stream = g_data_input_stream_new(G_INPUT_STREAM(file_stream));    
    
    gchar *summary = NULL, *location = NULL, *description = NULL;
    int start_y = 0, start_m = 0, start_d = 0, start_h = 0, start_min = 0;
    int end_y = 0, end_m = 0, end_d = 0, end_h = 0, end_min = 0;
    int is_priority = 0, is_yearly = 0, is_allday = 0;
    char *line = NULL;    
    
    GPtrArray *lines = g_ptr_array_new();    
    while ((line = g_data_input_stream_read_line(input_stream, NULL, NULL, &error))) {
        if (error) break;
        if (!line) break;        
        g_strstrip(line);
        if (strlen(line) > 0) {
            g_ptr_array_add(lines, line);
        } else {
            g_free(line);
        }
    }    
    
    for (int i = 0; i < lines->len; i++) {
        char *current_line = (char*)g_ptr_array_index(lines, i);
        if (strlen(current_line) == 0) continue;        
        
        // Use g_strsplit to handle string slicing safely without breaking post-loop free() boundaries
        gchar **tokens = g_strsplit(current_line, ":", 2);
        if (!tokens || !tokens[0] || !tokens[1]) {
            if (tokens) g_strfreev(tokens);
            continue;
        }
        
        const char *key = tokens[0];
        const char *value = tokens[1];
        
        if (g_strcmp0(key, "VERSION") == 0) {
            if (value && strcmp(value, "2.0") != 0) {
                g_warning("Warning: Unexpected iCalendar version %s", value);
            }
        }        
        else if (g_strcmp0(key, "BEGIN") == 0 && g_strcmp0(value, "VEVENT") == 0) {
            g_free(summary);     summary = NULL;
            g_free(location);    location = NULL;
            g_free(description); description = NULL;
            start_y = start_m = start_d = start_h = start_min = 0;
            end_y = end_m = end_d = end_h = end_min = 0;
            is_priority = is_yearly = is_allday = 0;
        }
        else if (g_str_has_prefix(key, "DTSTART")) {
            parse_ical_date(value, &start_y, &start_m, &start_d, &start_h, &start_min);
        }
        else if (g_str_has_prefix(key, "DTEND")) {
            parse_ical_date(value, &end_y, &end_m, &end_d, &end_h, &end_min);
        }
        else if (g_strcmp0(key, "SUMMARY") == 0) {
            g_free(summary); 
            summary = g_strdup(value ? value : "");
        }
        else if (g_strcmp0(key, "LOCATION") == 0) {
            g_free(location); 
            location = g_strdup(value ? value : "");
        }
        else if (g_strcmp0(key, "DESCRIPTION") == 0) {
            g_free(description); 
            description = g_strdup(value ? value : "");
        }
        else if (g_strcmp0(key, "PRIORITY") == 0) {
            is_priority = (value && g_ascii_strtoll(value, NULL, 10) > 0);
        }
        else if (g_strcmp0(key, "X-ISALLDAY") == 0) {
            is_allday = (value && strcmp(value, "1") == 0);
        }
        else if (g_strcmp0(key, "RRULE") == 0) {
            is_yearly = (value && strstr(value, "FREQ=YEARLY") != NULL);
        }
        else if (g_strcmp0(key, "END") == 0 && g_strcmp0(value, "VEVENT") == 0) {
            if (!summary && !location && !description &&
                start_y == 0 && start_m == 0 && start_d == 0 &&
                end_y == 0 && end_m == 0 && end_d == 0) {
                g_print("Warning: Empty event detected, skipping...\n");
                g_strfreev(tokens);
                continue;
            }            
            
            CalendarEvent *evt = g_object_new(CALENDAR_TYPE_EVENT, 0);
            if (!evt) {
                g_warning("Failed to create CalendarEvent object\n");
                g_strfreev(tokens);
                continue;
            }
            
            const char* summary_val = (summary ? summary : "");
            const char* location_val = (location ? location : "");
            const char* description_val = (description ? description : "");
            
            g_object_set(evt,
                "summary",     summary_val,
                "location",    location_val,
                "description", description_val,
                "startyear",   start_y, 
                "startmonth",  start_m, 
                "startday",    start_d,
                "starthour",   start_h, 
                "startmin",    start_min,
                "endyear",     end_y, 
                "endmonth",    end_m, 
                "endday",      end_d,
                "endhour",     end_h, 
                "endmin",      end_min,
                "isyearly",    is_yearly,
                "isallday",    is_allday,  
                "ispriority",  is_priority,
                NULL);
                
            int result = db_insert_event(db_handle, evt);
            if (result == -1) {
                g_warning("Failed to append new event.\n");
            }            
            
            g_object_unref(evt);
            
            g_free(summary);     summary = NULL;
            g_free(location);    location = NULL;
            g_free(description); description = NULL;
        }     
        
        // Free temporary tokens vectors at the end of each line loop step pass
        g_strfreev(tokens);
    }    
    
    g_free(summary);
    g_free(location);
    g_free(description);
    
    // Now this reliably cleans the unmodified original raw heap allocations perfectly!
    for (guint i = 0; i < lines->len; i++) {
        g_free(g_ptr_array_index(lines, i));
    }
    g_ptr_array_free(lines, TRUE); 
    
    set_tooltips_on_calendar(CUSTOM_CALENDAR(calendar));
    custom_calendar_update(CUSTOM_CALENDAR(calendar));
    custom_calendar_goto_today(CUSTOM_CALENDAR(calendar));
    update_store(CUSTOM_CALENDAR(calendar), store);          
    
    g_object_unref(input_stream);
    g_object_unref(file_stream);
    g_object_unref(file);
}


//======================================================================
/**
 * @brief Callback for the file open response after an import operation.
 * @param source The GObject that initiated the open operation.
 * @param result The GAsyncResult object.
 * @param user_data (not used)
 */
static void file_open_response (GObject *source, GAsyncResult *result, void *user_data)
{
	GtkFileDialog *dialog = GTK_FILE_DIALOG (source);    
	GtkWidget *window = g_object_get_data(G_OBJECT(dialog), "dialog-window-key");
	
	GFile *file;
	
	file = gtk_file_dialog_open_finish (dialog, result, NULL);
	if (file)
	{    
	m_file_name = g_file_get_path(file);
	import_ical_file(window);
	  
	g_object_unref (file);
	}
}   

//======================================================================
//Import ical
//======================================================================

/**
 * @brief Callback for the import action, which opens a file chooser dialog.
 * @param action The GSimpleAction that triggered the callback.
 * @param parameter The GVariant parameter (unused).
 * @param user_data A pointer to the GtkWindow.
 */
static void callbk_import(GSimpleAction *action, GVariant *parameter,  gpointer user_data)
{
	GtkWidget *window = user_data;
	GtkFileDialog *dialog; //file dialog
	dialog = gtk_file_dialog_new();
	gtk_file_dialog_set_title (dialog,"Import ical calendar file");  
	
	//iCalendar files typically have the file extension ".ical" ".ics" "
	//.ifb"  or ".icalendar" with a MIME type of "text/calendar
	
	GtkFileFilter* filefilter1 = gtk_file_filter_new();
	gtk_file_filter_add_suffix(filefilter1,"ical");
	gtk_file_filter_set_name(filefilter1,"ical");
	
	GtkFileFilter *filefilter2 = gtk_file_filter_new();
	gtk_file_filter_add_suffix(filefilter2,"ics");
	gtk_file_filter_set_name(filefilter2,"ics");
	
	GtkFileFilter *filefilter3 = gtk_file_filter_new();
	gtk_file_filter_add_suffix(filefilter3,"ifb");
	gtk_file_filter_set_name(filefilter3,"ifb");
	
	GtkFileFilter *filefilter4 = gtk_file_filter_new();
	gtk_file_filter_add_suffix(filefilter4,"icalendar");
	gtk_file_filter_set_name(filefilter4,"icalendar");
	
	GtkFileFilter* filefilter5 = gtk_file_filter_new();
	gtk_file_filter_add_suffix(filefilter5,"txt");
	gtk_file_filter_set_name(filefilter5,"Text");
	
	GListStore* liststore = g_list_store_new (GTK_TYPE_FILE_FILTER);
	g_list_store_append(liststore, filefilter1);
	g_list_store_append(liststore, filefilter2);
	g_list_store_append(liststore, filefilter3);
	g_list_store_append(liststore, filefilter4);
	g_list_store_append(liststore, filefilter5);	
	
	gtk_file_dialog_set_filters(dialog,G_LIST_MODEL(liststore));
	gtk_file_dialog_open (dialog, NULL, NULL, file_open_response, NULL); //no longer signal based
	
	g_object_set_data(G_OBJECT(dialog), "dialog-window-key",window);	
	g_object_unref (dialog);
	
}


//======================================================================
//Calendar callbks
//======================================================================

/**
 * @brief Callback for the home action, which sets the calendar to the current date.
 * @param action The GSimpleAction that triggered the callback.
 * @param parameter The GVariant parameter (unused).
 * @param user_data A pointer to GtkWindow (to get the CustomCalendar and GListStore)
 */
static void callbk_calendar_home(GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
    GtkWidget *window = GTK_WIDGET(user_data);
    GtkWidget *calendar = g_object_get_data(G_OBJECT(window), "window-calendar-key");
    GListStore *store   = g_object_get_data(G_OBJECT(window), "window-store-key");

    if (calendar && GTK_IS_WIDGET(calendar)) {
        // Jump your widget directly back to today's current real-world clock time dates
        custom_calendar_goto_today(CUSTOM_CALENDAR(calendar));
        
        m_start_day   = custom_calendar_get_day(CUSTOM_CALENDAR(calendar));
        m_start_month = custom_calendar_get_month(CUSTOM_CALENDAR(calendar));
        m_start_year  = custom_calendar_get_year(CUSTOM_CALENDAR(calendar));    

        // FIX: Ensure the header updates and clears its holiday suffix texts on Home resets too!
        const char *home_holiday = get_notable_date_text(m_start_year, m_start_month, m_start_day);
        custom_calendar_set_notable_date_suffix(CUSTOM_CALENDAR(calendar), home_holiday);

		set_tooltips_on_calendar(CUSTOM_CALENDAR(calendar));     
		if (m_notable_dates) {
		set_notables_on_calendar(CUSTOM_CALENDAR(calendar));           
		}
		custom_calendar_update(CUSTOM_CALENDAR(calendar));
		update_store(CUSTOM_CALENDAR(calendar), store); 
                        
        if (m_talk) {
            speak_events();
        }
    }
}

/**
 * @brief Callback for when a day is selected on the calendar.
 * @param calendar The CustomCalendar widget.
 * @param user_data A pointer to the GListStore.
 */
static void callbk_calendar_day_selected(CustomCalendar *calendar, gpointer user_data)
{       
    if (m_talking) return; 
    
    GListStore *store = user_data;    
    
    m_start_day   = custom_calendar_get_day(CUSTOM_CALENDAR(calendar));
    m_start_month = custom_calendar_get_month(CUSTOM_CALENDAR(calendar));
    m_start_year  = custom_calendar_get_year(CUSTOM_CALENDAR(calendar));    
    
    // Fetch our read-only string literal holiday title description
    const char *holiday_name = get_notable_date_text(m_start_year, m_start_month, m_start_day);
    
    // Push the text directly into the custom calendar instance label framework!
    custom_calendar_set_notable_date_suffix(CUSTOM_CALENDAR(calendar), holiday_name);
    
    set_tooltips_on_calendar(CUSTOM_CALENDAR(calendar));        
    custom_calendar_update(CUSTOM_CALENDAR(calendar));
    update_store(CUSTOM_CALENDAR(calendar), store);  
}

/**
 * @brief Synchronises the internal calendar engine state with the main window's application data model.
 * 
 * This core coordination function synchronises properties when moving between month or year views.
 * It carries out the following operations:
 * 1. Safely extracts the application storage object (`GListStore`) bound to the window container.
 * 2. Synchronises the global active temporal markers (`m_start_day`, `m_start_month`, `m_start_year`).
 * 3. Cross-references the targeted viewport selection against global holiday registries.
 * 4. Appends structural text suffixes, updates hover tooltips, and highlights holiday grids.
 * 5. Re-filters the background metadata storage cache to match the updated view state.
 *
 * @param calendar A pointer to the CustomCalendar instance tracking layout selections.
 * @param window   The application main window layout widget acting as the structural container context.
 * 
 * @return void
 */
static void sync_calendar_state(CustomCalendar *calendar, GtkWidget *window)
{
    g_return_if_fail(CUSTOM_IS_CALENDAR(calendar));
    g_return_if_fail(GTK_IS_WIDGET(window));

    // Pull the raw database tracking keys out safely
    GListStore *store = g_object_get_data(G_OBJECT(window), "window-store-key");    

    // Synchronize our temporary global selection integers with the calendar's active page targets
    m_start_day   = custom_calendar_get_day(CUSTOM_CALENDAR(calendar));
    m_start_month = custom_calendar_get_month(CUSTOM_CALENDAR(calendar));
    m_start_year  = custom_calendar_get_year(CUSTOM_CALENDAR(calendar));    

    // Look up the notable text descriptor for the NEW target date page!
    // If it's a regular day, get_notable_date_text returns NULL, clearing out the old text!
    const char *new_holiday_text = get_notable_date_text(m_start_year, m_start_month, m_start_day);    

    // Explicitly update the string storage slot inside the widget class private properties
    custom_calendar_set_notable_date_suffix(CUSTOM_CALENDAR(calendar), new_holiday_text);

    // standard application view model data updates 
    set_tooltips_on_calendar(CUSTOM_CALENDAR(calendar));     
    if (m_notable_dates) {
        set_notables_on_calendar(CUSTOM_CALENDAR(calendar));           
    }
    custom_calendar_update(CUSTOM_CALENDAR(calendar));
    update_store(CUSTOM_CALENDAR(calendar), store);  
}

/**
 * @brief Callback to navigate to the next month on the calendar.
 * @param calendar The CustomCalendar widget.
 * @param user_data A pointer to window to get the GListStore using key.
 */
static void callbk_calendar_next_month(CustomCalendar *calendar, gpointer user_data) 
{    
    sync_calendar_state(calendar, GTK_WIDGET(user_data));
}

/**
 * @brief Callback to navigate to the previous month on the calendar.
 * @param calendar The CustomCalendar widget.
 * @param user_data A pointer to window to get the GListStore using key.
 */
static void callbk_calendar_prev_month(CustomCalendar *calendar, gpointer user_data) 
{    
    sync_calendar_state(calendar, GTK_WIDGET(user_data));
}

/**
 * @brief Callback to navigate to the next year on the calendar.
 * @param calendar The CustomCalendar widget.
 * @param user_data A pointer to window to get the GListStore using key.
 */
static void callbk_calendar_next_year(CustomCalendar *calendar, gpointer user_data) 
{
    sync_calendar_state(calendar, GTK_WIDGET(user_data));
}

/**
 * @brief Callback to navigate to the previous year on the calendar.
 * @param calendar The CustomCalendar widget.
 * @param user_data A pointer to window to get the GListStore using key.
 */
static void callbk_calendar_prev_year(CustomCalendar *calendar, gpointer user_data) 
{
    sync_calendar_state(calendar, GTK_WIDGET(user_data));
}

/**
 * @brief Sets notable dates on the calendar.
 * @param calendar The CustomCalendar widget.
 */
static void set_notables_on_calendar(CustomCalendar *calendar)
{
    g_return_if_fail(CUSTOM_IS_CALENDAR(calendar));    
    // Wipe out any holiday highlighting classes from the previous month page view
    custom_calendar_reset_notables(calendar);		
        // Extract the active month page coordinates currently viewed on screen
    int viewed_month = custom_calendar_get_month(calendar);
    int viewed_year  = custom_calendar_get_year(calendar);    
    guint8 month_days = g_date_get_days_in_month(viewed_month, viewed_year);    
    // Scan every day in this viewed month dynamically
    for (int day = 1; day <= month_days; day++) {
        // Cross-reference against your read-only text string identifier function
        const char *is_holiday = get_notable_date_text(viewed_year, viewed_month, day);        
        if (is_holiday != NULL) {
            // Dynamic Hit! Mark the cell row color target instantly
            custom_calendar_mark_notable(calendar, day);
        }
    }    
    // Force your calendar grid engine to repaint the cells with the CSS classes
    custom_calendar_update(calendar);
}


/**
 * @brief Generates hover tooltips and event markers for all active days in the current month view.
 * 
 * This pipeline function processes calendar event indicators through the following pipeline:
 * 1. Resets the internal array of tooltip strings and clears active date event highlights.
 * 2. Iterates across each day of the active month and queries the database for matching schedules.
 * 3. Builds a dynamically sized string wrapper (`GString`) to stack multi-event details per cell.
 * 4. Extracts metadata properties from `CalendarEvent` instances using standard GObject syntax.
 * 5. Formatting routines strip empty texts and assemble timestamps alongside descriptive labels.
 * 6. Marks the target calendar grid layout day cell to display an active visual layout decorator.
 * 7. Securely pushes the generated tooltip text block into the container before freeing allocations.
 *
 * @param calendar A pointer to the targeted CustomCalendar instance.
 * 
 * @return void
 */
static void set_tooltips_on_calendar(CustomCalendar *calendar)
{
    custom_calendar_initialise_tooltip_array(calendar);
    custom_calendar_reset_marks(CUSTOM_CALENDAR(calendar)); 

    int selected_month = custom_calendar_get_month(CUSTOM_CALENDAR(calendar));
    int selected_year = custom_calendar_get_year(CUSTOM_CALENDAR(calendar));
    guint8 month_days = g_date_get_days_in_month(selected_month, selected_year);    

    // Cycle through all days in the currently viewed month
    for (int day = 1; day <= month_days; day++)
    {
        GArray* events_for_day = db_get_all_events_year_month_day(db_handle, selected_year, selected_month, day);
        if (events_for_day) {
            GString *day_tooltip_gstr = g_string_new("");            
            
            for (guint i = 0; i < events_for_day->len; i++) {
                CalendarEvent* day_event = g_array_index(events_for_day, CalendarEvent*, i);
                if (!day_event) continue;

                int start_day = 0, start_month = 0, start_year = 0;
                gchar *summary_str = NULL, *location_str = NULL, *description_str = NULL;
                int start_hour = 0, start_min = 0, end_hour = 0, end_min = 0;
                int is_yearly = 0, is_allday = 0, is_priority = 0;                
                
                // g_object_get allocates new heap buffers for string properties!
                g_object_get(day_event,
                             "startday",    &start_day,
                             "startmonth",  &start_month,
                             "startyear",   &start_year,
                             "summary",     &summary_str,
                             "location",    &location_str,
                             "description", &description_str,
                             "starthour",   &start_hour,
                             "startmin",    &start_min,
                             "endhour",     &end_hour,
                             "endmin",      &end_min,
                             "isyearly",    &is_yearly,
                             "isallday",    &is_allday,
                             "ispriority",  &is_priority,
                             NULL);                             

                gchar *des_loc_str = g_strdup("");
                gboolean has_desc = (description_str && *description_str != '\0');
                gboolean has_loc = (location_str && *location_str != '\0');                
                
                if (has_desc && has_loc) {
                    g_free(des_loc_str);
                    des_loc_str = g_strconcat(description_str, ". ", location_str, ".", NULL);
                } else if (has_desc) {
                    g_free(des_loc_str);
                    des_loc_str = g_strconcat(description_str, ".", NULL);
                } else if (has_loc) {
                    g_free(des_loc_str);
                    des_loc_str = g_strconcat(location_str, ".", NULL);
                }                

                if (!is_allday) {
                    gchar *time_str = get_time_str(start_hour, start_min);
                    g_string_append_printf(day_tooltip_gstr, "%s%s\n", 
                                           time_str ? time_str : "", 
                                           summary_str ? summary_str : "");
                    if (des_loc_str && *des_loc_str != '\0') {
                        g_string_append_printf(day_tooltip_gstr, "%s\n", des_loc_str);
                    }
                    g_free(time_str); 
                } else {
                    g_string_append_printf(day_tooltip_gstr, "%s\n", 
                                           summary_str ? summary_str : "");
                    if (des_loc_str && *des_loc_str != '\0') {
                        g_string_append_printf(day_tooltip_gstr, "%s\n", des_loc_str);
                    }
                }                

                // Flag the target day number inside your calendar layout system
                custom_calendar_mark_day(CUSTOM_CALENDAR(calendar), start_day);                 
                
                // Free string allocations created by g_object_get
                g_free(summary_str);
                g_free(location_str);
                g_free(description_str);
                g_free(des_loc_str);

                // FIX: Release the local database pointer reference to stop heap data accumulation!
                g_object_unref(day_event);
            }            

            if (day_tooltip_gstr->len > 0) {
                // Pass the data string over safely (this function handles internal duplication copies)
                custom_calendar_set_tooltip_str(CUSTOM_CALENDAR(calendar), day, day_tooltip_gstr->str);
            }            

            // Clean up the text segment and internal GString wrapper allocation structures seamlessly
            g_string_free(day_tooltip_gstr, TRUE);             
            
            // Clean up the temporary pointer collection wrapper structure safely
            g_array_free(events_for_day, TRUE); 
        }
    }
}

//======================================================================
//Search
//======================================================================

/**
 * @brief Handles selection activations within the search results list to jump to a specific date.
 * 
 * This callback is invoked when a row is selected within a search results GtkListBox. 
 * It performs the following sequence:
 * 1. Extracts the foundational widget tracking handles (`CustomCalendar` and `GListStore`) attached as instance metadata keys to the activated row.
 * 2. Unboxes the precise numeric target coordinates (Day, Month, Year) packed inside the row's object data pointers using macro casts.
 * 3. Commands the calendar widget layout engine to navigate directly to the target date page view.
 * 4. Updates global chronological tracking registers to ensure full view model synchronization.
 * 5. Rebuilds hover text tooltips, refreshes the grid, and updates the core collection storage data filter.
 * 6. Dismisses and tears down the parent dialog overlay window safely to return to the updated main application interface.
 *
 * @param listbox   The GtkListBox container tracking search output rows.
 * @param row       The specific activated or clicked GtkListBoxRow child item holding context data keys.
 * @param user_data A generic context pointer representing the parent search dialog window wrapper.
 * 
 * @return void
 */
static void callbk_jump_to_search_date(GtkListBox *listbox, GtkListBoxRow *row, gpointer user_data)
{
    GtkWidget *search_dialog = GTK_WIDGET(user_data);    

    // Extract the primary calendar and data store tracking handles from the clicked row
    GtkWidget *calendar = g_object_get_data(G_OBJECT(row), "target-calendar-key");
    GListStore *store   = g_object_get_data(G_OBJECT(row), "target-store-key");    

    // Extract the exact numeric calendar destination values from the row context data
    int target_day   = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(row), "jump-day-key"));
    int target_month = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(row), "jump-month-key"));
    int target_year  = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(row), "jump-year-key"));    

    if (calendar && store) {
        // Jump the main calendar component to the target date coordinates programmatically
        custom_calendar_goto_dmy(CUSTOM_CALENDAR(calendar), target_day, target_month, target_year);        

        // Synchronize active global tracker variables
        m_start_day   = target_day;
        m_start_month = target_month;
        m_start_year  = target_year;        

        // Trigger your standard main application view update passes
        set_tooltips_on_calendar(CUSTOM_CALENDAR(calendar));
        custom_calendar_update(CUSTOM_CALENDAR(calendar));
        update_store(CUSTOM_CALENDAR(calendar), store);  
    }    

    // Automatically dismiss and clear the search popup window overlay
    if (search_dialog) {
        gtk_window_destroy(GTK_WINDOW(search_dialog));
    }
}


/**
 * @brief Performs a search for events based on summary str
 * @param search_str The string to search for in event data.
 */
static void search_events_summary(const char* search_str, GtkWidget *main_window)
{
    char* search_str_lower = g_ascii_strdown(search_str, -1); 
    GtkWidget *dialog_search_results; 
    GtkWidget *scrolled_window; 
    GtkWidget *listbox;     
    
    dialog_search_results = gtk_window_new(); 
    gtk_window_set_title(GTK_WINDOW(dialog_search_results), "Search Results");
    gtk_window_set_default_size(GTK_WINDOW(dialog_search_results), 450, 350);     
    
    if (main_window && GTK_IS_WINDOW(main_window)) {
        gtk_window_set_transient_for(GTK_WINDOW(dialog_search_results), GTK_WINDOW(main_window));
        gtk_window_set_modal(GTK_WINDOW(dialog_search_results), TRUE);
    }    
    
    scrolled_window = gtk_scrolled_window_new(); 
    listbox = gtk_list_box_new();
    gtk_list_box_set_selection_mode(GTK_LIST_BOX(listbox), GTK_SELECTION_NONE);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), listbox); 
    
    g_signal_connect(listbox, "row-activated", G_CALLBACK(callbk_jump_to_search_date), dialog_search_results);    
    
    GtkWidget *calendar = g_object_get_data(G_OBJECT(main_window), "window-calendar-key");
    GListStore *store   = g_object_get_data(G_OBJECT(main_window), "window-store-key");    
    
    GArray* search_results = db_get_events_by_search(db_handle, search_str_lower, NULL); 
    if (search_results && search_results->len > 0) {
        for (guint i = 0; i < search_results->len; ++i) {
            CalendarEvent* event = g_array_index(search_results, CalendarEvent*, i);             
            
            // Sink the floating reference safely to one immediately upon retrieval.
            // This anchors the GObject structure, preventing GLib's automatic cleanup 
            // from throwing the G_IS_OBJECT assertion warning when the container is freed
            g_object_ref_sink(event);
            
            int day   = calendar_event_get_start_day(event);
            int month = calendar_event_get_start_month(event);
            int year  = calendar_event_get_start_year(event);            
            
            char *time_frag = "";
            gboolean spent_time_allocated = FALSE;
            
            if (!calendar_event_get_is_allday(event)) {
                time_frag = get_time_str(calendar_event_get_start_hour(event), calendar_event_get_start_min(event));
                spent_time_allocated = TRUE;
            }            
            
            char *row_text = g_strdup_printf("%02d/%02d/%04d  %s  %s  %s", 
                                             day, month, year,
                                             time_frag ? time_frag : "",
                                             calendar_event_get_summary(event) ? calendar_event_get_summary(event) : "",
                                             calendar_event_get_location(event) ? calendar_event_get_location(event) : "");            
            
            GtkWidget *row_label = gtk_label_new(row_text);
            gtk_widget_set_halign(row_label, GTK_ALIGN_START);
            gtk_widget_set_margin_start(row_label, 12);
            gtk_widget_set_margin_top(row_label, 6);
            gtk_widget_set_margin_bottom(row_label, 6);            
            
            GtkWidget *row_container = gtk_list_box_row_new();
            gtk_list_box_row_set_child(GTK_LIST_BOX_ROW(row_container), row_label);            
            
            g_object_set_data(G_OBJECT(row_container), "jump-day-key",       GINT_TO_POINTER(day));
            g_object_set_data(G_OBJECT(row_container), "jump-month-key",     GINT_TO_POINTER(month));
            g_object_set_data(G_OBJECT(row_container), "jump-year-key",      GINT_TO_POINTER(year));
            g_object_set_data(G_OBJECT(row_container), "target-calendar-key", calendar);
            g_object_set_data(G_OBJECT(row_container), "target-store-key",    store);            
            
            gtk_list_box_append(GTK_LIST_BOX(listbox), row_container);            
            
            g_free(row_text);
            if (spent_time_allocated && time_frag) {
                g_free(time_frag);
            }            
        }
        // This safely triggers clear_func rules, unreferencing elements from 1 to 0 completely!
        g_array_free(search_results, TRUE); 
    } else {
        GtkWidget *empty_label = gtk_label_new("No matching calendar events found.");
        gtk_widget_set_margin_start(empty_label, 12);
        gtk_list_box_append(GTK_LIST_BOX(listbox), empty_label);
        if (search_results) {
            g_array_free(search_results, TRUE);
        }
    }     
    
    g_free(search_str_lower);         
    gtk_window_set_child(GTK_WINDOW(dialog_search_results), scrolled_window); 
    gtk_window_present(GTK_WINDOW(dialog_search_results));     
}


/**
 * @brief Performs a search for events based on a location str
 * @param search_str The string to search for in event data.
 */

static void search_events_location(const char* search_str, GtkWidget *main_window)
{
    char* search_str_lower = g_ascii_strdown(search_str, -1); 
    GtkWidget *dialog_search_results; 
    GtkWidget *scrolled_window; 
    GtkWidget *listbox;     
    
    dialog_search_results = gtk_window_new(); 
    gtk_window_set_title(GTK_WINDOW(dialog_search_results), "Search Results");
    gtk_window_set_default_size(GTK_WINDOW(dialog_search_results), 450, 350);     
    
    if (main_window && GTK_IS_WINDOW(main_window)) {
        gtk_window_set_transient_for(GTK_WINDOW(dialog_search_results), GTK_WINDOW(main_window));
        gtk_window_set_modal(GTK_WINDOW(dialog_search_results), TRUE);
    }    
    
    scrolled_window = gtk_scrolled_window_new(); 
    listbox = gtk_list_box_new();
    gtk_list_box_set_selection_mode(GTK_LIST_BOX(listbox), GTK_SELECTION_NONE);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), listbox); 
    
    g_signal_connect(listbox, "row-activated", G_CALLBACK(callbk_jump_to_search_date), dialog_search_results);    
    
    GtkWidget *calendar = g_object_get_data(G_OBJECT(main_window), "window-calendar-key");
    GListStore *store   = g_object_get_data(G_OBJECT(main_window), "window-store-key");    
    
    // Querying by passing search_str_lower into the location (third) argument parameter
    GArray* search_results = db_get_events_by_search(db_handle, NULL, search_str_lower); 
    if (search_results && search_results->len > 0) {
        for (guint i = 0; i < search_results->len; ++i) {
            CalendarEvent* event = g_array_index(search_results, CalendarEvent*, i);             
            
            // Anchor the floating reference to one right upon retrieval.
            // This stops the background automatic cleanup engine from throwing G_IS_OBJECT errors!
            g_object_ref_sink(event);
            
            int day   = calendar_event_get_start_day(event);
            int month = calendar_event_get_start_month(event);
            int year  = calendar_event_get_start_year(event);            
            
            char *time_frag = "";
            gboolean spent_time_allocated = FALSE;
            
            if (!calendar_event_get_is_allday(event)) {
                time_frag = get_time_str(calendar_event_get_start_hour(event), calendar_event_get_start_min(event));
                spent_time_allocated = TRUE;
            }            
            
            char *row_text = g_strdup_printf("%02d/%02d/%04d  %s  %s  %s", 
                                             day, month, year,
                                             time_frag ? time_frag : "",
                                             calendar_event_get_summary(event) ? calendar_event_get_summary(event) : "",
                                             calendar_event_get_location(event) ? calendar_event_get_location(event) : "");            
            
            GtkWidget *row_label = gtk_label_new(row_text);
            gtk_widget_set_halign(row_label, GTK_ALIGN_START);
            gtk_widget_set_margin_start(row_label, 12);
            gtk_widget_set_margin_top(row_label, 6);
            gtk_widget_set_margin_bottom(row_label, 6);            
            
            GtkWidget *row_container = gtk_list_box_row_new();
            gtk_list_box_row_set_child(GTK_LIST_BOX_ROW(row_container), row_label);            
            
            // Map widget key bindings identically onto the row dataset configurations
            g_object_set_data(G_OBJECT(row_container), "jump-day-key",       GINT_TO_POINTER(day));
            g_object_set_data(G_OBJECT(row_container), "jump-month-key",     GINT_TO_POINTER(month));
            g_object_set_data(G_OBJECT(row_container), "jump-year-key",      GINT_TO_POINTER(year));
            g_object_set_data(G_OBJECT(row_container), "target-calendar-key", calendar);
            g_object_set_data(G_OBJECT(row_container), "target-store-key",    store);            
            
            gtk_list_box_append(GTK_LIST_BOX(listbox), row_container);            
            
            g_free(row_text);
            if (spent_time_allocated && time_frag) {
                g_free(time_frag);
            }            
        }
        // Safely triggers the container clear_func, freeing every processed event object cleanly
        g_array_free(search_results, TRUE); 
    } else {
        GtkWidget *empty_label = gtk_label_new("No matching calendar events found.");
        gtk_widget_set_margin_start(empty_label, 12);
        gtk_list_box_append(GTK_LIST_BOX(listbox), empty_label);
        if (search_results) {
            g_array_free(search_results, TRUE);
        }
    }     
    
    g_free(search_str_lower);         
    gtk_window_set_child(GTK_WINDOW(dialog_search_results), scrolled_window); 
    gtk_window_present(GTK_WINDOW(dialog_search_results));     
}


/**
 * @brief Callback for the search button in the search dialog.
 * @param button The GtkButton that triggered the callback.
 * @param user_data  (unused) 
 */

static void callbk_search_events(GtkButton *button, gpointer user_data)
{
    g_return_if_fail(GTK_IS_BUTTON(button));
    
    GtkWidget *main_window = GTK_WIDGET(user_data);
    GtkWidget *check_button_search_location = g_object_get_data(G_OBJECT(button), "check-button-search-location-key");
    int is_search_location = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_search_location)); 
    
    const char *final_search_term = NULL;
    char *clean_search_str = NULL;
    
    if (is_search_location) {
        GtkWidget *entry_search = g_object_get_data(G_OBJECT(button), "entry-search-key"); 
        GtkEntryBuffer *buffer_search = gtk_entry_get_buffer(GTK_ENTRY(entry_search));
        final_search_term = gtk_entry_buffer_get_text(buffer_search);
        
        clean_search_str = sanitize_text(final_search_term);
    } else {
        GtkWidget *dropdown_summary = g_object_get_data(G_OBJECT(button), "dropdown-search-summary-key");
        GtkStringObject *selected_item = GTK_STRING_OBJECT(gtk_drop_down_get_selected_item(GTK_DROP_DOWN(dropdown_summary)));
        
        if (selected_item) {
            final_search_term = gtk_string_object_get_string(selected_item);
            clean_search_str = g_strdup(final_search_term); 
        }
    }
    
    if (clean_search_str == NULL || strlen(clean_search_str) == 0) {
        g_warning("Search query is completely empty. Aborting search request pass.\n");
        if (clean_search_str) {
            // Use g_free instead of standard free
            g_free(clean_search_str);
        }
        return;
    } 
    
    if (is_search_location) {
        search_events_location(clean_search_str, main_window);
    } else {
        search_events_summary(clean_search_str, main_window);
    } 
    
    if (clean_search_str != NULL) {
        //  Use g_free instead of standard free to clean up GLib heap slices cleanly
        g_free(clean_search_str);
        clean_search_str = NULL;
    }
}


//======================================================================
// Search 
//======================================================================

/**
 * @brief Callback for the search action, which opens a search dialog.
 * @param action The GSimpleAction that triggered the callback.
 * @param parameter The GVariant parameter (unused).
 * @param user_data A pointer to the GtkWindow.
 */
//======================================================================
static void callbk_search(GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
    GtkWidget *window = user_data;    
    GtkWidget *dialog_search;    
    GtkWidget *box;
    GtkWidget *button_search;    
    GtkWidget *label_summary_search;
    GtkWidget *dropdown_search_summary; // Added DropDown container
    GtkWidget *label_entry_search;
    GtkWidget *entry_search;    
    GtkWidget *check_button_search_location;       
    
    dialog_search = gtk_window_new(); 
    gtk_window_set_title(GTK_WINDOW(dialog_search), "Search Events");
    gtk_window_set_default_size(GTK_WINDOW(dialog_search), 320, 150);    
    
    if (window && GTK_IS_WINDOW(window)) {
        gtk_window_set_transient_for(GTK_WINDOW(dialog_search), GTK_WINDOW(window));
        gtk_window_set_modal(GTK_WINDOW(dialog_search), TRUE);
    }    
    
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6); // Slightly extended layout margins
    gtk_widget_set_margin_start(box, 12);
    gtk_widget_set_margin_end(box, 12);
    gtk_widget_set_margin_top(box, 12);
    gtk_widget_set_margin_bottom(box, 12);
    gtk_window_set_child(GTK_WINDOW(dialog_search), box);    
    
    // Check Option
    check_button_search_location = gtk_check_button_new_with_label("Search Location (Uses Text Box)");    
    
    // Summary Selection via explicit Dropdown matching lists
    label_summary_search = gtk_label_new("Select Summary Category: ");
    gtk_widget_set_halign(label_summary_search, GTK_ALIGN_START);
    dropdown_search_summary = gtk_drop_down_new_from_strings(events); 
    
    // Alternative text string entry fields
    label_entry_search = gtk_label_new("Or Type Location Query: ");
    gtk_widget_set_halign(label_entry_search, GTK_ALIGN_START);
    entry_search = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry_search), 100);    
    
    button_search = gtk_button_new_with_label("Search");
    g_signal_connect(button_search, "clicked", G_CALLBACK(callbk_search_events), window);     
    //g_signal_connect(button_search, "clicked", G_CALLBACK(callbk_search_events), window);   
    g_signal_connect_swapped(button_search, "clicked", G_CALLBACK(gtk_window_destroy), dialog_search);    
    
    // Bind keys onto object data maps for lookup processing inside callbk_search_events
    g_object_set_data(G_OBJECT(button_search), "check-button-search-location-key", check_button_search_location);
    g_object_set_data(G_OBJECT(button_search), "dialog-search-key", dialog_search);
    g_object_set_data(G_OBJECT(button_search), "entry-search-key", entry_search);    
    g_object_set_data(G_OBJECT(button_search), "dropdown-search-summary-key", dropdown_search_summary); // Linked key
    
    // Pack into visual sequence cleanly
    gtk_box_append(GTK_BOX(box), label_summary_search);
    gtk_box_append(GTK_BOX(box), dropdown_search_summary);
    gtk_box_append(GTK_BOX(box), label_entry_search);
    gtk_box_append(GTK_BOX(box), entry_search);    
    gtk_box_append(GTK_BOX(box), check_button_search_location);    
    gtk_box_append(GTK_BOX(box), button_search);    
    
    gtk_window_present(GTK_WINDOW(dialog_search));    
}

	
//======================================================================
//Easter calculator
//======================================================================
/**
 * @brief Calculates the date of Easter for a given year.
 * @param year The year to calculate Easter for.
 * @return A newly allocated GDate object with the date of Easter. 
 * The caller is responsible for freeing this.
 */
GDate* calculate_easter(gint year) 
{
	// Implementation of Meeus/Jones/Butcher algorithm
	int a = year % 19;
    int b = year / 100;
    int c = year % 100;
    int d = b / 4;
    int e = b % 4;
    int f = (b + 8) / 25;
    int g = (b - f + 1) / 3;
    int h = (19 * a + b - d - g + 15) % 30;
    int i = c / 4;
    int k = c % 4;
    int l = (32 + 2 * e + 2 * i - h - k) % 7;
    int m = (a + 11 * h + 22 * l) / 451;
	
	int easter_month = (h + l - 7 * m + 114) / 31;
    int easter_day = ((h + l - 7 * m + 114) % 31) + 1;
	
	GDate *easter_date = g_date_new_dmy(easter_day, easter_month, year);
    return easter_date;
}

/**
 * @brief Callback for the calculate button in the Easter dialog.
 * @param button The GtkButton that triggered the callback.
 * @param user_data A pointer to the GtkSpinButton with the year.
 */
static void callbk_calc_easter(GtkButton *button, gpointer user_data)
{
    GtkWidget *label_result = g_object_get_data(G_OBJECT(button), "label-result-key");
    GtkWidget *spin_button_year = g_object_get_data(G_OBJECT(button), "spin-year-key");
    
    int easter_year = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_year));
    
    GDate* easter_date = calculate_easter(easter_year);
    
    int easter_day = g_date_get_day(easter_date);
    int easter_month = g_date_get_month(easter_date);
    
    // Note: get_month_string and get_day_of_week return static string literals (e.g., "sunday", "march")
    // from internal switch statements, so they do NOT need to be freed.
    char *easter_month_str = get_month_string(easter_month);
    char *weekday = get_day_of_week(easter_day, easter_month, easter_year); 
        
    // Allocate the entire formatted string cleanly in a single pass
    char *result_str = g_strdup_printf("%s %i %s %i", weekday, easter_day, easter_month_str, easter_year);
    
    gtk_label_set_text(GTK_LABEL(label_result), result_str);
    
    // Clean up all allocated structures 
    g_free(result_str);    
    g_date_free(easter_date);    
}
	
/**
 * @brief Callback for the Easter calculation action, which opens a dialog.
 * @param action The GSimpleAction that triggered the callback.
 * @param parameter The GVariant parameter (unused).
 * @param user_data A pointer to the GtkWindow.
 */
static void callbk_easter(GSimpleAction *action, GVariant *parameter,  gpointer user_data)
{
	GtkWidget *window = user_data;
	GtkWidget *dialog_easter;	
	GtkWidget *box;
	GtkWidget *button_calc_easter;
	
	GtkWidget *label_select_year;
	GtkWidget *spin_button_year;
	GtkWidget *label_result;
	
	dialog_easter = gtk_window_new(); 
	gtk_window_set_title(GTK_WINDOW(dialog_easter), "Easter");
	gtk_window_set_default_size(GTK_WINDOW(dialog_easter), 300, 100);
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
	gtk_window_set_child(GTK_WINDOW(dialog_easter), box);
	
	label_select_year = gtk_label_new("Select Year ");
	
	GtkAdjustment *adjustment_year = gtk_adjustment_new(2024.00, 0.0, 5000.00, 1.0, 1.0, 0.0);
	spin_button_year = gtk_spin_button_new(adjustment_year, 2025.00, 0);
	
	label_result = gtk_label_new("");
	
	button_calc_easter = gtk_button_new_with_label("Calculate Easter");
	g_signal_connect(button_calc_easter, "clicked", G_CALLBACK(callbk_calc_easter), window);
	
	g_object_set_data(G_OBJECT(button_calc_easter), "label-result-key", label_result);
	g_object_set_data(G_OBJECT(button_calc_easter), "spin-year-key", spin_button_year);
	
	gtk_box_append(GTK_BOX(box), label_select_year);
	gtk_box_append(GTK_BOX(box), spin_button_year);
	gtk_box_append(GTK_BOX(box), label_result);
	gtk_box_append(GTK_BOX(box), button_calc_easter);	
	gtk_window_present(GTK_WINDOW(dialog_easter));
	
}

//======================================================================
// Preferences
//======================================================================

/**
 * @brief Callback function for the setting preferences button.
 * @param button The GtkButton that triggered the callback.
 * @param user_data A pointer to the GtkWindow.
 */
 static void callbk_set_preferences(GtkButton *button, gpointer user_data)
{
    GtkWidget *window = user_data; 
    GtkWidget *calendar = g_object_get_data(G_OBJECT(window), "window-calendar-key");
    GtkWidget *dialog = g_object_get_data(G_OBJECT(button), "dialog-key");    
    // Calendar layout checkboxes
    GtkWidget *check_button_hour_format   = g_object_get_data(G_OBJECT(button), "check-button-hour-format-key");
    GtkWidget *check_button_show_end_time = g_object_get_data(G_OBJECT(button), "check-button-show-end-time-key");
    GtkWidget *check_button_show_tooltips = g_object_get_data(G_OBJECT(button), "check-button-show-tooltips-key");
    GtkWidget *check_button_dark_theme    = g_object_get_data(G_OBJECT(button), "check-button-dark-theme-key");
    GtkWidget *check_button_notable_dates = g_object_get_data(G_OBJECT(button), "check-button-notable-dates-key");    
    // Color Dialog Button pointers
    GtkWidget *colour_button_today        = g_object_get_data(G_OBJECT(button), "colour-button-today-key");
    GtkWidget *colour_button_event        = g_object_get_data(G_OBJECT(button), "colour-button-event-key");
    GtkWidget *colour_button_notable      = g_object_get_data(G_OBJECT(button), "colour-button-notable-key"); // Added    
    
    // Extract and safely re-allocate the Today Colour property string
    const GdkRGBA *rgba_today = gtk_color_dialog_button_get_rgba(GTK_COLOR_DIALOG_BUTTON(colour_button_today));
    g_free(m_todaycolour); // CRUCIAL LEAK FIX: Free old heap data first!
    m_todaycolour = gdk_rgba_to_string(rgba_today);    
    
    // Extract and safely re-allocate the Event Colour property string
    const GdkRGBA *rgba_event = gtk_color_dialog_button_get_rgba(GTK_COLOR_DIALOG_BUTTON(colour_button_event));
    g_free(m_eventcolour); // CRUCIAL LEAK FIX: Free old heap data first!
    m_eventcolour = gdk_rgba_to_string(rgba_event);
    
    // New: Extract and safely re-allocate the Notable Holiday Colour property string
    const GdkRGBA *rgba_notable = gtk_color_dialog_button_get_rgba(GTK_COLOR_DIALOG_BUTTON(colour_button_notable));
    g_free(m_notablecolour); // CRUCIAL LEAK FIX: Free old heap data first!
    m_notablecolour = gdk_rgba_to_string(rgba_notable);    
    
    // Speech loop settings parameters
    GtkWidget *check_button_talk              = g_object_get_data(G_OBJECT(button), "check-button-talk-key");
    GtkWidget *check_button_talk_startup      = g_object_get_data(G_OBJECT(button), "check-button-talk-startup-key");
    GtkWidget *check_button_talk_event_number = g_object_get_data(G_OBJECT(button), "check-button-talk-event-number-key");
    GtkWidget *check_button_talk_upcoming     = g_object_get_data(G_OBJECT(button), "check-button-talk-upcoming-key");
    GtkWidget *spin_button_upcoming_days     = g_object_get_data(G_OBJECT(button), "spin-upcoming-days-key");
    GtkWidget *spin_button_talk_rate         = g_object_get_data(G_OBJECT(button), "spin-talk-rate-key");
    GtkWidget *check_button_reset_all         = g_object_get_data(G_OBJECT(button), "check-button-reset-all-key");    
    
    // Save element statuses down onto variables
    m_12hour_format   = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_hour_format));
    m_use_end_time    = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_show_end_time));
    m_show_tooltips   = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_show_tooltips));
    m_is_dark_theme   = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_dark_theme));
    m_notable_dates   = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_notable_dates));
    
    m_talk             = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_talk));
    m_talk_at_startup  = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_talk_startup));
    m_talk_event_number = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_talk_event_number));
    m_talk_upcoming    = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_talk_upcoming));
    
    m_upcoming_days    = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_upcoming_days));
    m_talk_rate        = (int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_talk_rate));
    m_reset_preferences = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_reset_all));
    
    if (m_reset_preferences) {
        m_12hour_format = TRUE;
        m_use_end_time  = FALSE;
        m_window_width  = 800;
        m_window_height = 600;
        m_show_tooltips = TRUE;
        m_is_dark_theme = FALSE;
        
        g_free(m_todaycolour);
        g_free(m_eventcolour);
        g_free(m_notablecolour);
        
        m_todaycolour   = g_strdup("rgb(141,166,141)"); 
        m_eventcolour   = g_strdup("rgb(217,230,217)"); 
        m_notablecolour = g_strdup("rgb(245,245,220)"); // reset default to beige
        
        m_talk              = TRUE;
        m_talk_at_startup   = FALSE;
        m_talk_event_number = FALSE;
        m_talk_rate         = 16000;
        m_talk_upcoming     = FALSE;
        m_upcoming_days     = 7;
        m_notable_dates     = TRUE;
        m_reset_preferences = FALSE; 
    }
    
    config_write(); // Write out updated properties to GKeyFile on your disk
    
    // Inject the updated colors directly across your custom object properties safely
    g_object_set(calendar, "todaycolour", m_todaycolour, NULL);
    g_object_set(calendar, "eventcolour", m_eventcolour, NULL);
    custom_calendar_set_notable_colour(CUSTOM_CALENDAR(calendar), m_notablecolour); // Dynamic update
    
    custom_calendar_set_show_tooltips(CUSTOM_CALENDAR(calendar), m_show_tooltips);
    
    // Refresh the holiday layout marks and colors inside your main view grid
    set_notables_on_calendar(CUSTOM_CALENDAR(calendar));
    custom_calendar_update(CUSTOM_CALENDAR(calendar));
    
    GListStore *store = g_object_get_data(G_OBJECT(calendar), "calendar-store-key");
    callbk_calendar_day_selected(CUSTOM_CALENDAR(calendar), store);
    
    //GtkSettings *settings = gtk_widget_get_settings(gtk_widget_get_settings(window));
    //g_object_set(settings, "gtk-application-prefer-dark-theme", m_is_dark_theme, NULL);
    GtkSettings *settings = gtk_widget_get_settings(GTK_WIDGET(window));
	g_object_set(settings, "gtk-application-prefer-dark-theme", m_is_dark_theme, NULL);
    
    gtk_window_destroy(GTK_WINDOW(dialog));
}
/**
 * @brief Callback for the preferences action, which opens a preferences dialog.
 * @param action The GSimpleAction that triggered the callback.
 * @param parameter The GVariant parameter (unused).
 * @param user_data A pointer to the GtkWindow.
 */
static void callbk_preferences(GSimpleAction* action, GVariant *parameter, gpointer user_data)
{
    GtkWidget *window = user_data;
    GtkWidget *dialog;
    GtkWidget *grid;
    GtkWidget *button_set;
    
    GtkWidget *check_button_hour_format;
    GtkWidget *check_button_show_end_time;
    GtkWidget *check_button_show_tooltips;
    GtkWidget *check_button_dark_theme;
    GtkWidget *check_button_notable_dates;
    
    GtkWidget *label_todaycolour;
    GtkWidget *label_eventcolour; 
    GtkWidget *label_notablecolour; // Added Label
    GtkWidget *check_button_reset_all; 
    
    GtkWidget *check_button_talk; 
    GtkWidget *check_button_talk_startup; 
    GtkWidget *check_button_talk_event_number;
    GtkWidget *check_button_talk_upcoming; 
    GtkWidget *label_upcoming_days;
    GtkWidget *spin_button_upcoming_days;
    GtkWidget *label_talk_rate;
    GtkWidget *spin_button_talk_rate;
    
    GtkWidget *label_spacer1, *label_spacer2, *label_spacer3, *label_spacer4, *label_spacer5, *label_spacer6;
    
    label_spacer1 = gtk_label_new(""); label_spacer2 = gtk_label_new("");
    label_spacer3 = gtk_label_new(""); label_spacer4 = gtk_label_new("");
    label_spacer5 = gtk_label_new(""); label_spacer6 = gtk_label_new("");
    
    dialog = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(dialog), "Preferences");
    gtk_window_set_modal(GTK_WINDOW(dialog), TRUE);
    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));
    
    grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 4); // Added subtle vertical spacing padding
    
    button_set = gtk_button_new_with_label("Set Preferences");
    g_signal_connect(button_set, "clicked", G_CALLBACK(callbk_set_preferences), window);
    
    // Instantiating the Today Colour Picker Button
    GtkColorDialog *dialog_today = gtk_color_dialog_new();
    GtkWidget *colour_button_today = gtk_color_dialog_button_new(dialog_today);
    GdkRGBA rgba_today;
    if (gdk_rgba_parse(&rgba_today, m_todaycolour)) {
        gtk_color_dialog_button_set_rgba(GTK_COLOR_DIALOG_BUTTON(colour_button_today), &rgba_today);
    } 
    
    // Instantiating the Event Colour Picker Button
    GtkColorDialog *dialog_event = gtk_color_dialog_new();
    GtkWidget *colour_button_event = gtk_color_dialog_button_new(dialog_event);
    GdkRGBA rgba_event;
    if (gdk_rgba_parse(&rgba_event, m_eventcolour)) {
        gtk_color_dialog_button_set_rgba(GTK_COLOR_DIALOG_BUTTON(colour_button_event), &rgba_event);
    }

    // New: Instantiating the Notable Holiday Colour Picker Button
    GtkColorDialog *dialog_notable = gtk_color_dialog_new();
    GtkWidget *colour_button_notable = gtk_color_dialog_button_new(dialog_notable);
    GdkRGBA rgba_notable;
    if (gdk_rgba_parse(&rgba_notable, m_notablecolour)) {
        gtk_color_dialog_button_set_rgba(GTK_COLOR_DIALOG_BUTTON(colour_button_notable), &rgba_notable);
    }
    
    label_todaycolour   = gtk_label_new("Today Colour: ");
    label_eventcolour   = gtk_label_new("Event Colour: ");
    label_notablecolour = gtk_label_new("Notable Colour: "); // Label setup
    
    gtk_widget_set_halign(label_todaycolour, GTK_ALIGN_START);
    gtk_widget_set_halign(label_eventcolour, GTK_ALIGN_START);
    gtk_widget_set_halign(label_notablecolour, GTK_ALIGN_START);
    
    check_button_hour_format   = gtk_check_button_new_with_label("12 Hour Format");
    check_button_show_end_time = gtk_check_button_new_with_label("Use End Time");

	check_button_show_tooltips = gtk_check_button_new_with_label("Use Calendar Tooltips");
	check_button_dark_theme = gtk_check_button_new_with_label("Use Dark Theme");
	check_button_notable_dates = gtk_check_button_new_with_label("Notable Dates");
	check_button_talk = gtk_check_button_new_with_label("Enable Talking");
	check_button_talk_startup = gtk_check_button_new_with_label("Talk At Startup");
	check_button_talk_event_number = gtk_check_button_new_with_label("Talk Event Number");
	check_button_talk_upcoming = gtk_check_button_new_with_label("Talk Upcoming");
	check_button_reset_all = gtk_check_button_new_with_label("Reset All");
	GtkAdjustment *adjustment_upcoming_days = gtk_adjustment_new(7.00, 1.00, 14.00, 1.0, 1.0, 0.0);
	label_upcoming_days = gtk_label_new("Upcoming days: ");
	spin_button_upcoming_days = gtk_spin_button_new(adjustment_upcoming_days, 7, 0);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_upcoming_days), m_upcoming_days);
	GtkAdjustment *adjustment_talk_rate = gtk_adjustment_new(10000.00, 5000.00, 20000.00, 1000.0, 1000.0, 0.0);
	label_talk_rate = gtk_label_new("Talk Rate ");
	spin_button_talk_rate = gtk_spin_button_new(adjustment_talk_rate, 10000, 0);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_talk_rate), m_talk_rate);
	// Set checkboxes initial visual toggle active state
	gtk_check_button_set_active(GTK_CHECK_BUTTON(check_button_hour_format), m_12hour_format);
	gtk_check_button_set_active(GTK_CHECK_BUTTON(check_button_show_end_time), m_use_end_time);
	gtk_check_button_set_active(GTK_CHECK_BUTTON(check_button_show_tooltips), m_show_tooltips);
	gtk_check_button_set_active(GTK_CHECK_BUTTON(check_button_dark_theme), m_is_dark_theme);
	gtk_check_button_set_active(GTK_CHECK_BUTTON(check_button_notable_dates), m_notable_dates);
	gtk_check_button_set_active(GTK_CHECK_BUTTON(check_button_talk), m_talk);
	gtk_check_button_set_active(GTK_CHECK_BUTTON(check_button_talk_startup), m_talk_at_startup);
	gtk_check_button_set_active(GTK_CHECK_BUTTON(check_button_talk_event_number), m_talk_event_number);
	gtk_check_button_set_active(GTK_CHECK_BUTTON(check_button_talk_upcoming), m_talk_upcoming);
	gtk_check_button_set_active(GTK_CHECK_BUTTON(check_button_reset_all), m_reset_preferences);
	// Map object keys securely onto the save action button object
	g_object_set_data(G_OBJECT(button_set), "dialog-key", dialog);
	g_object_set_data(G_OBJECT(button_set), "check-button-hour-format-key", check_button_hour_format);
	g_object_set_data(G_OBJECT(button_set), "check-button-show-end-time-key", check_button_show_end_time);
	g_object_set_data(G_OBJECT(button_set), "check-button-show-tooltips-key", check_button_show_tooltips);
	g_object_set_data(G_OBJECT(button_set), "check-button-dark-theme-key", check_button_dark_theme);
	g_object_set_data(G_OBJECT(button_set), "check-button-notable-dates-key", check_button_notable_dates);
	g_object_set_data(G_OBJECT(button_set), "check-button-talk-key", check_button_talk);
	g_object_set_data(G_OBJECT(button_set), "check-button-talk-startup-key", check_button_talk_startup);
	g_object_set_data(G_OBJECT(button_set), "check-button-talk-event-number-key", check_button_talk_event_number);
	g_object_set_data(G_OBJECT(button_set), "check-button-talk-upcoming-key", check_button_talk_upcoming);
	g_object_set_data(G_OBJECT(button_set), "spin-upcoming-days-key", spin_button_upcoming_days);
	g_object_set_data(G_OBJECT(button_set), "spin-talk-rate-key", spin_button_talk_rate);
	g_object_set_data(G_OBJECT(button_set), "colour-button-today-key", colour_button_today);
	g_object_set_data(G_OBJECT(button_set), "colour-button-event-key", colour_button_event);
	g_object_set_data(G_OBJECT(button_set), "colour-button-notable-key", colour_button_notable); // Linked key
	g_object_set_data(G_OBJECT(button_set), "check-button-reset-all-key", check_button_reset_all);
	// Attach components to grid columns homogeneously
	gtk_grid_attach(GTK_GRID(grid), check_button_hour_format, 1, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), check_button_show_end_time, 2, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), check_button_notable_dates, 3, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), check_button_show_tooltips, 1, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), check_button_dark_theme, 2, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), label_spacer1, 1, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), label_todaycolour, 1, 4, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), colour_button_today, 2, 4, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), label_eventcolour, 1, 5, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), colour_button_event, 2, 5, 1, 1);
	// Appending the new Holiday row option right below
	gtk_grid_attach(GTK_GRID(grid), label_notablecolour, 1, 6, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), colour_button_notable, 2, 6, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), label_spacer2, 1, 7, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), check_button_talk, 1, 8, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), check_button_talk_startup, 2, 8, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), check_button_talk_event_number, 3, 8, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), label_spacer3, 1, 9, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), check_button_talk_upcoming, 1, 10, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), label_upcoming_days, 2, 10, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), spin_button_upcoming_days, 3, 10, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), label_spacer4, 1, 11, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), label_talk_rate, 1, 12, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), spin_button_talk_rate, 2, 12, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), label_spacer5, 1, 13, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), check_button_reset_all, 1, 14, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), label_spacer6, 1, 15, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), button_set, 1, 16, 3, 1);
	gtk_window_set_child(GTK_WINDOW(dialog), grid);
	gtk_window_present(GTK_WINDOW(dialog));
} 
//======================================================================
// About
//======================================================================
/**
 * @brief Callback for the about action, which opens an about dialog.
 * @param action The GSimpleAction that triggered the callback.
 * @param parameter The GVariant parameter (unused).
 * @param user_data A pointer to the GtkWindow.
 */
static void callbk_about(GSimpleAction * action, GVariant *parameter, gpointer user_data)
{
	
	GtkWidget *window = user_data;
	const gchar *authors[] = {"Alan Crispin", NULL};
	GtkWidget *about_dialog;
	about_dialog = gtk_about_dialog_new();
	gtk_window_set_transient_for(GTK_WINDOW(about_dialog),GTK_WINDOW(window));
	gtk_widget_set_size_request(about_dialog, 200,200);
	gtk_window_set_modal(GTK_WINDOW(about_dialog),TRUE);
	gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(about_dialog), "Talk Calendar (GTK4)");
	gtk_about_dialog_set_version (GTK_ABOUT_DIALOG(about_dialog), "Version 0.8.3");
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(about_dialog),"Copyright © 2026");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(about_dialog),"Talking Calendar");
	gtk_about_dialog_set_license_type (GTK_ABOUT_DIALOG(about_dialog), GTK_LICENSE_GPL_3_0);
	gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(about_dialog),"https://github.com/crispinprojects/");
	gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(about_dialog),"Talk Calendar Website");
	gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(about_dialog), authors);
	gtk_about_dialog_set_logo_icon_name(GTK_ABOUT_DIALOG(about_dialog), "x-office-calendar");
	gtk_widget_set_visible (about_dialog, TRUE);
}

/**
 * @brief Gets the total number of events from the database.
 * @return The total count of events.
 */
 int  get_total_number_of_events(void)
 {
	 int num_events =0; 
	 GArray* all_events = db_get_all_events(db_handle); 
	 num_events=all_events->len;  
	 return num_events;
 }
 
 int get_number_of_day_events(void)
 {		 
	 int  num_day_events =db_get_number_day_events(db_handle, m_start_year, m_start_month, m_start_day);
     //g_print("date =%d-%d-%d number day events = %d\n", m_start_day,m_start_month,m_start_year,num_day_events);
	 return num_day_events;
 }

/**
 * @brief Callback for the info action, which opens an info dialog.
 * @param action The GSimpleAction that triggered the callback.
 * @param parameter The GVariant parameter (unused).
 * @param user_data A pointer to the GtkWindow.
 */
static void callbk_info(GSimpleAction *action, GVariant *parameter,  gpointer user_data)
{
	GtkWidget *window =user_data;
	GtkWidget *calendar =g_object_get_data(G_OBJECT(window), "window-calendar-key");
	GtkWidget *dialog;
	GtkWidget *box;
	
	GtkWidget *label_keyboard_shortcuts;	
	GtkWidget *label_home_shortcut;
	
	GtkWidget *label_new_shortcut;
	GtkWidget *label_edit_shortcut;
	GtkWidget *label_delete_shortcut;
	
	GtkWidget *label_preferences_shortcut;
	GtkWidget *label_info_shortcut;
	GtkWidget *label_speak_shortcut;
	GtkWidget *label_time_shortcut;
	
	GtkWidget *label_record_info;
	GtkWidget *label_record_number;
	GtkWidget *label_sqlite_version;
	
	GSettings *settings;
	
	PangoAttrList *attrs;
	attrs = pango_attr_list_new();	 
	pango_attr_list_insert(attrs, pango_attr_weight_new(PANGO_WEIGHT_BOLD));
	
	dialog =gtk_window_new();
	
	gtk_window_set_default_size(GTK_WINDOW(dialog),380,100);
	gtk_window_set_title (GTK_WINDOW (dialog), "Information");
	
	box =gtk_box_new(GTK_ORIENTATION_VERTICAL,1);
	gtk_window_set_child (GTK_WINDOW (dialog), box);
	
	label_keyboard_shortcuts=gtk_label_new("Keyboard Shortcuts");
	gtk_label_set_attributes (GTK_LABEL (label_keyboard_shortcuts), attrs);
	
	label_home_shortcut=gtk_label_new("HOME: Go to today");	
	label_new_shortcut=gtk_label_new("Ctrl+N: New Event");
	label_edit_shortcut=gtk_label_new("Ctrl+E: Edit Selected Event");
	label_delete_shortcut=gtk_label_new("DELETE: Delete Selected Event");			
	
	label_preferences_shortcut=gtk_label_new("Ctrl+Alt+P: Preferences");
	label_info_shortcut=gtk_label_new("F1: Information");
	label_speak_shortcut=gtk_label_new("SPACEBAR: Speak Day");
	label_time_shortcut=gtk_label_new("T: Speak Time");
	
	label_record_info=gtk_label_new("Storage");
	gtk_label_set_attributes (GTK_LABEL (label_record_info), attrs);
	
	char* record_num_str =" Number of Records = ";
	char* n_str = g_strdup_printf("%d", get_total_number_of_events());
	record_num_str = g_strconcat(record_num_str, n_str,NULL);
	label_record_number =gtk_label_new(record_num_str);
	
	char* sqlite_version_str =" Sqlite Version  = ";
	char* v_str = g_strdup_printf("%s ", sqlite3_libversion());
	sqlite_version_str = g_strconcat(sqlite_version_str, v_str,NULL);
	label_sqlite_version =gtk_label_new(sqlite_version_str); 
	
	gtk_box_append(GTK_BOX(box),label_keyboard_shortcuts);
	gtk_box_append(GTK_BOX(box),label_home_shortcut);
	gtk_box_append(GTK_BOX(box),label_new_shortcut);
	gtk_box_append(GTK_BOX(box),label_edit_shortcut);
	gtk_box_append(GTK_BOX(box),label_delete_shortcut);		
	gtk_box_append(GTK_BOX(box),label_preferences_shortcut);
	gtk_box_append(GTK_BOX(box),label_info_shortcut);
	gtk_box_append(GTK_BOX(box), label_speak_shortcut);	
	gtk_box_append(GTK_BOX(box), label_time_shortcut);
	
	gtk_box_append(GTK_BOX(box), label_record_info);
	gtk_box_append(GTK_BOX(box), label_record_number);
	gtk_box_append(GTK_BOX(box), label_sqlite_version);	
	pango_attr_list_unref(attrs);
	
	gtk_window_present (GTK_WINDOW (dialog));	
	gtk_window_set_focus(GTK_WINDOW(window), GTK_WIDGET(calendar));
}


//======================================================================
//  get_upcoming_array 
//======================================================================

GArray* get_upcoming_array(int upcoming_days)
{
    GArray *evt_arry_upcoming = g_array_new(FALSE, FALSE, sizeof(CalendarEvent*));
    GDate *today_date = g_date_new();
    g_date_set_time_t(today_date, time(NULL));
    int today = g_date_get_day(today_date);
    int month = g_date_get_month(today_date);
    int year = g_date_get_year(today_date);
    g_date_free(today_date);
    GDate* date = g_date_new_dmy(today, month, year);
    g_date_add_days(date, 1);
    int loop_days = upcoming_days;
    while(loop_days >= 0)
    {
        int day = g_date_get_day(date);
        int month = g_date_get_month(date);
        int year = g_date_get_year(date);
        GArray* evt_arry_day = db_get_all_events_year_month_day(db_handle, year, month, day);
        if (evt_arry_day) { 
            for (guint i = 0; i < evt_arry_day->len; i++) {
                CalendarEvent* evt = g_array_index(evt_arry_day, CalendarEvent*, i); 
                g_array_append_val(evt_arry_upcoming, evt);
                // Note: Do NOT unref here because speak_events cleans this array up!
            } 
            g_array_free(evt_arry_day, TRUE);
        }
        g_date_add_days(date, 1);
        loop_days--;
    }
    g_date_free(date);
    if (evt_arry_upcoming != NULL && evt_arry_upcoming->len > 0) {
        return evt_arry_upcoming;
    } else {
        if (evt_arry_upcoming) g_array_free(evt_arry_upcoming, TRUE);
        return NULL;
    }
}

/**
 * @brief Returns a static, read-only string literal representation of a holiday.
 * @return A static literal string block pointer. DO NOT FREE THIS RESULT!
 */
 
 static const char* get_notable_date_text(int year, int month, int day)
{
    if (!m_notable_dates) {
        return NULL;
    }
        
    // Dynamic Easter-based queries
    GDate *easter = calculate_easter(year);
    if (easter && g_date_valid(easter)) {
        int ed = g_date_get_day(easter);
        int em = g_date_get_month(easter);
        g_date_free(easter);

        if (month == em && day == ed) return "Easter Sunday";

        GDate *gf = g_date_new_dmy(ed, em, year);
        g_date_subtract_days(gf, 2);
        gboolean is_gf = (month == g_date_get_month(gf) && day == g_date_get_day(gf));
        g_date_free(gf);
        if (is_gf) return "Easter Friday Bank Holiday";

        GDate *emonday = g_date_new_dmy(ed, em, year);
        g_date_add_days(emonday, 1);
        gboolean is_em = (month == g_date_get_month(emonday) && day == g_date_get_day(emonday));
        g_date_free(emonday);
        if (is_em) return "Easter Monday Bank Holiday";
    }

    // Dynamic Floating Sundays (Cleaned of apostrophes to match voice3.h)
    GDate *lent = calculate_easter(year);
    if (lent && g_date_valid(lent)) {
        g_date_subtract_days(lent, 21);
        gboolean is_md = (month == g_date_get_month(lent) && day == g_date_get_day(lent));
        g_date_free(lent);
        if (is_md) return "Mothers Sunday";
    }

    GDate *june = g_date_new_dmy(1, 6, year);
    if (june) {
        int fd = 1 + ((G_DATE_SUNDAY - g_date_get_weekday(june) + 7) % 7) + 14;
        g_date_free(june);
        if (month == 6 && day == fd) return "Fathers Day";
    }

    // Spring Bank Holiday (Last Monday in May) [INDEX 0.1.143]
    GDate *spring = g_date_new_dmy(31, 5, year);
    if (spring) {
        while (g_date_get_weekday(spring) != G_DATE_MONDAY) g_date_subtract_days(spring, 1);
        gboolean is_sbh = (month == 5 && day == g_date_get_day(spring));
        g_date_free(spring);
        if (is_sbh) return "Spring Bank Holiday";
    }

    // Late August Bank Holiday Calculation (Last Monday in August) 
    GDate *august_end = g_date_new_dmy(31, 8, year);
    if (august_end) {
        while (g_date_get_weekday(august_end) != G_DATE_MONDAY) g_date_subtract_days(august_end, 1);
        gboolean is_labh = (month == 8 && day == g_date_get_day(august_end));
        g_date_free(august_end);
        // Uses your existing recorded word tokens safely
        if (is_labh) return "August Bank Holiday"; 
    }

    switch (month) {
        case 1:  
            if (day == 1)  return "New Year Day"; 
            break;
            
        case 2:  
            if (day == 14) return "Valentine Day"; 
            break;
            
        case 8:  
            if (day == 31) return "August Bank Holiday"; 
            break;
            
        case 12: // December Cluster Block
            if (day == 25) return "Christmas Day"; 
            if (day == 26) return "Boxing Day"; 
            break; // Now the break cleanly guards BOTH options!
            
        default: 
            break;
    }    
    return NULL; 
}

//=====================================================================
static void append_notable_date_speech(GString *speak_gstr, int year, int month, int day)
{
    g_return_if_fail(speak_gstr != NULL);    
    //g_print("m_notable_dates = %d\n", m_notable_dates);
    
    if (!m_notable_dates) {
        return;
    }
    
    // Fetch the string literal token directly
    const char *holiday_text = get_notable_date_text(year, month, day);
    if (holiday_text) {
        // Convert the clean mixed-case display title to lowercase word tokens
        char *lower_token = g_ascii_strdown(holiday_text, -1);
        
        // Strip out punctuation symbols to ensure an exact match with voice3.h sound fragments
        g_strdelimit(lower_token, "'", ' '); 
        
        g_string_append_printf(speak_gstr, "%s ", lower_token);
        g_free(lower_token);
    }
}

//======================================================================
static void speak_events() 
{
    if (m_talk == 0) return;
    if (m_talking == TRUE) return;
    
    GString *speak_gstr = g_string_new("");
    
    gchar *dow_str = get_day_of_week(m_start_day, m_start_month, m_start_year);
    gchar *day_number_str = get_day_number_ordinal_string(m_start_day);
    gchar *month_str = get_month_string(m_start_month);
    
    // space separation without punctuation ensures audio keys match 
    g_string_append_printf(speak_gstr, "%s %s %s ", dow_str, day_number_str, month_str);
   
    append_notable_date_speech(speak_gstr, m_start_year, m_start_month, m_start_day);
        
    GArray* day_events_arry = db_get_all_events_year_month_day(db_handle, m_start_year, m_start_month, m_start_day); 
    if (day_events_arry) {
        int event_number = day_events_arry->len;
        if (m_talk_event_number) {
            if (event_number == 0)      g_string_append(speak_gstr, "you have no events ");
            else if (event_number == 1) g_string_append(speak_gstr, "you have one event ");
            else                        g_string_append_printf(speak_gstr, "you have %d events ", event_number);
        }
        
        for (int i = 0; i < day_events_arry->len; i++) {
            gchar *summary_str = NULL;
            gchar *description_str = NULL;
            gchar *location_str = NULL;
            gint start_hour = 0, start_min = 0, is_allday = 0, is_priority = 0;
            
            CalendarEvent *evt = g_array_index(day_events_arry, CalendarEvent *, i);
            g_object_get(evt,
                         "summary",     &summary_str,
                         "description", &description_str,
                         "location",    &location_str,
                         "starthour",   &start_hour,
                         "startmin",    &start_min,
                         "isallday",    &is_allday,
                         "ispriority",  &is_priority,
                         NULL);
                         
            if (!is_allday) {
                gchar* hour_str = NULL;
                const char* ampm_str = "";
                if (m_12hour_format) {
                    if (start_hour >= 13 && start_hour <= 23) {
                        int s_hour = start_hour - 12;
                        ampm_str = "pm ";
                        hour_str = get_cardinal_string(s_hour);
                    } else if (start_hour == 12) {
                        ampm_str = "pm ";
                        hour_str = get_cardinal_string(start_hour);
                    } else {
                        ampm_str = "am ";
                        hour_str = get_cardinal_string(start_hour);
                    }
                    g_string_append_printf(speak_gstr, "at %s ", hour_str);
                    
                    if (start_min > 0 && start_min < 10) {
                        gchar* min_str = get_cardinal_string(start_min);
                        g_string_append_printf(speak_gstr, "zero %s ", min_str);
                    } else if (start_min >= 10) {
                        gchar* min_str = get_cardinal_string(start_min);
                        g_string_append_printf(speak_gstr, "%s ", min_str);
                    }
                    g_string_append(speak_gstr, ampm_str);
                } else {
                    hour_str = get_cardinal_string(start_hour);
                    g_string_append_printf(speak_gstr, "at %s ", hour_str);
                    if (start_min > 0 && start_min < 10) {
                        gchar* min_str = get_cardinal_string(start_min);
                        g_string_append_printf(speak_gstr, "zero %s ", min_str);
                    } else if (start_min >= 10) {
                        gchar* min_str = get_cardinal_string(start_min);
                        g_string_append_printf(speak_gstr, "%s ", min_str);
                    }
                }
            } else {
                //g_string_append(speak_gstr, "all day ");
            }
            
            if (summary_str) {
                g_string_append_printf(speak_gstr, "%s ", summary_str);
            }
                       
            if (is_priority) {
                g_string_append(speak_gstr, "high priority event ");
            }
            
            if (i < day_events_arry->len - 1) {
                g_string_append(speak_gstr, "and ");
            } 
            
            g_free(summary_str);
            g_free(description_str);
            g_free(location_str);
        }
        g_array_free(day_events_arry, TRUE);
    }
    
    // Upcoming event tracking sequence
    GDate *today_date = g_date_new();
    g_date_set_time_t(today_date, time(NULL));
    int today = g_date_get_day(today_date);
    int month = g_date_get_month(today_date);
    int year = g_date_get_year(today_date);
    g_date_free(today_date); 
    
    if (m_talk_upcoming && m_start_day == today && m_start_month == month && m_start_year == year) {
        GArray* upcoming = get_upcoming_array(m_upcoming_days);
        if (upcoming) {
            if (upcoming->len == 1) g_string_append(speak_gstr, " you have upcoming event ");
            else                    g_string_append(speak_gstr, " you have upcoming events ");
            
            for (guint i = 0; i < upcoming->len; i++) {
                CalendarEvent* event = g_array_index(upcoming, CalendarEvent*, i);
                if (!event) continue; 
                gchar* u_summary_str = NULL;
                gint start_day = 0, start_month = 0, start_year = 0, is_priority = 0; 
                
                g_object_get(event, "summary", &u_summary_str, "startyear", &start_year, 
                             "startmonth", &start_month, "startday", &start_day, "ispriority", &is_priority, NULL); 
                             
                gchar *udow_str = get_day_of_week(start_day, start_month, start_year);
                gchar *uday_number_str = get_day_number_ordinal_string(start_day);
                gchar *umonth_str = get_month_string(start_month); 
                
                g_string_append_printf(speak_gstr, " %s %s %s %s ", udow_str, uday_number_str, umonth_str, u_summary_str ? u_summary_str : "");
                
                if (is_priority) {
                    g_string_append(speak_gstr, "high priority event ");
                }
                g_free(u_summary_str);
            } 
            for (guint i = 0; i < upcoming->len; i++) {
                CalendarEvent* event = g_array_index(upcoming, CalendarEvent*, i);
                if (event) g_object_unref(event); 
            }
            g_array_free(upcoming, TRUE);
        } 
    }
    
    if (speak_gstr->len > 0) {
        play_speak_str(speak_gstr->str);
    }
    g_string_free(speak_gstr, TRUE); 
}



static void callbk_speak(GSimpleAction* action, GVariant *parameter,gpointer user_data)
{	
	//g_print("callbk speak events\n");
	if(m_talking == FALSE) speak_events();		
}

//======================================================================
// Speak time
//======================================================================

static void callbk_speaktime(GSimpleAction * action, GVariant *parameter, gpointer user_data)
{
	//g_print("callbk speak time\n");
	
	GtkWidget *window = user_data;
	
	GDateTime *dt = g_date_time_new_now_local(); 
	gint hour =g_date_time_get_hour(dt);	
	gint min= g_date_time_get_minute(dt);	
	
	if(m_talking==FALSE) speak_time(hour,min);
    g_date_time_unref (dt);
	
}	

//======================================================================
static void speak_time(gint hour, gint min) 
{   
    if (m_talk == 0) return;
    if (m_talking == TRUE) return;  

    // Allocate a dynamic GString string builder context 
    GString *speak_gstr = g_string_new("the time is ");  
    const gchar* hour_str = "";
    const gchar* min_str = "";
    const gchar* ampm_str = "";

    if (m_12hour_format) {       
        if (hour >= 13 && hour <= 23)
        {
            int s_hour = hour - 12; 
            ampm_str = "pm ";             
            hour_str = get_cardinal_string(s_hour);
        }
        else if (hour == 12)
        {       
            ampm_str = "pm ";             
            hour_str = get_cardinal_string(hour);
        }
        else // hour < 12
        {       
            ampm_str = "am ";                 
            hour_str = get_cardinal_string(hour);
        }       
        
        g_string_append_printf(speak_gstr, "%s ", hour_str); 
        
        if (min == 0)
        {
            // Explicitly announce zero zero for top-of-the-hour accuracy
            g_string_append(speak_gstr, "zero zero ");
        }
        else if (min > 0 && min < 10)
        {   
            min_str = get_cardinal_string(min);   
            g_string_append_printf(speak_gstr, "zero %s ", min_str);
        }
        else if (min >= 10)
        {
            min_str = get_cardinal_string(min);   
            g_string_append_printf(speak_gstr, "%s ", min_str);
        }  
        g_string_append(speak_gstr, ampm_str);      
    } // 12hour format   
    else // 24hour format
    {               
        hour_str = get_cardinal_string(hour);   
        g_string_append_printf(speak_gstr, "%s ", hour_str);   
        
        if (min == 0)
        {
            g_string_append(speak_gstr, "zero zero ");
        }
        else if (min > 0 && min < 10)
        {   
            min_str = get_cardinal_string(min);   
            g_string_append_printf(speak_gstr, "zero %s ", min_str);
        }
        else if (min >= 10)
        {
            min_str = get_cardinal_string(min);   
            g_string_append_printf(speak_gstr, "%s ", min_str);
        }                               
    } // 24 hour format   

    // Pass the raw constructed string to speech engine 
    play_speak_str(speak_gstr->str);   

    // Release the GString metadata container and heap contents 
    g_string_free(speak_gstr, TRUE);
}

//======================================================================
//list view
//======================================================================

/**
 * @brief Synchronises data storage by filtering and loading events for the selected date.
 * 
 * This data pipeline function carries out the following steps:
 * 1. Empties the provided GListStore container to wipe clean any events from previous selection lookups.
 * 2. Queries the active selection coordinates (Day, Month, Year) from the CustomCalendar widget instance.
 * 3. Re-fetches a dynamic matching database array matching these coordinates using an external handler.
 * 4. Iterates over the event results array, mounting each entity into the managed GListStore.
 * 5. Safely unrefs local object counts to balance references and prevent memory leaks.
 * 6. Disposes of the temporary array wrapper layout container cleanly.
 *
 * @param calendar  The CustomCalendar widget instance holding active date constraints.
 * @param user_data A generic context pointer cast internally to the destination GListStore instance.
 * 
 * @return void
 */
static void update_store(CustomCalendar *calendar, gpointer user_data)
{	
    GListStore *store = user_data;
    g_list_store_remove_all(G_LIST_STORE(store));	
    
    int selected_day = custom_calendar_get_day(CUSTOM_CALENDAR(calendar));
    int selected_month = custom_calendar_get_month(CUSTOM_CALENDAR(calendar));
    int selected_year = custom_calendar_get_year(CUSTOM_CALENDAR(calendar));	

    // Pull targeted event records from your database back-end layer
    GArray* events_for_day = db_get_all_events_year_month_day(db_handle, selected_year, selected_month, selected_day);    
    if (events_for_day) {
        for (guint i = 0; i < events_for_day->len; i++) {
            CalendarEvent* event = g_array_index(events_for_day, CalendarEvent*, i);            
            
            // Appending to the store bumps the object reference count to 2
            g_list_store_append(G_LIST_STORE(store), event);    
            
            // Drop local creation reference down to 1 so the store fully manages its lifespan
            g_object_unref(event); 
        }
        // Free the pointer array container wrapper itself, but keep elements intact
        g_array_free(events_for_day, TRUE); 
    } else {
        g_print("No events found for the specified day or an error occurred.\n");
    }		
}

/**
 * @brief Callback for when a list item is activated.
 * @param list The GtkListView.
 * @param position The position of the activated item.
 * @param gpointer Unused pointer.
 */
static void callbk_listview (GtkListView *list, guint position, gpointer unused)
{
	 // leave empty
	//g_print("callbk_listview_acitvated\n");	
}

/**
 * @brief Callback to set up a new list item widget.
 * @param factory The GtkListItemFactory.
 * @param list_item The GtkListItem to set up.
 */
static void callbk_setup_listitem (GtkListItemFactory *factory, GtkListItem *list_item)
{ 
  GtkWidget *label = gtk_label_new ("");
  gtk_list_item_set_child (list_item, label);
}

/**
 * @brief Callback to bind data to a list item widget.
 * @param factory The GtkListItemFactory.
 * @param list_item The GtkListItem to bind data to.
 */
static void callbk_bind_listitem (GtkListItemFactory *factory, GtkListItem *list_item)
{
    GtkWidget *label;
    label = gtk_list_item_get_child (list_item);
    gtk_widget_set_halign (GTK_WIDGET (label), GTK_ALIGN_START);
    gtk_label_set_use_markup (GTK_LABEL (label), TRUE);

    CalendarEvent *event;
    event = gtk_list_item_get_item (list_item);
    
    // Fetch core pointers from object safely (these return internally cached literals)
    const char *summary     = calendar_event_get_summary (CALENDAR_EVENT (event));
    const char *description = calendar_event_get_description (CALENDAR_EVENT (event));
    const char *location    = calendar_event_get_location (CALENDAR_EVENT (event));
    int start_hour  = calendar_event_get_start_hour (CALENDAR_EVENT (event));
    int start_min   = calendar_event_get_start_min (CALENDAR_EVENT (event));
    int end_hour    = calendar_event_get_end_hour (CALENDAR_EVENT (event));
    int end_min     = calendar_event_get_end_min (CALENDAR_EVENT (event));
    int is_allday   = calendar_event_get_is_allday (CALENDAR_EVENT (event));
    int is_priority = calendar_event_get_is_priority (CALENDAR_EVENT (event));
    
    // Allocate safe GString builders instead of using g_strconcat
    GString *display_gstr = g_string_new("");
    GString *des_loc_gstr = g_string_new("");
    
    // Build the secondary details block cleanly
    gboolean has_desc = (description && strlen(description) > 0);
    gboolean has_loc  = (location && strlen(location) > 0);
    if (has_desc && has_loc) {
        g_string_append_printf(des_loc_gstr, "%s. %s.", description, location);
    } else if (has_desc) {
        g_string_append_printf(des_loc_gstr, "%s.", description);
    } else if (has_loc) {
        g_string_append_printf(des_loc_gstr, "%s.", location);
    }
    
    // Fix: If this specific row item is marked high priority, wrap the header block 
    // inside a deep crimson markup tag immediately to give it distinct prominence!
    if (is_priority) {
        g_string_append(display_gstr, "<span foreground='#cc0000'><b>[PRIORITY]</b> </span>");
    }
    
    // Process time calculations and primary display configurations
    if (!is_allday)
    {
        char *time_str_start = get_time_str(start_hour, start_min);
        char *time_str_end   = get_time_str(end_hour, end_min);
        
        if (is_priority) {
            // High priority text formatting
            if (m_use_end_time) {
                g_string_append_printf(display_gstr, "<span foreground='#cc0000'>%s to %s %s</span>\n", 
                                       time_str_start, time_str_end, summary ? summary : "");
            } else {
                g_string_append_printf(display_gstr, "<span foreground='#cc0000'>%s %s</span>\n", 
                                       time_str_start, summary ? summary : "");
            }
        } else {
            // Standard normal text formatting
            if (m_use_end_time) {
                g_string_append_printf(display_gstr, "%s to %s %s\n", time_str_start, time_str_end, summary ? summary : "");
            } else {
                g_string_append_printf(display_gstr, "%s %s\n", time_str_start, summary ? summary : "");
            }
        }
        
        g_free(time_str_start);
        g_free(time_str_end);
    }
    else // All-Day formatting rules
    {
        if (is_priority) {
            g_string_append_printf(display_gstr, "<span foreground='#cc0000'>%s</span>\n", summary ? summary : "");
        } else {
            g_string_append_printf(display_gstr, "%s\n", summary ? summary : "");
        }
    }
    
    // Append metadata properties details cleanly
    if (des_loc_gstr->len > 0) {
        if (is_priority) {
            // Keep the sub-description text slightly distinct but color-matched
            g_string_append_printf(display_gstr, "<span foreground='#aa3333'><i>%s</i></span>", des_loc_gstr->str);
        } else {
            g_string_append(display_gstr, des_loc_gstr->str);
        }
    }
    
    // Push the compiled markup values safely straight to the recycled UI label
    gtk_label_set_markup (GTK_LABEL (label), display_gstr->str);
    
    // Free the metadata structures to clean up allocations completely
    g_string_free(display_gstr, TRUE);
    g_string_free(des_loc_gstr, TRUE);
}


//======================================================================
//Timer functions for time reminder alert
//======================================================================

/**
 * @brief set values and close dialog window
 * @param button The GtkButton that triggered the callback. 
 * @param user_data 
 */
static void callbk_set_alarm_time(GtkButton *button, gpointer user_data)
{
    GtkWidget *dialog = g_object_get_data(G_OBJECT(button), "dialog-key");
    GtkWidget *check_button = g_object_get_data(G_OBJECT(button), "check-alarm-on-key");
    
    // Read the active visual toggle switch state right before saving
    if (check_button && GTK_IS_CHECK_BUTTON(check_button)) {
        m_alarm_on = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button));
    }
    
    // Flush updated values (hour, minute, alarm_on status) to the talkcalendar configuration file
    config_write();
    //g_print("Alarm settings written to config: %02d:%02d (Active: %s)\n", 
            //m_alarm_hour, m_alarm_min, m_alarm_on ? "TRUE" : "FALSE");
    
    if (dialog && GTK_IS_WINDOW(dialog)) {
        gtk_window_destroy(GTK_WINDOW(dialog));
    }
}

/**
 * @brief set the m_alarm_hour value
 * @param GtkSpinButton button that triggered the callback. 
 * @param user_data 
 */
static void callbk_spin_alarm_hour(GtkSpinButton *button, gpointer user_data)
{
    m_alarm_hour = gtk_spin_button_get_value_as_int(button);
    //g_print("alarm_hour = %d\n", m_alarm_hour);
}
/**
 * @brief set the m_alarm_min value
 * @param GtkSpinButton button that triggered the callback. 
 * @param user_data 
 */
static void callbk_spin_alarm_min(GtkSpinButton *button, gpointer user_data)
{
    m_alarm_min = gtk_spin_button_get_value_as_int(button);
    //g_print("alarm_min = %d\n", m_alarm_min);
}
/**
 * @brief callbk function to set the alarm time values
 * @param  GSimpleAction* action
 * @param  GVariant *parameter
 * @param user_data is window
 */
static void callbk_alarm_times(GSimpleAction* action, GVariant *parameter, gpointer user_data)
{
       
    GtkWidget *window = GTK_WIDGET(user_data); 
    GtkWidget *dialog_alarm;
    GtkWidget *box;
    GtkWidget *button_set_alarm;
    GtkWidget *label_alarm_hour;
    GtkWidget *label_alarm_min;
    GtkWidget *spin_button_alarm_hour;
    GtkWidget *spin_button_alarm_min;
    GtkWidget *check_button_alarm_on; // New toggle widget variable
    
    GtkAdjustment *adjustment_alarm_hour = gtk_adjustment_new((double)m_alarm_hour, 0.0, 23.0, 1.0, 1.0, 0.0);
    GtkAdjustment *adjustment_alarm_min  = gtk_adjustment_new((double)m_alarm_min,  0.0, 59.0, 1.0, 1.0, 0.0);
    
    dialog_alarm = gtk_window_new(); 
    gtk_window_set_title(GTK_WINDOW(dialog_alarm), "Set Alarm Time");
    gtk_window_set_default_size(GTK_WINDOW(dialog_alarm), 300, 180); // Adjusted height to accommodate toggle
    
    if (window && GTK_IS_WINDOW(window)) {
        gtk_window_set_transient_for(GTK_WINDOW(dialog_alarm), GTK_WINDOW(window));
        gtk_window_set_modal(GTK_WINDOW(dialog_alarm), TRUE);
    }
    
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_widget_set_margin_start(box, 12);
    gtk_widget_set_margin_end(box, 12);
    gtk_widget_set_margin_top(box, 12);
    gtk_widget_set_margin_bottom(box, 12);
    gtk_window_set_child(GTK_WINDOW(dialog_alarm), box);
    
    // Hour input configuration
    label_alarm_hour = gtk_label_new("Set Hour (24h format):");
    gtk_widget_set_halign(label_alarm_hour, GTK_ALIGN_START);
    spin_button_alarm_hour = gtk_spin_button_new(adjustment_alarm_hour, 1.0, 0);
    g_signal_connect(GTK_SPIN_BUTTON(spin_button_alarm_hour), "value-changed", G_CALLBACK(callbk_spin_alarm_hour), NULL);
    
    // Minute input configuration
    label_alarm_min = gtk_label_new("Set Minute:");
    gtk_widget_set_halign(label_alarm_min, GTK_ALIGN_START);
    spin_button_alarm_min = gtk_spin_button_new(adjustment_alarm_min, 1.0, 0);
    g_signal_connect(GTK_SPIN_BUTTON(spin_button_alarm_min), "value-changed", G_CALLBACK(callbk_spin_alarm_min), NULL);
    
    // Instantiate and pre-populate the GtkCheckButton toggle switch state
    check_button_alarm_on = gtk_check_button_new_with_label("Enable Alarm");
    gtk_check_button_set_active(GTK_CHECK_BUTTON(check_button_alarm_on), m_alarm_on);
    gtk_widget_set_margin_top(check_button_alarm_on, 6);
    gtk_widget_set_margin_bottom(check_button_alarm_on, 6);
    
    button_set_alarm = gtk_button_new_with_label("Save Alarm Settings");
    g_signal_connect(button_set_alarm, "clicked", G_CALLBACK(callbk_set_alarm_time), NULL);
    
    // Bind the dialog window and the switch component handles securely to the save button
    g_object_set_data(G_OBJECT(button_set_alarm), "dialog-key", dialog_alarm); 
    g_object_set_data(G_OBJECT(button_set_alarm), "check-alarm-on-key", check_button_alarm_on); 
    
    // Pack components sequentially into the vertical dialog layout
    gtk_box_append(GTK_BOX(box), label_alarm_hour);
    gtk_box_append(GTK_BOX(box), spin_button_alarm_hour);
    gtk_box_append(GTK_BOX(box), label_alarm_min);
    gtk_box_append(GTK_BOX(box), spin_button_alarm_min);
    gtk_box_append(GTK_BOX(box), check_button_alarm_on); // Added toggle switch element
    gtk_box_append(GTK_BOX(box), button_set_alarm);
    
    gtk_window_present(GTK_WINDOW(dialog_alarm)); 
}

/**
 * @brief update the time label
 * @param gpointer data to the GtkLabel
 */
static gboolean update_time_label(gpointer data)
{
    GtkLabel *label = (GtkLabel*)data;
    if (!label || !GTK_IS_LABEL(label)) {
        return FALSE; // Halt the timer loops safely if the label widget is gone
    }    
    GDateTime *now = g_date_time_new_now_local();
    int current_hour = g_date_time_get_hour(now);
    int current_min  = g_date_time_get_minute(now);
    int current_sec  = g_date_time_get_second(now);    
    char *time_str = NULL;
    if (m_12hour_format) {
        time_str = g_date_time_format(now, "%I:%M %p");
    } else {
        time_str = g_date_time_format(now, "%H:%M");    
    }    
    if (time_str) {
        gtk_label_set_text(GTK_LABEL(label), time_str);     
        g_free(time_str); // Free the formatted string layout block instantly!
    }    
    // Check alarm matching rules strictly on the 0th second boundary pass
    if (current_hour == m_alarm_hour && current_min == m_alarm_min && current_sec == 0 && m_alarm_on)
    {            
        // Use play_speak_str to announce your new "time reminder" word         
        g_print("time reminder fired\n");
        play_speak_str("time reminder alert time reminder alert");
    }    
    g_date_time_unref(now);    
    // Explicitly return TRUE to instruct GLib to continue the second counter  
    return TRUE; 
}


static void callbk_pane_position_changed(GObject *gobject, GParamSpec *pspec, gpointer user_data)
{
    // Record the live pixel position layout directly as the user drags it
    m_pane_position = gtk_paned_get_position(GTK_PANED(gobject));
}


static gboolean callbk_window_close_request(GtkWindow *window, gpointer user_data)
{
    // If the user already confirmed they want to exit, bypass the check and allow immediate closure
    if (app_is_exiting) {
        return FALSE; 
    }

    // If the alarm tracker is off, allow immediate closure pass
    if (!m_alarm_on) {
        return FALSE; 
    }

    // Alarm Tracker is Active! Launch the alert dialog
    g_print("Window close intercepted: Active Alarm Tracker Warning Box Spawned.\n");

    GtkAlertDialog *alert = gtk_alert_dialog_new("%s", "Warning: Alarm Tracker is Active!");
    gtk_alert_dialog_set_detail(alert, "Closing Talk Calendar will disable your active background reminders. Do you still wish to exit?");
    
    const char *buttons[] = { "Keep Calendar Open", "Exit Anyway", NULL };
    gtk_alert_dialog_set_buttons(alert, buttons);
    gtk_alert_dialog_set_cancel_button(alert, 0);

    gtk_alert_dialog_choose(alert, window, NULL, handle_final_dialog_response, window);
    g_object_set_data(G_OBJECT(window), "active-alert-dialog-instance", alert);

    return TRUE; 
}

static void handle_final_dialog_response(GObject *source_object, GAsyncResult *res, gpointer user_data)
{
    GtkAlertDialog *alert = GTK_ALERT_DIALOG(source_object);
    GtkWindow *window = GTK_WINDOW(user_data);
    
    int response = gtk_alert_dialog_choose_finish(alert, res, NULL);
    
    if (response == 1) {          
        app_is_exiting = TRUE;        
        g_print("User confirmed choice override. Preserving active alarm settings configuration.\n");
        gtk_window_destroy(window); 
    } else {
        g_print("User aborted close request sequence. Resuming normal operations.\n");
    }
}


/**
 * @brief Callback function to shutdown Talk Calendar.
 * @param GtkWindow  the window that triggered the call back
 * @param user_data A pointer to the GtkWidow.
 */
static void callbk_shutdown(GtkWindow *window, gpointer user_data)
{
    g_return_if_fail(GTK_IS_WINDOW(window));
    
    // Look up the paned layout container object using the window key map dictionary
    GtkWidget *paned = g_object_get_data(G_OBJECT(window), "window-paned-key");
    if (paned && GTK_IS_PANED(paned)) {
        m_pane_position = gtk_paned_get_position(GTK_PANED(paned));
    }

    gtk_window_get_default_size(window, &m_window_width, &m_window_height);    
    config_write();  
    //g_print("Configuration metrics and pane state successfully flushed to disk.\n");
}

/**
 * @brief Callback function to quit Talk Calendar.
 * @param action The GSimpleAction that triggered the callback.
 * @param parameter The GVariant parameter (unused).
 * @param user_data A pointer to the GtkWidow.
 */
static void callbk_quit(GSimpleAction *action, GVariant *parameter, gpointer user_data) 
{ 
    GtkWindow *window = GTK_WINDOW(user_data);  
    
    if (window && GTK_IS_WINDOW(window)) {      
        gtk_window_close(window); 
    }
}

/**
 * @brief Helper to create menu
 * @param app The GtkApplication
 */
static GMenu *create_menu(const GtkApplication *app) 
{		
	GMenu *menu;
    GMenu *file_menu;   
    GMenu *event_menu;
    GMenu *calendar_menu;
    GMenu *help_menu;
    GMenuItem *item;

	menu =g_menu_new();
	file_menu =g_menu_new();	
	event_menu =g_menu_new();
	calendar_menu =g_menu_new();
	help_menu =g_menu_new();
	
	//File items	
	item =g_menu_item_new("Export", "app.export");
	g_menu_append_item(file_menu,item);
	g_object_unref(item);
	
	item =g_menu_item_new("Import", "app.import");
	g_menu_append_item(file_menu,item);
	g_object_unref(item);
	
	item = g_menu_item_new("Quit", "app.quit");
    g_menu_append_item(file_menu, item);
    g_object_unref(item);
		
	//Event items
	item =g_menu_item_new("New Event", "app.newevent");
	g_menu_append_item(event_menu,item);
	g_object_unref(item);
	
	item =g_menu_item_new("Edit Selected Event", "app.editevent");
	g_menu_append_item(event_menu,item);
	g_object_unref(item);
	
	item =g_menu_item_new("Delete Selected Event", "app.deleteevent");
	g_menu_append_item(event_menu,item);
	g_object_unref(item);
	
	item =g_menu_item_new("Delete All Events", "app.deleteall");
	g_menu_append_item(event_menu,item);
	g_object_unref(item);
	
	item =g_menu_item_new("Speak", "app.speak");
	g_menu_append_item(event_menu,item);
	g_object_unref(item);
	
	item =g_menu_item_new("Search", "app.search");
	g_menu_append_item(event_menu,item);
	g_object_unref(item);
	
	//Calendar items
	item =g_menu_item_new("Go To Today", "app.home");
	g_menu_append_item(calendar_menu,item);
	g_object_unref(item);
	
	item =g_menu_item_new("Speak Time", "app.speaktime");
	g_menu_append_item(calendar_menu,item);
	g_object_unref(item);
		
	item =g_menu_item_new("Calculate Easter", "app.easter");
	g_menu_append_item(calendar_menu,item);
	g_object_unref(item);
	
	item =g_menu_item_new("Set Alarm", "app.setalarm");
	g_menu_append_item(calendar_menu,item);
	g_object_unref(item);
	
	item =g_menu_item_new("Preferences", "app.preferences");
	g_menu_append_item(calendar_menu,item);
	g_object_unref(item);	
		
	//Help items
	item =g_menu_item_new("Information", "app.info");
	g_menu_append_item(help_menu,item);
	g_object_unref(item);
	
	item =g_menu_item_new("About", "app.about");
	g_menu_append_item(help_menu,item);
	g_object_unref(item);
	
	g_menu_append_submenu(menu, "File", G_MENU_MODEL(file_menu));
    g_object_unref(file_menu);   
    g_menu_append_submenu(menu, "Event", G_MENU_MODEL(event_menu));
    g_object_unref(event_menu);
    g_menu_append_submenu(menu, "Calendar", G_MENU_MODEL(calendar_menu));
    g_object_unref(calendar_menu);
    g_menu_append_submenu(menu, "Help", G_MENU_MODEL(help_menu));
    g_object_unref(help_menu);
    
    return menu;
}

/**
 * @brief Active the application
 * @param app The GtkApplication
 */
static void activate (GtkApplication *app, gpointer  user_data)
{
	GtkWidget *window;	
	GMenu *menu;	
	GtkWidget *calendar;
	GtkWidget *label_time; //display time	
	GtkWidget *scrolled_window;	
	GtkWidget *paned;	
	GtkWidget *box;	
	GtkWidget *box_listview;
	GtkWidget *box_calendar;		
	GtkListItemFactory *factory;
	GListModel *model;
	GtkSingleSelection *selection;
	GtkWidget *list_view;	
	const gchar *home_accels[2] = { "Home", NULL };	
	const gchar *speak_accels[2] = { "space", NULL };	
	const gchar *speaktime_accels[2] = {"t", NULL };
	const gchar *newevent_accels[2] = {"<Ctrl>n", NULL };	
	const gchar *editevent_accels[2] = {"<Ctrl>e", NULL };		
	const gchar *delete_accels[2] = {"Delete", NULL };
	const gchar *info_accels[2] = {"F1", NULL };	
	const gchar * preferences_accels[2] = { "<Ctrl><Alt>P", NULL };
	const gchar * quit_accels[2] = { "<Ctrl>Q", NULL };		
	
    window = gtk_application_window_new(app);
    gtk_window_set_title (GTK_WINDOW(window), "Talk Calendar");		
    gtk_window_set_default_size (GTK_WINDOW(window), m_window_width, m_window_height);	
    
    // Connect the balanced exit pipelines securely
    g_signal_connect(window, "close-request", G_CALLBACK(callbk_window_close_request), NULL);
    g_signal_connect(window, "destroy",       G_CALLBACK(callbk_shutdown),             NULL);	
    
    GSimpleAction *quit_action = g_simple_action_new("quit", NULL);
    g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(quit_action));
    g_signal_connect(quit_action, "activate", G_CALLBACK(callbk_quit), window); 
	
	label_time=gtk_label_new("");	   
    gtk_label_set_xalign(GTK_LABEL(label_time),0.5);
	g_timeout_add_seconds(1, update_time_label, label_time);
			
	GListStore *store=NULL;
	store = g_list_store_new(G_TYPE_OBJECT);
	selection = gtk_single_selection_new(G_LIST_MODEL(store));
	gtk_single_selection_set_autoselect(selection,FALSE);	
	factory = gtk_signal_list_item_factory_new ();
    g_signal_connect (factory, "setup", G_CALLBACK (callbk_setup_listitem), NULL);
    g_signal_connect (factory, "bind", G_CALLBACK (callbk_bind_listitem), NULL);
	list_view = gtk_list_view_new(GTK_SELECTION_MODEL (selection),factory);
	g_signal_connect (list_view, "activate", G_CALLBACK (callbk_listview), NULL);	
	gtk_list_view_set_show_separators (GTK_LIST_VIEW(list_view),TRUE);		
	//setup custom calendar
	calendar = custom_calendar_new();		
	m_start_day = custom_calendar_get_day(CUSTOM_CALENDAR(calendar));
	m_start_month = custom_calendar_get_month(CUSTOM_CALENDAR(calendar));
	m_start_year = custom_calendar_get_year(CUSTOM_CALENDAR(calendar));	
	g_signal_connect(CUSTOM_CALENDAR(calendar), "day-selected", G_CALLBACK(callbk_calendar_day_selected), store);	
	g_signal_connect(CUSTOM_CALENDAR(calendar), "next-month", G_CALLBACK(callbk_calendar_next_month), window);
	g_signal_connect(CUSTOM_CALENDAR(calendar), "prev-month", G_CALLBACK(callbk_calendar_prev_month), window);
	g_signal_connect(CUSTOM_CALENDAR(calendar), "next-year", G_CALLBACK(callbk_calendar_next_year), window);
	g_signal_connect(CUSTOM_CALENDAR(calendar), "prev-year", G_CALLBACK(callbk_calendar_prev_year), window);		
	
	// heap duplicates:
    g_free(m_todaycolour);
    m_todaycolour = g_strdup("rgb(141,166,141)");     
    g_free(m_eventcolour);
    m_eventcolour = g_strdup("rgb(217,230,217)"); 	
	g_free(m_notablecolour);
    m_notablecolour = g_strdup("rgb(245,245,220)"); // beige
	
	g_object_set(calendar, "todaycolour", m_todaycolour, NULL);
	g_object_set(calendar, "eventcolour", m_eventcolour, NULL);
	g_object_set(calendar, "notablecolour", m_notablecolour, NULL);
	g_object_set(calendar, "showtooltips", m_show_tooltips, NULL);
	
	set_notables_on_calendar(CUSTOM_CALENDAR(calendar));		
	
	scrolled_window = gtk_scrolled_window_new();	
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window),list_view);	   
    gtk_widget_set_hexpand (GTK_WIDGET (list_view), TRUE);
    gtk_widget_set_vexpand (GTK_WIDGET (list_view), TRUE);
    gtk_widget_set_halign(list_view, GTK_ALIGN_FILL); 
	//gtk_widget_set_valign(list_view, GTK_ALIGN_FILL);	
	//listview box
	box_listview =gtk_box_new(GTK_ORIENTATION_VERTICAL,1);	
	gtk_box_append(GTK_BOX(box_listview), scrolled_window);
    
    //calendar box    
    box_calendar =gtk_box_new(GTK_ORIENTATION_VERTICAL,1);  
    gtk_box_append(GTK_BOX(box_calendar), label_time);  //add timer label
    gtk_box_append(GTK_BOX(box_calendar), calendar); 
	gtk_widget_set_vexpand (calendar, TRUE);
    gtk_widget_set_hexpand (calendar, TRUE);
    gtk_widget_set_halign(calendar, GTK_ALIGN_FILL); // ensure it fills horizontally  
      
	g_object_set_data(G_OBJECT(calendar), "calendar-window-key",window);
	g_object_set_data(G_OBJECT(calendar), "calendar-store-key",store);	
	g_object_set_data(G_OBJECT(window), "window-store-key",store);
	g_object_set_data(G_OBJECT(window), "window-calendar-key",calendar);	
	g_object_set_data(G_OBJECT(store), "store-window-key",window);
	g_object_set_data(G_OBJECT(store), "store-calendar-key",calendar);	
	g_object_set_data(G_OBJECT(selection), "selection-window-key",window);
	g_object_set_data(G_OBJECT(selection), "selection-calendar-key",calendar);	
	//Actions	
	//File actions
	GSimpleAction *export_action;
	export_action=g_simple_action_new("export",NULL); //app.export
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(export_action));
	g_signal_connect(export_action, "activate",  G_CALLBACK(callbk_export), window);	
	
	GSimpleAction *import_action;
	import_action=g_simple_action_new("import",NULL); //app.import
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(import_action)); 
	g_signal_connect(import_action, "activate",  G_CALLBACK(callbk_import), window);	
	
	//New event
	GSimpleAction *newevent_action;	
	newevent_action=g_simple_action_new("newevent",NULL); //app.newevent
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(newevent_action));	
	g_signal_connect(newevent_action, "activate",  G_CALLBACK(callbk_new_event), store);
	
	//Edit Event
	GSimpleAction *editevent_action;	
	editevent_action=g_simple_action_new("editevent",NULL); //app.editevent
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(editevent_action)); 	
	g_signal_connect(editevent_action, "activate",  G_CALLBACK(callbk_edit_event), selection);
	//Delete Event
	GSimpleAction *deleteevent_action;	
	deleteevent_action=g_simple_action_new("deleteevent",NULL); //app.deleteevent
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(deleteevent_action)); //make visible	
	g_signal_connect(deleteevent_action, "activate",  G_CALLBACK(callbk_delete_event), selection);	
	//Delete all
	GSimpleAction *deleteall_action;
	deleteall_action=g_simple_action_new("deleteall",NULL); //app.deleteall
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(deleteall_action)); //make visible
	g_signal_connect(deleteall_action, "activate",  G_CALLBACK(callbk_delete_all), window);		
	//Calendar home
	GSimpleAction *home_action;	
	home_action=g_simple_action_new("home",NULL); //app.home
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(home_action)); //make visible	
	g_signal_connect(home_action, "activate",  G_CALLBACK(callbk_calendar_home), window);	
	//Calendar search	
	GSimpleAction *search_action;
	search_action=g_simple_action_new("search",NULL); //app.search
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(search_action)); //make visible
	g_signal_connect(search_action, "activate",  G_CALLBACK(callbk_search), window);	
	//Calendar easter
	GSimpleAction *easter_action;
	easter_action=g_simple_action_new("easter",NULL); //app.easter
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(easter_action)); //make visible
	g_signal_connect(easter_action, "activate",  G_CALLBACK(callbk_easter), window);		
	//Calendar time alarm connection signature
	GSimpleAction *setalarm_action;	
	setalarm_action=g_simple_action_new("setalarm",NULL); //app.setalarm
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(setalarm_action)); //make visible	
	g_signal_connect(setalarm_action, "activate",  G_CALLBACK(callbk_alarm_times), window);
		
	//Preferences	
	GSimpleAction *preferences_action;
	preferences_action=g_simple_action_new("preferences",NULL); //app.preferences
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(preferences_action)); //make visible
	g_signal_connect(preferences_action, "activate",  G_CALLBACK(callbk_preferences), window);
	
	GSimpleAction *info_action;
	info_action=g_simple_action_new("info",NULL); //app.info
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(info_action)); //make visible
	g_signal_connect(info_action, "activate",  G_CALLBACK(callbk_info), window);
	
	GSimpleAction *about_action;
	about_action=g_simple_action_new("about",NULL); //app.about
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(about_action)); //make visible
	g_signal_connect(about_action, "activate",  G_CALLBACK(callbk_about), window);
	GSimpleAction *speak_action;	
	speak_action=g_simple_action_new("speak",NULL); //app.speak
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(speak_action)); //make visible	
	g_signal_connect(speak_action, "activate",  G_CALLBACK(callbk_speak), window);
	
	GSimpleAction *speaktime_action;	
	speaktime_action=g_simple_action_new("speaktime",NULL); //app.speaktime
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(speaktime_action)); //make visible	
	g_signal_connect(speaktime_action, "activate",  G_CALLBACK(callbk_speaktime), window);
	
	set_tooltips_on_calendar(CUSTOM_CALENDAR(calendar));		
	custom_calendar_update (CUSTOM_CALENDAR(calendar));
	update_store(CUSTOM_CALENDAR(calendar), store);	
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.home", home_accels);
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.speak", speak_accels);	
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.newevent", newevent_accels);
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.editevent", editevent_accels);
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.deleteevent", delete_accels);
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.info", info_accels);
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.preferences", preferences_accels);
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.speaktime",speaktime_accels);	
	menu=create_menu(app);	
	gtk_application_set_menubar (app,G_MENU_MODEL(menu));
    gtk_application_window_set_show_menubar(GTK_APPLICATION_WINDOW(window), TRUE);	
	if(m_talk && m_talk_at_startup) {
		speak_events();		
	}	
	
	g_object_set_data(G_OBJECT(window), "window-paned-key", paned);	
	
	paned = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    gtk_paned_set_start_child(GTK_PANED(paned), box_calendar);
    gtk_paned_set_end_child(GTK_PANED(paned), box_listview);    
    // Load your saved configuration parameter position
    gtk_paned_set_position(GTK_PANED(paned), m_pane_position);    
    // Listen to live position modifications automatically!
    g_signal_connect(paned, "notify::position", G_CALLBACK(callbk_pane_position_changed), NULL);
    
    gtk_window_set_child(GTK_WINDOW(window), paned);
	
    
	
	GtkSettings *settings = gtk_widget_get_settings(GTK_WIDGET(window));
    g_object_set(settings, "gtk-application-prefer-dark-theme", m_is_dark_theme, NULL);
	gtk_window_present(GTK_WINDOW (window));	
}

/**
 * @brief The main function, which initializes the application and runs it.
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line argument strings.
 * @return The application's exit code.
 */ 
int main (int argc, char **argv)
{
    int status;
    config_initialize();    
    db_handle = db_open("talkcalendar.db");    
    if (!db_handle) {
        g_critical("Failed to open database.");
        return 1;
    }        
    GtkApplication *app = gtk_application_new ("org.gtk.talkcalendar", G_APPLICATION_DEFAULT_FLAGS);    
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);   
    db_close(db_handle); 
    //Clean up global strings safely here, after the GUI window layout is completely gone
    g_clear_pointer(&m_todaycolour, g_free); 
    g_clear_pointer(&m_eventcolour, g_free); 
    g_clear_pointer(&m_notablecolour, g_free);
    g_clear_pointer(&m_config_file, g_free);
    return status;
}

