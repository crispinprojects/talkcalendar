/* main.c
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
#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gstdio.h>  //needed for g_mkdir
#include <stdio.h>
#include <ctype.h>

#include "calendarevent.h"
#include "dbmanager.h"
//speaking
#include "diphone.h"
#include "dictionary.h"
#include "synthesizer.h"

// Global database handle
static sqlite3 *db_handle = NULL;

// Global dictionary
static Dictionary* g_global_dictionary = NULL;


// File and directory names for configuration
#define CONFIG_DIRNAME "talkcalendar"
#define CONFIG_FILENAME "talkcalendar-071"

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


// Function prototypes for export/import functionality
static void callbk_export(GSimpleAction *action, GVariant *parameter, gpointer user_data);
static void file_save_response (GObject *source, GAsyncResult *result, void *user_data);
void export_file(char *file_name);
static void callbk_import(GSimpleAction *action, GVariant *parameter, gpointer user_data);
void import_ical_file(gpointer user_data);
static void file_open_response (GObject *source, GAsyncResult *result, void *user_data);

//calendar callbks

static void callbk_calendar_day_selected(GtkCalendar *calendar, gpointer user_data);
static void callbk_calendar_next_month(GtkCalendar *calendar, gpointer user_data);
static void callbk_calendar_prev_month(GtkCalendar *calendar, gpointer user_data);
static void callbk_calendar_next_year(GtkCalendar *calendar, gpointer user_data);
static void callbk_calendar_prev_year(GtkCalendar *calendar, gpointer user_data);

static void update_calendar(GtkCalendar *calendar, gpointer user_data);
static void update_date_label(GtkCalendar *calendar, gpointer user_data);

static void set_marks_on_calendar(GtkCalendar *calendar);
static void callbk_calendar_home(GSimpleAction * action, GVariant *parameter, gpointer user_data);

int  get_total_number_of_events(void); 
int get_number_of_day_events(void);


// Function prototypes for search functionality
static void callbk_search(GSimpleAction *action, GVariant *parameter, gpointer user_data);
static void callbk_search_events(GtkButton *button, gpointer user_data);
static void search_events_location(const char* search_str);
static void search_events_summary(const char* search_str);

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

static char* get_cardinal_string(int number);
char* get_time_str_talk(int hour, int min);

static char *ignore_first_zero(char *input);
static gchar* sanitize_text(const gchar* input);

static void task_callbk(GObject *gobject,GAsyncResult *res,  gpointer  user_data);

static void play_audio_async (GTask *task, gpointer object, gpointer task_data, GCancellable *cancellable);

static void update_store(GtkCalendar *calendar, gpointer user_data);
static void callbk_listview (GtkListView *list, guint position, gpointer unused);
static void callbk_setup_listitem (GtkListItemFactory *factory,GtkListItem *list_item);
static void callbk_bind_listitem (GtkListItemFactory *factory, GtkListItem *list_item);

static GMenu *create_menu(const GtkApplication *app); 

char* get_time_str(int hour, int min);

//======================================================================
// Global preference variables
//======================================================================
static gboolean m_reset_preferences=FALSE;
// Talk preferences
static gboolean m_talk =TRUE;
static gboolean m_talk_at_startup =TRUE;
static gboolean m_talk_time =TRUE;

//listview preferences
static gboolean m_12hour_format=TRUE; //am pm hour format
static gboolean m_use_end_time=FALSE;
//window size preferences
static int m_window_width=800;
static int m_window_height=600;
//calendar preferences

static gboolean m_talk_location=FALSE; 

//static gboolean m_talk_description=0; //TODO
static int m_talk_priority=0;

static int m_start_year=0;
static int m_start_month=0;
static int m_start_day=0;

gboolean m_talking=FALSE; //gtask

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


//======================================================================
// Save load config file
//======================================================================

/**
 * @brief Loads the default configuration values into global variables.
 */
static void config_load_default()
{
	//talking
	m_talk=TRUE;
	m_talk_at_startup=FALSE;
	m_talk_location=FALSE;
		
	//time format
	m_12hour_format=TRUE;
	m_use_end_time=FALSE;
		
	m_window_width=800;
	m_window_height=600;
}

/**
 * @brief Reads configuration values from the global config file into global variables.
 */
static void config_read()
{
	// Load keys from keyfile
	 GKeyFile *kf = g_key_file_new();
    if (!g_key_file_load_from_file(kf, m_config_file, G_KEY_FILE_NONE, NULL)) {
        g_key_file_free(kf);
        return;
    }
		
	//talk preferences
	m_talk = g_key_file_get_boolean(kf, "calendar_settings", "talk", NULL);
	m_talk_at_startup=g_key_file_get_boolean(kf, "calendar_settings", "talk_startup", NULL);
	m_talk_location=g_key_file_get_boolean(kf, "calendar_settings", "talk_location", NULL);
		
	//listview preferences
	m_12hour_format=g_key_file_get_boolean(kf, "calendar_settings", "hour_format", NULL);	
	m_use_end_time = g_key_file_get_boolean(kf, "calendar_settings", "show_end_time", NULL);
			
	//window size	
	m_window_width = g_key_file_get_integer(kf, "calendar_settings", "window_width", NULL);
	m_window_height=g_key_file_get_integer(kf, "calendar_settings", "window_height", NULL);
	
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
	g_key_file_set_boolean(kf, "calendar_settings", "talk_location", m_talk_location);
		
	//format
	g_key_file_set_boolean(kf, "calendar_settings", "hour_format", m_12hour_format);
	g_key_file_set_boolean(kf, "calendar_settings", "show_end_time", m_use_end_time);
	
	//window size	
	g_key_file_set_integer(kf, "calendar_settings", "window_width", m_window_width);
	g_key_file_set_integer(kf, "calendar_settings", "window_height", m_window_height); 
	
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
 * @brief Gets a human-readable time string for speech synthesis.
 * @param hour The hour (0-23).
 * @param min The minute (0-59).
 * @return A string like "10:30 am" or "14:45".
 */
char* get_time_str_talk(int hour, int min)
{
	char *time_str = "";
	char *hour_str = "";
	char *min_str = "";	
	char *ampm_str = "";
	
	if(m_12hour_format) {
	
	if (hour >= 13 && hour <= 23)
	{
	int corrected_hour = hour - 12;
	ampm_str = "pm ";					
	hour_str =get_cardinal_string(corrected_hour);
	}
	if(hour == 12)
	{
	ampm_str = " pm ";					
	hour_str =get_cardinal_string(hour);
	}
	if(hour <12)
	{
	ampm_str = "am ";					
	hour_str =get_cardinal_string(hour);
	}
	
	time_str= g_strconcat(time_str, hour_str," ", NULL);
	
	if (min > 0 && min< 10)
	{				
	
	time_str= g_strconcat(time_str, "zero ", NULL);
	
	min_str=get_cardinal_string(min);		
	time_str= g_strconcat(time_str, min_str," ", NULL);
	}
	else if(min >=10)
	{
	min_str=get_cardinal_string(min);	
	time_str= g_strconcat(time_str, min_str," ", NULL);
	}
	
	time_str= g_strconcat(time_str," ", ampm_str, NULL);
	
	} //12hour format
	
	else
	{				
	hour_str =get_cardinal_string(hour);		
	time_str= g_strconcat(time_str, hour_str," ", NULL);
	
	if (min > 0 && min < 10)
	{
	time_str= g_strconcat(time_str, "zero ", NULL);
	
	min_str=get_cardinal_string(min);		
	time_str= g_strconcat(time_str, min_str," ", NULL);
	}
	else if(min >=10)
	{
	min_str=get_cardinal_string(min);		
	time_str= g_strconcat(time_str, min_str," ", NULL);
	}			    				
	} //24 hour format
	
	return time_str;
}

/**
 * @brief Gets a formatted time string (e.g., "10:30" or "10:30 am").
 * @param hour The hour.
 * @param min The minute.
 * @return A newly allocated time string. The caller is responsible for freeing this.
 */
char* get_time_str(int hour, int min)
{
	char *time_str = "";
	char *hour_str = "";
	char *min_str = "";	
	char *ampm_str = " ";
	
	if (m_12hour_format)
	{
	
	if(hour == 0) //12am midnight
	{
	ampm_str = "am ";					
	hour_str = g_strdup_printf("%d", 12);	
	}
	
	if (hour >= 13 && hour <= 23)
	{
	int shour = hour;
	shour = shour - 12;
	ampm_str = "pm ";
	hour_str = g_strdup_printf("%d", shour);
	}
	if(hour == 12)
	{
	ampm_str = "pm ";					
	hour_str = g_strdup_printf("%d", hour);
	}
	if(hour <12 && hour >0)
	{
	ampm_str = "am ";					
	hour_str = g_strdup_printf("%d", hour);
	}	
	} // 12 hour format
	
	else //24 hour
	{
	hour_str = g_strdup_printf("%d", hour);
	} // 24
	
	min_str = g_strdup_printf("%d", min);
	
	if (min < 10)
	{
	time_str = g_strconcat(time_str, hour_str, ":0", min_str, NULL);
	}
	else
	{
	time_str = g_strconcat(time_str, hour_str, ":", min_str, NULL);
	}
	
	if (m_12hour_format) time_str = g_strconcat(time_str, ampm_str, NULL);
	else time_str = g_strconcat(time_str, " ", NULL);
	
	return time_str;
}

//======================================================================
static char* get_day_of_week(int day, int month, int year) 
{

	char* weekday_str="";
	GDate* day_date;
	day_date = g_date_new_dmy(day, month, year);
	GDateWeekday weekday =g_date_get_weekday(day_date);
		
		
	switch(weekday)
	{
	case G_DATE_MONDAY:
	weekday_str="monday";
	break;
	case G_DATE_TUESDAY:
	weekday_str="tuesday";
	break;
	case G_DATE_WEDNESDAY:
	weekday_str="wednesday";
	break;
	case G_DATE_THURSDAY:
	weekday_str="thursday";
	break;
	case G_DATE_FRIDAY:
	weekday_str="friday";
	break;
	case G_DATE_SATURDAY:
	weekday_str="saturday";
	break;
	case G_DATE_SUNDAY:
	weekday_str="sunday";
	break;
	default:
	weekday_str="unknown";
	}//switch

	return weekday_str;
}
//=====================================================================
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

//=====================================================================
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

//======================================================================
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

// Function to sanitize text by removing all punctuation except letters and spaces
static gchar* sanitize_text(const gchar* input)
{
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


//======================================================================
// file exists
//======================================================================

gboolean  file_exists(const char *file_name)
{
    FILE *file;
    file = fopen(file_name, "r");
    if (file){       
        fclose(file);
        return TRUE; //file exists return 1
    }
    return FALSE; //file does not exist
}

//======================================================================
//GTASK speaking
//======================================================================

static void task_callbk(GObject *gobject,GAsyncResult *res,  gpointer  user_data)
{		
	//the task callbk function is called back when the 
	//play_audio_async function has completed
	//m_talking is reset to false so that we can speak again
		
    m_talking=FALSE; 
    //g_print("gtask finished reset m_talking = %d\n",m_talking);	
    
}
//======================================================================

static void play_audio_async (GTask *task, gpointer object, gpointer task_data, GCancellable *cancellable)
{
    m_talking = TRUE; // Stop any new speaking 
    
    char* text = (char*)task_data;  
    //g_print("speak text = %s\n", text);
    
    // Use global dictionary instead of creating new one
    if (!g_global_dictionary) {
        printf("Global dictionary not initialized\n");
        g_task_return_boolean(task, FALSE);
        return;
    }
    
    // Generate audio file
    FILE* file = fopen("out.wav", "wb");
    if (file == NULL) {
        printf("Failed to create output file\n");
        g_task_return_boolean(task, FALSE);
        return;           
    }
    
    // Use tempo factor 1.75f like in the original C++ code
    synthesizer_vocoder(text, file, g_global_dictionary, 1.75f);
    fclose(file);
    
    // Play the audio file
    char command_str[256];
    snprintf(command_str, sizeof(command_str), "aplay -c 1 -f S16_LE -r 16000 out.wav 2>/dev/null || echo 'No aplay available'");
    system(command_str);
    
    g_task_return_boolean(task, TRUE);
}


/**
 * @brief Callback function for the "Add Event" button.
 * It retrieves data from dialog widgets, sanitizes it, and inserts a new event into the database.
 * @param button The GtkButton that triggered the callback.
 * @param user_data A pointer to the GListStore.
 */
static void callbk_add_new_event(GtkButton *button, gpointer user_data)
{	
    GListStore *store = user_data;	
    GtkWidget *window = g_object_get_data(G_OBJECT(button), "button-add-window-key");
    GtkWidget *calendar = g_object_get_data(G_OBJECT(button), "button-add-calendar-key");
    GtkWidget *label_date = g_object_get_data(G_OBJECT(window), "window-label-date-key");
    
    int start_day = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "day-key"));
    int start_month = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "month-key"));
    int start_year = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "year-key"));
    
    int end_day = start_day;
    int end_month = start_month;
    int end_year = start_year;
    
    GtkWidget *dialog = g_object_get_data(G_OBJECT(button), "dialog-key");
    GtkWidget *entry_summary = g_object_get_data(G_OBJECT(button), "entry-summary-key");
    GtkWidget *entry_description = g_object_get_data(G_OBJECT(button), "entry-description-key");
    GtkWidget *entry_location = g_object_get_data(G_OBJECT(button), "entry-location-key");
    
    GtkWidget *spin_button_start_hour = g_object_get_data(G_OBJECT(button), "spin-start-hour-key");
    GtkWidget *spin_button_start_min = g_object_get_data(G_OBJECT(button), "spin-start-min-key");
    GtkWidget *spin_button_end_hour = g_object_get_data(G_OBJECT(button), "spin-end-hour-key");
    GtkWidget *spin_button_end_min = g_object_get_data(G_OBJECT(button), "spin-end-min-key");
        
    GtkWidget *check_button_allday = g_object_get_data(G_OBJECT(button), "check-button-allday-key");
    GtkWidget *check_button_isyearly = g_object_get_data(G_OBJECT(button), "check-button-isyearly-key");
    GtkWidget *check_button_priority = g_object_get_data(G_OBJECT(button), "check-button-priority-key");
        
    GtkEntryBuffer *buffer_summary = gtk_entry_get_buffer(GTK_ENTRY(entry_summary));
    const char* summary = gtk_entry_buffer_get_text(buffer_summary);
    char* clean_summary = sanitize_text(summary);
        
    GtkEntryBuffer *buffer_description = gtk_entry_get_buffer(GTK_ENTRY(entry_description));
    const char* description = gtk_entry_buffer_get_text(buffer_description);	
    char* clean_description = sanitize_text(description);
    
    GtkEntryBuffer *buffer_location = gtk_entry_get_buffer(GTK_ENTRY(entry_location));
    const char* location = gtk_entry_buffer_get_text(buffer_location);
    char* clean_location = sanitize_text(location);
    
    int start_hour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_button_start_hour));
    int start_min = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_button_start_min));
    int end_hour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_button_end_hour));
    int end_min = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_button_end_min));
    
    int is_allday = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_allday));	
    int is_yearly = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_isyearly));	
    int is_priority = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_priority));
    
    CalendarEvent *new_event = g_object_new(CALENDAR_TYPE_EVENT, NULL);
    
    // FIX: Removed internal g_strdup. Pass raw pointers since object setters handle duplicating strings.
    g_object_set(new_event, 
                 "summary", clean_summary, 
                 "location", clean_location, 
                 "description", clean_description, 
                 "startyear", start_year, 
                 "startmonth", start_month, 
                 "startday", start_day, 
                 "starthour", start_hour, 
                 "startmin", start_min, 
                 "endyear", end_year, 
                 "endmonth", end_month, 
                 "endday", end_day, 
                 "endhour", end_hour, 
                 "endmin", end_min, 
                 "isyearly", is_yearly, 
                 "isallday", is_allday, 
                 "ispriority", is_priority, 
                 NULL);
    
    int new_id = db_insert_event(db_handle, new_event);
    if (new_id == -1) {
        g_warning("Failed to append new event.\n");
    }
    g_object_unref(new_event);
            
    // Safe memory release using native standard utility calls
    g_free(clean_summary);
    g_free(clean_location);
    g_free(clean_description);
    
    set_marks_on_calendar(GTK_CALENDAR(calendar));
    update_calendar(GTK_CALENDAR(calendar), GTK_LABEL(label_date));	
    update_store(GTK_CALENDAR(calendar), store);		
    gtk_window_destroy(GTK_WINDOW(dialog));
}

