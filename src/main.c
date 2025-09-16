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

#include <stdio.h>
#include <ctype.h>

#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gstdio.h>  //needed for g_mkdir

#include "calendarevent.h"
#include "dbmanager.h"
#include "customcalendar.h"
#include "diphone.h"
#include "wavcat.h"
#include "dictionary.h"
#include "wavplay.h"
#include "alarm.h"

// Global database handle, to be opened and closed with the application
static sqlite3 *db_handle = NULL;

// File and directory names for configuration
#define CONFIG_DIRNAME "talkcalendar"
#define CONFIG_FILENAME "talkcalendar-052"

static char * m_config_file = NULL;


//======================================================================
// Function declarations for configuration, callbacks, and helpers
//======================================================================

// Function prototypes for configuration handling
static void config_load_default(void);
static void config_read(void);
static void config_write(void);
void config_initialize(void);

// Function prototypes for GSimpleAction callbacks (toolbar menu actions)
static void callbk_new_event(GSimpleAction *action, GVariant *parameter, gpointer user_data);
static void callbk_edit_event(GSimpleAction *action, GVariant *parameter, gpointer user_data);
static void callbk_delete_event(GSimpleAction *action, GVariant *parameter, gpointer user_data);
static void callbk_confirm_delete_all(GtkButton *button, gpointer user_data);
static void callbk_delete_all(GSimpleAction *action, GVariant *parameter, gpointer user_data);
static void callbk_add_new_event(GtkButton *button, gpointer user_data);
static void callbk_update_event(GtkButton *button, gpointer user_data);

// Helper functions for sanitizing text input before database operations
char* sanitize_text(const char* input_text);

// Function prototypes for export/import functionality
static void callbk_export(GSimpleAction *action, GVariant *parameter, gpointer user_data);
static void file_save_response (GObject *source, GAsyncResult *result, void *user_data);
void export_file(char *file_name);
static void callbk_import(GSimpleAction *action, GVariant *parameter, gpointer user_data);
void import_ical_file(gpointer user_data);
static void file_open_response (GObject *source, GAsyncResult *result, void *user_data);

// Function prototypes for calendar view callbacks
static void callbk_calendar_home(GSimpleAction * action, GVariant *parameter, gpointer user_data);
static void callbk_calendar_day_selected(CustomCalendar *calendar, gpointer user_data);
static void callbk_calendar_next_month(CustomCalendar *calendar, gpointer user_data);
static void callbk_calendar_prev_month(CustomCalendar *calendar, gpointer user_data); 
static void callbk_calendar_next_year(CustomCalendar *calendar, gpointer user_data); 
static void callbk_calendar_prev_year(CustomCalendar *calendar, gpointer user_data);
static void set_tooltips_on_calendar(CustomCalendar *calendar);

// Function prototypes for search functionality
static void callbk_search(GSimpleAction *action, GVariant *parameter, gpointer user_data);
static void callbk_search_events(GtkButton *button, gpointer user_data);
//static void search_events(const char* search_str);
static void search_events_location(const char* search_str);
static void search_events_summary(const char* search_str);

// Function prototypes for Easter calculation
static void callbk_easter(GSimpleAction *action, GVariant *parameter, gpointer user_data);
GDate* calculate_easter(gint year);
static void callbk_calc_easter(GtkButton *button, gpointer user_data);

// Function prototypes for preference and info dialogs
static void callbk_preferences(GSimpleAction* action, GVariant *parameter,gpointer user_data);
static void callbk_about(GSimpleAction * action, GVariant *parameter, gpointer user_data);
int get_total_number_of_events(void);
static void callbk_info(GSimpleAction *action, GVariant *parameter, gpointer user_data);

static void callbk_speak(GtkButton *button, gpointer user_data);
static void audio_synthesis_task(GTask *task, gpointer source_object, gpointer task_data, GCancellable *cancellable);
static void audio_synthesis_completed(GObject *source_object, GAsyncResult *result, gpointer user_data);

// Function prototypes for speech synthesis functionality

static char* get_day_of_week(int day, int month, int year);
static char* get_day_number_ordinal_string(int day);
char* get_month_string(int month);
char* get_time_str_talk(int hour, int min);
static char* get_cardinal_string(int number);

// Function prototypes for GtkListView and event display
static void update_store(CustomCalendar *calendar, gpointer user_data);
static void callbk_listview (GtkListView *list, guint position, gpointer unused);
static void callbk_setup_listitem (GtkListItemFactory *factory,GtkListItem *list_item);
static void callbk_bind_listitem (GtkListItemFactory *factory, GtkListItem *list_item);
char* get_time_str(int hour, int min);

// Function prototype for update time label
static gboolean update_time_label(gpointer data);

// Function prototypes for basic alarm feature
static void callbk_alarm_button(GtkButton *button, gpointer user_data);
static void callbk_set_alarm(GtkButton *button, gpointer user_data);
static void play_alarm_audio_async (GTask *task, gpointer object,gpointer task_data,GCancellable *cancellable);
static void callbk_cancel_alarm(GtkButton *button, gpointer user_data);
static void play_alarm();

static void alarm_task_callbk(GObject *gobject,GAsyncResult *result,  gpointer  user_data);

//======================================================================
// Global preference variables
//======================================================================

// Preferences
static gboolean m_reset_preferences=FALSE;
// Talk preferences
static gboolean m_talk =TRUE;
static gboolean m_talk_at_startup =TRUE;
static gboolean m_talk_time =TRUE;

static gboolean m_talk_event_number=TRUE;

// Listview preferences
static gboolean m_12hour_format=TRUE; // am pm hour format
static gboolean m_use_end_time=FALSE;
// Window size preferences
static int m_window_width=800;
static int m_window_height=600;
// Calendar preferences
static gboolean m_show_tooltips=TRUE;
static gboolean m_is_dark_theme = FALSE; // global theme variable
//static  char* m_todaycolour="rgb(141,166,141)"; // sage
//static  char* m_eventcolour="rgb(217,230,217)"; // sage light

static char *m_todaycolour = NULL;
static char *m_eventcolour = NULL;

// Default file name for import/export
static char* m_file_name="talkcalendar.ical"; // import default

static gboolean continue_timer = TRUE;
static int m_alarm_hour=0;
static int m_alarm_min=0;
static int m_am_pm_index=0; //am=0 pm=1
static gboolean m_alarm_on=TRUE;
//static gboolean m_alarm_activated=FALSE; //TODO
//======================================================================

// Array of GActionEntry objects for application-level actions
const GActionEntry app_actions[] = {    
  { "home", callbk_calendar_home}, 
  { "newevent", callbk_new_event},
  { "editevent", callbk_edit_event},  
  { "deleteevent", callbk_delete_event},
  { "info", callbk_info},
  { "preferences", callbk_preferences} 
};
//======================================================================

// Define a structure to hold data for the GTask
typedef struct {
    DiphoneEntry** diphone_entries;
    int diphone_number;
    float tempo;
    float amplification;
} AudioTaskData;


/**
 * @brief This function is the worker. It runs in a background thread managed by GTask.
 * It performs the synthesis and playback without freezing the UI.
 * @param task The GTask object.
 * @param source_object The GObject that initiated the task (unused).
 * @param task_data A pointer to the AudioTaskData structure.
 * @param cancellable A GCancellable object (unused).
 */
static void audio_synthesis_task(GTask *task, gpointer source_object, gpointer task_data, GCancellable *cancellable) 
{
    (void) source_object;
    (void) cancellable;


    AudioTaskData *data = (AudioTaskData *)task_data;
	
    char* merge_file = "/tmp/talkcalendar.wav";
    
    // blocking code now in a thread
    merge_and_amplify_wav_files(merge_file, data->diphone_number, data->diphone_entries, 16000, data->amplification, data->tempo);
    wavplay("/tmp/talkcalendar.wav");
    
    // pass boolean result to the completion callback.
    g_task_set_task_data(task, GINT_TO_POINTER(TRUE), NULL);
    
    // data allocated for the task needs to be freed.
    g_free(data->diphone_entries);
    g_free(data);
}

/**
 * @brief This function is the completion callback. It is called on the main thread
 * when the worker function has finished. It can safely update the UI.
 * @param source_object The GObject that initiated the task (unused).
 * @param result The GAsyncResult object, which is a GTask in this case.
 * @param user_data A pointer to the user data passed to g_task_new.
 */
static void audio_synthesis_completed(GObject *source_object, GAsyncResult *result, gpointer user_data) 
{
    (void) source_object;
   
    GTask *task = G_TASK(result);
    
    GtkButton *button = GTK_BUTTON(user_data);
    // The data from g_task_set_task_data is retrieved here.
    gboolean success = GPOINTER_TO_INT(g_task_get_task_data(task));
    
    if (success) {       
		//g_print("Audio synthesis and playback finished.\n");
		
    } else {      
		//g_print("Audio synthesis and playback failed.\n");
    }
       
	gtk_widget_set_sensitive(GTK_WIDGET(button), TRUE); // Re-enable the button
	
 }

/**
 * @brief This function is the alarm completion callback. 
 * @param source_object The GObject that initiated the task (unused).
 * @param result The GAsyncResult object, which is a GTask in this case.
 * @param user_data pointer to the user data passed to g_task_new (unsued)
 */
 
static void alarm_task_callbk(GObject *gobject,GAsyncResult *result,  gpointer  user_data)
{		
	//the task callbk function is called back when the 
	//play_alarm audio_async function has completed
		
	GTask *task = G_TASK(result);    
    gboolean success = GPOINTER_TO_INT(g_task_get_task_data(task));
    
    if (success) {       
		//g_print("Audio alarm playback finished.\n");
		
    } else {      
		//g_print("Audio alarm playback failed.\n");
    }

}

/**
 * @brief background thread managed by GTask for playing alarm audio
 * @param task The GTask object.
 * @param source_object The GObject that initiated the task (unused).
 * @param task_data A pointer to the AudioTaskData structure.
 * @param cancellable A GCancellable object (unused).
 */

static void play_alarm_audio_async (GTask *task, gpointer object, gpointer task_data, GCancellable *cancellable)
{
	
	play_alarm();	
	g_task_set_task_data(task, GINT_TO_POINTER(TRUE), NULL);
}
  

/**
 * @brief This function plays the alarm audio.
 */