//======================================================================
//New Event
//======================================================================

/**
 * @brief Callback function to create and show a new event dialog.
 * @param action The GSimpleAction that triggered the callback.
 * @param parameter The GVariant parameter (unused).
 * @param user_data A pointer to the GListStore.
 */
static void callbk_new_event(GSimpleAction *action, GVariant *parameter, gpointer user_data)
{	
    GListStore *store = user_data;
    GtkWidget *window = g_object_get_data(G_OBJECT(store), "store-window-key");
    GtkWidget *calendar = g_object_get_data(G_OBJECT(store), "store-calendar-key");
    
    // 1. Fetch calendar timestamp object
    GDateTime* cal_date = gtk_calendar_get_date(GTK_CALENDAR(calendar));
    
    int day = g_date_time_get_day_of_month(cal_date);
    int month = g_date_time_get_month(cal_date);
    int year = g_date_time_get_year(cal_date);
    
    // Free the GDateTime reference immediately to prevent memory leakage
    g_date_time_unref(cal_date);
    
    
    // Forces  standard padding (e.g. "05-09-2026" instead of "5-9-2026")
    char* date_str = g_strdup_printf("%02d-%02d-%04d", day, month, year);
        
    GtkWidget *dialog;
    GtkWidget *button_add_event;	
    GtkWidget *grid;
    GtkWidget *label_date;	
    GtkWidget *label_summary;
    GtkWidget *entry_summary;	
    GtkWidget *label_description;
    GtkWidget *entry_description;	
    GtkWidget *label_location;
    GtkWidget *entry_location;
    
    GtkWidget *label_spacer1;
    GtkWidget *label_spacer2;
    GtkWidget *label_spacer3;
    GtkWidget *label_spacer4;
        
    GtkWidget *check_button_allday;	
    GtkWidget *check_button_isyearly;
    GtkWidget *check_button_priority;
    
    GtkWidget *label_start_time;
    GtkWidget *spin_button_start_hour;	
    GtkWidget *spin_button_start_min;
    GtkWidget *label_end_time;
    GtkWidget *spin_button_end_hour;	
    GtkWidget *spin_button_end_min;	
    
    dialog = gtk_window_new(); 
    gtk_window_set_title(GTK_WINDOW(dialog), "New Event");
    
    // Label creates its own internal text duplicate buffer automatically
    label_date = gtk_label_new(date_str);
    
    // Safe to release date_str instantly here
    g_free(date_str);
    
    GtkAdjustment *adjustment_start_hour = gtk_adjustment_new(1.00, 0.0, 23.00, 1.0, 1.0, 0.0);
    GtkAdjustment *adjustment_start_min = gtk_adjustment_new(0.00, 0.0, 59.00, 1.0, 1.0, 0.0);
    GtkAdjustment *adjustment_end_hour = gtk_adjustment_new(1.00, 0.0, 23.00, 1.0, 1.0, 0.0);
    GtkAdjustment *adjustment_end_min = gtk_adjustment_new(0.00, 0.0, 59.00, 1.0, 1.0, 0.0);
    
    label_spacer1 = gtk_label_new("");
    label_spacer2 = gtk_label_new("");
    label_spacer3 = gtk_label_new("");
    label_spacer4 = gtk_label_new("");
    
    button_add_event = gtk_button_new_with_label("Add Event");

    g_signal_connect(GTK_BUTTON(button_add_event), "clicked", G_CALLBACK(callbk_add_new_event), store);
    g_object_set_data(G_OBJECT(button_add_event), "button-add-window-key", window);
    g_object_set_data(G_OBJECT(button_add_event), "button-add-calendar-key", calendar);
    
    grid = gtk_grid_new();	
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    
    label_start_time = gtk_label_new("Start Time: ");
    spin_button_start_hour = gtk_spin_button_new(adjustment_start_hour, 1.0, 0);
    spin_button_start_min = gtk_spin_button_new(adjustment_start_min, 1.0, 0);
    label_end_time = gtk_label_new("End Time: ");		
    spin_button_end_hour = gtk_spin_button_new(adjustment_end_hour, 1.0, 0);
    spin_button_end_min = gtk_spin_button_new(adjustment_end_min, 1.0, 0);
            
    label_summary = gtk_label_new("Summary: ");
    entry_summary = gtk_entry_new();
    gtk_entry_set_has_frame(GTK_ENTRY(entry_summary), TRUE); 
    gtk_entry_set_max_length(GTK_ENTRY(entry_summary), 100);
    
    label_description = gtk_label_new("Description: ");
    entry_description = gtk_entry_new();
    gtk_entry_set_has_frame(GTK_ENTRY(entry_description), TRUE); 
    gtk_entry_set_max_length(GTK_ENTRY(entry_description), 100);
    
    label_location = gtk_label_new("Location: ");
    entry_location = gtk_entry_new();
    gtk_entry_set_has_frame(GTK_ENTRY(entry_location), TRUE); 
    gtk_entry_set_max_length(GTK_ENTRY(entry_location), 100);
    
    check_button_allday = gtk_check_button_new_with_label("Is All Day");	
    check_button_isyearly = gtk_check_button_new_with_label("Is Yearly");
    check_button_priority = gtk_check_button_new_with_label("Is High Priority");
    
    g_object_set_data(G_OBJECT(button_add_event), "day-key", GINT_TO_POINTER(day));
    g_object_set_data(G_OBJECT(button_add_event), "month-key", GINT_TO_POINTER(month));
    g_object_set_data(G_OBJECT(button_add_event), "year-key", GINT_TO_POINTER(year));
    
    g_object_set_data(G_OBJECT(button_add_event), "dialog-key", dialog);
    g_object_set_data(G_OBJECT(button_add_event), "window-key", window);
    g_object_set_data(G_OBJECT(button_add_event), "entry-summary-key", entry_summary);
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
    gtk_grid_attach(GTK_GRID(grid), entry_summary, 2, 2, 3, 1);
    gtk_grid_attach(GTK_GRID(grid), label_description, 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_description, 2, 3, 3, 1);
    gtk_grid_attach(GTK_GRID(grid), label_location, 1, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_location, 2, 4, 3, 1);
    gtk_grid_attach(GTK_GRID(grid), label_spacer1, 1, 5, 3, 1);
        
    gtk_grid_attach(GTK_GRID(grid), label_start_time, 1, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), spin_button_start_hour, 2, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), spin_button_start_min, 3, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label_end_time, 1, 7, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), spin_button_end_hour, 2, 7, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), spin_button_end_min, 3, 7, 1, 1);
    
    gtk_grid_attach(GTK_GRID(grid), label_spacer2, 1, 8, 3, 1);
    gtk_grid_attach(GTK_GRID(grid), check_button_allday, 1, 9, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), check_button_isyearly, 2, 9, 1, 1);  
    gtk_grid_attach(GTK_GRID(grid), check_button_priority, 3, 9, 1, 1);
    
    gtk_grid_attach(GTK_GRID(grid), label_spacer4, 1, 10, 3, 1);
    gtk_grid_attach(GTK_GRID(grid), button_add_event, 1, 11, 4, 1);
    
    gtk_window_set_child(GTK_WINDOW(dialog), grid);	
    gtk_window_present(GTK_WINDOW(dialog));	
}