static void play_alarm()
{	
		
	unsigned char *data = (unsigned char*)malloc(alarm_wav_len * sizeof(unsigned char));
	memcpy(data, alarm_wav, alarm_wav_len * sizeof(unsigned char)); //copy  alarm into data	
	unsigned int data_len = alarm_wav_len;	
    char *alarm_file ="/tmp/alarm.wav"; 
	FILE* f = fopen(alarm_file, "w");
    fwrite(data, data_len, 1, f);
    fclose(f);  
    wavplay("/tmp/alarm.wav");
	free(data);		
}

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
	m_talk_event_number=TRUE;
	//alarm
	m_alarm_hour=0;
    m_alarm_min=0;
	m_alarm_on=TRUE;
		
	//calendar
	m_12hour_format=TRUE;
	m_use_end_time=FALSE;
	m_show_tooltips=TRUE;
	m_is_dark_theme=FALSE;		
	m_todaycolour="rgb(141,166,141)"; //sage
	m_eventcolour="rgb(217,230,217)"; //sage light
	m_window_width=800;
	m_window_height=600;
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
		
	//talk preferences
	m_talk = g_key_file_get_boolean(kf, "calendar_settings", "talk", NULL);
	m_talk_event_number=g_key_file_get_boolean(kf, "calendar_settings", "talk_event_number", NULL);
		
	//alarm (save alarm settings so that they are restored)
	m_alarm_hour=g_key_file_get_integer(kf, "calendar_settings", "alarm_hour", NULL);
    m_alarm_min=g_key_file_get_integer(kf, "calendar_settings", "alarm_min", NULL);
    m_am_pm_index=g_key_file_get_integer(kf, "calendar_settings", "am_pm_index", NULL);
	m_alarm_on=g_key_file_get_boolean(kf, "calendar_settings", "alarm_on", NULL);
		
	//listview preferences
	m_12hour_format=g_key_file_get_boolean(kf, "calendar_settings", "hour_format", NULL);	
	m_use_end_time = g_key_file_get_boolean(kf, "calendar_settings", "show_end_time", NULL);
	//calendar preferences
	m_show_tooltips = g_key_file_get_boolean(kf, "calendar_settings", "show_tooltips", NULL);
	m_is_dark_theme =g_key_file_get_boolean(kf, "calendar_settings", "dark_theme", NULL);
		
	// free any previously allocated string before overwriting it.
    g_free(m_todaycolour);
    m_todaycolour = g_key_file_get_string(kf, "calendar_settings", "todaycolour", NULL);

    g_free(m_eventcolour);
    m_eventcolour = g_key_file_get_string(kf, "calendar_settings", "eventcolour", NULL);

    // if the file does not contain a value, g_key_file_get_string returns NULL.
    // so then provide a default value.
    if (!m_todaycolour) {
        m_todaycolour = g_strdup("rgb(221,160,221)");
    }

    if (!m_eventcolour) {
        m_eventcolour = g_strdup("rgb(211,211,211)");
    }
    		
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
	g_key_file_set_boolean(kf, "calendar_settings", "talk_event_number", m_talk_event_number);
		
	//alarm	
	g_key_file_set_integer(kf, "calendar_settings", "alarm_hour", m_alarm_hour);
	g_key_file_set_integer(kf, "calendar_settings", "alarm_min", m_alarm_min);
	g_key_file_set_integer(kf, "calendar_settings", "am_pm_index", m_am_pm_index);
	g_key_file_set_boolean(kf, "calendar_settings", "alarm_on",m_alarm_on);
	
	//listview
	g_key_file_set_boolean(kf, "calendar_settings", "hour_format", m_12hour_format);
	g_key_file_set_boolean(kf, "calendar_settings", "show_end_time", m_use_end_time);
	
	//calendar
	g_key_file_set_boolean(kf, "calendar_settings", "show_tooltips", m_show_tooltips);
	g_key_file_set_boolean(kf, "calendar_settings", "dark_theme", m_is_dark_theme);
	
	g_key_file_set_string(kf, "calendar_settings", "todaycolour", m_todaycolour);
	g_key_file_set_string(kf, "calendar_settings", "eventcolour", m_eventcolour);	
		
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
 * @brief santizes text for insertion into database
 * @param input_text The null-terminated string to sanitize.
 * @return A new, dynamically allocated string with forbidden characters removed,
 *  or NULL if the input is NULL or memory allocation fails.
 */
char* sanitize_text(const char* input_text) 
{
    if (input_text == NULL) {
        return NULL;
    }

    // Allocate memory for the new string. The size will be at most the
    // length of the input string plus one for the null terminator.
    size_t len = strlen(input_text);
    char* sanitized_text = (char*)malloc(len + 1);
    if (sanitized_text == NULL) {
        // Handle memory allocation failure
        perror("Failed to allocate memory");
        return NULL;
    }

    // Iterate through the input string and copy only allowed characters.
    size_t j = 0;
    for (size_t i = 0; i < len; ++i) {
        char c = input_text[i];
        
        // Check if the character is one of the forbidden characters.
        // ispunct() from <ctype.h> checks for all standard punctuation,
        // but we add an explicit check for '&' just in case.
        if (c != ';' && c != ',' && c != '&' && !ispunct(c)) {
            sanitized_text[j++] = c;
        }
    }

    // Null-terminate the new string to make it a valid C string.
    sanitized_text[j] = '\0';

    return sanitized_text;
}


/**
 * @brief Callback function for the "Add Event" button.
 * It retrieves data from dialog widgets, sanitizes it, and inserts a new event into the database.
 * @param button The GtkButton that triggered the callback.
 * @param user_data A pointer to the GListStore.
 */
static void callbk_add_new_event(GtkButton *button, gpointer user_data)
{	
	GListStore *store =user_data;	
	GtkWidget *window = g_object_get_data(G_OBJECT(button), "button-add-window-key");
	GtkWidget *calendar = g_object_get_data(G_OBJECT(button), "button-add-calendar-key");
	
	
	int start_day =GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "day-key"));
	int start_month =GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "month-key"));
	int start_year =GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "year-key"));
	
	int end_day =start_day;
	int end_month =start_month;
	int end_year =start_year;
	
	GtkWidget *dialog = g_object_get_data(G_OBJECT(button), "dialog-key");
	GtkWidget *entry_summary = g_object_get_data(G_OBJECT(button), "entry-summary-key");
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
		
	buffer_summary = gtk_entry_get_buffer(GTK_ENTRY(entry_summary));
	const char* summary = gtk_entry_buffer_get_text(buffer_summary);
	
	// The function returns a pointer to a new string on the heap.
    char* clean_summary = sanitize_text(summary);
		
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
	
	g_object_set(new_event, "summary", g_strdup(clean_summary), NULL);
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
			
	
	 if (clean_summary != NULL) {
       
        // CRUCIAL to free the memory that was allocated by the function
        // to prevent a memory leak.
        free(clean_summary);
        clean_summary = NULL; // Best practice to set the pointer to NULL after freeing.
    }
    
    if (clean_location != NULL) {
       
        // CRUCIAL to free the memory that was allocated by the function
        // to prevent a memory leak.
        free(clean_location);
        clean_location = NULL; // Best practice to set the pointer to NULL after freeing.
    }
    
    if (clean_description != NULL) {
       
        // CRUCIAL to free the memory that was allocated by the function
        // to prevent a memory leak.
        free(clean_description);
        clean_description = NULL; // Best practice to set the pointer to NULL after freeing.
    }
	
		
	set_tooltips_on_calendar(CUSTOM_CALENDAR(calendar));		
	custom_calendar_update (CUSTOM_CALENDAR(calendar));
	update_store(CUSTOM_CALENDAR(calendar), store);		
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
static void callbk_new_event(GSimpleAction *action, GVariant *parameter,  gpointer user_data)
{	
	GListStore *store =user_data;
	GtkWidget *window = g_object_get_data(G_OBJECT(store), "store-window-key");
	GtkWidget *calendar = g_object_get_data(G_OBJECT(store), "store-calendar-key");
	
	int day = custom_calendar_get_day(CUSTOM_CALENDAR(calendar));
	int month = custom_calendar_get_month(CUSTOM_CALENDAR(calendar));
	int year = custom_calendar_get_year(CUSTOM_CALENDAR(calendar));	
	char* day_str = g_strdup_printf("%d",day);
	char* month_str = g_strdup_printf("%d",month);
	char* year_str = g_strdup_printf("%d",year);
	char* date_str="";
	date_str= g_strconcat(date_str, day_str, "-",month_str, "-",year_str, NULL);
		
	
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
			
	//Summary
	label_summary = gtk_label_new("Summary: ");
	entry_summary = gtk_entry_new();
	gtk_entry_set_has_frame(GTK_ENTRY(entry_summary),TRUE); 
	gtk_entry_set_max_length(GTK_ENTRY(entry_summary), 100);
	
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
	
	
	g_object_set_data(G_OBJECT(button_add_event), "day-key",GINT_TO_POINTER(day));
	g_object_set_data(G_OBJECT(button_add_event), "month-key",GINT_TO_POINTER(month));
	g_object_set_data(G_OBJECT(button_add_event), "year-key",GINT_TO_POINTER(year));
	
	g_object_set_data(G_OBJECT(button_add_event), "dialog-key",dialog);
	g_object_set_data(G_OBJECT(button_add_event), "window-key",window);
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
	
	CalendarEvent *selectedevent =user_data; //user_data is selectedevent (not store)
	
	GtkWidget *dialog = g_object_get_data(G_OBJECT(button), "dialog-key");
	GtkWidget *window = g_object_get_data(G_OBJECT(button), "window-key");
	GtkWidget *calendar = g_object_get_data(G_OBJECT(button), "calendar-key");
	GListStore *store =g_object_get_data(G_OBJECT(button), "store-key");
	
	
	int start_day =GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "day-key"));
	int start_month =GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "month-key"));
	int start_year =GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "year-key"));
	
	//multiday not currently supported
	int end_day=start_day;
	int end_month=start_month;
	int end_year=start_year;
			
	GtkWidget *entry_summary = g_object_get_data(G_OBJECT(button), "entry-summary-key");
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
			
	buffer_summary = gtk_entry_get_buffer(GTK_ENTRY(entry_summary));
	const char* summary = gtk_entry_buffer_get_text(buffer_summary);
	char* clean_summary = sanitize_text(summary);
	
	
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
    calendar_event_set_summary(selectedevent, g_strdup(clean_summary));
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
    
     if (clean_summary != NULL) {
       
        // CRUCIAL to free the memory that was allocated by the function
        // to prevent a memory leak.
        free(clean_summary);
        clean_summary = NULL; // Best practice to set the pointer to NULL after freeing.
    }
    
    if (clean_location != NULL) {
       
        // CRUCIAL to free the memory that was allocated by the function
        // to prevent a memory leak.
        free(clean_location);
        clean_location = NULL; // Best practice to set the pointer to NULL after freeing.
    }
    
    if (clean_description != NULL) {
       
        // CRUCIAL to free the memory that was allocated by the function
        // to prevent a memory leak.
        free(clean_description);
        clean_description = NULL; // Best practice to set the pointer to NULL after freeing.
    }
	
	set_tooltips_on_calendar(CUSTOM_CALENDAR(calendar));
	custom_calendar_update (CUSTOM_CALENDAR(calendar));
	update_store(CUSTOM_CALENDAR(calendar), store);		
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
static void callbk_edit_event(GSimpleAction *action, GVariant *parameter,  gpointer user_data)
{	
	
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
	GtkWidget *entry_summary;	
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
	entry_summary = gtk_entry_new();
	gtk_entry_set_has_frame(GTK_ENTRY(entry_summary),TRUE); 
	gtk_entry_set_max_length(GTK_ENTRY(entry_summary), 100);
	buffer_summary = gtk_entry_buffer_new(summary, -1); // show  event summary
    gtk_entry_set_buffer(GTK_ENTRY(entry_summary), buffer_summary);
	
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
	
	//g_object_set_data(G_OBJECT(button_update), "id-key",GINT_TO_POINTER(id_key));
	g_object_set_data(G_OBJECT(button_update), "day-key",GINT_TO_POINTER(start_day));
	g_object_set_data(G_OBJECT(button_update), "month-key",GINT_TO_POINTER(start_month));
	g_object_set_data(G_OBJECT(button_update), "year-key",GINT_TO_POINTER(start_year));
	
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
        g_print("No event selected.\n");
        return;
    }
    
    //GtkWidget *window = g_object_get_data(G_OBJECT(selection), "selection-window-key");
	GtkWidget *calendar = g_object_get_data(G_OBJECT(selection), "selection-calendar-key");;

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

/**
 * @brief button callbk function to set the alarm values
 * @param button The GtkButton that triggered the callback. 
 * @param user_data is the alarm status label 
 */
static void callbk_set_alarm(GtkButton *button, gpointer user_data)
{	
	m_alarm_on=TRUE;	
	GtkWidget *label_alarm_status=user_data;
	
	GtkWidget *spin_button_alarm_hour = g_object_get_data(G_OBJECT(button), "spin-alarm-hour-key");
	GtkWidget *spin_button_alarm_min = g_object_get_data(G_OBJECT(button), "spin-alarm-min-key");
		
	m_alarm_hour= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_alarm_hour));
	m_alarm_min= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_alarm_min));
	
	char *alarm_str ="Alarm On ";	
	char* hour_str = g_strdup_printf("%02d",m_alarm_hour);
	char* min_str = g_strdup_printf("%02d",m_alarm_min);
	alarm_str = g_strconcat(alarm_str,hour_str,":",min_str,NULL);		
	gtk_label_set_text(GTK_LABEL(label_alarm_status), alarm_str);
	
	//g_print("Alarm set for %02d:%02d.\n", m_alarm_hour, m_alarm_min);
	config_write();	//save alarm values
	
	g_free(alarm_str);
}

/**
 * @brief button callbk function to reset the alarm 
 * @param button The GtkButton that triggered the callback. 
 * @param user_data is the alarm status label 
 */
static void callbk_cancel_alarm(GtkButton *button, gpointer user_data)
{	
	m_alarm_on=FALSE;	
	GtkWidget *label_alarm_status=user_data;
	gtk_label_set_text(GTK_LABEL(label_alarm_status), "Alarm Off");
	m_alarm_hour=0;
	m_alarm_min=0;
	m_am_pm_index=0;
	//g_print("Alarm set for %02d:%02d.\n", m_alarm_hour, m_alarm_min);
	config_write();	//save alarm values
}

/**
 * @brief button callbk function to set up the alarm UI
 * @param button The GtkButton that triggered the callback. 
 * @param user_data (unused)
 */
static void callbk_alarm_button(GtkButton *button, gpointer user_data)
{
	GtkWidget *window =user_data;
	GtkWidget *alarm_window;
	alarm_window = gtk_window_new(); 
	gtk_window_set_title(GTK_WINDOW(alarm_window), "Set Alarm");
	gtk_window_set_default_size (GTK_WINDOW (alarm_window),400, 150);
	gtk_window_set_transient_for(GTK_WINDOW(alarm_window), GTK_WINDOW(window));
  	gtk_window_set_modal(GTK_WINDOW(alarm_window), TRUE);
  	 
	GtkWidget *label_alarm_status = gtk_label_new("");
		
	if(m_alarm_on){		
		char *alarm_str ="Alarm On ";	
	    char* hour_str = g_strdup_printf("%02d",m_alarm_hour);
	    char* min_str = g_strdup_printf("%02d",m_alarm_min);
	    alarm_str = g_strconcat(alarm_str,hour_str,":",min_str,NULL);		
		gtk_label_set_text(GTK_LABEL(label_alarm_status), alarm_str);
		g_free(hour_str);
		g_free(min_str);
		g_free(alarm_str);
	}
	else{
		gtk_label_set_text(GTK_LABEL(label_alarm_status), "Alarm Off");
	}		
    // Alarm Time Selection
	GtkWidget *hbox_alarm = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_box_append(GTK_BOX(hbox_alarm), gtk_label_new("Set Alarm:"));
	//GtkWidget *spin_button_alarm_hour = gtk_spin_button_new_with_range(1, 12, 1);//12 hour
	GtkWidget *spin_button_alarm_hour = gtk_spin_button_new_with_range(0, 23, 1);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_alarm_hour), m_alarm_hour);
	gtk_box_append(GTK_BOX(hbox_alarm), spin_button_alarm_hour);
	gtk_box_append(GTK_BOX(hbox_alarm), gtk_label_new(":"));
	GtkWidget *spin_button_alarm_min = gtk_spin_button_new_with_range(0, 59, 1);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_alarm_min), m_alarm_min);	
	gtk_box_append(GTK_BOX(hbox_alarm), spin_button_alarm_min);
	
	GtkWidget *vbox_buttons = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	
	//// Set and Cancel Buttons
	GtkWidget *set_alarm_button = gtk_button_new_with_label("Set Alarm");
	g_signal_connect(set_alarm_button, "clicked", G_CALLBACK(callbk_set_alarm), label_alarm_status);
	gtk_box_append(GTK_BOX(vbox_buttons), set_alarm_button);
		
	g_object_set_data(G_OBJECT(set_alarm_button), "spin-alarm-hour-key", spin_button_alarm_hour);
	g_object_set_data(G_OBJECT(set_alarm_button), "spin-alarm-min-key", spin_button_alarm_min);	
	
	GtkWidget *cancel_button = gtk_button_new_with_label("Cancel Alarm");
	g_signal_connect(cancel_button, "clicked", G_CALLBACK(callbk_cancel_alarm), label_alarm_status);
	gtk_box_append(GTK_BOX(vbox_buttons), cancel_button);
	
	gtk_box_append(GTK_BOX(vbox_buttons), label_alarm_status);

	GtkWidget *vbox_layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_box_append(GTK_BOX(vbox_layout), hbox_alarm);
	gtk_box_append(GTK_BOX(vbox_layout), vbox_buttons);
	
	gtk_window_set_child (GTK_WINDOW (alarm_window), vbox_layout);		
		
	gtk_window_present(GTK_WINDOW (alarm_window));
}

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
	
	//GtkWidget *window = g_object_get_data(G_OBJECT(dialog), "dialog-window-key");
	
	GFile *file;
	file = gtk_file_dialog_save_finish (dialog, result, NULL);
	if (file)
	{	 
	char *file_name = g_file_get_path(file);	  
	export_file(file_name);
	}
}
//======================================================================

/**
 * @brief Exports all calendar events to an iCal file.
 * * @param file_name The path to the file to export to.
 */