//======================================================================
// update event
//======================================================================

/**
 * @brief Callback function for the "Update Event" button.
 * It retrieves data from dialog widgets, sanitizes it, and updates an existing event in the database.
 * @param button The GtkButton that triggered the callback.
 * @param user_data A pointer to the CalendarEvent object to be updated.
 */
static void callbk_update_event(GtkButton *button, gpointer user_data)
{
    CalendarEvent *selectedevent = user_data; // user_data is selectedevent (not store)
    
    GtkWidget *dialog = g_object_get_data(G_OBJECT(button), "dialog-key");
    GtkWidget *window = g_object_get_data(G_OBJECT(button), "window-key");
    GtkWidget *calendar = g_object_get_data(G_OBJECT(button), "calendar-key");
    GListStore *store = g_object_get_data(G_OBJECT(button), "store-key");
    GtkWidget *label_date = g_object_get_data(G_OBJECT(window), "window-label-date-key");
    
    int start_day = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "day-key"));
    int start_month = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "month-key"));
    int start_year = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "year-key"));
    
    // Multiday not currently supported
    int end_day = start_day;
    int end_month = start_month;
    int end_year = start_year;
            
    GtkWidget *entry_summary = g_object_get_data(G_OBJECT(button), "entry-summary-key");
    GtkWidget *entry_description = g_object_get_data(G_OBJECT(button), "entry-description-key");
    GtkWidget *entry_location = g_object_get_data(G_OBJECT(button), "entry-location-key");
    
    GtkWidget *spin_button_start_hour = g_object_get_data(G_OBJECT(button), "spin-start-hour-key");
    GtkWidget *spin_button_start_min = g_object_get_data(G_OBJECT(button), "spin-start-min-key");
    GtkWidget *spin_button_end_hour = g_object_get_data(G_OBJECT(button), "spin-end-hour-key");
    GtkWidget *spin_button_end_min = g_object_get_data(G_OBJECT(button), "spin-end-min-key");
        
    GtkWidget *check_button_allday = g_object_get_data(G_OBJECT(button), "check-button-allday-key");
    GtkWidget *check_button_isyearly = g_object_get_data(G_OBJECT(button), "check-button-isyearly-key");
    GtkWidget *check_button_priority = g_object_get_data(G_OBJECT(button), "check-button-priority-key");
            
    GtkEntryBuffer *buffer_summary = gtk_entry_get_buffer(GTK_ENTRY(entry_summary));
    const char* summary = gtk_entry_buffer_get_text(buffer_summary);
    char* clean_summary = sanitize_text(summary);
    
    GtkEntryBuffer *buffer_description = gtk_entry_get_buffer(GTK_ENTRY(entry_description));
    const char* description = gtk_entry_buffer_get_text(buffer_description);
    char* clean_description = sanitize_text(description);
    
    GtkEntryBuffer *buffer_location = gtk_entry_get_buffer(GTK_ENTRY(entry_location));
    const char* location = gtk_entry_buffer_get_text(buffer_location);
    char* clean_location = sanitize_text(location);
        
    int start_hour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_button_start_hour));
    int start_min = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_button_start_min));
    int end_hour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_button_end_hour));
    int end_min = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_button_end_min));
    
    int is_allday = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_allday));    
    int is_yearly = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_isyearly));
    int is_priority = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_priority));
      
    calendar_event_set_summary(selectedevent, clean_summary);
    calendar_event_set_location(selectedevent, clean_location);
    calendar_event_set_description(selectedevent, clean_description);
    
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
    if (db_update_event(db_handle, selectedevent) != 0) {        
        g_warning("Failed to update event with ID: %d\n", selected_event_id);
    }
    
    // Use standard glib resource freeing function (g_free) for stability
    g_free(clean_summary);
    g_free(clean_location);
    g_free(clean_description);
    
    // Update visual interface components
    set_marks_on_calendar(GTK_CALENDAR(calendar));
    update_calendar(GTK_CALENDAR(calendar), GTK_LABEL(label_date));
    update_store(GTK_CALENDAR(calendar), store);        
    
    gtk_window_destroy(GTK_WINDOW(dialog));
}


//======================================================================
//Edit event
//======================================================================
/**
 * @brief Callback function to create and show a dialog to edit a selected event.
 * @param action The GSimpleAction that triggered the callback.
 * @param parameter The GVariant parameter (unused).
 * @param user_data A pointer to the GtkSingleSelection.
 */