void export_file(char *file_name) 
{
	GFile *file;	
	GFileOutputStream *file_stream;
	GDataOutputStream *data_stream;
	GError *err = NULL;
	
	file = g_file_new_for_path(file_name);
	
	file_stream = g_file_replace(file, 0,TRUE, G_FILE_CREATE_NONE, NULL, &err);
	
	if (file_stream == NULL) {		
	g_warning ("Error message = %s", err->message);
	g_error_free (err);
	g_print("Unable to open file: %s\n",file_name);
	g_object_unref (file);
	return;
	}

	data_stream = g_data_output_stream_new(G_OUTPUT_STREAM(file_stream));
	
    GArray* all_events = db_get_all_events(db_handle);
    
    if (all_events) {
		
		char *line = "";
	    line = g_strconcat(line,"BEGIN:VCALENDAR\n",NULL);	
	    g_data_output_stream_put_string(data_stream, line, NULL, NULL);
        
        
        //for all events
        for (guint i = 0; i < all_events->len; ++i) 
        {
		CalendarEvent* event = g_array_index(all_events, CalendarEvent*, i);
				
		line="";
		gint event_id = 0;
		gchar *summary_str = "";
		gchar *location_str = "";
		gchar *description_str = "";
		
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
		//gint is_multiday = 0;
		gint is_priority = 0;
		
		//gint has_reminder = 0;
		//gint reminder_hour = 0;
		//gint reminder_min = 0;
		char* recurrence_str="RRULE:";
				
		g_object_get(event, "eventid", &event_id, NULL);
		g_object_get(event, "summary", &summary_str, NULL);
		g_object_get(event, "location", &location_str, NULL);
		g_object_get(event, "description", &description_str, NULL);
		g_object_get(event, "startyear", &start_year, NULL);
		g_object_get(event, "startmonth", &start_month, NULL);
		g_object_get(event, "startday", &start_day, NULL);
		g_object_get(event, "starthour", &start_hour, NULL);
		g_object_get(event, "startmin", &start_min, NULL);
		g_object_get(event, "endyear", &end_year, NULL);
		g_object_get(event, "endmonth", &end_month, NULL);
		g_object_get(event, "endday", &end_day, NULL);
		g_object_get(event, "endhour", &end_hour, NULL);
		g_object_get(event, "endmin", &end_min, NULL);
		g_object_get(event, "isyearly", &is_yearly, NULL);
		g_object_get(event, "isallday", &is_allday, NULL);		
		g_object_get(event, "ispriority", &is_priority, NULL);
		
		
		char* start_day_str = g_strdup_printf("%02d",start_day);
		char* start_month_str = g_strdup_printf("%02d",start_month);
		char* start_year_str = g_strdup_printf("%d",start_year);
		char* start_hour_str = g_strdup_printf("%02d",start_hour);
		char* start_min_str = g_strdup_printf("%02d",start_min);
		char* start_sec_str = g_strdup_printf("%02d",start_seconds);
		
		char* end_day_str = g_strdup_printf("%02d",end_day);
		char* end_month_str = g_strdup_printf("%02d",end_month);
		char* end_year_str = g_strdup_printf("%d",end_year);
		char* end_hour_str = g_strdup_printf("%02d",end_hour);
		char* end_min_str = g_strdup_printf("%02d",end_min);
		char* end_sec_str = g_strdup_printf("%02d",end_seconds);
		
		char* priority_str="";
		if (is_priority ==1) priority_str="PRIORITY:1";
		else priority_str="PRIORITY:0";
		
		//recurrence rule (more todo)
		
		if(is_yearly)
		{					
		recurrence_str = g_strconcat(recurrence_str,
		"FREQ=YEARLY;",
		"INTERVAL=1;",
		"BYMONTH=",
		start_month_str,
		";",
		"BYMONTHDAY=",
		start_day_str,	   
		NULL);			  
		}
		
		char *dts ="DTSTART:";		
		dts = g_strconcat(dts,
		start_year_str,
		start_month_str,
		start_day_str,
		"T",
		start_hour_str,
		start_min_str,
		start_sec_str,
		"\n",
		NULL);
		
		char *dte ="DTEND:";		
		dte = g_strconcat(dte,
		end_year_str,
		end_month_str,
		end_day_str,
		"T",
		end_hour_str,
		end_min_str,
		end_sec_str,
		"\n",
		NULL);
		
		line = g_strconcat(line,"BEGIN:VEVENT\n",NULL);		
		line = g_strconcat(line,dts,NULL);
		line = g_strconcat(line,dte,NULL);
		line = g_strconcat(line,"LOCATION:",location_str, "\n", NULL);
		line = g_strconcat(line,"SUMMARY:",summary_str,"\n", NULL);
		line = g_strconcat(line,"DESCRIPTION:",description_str,"\n", NULL);
		
		line = g_strconcat(line,priority_str,"\n", NULL);
		
		if(is_yearly)
		{
		
		line = g_strconcat(line,recurrence_str,"\n", NULL);
		is_yearly=0; //prevent next line repeats
		}
		
		line = g_strconcat(line,"END:VEVENT\n",NULL);		
		g_data_output_stream_put_string(data_stream, line, NULL, NULL);
				
		
		g_object_unref(event);
        } //for all events
        
        line ="";
	    line = g_strconcat(line,"END:VCALENDAR\n",NULL);
	    g_data_output_stream_put_string(data_stream, line, NULL, NULL);
        
        g_array_unref(all_events);
		
		} else 
		{
        g_warning("Failed to retrieve events or no events found.");
		
		}
		
	g_object_unref(data_stream);
	g_object_unref(file_stream);
	g_object_unref(file);
		
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

/**
 * @brief Imports events from an iCal file.
 * @param gpointer to GtkWindow to get data
 */
void import_ical_file(gpointer user_data) 
{
	GtkWidget *window = user_data; //need window to get calendar
	GtkWidget *calendar = g_object_get_data(G_OBJECT(window), "window-calendar-key");
	GListStore *store =g_object_get_data(G_OBJECT(window), "window-store-key");
	//Two stage parser
	//Stage 1 checks for timezone
	//Stage2 extracts event details
	
	
	GFile *file;
	//GFileInputStream creates a stream of input that you can use to read data from a file
	GFileInputStream *file_stream = NULL;
	GDataInputStream *input_stream = NULL;	
	file = g_file_new_for_path(m_file_name);
	
	file_stream = g_file_read(file, NULL, NULL);
	if (!file_stream)
	{
	g_print("CRITICAL: error: unable to open backup file called example.ics\n");	
	return;
	}
	else {
	//g_print("successfully opened: %s\n", file_name);
	}
	
	input_stream = g_data_input_stream_new(G_INPUT_STREAM(file_stream));
	
	char *key="";     
	char *value="";
	
	char *summary_str = "";
	//char *event_number_str="";
	char *location_str = "";
	char *description_str = "";
	
	int start_day=0;
	int start_month=0;
	int start_year=0;
	
	int end_day=0;
	int end_month=0;
	int end_year=0;
	
	int start_hour = 0;
	int start_min = 0;
	
	int end_hour = 0;
	int end_min = 0;
	
	int is_allday = 0;		
	int is_priority = 0;
	int is_yearly=0;
	
	
	gboolean is_timezone=0;
	char *timezone_str="";
	
	//Stage1: scan for timezone
	
	gchar *line1=""; //parser1
	
	while ((line1 = g_data_input_stream_read_line (input_stream, NULL, NULL, NULL))) {
	
	g_strstrip (line1);			
	
	gchar** tokens = g_strsplit (line1, ":", -1);
	key =tokens[0];
	value =tokens[1];
	
	if ((strcmp (key,"BEGIN") == 0) && (strcmp (value,"VTIMEZONE") == 0)) //check for timezone
	{
	is_timezone=1;
	}
	if (g_strcmp0 (key,"TZID") == 0)
	{				
	timezone_str=g_strdup(value);
	}
	
	g_free(line1);	
	}//while timezone check
	
	//Stage 2: extract event details
	if(is_timezone) //ical file has timezone
	{		
	//parse ical file which has a time zone
	char* dtstart_key ="DTSTART;";
	dtstart_key=g_strconcat(dtstart_key,"TZID=",timezone_str,NULL);
	char* dtend_key="DTEND;";
	dtend_key=g_strconcat(dtend_key,"TZID=",timezone_str,NULL);
	
	
	//reload file stream (stage 2 parse)
	file_stream = g_file_read(file, NULL, NULL);		
	input_stream = g_data_input_stream_new(G_INPUT_STREAM(file_stream));
	
	char* line2=""; //parser2
	while ((line2 = g_data_input_stream_read_line (input_stream, NULL, NULL, NULL))) {
	
	g_strstrip (line2);			
	gchar** tokens = g_strsplit (line2, ":", -1);
	key =tokens[0];
	value =tokens[1];			
	
	if (g_strcmp0 (key,dtstart_key) == 0)  //date time start
	{	
	const char* start_date_str =g_strdup(value);				
	char* start_year_substring="";
	char* start_month_substring="";
	char* start_day_substring="";
	char* start_hour_str="";
	char* start_min_str="";
	
	start_year_substring = g_utf8_substring (start_date_str,0,4);
	start_month_substring = g_utf8_substring (start_date_str,4,6);
	start_day_substring = g_utf8_substring (start_date_str,6,8);
	
	start_hour_str = g_utf8_substring (start_date_str,9,11);
	start_min_str = g_utf8_substring (start_date_str,11,13);
	
	start_month_substring =ignore_first_zero(start_month_substring);
	start_day_substring =ignore_first_zero(start_day_substring);				
	start_hour_str =ignore_first_zero(start_hour_str);
	start_min_str =ignore_first_zero(start_min_str);
	
	if (strcmp (start_hour_str,"") == 0) start_hour_str ="0";
	if (strcmp (start_min_str,"") == 0) start_min_str ="0";
	
	//convert str to int using str-to-long-int
	start_year=g_ascii_strtoll(start_year_substring, NULL, 0);
	start_month=g_ascii_strtoll(start_month_substring, NULL, 0);
	start_day=g_ascii_strtoll(start_day_substring, NULL, 0);
	
	start_hour=g_ascii_strtoll(start_hour_str, NULL, 0);
	start_min=g_ascii_strtoll(start_min_str, NULL, 0);	
	
	} //if dtstart
	
	if (g_strcmp0 (key,dtend_key) == 0)  //date time end
	{	
	const char* end_date_str =g_strdup(value);				
	char* end_year_substring="";
	char* end_month_substring="";
	char* end_day_substring="";
	char* end_hour_str="";
	char* end_min_str="";
	
	end_year_substring = g_utf8_substring (end_date_str,0,4);
	end_month_substring = g_utf8_substring (end_date_str,4,6);
	end_day_substring = g_utf8_substring (end_date_str,6,8);
	
	end_hour_str = g_utf8_substring (end_date_str,9,11);
	end_min_str = g_utf8_substring (end_date_str,11,13);
	
	end_month_substring =ignore_first_zero(end_month_substring);
	end_day_substring =ignore_first_zero(end_day_substring);				
	end_hour_str =ignore_first_zero(end_hour_str);
	end_min_str =ignore_first_zero(end_min_str);
	
	if (strcmp (end_hour_str,"") == 0) end_hour_str ="0";
	if (strcmp (end_min_str,"") == 0) end_min_str ="0";
	
	//convert str to int using str-to-long-int
	end_year=g_ascii_strtoll(end_year_substring, NULL, 0);
	end_month=g_ascii_strtoll(end_month_substring, NULL, 0);
	end_day=g_ascii_strtoll(end_day_substring, NULL, 0);
	
	end_hour=g_ascii_strtoll(end_hour_str, NULL, 0);
	end_min=g_ascii_strtoll(end_min_str, NULL, 0);	
	
	} //if dtend	
	
	if (g_strcmp0 (key,"SUMMARY") == 0)
	{				
	summary_str=g_strdup(value);
	
	}
	if (g_strcmp0 (key,"LOCATION") == 0)
	{				
	location_str=g_strdup(value);
	
	}
	if (g_strcmp0 (key,"DESCRIPTION") == 0)
	{				
	description_str=g_strdup(value);
	
	}
	
	if (strcmp (key,"PRIORITY") == 0)
	{
	const char* priority_str =g_strdup(value);
	int p_num=g_ascii_strtoll(priority_str, NULL, 0);
	if (p_num >0) is_priority=1;
	else is_priority=0;			  
	}
	
	
	if (strcmp (key,"RRULE") == 0)
	{
	const char* rule_str =g_strdup(value);			   			    
	//YEARLY is the only RRULE recurring event currently supported
	//More work needed here.			    
	if (g_strrstr(rule_str,"FREQ=YEARLY") != NULL)
	{
	is_yearly=1;
	}			   
	}
	
	////event ends and so insert into db	        
	if ((strcmp (key,"END") == 0) && (strcmp (value,"VEVENT") == 0)) //VEVENT ends
	{
	
	//is_allday=0;
	//if((start_hour==0) 
	//&& (start_min==0)
	//&& (end_hour==0)
	//&&(end_min==0))
	//{
	//is_allday=1;
	//}	
	
	is_allday=1;
	if((start_hour!=0) && (start_min!=0))				
	{
	is_allday=0;
	}				
	//VALARM to do
	
	CalendarEvent *evt = g_object_new(CALENDAR_TYPE_EVENT, 0);
	
	g_object_set(evt, "summary", g_strdup(summary_str), NULL);
	g_object_set(evt, "location", g_strdup(location_str), NULL);
	g_object_set(evt, "description", g_strdup(description_str), NULL);
	g_object_set(evt, "startyear", start_year, NULL);
	g_object_set(evt, "startmonth", start_month, NULL);
	g_object_set(evt, "startday", start_day, NULL);
	g_object_set(evt, "starthour", start_hour, NULL);
	g_object_set(evt, "startmin", start_min, NULL);
	g_object_set(evt, "endyear", end_year, NULL); // to do
	g_object_set(evt, "endmonth", end_month, NULL);
	g_object_set(evt, "endday", end_day, NULL);
	g_object_set(evt, "endhour", end_hour, NULL);
	g_object_set(evt, "endmin", end_min, NULL);
	g_object_set(evt, "isyearly", is_yearly, NULL);
	g_object_set(evt, "isallday", is_allday, NULL);			
	g_object_set(evt, "ispriority", is_priority, NULL);
	
	//db_insert_event(evt); //insert event into database	
	
	//insert event into database
	int new_id = db_insert_event(db_handle, evt);
    if (new_id != -1) {
        //g_print("Successfully appended new event with ID: %d\n", new_id);
    } else {
        g_warning("Failed to append new event.\n");
    }	
	
	
	//reset is_yearly for next event
	is_allday=0;
	is_yearly=0;
	is_priority=0;	
	}	//VEVENT END	
	
	g_free(line2);
	} //while parse loop
	
	//g_free
	g_free(dtstart_key);
	g_free(dtend_key);
	
	} //if timezone
	
	else { //no timezone
	
	file_stream = g_file_read(file, NULL, NULL);		
	input_stream = g_data_input_stream_new(G_INPUT_STREAM(file_stream));
	
	char* line2="";
	while ((line2 = g_data_input_stream_read_line (input_stream, NULL, NULL, NULL))) {
	
	
	g_strstrip (line2);	
	
	gchar** tokens = g_strsplit (line2, ":", -1);
	key =tokens[0];
	value =tokens[1];
	
	if (g_strcmp0 (key,"DTSTART") == 0) //date time start version 1 style
	{
	
	//no timezone
	const char* start_date_str =g_strdup(value);				
	char* start_year_substring="";
	char* start_month_substring="";
	char* start_day_substring="";
	char* start_hour_str="";
	char* start_min_str="";
	
	start_year_substring = g_utf8_substring (start_date_str,0,4);
	start_month_substring = g_utf8_substring (start_date_str,4,6);
	start_day_substring = g_utf8_substring (start_date_str,6,8);
	
	start_hour_str = g_utf8_substring (start_date_str,9,11);
	start_min_str = g_utf8_substring (start_date_str,11,13);
	
	start_month_substring =ignore_first_zero(start_month_substring);
	start_day_substring =ignore_first_zero(start_day_substring);				
	start_hour_str =ignore_first_zero(start_hour_str);
	start_min_str =ignore_first_zero(start_min_str);
	
	if (strcmp (start_hour_str,"") == 0) start_hour_str ="0";
	if (strcmp (start_min_str,"") == 0) start_min_str ="0";
	
	//convert str to int using str-to-long-int
	start_year=g_ascii_strtoll(start_year_substring, NULL, 0);
	start_month=g_ascii_strtoll(start_month_substring, NULL, 0);
	start_day=g_ascii_strtoll(start_day_substring, NULL, 0);
	
	start_hour=g_ascii_strtoll(start_hour_str, NULL, 0);
	start_min=g_ascii_strtoll(start_min_str, NULL, 0);	
	}	
	
	if (g_strcmp0 (key,"DTEND") == 0) //date time end
	{
	//no timezone
	const char* end_date_str =g_strdup(value);				
	char* end_year_substring="";
	char* end_month_substring="";
	char* end_day_substring="";
	char* end_hour_str="";
	char* end_min_str="";
	
	end_year_substring = g_utf8_substring (end_date_str,0,4);
	end_month_substring = g_utf8_substring (end_date_str,4,6);
	end_day_substring = g_utf8_substring (end_date_str,6,8);
	
	end_hour_str = g_utf8_substring (end_date_str,9,11);
	end_min_str = g_utf8_substring (end_date_str,11,13);
	
	end_month_substring =ignore_first_zero(end_month_substring);
	end_day_substring =ignore_first_zero(end_day_substring);				
	end_hour_str =ignore_first_zero(end_hour_str);
	end_min_str =ignore_first_zero(end_min_str);
	
	if (strcmp (end_hour_str,"") == 0) end_hour_str ="0";
	if (strcmp (end_min_str,"") == 0) end_min_str ="0";
	
	//convert str to int using str-to-long-int
	end_year=g_ascii_strtoll(end_year_substring, NULL, 0);
	end_month=g_ascii_strtoll(end_month_substring, NULL, 0);
	end_day=g_ascii_strtoll(end_day_substring, NULL, 0);				
	end_hour=g_ascii_strtoll(end_hour_str, NULL, 0);
	end_min=g_ascii_strtoll(end_min_str, NULL, 0);
	}
	
	if (g_strcmp0 (key,"SUMMARY") == 0)
	{				
	summary_str=g_strdup(value);
	}
	if (g_strcmp0 (key,"LOCATION") == 0)
	{				
	location_str=g_strdup(value);
	}
	if (g_strcmp0 (key,"DESCRIPTION") == 0)
	{				
	description_str=g_strdup(value);
	}
	
	if (strcmp (key,"PRIORITY") == 0)
	{
	const char* priority_str =g_strdup(value);
	int p_num=g_ascii_strtoll(priority_str, NULL, 0);
	if (p_num >0) is_priority=1;
	else is_priority=0;			  
	}
	
	
	if (strcmp (key,"RRULE") == 0)
	{
	const char* rule_str =g_strdup(value);			   			    
	//YEARLY is the only RRULE recurring event currently supported
	//More work needed here.			    
	if (g_strrstr(rule_str,"FREQ=YEARLY") != NULL)
	{
	is_yearly=1;
	}			   
	}
	
	//event ends and so insert into db	        
	if ((strcmp (key,"END") == 0) && (strcmp (value,"VEVENT") == 0)) //VEVENT ends
	{
	
	//is_allday=0;
	//if((start_hour==0) 
	//&& (start_min==0)
	//&& (end_hour==0)
	//&&(end_min==0))
	//{
	//is_allday=1;
	//}
	
	is_allday=1;
	if((start_hour!=0) && (start_min!=0))				
	{
	is_allday=0;
	}	
	
	//VALARM to do
	
	CalendarEvent *evt = g_object_new(CALENDAR_TYPE_EVENT, 0);
	
	g_object_set(evt, "summary", g_strdup(summary_str), NULL);
	g_object_set(evt, "location", g_strdup(location_str), NULL);
	g_object_set(evt, "description", g_strdup(description_str), NULL);
	g_object_set(evt, "startyear", start_year, NULL);
	g_object_set(evt, "startmonth", start_month, NULL);
	g_object_set(evt, "startday", start_day, NULL);
	g_object_set(evt, "starthour", start_hour, NULL);
	g_object_set(evt, "startmin", start_min, NULL);
	g_object_set(evt, "endyear", end_year, NULL); // to do
	g_object_set(evt, "endmonth", end_month, NULL);
	g_object_set(evt, "endday", end_day, NULL);
	g_object_set(evt, "endhour", end_hour, NULL);
	g_object_set(evt, "endmin", end_min, NULL);
	g_object_set(evt, "isyearly", is_yearly, NULL);
	g_object_set(evt, "isallday", is_allday, NULL);			
	g_object_set(evt, "ispriority", is_priority, NULL);			
	
	//db_insert_event(evt); //insert event into database
	
	//insert event into database
	int new_id = db_insert_event(db_handle, evt);
    if (new_id != -1) {
        //g_print("Successfully appended new event with ID: %d\n", new_id);
    } else {
        g_warning("Failed to append new event.\n");
    }	
	
	//reset is_yearly for next event
	is_yearly=0;
	is_priority=0;
	is_allday=0;			
	
	}	//VEVENT END	
	
	g_free(line2);
	
	} //while parse
	
	} //else no timezone

	//call calendar home
	
	set_tooltips_on_calendar(CUSTOM_CALENDAR(calendar));
	//set_tooltips_on_calendar(CUSTOM_CALENDAR(calendar));	
	custom_calendar_update (CUSTOM_CALENDAR(calendar));
	custom_calendar_goto_today(CUSTOM_CALENDAR(calendar));
	update_store(CUSTOM_CALENDAR(calendar), store);
	
	int day = custom_calendar_get_day(CUSTOM_CALENDAR(calendar));
    int month = custom_calendar_get_month(CUSTOM_CALENDAR(calendar));
    int year = custom_calendar_get_year(CUSTOM_CALENDAR(calendar));	
	
	g_object_unref(file);   	
	g_object_unref (input_stream);
	g_object_unref (file_stream);
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
	//GListStore *store = g_object_get_data(G_OBJECT(window), "window-store-key");
	
	GFile *file;
	
	file = gtk_file_dialog_open_finish (dialog, result, NULL);
	if (file)
	{     
	//char* file_name = g_file_get_path(file);
	//import_ical_file(file_name, window);	
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
	GtkWindow *window =user_data;	
	GtkWidget *calendar =g_object_get_data(G_OBJECT(window), "window-calendar-key");
	GListStore *store =g_object_get_data(G_OBJECT(window), "window-store-key");
	
	custom_calendar_goto_today(CUSTOM_CALENDAR(calendar));
	
	int day = custom_calendar_get_day(CUSTOM_CALENDAR(calendar));
	int month = custom_calendar_get_month(CUSTOM_CALENDAR(calendar));
	int year = custom_calendar_get_year(CUSTOM_CALENDAR(calendar));	
	//mark up calendar
	set_tooltips_on_calendar(CUSTOM_CALENDAR(calendar));
	custom_calendar_update(CUSTOM_CALENDAR(calendar));
	update_store(CUSTOM_CALENDAR(calendar), store);
}

/**
 * @brief Callback for when a day is selected on the calendar.
 * @param calendar The CustomCalendar widget.
 * @param user_data A pointer to the GListStore.
 */
static void callbk_calendar_day_selected(CustomCalendar *calendar, gpointer user_data)
{	
	GListStore *store =user_data;	
	set_tooltips_on_calendar(CUSTOM_CALENDAR(calendar));		
	custom_calendar_update (CUSTOM_CALENDAR(calendar));
	update_store(CUSTOM_CALENDAR(calendar), store);	
}

/**
 * @brief Callback to navigate to the next month on the calendar.
 * @param calendar The CustomCalendar widget.
 * @param user_data A pointer to window to get the GListStore.
 */
static void callbk_calendar_next_month(CustomCalendar *calendar, gpointer user_data) 
{	
	GtkWidget *window=user_data;
	GListStore *store =g_object_get_data(G_OBJECT(window), "window-store-key");
	set_tooltips_on_calendar(CUSTOM_CALENDAR(calendar));		
	custom_calendar_update (CUSTOM_CALENDAR(calendar));
	update_store(CUSTOM_CALENDAR(calendar), store);
}

/**
 * @brief Callback to navigate to the previous month on the calendar.
 * @param calendar The CustomCalendar widget.
 * @param user_data A pointer to window to get the GListStore.
 */
static void callbk_calendar_prev_month(CustomCalendar *calendar, gpointer user_data) 
{	
	GtkWidget *window=user_data;
	GListStore *store =g_object_get_data(G_OBJECT(window), "window-store-key");
	set_tooltips_on_calendar(CUSTOM_CALENDAR(calendar));
	custom_calendar_update (CUSTOM_CALENDAR(calendar));
	update_store(CUSTOM_CALENDAR(calendar), store);

}

/**
 * @brief Callback to navigate to the next year on the calendar.
 * @param calendar The CustomCalendar widget.
 * @param user_data A pointer to window to get the GListStore.
 */
static void callbk_calendar_next_year(CustomCalendar *calendar, gpointer user_data) 
{
	GtkWidget *window=user_data;
	GListStore *store =g_object_get_data(G_OBJECT(window), "window-store-key");
	set_tooltips_on_calendar(CUSTOM_CALENDAR(calendar));		
	custom_calendar_update (CUSTOM_CALENDAR(calendar));
	update_store(CUSTOM_CALENDAR(calendar), store);
}

/**
 * @brief Callback to navigate to the previous year on the calendar.
 * @param calendar The CustomCalendar widget.
 * @param user_data A pointer to window to get the GListStore.
 */
static void callbk_calendar_prev_year(CustomCalendar *calendar, gpointer user_data) 
{
	GtkWidget *window=user_data;
	GListStore *store =g_object_get_data(G_OBJECT(window), "window-store-key");
	set_tooltips_on_calendar(CUSTOM_CALENDAR(calendar));
	custom_calendar_update (CUSTOM_CALENDAR(calendar));
	update_store(CUSTOM_CALENDAR(calendar), store);		
}

/**
 * @brief Sets tooltips and marks on the calendar for days with events.
 * @param calendar The CustomCalendar widget.
 */
static void set_tooltips_on_calendar(CustomCalendar *calendar) 
{	
	custom_calendar_initialise_tooltip_array(calendar);	
	custom_calendar_reset_marks(CUSTOM_CALENDAR(calendar));	
	
	int selected_day = custom_calendar_get_day(CUSTOM_CALENDAR(calendar));
	int selected_month = custom_calendar_get_month(CUSTOM_CALENDAR(calendar));
	int selected_year = custom_calendar_get_year(CUSTOM_CALENDAR(calendar));
	
	guint8 month_days =g_date_get_days_in_month(selected_month,selected_year);	
		
	//cycle through month days and display any events
	for (int day=1; day<=month_days; day++)
	{
		
	//get all events for selected day
	GArray* events_for_day = db_get_all_events_year_month_day(db_handle, selected_year, selected_month, day);
    
    if (events_for_day) {      
        for (guint i = 0; i < events_for_day->len; i++) {
        CalendarEvent* day_event = g_array_index(events_for_day, CalendarEvent*, i);
        int start_day=0;
        int start_month=0;
        int start_year=0;
        char* summary_str="";
        char* summary_str12="";	
        char *location_str="";
        char *description_str="";	
        int start_hour=0;
        int start_min=0;	
        int end_hour=0;
        int end_min=0;
        int is_yearly=0;
        int is_allday=0;
        int is_priority=0;
        
        g_object_get (day_event, "startday", &start_day, NULL);
        g_object_get (day_event, "startmonth", &start_month, NULL);
        g_object_get (day_event, "startyear", &start_year, NULL);	
        g_object_get(day_event, "summary", &summary_str, NULL);	
        g_object_get(day_event, "location", &location_str, NULL);
        g_object_get(day_event, "description", &description_str, NULL);	
        g_object_get(day_event, "starthour", &start_hour, NULL);
        g_object_get(day_event, "startmin", &start_min, NULL);	
        g_object_get(day_event, "endhour", &end_hour, NULL);
        g_object_get(day_event, "endmin", &end_min, NULL);
        g_object_get(day_event, "isyearly", &is_yearly, NULL);
        g_object_get(day_event, "isallday", &is_allday, NULL);
        g_object_get(day_event, "ispriority", &is_priority, NULL);
        
        char *display_str="";
        char *tooltip_str="";
        char *des_loc_str="";
        char *time_str = "";
        char *starthour_str = "";
        char *startmin_str = "";
        char *endhour_str = "";
        char *endmin_str = "";
        char *ampm_str = " ";
        
        if(!is_allday)
        {		
        //calendar display
        time_str =get_time_str(start_hour,start_min);  
        //tooltip
        tooltip_str = g_strconcat(tooltip_str, time_str, summary_str, "\n",NULL);
        
        if ((!strlen(description_str) == 0) && (!strlen(location_str) == 0))
        {
		des_loc_str = g_strconcat(des_loc_str, description_str, ". ",location_str, ".", NULL);
        }
        if ((!strlen(description_str) == 0) && (strlen(location_str) == 0))
        {
		des_loc_str = g_strconcat(des_loc_str, description_str, ".",NULL);
        }
        if ((strlen(description_str) == 0) && (!strlen(location_str) == 0))
        {
		des_loc_str = g_strconcat(des_loc_str, location_str, ".",NULL);
        }
        
        tooltip_str = g_strconcat(tooltip_str,des_loc_str, "\n",NULL);    
        
        } //if !all_day	
        else
        {
        tooltip_str = g_strconcat(tooltip_str, summary_str, "\n",NULL);
        
        if ((!strlen(description_str) == 0) && (!strlen(location_str) == 0))
        {
		des_loc_str = g_strconcat(des_loc_str, description_str, ". ",location_str, ".", NULL);
        }
        if ((!strlen(description_str) == 0) && (strlen(location_str) == 0))
        {
		des_loc_str = g_strconcat(des_loc_str, description_str, ".",NULL);
        }
        if ((strlen(description_str) == 0) && (!strlen(location_str) == 0))
        {
		des_loc_str = g_strconcat(des_loc_str, location_str, ".",NULL);
        }
        
        tooltip_str = g_strconcat(tooltip_str,des_loc_str, "\n",NULL);     
        
        }
        
        custom_calendar_set_tooltip_str(CUSTOM_CALENDAR(calendar), start_day, tooltip_str); 
        custom_calendar_mark_day(CUSTOM_CALENDAR(calendar), start_day);	
        
        g_object_unref(day_event); // Free the GObject
        }
        g_array_free(events_for_day, TRUE); // Free the array
    } else {
        g_print("No events found for the specified day or an error occurred.\n");
    }
	
 } //days in month
	
}

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
       
        // CRUCIAL to free the memory that was allocated by the function
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
	
	GtkWidget *check_button_show_tooltips= g_object_get_data(G_OBJECT(button), "check-button-show-tooltips-key");
	GtkWidget *check_button_dark_theme= g_object_get_data(G_OBJECT(button), "check-button-dark-theme-key");
			
	GtkWidget *colour_button_today= g_object_get_data(G_OBJECT(button), "colour-button-today-key");
	GtkWidget *colour_button_event= g_object_get_data(G_OBJECT(button), "colour-button-event-key");
	
	const GdkRGBA *rgba_today;
	rgba_today = gtk_color_dialog_button_get_rgba(GTK_COLOR_DIALOG_BUTTON(colour_button_today));	
	m_todaycolour = gdk_rgba_to_string (rgba_today);			
	
	const GdkRGBA *rgba_event;
	rgba_event = gtk_color_dialog_button_get_rgba(GTK_COLOR_DIALOG_BUTTON(colour_button_event));	
	m_eventcolour = gdk_rgba_to_string (rgba_event);		
	
	//talking
	GtkWidget *check_button_talk= g_object_get_data(G_OBJECT(button), "check-button-talk-key");
	GtkWidget *check_button_talk_event_number= g_object_get_data(G_OBJECT(button), "check-button-talk-event-number-key");		
	
	GtkWidget *check_button_reset_all= g_object_get_data(G_OBJECT(button), "check-button-reset-all-key");
	
	//listview
	m_12hour_format=gtk_check_button_get_active (GTK_CHECK_BUTTON(check_button_hour_format));	
	m_use_end_time=gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_show_end_time));
	
	//calendar
	m_show_tooltips=gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_show_tooltips));
	m_is_dark_theme=gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_dark_theme));
			
	//speak
	m_talk=gtk_check_button_get_active (GTK_CHECK_BUTTON(check_button_talk));
	m_talk_event_number=gtk_check_button_get_active (GTK_CHECK_BUTTON(check_button_talk_event_number));	
	
	m_reset_preferences=gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_reset_all));
	
	if(m_reset_preferences) {
	//reset everything
	//listview
	m_12hour_format=TRUE;
	m_use_end_time=FALSE;	
	//window size
	m_window_width=800;
	m_window_height=600;
	//calendar
	m_show_tooltips=TRUE;
	m_is_dark_theme=FALSE;	
    m_todaycolour="rgb(141,166,141)"; //sage
    m_eventcolour="rgb(217,230,217)"; //sage light
	
	//talking
	m_talk=TRUE;			
	m_talk_event_number=TRUE;		
	//m_reset_preferences=FALSE; //toggle
	}
	
	config_write();	//save preferences
		
	g_object_set(calendar, "todaycolour", m_todaycolour, NULL);
	g_object_set(calendar, "eventcolour", m_eventcolour, NULL);
	//g_object_set(calendar, "showtooltips", m_show_tooltips, NULL);
	custom_calendar_set_show_tooltips(CUSTOM_CALENDAR(calendar), m_show_tooltips);	
	custom_calendar_update (CUSTOM_CALENDAR(calendar));
	
	GListStore *store =g_object_get_data(G_OBJECT(calendar), "calendar-store-key");
	callbk_calendar_day_selected(CUSTOM_CALENDAR(calendar),store);	
	
	//apply theme	
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
 