static void callbk_edit_event(GSimpleAction *action, GVariant *parameter, gpointer user_data)
{	
    GtkSingleSelection *selection = user_data; // user_data is a GtkSingleSelection
    GListModel *model = gtk_single_selection_get_model(selection);
    GListStore *store = G_LIST_STORE(model); 
    CalendarEvent* selectedevent = gtk_single_selection_get_selected_item(GTK_SINGLE_SELECTION(selection));
	
    if (selectedevent == NULL) {
        g_print("No event selected.\n");
        return;
    }
	
    GtkWidget *window = g_object_get_data(G_OBJECT(selection), "selection-window-key");
    GtkWidget *calendar = g_object_get_data(G_OBJECT(selection), "selection-calendar-key");
	
    const char *summary = calendar_event_get_summary(CALENDAR_EVENT(selectedevent));
    const char *description = calendar_event_get_description(CALENDAR_EVENT(selectedevent));
    const char *location = calendar_event_get_location(CALENDAR_EVENT(selectedevent));
	
    int start_day = calendar_event_get_start_day(CALENDAR_EVENT(selectedevent));
    int start_month = calendar_event_get_start_month(CALENDAR_EVENT(selectedevent));
    int start_year = calendar_event_get_start_year(CALENDAR_EVENT(selectedevent));
	
    int start_hour = calendar_event_get_start_hour(CALENDAR_EVENT(selectedevent));
    int start_min = calendar_event_get_start_min(CALENDAR_EVENT(selectedevent));
    int end_hour = calendar_event_get_end_hour(CALENDAR_EVENT(selectedevent));
    int end_min = calendar_event_get_end_min(CALENDAR_EVENT(selectedevent));
	
    int is_allday = calendar_event_get_is_allday(CALENDAR_EVENT(selectedevent));	
    int is_yearly = calendar_event_get_is_yearly(CALENDAR_EVENT(selectedevent));	
    int is_priority = calendar_event_get_is_priority(CALENDAR_EVENT(selectedevent));
		
    GtkWidget *dialog;
    GtkWidget *button_update;	
    GtkWidget *grid;
    GtkWidget *label_date;	
    GtkWidget *label_summary;
    GtkWidget *entry_summary;	
    GtkWidget *label_description;
    GtkWidget *entry_description;	
    GtkWidget *label_location;
    GtkWidget *entry_location;
	
    GtkWidget *label_spacer1;
    GtkWidget *label_spacer2;
    GtkWidget *label_spacer4;
		
    GtkWidget *check_button_allday;	
    GtkWidget *check_button_isyearly;
    GtkWidget *check_button_priority;
	
    GtkWidget *label_start_time;
    GtkWidget *spin_button_start_hour;	
    GtkWidget *spin_button_start_min;
    GtkWidget *label_end_time;
    GtkWidget *spin_button_end_hour;	
    GtkWidget *spin_button_end_min;	
		
    dialog = gtk_window_new(); 
    gtk_window_set_title(GTK_WINDOW(dialog), "Update Event");
	
    // Leak-free string building pattern that formats date text safely
    char* date_str = g_strdup_printf("%02d-%02d-%04d", start_day, start_month, start_year);
    label_date = gtk_label_new(date_str);
    g_free(date_str); //  Free instantly now that the widget has duplicated its content
	
    GtkAdjustment *adjustment_start_hour = gtk_adjustment_new(1.00, 0.0, 23.00, 1.0, 1.0, 0.0);
    GtkAdjustment *adjustment_start_min = gtk_adjustment_new(0.00, 0.0, 59.00, 1.0, 1.0, 0.0);
    GtkAdjustment *adjustment_end_hour = gtk_adjustment_new(1.00, 0.0, 23.00, 1.0, 1.0, 0.0);
    GtkAdjustment *adjustment_end_min = gtk_adjustment_new(0.00, 0.0, 59.00, 1.0, 1.0, 0.0);
	
    label_spacer1 = gtk_label_new("");
    label_spacer2 = gtk_label_new("");
    label_spacer4 = gtk_label_new("");
	
    button_update = gtk_button_new_with_label("Update Selected Event");
    g_signal_connect(GTK_BUTTON(button_update), "clicked", G_CALLBACK(callbk_update_event), selectedevent);
	
    g_object_set_data(G_OBJECT(button_update), "dialog-key", dialog);
    g_object_set_data(G_OBJECT(button_update), "window-key", window);
    g_object_set_data(G_OBJECT(button_update), "calendar-key", calendar);
    g_object_set_data(G_OBJECT(button_update), "store-key", store);
	
    grid = gtk_grid_new();	
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
    label_start_time = gtk_label_new("Start Time: ");
    spin_button_start_hour = gtk_spin_button_new(adjustment_start_hour, 1.0, 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_start_hour), start_hour);
    spin_button_start_min = gtk_spin_button_new(adjustment_start_min, 1.0, 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_start_min), start_min);

    label_end_time = gtk_label_new("End Time: ");		
    spin_button_end_hour = gtk_spin_button_new(adjustment_end_hour, 1.0, 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_end_hour), end_hour);
    spin_button_end_min = gtk_spin_button_new(adjustment_end_min, 1.0, 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_end_min), end_min);
	
    label_summary = gtk_label_new("Summary: ");
    entry_summary = gtk_entry_new();
    gtk_entry_set_has_frame(GTK_ENTRY(entry_summary), TRUE); 
    gtk_entry_set_max_length(GTK_ENTRY(entry_summary), 100);
    GtkEntryBuffer *buffer_summary = gtk_entry_buffer_new(summary, -1);
    gtk_entry_set_buffer(GTK_ENTRY(entry_summary), buffer_summary);
	
    label_description = gtk_label_new("Description: ");
    entry_description = gtk_entry_new();
    gtk_entry_set_has_frame(GTK_ENTRY(entry_description), TRUE); 
    gtk_entry_set_max_length(GTK_ENTRY(entry_description), 100);
    GtkEntryBuffer *buffer_description = gtk_entry_buffer_new(description, -1);
    gtk_entry_set_buffer(GTK_ENTRY(entry_description), buffer_description);
	
    label_location = gtk_label_new("Location: ");
    entry_location = gtk_entry_new();
    gtk_entry_set_has_frame(GTK_ENTRY(entry_location), TRUE); 
    gtk_entry_set_max_length(GTK_ENTRY(entry_location), 100);
    GtkEntryBuffer *buffer_location = gtk_entry_buffer_new(location, -1);
    gtk_entry_set_buffer(GTK_ENTRY(entry_location), buffer_location);

    check_button_allday = gtk_check_button_new_with_label("Is All Day");
    gtk_check_button_set_active(GTK_CHECK_BUTTON(check_button_allday), is_allday);	
    check_button_isyearly = gtk_check_button_new_with_label("Is Yearly");
    gtk_check_button_set_active(GTK_CHECK_BUTTON(check_button_isyearly), is_yearly);
    check_button_priority = gtk_check_button_new_with_label("Is High Priority");
    gtk_check_button_set_active(GTK_CHECK_BUTTON(check_button_priority), is_priority);
	
    g_object_set_data(G_OBJECT(button_update), "day-key", GINT_TO_POINTER(start_day));
    g_object_set_data(G_OBJECT(button_update), "month-key", GINT_TO_POINTER(start_month));
    g_object_set_data(G_OBJECT(button_update), "year-key", GINT_TO_POINTER(start_year));
	
    g_object_set_data(G_OBJECT(button_update), "entry-summary-key", entry_summary);
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
    gtk_grid_attach(GTK_GRID(grid), entry_summary, 2, 2, 3, 1);
    gtk_grid_attach(GTK_GRID(grid), label_description, 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_description, 2, 3, 3, 1);
    gtk_grid_attach(GTK_GRID(grid), label_location, 1, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_location, 2, 4, 3, 1);
    gtk_grid_attach(GTK_GRID(grid), label_spacer1, 1, 5, 3, 1);
		
    gtk_grid_attach(GTK_GRID(grid), label_start_time, 1, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), spin_button_start_hour, 2, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), spin_button_start_min, 3, 6, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label_end_time, 1, 7, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), spin_button_end_hour, 2, 7, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), spin_button_end_min, 3, 7, 1, 1);
	
    gtk_grid_attach(GTK_GRID(grid), label_spacer2, 1, 8, 3, 1);
    gtk_grid_attach(GTK_GRID(grid), check_button_allday, 1, 9, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), check_button_isyearly, 2, 9, 1, 1);  
    gtk_grid_attach(GTK_GRID(grid), check_button_priority, 3, 9, 1, 1);
	
    gtk_grid_attach(GTK_GRID(grid), label_spacer4, 1, 10, 3, 1);
    gtk_grid_attach(GTK_GRID(grid), button_update, 1, 11, 4, 1);
	
    gtk_window_set_child(GTK_WINDOW(dialog), grid);	
    gtk_window_present(GTK_WINDOW(dialog));	
}


//======================================================================
// Delete event
//======================================================================
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
    
    //GtkWidget *window = g_object_get_data(G_OBJECT(selection), "selection-window-key");
	GtkWidget *calendar = g_object_get_data(G_OBJECT(selection), "selection-calendar-key");
	GtkWidget *label_date =g_object_get_data(G_OBJECT(selection), "selection-label-key");	

    // Get the ID directly from the selected event object
    int event_id_to_delete = calendar_event_get_eventid(selectedevent);

    if (db_delete_event(db_handle, event_id_to_delete) == 0) {
       //g_print("Successfully removed event with ID: %d\n", event_id_to_delete);
    } else {
        g_warning("Failed to remove event with ID: %d\n", event_id_to_delete);
    }
			
	set_marks_on_calendar(GTK_CALENDAR(calendar));
	update_calendar(GTK_CALENDAR(calendar), GTK_LABEL(label_date));	
	update_store(GTK_CALENDAR(calendar), store);
	
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
	set_marks_on_calendar(GTK_CALENDAR(calendar));
	update_calendar(GTK_CALENDAR(calendar), GTK_LABEL(label_date));
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
            
            gint start_year = 0;
            gint start_month = 0;
            gint start_day = 0;
            gint start_hour = 0;
            gint start_min = 0;
            gint start_seconds = 0;
            
            gint end_year = 0;
            gint end_month = 0;
            gint end_day = 0;
            gint end_hour = 0;
            gint end_min = 0;
            gint end_seconds = 0;
            
            gint is_yearly = 0;
            gint is_allday = 0;
            gint is_priority = 0;
            
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
            
            // Add priority field
            g_data_output_stream_put_string(data_stream, priority_str, NULL, NULL);
            
            // Add is_allday field (as a custom property)
            gchar *allday_str = is_allday ? "X-ISALLDAY:1\n" : "X-ISALLDAY:0\n";
            g_data_output_stream_put_string(data_stream, allday_str, NULL, NULL);
            
            // Add recurrence rule if yearly
            if (is_yearly) {
                gchar *recurrence_str = g_strdup_printf("RRULE:FREQ=YEARLY;INTERVAL=1;BYMONTH=%s;BYMONTHDAY=%s\n",
                                                      start_month_str, start_day_str);
                g_data_output_stream_put_string(data_stream, recurrence_str, NULL, NULL);
                g_free(recurrence_str);
            }
            
            g_data_output_stream_put_string(data_stream, "END:VEVENT\n", NULL, NULL);
            
            // Clean up
            g_free(start_day_str);
            g_free(start_month_str);
            g_free(start_year_str);
            g_free(start_hour_str);
            g_free(start_min_str);
            g_free(start_sec_str);
            
            g_free(end_day_str);
            g_free(end_month_str);
            g_free(end_year_str);
            g_free(end_hour_str);
            g_free(end_min_str);
            g_free(end_sec_str);
            
            g_free(dtstart_str);
            g_free(dtend_str);
            
            // Free strings from object getters
            if (summary_str) g_free(summary_str);
            if (location_str) g_free(location_str);
            if (description_str) g_free(description_str);
            
            g_object_unref(event);
        }
        
        // Write VCALENDAR footer
        g_data_output_stream_put_string(data_stream, "END:VCALENDAR\n", NULL, NULL);
        g_array_unref(all_events);
    } else {
        g_warning("Failed to retrieve events or no events found.");
    }
    
    // Clean up resources
    if (data_stream) {
        g_object_unref(data_stream);
    }
    if (file_stream) {
        g_object_unref(file_stream);
    }
    if (file) {
        g_object_unref(file);
    }
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
       
    GtkWidget *window = user_data; //need window to get calendar
	GtkWidget *calendar = g_object_get_data(G_OBJECT(window), "window-calendar-key");
	GListStore *store =g_object_get_data(G_OBJECT(window), "window-store-key");
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
    
    // Event Buffers
    gchar *summary = NULL, *location = NULL, *description = NULL;
    int start_y = 0, start_m = 0, start_d = 0, start_h = 0, start_min = 0;
    int end_y = 0, end_m = 0, end_d = 0, end_h = 0, end_min = 0;
    int is_priority = 0, is_yearly = 0, is_allday = 0;

    char *line = NULL;
    
    // Read all lines first to avoid stream corruption
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
    
    // Process lines
    for (int i = 0; i < lines->len; i++) {
        char *current_line = (char*)g_ptr_array_index(lines, i);
        //g_print("Processing line: %s\n", current_line);
        
        if (strlen(current_line) == 0) continue;
        
        char *colon = strchr(current_line, ':');
        if (!colon) continue;

        *colon = '\0'; 
        const char *key = current_line;
        const char *value = colon + 1;

        //new version check
       if (g_strcmp0(key, "VERSION") == 0) {
        // validate version (should be "2.0" for RFC 5545)
        if (value && strcmp(value, "2.0") != 0) {
        g_warning("Warning: Unexpected iCalendar version %s", value);
        }
        }
        
         // Handle BEGIN/END VEVENT markers 
        else if (g_strcmp0(key, "BEGIN") == 0 && g_strcmp0(value, "VEVENT") == 0) {
            // Reset buffers for new event
            g_free(summary); summary = NULL;
            g_free(location); location = NULL;
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
            // Handle the custom all-day field
            is_allday = (value && strcmp(value, "1") == 0);
        }
        else if (g_strcmp0(key, "RRULE") == 0) {
            is_yearly = (value && strstr(value, "FREQ=YEARLY") != NULL);
        }
        else if (g_strcmp0(key, "END") == 0 && g_strcmp0(value, "VEVENT") == 0) {
            // Safety check - ensure we have valid data
            if (!summary && !location && !description &&
                start_y == 0 && start_m == 0 && start_d == 0 &&
                end_y == 0 && end_m == 0 && end_d == 0) {
                g_print("Warning: Empty event detected, skipping...\n");
                g_free(line);
                continue;
            }
            
            CalendarEvent *evt = NULL;
            // Determine is_allday from start time (this preserves existing logic)
            int calculated_is_allday = (start_h == 0 && start_min == 0);

            // Create and set up the event safely
            evt = g_object_new(CALENDAR_TYPE_EVENT, 0);
            if (!evt) {
                g_warning("Failed to create CalendarEvent object\n");
                g_free(line);
                continue;
            }

            // Use safe string handling with explicit NULL checks
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
                "isallday",    is_allday,  // Use the imported value
                "ispriority",  is_priority,
                NULL);

            // Insert event into database
            int result = db_insert_event(db_handle, evt);
            if (result == -1) {
                g_warning("Failed to append new event.\n");
            }            
            // Safely unref the object
            if (evt) {
				//g_print("Before unref - evt: %p\n", evt);
                g_object_unref(evt);
                evt = NULL;  // Prevent double-unref
            }
        }     
    }    
    // Cleanup
    for (int i = 0; i < lines->len; i++) {
        g_free(g_ptr_array_index(lines, i));
    }
    g_ptr_array_free(lines, TRUE);    
 
	set_marks_on_calendar(GTK_CALENDAR(calendar));
	update_calendar(GTK_CALENDAR(calendar), GTK_LABEL(label_date));    
    update_store(GTK_CALENDAR(calendar), store);
        
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
static void callbk_calendar_home(GSimpleAction * action, GVariant *parameter, gpointer user_data)
{ 
	//g_print("callbk_calendar_home\n");
	
	GtkWindow *window =user_data;	
	GtkWidget *calendar =g_object_get_data(G_OBJECT(window), "window-calendar-key");
	GListStore *store =g_object_get_data(G_OBJECT(window), "window-store-key");
	GtkWidget *label_date =g_object_get_data(G_OBJECT(window), "window-label-date-key");	
	
	GDateTime *today;
	today = g_date_time_new_now_local();
	m_start_year = g_date_time_get_year(today);
	m_start_month = g_date_time_get_month(today);
	m_start_day = g_date_time_get_day_of_month(today);	
	//g_print("Date is : %d-%d-%d \n", m_start_day, m_start_month,m_start_year);
	
	gtk_calendar_select_day (GTK_CALENDAR(calendar), today); //being depreciated and replaced by		
	//gtk_calendar_set_date (GTK_CALENDAR(calendar), today); //gtk4.20 onwards -unstable do not use
	
	update_calendar(GTK_CALENDAR(calendar), GTK_LABEL(label_date));	
	update_store(GTK_CALENDAR(calendar), store);
	g_date_time_unref(today);	
}

//======================================================================
static void callbk_calendar_next_month(GtkCalendar *calendar, gpointer user_data)
{
	//g_print("next month\n");
	update_calendar(calendar, user_data);
}
//======================================================================
static void callbk_calendar_prev_month(GtkCalendar *calendar, gpointer user_data)
{
	//g_print("prev month\n");		
	update_calendar(calendar, user_data);	
}
//======================================================================
static void callbk_calendar_next_year(GtkCalendar *calendar, gpointer user_data)
{
	//g_print("next year\n");
	update_calendar(calendar, user_data);	
}
//======================================================================
static void callbk_calendar_prev_year(GtkCalendar *calendar, gpointer user_data)
{
	//g_print("prev year\n");
	update_calendar(calendar, user_data);
}
//======================================================================

//======================================================================
// Day selected
//======================================================================

static void callbk_calendar_day_selected(GtkCalendar *calendar, gpointer user_data)
{
	//g_print("day selected\n");
	update_calendar(calendar, user_data);			
}
static void set_marks_on_calendar(GtkCalendar *calendar)
{
    //g_print("calling set marks on calendar\n");       
    GPtrArray* evt_arry_month = db_get_all_events_year_month(db_handle, m_start_year, m_start_month);
    if (!evt_arry_month) return; 

    gtk_calendar_clear_marks(calendar);
    guint8 month_days = g_date_get_days_in_month(m_start_month, m_start_year);    
    
    for (guint i = 0; i < evt_arry_month->len; i++) {  
        gint start_day = 0;
        
        // Grab the object out of the Pointer Array safely
        CalendarEvent *evt = g_ptr_array_index(evt_arry_month, i);
        if (!evt) continue;        
        
        g_object_get(evt, "startday", &start_day, NULL);        
        
        if (start_day >= 1 && start_day <= month_days) {
            gtk_calendar_mark_day(calendar, (guint)start_day);
        }
        // NO MORE g_object_unref(evt) HERE! 
    }     
    
    // This single call frees the array container AND safely unrefs all internal CalendarEvents
    g_ptr_array_free(evt_arry_month, TRUE); 
}

//======================================================================
//Update date label
//======================================================================
static void update_date_label(GtkCalendar *calendar, gpointer user_data)
{
    GtkWidget *label_date = (GtkWidget *) user_data;
    GDateTime *dt;

    // 1. Create local date time
    dt = g_date_time_new_local(m_start_year, m_start_month, m_start_day, 1, 1, 1);
    if (!dt) return; 

    // 2. Generate the formatted date string instantly using GLib format specifiers
    // %A = Full weekday name (e.g., Monday)
    // %e = Day of the month (1-31)
    // %B = Full month name (e.g., January)
    // %Y = 4-digit year
    gchar *formatted_date = g_date_time_format(dt, "%A %e %B %Y");
    g_date_time_unref(dt); // Free datetime safely

    gchar *final_str = NULL;
    int event_num = get_number_of_day_events();

    // 3. Append event star if needed
    if (event_num > 0) {
        final_str = g_strconcat(formatted_date, "*", NULL);
    } else {
        // If no events, we can just point to or duplicate the formatted string
        final_str = g_strdup(formatted_date);
    }

    // 4. Update the UI 
    gtk_label_set_text(GTK_LABEL(label_date), final_str);

    // 5. Clean up all allocated strings to guarantee zero memory leaks
    g_free(formatted_date);
    g_free(final_str);
}


static void update_calendar(GtkCalendar *calendar, gpointer user_data)
{
	
	//g_print("update GtkCalendar\n");
	GtkWidget *label_date = (GtkWidget *)user_data;	
	GListStore *store =g_object_get_data(G_OBJECT(calendar), "calendar-store-key");
	
	GDateTime *cal_date = gtk_calendar_get_date(GTK_CALENDAR(calendar));
	
	m_start_day = g_date_time_get_day_of_month(cal_date);
	m_start_month =g_date_time_get_month(cal_date);
	m_start_year=g_date_time_get_year(cal_date);
	//g_print("Date is : %d-%d-%d \n", m_start_day, m_start_month,m_start_year);
	
	update_date_label(GTK_CALENDAR(calendar), label_date);	
	
	//set marks on calendar
	set_marks_on_calendar(GTK_CALENDAR(calendar));
	update_store(GTK_CALENDAR(calendar), store);
	
}

//======================================================================
//Search
//======================================================================

/**
 * @brief Performs a search for events based on summary str
 * @param search_str The string to search for in event data.
 */
static void search_events_summary(const char* search_str)
{
	char* search_str_lower = g_ascii_strdown(search_str,-1);
		
	GtkWidget *dialog_search_results;	
	GtkWidget *scrolled_window;	
	GtkWidget *textview; 
    GtkTextBuffer *textbuffer;
    	
	dialog_search_results =gtk_window_new(); 
	gtk_window_set_title (GTK_WINDOW (dialog_search_results), "Search Results");
	gtk_window_set_default_size(GTK_WINDOW(dialog_search_results),500,300);
	
	textview = gtk_text_view_new ();
	textbuffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (textview));     
	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (textview), GTK_WRAP_WORD_CHAR);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(textview),FALSE);
	
	scrolled_window = gtk_scrolled_window_new();	
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window),textview);
	
    char* result_str ="";	
	
    GArray* search_results = db_get_events_by_search(db_handle, search_str_lower, NULL);//search summary
     
    if (search_results && search_results->len > 0) {
        //g_print("Search results found:\n");
        for (guint i = 0; i < search_results->len; ++i) {
			CalendarEvent* event = g_array_index(search_results, CalendarEvent*, i);
			
			char *day_str= g_strdup_printf("%d",calendar_event_get_start_day(event));
			char *month_str= g_strdup_printf("%d",calendar_event_get_start_month(event));
			char *year_str= g_strdup_printf("%d",calendar_event_get_start_year(event));
			
			int hour =calendar_event_get_start_hour(event);		
			int min =calendar_event_get_start_min(event);
			
			char *time_str="";
			
			int is_allday =calendar_event_get_is_allday(event);
			
			if (!is_allday) {
				time_str= g_strconcat(time_str, "Time: ",get_time_str(hour,min),NULL);
			}
			
			result_str= g_strconcat(result_str, day_str,"-",month_str,"-",year_str," ", calendar_event_get_summary(event),
			" ", calendar_event_get_location(event),			
			" ", time_str,"\n",  
			NULL);	 
			
			g_object_unref(event);
        }
        g_array_unref(search_results);
    } else {
        g_warning("No search results found or failed to search.\n");
        if (search_results) {
             g_array_unref(search_results);
        }
    }
	
	gtk_text_buffer_set_text (textbuffer, result_str, -1);   
    gtk_window_set_child (GTK_WINDOW (dialog_search_results),scrolled_window);	
	gtk_window_present (GTK_WINDOW (dialog_search_results));	
}

/**
 * @brief Performs a search for events based on a location str
 * @param search_str The string to search for in event data.
 */