static void callbk_preferences(GSimpleAction* action, GVariant *parameter,gpointer user_data)
{			
	GtkWidget *window =user_data;
    GtkWidget *dialog;
    GtkWidget *grid;
    GtkWidget *button_set;

    GtkWidget *check_button_hour_format;
    GtkWidget *check_button_show_end_time;
    GtkWidget *check_button_show_tooltips;
    GtkWidget *check_button_dark_theme;
    GtkWidget *check_button_talk;
    
    GtkWidget *check_button_talk_event_number;
    //GtkWidget *check_button_talk_upcoming;
    GtkWidget *check_button_reset_all;
    GtkWidget *label_todaycolour;
    GtkWidget *label_eventcolour;
    
    // Unused spacers, can be removed.
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

    GtkColorDialog *dialog_today = gtk_color_dialog_new();
    GtkWidget *colour_button_today = gtk_color_dialog_button_new(dialog_today);
    

    GdkRGBA rgba_today;
    if (gdk_rgba_parse (&rgba_today, m_todaycolour)) {
        gtk_color_dialog_button_set_rgba (GTK_COLOR_DIALOG_BUTTON(colour_button_today), &rgba_today);
    }
   
    GtkColorDialog *dialog_event = gtk_color_dialog_new();
    GtkWidget *colour_button_event = gtk_color_dialog_button_new(dialog_event);

    GdkRGBA rgba_event;
    if (gdk_rgba_parse (&rgba_event, m_eventcolour)) {
        gtk_color_dialog_button_set_rgba (GTK_COLOR_DIALOG_BUTTON(colour_button_event), &rgba_event);
    }
		
	label_todaycolour = gtk_label_new("Today Colour: ");
	label_eventcolour = gtk_label_new("Event Colour: ");
	
	//calendar
	check_button_hour_format = gtk_check_button_new_with_label ("12 Hour Format");	
	check_button_show_end_time = gtk_check_button_new_with_label ("Use End Time");
	check_button_show_tooltips = gtk_check_button_new_with_label ("Use Calendar Tooltips");
	check_button_dark_theme = gtk_check_button_new_with_label ("Use Dark Theme");
	
	//speech
	check_button_talk = gtk_check_button_new_with_label ("Enable Talking");
	check_button_talk_event_number = gtk_check_button_new_with_label ("Talk Event Number");
	//check_button_talk_upcoming= gtk_check_button_new_with_label ("Talk Upcoming");
		
	check_button_reset_all = gtk_check_button_new_with_label ("Reset All");
		
	//set calendar preferences
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_hour_format),m_12hour_format);	
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_show_end_time),m_use_end_time);
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_show_tooltips),m_show_tooltips);
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_dark_theme),m_is_dark_theme);
	
	////set speak
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_talk), m_talk);
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_talk_event_number), m_talk_event_number);
	
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_reset_all), m_reset_preferences);
	
	//data setters
	g_object_set_data(G_OBJECT(button_set), "dialog-key",dialog);
	//calendar
	g_object_set_data(G_OBJECT(button_set), "check-button-hour-format-key",check_button_hour_format);
	g_object_set_data(G_OBJECT(button_set), "check-button-show-end-time-key",check_button_show_end_time);		
	g_object_set_data(G_OBJECT(button_set), "check-button-show-tooltips-key",check_button_show_tooltips);
	g_object_set_data(G_OBJECT(button_set), "check-button-dark-theme-key",check_button_dark_theme);
	
	//speaking
	g_object_set_data(G_OBJECT(button_set), "check-button-talk-key",check_button_talk);
	g_object_set_data(G_OBJECT(button_set), "check-button-talk-event-number-key",check_button_talk_event_number);				
	//colour
	g_object_set_data(G_OBJECT(button_set), "colour-button-today-key", colour_button_today);
	g_object_set_data(G_OBJECT(button_set), "colour-button-event-key", colour_button_event);	
	//reset
	g_object_set_data(G_OBJECT(button_set), "check-button-reset-all-key",check_button_reset_all);
	
	//grid layout	
	//Calendar preferences	
	gtk_grid_attach(GTK_GRID(grid), check_button_hour_format,    1, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), check_button_show_end_time,  2, 1, 1, 1);
		
	gtk_grid_attach(GTK_GRID(grid), check_button_show_tooltips,  1, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), check_button_dark_theme,     2, 2, 1, 1);		
	
	gtk_grid_attach(GTK_GRID(grid), label_spacer1,             1, 3, 1, 1);
	
	gtk_grid_attach(GTK_GRID(grid), label_todaycolour,         1, 4, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), colour_button_today,       2, 4, 1, 1);
	
	gtk_grid_attach(GTK_GRID(grid), label_eventcolour,         1, 5, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), colour_button_event,       2, 5, 1, 1);
	
	gtk_grid_attach(GTK_GRID(grid), label_spacer2,               1, 6, 1, 1);
	
	//speak preferences
	gtk_grid_attach(GTK_GRID(grid), check_button_talk,             		1, 7, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), check_button_talk_event_number,     2, 7, 1, 1);
	
	gtk_grid_attach(GTK_GRID(grid), label_spacer3,     			  1, 8, 1, 1);
		
	gtk_grid_attach(GTK_GRID(grid), label_spacer5,      			 1, 9, 1, 1);	
	gtk_grid_attach(GTK_GRID(grid), check_button_reset_all,  		1, 10, 1, 1);	
	gtk_grid_attach(GTK_GRID(grid), label_spacer6,       			1, 11, 1, 1);	
	gtk_grid_attach(GTK_GRID(grid), button_set,  1, 12, 3, 1);
	
	gtk_window_set_child (GTK_WINDOW (dialog), grid);	
	gtk_window_present(GTK_WINDOW(dialog));
}
 
 
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
	gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(about_dialog), "Talk Calendar");
	gtk_about_dialog_set_version (GTK_ABOUT_DIALOG(about_dialog), "Version 0.5.2");
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(about_dialog),"Copyright © 2025");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(about_dialog),"Talk Calendar (Integral Speech Synthesizer)");
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
		
	GtkWidget *label_font_info;	
	GtkWidget *label_desktop_font;
	GtkWidget *label_gnome_text_scale;
	
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
	label_speak_shortcut=gtk_label_new("SPACEBAR: Speak Selected Day Events");
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
			
	
	label_font_info=gtk_label_new("Font");
	gtk_label_set_attributes (GTK_LABEL (label_font_info), attrs);
	
	settings = g_settings_new ("org.gnome.desktop.interface");
	gchar* desktop_font_str = g_settings_get_string (settings, "font-name");
	
	char* desktop_str = "Desktop Font = ";
	desktop_str =g_strconcat(desktop_str, desktop_font_str,NULL);
	label_desktop_font=gtk_label_new(desktop_str);
	
	gdouble sf =g_settings_get_double (settings,"text-scaling-factor");	
	char* gnome_text_scale_factor ="Text Scale Factor = ";
	char* font_scale_value_str = g_strdup_printf("%0.2lf", sf);
	gnome_text_scale_factor=g_strconcat(gnome_text_scale_factor, font_scale_value_str,NULL);
	label_gnome_text_scale=gtk_label_new(gnome_text_scale_factor);
	
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
		
	gtk_box_append(GTK_BOX(box),label_font_info);
	gtk_box_append(GTK_BOX(box),label_desktop_font);
	gtk_box_append(GTK_BOX(box),label_gnome_text_scale);
	
	pango_attr_list_unref(attrs);
	
	gtk_window_present (GTK_WINDOW (dialog));
	
	gtk_window_set_focus(GTK_WINDOW(window), GTK_WIDGET(calendar));
}