static void search_events_location(const char* search_str)
{
	char* search_str_lower = g_ascii_strdown(search_str,-1);
		
	GtkWidget *dialog_search_results;	
	GtkWidget *scrolled_window;	
	GtkWidget *textview; 
    GtkTextBuffer *textbuffer;
    	
	dialog_search_results =gtk_window_new(); 
	gtk_window_set_title (GTK_WINDOW (dialog_search_results), "Search Results");
	gtk_window_set_default_size(GTK_WINDOW(dialog_search_results),500,300);
	
	textview = gtk_text_view_new ();
	textbuffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (textview));     
	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (textview), GTK_WRAP_WORD_CHAR);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(textview),FALSE);
	
	scrolled_window = gtk_scrolled_window_new();	
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window),textview);
	
    char* result_str ="";	
	
    GArray* search_results = db_get_events_by_search(db_handle, NULL, search_str_lower);//search location
     
    if (search_results && search_results->len > 0) {
        //g_print("Search results found:\n");
        for (guint i = 0; i < search_results->len; ++i) {
			CalendarEvent* event = g_array_index(search_results, CalendarEvent*, i);
			
			char *day_str= g_strdup_printf("%d",calendar_event_get_start_day(event));
			char *month_str= g_strdup_printf("%d",calendar_event_get_start_month(event));
			char *year_str= g_strdup_printf("%d",calendar_event_get_start_year(event));
			
			int hour =calendar_event_get_start_hour(event);		
			int min =calendar_event_get_start_min(event);
			
			char *time_str="";
			
			int is_allday =calendar_event_get_is_allday(event);
			
			if (!is_allday) {
				time_str= g_strconcat(time_str, "Time: ",get_time_str(hour,min),NULL);
			}
			
			result_str= g_strconcat(result_str, day_str,"-",month_str,"-",year_str," ", calendar_event_get_summary(event),
			" ", calendar_event_get_location(event),			
			" ", time_str,"\n",  
			NULL);	 
			
			
			g_object_unref(event);
        }
        g_array_unref(search_results);
    } else {
        g_warning("No search results found or failed to search.\n");
        if (search_results) {
             g_array_unref(search_results);
        }
    }
	
	gtk_text_buffer_set_text (textbuffer, result_str, -1);  
    gtk_window_set_child (GTK_WINDOW (dialog_search_results),scrolled_window);	
	gtk_window_present (GTK_WINDOW (dialog_search_results));
	
}

/**
 * @brief Callback for the search button in the search dialog.
 * @param button The GtkButton that triggered the callback.
 * @param user_data  (unused) 
 */
static void callbk_search_events(GtkButton *button, gpointer user_data)
{

	GtkEntryBuffer *buffer_search;
	GtkWidget *entry_search = g_object_get_data(G_OBJECT(button), "entry-search-key");
	
	buffer_search = gtk_entry_get_buffer(GTK_ENTRY(entry_search));
	
	const char* search_str=gtk_entry_buffer_get_text(buffer_search);	
	char* clean_search_str = sanitize_text(search_str);
		
	GtkWidget *check_button_search_location = g_object_get_data(G_OBJECT(button), "check-button-search-location-key");

	int is_search_location = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_search_location));
	
	if(is_search_location) search_events_location(clean_search_str);
	else search_events_summary(clean_search_str);
	
	if (clean_search_str != NULL) {
       
        // free the memory that was allocated by the function
        // to prevent a memory leak.
        free(clean_search_str);
        clean_search_str = NULL; // Best practice to set the pointer to NULL after freeing.
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
static void callbk_search(GSimpleAction *action, GVariant *parameter,  gpointer user_data)
{
	GtkWidget *window = user_data;
	
	GtkWidget *dialog_search;	
	GtkWidget *box;
	GtkWidget *button_search;	
	GtkWidget *label_entry_search;
	GtkWidget *entry_search;	
	GtkWidget *check_button_search_location;
   	
	dialog_search = gtk_window_new(); 
	gtk_window_set_title(GTK_WINDOW(dialog_search), "Search Events");
	gtk_window_set_default_size(GTK_WINDOW(dialog_search), 300, 100);
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
	gtk_window_set_child(GTK_WINDOW(dialog_search), box);
	
	check_button_search_location = gtk_check_button_new_with_label("Search Location");
	
	label_entry_search = gtk_label_new("Search Text: ");
	entry_search = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(entry_search), 100);
	
	button_search = gtk_button_new_with_label("Search");
	g_signal_connect(button_search, "clicked", G_CALLBACK(callbk_search_events), window);
	g_object_set_data(G_OBJECT(button_search), "check-button-search-location-key", check_button_search_location);
	
	g_object_set_data(G_OBJECT(button_search), "dialog-search-key", dialog_search);
	g_object_set_data(G_OBJECT(button_search), "entry-search-key", entry_search);
	
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
	GtkWidget *label_result= g_object_get_data(G_OBJECT(button), "label-result-key");
	GtkWidget *spin_button_year=g_object_get_data(G_OBJECT(button), "spin-year-key");;
	
	int easter_year= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_year));
	
	GDate* easter_date = calculate_easter(easter_year);
    
    int easter_day = g_date_get_day(easter_date);
	int easter_month =g_date_get_month(easter_date);
	char* easter_month_str = get_month_string(easter_month);
	char *easter_day_str = g_strdup_printf("%i",easter_day);
	char *easter_year_str = g_strdup_printf("%i",easter_year);
	char *weekday=get_day_of_week(easter_day, easter_month, easter_year); //weekday must be a sunday
		
	char* result_str="";	
	result_str = g_strconcat(weekday, " ", easter_day_str, " ", easter_month_str, " ", easter_year_str, NULL);
	gtk_label_set_text(GTK_LABEL(label_result),result_str);
	
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
static void callbk_set_preferences(GtkButton *button, gpointer  user_data)
{
	GtkWidget *window = user_data;   
	GtkWidget *calendar =g_object_get_data(G_OBJECT(window), "window-calendar-key");	
	GtkWidget *dialog = g_object_get_data(G_OBJECT(button), "dialog-key");
	
	//calendar
	GtkWidget *check_button_hour_format= g_object_get_data(G_OBJECT(button), "check-button-hour-format-key");
	GtkWidget *check_button_show_end_time= g_object_get_data(G_OBJECT(button), "check-button-show-end-time-key");
	
	//talking
	GtkWidget *check_button_talk= g_object_get_data(G_OBJECT(button), "check-button-talk-key");
	GtkWidget *check_button_talk_startup= g_object_get_data(G_OBJECT(button), "check-button-talk-startup-key");	
	GtkWidget *check_button_talk_location= g_object_get_data(G_OBJECT(button), "check-button-talk-location-key");		
	GtkWidget *check_button_reset_all= g_object_get_data(G_OBJECT(button), "check-button-reset-all-key");
	
	//listview
	m_12hour_format=gtk_check_button_get_active (GTK_CHECK_BUTTON(check_button_hour_format));	
	m_use_end_time=gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_show_end_time));
				
	//speak
	m_talk=gtk_check_button_get_active (GTK_CHECK_BUTTON(check_button_talk));
	m_talk_at_startup=gtk_check_button_get_active (GTK_CHECK_BUTTON(check_button_talk_startup));
	m_talk_location=gtk_check_button_get_active (GTK_CHECK_BUTTON(check_button_talk_location));	
	
	m_reset_preferences=gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_reset_all));
	
	if(m_reset_preferences) {
	//reset everything
	//listview
	m_12hour_format=TRUE;
	m_use_end_time=FALSE;	
	//window size
	m_window_width=800;
	m_window_height=600;
		
	//talking
	m_talk=TRUE;			
	m_talk_at_startup=FALSE;
	m_talk_location=FALSE;			
	m_reset_preferences=FALSE; //toggle
	}
	
	config_write();	//save preferences
			
	//GListStore *store =g_object_get_data(G_OBJECT(calendar), "calendar-store-key");

	gtk_window_destroy(GTK_WINDOW(dialog));
}

/**
 * @brief Callback for the preferences action, which opens a preferences dialog.
 * @param action The GSimpleAction that triggered the callback.
 * @param parameter The GVariant parameter (unused).
 * @param user_data A pointer to the GtkWindow.
 */
 
static void callbk_preferences(GSimpleAction* action, GVariant *parameter,gpointer user_data)
{			
	//g_print("callbk preferences\n");
	
	GtkWidget *window =user_data;
    GtkWidget *dialog;
    GtkWidget *grid;
    GtkWidget *button_set;
   
    GtkWidget *check_button_talk;
    GtkWidget *check_button_talk_startup;
    GtkWidget *check_button_talk_location;
    
    GtkWidget *check_button_hour_format;
    GtkWidget *check_button_show_end_time; 
    
    GtkWidget *check_button_reset_all;
       
    // Spacers
    GtkWidget *label_spacer1;
    GtkWidget *label_spacer2;
    GtkWidget *label_spacer3;
    GtkWidget *label_spacer4;
    GtkWidget *label_spacer5;
    GtkWidget *label_spacer6;

    label_spacer1 = gtk_label_new("");
    label_spacer2 = gtk_label_new("");
    label_spacer3 = gtk_label_new("");
    label_spacer4 = gtk_label_new("");
    label_spacer5 = gtk_label_new("");
    label_spacer6 = gtk_label_new("");

    dialog =gtk_window_new();
    gtk_window_set_title (GTK_WINDOW (dialog), "Preferences");
    gtk_window_set_modal(GTK_WINDOW (dialog),TRUE);
    gtk_window_set_transient_for(GTK_WINDOW (dialog),GTK_WINDOW(window));

    grid = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    button_set = gtk_button_new_with_label ("Set Preferences");
    g_signal_connect (button_set, "clicked", G_CALLBACK (callbk_set_preferences), window);
    g_object_set_data(G_OBJECT(button_set), "dialog-key",dialog);
    
    //speech
	check_button_talk = gtk_check_button_new_with_label ("Enable Talking");
	check_button_talk_startup = gtk_check_button_new_with_label ("Talk At Startup");
	check_button_talk_location = gtk_check_button_new_with_label ("Talk Location");
	
	//calendar
	check_button_hour_format = gtk_check_button_new_with_label ("12 Hour Format");	
	check_button_show_end_time = gtk_check_button_new_with_label ("Use End Time");
	
	check_button_reset_all = gtk_check_button_new_with_label ("Reset All");
		
	//set calendar preferences
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_hour_format),m_12hour_format);	
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_show_end_time),m_use_end_time);
	
	//set speak
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_talk), m_talk);
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_talk_startup), m_talk_at_startup);
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_talk_location), m_talk_location);
	
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_reset_all), m_reset_preferences);
	
	//data setters
	g_object_set_data(G_OBJECT(button_set), "dialog-key",dialog);
	//calendar
	g_object_set_data(G_OBJECT(button_set), "check-button-hour-format-key",check_button_hour_format);
	g_object_set_data(G_OBJECT(button_set), "check-button-show-end-time-key",check_button_show_end_time);		
	
	//speaking
	g_object_set_data(G_OBJECT(button_set), "check-button-talk-key",check_button_talk);
	g_object_set_data(G_OBJECT(button_set), "check-button-talk-startup-key",check_button_talk_startup);	
	g_object_set_data(G_OBJECT(button_set), "check-button-talk-location-key",check_button_talk_location);				
	//reset
	g_object_set_data(G_OBJECT(button_set), "check-button-reset-all-key",check_button_reset_all);
	
	//grid layout	
	//Calendar preferences	
	gtk_grid_attach(GTK_GRID(grid), check_button_hour_format,    1, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), check_button_show_end_time,  2, 1, 1, 1);
	
	gtk_grid_attach(GTK_GRID(grid), label_spacer1,             1, 2, 1, 1);
		
	//speak preferences
	gtk_grid_attach(GTK_GRID(grid), check_button_talk,             1, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), check_button_talk_startup,     2, 3, 1, 1);
	
	gtk_grid_attach(GTK_GRID(grid), label_spacer2,               1, 4, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), check_button_talk_location,   1, 5, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), label_spacer3,     			 1, 6, 1, 1);
		
	
	gtk_grid_attach(GTK_GRID(grid), check_button_reset_all,  		1, 7, 1, 1);	
	gtk_grid_attach(GTK_GRID(grid), label_spacer4,       			1, 8, 1, 1);	
	gtk_grid_attach(GTK_GRID(grid), button_set,  1, 9, 3, 1);
	
	gtk_window_set_child (GTK_WINDOW (dialog), grid);	
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
	gtk_about_dialog_set_version (GTK_ABOUT_DIALOG(about_dialog), "Version 0.7.1");
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
// speak events
//======================================================================