//======================================================================
//Speak helpers
//======================================================================
/**
 * @brief Gets the string representation of a day of the week.
 * @param day The day of the month.
 * @param month The month.
 * @param year The year.
 * @return A string representing the day of the week.
 */
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


static void callbk_speak(GtkButton *button, gpointer user_data)
{
	//g_print("callbk_speak\n");
	if(m_talk==FALSE) return;
	//GtkWidget *window =user_data;
	(void) user_data;
	GtkWidget *calendar = g_object_get_data(G_OBJECT(button), "button-speak-calendar-key");
	//GtkWidget *button_speak_time = g_object_get_data(G_OBJECT(button), "button-speak-time-key");
	gtk_widget_set_sensitive(GTK_WIDGET(button), FALSE); // Disable button while speaking
	//gtk_widget_set_sensitive(GTK_WIDGET(button_speak_time), FALSE); // Disable button while speaking
	
	
	// Create a dynamic array for words
    GPtrArray *words_array = g_ptr_array_new();
		
    int day = custom_calendar_get_day(CUSTOM_CALENDAR(calendar));
    int month = custom_calendar_get_month(CUSTOM_CALENDAR(calendar));
    int year = custom_calendar_get_year(CUSTOM_CALENDAR(calendar));

    char *dow_str = get_day_of_week(day, month, year);
    char *day_number_str = get_day_number_ordinal_string(day);
    char *month_str = get_month_string(month);
         
    // Add initial date words. We add copies to manage memory later.
    g_ptr_array_add(words_array, g_strdup(dow_str));
    g_ptr_array_add(words_array, g_strdup(day_number_str));
    g_ptr_array_add(words_array, g_strdup(month_str));
  
    
    //get all events for selected day
	GArray* events_for_day = db_get_all_events_year_month_day(db_handle, year, month, day);
	
	if(m_talk_event_number && events_for_day->len>0)
	{
		
		if(events_for_day->len==1)
		{
			g_ptr_array_add(words_array, g_strdup("one"));
			g_ptr_array_add(words_array, g_strdup("event"));
		}
		else if(events_for_day->len==2)
		{
			g_ptr_array_add(words_array, g_strdup("two"));
			g_ptr_array_add(words_array, g_strdup("events"));
	    }
	    else if(events_for_day->len==3)
		{
			g_ptr_array_add(words_array, g_strdup("three"));
			g_ptr_array_add(words_array, g_strdup("events"));
	    }
	    else if(events_for_day->len==4)
		{
			g_ptr_array_add(words_array, g_strdup("four"));
			g_ptr_array_add(words_array, g_strdup("events"));
	    }
	    else if(events_for_day->len==5)
		{
			g_ptr_array_add(words_array, g_strdup("five"));
			g_ptr_array_add(words_array, g_strdup("events"));
	    }
	    else if(events_for_day->len>5)
		{
			g_ptr_array_add(words_array, g_strdup("many"));
			g_ptr_array_add(words_array, g_strdup("events"));
	    }
	}
	
	
    
    if (events_for_day) {      
    for (guint i = 0; i < events_for_day->len; i++) 
    {
    char *summary_str = "";
    gint start_hour = 0;
	gint start_min = 0;
	gint end_hour = 0;
	gint end_min = 0;
	gint is_allday = 0;
	gint is_priority = 0;
        
    CalendarEvent* day_event = g_array_index(events_for_day, CalendarEvent*, i);
    
    g_object_get(day_event, "summary", &summary_str, NULL);
    g_object_get(day_event, "starthour", &start_hour, NULL);
	g_object_get(day_event, "startmin", &start_min, NULL);
    g_object_get(day_event, "endhour", &end_hour, NULL);
	g_object_get(day_event, "endmin", &end_min, NULL);		
	g_object_get(day_event, "isallday", &is_allday, NULL);
	g_object_get(day_event, "ispriority", &is_priority, NULL);
    	
	if(!is_allday) {
	
	char* time_str_start ="";
	time_str_start= get_time_str_talk(start_hour, start_min);
	
	
	char *token_time_start = strtok(time_str_start, " ");
    while (token_time_start != NULL) {
    //g_print("token_time_start word =%s\n", token_time_start);
    // Add each word token to the GPtrArray
    g_ptr_array_add(words_array, g_strdup(token_time_start));
	token_time_start = strtok(NULL, " ");
    }
    g_free(time_str_start);
	
	//end time
	
	if(m_use_end_time)
	{
	g_ptr_array_add(words_array, g_strdup("to"));
	char* time_str_end ="";
	time_str_end= get_time_str_talk(end_hour, end_min);		
	char *token_time_end = strtok(time_str_end, " ");
    while (token_time_end != NULL) {   
    // Add each word token to the GPtrArray
    g_ptr_array_add(words_array, g_strdup(token_time_end));
	token_time_end = strtok(NULL, " ");
    }
    g_free(time_str_end);	
	} //if use_end_time
			
	} //if not allday
     
    char *summary_str_lower = g_ascii_strdown(summary_str, -1);
    
    char *token = strtok(summary_str_lower, " ");
    while (token != NULL) {
    //g_print("summary word =%s\n", token);
    // Add each word token to the GPtrArray
    g_ptr_array_add(words_array, g_strdup(token));
    token = strtok(NULL, " ");
    }
    g_free(summary_str_lower);
    
    if(is_priority) {	
	g_ptr_array_add(words_array, g_strdup("high"));
	g_ptr_array_add(words_array,  g_strdup("priority"));
	}
      
    g_object_unref(day_event); // Free the GObject
    }
    g_array_free(events_for_day, TRUE); // Free the array
    } else {
    g_print("No events found for the specified day or an error occurred.\n");
    }
    
    // DEBUG: print the words to verify
    //g_print("Words array: ");
    //for (guint i = 0; i < words_array->len; i++) {
        //g_print("%s ", (char*)g_ptr_array_index(words_array, i));
    //}
    //g_print("\n");

    AudioTaskData *data = g_new(AudioTaskData, 1);
    data->diphone_entries = NULL;
    data->diphone_number = 0;
    data->tempo = 2.0f;
    data->amplification = 2.0f;

    for (guint i = 0; i < words_array->len; i++) {
        char* word_to_process = (char*)g_ptr_array_index(words_array, i);
        WordEntry* word_entry = find_word_entry(word_to_process);

        if (word_entry != NULL) {
            char* diphone_string = g_strdup(word_entry->diphone_str);
            char* start_ptr = diphone_string;
            char* end_ptr;

            while ((end_ptr = strchr(start_ptr, ' ')) != NULL) {
                *end_ptr = '\0';
                DiphoneEntry* entry = find_diphone_entry(start_ptr);
                if (entry != NULL) {
                    data->diphone_entries = (DiphoneEntry**)g_realloc_n(data->diphone_entries, data->diphone_number + 1, sizeof(DiphoneEntry*));
                    data->diphone_entries[data->diphone_number++] = entry;
                }
                *end_ptr = ' ';
                start_ptr = end_ptr + 1;
            }
            if (*start_ptr != '\0') {
                DiphoneEntry* entry = find_diphone_entry(start_ptr);
                if (entry != NULL) {
                    data->diphone_entries = (DiphoneEntry**)g_realloc_n(data->diphone_entries, data->diphone_number + 1, sizeof(DiphoneEntry*));
                    data->diphone_entries[data->diphone_number++] = entry;
                }
            }
            g_free(diphone_string);
        }
    }

    
    
    
    
    // Clean up the words_array and its contents
    g_ptr_array_free(words_array, TRUE);
		
	
    GTask *task = g_task_new(NULL, NULL, audio_synthesis_completed, button);
    g_task_set_task_data(task, data, NULL);
    g_task_run_in_thread(task, audio_synthesis_task);
    g_object_unref(task);
	
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
	ampm_str = "pmm ";					
	hour_str =get_cardinal_string(corrected_hour);
	}
	if(hour == 12)
	{
	ampm_str = "pmm ";					
	hour_str =get_cardinal_string(hour);
	}
	if(hour <12)
	{
	ampm_str = "amm ";					
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
 * @brief Gets the cardinal string for a number (e.g., "one", "two").
 * @param number The number.
 * @return The cardinal string.
 */
static char* get_cardinal_string(int number)
{
	char* result ="zero";
	switch(number)
	{
	//case 0:
	//result ="zero";
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
	result="thirty four";
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
 * @brief Updates the GListStore with events for the currently selected day.
 * @param calendar The CustomCalendar widget.
 * @param user_data A pointer to the GListStore.
 */
static void update_store(CustomCalendar *calendar, gpointer user_data)
{	
	GListStore *store = user_data;
	g_list_store_remove_all(G_LIST_STORE(store));
	
	int selected_day = custom_calendar_get_day(CUSTOM_CALENDAR(calendar));
	int selected_month = custom_calendar_get_month(CUSTOM_CALENDAR(calendar));
	int selected_year = custom_calendar_get_year(CUSTOM_CALENDAR(calendar));
	
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
  
  //char* start_hour_str =g_strdup_printf("%d",start_hour);
  //char* start_min_str =g_strdup_printf("%d",start_min);
  
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


/**
 * @brief update the time label
 * @param gpointer data to the GtkLabel
 */
static gboolean update_time_label(gpointer data)
{
	GtkLabel *label = (GtkLabel*)data;
	GtkWidget *label_alarm_state = g_object_get_data(G_OBJECT(label), "label-time-alarm-key");
 

    GDateTime *now = g_date_time_new_now_local();
    int current_hour = g_date_time_get_hour(now);
    int current_min = g_date_time_get_minute(now);
    int current_sec = g_date_time_get_second(now);
    char *time_str;
    //char *time_str = g_date_time_format(date_time, "%H:%M:%S");   // 24hr time format
	//char *time_str = g_date_time_format(date_time, "%H:%M");   // 24hr time format
    if(m_12hour_format)
    time_str = g_date_time_format(now, "%I:%M %p"); //12 hour format
    else 
    time_str = g_date_time_format(now, "%H:%M");
    
    gtk_label_set_text(GTK_LABEL(label), time_str); 
    
    if(current_hour==m_alarm_hour && current_min==m_alarm_min && current_sec==0 && m_alarm_on)
    {			
		//play the alarm signal in a thread
		GTask* task = g_task_new(NULL, NULL, alarm_task_callbk, NULL);	
		//GTask* task = g_task_new(NULL, NULL, NULL, NULL);		
	    g_task_run_in_thread(task, play_alarm_audio_async);     
	    g_object_unref(task);
    }
    
	g_free(time_str);
    g_date_time_unref(now);

	
	return continue_timer;
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

/**
 * @brief The main application entry point.
 * @param app The GtkApplication instance.
 * @param user_data User data.
 */
static void activate (GtkApplication *app, gpointer  user_data)
{
	GtkWidget *window;
	GtkWidget *header;
		
	GtkWidget *calendar;
	GtkWidget *scrolled_window;
	GtkWidget *paned;	
	GtkWidget *box;	
	GtkWidget *box_listview;
	GtkWidget *box_calendar;
	
	GtkWidget *button_speak;
	GtkWidget* label_time;
		
	GtkListItemFactory *factory;
	GListModel *model;
	GtkSingleSelection *selection;
	GtkWidget *list_view;
		
	window = gtk_application_window_new(app);
	gtk_window_set_title (GTK_WINDOW(window), "");		
	gtk_window_set_default_size (GTK_WINDOW(window), m_window_width, m_window_height);	
	g_signal_connect(window, "destroy", G_CALLBACK(callbk_shutdown), NULL);
	header = gtk_header_bar_new();
	gtk_window_set_titlebar(GTK_WINDOW(window), header);
		
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
	
	calendar = custom_calendar_new();
	
	int day = custom_calendar_get_day(CUSTOM_CALENDAR(calendar));
	int month = custom_calendar_get_month(CUSTOM_CALENDAR(calendar));
	int year = custom_calendar_get_year(CUSTOM_CALENDAR(calendar));
	
	g_signal_connect(CUSTOM_CALENDAR(calendar), "day-selected", G_CALLBACK(callbk_calendar_day_selected), store);
	g_signal_connect(CUSTOM_CALENDAR(calendar), "next-month", G_CALLBACK(callbk_calendar_next_month), window);
	g_signal_connect(CUSTOM_CALENDAR(calendar), "prev-month", G_CALLBACK(callbk_calendar_prev_month), window);
	g_signal_connect(CUSTOM_CALENDAR(calendar), "next-year", G_CALLBACK(callbk_calendar_next_year), window);
	g_signal_connect(CUSTOM_CALENDAR(calendar), "prev-year", G_CALLBACK(callbk_calendar_prev_year), window);
		
	g_object_set(calendar, "todaycolour", m_todaycolour, NULL);
	g_object_set(calendar, "eventcolour", m_eventcolour, NULL);
	g_object_set(calendar, "showtooltips", m_show_tooltips, NULL);
	
	// Set properties for colors and tooltips
    //g_object_set(calendar,
                 //"todaycolour", "rgb(141,166,141)",  // Sage
                 //"eventcolour", "rgb(217,230,217)",  // Sage light
                 //"showtooltips", TRUE,
                 //NULL);	
                
                 
	
	char* day_str = g_strdup_printf("%d", day);
	char* month_str =g_strdup_printf("%d", month);
	char* year_str =g_strdup_printf("%d", year);
	char* today_str=""; 
	today_str= g_strconcat(today_str, day_str, "-",month_str,"-",year_str,NULL);

	scrolled_window = gtk_scrolled_window_new();	
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window),list_view);
	   
    gtk_widget_set_hexpand (GTK_WIDGET (list_view), TRUE);
    gtk_widget_set_vexpand (GTK_WIDGET (list_view), TRUE);
	//gtk_widget_set_vexpand (GTK_WIDGET (list_view), FALSE);
    gtk_widget_set_halign(list_view, GTK_ALIGN_FILL); 
	gtk_widget_set_valign(list_view, GTK_ALIGN_FILL);
	
	box_listview =gtk_box_new(GTK_ORIENTATION_VERTICAL,1);	
	gtk_box_append(GTK_BOX(box_listview), scrolled_window); 
	
	box_calendar =gtk_box_new(GTK_ORIENTATION_VERTICAL,1);	
	 		
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
	
	const gchar *home_accels[2] = { "Home", NULL };	
	//const gchar *speak_accels[2] = { "space", NULL };
	//const gchar *speaktime_accels[2] = {"t", NULL };
	const gchar *newevent_accels[2] = {"<Ctrl>n", NULL };	
	const gchar *editevent_accels[2] = {"<Ctrl>e", NULL };		
	const gchar *delete_accels[2] = {"Delete", NULL };
	const gchar *info_accels[2] = {"F1", NULL };	
	const gchar * preferences_accels[2] = { "<Ctrl><Alt>P", NULL };
	const gchar * quit_accels[2] = { "<Ctrl>Q", NULL };
	
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
			
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.home", home_accels);	
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.newevent", newevent_accels);
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.editevent", editevent_accels);
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.deleteevent", delete_accels);
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.info", info_accels);
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.preferences", preferences_accels);
	
	//hamburger menu
	GMenu *menu, *section;
	GtkWidget *menu_button;
	GMenu *tools_menu; 
	GMenuItem *item;
	
	menu = g_menu_new();
	section = g_menu_new ();
	
	g_menu_append (section, "Export", "app.export"); 	
	g_menu_append_section (menu, NULL, G_MENU_MODEL (section));
	g_object_unref (section);
	
	section = g_menu_new ();
	g_menu_append (section, "Import", "app.import"); 	
	g_menu_append_section (menu, NULL, G_MENU_MODEL (section));
	g_object_unref (section);
	
	section = g_menu_new ();
	g_menu_append (section, "New Event", "app.newevent"); 	
	g_menu_append_section (menu, NULL, G_MENU_MODEL (section));
	g_object_unref (section);
	
	section = g_menu_new ();
	g_menu_append (section, "Edit Event", "app.editevent"); 	
	g_menu_append_section (menu, NULL, G_MENU_MODEL (section));
	g_object_unref (section);
	
	section = g_menu_new ();
	g_menu_append (section, "Delete Event", "app.deleteevent"); 	
	g_menu_append_section (menu, NULL, G_MENU_MODEL (section));
	g_object_unref (section);
	
	section = g_menu_new ();
	g_menu_append (section, "Delete All", "app.deleteall"); 	
	g_menu_append_section (menu, NULL, G_MENU_MODEL (section));
	g_object_unref (section);
			
	tools_menu =g_menu_new();
	item =g_menu_item_new("Calculate Easter", "app.easter");
	g_menu_append_item(tools_menu,item);
	g_object_unref(item);
	
	item =g_menu_item_new("Search", "app.search");
	g_menu_append_item(tools_menu,item);
	g_object_unref(item);
	
	g_menu_append_submenu(menu, "Tools", G_MENU_MODEL(tools_menu));
	g_object_unref(tools_menu); 
		
	section = g_menu_new();
	g_menu_append(section, "Preferences", "app.preferences");
	g_menu_append_section(menu, NULL, G_MENU_MODEL(section));
	g_object_unref(section);
		
	section = g_menu_new ();
	g_menu_append (section, "Information", "app.info"); //show app info
	g_menu_append_section (menu, NULL, G_MENU_MODEL (section));
	g_object_unref (section);
	
	section = g_menu_new ();
	g_menu_append (section, "About", "app.about");
	g_menu_append_section (menu, NULL, G_MENU_MODEL (section));
	g_object_unref (section);
	
	menu_button = gtk_menu_button_new();
	gtk_widget_set_tooltip_text(menu_button, "Menu");
	gtk_menu_button_set_icon_name (GTK_MENU_BUTTON (menu_button),"open-menu-symbolic"); 		
	gtk_menu_button_set_menu_model (GTK_MENU_BUTTON (menu_button), G_MENU_MODEL(menu));
	gtk_header_bar_pack_end(GTK_HEADER_BAR (header), menu_button);
		
	
	set_tooltips_on_calendar(CUSTOM_CALENDAR(calendar));
		
	custom_calendar_update (CUSTOM_CALENDAR(calendar));
	update_store(CUSTOM_CALENDAR(calendar), store);
	
	//speak buttons
	
	button_speak= gtk_button_new_with_label("Speak");		
	//g_signal_connect(button_speak_events, "clicked", G_CALLBACK(callbk_speak_events), window);
	g_signal_connect(button_speak, "clicked", G_CALLBACK(callbk_speak), button_speak);		
	gtk_header_bar_pack_start(GTK_HEADER_BAR(header), button_speak);	
	g_object_set_data(G_OBJECT(button_speak), "button-speak-calendar-key",calendar);
	
	label_time=gtk_label_new("");	
    gtk_label_set_xalign(GTK_LABEL(label_time),0.5);
	g_timeout_add_seconds(1, update_time_label, label_time);
	//gtk_header_bar_pack_start(GTK_HEADER_BAR(header), label_time);
	gtk_header_bar_pack_end(GTK_HEADER_BAR(header), label_time);
		
	//GtkWidget *button_alarm = gtk_button_new_with_label("Alarm");	
	GtkWidget *button_alarm = gtk_button_new_from_icon_name("alarm-symbolic");
	g_signal_connect(button_alarm, "clicked", G_CALLBACK(callbk_alarm_button), window);	
	gtk_header_bar_pack_end(GTK_HEADER_BAR(header), button_alarm);
		
	paned = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    gtk_paned_set_start_child(GTK_PANED(paned), box_calendar);
    gtk_paned_set_end_child(GTK_PANED(paned), box_listview);	
	gtk_window_set_child (GTK_WINDOW (window), paned);		
	
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
int main (int  argc, char **argv)
{
	//GtkApplication *app;
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
	
	db_close(db_handle); // Close database on exit	
	
	return status;
}