static void callbk_speak(GSimpleAction* action, GVariant *parameter,gpointer user_data)
{	
	//g_print("callbk speak events\n");
	if(m_talking == FALSE) speak_events();	
	
}

static void speak_events() {

    if (m_talk == 0) return;
    if (m_talking == TRUE) return;
    
    // 1. Use a GString builder to eliminate concatenation leaks
    GString *speak_builder = g_string_new("");
    
    gchar *dow_str = get_day_of_week(m_start_day, m_start_month, m_start_year);    
    gchar *day_number_str = get_day_number_ordinal_string(m_start_day); 
    gchar *month_str = get_month_string(m_start_month); 
    
    g_string_append_printf(speak_builder, "%s %s %s. ", dow_str, day_number_str, month_str);
    
    GArray* events_for_day = db_get_all_events_year_month_day(db_handle, m_start_year, m_start_month, m_start_day);
        
    if (events_for_day) {      
        for (guint i = 0; i < events_for_day->len; i++) 
        {
            // Pointers must initialize to NULL to track safe disposal
            gchar *summary_str = NULL;
            gchar *location_str = NULL;
            gint start_hour = 0;
            gint start_min = 0;
            gint end_hour = 0;
            gint end_min = 0;
            gint is_allday = 0;
            gint is_priority = 0;
            
            CalendarEvent* day_event = g_array_index(events_for_day, CalendarEvent*, i);
            
            // Strings pulled here are fresh heap copies!
            g_object_get(day_event, 
                         "summary", &summary_str, 
                         "location", &location_str,
                         "starthour", &start_hour, 
                         "startmin", &start_min, 
                         "endhour", &end_hour, 
                         "endmin", &end_min,        
                         "isallday", &is_allday, 
                         "ispriority", &is_priority, 
                         NULL);
            
            if (!is_allday) {    
                gchar *time_str_start = get_time_str_talk(start_hour, start_min);    
                g_string_append_printf(speak_builder, "%s ", time_str_start);    
                g_free(time_str_start); // Free string generated by time translator
            } 
            
            if (summary_str) {
                g_string_append_printf(speak_builder, "%s. ", summary_str);
            }
            
            if (m_talk_location && location_str && strlen(location_str) > 0) {
                g_string_append_printf(speak_builder, "%s. ", location_str);
            }
            
            if (is_priority) {        
                g_string_append(speak_builder, " high priority ");
            }
            
            g_string_append_c(speak_builder, ' ');
            
            // Clean up the string allocations returned by g_object_get
            g_free(summary_str);
            g_free(location_str);
            
            g_object_unref(day_event); // Clean up container object reference safely
        }    
        g_array_free(events_for_day, TRUE); 
    } else {
        //g_print("No events found for the specified day or an error occurred.\n");
    }
        
    //g_print("Speak events: final string = %s\n", speak_builder->str);    
    
    // Sanitize the builder text output
    gchar *sanitized_text = sanitize_text(speak_builder->str);
    g_string_free(speak_builder, TRUE); // Destroy the builder framework structure
    
    if (!sanitized_text || strlen(sanitized_text) == 0) {
        //g_print("No valid text to speak after sanitization\n");
        g_free(sanitized_text);
        return;
    }    
        
    GTask* task = g_task_new(NULL, NULL, task_callbk, NULL);
    
    // Pass g_free as the third parameter so the task worker thread clears memory automatically when finished!
    g_task_set_task_data(task, sanitized_text, g_free);
  
    g_task_run_in_thread(task, play_audio_async);     
    g_object_unref(task);    
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

static void speak_time(gint hour, gint min) 
{	
    if (m_talk == 0) return;
    if (m_talking == TRUE) return;
        
    // 1. Initialize a safe GString builder to eliminate string copying leaks
    GString *speak_builder = g_string_new("the time is ");
    
    const gchar *ampm_str = "";
    const gchar *hour_str = "";
    const gchar *min_str = "";
        
    if (m_12hour_format) {
        if (hour >= 13 && hour <= 23) {
            int s_hour = hour - 12;
            ampm_str = " p.m. ";                    
            hour_str = get_cardinal_string(s_hour);
        }
        else if (hour == 12) {
            ampm_str = " p.m. ";                    
            hour_str = get_cardinal_string(hour);
        }
        else { // hour < 12
            // Corrects 0 hours (midnight) to 12 in a 12-hour spoken layout
            int s_hour = (hour == 0) ? 12 : hour;
            ampm_str = " a.m. ";                    
            hour_str = get_cardinal_string(s_hour);
        }
        
        g_string_append_printf(speak_builder, "%s ", hour_str);
        
        if (min > 0 && min < 10) {    
            min_str = get_cardinal_string(min);    
            g_string_append_printf(speak_builder, "O %s ", min_str);
        }
        else if (min >= 10) {
            min_str = get_cardinal_string(min);
            g_string_append_printf(speak_builder, "%s ", min_str);
        }    
        
        g_string_append(speak_builder, ampm_str);
            
    } // 12-hour format
    else {                
        hour_str = get_cardinal_string(hour);    
        g_string_append_printf(speak_builder, "%s ", hour_str);
        
        if (min > 0 && min < 10) {    
            min_str = get_cardinal_string(min);    
            g_string_append_printf(speak_builder, "o %s ", min_str);
        }
        else if (min >= 10) {
            min_str = get_cardinal_string(min);    
            g_string_append_printf(speak_builder, "%s ", min_str);
        }                                
    } // 24-hour format
    
    //g_print("DEBUG: speak_str builder contents = %s\n", speak_builder->str);
    
    // Sanitize text directly from the builder buffer
    gchar *sanitized_text = sanitize_text(speak_builder->str);
    g_string_free(speak_builder, TRUE); // Safe to destroy the builder container completely
    
    if (!sanitized_text || strlen(sanitized_text) == 0) {
        //g_print("No valid text to speak after sanitization\n");
        g_free(sanitized_text);
        return;
    }    
    //g_print("Speaking: %s\n", sanitized_text);
        
    GTask *task = g_task_new(NULL, NULL, task_callbk, NULL);
    
    //Pass g_free so GLib safely unallocates the heap string once the thread completes execution!
    g_task_set_task_data(task, sanitized_text, g_free);
  
    g_task_run_in_thread(task, play_audio_async);     
    g_object_unref(task);    
}

//======================================================================

//======================================================================
//list view
//======================================================================

/**
 * @brief Updates the GListStore with events for the currently selected day.
 * @param calendar The CustomCalendar widget.
 * @param user_data A pointer to the GListStore.
 */
static void update_store(GtkCalendar *calendar, gpointer user_data)
{	
	GListStore *store = user_data;
	g_list_store_remove_all(G_LIST_STORE(store));
	GDateTime* cal_date;  
	cal_date = gtk_calendar_get_date(GTK_CALENDAR(calendar));
	
	int selected_day = g_date_time_get_day_of_month(cal_date);
	int selected_month =g_date_time_get_month(cal_date);
	int selected_year=g_date_time_get_year(cal_date);	
	//get all events for selected day
	GArray* events_for_day = db_get_all_events_year_month_day(db_handle, selected_year, selected_month, selected_day);    
    if (events_for_day) {
        //g_print("Found %u events for 2025-10-27:\n", events_for_day->len);
        for (guint i = 0; i < events_for_day->len; i++) {
            CalendarEvent* event = g_array_index(events_for_day, CalendarEvent*, i);            
            g_list_store_append(G_LIST_STORE(store),event);    
            g_object_unref(event); // Free the GObject
        }
        g_array_free(events_for_day, TRUE); // Free the array
    } else {
        //g_print("No events found for the specified day or an error occurred.\n");
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
  gtk_widget_set_halign (GTK_WIDGET(label), GTK_ALIGN_START);
  gtk_label_set_use_markup(GTK_LABEL(label), TRUE);
  
  CalendarEvent *event;

  event = gtk_list_item_get_item (list_item);
  
  const char *summary = calendar_event_get_summary(CALENDAR_EVENT(event));
  const char *description = calendar_event_get_description(CALENDAR_EVENT(event));
  const char  *location =calendar_event_get_location(CALENDAR_EVENT(event));
  
  int start_hour =calendar_event_get_start_hour(CALENDAR_EVENT(event));
  int start_min = calendar_event_get_start_min(CALENDAR_EVENT(event));
  int end_hour =calendar_event_get_end_hour(CALENDAR_EVENT(event));
  int end_min = calendar_event_get_end_min(CALENDAR_EVENT(event));
  int is_allday = calendar_event_get_is_allday(CALENDAR_EVENT(event));
  int is_priority = calendar_event_get_is_priority(CALENDAR_EVENT(event));
    
  char *des_loc_str="";
  char *time_str_start = "";
  char *time_str_end = "";
  char* display_str="";
  
  
  if(!is_allday)
   {		
	//calendar display
	time_str_start =get_time_str(start_hour,start_min);
	time_str_end =get_time_str(end_hour,end_min);
	if(m_use_end_time) display_str = g_strconcat(display_str, time_str_start," to ",time_str_end, " ", summary, "\n",NULL);
	else display_str = g_strconcat(display_str, time_str_start, summary, "\n",NULL);
	
	if ((!strlen(description) == 0) && (!strlen(location) == 0))
	{
	des_loc_str = g_strconcat(des_loc_str, description, ". ",location, ".", NULL);
	}
	if ((!strlen(description) == 0) && (strlen(location) == 0))
	{
	des_loc_str = g_strconcat(des_loc_str, description, ".",NULL);
	}
	if ((strlen(description) == 0) && (!strlen(location) == 0))
	{
	des_loc_str = g_strconcat(des_loc_str, location, ".",NULL);
	}
   }
	else //allday
	{
		display_str = g_strconcat(display_str, summary, "\n",NULL);
		
		if ((!strlen(description) == 0) && (!strlen(location) == 0))
		{
		des_loc_str = g_strconcat(des_loc_str, description, ". ",location, ".", NULL);
		}
		if ((!strlen(description) == 0) && (strlen(location) == 0))
		{
		des_loc_str = g_strconcat(des_loc_str, description, ".",NULL);
		}
		if ((strlen(description) == 0) && (!strlen(location) == 0))
		{
		des_loc_str = g_strconcat(des_loc_str,"", location,".",NULL);
		}		
	} 
	
	if(is_priority) {		
	display_str =g_strconcat(display_str,des_loc_str," High Priority", NULL);
	}
	else
	{	
	display_str =g_strconcat(display_str,des_loc_str,NULL);
	}
  gtk_label_set_label (GTK_LABEL (label), display_str);    
}


//======================================================================

/**
 * @brief Callback function to quit Talk Calendar.
 * @param action The GSimpleAction that triggered the callback.
 * @param parameter The GVariant parameter (unused).
 * @param user_data A pointer to the GtkWidow.
 */
static void callbk_quit(GSimpleAction *action, GVariant *parameter, gpointer user_data) 
{ 
	GtkWindow *window=GTK_WINDOW(user_data);  
    GtkApplication* app =gtk_window_get_application(GTK_WINDOW(window)); 
    gtk_window_get_default_size(GTK_WINDOW(window), &m_window_width,&m_window_height);
	config_write(); 
	
	if (m_config_file) {
        g_free(m_config_file);
        m_config_file = NULL;
    }   
    g_application_quit(G_APPLICATION(app)); 
}
/**
 * @brief Callback function to shutdown Talk Calendar.
 * @param GtkWindow that triggered the callback.  
 * @param user_data (not used)
 */
static void callbk_shutdown(GtkWindow *window, gpointer user_data)
{
	gtk_window_get_default_size(GTK_WINDOW(window), &m_window_width,&m_window_height);
	config_write(); 
 	
	if (m_config_file) {
		g_free(m_config_file);
		m_config_file = NULL;
	}
}

//======================================================================
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

/*
 * On XFCE (X11 Backend): The display pipeline forces synchronous window mapping. 
 * When you create the window, the widgets build their layout almost instantly 
 * before the code processes the next lines. 
 * The calendar exists structurally, so gtk_calendar_mark_day succeeds.

* On GNOME (Wayland Backend): Wayland uses completely asynchronous window configuration. 
*  When gtk_window_present is called, the window and its internal nodes are scheduled to draw, 
*  but they are not created instantly. If you call gtk_calendar_mark_day immediately after 
*  creating the Calendar widget, the calendar’s internal day sub-nodes do not exist yet, 
*  causing the call to be silently ignored. 
* 
* I have attempted to fix this rendering bug across all desktop environments by delaying 
* the gtk_calendar_mark_day function until after the calendar widget emits its map or 
* realize signal. I do not think this issue is a libawaita problem.
* 
* This is why I have a callbk_calendar_initial_map callback function
*/

static void callbk_calendar_initial_map (GtkWidget *widget, gpointer user_data) {
    //g_print("Calendar is mapped to the screen. Applying initialization marks.\n");
    // Explicitly draw the markers now that the grid nodes are physically ready
    set_marks_on_calendar(GTK_CALENDAR(widget));
}

//======================================================================
static void activate (GtkApplication *app, gpointer  user_data)
{
	GtkWidget *window;	
	GMenu *menu;	
	GtkWidget *calendar;
	GtkWidget *label_date; //display selected date
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
	
	g_signal_connect(window, "destroy", G_CALLBACK(callbk_shutdown), NULL);
	
	//setup selected date label
	label_date = gtk_label_new("");
	gtk_label_set_xalign(GTK_LABEL(label_date), 0.5);
	
		
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
	
	//setup GTK Calendar
	calendar =gtk_calendar_new();
	// FORCE marking to delay until Wayland mapping loop completes:
	g_signal_connect(calendar, "map", G_CALLBACK(callbk_calendar_initial_map), NULL);

	g_signal_connect(GTK_CALENDAR(calendar), "day-selected", G_CALLBACK(callbk_calendar_day_selected),label_date);	
	g_signal_connect(GTK_CALENDAR(calendar), "next-month", G_CALLBACK(callbk_calendar_next_month), label_date);
	g_signal_connect(GTK_CALENDAR(calendar), "prev-month", G_CALLBACK(callbk_calendar_prev_month), label_date);
	g_signal_connect(GTK_CALENDAR(calendar), "next-year", G_CALLBACK(callbk_calendar_next_year), label_date);
	g_signal_connect(GTK_CALENDAR(calendar), "prev-year", G_CALLBACK(callbk_calendar_prev_year), label_date);
	
	
	GDateTime* cal_date;  
	cal_date = gtk_calendar_get_date(GTK_CALENDAR(calendar));
	
	m_start_day = g_date_time_get_day_of_month(cal_date);
	m_start_month =g_date_time_get_month(cal_date);
	m_start_year=g_date_time_get_year(cal_date);
	//g_print("Date is : %d-%d-%d \n", m_start_day, m_start_month,m_start_year);		
	
	update_date_label(GTK_CALENDAR(calendar), label_date);	
	
	
	scrolled_window = gtk_scrolled_window_new();	
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window),list_view);
	   
    gtk_widget_set_hexpand (GTK_WIDGET (list_view), TRUE);
    gtk_widget_set_vexpand (GTK_WIDGET (list_view), TRUE);

    gtk_widget_set_halign(list_view, GTK_ALIGN_FILL); 
	//gtk_widget_set_valign(list_view, GTK_ALIGN_FILL);
	
	box_listview =gtk_box_new(GTK_ORIENTATION_VERTICAL,1);	
	gtk_box_append(GTK_BOX(box_listview), scrolled_window); 
	
	box_calendar =gtk_box_new(GTK_ORIENTATION_VERTICAL,1);	
	gtk_box_append(GTK_BOX(box_calendar), label_date);	
	gtk_box_append(GTK_BOX(box_calendar), calendar); 
	gtk_widget_set_vexpand (calendar, TRUE);
    gtk_widget_set_hexpand (calendar, TRUE);
    gtk_widget_set_halign(calendar, GTK_ALIGN_FILL); //alignment
    
    //GTK_ALIGN_FILL, GTK_ALIGN_START, GTK_ALIGN_END, GTK_ALIGN_CENTER, GTK_ALIGN_BASELINE (was GTK_ALIGN_BASELINE_FILL)
	
	g_object_set_data(G_OBJECT(calendar), "calendar-window-key",window);
	g_object_set_data(G_OBJECT(calendar), "calendar-store-key",store);
	
	g_object_set_data(G_OBJECT(window), "window-store-key",store);
	g_object_set_data(G_OBJECT(window), "window-calendar-key",calendar);
	
	g_object_set_data(G_OBJECT(store), "store-window-key",window);
	g_object_set_data(G_OBJECT(store), "store-calendar-key",calendar);
	
	g_object_set_data(G_OBJECT(selection), "selection-window-key",window);
	g_object_set_data(G_OBJECT(selection), "selection-calendar-key",calendar);
	g_object_set_data(G_OBJECT(selection), "selection-label-key",label_date);
	
	g_object_set_data(G_OBJECT(window), "window-label-date-key",label_date);
	
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
	
	GSimpleAction *quit_action = g_simple_action_new("quit", NULL); //app.quit
    g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(quit_action));
    g_signal_connect(quit_action, "activate", G_CALLBACK(callbk_quit), window); 
		
	//Actions
	
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
		
	set_marks_on_calendar(GTK_CALENDAR(calendar));
	update_calendar(GTK_CALENDAR(calendar), GTK_LABEL(label_date));	
	update_store(GTK_CALENDAR(calendar), store);
	
	
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
	
	
	paned = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    gtk_paned_set_start_child(GTK_PANED(paned), box_calendar);
    gtk_paned_set_end_child(GTK_PANED(paned), box_listview);
    
    //Note initial width height values m_window_width=800 and m_window_height=600     
    // set initial divider position (in pixels)
    int divider_position =450; // 
    gtk_paned_set_position(GTK_PANED(paned),divider_position);	
	gtk_window_set_child (GTK_WINDOW (window), paned);		
	
	gtk_window_present(GTK_WINDOW (window));	
}

/**
 * @brief The main function, which initializes the application and runs it.
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line argument strings.
 * @return The application's exit code.
 */
 
int main (int  argc, char **argv)
{
    int status;
    config_initialize();
    
    db_handle = db_open("talkcalendar.db");
    if (!db_handle) {
        g_critical("Failed to open database.");
        return 1;
    }
    
    // Initialize global dictionary after DB but before GTK setup
    g_global_dictionary = Dictionary_new();
    if (!g_global_dictionary) {
        g_critical("Failed to create global dictionary");
        db_close(db_handle);
        return 1;
    }
    
    GtkApplication *app = gtk_application_new ("org.gtk.talkcalendar", G_APPLICATION_DEFAULT_FLAGS);	
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);
    
    // Clean up global dictionary
    if (g_global_dictionary) {
        Dictionary_free(g_global_dictionary);
        g_global_dictionary = NULL;
    }
    
    db_close(db_handle); 
    return status;
}

