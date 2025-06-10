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
// Talk Calendar Testing GTK4
// Author: Alan Crispin <crispinalan@gmail.com> 
// Date:June 2025
// use Makefile to compile
//====================================================================

#include <gtk/gtk.h>
#include <ctype.h> //whitespace
#include <glib/gstdio.h>  //needed for g_mkdir
#include <math.h>  //compile with -lm

#include "calendarevent.h"
#include "dbmanager.h"
#include "displayitem.h"

#include "diphone.h"
#include "dictionary.h"
#include "wordrules.h"
#include "notabledates.h"
#include "raw_utils.h"

#define CONFIG_DIRNAME "talkcalendar"
#define CONFIG_FILENAME "talkcalendar-040"
static char * m_config_file = NULL;

//Declarations
static void create_header(GtkWindow *window);
static void callbk_new_event(GSimpleAction *action, GVariant *parameter,  gpointer user_data);
static void callbk_add_new_event(GtkButton *button, gpointer user_data);

static void callbk_edit_event(GSimpleAction *action, GVariant *parameter,  gpointer user_data);
static void callbk_update_event(GtkButton *button, gpointer user_data);

static void callbk_delete_selected(GSimpleAction *action, GVariant *parameter,  gpointer user_data);

static int get_month_number(const char* month_str);

static void callbk_export(GSimpleAction *action, GVariant *parameter,  gpointer user_data);
static void file_save_response (GObject *source, GAsyncResult *result, void *user_data);
void export_file(char *file_name) ;

static void callbk_import(GSimpleAction *action, GVariant *parameter,  gpointer user_data);
static void file_chooser_response (GObject *source, GAsyncResult *result, void *user_data);
void import_ical_file(gpointer user_data);

//gboolean import_ical_file(gpointer user_data);

gboolean file_exists(const char *file_name);


//Callbks
static void callbk_about(GSimpleAction* action, GVariant *parameter, gpointer user_data);
static void callbk_info(GSimpleAction *action, GVariant *parameter,  gpointer user_data);

static void callbk_set_preferences(GtkButton *button, gpointer  user_data);
static void callbk_preferences(GSimpleAction* action, GVariant *parameter,gpointer user_data);
static void callbk_check_button_upcoming_toggled(GtkCheckButton *check_button, gpointer user_data);

static void callbk_delete_all(GSimpleAction *action, GVariant *parameter,  gpointer user_data);

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


//text processing
static char *ignore_first_zero(char *input);
static char *remove_zeros(const char *text);
static char *remove_commas(const char *text);
static char *remove_fullstop(const char *text);
static char* remove_semicolons (const char *text);
static char* remove_question_marks (const char *text);
static char* remove_explanation_marks (const char *text);
static char* remove_punctuations(const char *text);
static char* replace_hypens(const char *text);
static char* replace_newlines(const char *text);
char *trim_whitespace(char *s);

char* get_time_str(int hour, int min);

//Search
static void callbk_search(GSimpleAction *action, GVariant *parameter,  gpointer user_data);
static void callbk_search_events(GtkButton *button, gpointer user_data);
static void search_events(const char* search_str);

//Speaking
static void speak_events();
static void callbk_speak(GSimpleAction* action, GVariant *parameter,gpointer user_data);
static void callbk_speaktime(GSimpleAction * action, GVariant *parameter, gpointer user_data);

GList* convert_date_to_weekday_diphone_list(int day, int month, int year);
GList* convert_day_number_to_diphone_list(int day_number);
GList* convert_month_to_diphone_list(int month);
GList* get_event_number_diphone_list(int event_number);
GList* convert_number_to_diphone_list(int number);
GList* get_upcoming_number_diphone_list(int number);
static void speak_time(gint hour, gint min);

static void task_callbk(GObject *gobject,GAsyncResult *res,  gpointer  user_data);

unsigned char *rawcat(unsigned char *arrys[], unsigned int arry_size[], int arry_count);
unsigned int get_merge_size(unsigned int sizes_arry[], int arry_size);
static void play_diphone_list(GList *diphone_list);

static void play_audio_async (GTask *task,
                          gpointer object,
                          gpointer task_data,
                          GCancellable *cancellable);

int  get_number_of_day_events();

GArray*  get_upcoming_array(int upcoming_days);
int  get_total_number_of_events();

//======================================================================

//window
static int m_window_width=600;
static int m_window_height=400;

//listbox
static GListStore *m_store=NULL;   //m_store is a Gio GListStore store (not GktListStore which is being depreciated)
static int m_id_selection=-1;
static int m_row_index=-1; //listbox row index
static int m_index=-1;
static int m_store_size=0;

//listbox display
static GtkWidget *create_widget (gpointer item, gpointer user_data);
static void add_separator (GtkListBoxRow *row, GtkListBoxRow *before, gpointer data);
static void callbk_row_activated (GtkListBox  *listbox,	 GtkListBoxRow *row, gpointer user_data);
static void display_event_array(GArray *evt_arry);

//debugging
void print_array(GArray *a);

CalendarEvent *selected_evt;

//calendar

static int m_start_year=0;
static int m_start_month=0;
static int m_start_day=0;

static int m_end_year=0;
static int m_end_month=0;
static int m_end_day=0;

static int m_start_hour=0;
static int m_start_min=0;
static int m_end_hour=0;
static int m_end_min=0;

static int m_priority=0;
static int m_is_yearly=0;
static int m_is_allday=0;

//listview display
static int m_12hour_format=1; //am pm hour format
static int m_show_end_time=0; //show end_time
static int m_show_location=1; //show location
static int m_notable_dates=0;

//Speaking
//talk preferences
static int m_talk =1;
static int m_talk_time=1;
static int m_talk_summary=1; 
static int m_talk_at_startup =0;
static int m_talk_upcoming=0;
static int m_upcoming_days=7;
static int m_talk_priority=0;

gboolean m_talking=FALSE; //async
static unsigned int m_sample_rate=32000;

static int m_reset_preferences=0;

static char* m_file_name="talkcalendar.ical";

static const char* m_summary ="appointment";
static const char* m_location ="";
static const char* m_description ="";

//====================================================================

const GActionEntry app_actions[] = {
  { "speak", callbk_speak}, 
  { "speaktime", callbk_speaktime},   
  { "home", callbk_calendar_home}, 
  { "newevent", callbk_new_event},
  { "info", callbk_info},
  { "preferences", callbk_preferences},
  { "deleteevent", callbk_delete_selected}
  //{ "quit", callbk_quit}
};

//=====================================================================
static int get_month_number(const char* month_str) {
	
	char* month= g_ascii_strdown(month_str,-1);
	
	if(g_strcmp0(month,"january")==0) return 1;
	else if(g_strcmp0(month,"february")==0) return 2;
	else if(g_strcmp0(month,"march")==0) return 3;
	else if(g_strcmp0(month,"april")==0) return 4;
	else if(g_strcmp0(month,"may")==0) return 5;
	else if(g_strcmp0(month,"june")==0) return 6;
	else if(g_strcmp0(month,"july")==0) return 7;
	else if(g_strcmp0(month,"august")==0) return 8;
	else if(g_strcmp0(month,"september")==0) return 9;
	else if(g_strcmp0(month,"october")==0) return 10;
	else if(g_strcmp0(month,"november")==0) return 11;
	else if(g_strcmp0(month,"december")==0) return 12;
	else return 0;	
}
//======================================================================

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
static guint get_dropdown_position_month(const char* month)
{
	
	guint position=0;//starts at zero not one
	gchar* summary_lower= g_ascii_strdown(month,-1);
		
	if (g_strcmp0(summary_lower,"january")==0) {
	position=0;
	}
	if (g_strcmp0(summary_lower,"february")==0) {
	position=1;
	}	
	if (g_strcmp0(summary_lower,"march")==0) {
	position=2;
	}
	if (g_strcmp0(summary_lower,"april")==0) {
	position=3;
	}
		if (g_strcmp0(summary_lower,"may")==0) {
	position=4;
	}
	if (g_strcmp0(summary_lower,"june")==0) {
	position=5;
	}
	if (g_strcmp0(summary_lower,"july")==0) {
	position=6;
	}
	if (g_strcmp0(summary_lower,"august")==0) {
	position=7;
	}
	if (g_strcmp0(summary_lower,"september")==0) {
	position=8;
	}
	if (g_strcmp0(summary_lower,"october")==0) {
	position=9;
	}	
	if (g_strcmp0(summary_lower,"november")==0) {
	position=10;
	}	
	if (g_strcmp0(summary_lower,"december")==0) {
	position=11;
	}
	
	return position;
}

//=====================================================================
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
// Save load config file
//======================================================================

static void config_load_default()
{
		
	m_talk=1;
	m_talk_at_startup=0;
	m_talk_upcoming=0;
	m_upcoming_days=7;
		
	//calendar
	m_12hour_format=1;
	m_show_end_time=0;
	m_notable_dates=0;
		
	m_window_width=600;
	m_window_height=500;
	
}

//======================================================================

static void config_read()
{
	m_talk=1;
	m_talk_at_startup=0;
	m_talk_upcoming=0;
	m_upcoming_days=7;
	
	//calendar
	m_12hour_format=1;
	m_show_end_time=0;
	m_notable_dates=0;
		
	m_window_width=600;
	m_window_height=500;
			
	// Load keys from keyfile
	GKeyFile * kf = g_key_file_new();
	g_key_file_load_from_file(kf, m_config_file, G_KEY_FILE_NONE, NULL);

	//talk general
	m_talk = g_key_file_get_integer(kf, "calendar_settings", "speak", NULL);
	m_talk_at_startup=g_key_file_get_integer(kf, "calendar_settings", "speak_startup", NULL);
	m_talk_upcoming=g_key_file_get_integer(kf, "calendar_settings", "speak_upcoming", NULL);	
	m_upcoming_days=g_key_file_get_integer(kf, "calendar_settings", "upcoming_days", NULL);
		
	//listview
	m_12hour_format=g_key_file_get_integer(kf, "calendar_settings", "hour_format", NULL);
	m_show_end_time = g_key_file_get_integer(kf, "calendar_settings", "show_end_time", NULL);
	//date label
	m_notable_dates = g_key_file_get_integer(kf, "calendar_settings", "notable_dates", NULL);
	
	//window size	
    m_window_width = g_key_file_get_integer(kf, "calendar_settings", "window_width", NULL);
	m_window_height=g_key_file_get_integer(kf, "calendar_settings", "window_height", NULL);
        	
	g_key_file_free(kf);
}
//======================================================================

void config_write()
{

	GKeyFile * kf = g_key_file_new();

	//talk general	
	g_key_file_set_integer(kf, "calendar_settings", "speak", m_talk);	
	g_key_file_set_integer(kf, "calendar_settings", "speak_startup", m_talk_at_startup);
	g_key_file_set_integer(kf, "calendar_settings", "speak_upcoming", m_talk_upcoming);
	g_key_file_set_integer(kf, "calendar_settings", "upcoming_days", m_upcoming_days);	
		
	//listview
	g_key_file_set_integer(kf, "calendar_settings", "hour_format", m_12hour_format);
	g_key_file_set_integer(kf, "calendar_settings", "show_end_time", m_show_end_time);
	
	//speak
	g_key_file_set_integer(kf, "calendar_settings", "speak_startup", m_talk_at_startup);
	g_key_file_set_integer(kf, "calendar_settings", "speak_upcoming", m_talk_upcoming);
	g_key_file_set_integer(kf, "calendar_settings", "upcoming_days", m_upcoming_days);	
	
	//date label
	g_key_file_set_integer(kf, "calendar_settings", "notable_dates", m_notable_dates);
	
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
int  get_number_of_day_events(){
	int event_count=db_get_number_of_rows_year_month_day(m_start_year, m_start_month, m_start_day);	
	return event_count;
}

//======================================================================
int  get_total_number_of_events(){

	return db_get_number_of_rows_all();
}
//======================================================================
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
//=====================================================================

static char *remove_zeros(const char *text)
{
	GString *str;
	const char *p;
	str = g_string_new("");
	p = text;
	while (*p)
	{
		gunichar cp = g_utf8_get_char(p);
		if (cp != '0')
		{ 
			g_string_append_unichar(str, *p);
		} // if
		++p;
	}
	return g_string_free(str, FALSE);
}
//======================================================================
static char *remove_commas(const char *text)
{
	GString *str;
	const char *p;
	str = g_string_new("");
	p = text;
	while (*p)
	{
		gunichar cp = g_utf8_get_char(p);
		if (cp != ',')
		{ 
			g_string_append_unichar(str, *p);
		} // if
		++p;
	}
	return g_string_free(str, FALSE);
}
//======================================================================
static char *remove_fullstop(const char *text)
{
	GString *str;
	const char *p;
	str = g_string_new("");
	p = text;
	while (*p)
	{
		gunichar cp = g_utf8_get_char(p);
		if (cp != '.')
		{ 
			g_string_append_unichar(str, *p);
		} // if
		++p;
	}
	return g_string_free(str, FALSE);
}
//======================================================================
static char* remove_semicolons (const char *text)
{
	GString *str;
	const char *p;
	str = g_string_new ("");
	p = text;
	while (*p)
	{
	gunichar cp = g_utf8_get_char(p);
	if ( cp != ';' ){ 
	g_string_append_unichar (str, *p);
	}//if
	++p;
	}
	return g_string_free (str, FALSE);
}
//======================================================================
static char* remove_question_marks (const char *text)
{
	GString *str;
	const char *p;
	str = g_string_new ("");
	p = text;
	while (*p)
	{
	gunichar cp = g_utf8_get_char(p);
	if ( cp != '?' ){ 
	g_string_append_unichar (str, *p);
	}//if
	++p;
	}
	return g_string_free (str, FALSE);
}
//======================================================================
static char* remove_explanation_marks (const char *text)
{
	GString *str;
	const char *p;
	str = g_string_new ("");
	p = text;
	while (*p)
	{
	gunichar cp = g_utf8_get_char(p);
	if ( cp != '!' ){ 
	g_string_append_unichar (str, *p);
	}//if
	++p;
	}
	return g_string_free (str, FALSE);
}
//======================================================================
static char* remove_punctuations(const char *text)
{
	GString *str;
	const char *p;
	str = g_string_new ("");
	p = text;
	while (*p)
	{
	gunichar cp = g_utf8_get_char(p);
	if ( cp != '\'' ){ //remove all apostrophes
	g_string_append_unichar (str, *p);
	}//if
	++p;
	}
	return g_string_free (str, FALSE);
}
//======================================================================
static char* replace_hypens(const char *text)
{
	GString *str;
	const char *p;
	str = g_string_new ("");
	p = text;
	gint i=0;
	while (*p)
	{
	gunichar cp = g_utf8_get_char(p);
	if ( cp != '-' ){ //append
	g_string_append_unichar (str, *p);
	}//if
	if ( cp == '-' ){ //replace			
	g_string_insert_unichar (str,i,' ');
	}//if	
	++p;
	++i;
	}
	return g_string_free (str, FALSE);
}
//======================================================================
static char* replace_newlines(const char *text)
{
	GString *str;
	const char *p;
	str = g_string_new ("");
	p = text;
	gint i=0;
	while (*p)
	{
	gunichar cp = g_utf8_get_char(p);
	if ( cp != '\n' ){ //append
	g_string_append_unichar (str, *p);
	}//if
	if ( cp == '\n' ){ //replace			
	g_string_insert_unichar (str,i,' ');
	}//if	
	++p;
	++i;
	}
	return g_string_free (str, FALSE);
}
//======================================================================

char *trim_whitespace(char *s) 
{
  // returns a pointer to the (shifted) trimmed string
  char *original = s;
  size_t len = 0;

  while (isspace((unsigned char) *s)) {
    s++;
  } 
  if (*s) {
    char *p = s;
    while (*p) p++;
    while (isspace((unsigned char) *(--p)));
    p[1] = '\0';
    // len = (size_t) (p - s);   // older errant code
    len = (size_t) (p - s + 1);  // Thanks to @theriver
  }

  return (s == original) ? s : memmove(original, s, len + 1);
}

//=====================================================================
static void callbk_spin_day_start(GtkSpinButton *button, gpointer user_data)
{	
	m_start_day = gtk_spin_button_get_value_as_int (button);	
}
//=====================================================================
static void callbk_dropdown_month_start(GtkDropDown* self, gpointer user_data)
{		
	const char* month = gtk_string_object_get_string (GTK_STRING_OBJECT (gtk_drop_down_get_selected_item (self)));
	m_start_month=get_month_number(month);		
}
//=====================================================================
static void callbk_spin_year_start(GtkSpinButton *button, gpointer user_data)
{	
	m_start_year = gtk_spin_button_get_value_as_int (button);	
}

//======================================================================
static void callbk_spin_hour_start(GtkSpinButton *button, gpointer user_data)
{	
	m_start_hour = gtk_spin_button_get_value_as_int (button);	
}
//======================================================================
static void callbk_spin_min_start(GtkSpinButton *button, gpointer user_data)
{	
	m_start_min = gtk_spin_button_get_value_as_int (button);	
}
//======================================================================

static void callbk_spin_hour_end(GtkSpinButton *button, gpointer user_data)
{	
	m_end_hour = gtk_spin_button_get_value_as_int (button);
	//clamping checks
	if (m_end_hour<m_start_hour) m_end_hour =m_start_hour;	
}
//======================================================================

static void callbk_spin_min_end(GtkSpinButton *button, gpointer user_data)
{	
	m_end_min = gtk_spin_button_get_value_as_int (button);	
	//clamping check
	if ((m_end_hour == m_start_hour) && (m_end_min < m_start_min)) m_end_min =m_start_min;
}

//======================================================================
static void callbk_check_button_allday_toggled(GtkCheckButton *check_button, gpointer user_data)
{
	GtkWidget *spin_button_start_hour;
	GtkWidget *spin_button_start_min;
	GtkWidget *spin_button_end_hour;
	GtkWidget *spin_button_end_min;
	GtkWidget *check_button_reminder;
		
	spin_button_start_hour = g_object_get_data(G_OBJECT(user_data), "cb_allday_spin_start_hour_key");
	spin_button_start_min = g_object_get_data(G_OBJECT(user_data), "cb_allday_spin_start_min_key");
	spin_button_end_hour = g_object_get_data(G_OBJECT(user_data), "cb_allday_spin_end_hour_key");
	spin_button_end_min = g_object_get_data(G_OBJECT(user_data), "cb_allday_spin_end_min_key");
	
	if (gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button)))
	{
		gtk_widget_set_sensitive(spin_button_start_hour, FALSE);
		gtk_widget_set_sensitive(spin_button_start_min, FALSE);
		gtk_widget_set_sensitive(spin_button_end_hour, FALSE);
		gtk_widget_set_sensitive(spin_button_end_min, FALSE);		
	}
	else
	{
		gtk_widget_set_sensitive(spin_button_start_hour, TRUE);
		gtk_widget_set_sensitive(spin_button_start_min, TRUE);
		gtk_widget_set_sensitive(spin_button_end_hour, TRUE);
		gtk_widget_set_sensitive(spin_button_end_min, TRUE);
	}
}

//======================================================================

static void callbk_add_new_event(GtkButton *button, gpointer user_data)
{

	g_return_if_fail(GTK_IS_BUTTON(button));
	
	GtkWidget *window = user_data;
	GtkWidget *calendar = g_object_get_data(G_OBJECT(window), "window-calendar-key");	
	GtkWidget *label_date =g_object_get_data(G_OBJECT(window), "window-label-date-key");
	
	GtkWidget *dialog = g_object_get_data(G_OBJECT(button), "dialog-key");
	
	GtkEntryBuffer *buffer_summary;
	GtkWidget *entry_summary = g_object_get_data(G_OBJECT(button), "entry-summary-key");
	
	GtkEntryBuffer *buffer_location;
	GtkWidget *entry_location = g_object_get_data(G_OBJECT(button), "entry-location-key");
	
	GtkEntryBuffer *buffer_description;
	GtkWidget *entry_description = g_object_get_data(G_OBJECT(button), "entry-description-key");
	
	GtkWidget *check_button_allday = g_object_get_data(G_OBJECT(button), "check-button-allday-key");
	//GtkWidget *check_button_multiday = g_object_get_data(G_OBJECT(button), "check-button-multiday-key");
	GtkWidget *check_button_isyearly = g_object_get_data(G_OBJECT(button), "check-button-isyearly-key");
	GtkWidget *check_button_priority = g_object_get_data(G_OBJECT(button), "check-button-priority-key");
	
	GtkWidget *spin_button_day_start = g_object_get_data(G_OBJECT(button), "spin-day-start-key");
	GtkWidget *spin_button_year_start= g_object_get_data(G_OBJECT(button), "spin-year-start-key");	
	
	GtkWidget *spin_button_start_hour = g_object_get_data(G_OBJECT(button), "spin-start-hour-key");
	GtkWidget *spin_button_start_min = g_object_get_data(G_OBJECT(button), "spin-start-min-key");
	
	GtkWidget *spin_button_end_hour = g_object_get_data(G_OBJECT(button), "spin-end-hour-key");
	GtkWidget *spin_button_end_min = g_object_get_data(G_OBJECT(button), "spin-end-min-key");
		
	//m_summary	
	m_summary="";	
	guint16 summary_str_len =0; 	
	summary_str_len = gtk_entry_get_text_length(GTK_ENTRY(entry_summary));
	
	if(summary_str_len ==0)
	{
	m_summary ="Unknown event";
	} //if len
	else
	{
	buffer_summary = gtk_entry_get_buffer(GTK_ENTRY(entry_summary));
	m_summary = gtk_entry_buffer_get_text(buffer_summary);
	
	char* summary = g_strdup(m_summary);//duplicate as m_summary const
	m_summary=trim_whitespace(summary);
	
	m_summary = remove_semicolons(m_summary);
	m_summary = remove_commas(m_summary);
	m_summary =remove_punctuations(m_summary);		
	} //else

	
	m_description="";		
	buffer_description = gtk_entry_get_buffer(GTK_ENTRY(entry_description));
	m_description = gtk_entry_buffer_get_text(buffer_description);
	
	char* description = g_strdup(m_description);//duplicate as const
	m_description=trim_whitespace(description);
	m_description = remove_semicolons(m_description);
	m_description = remove_commas(m_description);
	m_description =remove_punctuations(m_description);
	
	m_location="";
	buffer_location = gtk_entry_get_buffer(GTK_ENTRY(entry_location));
	m_location = gtk_entry_buffer_get_text(buffer_location);
	
	char* location = g_strdup(m_location);//duplicate as const
	m_location=trim_whitespace(location);
	m_location = remove_semicolons(m_location);
	m_location = remove_commas(m_location);
	m_location =remove_punctuations(m_location);
	
	//capture typed values
	m_start_day= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_day_start));
	m_start_year= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_year_start));	 
			
	m_start_hour= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_start_hour));
	m_start_min= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_start_min));	
	m_end_hour= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_end_hour));
	m_end_min= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_end_min));
	
	m_is_allday = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_allday));
	
	if (m_is_allday) 
	{
		m_start_hour=0; //sorting to top
		m_start_min=0;
		m_end_hour=0;
		m_end_min=0;
	 }
	
		
	m_is_yearly = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_isyearly));	
	m_priority = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_priority));
	
	//no multiday
	m_end_day =m_start_day;
	m_end_month=m_start_month;
	m_end_year=m_start_year;
			
	//add event into db
		
	CalendarEvent *evt = g_object_new(CALENDAR_TYPE_EVENT, 0);
	
	g_object_set(evt, "summary", g_strdup(m_summary), NULL);
	g_object_set(evt, "location", g_strdup(m_location), NULL);
	g_object_set(evt, "description", g_strdup(m_description), NULL);
	g_object_set(evt, "startyear", m_start_year, NULL);
	g_object_set(evt, "startmonth", m_start_month, NULL);
	g_object_set(evt, "startday", m_start_day, NULL);
	g_object_set(evt, "starthour", m_start_hour, NULL);
	g_object_set(evt, "startmin", m_start_min, NULL);
	g_object_set(evt, "endyear", m_end_year, NULL); // to do
	g_object_set(evt, "endmonth", m_end_month, NULL);
	g_object_set(evt, "endday", m_end_day, NULL);
	g_object_set(evt, "endhour", m_end_hour, NULL);
	g_object_set(evt, "endmin", m_end_min, NULL);
	g_object_set(evt, "isyearly", m_is_yearly, NULL);
	g_object_set(evt, "isallday", m_is_allday, NULL);		
	g_object_set(evt, "ispriority", m_priority, NULL);	
	
	db_insert_event(evt); //insert event into database	
	
	m_id_selection = -1;
	m_row_index=-1;
	
	//update calendar (also updates listbox)	
	set_marks_on_calendar(GTK_CALENDAR(calendar));
	update_calendar(GTK_CALENDAR(calendar), GTK_LABEL(label_date));				
	
	gtk_window_destroy(GTK_WINDOW(dialog));	
	
}
//======================================================================

static void callbk_new_event(GSimpleAction *action, GVariant *parameter,  gpointer user_data)
{
		
	GtkWidget *window = user_data;
	GtkWidget *dialog;
	
	dialog = gtk_window_new(); 
	gtk_window_set_title(GTK_WINDOW(dialog), "New Event");
	
	GtkWidget *button_add_event;
	
	GtkWidget *grid;
	
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
	GtkWidget *label_spacer5;
	GtkWidget *label_spacer6;
	
	//date
	GtkWidget *label_date_start;
	GtkWidget *spin_button_day_start;	
	GtkWidget *dropdown_month_start;	
	GtkWidget *spin_button_year_start;
	
	// Check buttons
	GtkWidget *check_button_allday;	
	GtkWidget *check_button_isyearly;
	GtkWidget *check_button_priority;
	GtkWidget *check_button_hasreminder;

	//Adjustments
	// value,lower,upper,step_increment,page_increment,page_size
	GtkAdjustment *adjustment_day = gtk_adjustment_new(1.00, 0.0, 31.00, 1.0, 1.0, 0.0);	
	GtkAdjustment *adjustment_year = gtk_adjustment_new(2024.00, 0.0, 5000.00, 1.0, 1.0, 0.0);
	GtkAdjustment *adjustment_day_end = gtk_adjustment_new(1.00, 0.0, 31.00, 1.0, 1.0, 0.0);
	GtkAdjustment *adjustment_year_end = gtk_adjustment_new(2024.00, 0.0, 5000.00, 1.0, 1.0, 0.0);
	
	//start time
	GtkWidget *label_start_time;
	GtkWidget *spin_button_start_hour;	
	GtkWidget *spin_button_start_min;
	//end time
	GtkWidget *label_end_time;
	GtkWidget *spin_button_end_hour;	
	GtkWidget *spin_button_end_min;
	
	GtkAdjustment *adjustment_start_hour = gtk_adjustment_new(1.00, 0.0, 23.00, 1.0, 1.0, 0.0);
	GtkAdjustment *adjustment_start_min= gtk_adjustment_new(1.00, 0.0, 59.00, 1.0, 1.0, 0.0);
	
	GtkAdjustment *adjustment_end_hour = gtk_adjustment_new(1.00, 0.0, 23.00, 1.0, 1.0, 0.0);
	GtkAdjustment *adjustment_end_min = gtk_adjustment_new(1.00, 0.0, 59.00, 1.0, 1.0, 0.0);
	
	label_spacer1 = gtk_label_new("");
	label_spacer2 = gtk_label_new("");
	label_spacer3 = gtk_label_new("");
	label_spacer4 = gtk_label_new("");
	label_spacer5 = gtk_label_new("");
	label_spacer6 = gtk_label_new("");
	
	button_add_event = gtk_button_new_with_label ("Add Event");
	g_signal_connect (GTK_BUTTON (button_add_event),"clicked", G_CALLBACK (callbk_add_new_event), G_OBJECT (window));
	
	grid = gtk_grid_new();	
	gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	m_end_day=m_start_day;
	m_end_month=m_start_month;
	m_end_year=m_start_year;
	
	m_start_hour=0;
	m_start_min=0;
	m_end_hour=0;
	m_end_min=0;
		
	//summary
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
	gtk_entry_set_max_length(GTK_ENTRY(entry_location), 25);
		
	//start date
	label_date_start =gtk_label_new("Start Date: ");	
	spin_button_day_start = gtk_spin_button_new(adjustment_day, 1.0, 0);	
	g_signal_connect(GTK_SPIN_BUTTON(spin_button_day_start), "value_changed", G_CALLBACK(callbk_spin_day_start), NULL);	
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_day_start), m_start_day);
	
	dropdown_month_start =gtk_drop_down_new_from_strings(month_strs);    
    g_signal_connect(GTK_DROP_DOWN(dropdown_month_start), "notify::selected", G_CALLBACK(callbk_dropdown_month_start), NULL);
    gtk_drop_down_set_selected(GTK_DROP_DOWN(dropdown_month_start),m_start_month-1);
	
	spin_button_year_start = gtk_spin_button_new(adjustment_year, 1.0, 0);
	g_signal_connect(GTK_SPIN_BUTTON(spin_button_year_start), "value_changed", G_CALLBACK(callbk_spin_year_start), NULL);		
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_year_start), m_start_year);
	
	//Times
	//start time
	label_start_time =gtk_label_new("Start Time: ");	
	
	spin_button_start_hour = gtk_spin_button_new(adjustment_start_hour, 1.0, 0);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_start_hour), m_start_hour);
	g_signal_connect(GTK_SPIN_BUTTON(spin_button_start_hour), "value_changed", G_CALLBACK(callbk_spin_hour_start), NULL);	
		
	spin_button_start_min = gtk_spin_button_new(adjustment_start_min, 1.0, 0);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_start_min), m_start_min);	
	g_signal_connect(GTK_SPIN_BUTTON(spin_button_start_min), "value_changed", G_CALLBACK(callbk_spin_min_start), NULL);
		
	//end time
	label_end_time =gtk_label_new("End Time: ");	
	
	spin_button_end_hour = gtk_spin_button_new(adjustment_end_hour, 1.0, 0);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_end_hour), m_end_hour);
	g_signal_connect(GTK_SPIN_BUTTON(spin_button_end_hour), "value_changed", G_CALLBACK(callbk_spin_hour_end), NULL);
	
	spin_button_end_min = gtk_spin_button_new(adjustment_end_min, 1.0, 0);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_end_min), m_end_min);
	g_signal_connect(GTK_SPIN_BUTTON(spin_button_end_min), "value_changed", G_CALLBACK(callbk_spin_min_end), NULL);
		
	// check button allday
	check_button_allday = gtk_check_button_new_with_label("Is All Day");
	g_signal_connect_swapped(GTK_CHECK_BUTTON(check_button_allday), "toggled",
							 G_CALLBACK(callbk_check_button_allday_toggled), check_button_allday);
	g_object_set_data(G_OBJECT(check_button_allday), "cb_allday_spin_start_hour_key", spin_button_start_hour);
	g_object_set_data(G_OBJECT(check_button_allday), "cb_allday_spin_start_min_key", spin_button_start_min);
	g_object_set_data(G_OBJECT(check_button_allday), "cb_allday_spin_end_hour_key", spin_button_end_hour);
	g_object_set_data(G_OBJECT(check_button_allday), "cb_allday_spin_end_min_key", spin_button_end_min);
		
	check_button_isyearly = gtk_check_button_new_with_label("Is Yearly");
	check_button_priority = gtk_check_button_new_with_label("Is High Priority");
	
	g_object_set_data(G_OBJECT(button_add_event), "dialog-key", dialog);

	g_object_set_data(G_OBJECT(button_add_event), "entry-summary-key", entry_summary);
	g_object_set_data(G_OBJECT(button_add_event), "entry-location-key", entry_location);	
	g_object_set_data(G_OBJECT(button_add_event), "entry-description-key", entry_description);
	
	//need to capture spin button values in case these are typed
	
	g_object_set_data(G_OBJECT(button_add_event), "spin-start-hour-key", spin_button_start_hour);
	g_object_set_data(G_OBJECT(button_add_event), "spin-start-min-key", spin_button_start_min);
	g_object_set_data(G_OBJECT(button_add_event), "spin-end-hour-key", spin_button_end_hour);
	g_object_set_data(G_OBJECT(button_add_event), "spin-end-min-key", spin_button_end_min);
	
		
	g_object_set_data(G_OBJECT(button_add_event), "spin-day-start-key", spin_button_day_start);	
	g_object_set_data(G_OBJECT(button_add_event), "spin-year-start-key", spin_button_year_start);	
	
	g_object_set_data(G_OBJECT(button_add_event), "check-button-allday-key", check_button_allday);	
	g_object_set_data(G_OBJECT(button_add_event), "check-button-isyearly-key", check_button_isyearly);
	g_object_set_data(G_OBJECT(button_add_event), "check-button-priority-key", check_button_priority);
		
	
	gtk_grid_attach(GTK_GRID(grid), label_summary, 1, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), entry_summary, 2, 1, 3, 1);
	
	gtk_grid_attach(GTK_GRID(grid), label_description, 1, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), entry_description, 2, 2, 3, 1);
	
	gtk_grid_attach(GTK_GRID(grid), label_location, 1, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), entry_location, 2, 3, 3, 1);
	
	gtk_grid_attach(GTK_GRID(grid), label_spacer1,       1, 4, 3, 1);
	//start date
	gtk_grid_attach(GTK_GRID(grid), label_date_start,       1, 5, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), spin_button_day_start,  2, 5, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), dropdown_month_start,    3, 5, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), spin_button_year_start,  4, 5, 1, 1);
		
	gtk_grid_attach(GTK_GRID(grid), label_spacer2,       1, 6, 3, 1);
	
	//start time
	gtk_grid_attach(GTK_GRID(grid), label_start_time,       1, 9, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), spin_button_start_hour,  2, 9, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), spin_button_start_min,   3, 9, 1, 1);
	//end time
	gtk_grid_attach(GTK_GRID(grid), label_end_time,        1, 10, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), spin_button_end_hour,  2, 10, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), spin_button_end_min,   3, 10, 1, 1);
	
	gtk_grid_attach(GTK_GRID(grid), label_spacer4,       1, 11, 3, 1);
	
	gtk_grid_attach(GTK_GRID(grid), check_button_allday,        1, 12, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), check_button_isyearly,      2, 12, 1, 1);  
    gtk_grid_attach(GTK_GRID(grid), check_button_priority,      3, 12, 1, 1);
   
    gtk_grid_attach(GTK_GRID(grid), label_spacer5,       1, 13, 3, 1);

	gtk_grid_attach(GTK_GRID(grid), button_add_event,  1, 14, 4, 1);

    gtk_window_set_child (GTK_WINDOW (dialog), grid);	
	gtk_window_present(GTK_WINDOW(dialog));	
	    
}

//=====================================================================
static void callbk_day_events_dialog(GtkButton *button, gpointer  user_data)
{	
	g_print("callbk_day_events_dialog\n");
	GtkWindow *window =user_data;		
	GtkWidget *dialog = g_object_get_data(G_OBJECT(button), "dialog-key");	
	gtk_window_destroy(GTK_WINDOW(dialog));

}

//======================================================================

static void callbk_update_event(GtkButton *button, gpointer user_data)
{
	GtkWidget *window = user_data;
	GtkWidget *calendar = g_object_get_data(G_OBJECT(window), "window-calendar-key");	
	GtkWidget *label_date =g_object_get_data(G_OBJECT(window), "window-label-date-key");
	
	GtkWidget *dialog = g_object_get_data(G_OBJECT(button), "dialog-key");
	
	GtkEntryBuffer *buffer_summary;
	GtkWidget *entry_summary = g_object_get_data(G_OBJECT(button), "entry-summary-key");
	
	GtkEntryBuffer *buffer_location;
	GtkWidget *entry_location = g_object_get_data(G_OBJECT(button), "entry-location-key");

	GtkEntryBuffer *buffer_description;
	GtkWidget *entry_description = g_object_get_data(G_OBJECT(button), "entry-description-key");

	GtkWidget *check_button_allday = g_object_get_data(G_OBJECT(button), "check-button-allday-key");
	
	GtkWidget *check_button_isyearly = g_object_get_data(G_OBJECT(button), "check-button-isyearly-key");
	GtkWidget *check_button_priority = g_object_get_data(G_OBJECT(button), "check-button-priority-key");
	
	GtkWidget *spin_button_day_start = g_object_get_data(G_OBJECT(button), "spin-day-start-key");
	GtkWidget *spin_button_year_start= g_object_get_data(G_OBJECT(button), "spin-year-start-key");
	
	GtkWidget *spin_button_start_hour = g_object_get_data(G_OBJECT(button), "spin-start-hour-key");
	GtkWidget *spin_button_start_min = g_object_get_data(G_OBJECT(button), "spin-start-min-key");
	GtkWidget *spin_button_end_hour = g_object_get_data(G_OBJECT(button), "spin-end-hour-key");
	GtkWidget *spin_button_end_min = g_object_get_data(G_OBJECT(button), "spin-end-min-key");
		
	m_start_day= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_day_start));
	m_start_year= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_year_start));
		
	m_summary="";	
	guint16 summary_str_len =0; //check for empty entry
	
	summary_str_len = gtk_entry_get_text_length(GTK_ENTRY(entry_summary));
	
	if(summary_str_len ==0)
	{
	m_summary =" Unknown event";
	} //if len
	else
	{
	buffer_summary = gtk_entry_get_buffer(GTK_ENTRY(entry_summary));
	m_summary = gtk_entry_buffer_get_text(buffer_summary);	
	char* summary = g_strdup(m_summary);//duplicate as m_summary const
	m_summary=trim_whitespace(summary);	
	m_summary = remove_semicolons(m_summary);
	m_summary = remove_commas(m_summary);
	m_summary =remove_punctuations(m_summary);		
	} //else
		
	//m_description	
	buffer_description = gtk_entry_get_buffer(GTK_ENTRY(entry_description));
	m_description = gtk_entry_buffer_get_text(buffer_description);
	
	char* description = g_strdup(m_description);//duplicate as const
	m_description=trim_whitespace(description);
	m_description = remove_semicolons(m_description);
	m_description = remove_commas(m_description);
	m_description =remove_punctuations(m_description);
	
	buffer_location = gtk_entry_get_buffer(GTK_ENTRY(entry_location));
	m_location = gtk_entry_buffer_get_text(buffer_location);
	
	char* location = g_strdup(m_location);//duplicate as const	
	m_location=trim_whitespace(location);
	m_location = remove_semicolons(m_location);
	m_location = remove_commas(m_location);
	m_location =remove_punctuations(m_location);
		
	m_is_allday = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_allday));	
	m_is_yearly = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_isyearly));	
	m_priority = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_priority));
			
	//capture typed values
	 m_start_day= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_day_start));
	 m_start_year= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_year_start));
			 
	 m_start_hour= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_start_hour));
	 m_start_min= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_start_min));
	 m_end_hour= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_end_hour));
	 m_end_min= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_end_min));
	 
	if (m_is_allday) 
	{
		m_start_hour=0; //sorting to top
		m_start_min=0;
		m_end_hour=0;
		m_end_min=0;
	 }
	
	
	//no multiday
	m_end_day =m_start_day;
	m_end_month=m_start_month;
	m_end_year=m_start_year;
	
	g_object_set(selected_evt, "summary", g_strdup(m_summary), NULL);
	g_object_set(selected_evt, "location", g_strdup(m_location), NULL);
	g_object_set(selected_evt, "description", g_strdup(m_description), NULL);
	g_object_set(selected_evt, "startyear", m_start_year, NULL);
	g_object_set(selected_evt, "startmonth", m_start_month, NULL);
	g_object_set(selected_evt, "startday", m_start_day, NULL);
	g_object_set(selected_evt, "starthour", m_start_hour, NULL);
	g_object_set(selected_evt, "startmin", m_start_min, NULL);
	g_object_set(selected_evt, "endyear", m_end_year, NULL); // to do
	g_object_set(selected_evt, "endmonth", m_end_month, NULL);
	g_object_set(selected_evt, "endday", m_end_day, NULL);
	g_object_set(selected_evt, "endhour", m_end_hour, NULL);
	g_object_set(selected_evt, "endmin", m_end_min, NULL);
	g_object_set(selected_evt, "isyearly", m_is_yearly, NULL);
	g_object_set(selected_evt, "isallday", m_is_allday, NULL);	
	g_object_set(selected_evt, "ispriority", m_priority, NULL);
		
	db_update_event(selected_evt);
	
	m_row_index = -1;
	m_id_selection = -1;
		
	
	//update calendar (also updates listbox)	
	set_marks_on_calendar(GTK_CALENDAR(calendar));
	update_calendar(GTK_CALENDAR(calendar), GTK_LABEL(label_date));
	gtk_window_destroy(GTK_WINDOW(dialog));		
	
}

//======================================================================
static void callbk_edit_event(GSimpleAction *action, GVariant *parameter,  gpointer user_data)
{
     
     //if(m_index<0) return;     
    if (m_id_selection == -1) return;
	
	GtkWindow *window = user_data;
	GtkWidget *dialog;
	
	dialog = gtk_window_new();
	gtk_window_set_title(GTK_WINDOW(dialog), "Update Event");
	
	GtkWidget *button_update;	
	GtkWidget *grid;
	
	GtkWidget *label_summary;
	GtkWidget *entry_summary;
		
	GtkWidget *label_description;
	GtkWidget *entry_description;
	
	GtkWidget *label_location;
	GtkWidget *entry_location;
	
	GtkEntryBuffer *buffer_summary;
	GtkEntryBuffer *buffer_location;
	GtkEntryBuffer *buffer_description; 
	
	GtkWidget *label_spacer1;
	GtkWidget *label_spacer2;
	GtkWidget *label_spacer3;
	GtkWidget *label_spacer4;
	GtkWidget *label_spacer5;
	GtkWidget *label_spacer6;
	
	//start date
	GtkWidget *label_start_date;
	GtkWidget *spin_button_start_day;
	GtkWidget *dropdown_month_start;			
	GtkWidget *spin_button_start_year;
	
	// Check buttons
	GtkWidget *check_button_allday;	
	GtkWidget *check_button_isyearly;
	GtkWidget *check_button_priority;
	
	//Adjustments
	// value,lower,upper,step_increment,page_increment,page_size
	GtkAdjustment *adjustment_day_start = gtk_adjustment_new(1.00, 0.0, 31.00, 1.0, 1.0, 0.0);	
	GtkAdjustment *adjustment_year_start = gtk_adjustment_new(2024.00, 0.0, 5024.00, 1.0, 1.0, 0.0);
	GtkAdjustment *adjustment_day_end = gtk_adjustment_new(1.00, 0.0, 31.00, 1.0, 1.0, 0.0);
	GtkAdjustment *adjustment_year_end = gtk_adjustment_new(2024.00, 0.0, 5000.00, 1.0, 1.0, 0.0);
	
	//start time
	GtkWidget *label_start_time;
	GtkWidget *spin_button_start_hour;	
	GtkWidget *spin_button_start_min;
	//end time
	GtkWidget *label_end_time;
	GtkWidget *spin_button_end_hour;	
	GtkWidget *spin_button_end_min;	
		
	GtkAdjustment *adjustment_start_hour = gtk_adjustment_new(1.00, 0.0, 23.00, 1.0, 1.0, 0.0);
	GtkAdjustment *adjustment_start_min= gtk_adjustment_new(1.00, 0.0, 59.00, 1.0, 1.0, 0.0);
	
	GtkAdjustment *adjustment_end_hour = gtk_adjustment_new(1.00, 0.0, 23.00, 1.0, 1.0, 0.0);
	GtkAdjustment *adjustment_end_min = gtk_adjustment_new(1.00, 0.0, 59.00, 1.0, 1.0, 0.0);
	
	GtkAdjustment *adjustment_reminder_hour = gtk_adjustment_new(1.00, 0.0, 23.00, 1.0, 1.0, 0.0);
	GtkAdjustment *adjustment_reminder_min= gtk_adjustment_new(1.00, 0.0, 59.00, 1.0, 1.0, 0.0);
	
	label_spacer1 = gtk_label_new("");
	label_spacer2 = gtk_label_new("");
	label_spacer3 = gtk_label_new("");
	label_spacer4 = gtk_label_new("");
	label_spacer5 = gtk_label_new("");
	label_spacer6 = gtk_label_new("");
	
	//m_current_month=m_start_month;
	
	button_update = gtk_button_new_with_label ("Update Selected Event");
	g_signal_connect (GTK_BUTTON (button_update),"clicked", G_CALLBACK (callbk_update_event), G_OBJECT (window));
	
	grid = gtk_grid_new();	
	gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	//get selected event
	gint evt_id = 0;
	gchar *summary_str = "";
	gchar *location_str = "";
	gchar *description_str = "";

	gint start_year = 0;
	gint start_month = 0;
	gint start_day = 0;
	gint start_hour = 0;
	gint start_min = 0;

	gint end_year = 0;
	gint end_month = 0;
	gint end_day = 0;
	gint end_hour = 0;
	gint end_min = 0;

	gint is_yearly = 0;
	gint is_allday = 0;
	gint is_priority = 0;	
	
	//if(selected_evt ==NULL) return; //to do
		
	g_object_get(selected_evt, "summary", &summary_str, NULL);
	g_object_get(selected_evt, "location", &location_str, NULL);
	g_object_get(selected_evt, "description", &description_str, NULL); // placeholders for future updates
	g_object_get (selected_evt, "startyear", &start_year, NULL);
	g_object_get (selected_evt, "startmonth", &start_month, NULL);
	g_object_get (selected_evt, "startday", &start_day, NULL);
	g_object_get(selected_evt, "starthour", &start_hour, NULL);
	g_object_get(selected_evt, "startmin", &start_min, NULL);
	g_object_get (selected_evt, "endyear", &end_year, NULL);
	g_object_get (selected_evt, "endmonth", &end_month, NULL);
	g_object_get (selected_evt, "endday", &end_day, NULL);
	g_object_get(selected_evt, "endhour", &end_hour, NULL);
	g_object_get(selected_evt, "endmin", &end_min, NULL);
	g_object_get(selected_evt, "isyearly", &is_yearly, NULL);
	g_object_get(selected_evt, "isallday", &is_allday, NULL);	
	g_object_get(selected_evt, "ispriority", &is_priority, NULL);
		
	m_summary = g_strdup(summary_str);
	m_location = g_strdup(location_str);
	m_description = g_strdup(description_str);
	
	m_start_year=start_year; 
	m_start_month=start_month;
	m_start_day=start_day;	
	m_start_hour = start_hour;
	m_start_min = start_min;
	
	m_end_year=end_year; 
	m_end_month=end_month;
	m_end_day=end_day;	
	m_end_hour = end_hour;
	m_end_min = end_min;
	
	m_is_yearly = is_yearly;
	m_is_allday = is_allday;	
	m_priority = is_priority;
		
	//summary
	label_summary = gtk_label_new("Summary: ");
	entry_summary = gtk_entry_new();
	gtk_entry_set_has_frame(GTK_ENTRY(entry_summary),TRUE); 
	gtk_entry_set_max_length(GTK_ENTRY(entry_summary), 100);
	buffer_summary = gtk_entry_buffer_new(m_summary, -1); // show 
	gtk_entry_set_buffer(GTK_ENTRY(entry_summary), buffer_summary);
	
	//description
	label_description = gtk_label_new("Description: ");
	entry_description = gtk_entry_new();
	gtk_entry_set_has_frame(GTK_ENTRY(entry_description),TRUE); 
	gtk_entry_set_max_length(GTK_ENTRY(entry_description), 100);
	buffer_description = gtk_entry_buffer_new(m_description, -1); // show description
	gtk_entry_set_buffer(GTK_ENTRY(entry_description), buffer_description);

	//location
	label_location = gtk_label_new("Location: ");
	entry_location = gtk_entry_new();
	gtk_entry_set_has_frame(GTK_ENTRY(entry_location),TRUE); 
	gtk_entry_set_max_length(GTK_ENTRY(entry_location), 25);
	buffer_location = gtk_entry_buffer_new(m_location, -1); // show location
	gtk_entry_set_buffer(GTK_ENTRY(entry_location), buffer_location);

	//start date
	label_start_date =gtk_label_new("Start Date: ");
	
	spin_button_start_day = gtk_spin_button_new(adjustment_day_start, 1.0, 0);	
	g_signal_connect(GTK_SPIN_BUTTON(spin_button_start_day), "value_changed", G_CALLBACK(callbk_spin_day_start), NULL);	
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_start_day), m_start_day);
	
	dropdown_month_start =gtk_drop_down_new_from_strings(month_strs);    
    g_signal_connect(GTK_DROP_DOWN(dropdown_month_start), "notify::selected", G_CALLBACK(callbk_dropdown_month_start), NULL);
    gtk_drop_down_set_selected(GTK_DROP_DOWN(dropdown_month_start),m_start_month-1);
	
	spin_button_start_year = gtk_spin_button_new(adjustment_year_start, 1.0, 0);
	g_signal_connect(GTK_SPIN_BUTTON(spin_button_start_year), "value_changed", G_CALLBACK(callbk_spin_year_start), NULL);		
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_start_year), m_start_year);
	
	//Times
	//start time
	label_start_time =gtk_label_new("Start Time: ");	
	
	spin_button_start_hour = gtk_spin_button_new(adjustment_start_hour, 1.0, 0);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_start_hour), m_start_hour);
	g_signal_connect(GTK_SPIN_BUTTON(spin_button_start_hour), "value_changed", G_CALLBACK(callbk_spin_hour_start), NULL);	
		
	spin_button_start_min = gtk_spin_button_new(adjustment_start_min, 1.0, 0);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_start_min), m_start_min);	
	g_signal_connect(GTK_SPIN_BUTTON(spin_button_start_min), "value_changed", G_CALLBACK(callbk_spin_min_start), NULL);
		
	//end time
	label_end_time =gtk_label_new("End Time: ");	
	
	spin_button_end_hour = gtk_spin_button_new(adjustment_end_hour, 1.0, 0);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_end_hour), m_end_hour); //end hour
	g_signal_connect(GTK_SPIN_BUTTON(spin_button_end_hour), "value_changed", G_CALLBACK(callbk_spin_hour_end), NULL);
	
	spin_button_end_min = gtk_spin_button_new(adjustment_end_min, 1.0, 0);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_end_min), m_end_min); //end min
	g_signal_connect(GTK_SPIN_BUTTON(spin_button_end_min), "value_changed", G_CALLBACK(callbk_spin_min_end), NULL);
	
	check_button_allday = gtk_check_button_new_with_label("Is All Day");
	gtk_check_button_set_active(GTK_CHECK_BUTTON(check_button_allday), m_is_allday);
	g_signal_connect_swapped(GTK_CHECK_BUTTON(check_button_allday), "toggled",
							 G_CALLBACK(callbk_check_button_allday_toggled), check_button_allday);
	
	
	if (m_is_allday)
	{
		gtk_widget_set_sensitive(spin_button_start_hour, FALSE);
		gtk_widget_set_sensitive(spin_button_start_min, FALSE);
		gtk_widget_set_sensitive(spin_button_end_hour, FALSE);
		gtk_widget_set_sensitive(spin_button_end_min, FALSE);
	}
	else
	{
		gtk_widget_set_sensitive(spin_button_start_hour, TRUE);
		gtk_widget_set_sensitive(spin_button_start_min, TRUE);
		gtk_widget_set_sensitive(spin_button_end_hour, TRUE);
		gtk_widget_set_sensitive(spin_button_end_min, TRUE);
	}
	
	
	g_object_set_data(G_OBJECT(check_button_allday), "cb_allday_spin_start_hour_key", spin_button_start_hour);
	g_object_set_data(G_OBJECT(check_button_allday), "cb_allday_spin_start_min_key", spin_button_start_min);
	g_object_set_data(G_OBJECT(check_button_allday), "cb_allday_spin_end_hour_key", spin_button_end_hour);
	g_object_set_data(G_OBJECT(check_button_allday), "cb_allday_spin_end_min_key", spin_button_end_min);
		
	
	check_button_isyearly = gtk_check_button_new_with_label("Is Yearly");
	check_button_priority = gtk_check_button_new_with_label("Is High Priority");
	
	gtk_check_button_set_active(GTK_CHECK_BUTTON(check_button_isyearly), m_is_yearly);	
	gtk_check_button_set_active(GTK_CHECK_BUTTON(check_button_priority), m_priority);
	
	g_object_set_data(G_OBJECT(button_update), "dialog-key", dialog);
	
	g_object_set_data(G_OBJECT(button_update), "entry-summary-key", entry_summary);
	g_object_set_data(G_OBJECT(button_update), "entry-location-key", entry_location);	
	g_object_set_data(G_OBJECT(button_update), "entry-description-key", entry_description);
		
	g_object_set_data(G_OBJECT(button_update), "spin-start-hour-key", spin_button_start_hour);
	g_object_set_data(G_OBJECT(button_update), "spin-start-min-key", spin_button_start_min);
	g_object_set_data(G_OBJECT(button_update), "spin-end-hour-key", spin_button_end_hour);
	g_object_set_data(G_OBJECT(button_update), "spin-end-min-key", spin_button_end_min);
	
	g_object_set_data(G_OBJECT(button_update), "spin-day-start-key", spin_button_start_day);	
	g_object_set_data(G_OBJECT(button_update), "spin-year-start-key", spin_button_start_year);	
		
	g_object_set_data(G_OBJECT(button_update), "check-button-allday-key", check_button_allday);	
	g_object_set_data(G_OBJECT(button_update), "check-button-isyearly-key", check_button_isyearly);
	g_object_set_data(G_OBJECT(button_update), "check-button-priority-key", check_button_priority);
	
	//grid layout
	gtk_grid_attach(GTK_GRID(grid), label_summary, 1, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), entry_summary, 2, 1, 3, 1);
	
	gtk_grid_attach(GTK_GRID(grid), label_description, 1, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), entry_description, 2, 2, 3, 1);
		
	gtk_grid_attach(GTK_GRID(grid), label_location, 1, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), entry_location, 2, 3, 3, 1);
	
	gtk_grid_attach(GTK_GRID(grid), label_spacer1,       1, 4, 3, 1);
	//start date
	gtk_grid_attach(GTK_GRID(grid), label_start_date,       1, 5, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), spin_button_start_day,  2, 5, 1, 1);	
	gtk_grid_attach(GTK_GRID(grid), dropdown_month_start,    3, 5, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), spin_button_start_year,  4, 5, 1, 1);	
	
	gtk_grid_attach(GTK_GRID(grid), label_spacer2,       1, 6, 3, 1);
		
	//start time
	gtk_grid_attach(GTK_GRID(grid), label_start_time,       1, 9, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), spin_button_start_hour,  2, 9, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), spin_button_start_min,   3, 9, 1, 1);
	//end time
	gtk_grid_attach(GTK_GRID(grid), label_end_time,        1, 10, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), spin_button_end_hour,  2, 10, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), spin_button_end_min,   3, 10, 1, 1);
	
	gtk_grid_attach(GTK_GRID(grid), label_spacer4,       1, 11, 3, 1);

	gtk_grid_attach(GTK_GRID(grid), check_button_allday,        1, 12, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), check_button_isyearly,      2, 12, 1, 1);  
    gtk_grid_attach(GTK_GRID(grid), check_button_priority,      3, 12, 1, 1);
   
    gtk_grid_attach(GTK_GRID(grid), label_spacer5,       1, 13, 3, 1);
	
	gtk_grid_attach(GTK_GRID(grid), button_update,  1, 14, 4, 1);

    gtk_window_set_child (GTK_WINDOW (dialog), grid);	
	gtk_window_present(GTK_WINDOW(dialog));   	
  
}
//======================================================================


static void callbk_delete_selected(GSimpleAction *action, GVariant *parameter,  gpointer user_data)
{
	
	GtkWindow *window =user_data;
	GtkWidget *calendar =g_object_get_data(G_OBJECT(window), "window-calendar-key");
	GtkWidget *label_date =g_object_get_data(G_OBJECT(window), "window-label-date-key");
	int selected_evt_id=0;
	g_object_get (selected_evt, "eventid", &selected_evt_id, NULL);	
	
	db_delete_row(selected_evt_id);
	m_row_index=-1; //used for delete selection
	m_id_selection=-1;
	
	//update listview day events	
	g_list_store_remove_all(m_store); // clear	
	GArray *evt_arry_day;	
	evt_arry_day = g_array_new(FALSE, FALSE, sizeof(CALENDAR_TYPE_EVENT)); // setup arraylist
	db_get_all_events_year_month_day(evt_arry_day, m_start_year,m_start_month, m_start_day);		
	display_event_array(evt_arry_day);
	g_array_free(evt_arry_day, FALSE); //clear the array 
	
	//update calendar
		
}

//======================================================================

static void callbk_confirm_delete_all(GtkButton *button, gpointer  user_data)
{	
	GtkWindow *window =user_data;	
	GtkWidget *calendar =g_object_get_data(G_OBJECT(window), "window-calendar-key");
	
	GtkWidget *dialog = g_object_get_data(G_OBJECT(button), "dialog-key");
	
	db_delete_all();
	
	//update listview day events	
	g_list_store_remove_all(m_store); // clear	
	GArray *evt_arry_day;	
	evt_arry_day = g_array_new(FALSE, FALSE, sizeof(CALENDAR_TYPE_EVENT)); // setup arraylist
	db_get_all_events_year_month_day(evt_arry_day, m_start_year,m_start_month, m_start_day);		
	display_event_array(evt_arry_day);
	g_array_free(evt_arry_day, FALSE); //clear the array 
		 		
	//custom_calendar_update(CUSTOM_CALENDAR(calendar));
	gtk_window_destroy(GTK_WINDOW(dialog));
}

//======================================================================
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
//Export ical file
//======================================================================

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
static void file_save_response (GObject *source, GAsyncResult *result, void *user_data)
{
  
  GtkFileDialog *dialog = GTK_FILE_DIALOG (source);  
  
  GtkWidget *window = g_object_get_data(G_OBJECT(dialog), "dialog-window-key");
 
  GFile *file;
  file = gtk_file_dialog_save_finish (dialog, result, NULL);
	  if (file)
	  {	 
	  char *file_name = g_file_get_path(file);	  
	  export_file(file_name);
	  }
}
//=====================================================================
void export_file(char *file_name) 
{
	GFile *file;	
	GFileOutputStream *file_stream;
	GDataOutputStream *data_stream;
	GError *err = NULL;
	
	file = g_file_new_for_path(file_name);

	file_stream = g_file_replace(file, 0,TRUE, G_FILE_CREATE_NONE, NULL, &err);
	    
	if (file_stream == NULL) {
                
				//gint errno = err->code;
				g_warning ("Error message = %s", err->message);
                g_error_free (err);
                g_print("Unable to open file: %s\n",file_name);
                g_object_unref (file);
                return;
        }

	data_stream = g_data_output_stream_new(G_OUTPUT_STREAM(file_stream));
	
	GArray *evt_arry =g_array_new(FALSE, FALSE, sizeof(CALENDAR_TYPE_EVENT));
	db_get_all_events(evt_arry);
	
	
	char *line = "";
	line = g_strconcat(line,"BEGIN:VCALENDAR\n",NULL);	
	g_data_output_stream_put_string(data_stream, line, NULL, NULL);

	for (int i = 0; i < evt_arry->len; i++)
	{		
		line="";
		gint evt_id = 0;
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
		gint is_multiday = 0;
		gint is_priority = 0;
		
		gint has_reminder = 0;
		gint reminder_hour = 0;
		gint reminder_min = 0;
		char* recurrence_str="RRULE:";

		CalendarEvent *evt = g_array_index(evt_arry, CalendarEvent *, i);

		g_object_get(evt, "eventid", &evt_id, NULL);
		g_object_get(evt, "summary", &summary_str, NULL);
		g_object_get(evt, "location", &location_str, NULL);
		g_object_get(evt, "description", &description_str, NULL);
		g_object_get(evt, "startyear", &start_year, NULL);
		g_object_get(evt, "startmonth", &start_month, NULL);
		g_object_get(evt, "startday", &start_day, NULL);
		g_object_get(evt, "starthour", &start_hour, NULL);
		g_object_get(evt, "startmin", &start_min, NULL);
		g_object_get(evt, "endyear", &end_year, NULL);
		g_object_get(evt, "endmonth", &end_month, NULL);
		g_object_get(evt, "endday", &end_day, NULL);
		g_object_get(evt, "endhour", &end_hour, NULL);
		g_object_get(evt, "endmin", &end_min, NULL);
		g_object_get(evt, "isyearly", &is_yearly, NULL);
		g_object_get(evt, "isallday", &is_allday, NULL);		
		g_object_get(evt, "ispriority", &is_priority, NULL);
			
	
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
		
	}//for evt_arry
	
	line ="";
	line = g_strconcat(line,"END:VCALENDAR\n",NULL);
	g_data_output_stream_put_string(data_stream, line, NULL, NULL);

	g_object_unref(data_stream);
	g_object_unref(file_stream);
	g_object_unref(file);
		
}

//======================================================================
// import ical
//======================================================================

static void file_chooser_response (GObject *source, GAsyncResult *result, void *user_data)
{
  //GtkWidget *window = user_data;
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
// import ical
//======================================================================

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
	gtk_file_dialog_open (dialog, NULL, NULL, file_chooser_response, NULL); //no longer signal based
	
	g_object_set_data(G_OBJECT(dialog), "dialog-window-key",window);	
	g_object_unref (dialog);
	
}

//======================================================================
// Import ical file
//======================================================================
void import_ical_file(gpointer user_data) 
{
	
		
	GtkWidget *window = user_data; //need window to get calendar
	GtkWidget *calendar = g_object_get_data(G_OBJECT(window), "window-calendar-key");
	GtkWidget *label_date = g_object_get_data(G_OBJECT(window), "window-label-date-key");
	//Two stage parser
	//Stage 1 checks for timezone
	//Stage2 extracts event details
	
	
	GFile *file;
	//GFileInputStream creates a stream of input that you can use to read data from a file
	GFileInputStream *file_stream = NULL;
	GDataInputStream *input_stream = NULL;	
	file = g_file_new_for_path(m_file_name);
	//file = g_file_new_for_path("events.ical");
	
	file_stream = g_file_read(file, NULL, NULL);
	if (!file_stream)
	{
		g_print("CRITICAL: error: unable to open backup file called example.ics\n");
		//return;
		return;
	}
	else {
		//g_print("successfully opened: %s\n", file_name);
	}

	input_stream = g_data_input_stream_new(G_INPUT_STREAM(file_stream));
	
	char *key="";     
    char *value="";
    
	char *summary_str = "";
	char *event_number_str="";
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
								
				db_insert_event(evt); //insert event into database	
				
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
				
				db_insert_event(evt); //insert event into database	
				
				//reset is_yearly for next event
				is_yearly=0;
				is_priority=0;
				is_allday=0;			
				
			}	//VEVENT END	
			
			g_free(line2);
			
		} //while parse
		
	} //else no timezone
   	
   	
   	m_id_selection = -1; //no selection
   	
   	//update calendar (also updates listbox)	
	set_marks_on_calendar(GTK_CALENDAR(calendar));
	update_calendar(GTK_CALENDAR(calendar), GTK_LABEL(label_date));
	
   	
    g_object_unref(file);   	
	g_object_unref (input_stream);
	g_object_unref (file_stream);
	//return true;
   
}

//======================================================================
static void callbk_about(GSimpleAction * action, GVariant *parameter, gpointer user_data){


	GtkWidget *window = user_data;
	
	const gchar *authors[] = {"Alan Crispin", NULL};
	GtkWidget *about_dialog;
	about_dialog = gtk_about_dialog_new();
	gtk_window_set_transient_for(GTK_WINDOW(about_dialog),GTK_WINDOW(window));
	gtk_widget_set_size_request(about_dialog, 200,200);
    gtk_window_set_modal(GTK_WINDOW(about_dialog),TRUE);
	gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(about_dialog), "Talk Calendar");
	gtk_about_dialog_set_version (GTK_ABOUT_DIALOG(about_dialog), "Version 0.4.0");
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(about_dialog),"Copyright © 2025");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(about_dialog),"Speaking Calendar (Diphone Synthesizer)");
	gtk_about_dialog_set_license_type (GTK_ABOUT_DIALOG(about_dialog), GTK_LICENSE_LGPL_2_1);
	gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(about_dialog),"https://github.com/crispinprojects/");
	gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(about_dialog),"Talk Calendar Website");
	gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(about_dialog), authors);
	//gtk_about_dialog_set_logo_icon_name(GTK_ABOUT_DIALOG(about_dialog), NULL);	
	gtk_about_dialog_set_logo_icon_name(GTK_ABOUT_DIALOG(about_dialog), "gtk-about");
	gtk_widget_set_visible (about_dialog, TRUE);		
	
}

//======================================================================
// Speaking
//======================================================================

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
static void play_audio_async (GTask *task,
                          gpointer object,
                          gpointer task_data,
                          GCancellable *cancellable)
{
    m_talking=TRUE; //stop any new speaking 
    char* raw_file_path =task_data;        
    tsm(raw_file_path); //time scale modification
    //m_sample_rate=32000; //tsm reduces time scale by 0.5
    set_sample_rate(m_sample_rate);    
    //g_print("sample_rate = %d\n",m_sample_rate);    
    raw_player(raw_file_path); //using my own player (PERIODS=1)   
    g_task_return_boolean(task, TRUE);
    
}
//======================================================================

static void play_diphone_list(GList *diphone_list)
{	
	gpointer diphone_list_pointer;
	gchar* diphone_str;		
	gint diphone_number  =g_list_length(diphone_list);
	
	//create diphone array using list length
	unsigned char *diphone_arrays[diphone_number]; 
	unsigned int diphone_arrays_sizes[diphone_number];
		
	//load diphone arrays
	for(int i=0; i <diphone_number; i++)
	{
		diphone_list_pointer=g_list_nth_data(diphone_list,i);
		diphone_str=(gchar *)diphone_list_pointer;	
		//g_print("play_diphone_list: diphone = %s\n",diphone_str);
		diphone_arrays[i] = load_diphone_arry(diphone_str);	
		diphone_arrays_sizes[i]=load_diphone_len(diphone_str);		
	}	
	
	//concatenate using raw cat
	unsigned char *data = rawcat(diphone_arrays, diphone_arrays_sizes, diphone_number);	
	unsigned int data_len = get_merge_size(diphone_arrays_sizes,diphone_number);	
    	
	gchar* raw_file_path ="/tmp/talk.raw";
	save_raw_file(raw_file_path, data, data_len);
	    
	GTask* task = g_task_new(NULL, NULL, task_callbk, NULL);
	g_task_set_task_data (task,raw_file_path,NULL);
    g_task_run_in_thread(task, play_audio_async);     
    g_object_unref(task);
	
	//clean up 	
	free(data);	//prevent memory leak
		
}


//======================================================================
// Concatentation
//======================================================================

unsigned char *rawcat(unsigned char *arrys[], unsigned int arry_size[], int arry_count) {
		
	
	if (arry_count<2) return NULL;	
	
	unsigned int  total_samples=0;
	for (int c = 0; c < arry_count; c++) 
	{  
    unsigned int count =arry_size[c]; 
    total_samples=total_samples+count;	
    }        
	unsigned char *data = (unsigned char*)malloc(total_samples * sizeof(unsigned char));
	
	unsigned int offset=0;
	for(int k=0; k<arry_count; k++)
	{
		//loop through each arry	
		for(int i = 0; i < arry_size[k]; i++) 
		{		
		data[i+offset]=arrys[k][i];
		}		
		offset =offset+arry_size[k];
	}//k kount
	return data;
}
//=====================================================================
unsigned int get_merge_size(unsigned int sizes_arry[], int arry_size){
	
	unsigned int total_samples=0;
	for (int i = 0; i < arry_size; i++) 
	{  
    unsigned int count =sizes_arry[i]; 
    total_samples=total_samples+count;	
    }
	return total_samples;
}
//=====================================================================

//======================================================================
// Speak time
//======================================================================

static void speak_time(gint hour, gint min) 
{	
	if(m_talk==0) return;
	if (m_talking ==TRUE) return;
	
	//g_print("speak time = %d:%d\n",hour,min);
			
	GList *diphone_list=NULL;
	GList* time_list=NULL;
	GList* hour_list=NULL;
	GList* min_list=NULL;	
	
	gchar *time_str = "";
	gchar *hour_str = "";
	gchar *min_str = "";		
	gchar *ampm_str = "";
	
	diphone_list =g_list_concat(word_to_diphones("the"),word_to_diphones("time"));
	diphone_list =g_list_concat(diphone_list,word_to_diphones("is"));	
    diphone_list =g_list_concat(diphone_list,word_to_diphones("pause"));
	
	if (m_12hour_format)
			{
				
				if(hour ==0) //12am midnight
				{		
				ampm_str = "amm";				
				hour_list =convert_number_to_diphone_list(12);		
				}
								
				if (hour >= 13 && hour <= 23)
				{
					int s_hour = hour - 12;
					ampm_str = "pmm";					
					hour_list =convert_number_to_diphone_list(s_hour);
				}
			   if(hour == 12)
				{
					ampm_str = "pmm";					
					hour_list =convert_number_to_diphone_list(hour);
				}
			   if(hour <12 && hour >0)
				{
					ampm_str = "amm";					
					hour_list =convert_number_to_diphone_list(hour);
				}
			} // 12
			if(!m_12hour_format) //24 hours
			{
				hour_list =convert_number_to_diphone_list(hour);
			} // 24

			if (min > 0 && min < 10)
			{				
			 	GList* zero_list=convert_number_to_diphone_list(0);
				GList* zero_min_list =convert_number_to_diphone_list(min);
		        min_list =g_list_concat(zero_list,zero_min_list);
			}
			else if(min >=10)
			{
				min_list =convert_number_to_diphone_list(min);
			}

	if (m_12hour_format) {	
		
		time_list =g_list_concat(hour_list, word_to_diphones("pau"));
		time_list =g_list_concat(time_list,min_list);
		time_list =g_list_concat(time_list, word_to_diphones("pau"));
	    time_list =g_list_concat(time_list,word_to_diphones(ampm_str));		   
	    time_list =g_list_concat(time_list, word_to_diphones("pau"));	
	}
	else {
		time_list =g_list_concat(hour_list, word_to_diphones("pau"));
		time_list =g_list_concat(time_list,min_list);
	}
	  	
	diphone_list =g_list_concat(diphone_list,time_list);
	play_diphone_list(diphone_list);	
	g_list_free(diphone_list);
		
}
//======================================================================

static void callbk_speaktime(GSimpleAction * action, GVariant *parameter, gpointer user_data)
{	
	GtkWidget *window = user_data;
	
	GDateTime *dt = g_date_time_new_now_local(); 
	gint hour =g_date_time_get_hour(dt);	
	gint min= g_date_time_get_minute(dt);	
	
	if(m_talking==FALSE) speak_time(hour,min);	
			
    g_date_time_unref (dt);
}

//=====================================================================

static void callbk_speak(GSimpleAction* action, GVariant *parameter,gpointer user_data)
{	
	if(m_talking == FALSE) speak_events();	
}

//=====================================================================

//======================================================================
// Diphone Speaking 
//======================================================================

GList* convert_date_to_weekday_diphone_list(int day, int month, int year) {
	
	//char* weekday_str="";
	GList* result =NULL;
	
	GDate* day_date;
	day_date = g_date_new_dmy(day, month, year);
	GDateWeekday weekday =g_date_get_weekday(day_date);
	
	
	 switch (weekday) {
		case G_DATE_MONDAY:		
		result =word_to_diphones("monday");			
		break;
		case G_DATE_TUESDAY:		
		result =word_to_diphones("tuesday");		
		break;
		case G_DATE_WEDNESDAY:		
		result =word_to_diphones("wednesday");			
		break;
		case G_DATE_THURSDAY:		
		result =word_to_diphones("thursday");			
		break;
		case G_DATE_FRIDAY:		
		result =word_to_diphones("friday");			
		break;
		case G_DATE_SATURDAY:	
		result =word_to_diphones("saturday");		
		break;
		case G_DATE_SUNDAY:	
		result =word_to_diphones("sunday");			
		break;
		default:
		//Unknown day of week		
		result =word_to_diphones("day");
		//g_print("weekday = unkown\n");	
		break;
	    }//switch dow
	
	return result;
}

//======================================================================
// Convert day number to diphone list
//======================================================================
GList* convert_day_number_to_diphone_list(int day_number) {
	
	GList* result =NULL;
	
	switch (day_number) {
		case 1:
		result =word_to_diphones("first");
		break;		
		case 2:
		result =word_to_diphones("second");
		break;
		case 3:
		//g_print("third selected\n");
		result =word_to_diphones("third");
		
		break;
		case 4:
		result =word_to_diphones("fourth");
		break;
		case 5:
		result =word_to_diphones("fifth");
		break;
		case 6:
		result =word_to_diphones("sixth");
		break;
		case 7:
		result =word_to_diphones("seventh");
		break;
		case 8:
		result =word_to_diphones("eighth");
		break;
		case 9:
		result =word_to_diphones("ninth");
		break;
		case 10:
		result =word_to_diphones("tenth");
		break;
		case 11:
		result =word_to_diphones("eleventh");
		break;
		case 12:		
		result =word_to_diphones("twelfth");	
		break;
		case 13:		
		result =word_to_diphones("thirteenth");
		break;
		case 14:			
		result =word_to_diphones("fourteenth");	
		break;
		case 15:		
		result =word_to_diphones("fifteenth");
		break;
		case 16:		
		result =word_to_diphones("sixteenth");
		break;
		case 17:		
		result =word_to_diphones("seventeenth");
		break;
		case 18:		
		result =word_to_diphones("eighteenth");
		break;
		case 19:		
		result =word_to_diphones("nineteenth");
		break;
		case 20:		
		result =word_to_diphones("twentieth");
		break;
		case 21:		
		result =g_list_concat(word_to_diphones("twenty"),word_to_diphones("first"));				
		break;
		case 22:		
		result =g_list_concat(word_to_diphones("twenty"),word_to_diphones("second"));		
		break;
		case 23:
		result =g_list_concat(word_to_diphones("twenty"),word_to_diphones("third"));	
		break;
		case 24:		
		result =g_list_concat(word_to_diphones("twenty"),word_to_diphones("fourth"));
		break;
		case 25:		
		result =g_list_concat(word_to_diphones("twenty"),word_to_diphones("fifth"));
		break;
		case 26:		
		result =g_list_concat(word_to_diphones("twenty"),word_to_diphones("sixth"));
		break;
		case 27:		
		result =g_list_concat(word_to_diphones("twenty"),word_to_diphones("seventh"));
		break;
		case 28:		
		result =g_list_concat(word_to_diphones("twenty"),word_to_diphones("eighth"));
		break;
		case 29:		
		result =g_list_concat(word_to_diphones("twenty"),word_to_diphones("ninth"));
		break;
		case 30:		
		result =word_to_diphones("thirtieth");
		break;
		case 31:
		result =g_list_concat(word_to_diphones("thirty"),word_to_diphones("first"));		
		break;
		default:
		//Unknown ordinal
		result =word_to_diphones("zero");
		break;		
	  } //day switch      
		
	return result;	
}

//======================================================================
// Convert month to diphone list
//======================================================================
GList* convert_month_to_diphone_list(int month) {
	
	GList* result =NULL;
	
	switch(month) {
	case 1:		
		result =word_to_diphones("january");
		break;
	case 2:			
		result =word_to_diphones("february");	
		break;
	case 3:		
		result =word_to_diphones("march");
		break; 
	case 4:
		result =word_to_diphones("april");
		break; 
	case 5:		
		result =word_to_diphones("may");
		break;
	case 6:		
		result =word_to_diphones("june");
		break; 
	case 7:		
		result =word_to_diphones("july");
		break;
	case 8:		
		result =word_to_diphones("august");
		break;
	case 9:		
		result =word_to_diphones("september");
		break;
	case 10:		
		result =word_to_diphones("october");
		break;
	case 11:		
		result =word_to_diphones("november");
		break; 
	case 12:		
		result =word_to_diphones("december");
		break; 
	default:
		result =word_to_diphones("month");
	}

	return result;
}

//======================================================================
// Convert upcoming event number to diphone list
//======================================================================
GList* get_upcoming_number_diphone_list(int number) {
	
	GList* result =NULL;
	
	if (number ==0) {	
	GList *noevents_list=NULL;    
	noevents_list = word_to_diphones("no");   
	noevents_list = g_list_concat(noevents_list,word_to_diphones("upcoming")); 
	noevents_list = g_list_concat(noevents_list,word_to_diphones("events")); 
	result =noevents_list;	
	} //if
	
	else if(number ==1){		
		result =g_list_concat(word_to_diphones("one"),word_to_diphones("upcoming"));
		result =g_list_concat(result,word_to_diphones("event"));
	}
	else if(number ==2){		
		result =g_list_concat(word_to_diphones("two"),word_to_diphones("upcoming"));
		result =g_list_concat(result,word_to_diphones("events"));
	}
	else if(number ==3){
		 result =g_list_concat(word_to_diphones("three"),word_to_diphones("upcoming"));
		 result =g_list_concat(result,word_to_diphones("events")); 
	}
	else if(number ==4){
		result =g_list_concat(word_to_diphones("four"),word_to_diphones("upcoming")); 
		result =g_list_concat(result,word_to_diphones("events"));
	}
	else if(number ==5){ 
		result =g_list_concat(word_to_diphones("five"),word_to_diphones("upcoming"));
		result =g_list_concat(result,word_to_diphones("events"));	
	}		
	else {
	result =g_list_concat(word_to_diphones("many"),word_to_diphones("upcoming"));
	result =g_list_concat(result,word_to_diphones("events"));
	}
	
	return result;
}

//======================================================================
// convert number to diphone list (time)
//======================================================================
GList* convert_number_to_diphone_list(int number) {
	
	GList* result =NULL;
	
	switch (number) {		
		case 1:
		result =word_to_diphones("one");
		break;		
		case 2:
		result =word_to_diphones("two");
		break;
		case 3:
		result =word_to_diphones("three");
		break;
		case 4:
		result =word_to_diphones("four");
		break;
		case 5:
		result =word_to_diphones("five");
		break;
		case 6:
		result =word_to_diphones("six");
		break;
		case 7:
		result =word_to_diphones("seven");
		break;
		case 8:
		result =word_to_diphones("eight");
		break;
		case 9:
		result =word_to_diphones("nine");
		break;
		case 10:
		result =word_to_diphones("ten");
		break;
		case 11:
		result =word_to_diphones("eleven");
		break;
		case 12:
		result =word_to_diphones("twelve");
		break;
		case 13:
		result =word_to_diphones("thirteen");
		break;
		case 14:
		result =word_to_diphones("fourteen");
		break;
		case 15:
		result =word_to_diphones("fifteen");
		break;
		case 16:
		result =word_to_diphones("sixteen");
		break;
		case 17:
		result =word_to_diphones("seventeen");
		break;
		case 18:
		result =word_to_diphones("eighteen");
		break;
		case 19:
		result =word_to_diphones("nineteen");
		break;
		case 20:
		result =word_to_diphones("twenty");
		break;
		case 21:
		result =g_list_concat(word_to_diphones("twenty"),word_to_diphones("one"));
		break;
		case 22:
		result =g_list_concat(word_to_diphones("twenty"),word_to_diphones("two"));
		break;
		case 23:
		result =g_list_concat(word_to_diphones("twenty"),word_to_diphones("three"));
		break;
		case 24:
		result =g_list_concat(word_to_diphones("twenty"),word_to_diphones("four"));
		break;
		case 25:
		result =g_list_concat(word_to_diphones("twenty"),word_to_diphones("five"));
		break;
		case 26:
		result =g_list_concat(word_to_diphones("twenty"),word_to_diphones("six"));
		break;
		case 27:
		result =g_list_concat(word_to_diphones("twenty"),word_to_diphones("seven"));
		break;
		case 28:
		result =g_list_concat(word_to_diphones("twenty"),word_to_diphones("eight"));
		break;
		case 29:
		result =g_list_concat(word_to_diphones("twenty"),word_to_diphones("nine"));
		break;
		case 30:
		result =word_to_diphones("thirty");
		break;
		case 31:
		result =g_list_concat(word_to_diphones("thirty"),word_to_diphones("one"));
		break;
		case 32:
		result =g_list_concat(word_to_diphones("thirty"),word_to_diphones("two"));
		break;
		case 33:
		result =g_list_concat(word_to_diphones("thirty"),word_to_diphones("three"));
		break;
		case 34:
		result =g_list_concat(word_to_diphones("thirty"),word_to_diphones("four"));
		break;
		case 35:
		result =g_list_concat(word_to_diphones("thirty"),word_to_diphones("five"));
		break;
		case 36:
		result =g_list_concat(word_to_diphones("thirty"),word_to_diphones("six"));
		break;
		case 37:
		result =g_list_concat(word_to_diphones("thirty"),word_to_diphones("seven"));
		break;
		case 38:
		result =g_list_concat(word_to_diphones("thirty"),word_to_diphones("eight"));
		break;
		case 39:
		result =g_list_concat(word_to_diphones("thirty"),word_to_diphones("nine"));
		break;
		case 40:
		result =word_to_diphones("forty");
		break;
		case 41:
		result =g_list_concat(word_to_diphones("forty"),word_to_diphones("one"));
		break;
		case 42:
		result =g_list_concat(word_to_diphones("forty"),word_to_diphones("two"));
		break;
		case 43:
		result =g_list_concat(word_to_diphones("forty"),word_to_diphones("three"));
		break;
		case 44:
		result =g_list_concat(word_to_diphones("forty"),word_to_diphones("four"));
		break;
		case 45:
		result =g_list_concat(word_to_diphones("forty"),word_to_diphones("five"));
		break;
		case 46:
		result =g_list_concat(word_to_diphones("forty"),word_to_diphones("six"));
		break;
		case 47:
		result =g_list_concat(word_to_diphones("forty"),word_to_diphones("seven"));
		break;
		case 48:
		result =g_list_concat(word_to_diphones("forty"),word_to_diphones("eight"));
		break;
		case 49:
		result =g_list_concat(word_to_diphones("forty"),word_to_diphones("nine"));
		break;
		case 50:
		result =word_to_diphones("fifty");
		break;
		case 51:
		result =g_list_concat(word_to_diphones("fifty"),word_to_diphones("one"));
		break;
		case 52:
		result =g_list_concat(word_to_diphones("fifty"),word_to_diphones("two"));
		break;
		case 53:
		result =g_list_concat(word_to_diphones("fifty"),word_to_diphones("three"));
		break;
		case 54:
		result =g_list_concat(word_to_diphones("fifty"),word_to_diphones("four"));
		break;
		case 55:
		result =g_list_concat(word_to_diphones("fifty"),word_to_diphones("five"));
		break;
		case 56:
		result =g_list_concat(word_to_diphones("fifty"),word_to_diphones("six"));
		break;
		case 57:
		result =g_list_concat(word_to_diphones("fifty"),word_to_diphones("seven"));
		break;
		case 58:
		result =g_list_concat(word_to_diphones("fifty"),word_to_diphones("eight"));
		break;
		case 59:
		result =g_list_concat(word_to_diphones("fifty"),word_to_diphones("nine"));
		break;
		
		default:		
		result =word_to_diphones("zero");
		break;		
				
	}
		
	return result;
}

//======================================================================
// speak events
//======================================================================
static void speak_events() {

	
	if(m_talk==0) return;
	if (m_talking ==TRUE) return; //already talking
		
	int day_events_number=0;
	GList *diphone_list=NULL;
		
	GList *weekday_list=convert_date_to_weekday_diphone_list(m_start_day, m_start_month, m_start_year);
		
	GList *day_number_list =convert_day_number_to_diphone_list(m_start_day);	
	
	GList *month_list=convert_month_to_diphone_list(m_start_month);
	
	diphone_list =g_list_concat(diphone_list,weekday_list);
	diphone_list =g_list_concat(diphone_list, word_to_diphones("pause1"));
	diphone_list =g_list_concat(diphone_list,day_number_list);
	//diphone_list =g_list_concat(diphone_list, word_to_diphones("pause"));
	diphone_list =g_list_concat(diphone_list,month_list);
	diphone_list =g_list_concat(diphone_list, word_to_diphones("pause1"));
    //diphone_list =g_list_concat(diphone_list, word_to_diphones("pause"));
        
   
    if ((m_notable_dates ==1) && (is_notable_date(m_start_day,m_start_month,m_start_year)))	
	{
		
		diphone_list =g_list_concat(diphone_list, word_to_diphones("pause1"));
		
		
		char* notable_str =get_notable_date_speak_str(m_start_day, m_start_month,m_start_year);
				
		GList *notable_word_list=NULL;  
		
		gchar** hwords;		 
		hwords = g_strsplit (notable_str, " ", 0); //split on space
		int j=0;			   
		while(hwords[j] != NULL)
		{	
		notable_word_list=word_to_diphones(hwords[j]);
		diphone_list =g_list_concat(diphone_list,notable_word_list);	
		j++;
		} //while loop words
		
		diphone_list =g_list_concat(diphone_list,word_to_diphones("pause2"));	
		//diphone_list =g_list_concat(diphone_list,word_to_diphones("pause"));	
	} //if notable dates
	
	GArray *day_events_arry =g_array_new(FALSE, FALSE, sizeof(CALENDAR_TYPE_EVENT));
	db_get_all_events_year_month_day(day_events_arry , m_start_year,m_start_month, m_start_day);

	
	
	

	//g_print("day_events_arry len =%d\n", day_events_arry->len);
	//-----------------------------------------------------------------------
	// loop through day events
	//------------------------------------------------------------------------
	
	for (int i = 0; i < day_events_arry->len; i++)
	{

		gint evt_id = 0;
		gchar *summary_str = "";
		gchar *location_str = "";
		gchar *description_str = "";

		gint start_year = 0;
		gint start_month = 0;
		gint start_day = 0;
		gint start_hour = 0;
		gint start_min = 0;

		gint end_year = 0;
		gint end_month = 0;
		gint end_day = 0;
		gint end_hour = 0;
		gint end_min = 0;

		gint is_yearly = 0;
		gint is_allday = 0;
		gint is_priority = 0;
		gint has_reminder = 0;
		gint reminder_min = 0;

		CalendarEvent *evt = g_array_index(day_events_arry, CalendarEvent *, i);

		g_object_get(evt, "eventid", &evt_id, NULL);
		g_object_get(evt, "summary", &summary_str, NULL);
		g_object_get(evt, "location", &location_str, NULL);
		g_object_get(evt, "description", &description_str, NULL);
		g_object_get(evt, "startyear", &start_year, NULL);
		g_object_get(evt, "startmonth", &start_month, NULL);
		g_object_get(evt, "startday", &start_day, NULL);
		g_object_get(evt, "starthour", &start_hour, NULL);
		g_object_get(evt, "startmin", &start_min, NULL);
		g_object_get(evt, "endyear", &end_year, NULL);
		g_object_get(evt, "endmonth", &end_month, NULL);
		g_object_get(evt, "endday", &end_day, NULL);
		g_object_get(evt, "endhour", &end_hour, NULL);
		g_object_get(evt, "endmin", &end_min, NULL);
		g_object_get(evt, "isyearly", &is_yearly, NULL);
		g_object_get(evt, "isallday", &is_allday, NULL);
		g_object_get(evt, "ispriority", &is_priority, NULL);

		gchar *start_time_str = "";
		gchar *time_str = "";
		gchar *starthour_str = "";
		gchar *startmin_str = "";
		gchar *endhour_str = "";
		gchar *endmin_str = "";
		gchar *ampm_str = "";
		
		//g_print("%s %d:%d\n", summary_str,start_hour,start_min);

	//--------------------------------------------------------------
	// Talk Time
	//---------------------------------------------------------------

	if (m_talk_time) {
	
	 GList* time_list=NULL;	 
		
		
		if(!is_allday) {

		GList* hour_list=NULL;
	  	GList* min_list=NULL;

		//g_print("time format %i\n", m_12hour_format);
		//g_print("start_hour = %i\n",start_hour);
		//g_print("start_min = %i\n",start_min);
		//hour_list =convert_number_to_diphone_list(start_hour);

			if (m_12hour_format)
			{
				if(start_hour ==0) //12am midnight
				{		
				ampm_str = "amm";				
				hour_list =convert_number_to_diphone_list(12);		
				}
				
				
				if (start_hour >= 13 && start_hour <= 23)
				{
					int s_hour = start_hour - 12;

					//g_print("s_hour = %i\n",s_hour);
					ampm_str = "pmm";
				
					hour_list =convert_number_to_diphone_list(s_hour);
				}
				if(start_hour ==12)
				{
					ampm_str = "pmm";
					
					hour_list =convert_number_to_diphone_list(start_hour);
				}
			   if(start_hour <12  && start_hour >0)	
				{
					ampm_str = "amm";
					
					hour_list =convert_number_to_diphone_list(start_hour);
				}
			} // 12
			if(!m_12hour_format) //24 hours
			{				
				hour_list =convert_number_to_diphone_list(start_hour);
			} // 24
		
			if (start_min > 0 && start_min < 10)
			{
				
			 	GList* zero_list=convert_number_to_diphone_list(0);
				GList* start_min_list =convert_number_to_diphone_list(start_min);
		        min_list =g_list_concat(zero_list,start_min_list);	
			}
			else if(start_min >=10)
			{
				min_list =convert_number_to_diphone_list(start_min);
			}

	time_list =g_list_concat(time_list, hour_list);
	time_list =g_list_concat(time_list, word_to_diphones("pause"));
	time_list =g_list_concat(time_list, min_list);
	 
	 //time_list =g_list_concat(hour_list,min_list);
	} // not all day

	//add am or pm diphone list
	//time_list =g_list_concat(time_list, word_to_diphones("pause"));
	time_list =g_list_concat(time_list,word_to_diphones(ampm_str));	
	time_list =g_list_concat(time_list, word_to_diphones("pause"));	
	diphone_list =g_list_concat(diphone_list,time_list);
	
	
	} //end talk time------------------------------------------


	//----------------------------------------------------------
	// talk summary title
	//-----------------------------------------------------------
	GList *event_title_list=NULL;  
    char* str = remove_semicolons(summary_str);
    
    char* summary_str2 =word_rules(str);
	g_print("changed_summary = %s\n", summary_str2);
  
	gchar** words;		 
	words = g_strsplit (summary_str2, " ", 0); //split on space
	int j=0;			   
	while(words[j] != NULL)
	{	
	event_title_list=word_to_diphones(words[j]);
	diphone_list =g_list_concat(diphone_list,event_title_list);	
	j++;
	} //while loop words
   
  
    if(i < day_events_arry->len-1)
    {
    diphone_list =g_list_concat(diphone_list,word_to_diphones("pause"));	
    diphone_list =g_list_concat(diphone_list,word_to_diphones("then"));	
    }
    
	} // day_events for loop
	
	//diphone_list =g_list_concat(diphone_list, word_to_diphones("pause"));	
	//diphone_list =g_list_concat(diphone_list, word_to_diphones("pause"));		
	
	play_diphone_list(diphone_list);	
	g_list_free(diphone_list);	
	
	

}

//=====================================================================
void dialog_search_shutdown(GtkWindow *dialog, gint response_id, gpointer user_data)
{	
	gtk_window_destroy(GTK_WINDOW(dialog));	
}

//=====================================================================
static void search_events(const char* search_str)
{
	
	char* search_str_lower = g_ascii_strdown(search_str,-1);
	//cycle through all events for text str
	GArray *all_events_arry =g_array_new(FALSE, FALSE, sizeof(CALENDAR_TYPE_EVENT));
	db_get_all_events(all_events_arry);
		
	GArray *search_events_arry;
	search_events_arry = g_array_new(FALSE, FALSE, sizeof(CALENDAR_TYPE_EVENT)); 
	
	//find search events array
	for (int i = 0; i < all_events_arry->len; i++)
	{
		gint evt_id = 0;
		gchar *summary_str = "";
		gchar *description_str = "";		
		gchar *location_str = "";
				
		//get each event
		CalendarEvent *evt = g_array_index(all_events_arry, CalendarEvent *, i);
		
		g_object_get(evt, "summary", &summary_str, NULL);
		g_object_get(evt, "description", &description_str, NULL);
		g_object_get(evt, "location", &location_str, NULL);		
		
		char* summary_str_lower= g_ascii_strdown(summary_str,-1);
		char* description_str_lower= g_ascii_strdown(description_str,-1);		
		char* location_str_lower= g_ascii_strdown(location_str,-1);	
		//contains substring
		
		char *event_str="";
		
		event_str= g_strconcat(event_str,summary_str_lower, " ",description_str_lower," ", location_str_lower, NULL);	
		
		char * result;
		//result = strstr (summary_str_lower,search_str_lower);
		result = strstr (event_str,search_str_lower);
		if (result != NULL)
		{
		g_array_append_val(search_events_arry, evt);
		}
    } //all events
      	
	GtkWidget *dialog_search_results;		
	//GtkWidget *label;
	GtkWidget *listbox, *box, *label;
	
	dialog_search_results =gtk_window_new(); 
	gtk_window_set_title (GTK_WINDOW (dialog_search_results), "Search Results");
	gtk_window_set_default_size(GTK_WINDOW(dialog_search_results),400,300);
	//g_signal_connect (GTK_WINDOW(dialog_search_results), "destroy", G_CALLBACK (dialog_search_shutdown), NULL);
	
	listbox = gtk_list_box_new ();
	gtk_list_box_set_selection_mode(GTK_LIST_BOX(listbox), GTK_SELECTION_SINGLE);
	//g_signal_connect (listbox, "row-activated", G_CALLBACK (callbk_row_activated),NULL);
		
	for (int i = 0; i < search_events_arry->len; i++)
	{
	CalendarEvent *evt_day = g_array_index(search_events_arry, CalendarEvent *, i);
	
	int start_day=0;
	int start_month=0;
	int start_year=0;
	char* summary_str="";	
	char *location_str="";
	char *description_str="";	
	int start_hour=0;
	int start_min=0;	
	int end_hour=0;
	int end_min=0;
	int is_yearly=0;
	int is_allday=0;
	int is_priority=0;
		
	g_object_get (evt_day, "startday", &start_day, NULL);
	g_object_get (evt_day, "startmonth", &start_month, NULL);
	g_object_get (evt_day, "startyear", &start_year, NULL);	
	g_object_get(evt_day, "summary", &summary_str, NULL);	
	g_object_get(evt_day, "location", &location_str, NULL);
	g_object_get(evt_day, "description", &description_str, NULL);	
	g_object_get(evt_day, "starthour", &start_hour, NULL);
	g_object_get(evt_day, "startmin", &start_min, NULL);	
	g_object_get(evt_day, "endhour", &end_hour, NULL);
	g_object_get(evt_day, "endmin", &end_min, NULL);
	g_object_get(evt_day, "isyearly", &is_yearly, NULL);
	g_object_get(evt_day, "isallday", &is_allday, NULL);
	g_object_get(evt_day, "ispriority", &is_priority, NULL);
		
	char *display_str="";
	
	char *day_str= g_strdup_printf("%d",start_day);
	char *month_str= g_strdup_printf("%d",start_month);
	char *year_str= g_strdup_printf("%d",start_year);
	
	display_str = g_strconcat(display_str, "Date: ",day_str,"-",month_str,"-",year_str, "\n", NULL);
	
	char *time_str = "";
	char *starthour_str = "";
	char *startmin_str = "";
	char *endhour_str = "";
	char *endmin_str = "";
	char *ampm_str = " ";
		
	if(!is_allday)
	{
	//if not all_day then add start time
	if (m_12hour_format)
	{
	
	if (start_hour >= 13 && start_hour <= 23)
	{
	int shour = start_hour;
	shour = shour - 12;
	ampm_str = "pm ";
	starthour_str = g_strdup_printf("%d", shour);
	}
	else
	{
	ampm_str = "am ";
	starthour_str = g_strdup_printf("%d", start_hour);
	}
	} // 12
	else
	{
	starthour_str = g_strdup_printf("%d", start_hour);
	} // 24
	
	startmin_str = g_strdup_printf("%d", start_min);
	
	if (start_min < 10)
	{
	time_str = g_strconcat(time_str, starthour_str, ":0", startmin_str, NULL);
	}
	else
	{
	time_str = g_strconcat(time_str, starthour_str, ":", startmin_str, NULL);
	}
	
	time_str = g_strconcat(time_str, ampm_str, NULL);
	
	if (m_show_end_time)
	{
	
	if (m_12hour_format)
	{
	ampm_str = "";
	
	if (end_hour >= 13 && end_hour <= 23)
	{
	end_hour = end_hour - 12;
	ampm_str = "pm ";
	endhour_str = g_strdup_printf("%d", end_hour);
	}
	else
	{
	ampm_str = "am ";
	endhour_str = g_strdup_printf("%d", end_hour);
	}
	} // 12
	else
	{
	endhour_str = g_strdup_printf("%d", end_hour);
	} // 24
	
	endmin_str = g_strdup_printf("%d", end_min);
	
	if (end_min < 10)
	{
	time_str = g_strconcat(time_str, "to ", endhour_str, ":0", endmin_str, NULL);
	}
	else
	{
	time_str = g_strconcat(time_str, "to ", endhour_str, ":", endmin_str, NULL);
	}
	time_str = g_strconcat(time_str, ampm_str, NULL);
	} // show_end_time	
	
	time_str = g_strconcat(time_str, NULL);	
	display_str = g_strconcat(display_str, time_str, summary_str, "\n", NULL);	
		
	}//if not allday
	else
	{
		display_str=g_strconcat(display_str,summary_str, "\n",NULL);
	}
	
	//if (is_priority)
	//{
	//display_str = g_strconcat(display_str, " High Priority.", NULL);
	//}
	
	if (!strlen(description_str) == 0){
	display_str = g_strconcat(display_str,description_str, "\n", NULL);
	}
	
	if (!strlen(location_str) == 0){
	display_str = g_strconcat(display_str,location_str, "\n", NULL);
	}
		
	box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 6);
	gtk_list_box_append (GTK_LIST_BOX (listbox), box);	
	label = gtk_label_new (display_str);
	gtk_box_append (GTK_BOX (box), label);	
    
    }//for searchevents
	
	gtk_window_set_child (GTK_WINDOW (dialog_search_results),listbox);
	gtk_window_present (GTK_WINDOW (dialog_search_results));
       	
	g_array_free(all_events_arry, FALSE); //clear the array
	g_array_free(search_events_arry, FALSE); //clear the array	

}

//======================================================================

static void callbk_search_events(GtkButton *button, gpointer user_data)
{

	GtkWidget *window = user_data;
	
	GtkEntryBuffer *buffer_search;
	GtkWidget *entry_search = g_object_get_data(G_OBJECT(button), "entry-search-key");
	
	buffer_search = gtk_entry_get_buffer(GTK_ENTRY(entry_search));
	
	const char* search_str=gtk_entry_buffer_get_text(buffer_search);
	
	//search_str = gtk_entry_buffer_get_text(search_str);
	search_str = remove_semicolons(search_str);
	search_str = remove_commas(search_str);
	search_str =remove_punctuations(search_str);
	//g_print("search_events: search_str = %s\n", search_str);

	search_events(search_str);
}

//=====================================================================

static void callbk_search(GSimpleAction *action, GVariant *parameter,  gpointer user_data)
{
	//search_events("dentist");
	
	GtkWidget *window = user_data;

	GtkWidget *dialog_search;
	gint response;
	
	GtkWidget *box;
	GtkWidget *button_search;
	
	GtkWidget *label_entry_search;
	GtkWidget *entry_search;
	
	dialog_search = gtk_window_new(); 
	gtk_window_set_title(GTK_WINDOW(dialog_search), "Search Events");
	gtk_window_set_default_size(GTK_WINDOW(dialog_search), 300, 100);
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
	gtk_window_set_child(GTK_WINDOW(dialog_search), box);

	label_entry_search = gtk_label_new("Search Text: ");
	entry_search = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(entry_search), 100);
	
	button_search = gtk_button_new_with_label("Search");
	g_signal_connect(button_search, "clicked", G_CALLBACK(callbk_search_events), window);
	
	g_object_set_data(G_OBJECT(button_search), "dialog-search-key", dialog_search);
	g_object_set_data(G_OBJECT(button_search), "entry-search-key", entry_search);
	
	gtk_box_append(GTK_BOX(box), label_entry_search);
	gtk_box_append(GTK_BOX(box), entry_search);
	
	gtk_box_append(GTK_BOX(box), button_search);	
	gtk_window_present(GTK_WINDOW(dialog_search));	
}

//======================================================================
static void callbk_check_button_upcoming_toggled(GtkCheckButton *check_button, gpointer user_data)
{
	GtkWidget *spin_button_upcoming_days;
	spin_button_upcoming_days = g_object_get_data(G_OBJECT(user_data), "cb_upcoming_spin_upcoming_key");
	
	if (gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button)))
	{
		gtk_widget_set_sensitive(spin_button_upcoming_days, TRUE);
		
	}
	else
	{
		gtk_widget_set_sensitive(spin_button_upcoming_days, FALSE);
	}
}

//======================================================================
static void callbk_set_preferences(GtkButton *button, gpointer  user_data)
{
	GtkWidget *window = user_data;
	GtkWidget *calendar =g_object_get_data(G_OBJECT(window), "window-calendar-key");
	GtkWidget *label_date =g_object_get_data(G_OBJECT(window), "window-label-date-key");
	GtkWidget *dialog = g_object_get_data(G_OBJECT(button), "dialog-key");

	
	//calendar listbox
	GtkWidget *check_button_hour_format= g_object_get_data(G_OBJECT(button), "check-button-hour-format-key");
	GtkWidget *check_button_show_end_time= g_object_get_data(G_OBJECT(button), "check-button-show-end-time-key");	
	GtkWidget *check_button_notable_dates= g_object_get_data(G_OBJECT(button), "check-button-notable-dates-key");	
			
	//general talk preferences	
	GtkWidget *check_button_talk= g_object_get_data(G_OBJECT(button), "check-button-talk-key");
    GtkWidget *check_button_talk_startup= g_object_get_data(G_OBJECT(button), "check-button-talk-startup-key");    
    	
	GtkWidget *check_button_talk_upcoming= g_object_get_data(G_OBJECT(button), "check-button-talk-upcoming-key");
	GtkWidget *spin_button_upcoming_days = g_object_get_data(G_OBJECT(button), "spin-upcoming-days-key");
	
    GtkWidget *check_button_reset_all= g_object_get_data(G_OBJECT(button), "check-button-reset-all-key");
	//calendar
	m_12hour_format=gtk_check_button_get_active (GTK_CHECK_BUTTON(check_button_hour_format));
	m_show_end_time=gtk_check_button_get_active (GTK_CHECK_BUTTON(check_button_show_end_time));
	m_notable_dates=gtk_check_button_get_active (GTK_CHECK_BUTTON(check_button_notable_dates));
		
	//talk general
	m_talk=gtk_check_button_get_active (GTK_CHECK_BUTTON(check_button_talk));
	m_talk_at_startup=gtk_check_button_get_active (GTK_CHECK_BUTTON(check_button_talk_startup));
	
	m_talk_upcoming =gtk_check_button_get_active (GTK_CHECK_BUTTON(check_button_talk_upcoming));
	m_upcoming_days = gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_upcoming_days));
		
	
	m_reset_preferences=gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_reset_all));

	if(m_reset_preferences) {
	//reset everything
	//calendar
	m_12hour_format=1;
	m_show_end_time=0;
	m_notable_dates=0;
		
	//speaking
	m_talk=1;
	m_talk_at_startup=0;
	m_talk_upcoming=0;
	m_upcoming_days=7;	
	
	//m_sample_rate=32000; 
	m_window_width=600;
    m_window_height=400;
	m_reset_preferences=0; //toggle
	}
		
	config_write();	//save preferences
		
	//update calendar (also updates listbox)	
	set_marks_on_calendar(GTK_CALENDAR(calendar));
	update_calendar(GTK_CALENDAR(calendar), GTK_LABEL(label_date));
	
	//create_header(GTK_WINDOW(window)); //update header size
		
	gtk_window_destroy(GTK_WINDOW(dialog));
    
}

//======================================================================
static void callbk_preferences(GSimpleAction* action, GVariant *parameter,gpointer user_data)
{	
	GtkWidget *window =user_data;
	
	GtkWidget *dialog;
	GtkWidget *grid;
		
	//calendar	
	GtkWidget *check_button_hour_format;
	GtkWidget *check_button_show_end_time;	
	GtkWidget *check_button_notable_dates; //notable dates	
	
	//talk
	GtkWidget *check_button_talk;
	GtkWidget *check_button_talk_startup;
			
	GtkWidget *check_button_talk_upcoming;
	GtkWidget *label_upcoming_days;
	GtkWidget *spin_button_upcoming_days;
	
	GtkWidget *check_button_reset_all;		
	GtkWidget *button_set;			
			
    GtkWidget *label_spacer1;
	GtkWidget *label_spacer2;
	GtkWidget *label_spacer3;
	GtkWidget *label_spacer4;
	GtkWidget *label_spacer5;
	
	label_spacer1 = gtk_label_new("");
	label_spacer2 = gtk_label_new("");
	label_spacer3 = gtk_label_new("");
	label_spacer4 = gtk_label_new("");
	label_spacer5 = gtk_label_new("");
	
	dialog =gtk_window_new(); 
	gtk_window_set_title (GTK_WINDOW (dialog), "Preferences");
	gtk_window_set_modal(GTK_WINDOW (dialog),TRUE);
	gtk_window_set_transient_for(GTK_WINDOW (dialog),GTK_WINDOW(window));
	
	grid = gtk_grid_new();	
	gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
		
	button_set = gtk_button_new_with_label ("Set Preferences");
	g_signal_connect (button_set, "clicked", G_CALLBACK (callbk_set_preferences), window);

	//calendar
	check_button_hour_format = gtk_check_button_new_with_label ("12 Hour Format");
	check_button_show_end_time= gtk_check_button_new_with_label ("Show End Time");
	check_button_notable_dates = gtk_check_button_new_with_label ("Notable Dates");
			
	//General talk settings
	check_button_talk = gtk_check_button_new_with_label ("Enable Talking");
	check_button_talk_startup = gtk_check_button_new_with_label ("Talk At Startup");
	
	check_button_talk_upcoming= gtk_check_button_new_with_label ("Talk Upcoming Events");	
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_talk_upcoming), m_talk_upcoming);
	GtkAdjustment *adjustment_upcoming_days; //upcoming days
	// value,lower,upper,step_increment,page_increment,page_size
	adjustment_upcoming_days = gtk_adjustment_new(7.00, 1.00, 14.00, 1.0, 1.0, 0.0);	
	label_upcoming_days = gtk_label_new("Upcoming days:  ");
	spin_button_upcoming_days = gtk_spin_button_new(adjustment_upcoming_days, 7, 0);
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_upcoming_days), m_upcoming_days);
	if(m_talk_upcoming) gtk_widget_set_sensitive(spin_button_upcoming_days, TRUE);
	else gtk_widget_set_sensitive(spin_button_upcoming_days, FALSE);
	
	g_signal_connect_swapped(GTK_CHECK_BUTTON(check_button_talk_upcoming), "toggled",	
							 G_CALLBACK(callbk_check_button_upcoming_toggled), check_button_talk_upcoming);	
	g_object_set_data(G_OBJECT(check_button_talk_upcoming), "cb_upcoming_spin_upcoming_key",spin_button_upcoming_days);
	
			
	g_object_set_data(G_OBJECT(button_set), "check-button-talk-key",check_button_talk);
	g_object_set_data(G_OBJECT(button_set), "check-button-talk-startup-key",check_button_talk_startup);
	g_object_set_data(G_OBJECT(button_set), "check-button-talk-upcoming-key",check_button_talk_upcoming);
	
	check_button_reset_all = gtk_check_button_new_with_label ("Reset All");
			 
	//set calendar preferences
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_hour_format),m_12hour_format);
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_show_end_time), m_show_end_time);	
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_notable_dates),m_notable_dates);	
		
	//set speak
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_talk), m_talk);
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_talk_startup), m_talk_at_startup);
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_talk_upcoming), m_talk_upcoming);
		
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_reset_all), m_reset_preferences);

	//data setters	
	g_object_set_data(G_OBJECT(button_set), "dialog-key",dialog);
	//calendar
	g_object_set_data(G_OBJECT(button_set), "check-button-hour-format-key",check_button_hour_format);
	g_object_set_data(G_OBJECT(button_set), "check-button-show-end-time-key",check_button_show_end_time);
	g_object_set_data(G_OBJECT(button_set), "check-button-notable-dates-key",check_button_notable_dates);	
			
	//speaking
	g_object_set_data(G_OBJECT(button_set), "check-button-talk-key",check_button_talk);
	g_object_set_data(G_OBJECT(button_set), "check-button-talk-startup-key",check_button_talk_startup);
	g_object_set_data(G_OBJECT(button_set), "check-button-talk-upcoming-key",check_button_talk_upcoming);
		
	g_object_set_data(G_OBJECT(button_set), "spin-upcoming-days-key", spin_button_upcoming_days);
		
	g_object_set_data(G_OBJECT(button_set), "check-button-reset-all-key",check_button_reset_all);
			
	//Calendar preferences	
	gtk_grid_attach(GTK_GRID(grid), check_button_hour_format,         1,1,1,1);			
	gtk_grid_attach(GTK_GRID(grid), check_button_show_end_time,       2,1,1,1);
	gtk_grid_attach(GTK_GRID(grid), check_button_notable_dates,       3,1,1,1);	
	
	gtk_grid_attach(GTK_GRID(grid), label_spacer1,                  1, 2, 1, 1);
	
	
	//gtk_grid_attach(GTK_GRID(grid), label_spacer2,                  1, 4, 1, 1);
	
	//speak preferences
	gtk_grid_attach(GTK_GRID(grid), check_button_talk,      		       1, 3, 1, 1);	
	gtk_grid_attach(GTK_GRID(grid), check_button_talk_startup,        	   2, 3, 1, 1);	
	
	gtk_grid_attach(GTK_GRID(grid), label_spacer2,                         1, 4, 1, 1);
	
			
	gtk_grid_attach(GTK_GRID(grid), check_button_talk_upcoming,      1, 5, 1, 1);	
	gtk_grid_attach(GTK_GRID(grid), label_upcoming_days,             2, 5, 1, 1);		
	gtk_grid_attach(GTK_GRID(grid), spin_button_upcoming_days,       3, 5, 1, 1);		
	
	gtk_grid_attach(GTK_GRID(grid), label_spacer3,                   1, 6, 1, 1);	
	
			
	gtk_grid_attach(GTK_GRID(grid), check_button_reset_all,  1, 7, 1, 1);
	
	gtk_grid_attach(GTK_GRID(grid), label_spacer4,       1, 8, 1, 1);
	
	gtk_grid_attach(GTK_GRID(grid), button_set,  1, 9, 3, 1);
	
    gtk_window_set_child (GTK_WINDOW (dialog), grid);	
	gtk_window_present(GTK_WINDOW(dialog));
	
		
}
//=====================================================================

//======================================================================
// LISTBOX functions and callbks
//======================================================================

static GtkWidget *create_widget (gpointer item, gpointer user_data)
{
  DisplayItem *obj = (DisplayItem *)item;
  GtkWidget *label;
  label = gtk_label_new (""); 
  gtk_widget_set_halign (GTK_WIDGET (label), GTK_ALIGN_START); //left align 
  g_object_bind_property (obj, "label", label, "label", G_BINDING_SYNC_CREATE);
  return label;
}
//======================================================================
static void add_separator (GtkListBoxRow *row, GtkListBoxRow *before, gpointer data)
{	
  if (!before) return;
  gtk_list_box_row_set_header (row, gtk_separator_new (GTK_ORIENTATION_HORIZONTAL));
}
//======================================================================
static void callbk_row_activated (GtkListBox *listbox,GtkListBoxRow *row, gpointer user_data)
{
	m_row_index = gtk_list_box_row_get_index (row);
	//m_index = gtk_list_box_row_get_index (row);
	//g_print("m_row_index = %d\n",m_row_index);
	DisplayItem *obj = g_list_model_get_item (G_LIST_MODEL (m_store), m_row_index);
	if(obj==NULL) return;
	gint id_value;
	gchar* label_value;
	g_object_get (obj, "id", &id_value, NULL);
	g_object_get (obj, "label", &label_value, NULL);
	m_id_selection=id_value;
	//g_print("m_id_selection = %d\n",m_id_selection);
	gint evt_id=0;
	gchar *summary_str="";
	gchar *location_str="";		
	//CalendarEvent *tmp_evt = g_object_new(CALENDAR_TYPE_EVENT, 0);	
	selected_evt = g_object_new(CALENDAR_TYPE_EVENT, 0);
	db_get_event(m_id_selection, selected_evt);
	
	g_object_get (selected_evt, "eventid", &evt_id, NULL);
	g_object_get (selected_evt, "summary", &summary_str, NULL);
	g_object_get (selected_evt, "location", &location_str, NULL);	
	//g_print("selected event: id = %d summary = %s location = %s\n",evt_id, summary_str, location_str);		
}

//======================================================================
// Display events (time order)
//======================================================================

static void display_event_array(GArray *evt_arry) {
	
	g_print("calling display_event_array\n");
	gint evt_id;
	const gchar *summary_str;
	const gchar *location_str;
	const gchar *description_str;
	gint start_year;
	gint start_month;
	gint start_day;
	gint start_hour;
	gint start_min;
	gint end_year;
	gint end_month;
	gint end_day;
	gint end_hour;
	gint end_min;
	gint is_yearly;
	gint is_allday;
	gint is_priority;

	
	// Display
	g_list_store_remove_all(m_store); // clear

	// loop through the events array adding events to listbox store
	for (int i = 0; i < evt_arry->len; i++)	{
		CalendarEvent *evt = g_array_index(evt_arry, CalendarEvent *, i);
		g_object_get(evt, "eventid", &evt_id, NULL);
		g_object_get(evt, "summary", &summary_str, NULL);
		g_object_get(evt, "location", &location_str, NULL);
		g_object_get(evt, "description", &description_str, NULL);
		g_object_get(evt, "startyear", &start_year, NULL);
		g_object_get(evt, "startmonth", &start_month, NULL);
		g_object_get(evt, "startday", &start_day, NULL);
		g_object_get(evt, "starthour", &start_hour, NULL);
		g_object_get(evt, "startmin", &start_min, NULL);
		g_object_get(evt, "endyear", &end_year, NULL);
		g_object_get(evt, "endmonth", &end_month, NULL);
		g_object_get(evt, "endday", &end_day, NULL);
		g_object_get(evt, "endhour", &end_hour, NULL);
		g_object_get(evt, "endmin", &end_min, NULL);
		g_object_get(evt, "isyearly", &is_yearly, NULL);
		g_object_get(evt, "isallday", &is_allday, NULL);	
		g_object_get(evt, "ispriority", &is_priority, NULL);
	     
      //create display str      
      gchar *display_str = "";
			gchar *time_str = "";
			gchar *starthour_str = "";
			gchar *startmin_str = "";
			gchar *endhour_str = "";
			gchar *endmin_str = "";
			gchar *ampm_str = " ";

			if (m_12hour_format)
			{

				if(start_hour ==0) //12am midnight
				{
				ampm_str = "am ";	
				starthour_str = g_strdup_printf("%d", 12);
				}
					
				
				if (start_hour >= 13 && start_hour <= 23)
				{
					int shour = start_hour;
					shour = shour - 12;
					ampm_str = "pm ";
					starthour_str = g_strdup_printf("%d", shour);
				}
				if(start_hour  == 12)
				{
					ampm_str = "pm ";					
					starthour_str = g_strdup_printf("%d", start_hour);
				}
				
				 if(start_hour <12 && start_hour >0)
				{
					ampm_str = "am ";
					starthour_str = g_strdup_printf("%d", start_hour);
				}			
				
			} // 12hout format
			else
			{
				starthour_str = g_strdup_printf("%d", start_hour);
			} // 24

			startmin_str = g_strdup_printf("%d", start_min);

			if (start_min < 10)
			{
				time_str = g_strconcat(time_str, starthour_str, ":0", startmin_str, NULL);
			}
			else
			{
				time_str = g_strconcat(time_str, starthour_str, ":", startmin_str, NULL);
			}

			time_str = g_strconcat(time_str, ampm_str, NULL);

			if (m_show_end_time)
			{

				if (m_12hour_format)
				{
				ampm_str = "";
				
				if(end_hour ==0) //12am midnight
				{
				ampm_str = "am ";	
				endhour_str = g_strdup_printf("%d", 12);
				}				
				
				if (end_hour >= 13 && end_hour <= 23)
				{
				end_hour = end_hour - 12;
				ampm_str = "pm ";
				endhour_str = g_strdup_printf("%d", end_hour);
				}				
				if(end_hour  == 12)
				{
				ampm_str = "pm ";					
				endhour_str = g_strdup_printf("%d", end_hour);
				}				
				if(end_hour <12 && end_hour >0)
				{
				ampm_str = "am ";
				endhour_str = g_strdup_printf("%d", end_hour);
				}	
				
				} // 12
				else
				{
					endhour_str = g_strdup_printf("%d", end_hour);
				} // 24

				endmin_str = g_strdup_printf("%d", end_min);

				if (end_min < 10)
				{
					time_str = g_strconcat(time_str, "to ", endhour_str, ":0", endmin_str, NULL);
				}
				else
				{
					time_str = g_strconcat(time_str, "to ", endhour_str, ":", endmin_str, NULL);
				}
				time_str = g_strconcat(time_str, ampm_str, NULL);
			} // show_end_time

			if(!is_allday)
			{
				time_str = g_strconcat(time_str, NULL);
			}
			else
			{
				time_str="";
				//time_str = g_strconcat(time_str, NULL);
			}
			
			if (!strlen(time_str) == 0)
			{
				display_str = g_strconcat(display_str, time_str," ", summary_str, NULL);
			}
			else
			{
				display_str = g_strconcat(display_str, summary_str, NULL);
			}
			
					
			display_str = g_strconcat(display_str, "\n", NULL);
			
			if ((!strlen(description_str) == 0) && (!strlen(location_str) == 0))
			{
				display_str = g_strconcat(display_str, description_str, ". ",location_str, ".", NULL);
			}
			if ((!strlen(description_str) == 0) && (strlen(location_str) == 0))
			{
				display_str = g_strconcat(display_str, description_str, ".",NULL);
			}
			if ((strlen(description_str) == 0) && (!strlen(location_str) == 0))
			{
				display_str = g_strconcat(display_str, location_str, ".",NULL);
			}
			
						
			if (is_priority)
			{
				display_str = g_strconcat(display_str, "\n","High Priority.", NULL);
			}
						
			// Display day events db sorted

			if (is_allday)
			{
				start_hour = 0;
				start_min = 0;
			}
			//start_time_sort = start_hour * 60 * 60 + 60 * start_min; // seconds

			DisplayItem *item = NULL;
			item = g_object_new(display_item_get_type(),
								"id", evt_id,
								"label", display_str,								
								NULL);			
			
			g_list_store_append (m_store, item); //db sorted
			g_object_unref(item);		
		}//evt_arry loop
}

//======================================================================


static void callbk_info(GSimpleAction *action, GVariant *parameter,  gpointer user_data)
{	
	GtkWidget *window =user_data;
	GtkWidget *calendar =g_object_get_data(G_OBJECT(window), "window-calendar-key");
	GtkWidget *dialog;
	GtkWidget *box;
	gint response;
	
	GtkWidget *label_keyboard_shortcuts;	
	GtkWidget *label_home_shortcut;
	GtkWidget *label_newevent_shortcut;
	GtkWidget *label_editevent_shortcut;
	GtkWidget *label_deleteevent_shortcut;
	GtkWidget *label_preferences_shortcut;
	GtkWidget *label_info_shortcut;
	GtkWidget *label_speak_shortcut;
	GtkWidget *label_time_shortcut;
	GtkWidget *label_quit_shortcut;
		
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
		
	label_home_shortcut=gtk_label_new("Home: Go to today");	
	label_newevent_shortcut=gtk_label_new("Ctrl+n: New event");
	label_editevent_shortcut=gtk_label_new("Ctrl+e: Edit selected event");	
	label_deleteevent_shortcut=gtk_label_new("Delete: Delete selected event");
	label_preferences_shortcut=gtk_label_new("Ctrl+Alt+P: Preferences");
	label_info_shortcut=gtk_label_new("F1: Information");
	label_speak_shortcut=gtk_label_new("Spacebar: Speak day events");
	label_time_shortcut=gtk_label_new("t: Speak time");
	label_quit_shortcut=gtk_label_new("Ctrl+q: Quit");
		
	label_record_info=gtk_label_new("Storage");
	gtk_label_set_attributes (GTK_LABEL (label_record_info), attrs);
	
	char* record_num_str =" Number of records = ";
	char* n_str = g_strdup_printf("%d", get_total_number_of_events());
	record_num_str = g_strconcat(record_num_str, n_str,NULL);
	label_record_number =gtk_label_new(record_num_str);
	
	char* sqlite_version_str =" Sqlite version  = ";
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
	gtk_box_append(GTK_BOX(box),label_newevent_shortcut);
	gtk_box_append(GTK_BOX(box),label_editevent_shortcut);
	gtk_box_append(GTK_BOX(box),label_deleteevent_shortcut);	
	gtk_box_append(GTK_BOX(box),label_preferences_shortcut);
	gtk_box_append(GTK_BOX(box),label_info_shortcut);
	gtk_box_append(GTK_BOX(box), label_speak_shortcut);	
	gtk_box_append(GTK_BOX(box), label_time_shortcut);
	gtk_box_append(GTK_BOX(box), label_quit_shortcut);	
		
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

//======================================================================
//Update date label
//======================================================================
static void update_date_label(GtkCalendar *calendar, gpointer user_data)
{
	GtkWidget *label_date = (GtkWidget *) user_data;
	//g_print("Day is : %d-%d-%d \n", m_start_day, m_start_month,m_start_year);
	 gchar* date_str="";
	 gchar* weekday_str="";

	 GDateTime *dt;
	 dt = g_date_time_new_local(m_start_year, m_start_month, m_start_day, 1, 1, 1);
	 gint day_of_week = g_date_time_get_day_of_week(dt);
	 g_date_time_unref(dt); //freeit quick

	 switch(day_of_week)
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
	 		weekday_str="Unknown";
	 }//switch

	 gchar* day_str =  g_strdup_printf("%d",m_start_day);
	 gchar *year_str = g_strdup_printf("%d",m_start_year);

	date_str =g_strconcat(date_str,weekday_str," ", day_str, " ", NULL);

	 switch(m_start_month)
	 {
	 	case G_DATE_JANUARY:
	 		date_str =g_strconcat(date_str,"January ",year_str, NULL);
	 		break;
	 	case G_DATE_FEBRUARY:
	 		date_str =g_strconcat(date_str,"February ",year_str, NULL);
	 		break;
	 	case G_DATE_MARCH:
	 		date_str =g_strconcat(date_str,"March ",year_str, NULL);
	 		break;
	 	case G_DATE_APRIL:
	 		date_str =g_strconcat(date_str,"April ",year_str, NULL);
	 		break;
	 	case G_DATE_MAY:
	 		date_str =g_strconcat(date_str,"May ",year_str, NULL);
	 		break;
	 	case G_DATE_JUNE:
	 		date_str =g_strconcat(date_str,"June ",year_str, NULL);
	 		break;
	 	case G_DATE_JULY:
	 		date_str =g_strconcat(date_str,"July ",year_str, NULL);
	 		break;
	 	case G_DATE_AUGUST:
	 		date_str =g_strconcat(date_str,"August ",year_str, NULL);
	 		break;
	 	case G_DATE_SEPTEMBER:
	 		date_str =g_strconcat(date_str,"September ",year_str, NULL);
	 		break;
	 	case G_DATE_OCTOBER:
	 		date_str =g_strconcat(date_str,"October ",year_str, NULL);
	 		break;
	 	case G_DATE_NOVEMBER:
	 		date_str =g_strconcat(date_str,"November ",year_str, NULL);
	 		break;
	 	case G_DATE_DECEMBER:
	 		date_str =g_strconcat(date_str,"December ",year_str, NULL);
	 		break;
	 	default:
	 		date_str =g_strconcat(date_str,"Unknown ",year_str, NULL);
	 }
		
	if ((m_notable_dates ==1) && (is_notable_date(m_start_day,m_start_month,m_start_year)))
	{		
		gchar * notable_str = get_notable_date_str(m_start_day,m_start_month,m_start_year);	 	
	 	date_str =g_strconcat(date_str," ",notable_str, NULL);
	}
	
		
	 int event_num =get_number_of_day_events();
	 if(event_num>0) {
	 	date_str =g_strconcat(date_str,"*", NULL);
	 }
	 
	gtk_label_set_text(GTK_LABEL(label_date), date_str);	 
	
}
//======================================================================
// update calendar
//======================================================================

static void update_calendar(GtkCalendar *calendar, gpointer user_data)
{
	GtkWidget *label_date = (GtkWidget *)user_data;
	
	GDateTime *cal_date = gtk_calendar_get_date(GTK_CALENDAR(calendar));
	
	m_start_day = g_date_time_get_day_of_month(cal_date);
	m_start_month =g_date_time_get_month(cal_date);
	m_start_year=g_date_time_get_year(cal_date);
	g_print("Date is : %d-%d-%d \n", m_start_day, m_start_month,m_start_year);
	
	update_date_label(GTK_CALENDAR(calendar), label_date);	
	
	//set marks on calendar
	set_marks_on_calendar(GTK_CALENDAR(calendar));
	
	//listbox
	g_list_store_remove_all(m_store); // clear listbox store
	GArray *evt_arry_day; //normal day events
	evt_arry_day = g_array_new(FALSE, FALSE, sizeof(CALENDAR_TYPE_EVENT)); // setup arraylist
	db_get_all_events_year_month_day(evt_arry_day, m_start_year,m_start_month, m_start_day);
	//print_array(evt_arry_day);		
	display_event_array(evt_arry_day); //display listbox day events
	g_array_free(evt_arry_day, FALSE); //clear the array 
}

//======================================================================
static void callbk_calendar_next_month(GtkCalendar *calendar, gpointer user_data)
{
	g_print("next month\n");
	update_calendar(calendar, user_data);
}
//======================================================================
static void callbk_calendar_prev_month(GtkCalendar *calendar, gpointer user_data)
{
	g_print("prev month\n");		
	update_calendar(calendar, user_data);	
}
//======================================================================
static void callbk_calendar_next_year(GtkCalendar *calendar, gpointer user_data)
{
	g_print("next year\n");
	update_calendar(calendar, user_data);	
}
//======================================================================
static void callbk_calendar_prev_year(GtkCalendar *calendar, gpointer user_data)
{
	g_print("prev year\n");
	update_calendar(calendar, user_data);
}
//======================================================================

//======================================================================
// Day selected
//======================================================================

static void callbk_calendar_day_selected(GtkCalendar *calendar, gpointer user_data)
{
	g_print("day selected\n");
	update_calendar(calendar, user_data);			
}
//======================================================================

static void set_marks_on_calendar(GtkCalendar *calendar)
{
	g_print("calling set marks on calendar\n");
	
	GArray *evt_arry_month; //standard month events
	evt_arry_month = g_array_new(FALSE, FALSE, sizeof(CALENDAR_TYPE_EVENT));	
	db_get_all_events_year_month(evt_arry_month, m_start_year,m_start_month);
	
	//remove all visual markers
	gtk_calendar_clear_marks(GTK_CALENDAR(calendar));

	
	for (int i=0; i<evt_arry_month->len; i++) {  
		gint start_day=0;
		gint start_month=0;
		gint start_year=0;
			
		gint end_day=0;
		gint end_month=0;
		gint end_year=0;				
		
		guint8 month_days =g_date_get_days_in_month(m_start_month,m_start_year);
	
		CalendarEvent *evt =g_array_index(evt_arry_month, CalendarEvent*, i);
		
		g_object_get (evt, "startday", &start_day, NULL);
		g_object_get (evt, "startmonth", &start_month, NULL);
		g_object_get (evt, "startyear", &start_year, NULL);
		
		g_print("month event day = %d-%d-%d\n",start_day,start_month,start_year);
		
		//places a visual marker on day of the current month.
		gtk_calendar_mark_day(GTK_CALENDAR(calendar),start_day);
  	
     }//for
     
	g_array_free(evt_arry_month, FALSE); //clear standard month events
}

//======================================================================
static void callbk_calendar_home(GSimpleAction * action, GVariant *parameter, gpointer user_data)
{
	g_print("callbk_calendar_home\n");
	
	GtkWindow *window =user_data;	
	GtkWidget *calendar =g_object_get_data(G_OBJECT(window), "window-calendar-key");
	GtkWidget *label_date =g_object_get_data(G_OBJECT(window), "window-label-date-key");
	
	GDateTime *today;
	today = g_date_time_new_now_local();
	m_start_year = g_date_time_get_year(today);
	m_start_month = g_date_time_get_month(today);
	m_start_day = g_date_time_get_day_of_month(today);	
	g_print("Date is : %d-%d-%d \n", m_start_day, m_start_month,m_start_year);
	
	gtk_calendar_select_day (GTK_CALENDAR(calendar), today); //being depreciated and replaced by		
	//gtk_calendar_set_date (GTK_CALENDAR(calendar), today); //gtk4.20 onwards -unstable do not use
	
	update_calendar(GTK_CALENDAR(calendar), GTK_LABEL(label_date));
	g_date_time_unref(today);
}
//======================================================================

static void create_header(GtkWindow *window)
{
	GtkWidget *header;
	GtkWidget *button_new_event;
	GtkWidget *button_edit_event;
	GtkWidget *button_delete_selected;
	GtkWidget *menu_button;

	
	header = gtk_header_bar_new();
	gtk_window_set_titlebar(GTK_WINDOW(window), header);

	button_new_event = gtk_button_new_with_label("New Event");
	gtk_widget_set_tooltip_text(button_new_event, "New calendar event");
	GtkWidget *label_new_event = gtk_button_get_child(GTK_BUTTON(button_new_event));	
	g_signal_connect(button_new_event, "clicked", G_CALLBACK(callbk_new_event), window);

	button_edit_event = gtk_button_new_with_label("Edit Event");
	gtk_widget_set_tooltip_text(button_edit_event, "Edit selected event");
	GtkWidget *label_edit_event = gtk_button_get_child(GTK_BUTTON(button_edit_event));	
	g_signal_connect(button_edit_event, "clicked", G_CALLBACK(callbk_edit_event), window);

	button_delete_selected = gtk_button_new_with_label("Delete Event");
	gtk_widget_set_tooltip_text(button_delete_selected, "Delete selected event");
	GtkWidget *label_delete = gtk_button_get_child(GTK_BUTTON(button_delete_selected));
	g_signal_connect(button_delete_selected, "clicked", G_CALLBACK(callbk_delete_selected), window);


	// Packing
	gtk_header_bar_pack_start(GTK_HEADER_BAR(header), button_new_event);
	gtk_header_bar_pack_start(GTK_HEADER_BAR(header), button_edit_event);
	gtk_header_bar_pack_start(GTK_HEADER_BAR(header), button_delete_selected);

	// Menu model
	GMenu *menu, *section;
	menu = g_menu_new();

	section = g_menu_new();
	g_menu_append(section, "Preferences", "app.preferences");
	g_menu_append_section(menu, NULL, G_MENU_MODEL(section));
	g_object_unref(section);

	section = g_menu_new();
	g_menu_append(section, "Speak", "app.speak");
	g_menu_append_section(menu, NULL, G_MENU_MODEL(section));
	g_object_unref(section);

	section = g_menu_new();
	g_menu_append(section, "Speak Time", "app.speaktime");
	g_menu_append_section(menu, NULL, G_MENU_MODEL(section));
	g_object_unref(section);

	section = g_menu_new();
	g_menu_append(section, "Export", "app.export");
	g_menu_append_section(menu, NULL, G_MENU_MODEL(section));
	g_object_unref(section);

	 section = g_menu_new ();
	 g_menu_append (section, "Import", "app.import"); 
	 g_menu_append_section (menu, NULL, G_MENU_MODEL (section));
	 g_object_unref (section);
	 
	 section = g_menu_new ();
	 g_menu_append (section, "Delete All", "app.deleteall"); 
	 g_menu_append_section (menu, NULL, G_MENU_MODEL (section));
	 g_object_unref (section);
	 
	 section = g_menu_new ();
	 g_menu_append (section, "Search", "app.search"); 
	 g_menu_append_section (menu, NULL, G_MENU_MODEL (section));
	 g_object_unref (section);

	section = g_menu_new();
	g_menu_append(section, "Information", "app.info"); // show app info
	g_menu_append_section(menu, NULL, G_MENU_MODEL(section));
	g_object_unref(section);

	section = g_menu_new();
	g_menu_append(section, "About", "app.about");
	g_menu_append_section(menu, NULL, G_MENU_MODEL(section));
	g_object_unref(section);


	// Now hamburger style menu button
	menu_button = gtk_menu_button_new();
	gtk_widget_set_tooltip_text(menu_button, "Menu");
	gtk_menu_button_set_icon_name(GTK_MENU_BUTTON(menu_button), "open-menu-symbolic");
	gtk_menu_button_set_menu_model(GTK_MENU_BUTTON(menu_button), G_MENU_MODEL(menu));
	gtk_header_bar_pack_end(GTK_HEADER_BAR(header), menu_button);
}

//======================================================================
static void startup(GtkApplication *app)
{	 	
	 config_initialize(); //calls config_read	  	
	 db_create_events_table(); //startup database 
}
//======================================================================
void callbk_shutdown(GtkWindow *window, gint response_id, gpointer user_data)
{
	g_print("shutdown invoked. Saving window width and height\n");
	gtk_window_get_default_size(GTK_WINDOW(window), &m_window_width,&m_window_height);	
	config_write();			
}

//======================================================================

static void activate (GtkApplication *app, gpointer  user_data)
{
	
	GtkWidget *window;	
	GtkWidget *calendar; 
	
	GtkWidget *box;
	GtkWidget *sw; //scrolled window
	GtkWidget* listbox;
	GtkWidget *label_date; //display selected date
	
		
	// create a new window, and set its title
	window = gtk_application_window_new (app);
	//gtk_window_set_title (GTK_WINDOW (window), "Talk Calendar ");
	gtk_window_set_title (GTK_WINDOW (window), " ");
	gtk_window_set_default_size (GTK_WINDOW (window),m_window_width,m_window_height); 		
	g_signal_connect (window, "destroy", G_CALLBACK (callbk_shutdown),app);	
	create_header(GTK_WINDOW(window));
	
	//setup selected date label
	label_date = gtk_label_new("");
	gtk_label_set_xalign(GTK_LABEL(label_date), 0.5);
	
	//Keyboard accelerators
	const gchar *home_accels[2] = { "Home", NULL };
	const gchar *speak_accels[2] = { "space", NULL };
	const gchar *newevent_accels[2] = {"<Ctrl>n", NULL };	
	const gchar *editevent_accels[2] = {"<Ctrl>e", NULL };
	const gchar *time_accels[2] = {"t", NULL };
	const gchar *info_accels[2] = {"F1", NULL };
	const gchar *delete_accels[2] = {"Delete", NULL };	
	const gchar * preferences_accels[2] = { "<Ctrl><Alt>P", NULL };
	const gchar * quit_accels[2] = { "<Ctrl>Q", NULL };
		
	//setup GTK Calendar
	calendar =gtk_calendar_new();
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
	g_print("Date is : %d-%d-%d \n", m_start_day, m_start_month,m_start_year);		
	update_date_label(GTK_CALENDAR(calendar), label_date);	
		
	//setup scrolled window and with listbox inside
	sw = gtk_scrolled_window_new ();
	gtk_widget_set_hexpand (GTK_WIDGET (sw), true);
	gtk_widget_set_vexpand (GTK_WIDGET (sw), true);

	listbox = gtk_list_box_new ();
	gtk_list_box_set_selection_mode (GTK_LIST_BOX (listbox), GTK_SELECTION_SINGLE);
	gtk_list_box_set_show_separators (GTK_LIST_BOX (listbox), TRUE);
	gtk_list_box_set_header_func (GTK_LIST_BOX (listbox), add_separator, NULL, NULL);
		
	 //storage	
    m_store = g_list_store_new (display_item_get_type()); //setup display store
	gtk_list_box_bind_model (GTK_LIST_BOX (listbox), G_LIST_MODEL (m_store), create_widget, NULL, NULL);
	g_signal_connect (listbox, "row-activated", G_CALLBACK (callbk_row_activated),NULL);
	
	gtk_scrolled_window_set_child (GTK_SCROLLED_WINDOW (sw), listbox);

	//selection
	m_row_index=-1;
    m_id_selection=-1;
   		
	//setup layout box
	box =gtk_box_new(GTK_ORIENTATION_VERTICAL,1);	
    gtk_window_set_child (GTK_WINDOW (window), box);
    
    gtk_box_append(GTK_BOX(box), label_date);
	gtk_box_append(GTK_BOX(box), calendar);
	gtk_box_append(GTK_BOX(box), sw); //listbox inside sw
	      
	//setup key-value pairs
	g_object_set_data(G_OBJECT(window), "window-calendar-key",calendar);
	g_object_set_data(G_OBJECT(window), "window-label-date-key",label_date);
	//g_object_set_data(G_OBJECT(window), "label-date-key", label_date);	
	
	//setup actions	
	//file actions
	GSimpleAction *export_action;
	export_action=g_simple_action_new("export",NULL); //app.export
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(export_action)); //make visible
	g_signal_connect(export_action, "activate",  G_CALLBACK(callbk_export), window);
	
	GSimpleAction *import_action;
	import_action=g_simple_action_new("import",NULL); //app.import
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(import_action)); //make visible
	g_signal_connect(import_action, "activate",  G_CALLBACK(callbk_import), window);
	
	
	//edit actions	
	GSimpleAction *preferences_action;
	preferences_action=g_simple_action_new("preferences",NULL); //app.preferences
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(preferences_action)); //make visible
	g_signal_connect(preferences_action, "activate",  G_CALLBACK(callbk_preferences), window);
	
	//event actions
	//new event
	GSimpleAction *newevent_action;	
	newevent_action=g_simple_action_new("newevent",NULL); //app.newevent
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(newevent_action)); //make visible	
	g_signal_connect(newevent_action, "activate",  G_CALLBACK(callbk_new_event), window);
	
	//edit Event
	GSimpleAction *editevent_action;	
	editevent_action=g_simple_action_new("editevent",NULL); //app.editevent
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(editevent_action)); //make visible	
	g_signal_connect(editevent_action, "activate",  G_CALLBACK(callbk_edit_event), window);	
	
	//delete actions
	GSimpleAction *deleteevent_action;	
	deleteevent_action=g_simple_action_new("deleteevent",NULL); //app.deleteevent
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(deleteevent_action)); //make visible	
	g_signal_connect(deleteevent_action, "activate",  G_CALLBACK(callbk_delete_selected), window);
	
	GSimpleAction *deleteall_action;
	deleteall_action=g_simple_action_new("deleteall",NULL); //app.deleteall
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(deleteall_action)); //make visible
	g_signal_connect(deleteall_action, "activate",  G_CALLBACK(callbk_delete_all), window);
	
	GSimpleAction *search_action;
	search_action=g_simple_action_new("search",NULL); //app.search
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(search_action)); //make visible
	g_signal_connect(search_action, "activate",  G_CALLBACK(callbk_search), window);
	
	//speak actions
	GSimpleAction *speak_action;	
	speak_action=g_simple_action_new("speak",NULL); //app.speak
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(speak_action)); //make visible	
	g_signal_connect(speak_action, "activate",  G_CALLBACK(callbk_speak), window);
	
	GSimpleAction *speaktime_action;	
	speaktime_action=g_simple_action_new("speaktime",NULL); //app.speaktime
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(speaktime_action)); //make visible	
	g_signal_connect(speaktime_action, "activate",  G_CALLBACK(callbk_speaktime), window);
	
	//calendar actions	
	GSimpleAction *home_action;	
	home_action=g_simple_action_new("home",NULL); //app.home
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(home_action)); //make visible	
	g_signal_connect(home_action, "activate",  G_CALLBACK(callbk_calendar_home), window);
			
	//help actions
	GSimpleAction *info_action;
	info_action=g_simple_action_new("info",NULL); //app.info
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(info_action)); //make visible
	g_signal_connect(info_action, "activate",  G_CALLBACK(callbk_info), window);
		
	GSimpleAction *about_action;
	about_action=g_simple_action_new("about",NULL); //app.about
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(about_action)); //make visible
	g_signal_connect(about_action, "activate",  G_CALLBACK(callbk_about), window);
			
	// connect keyboard accelerators	
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.home", home_accels);
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.newevent", newevent_accels);
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.editevent", editevent_accels);
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.speak", speak_accels);		
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.speaktime", time_accels);	
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.info", info_accels);
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.preferences", preferences_accels);
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.deleteevent", delete_accels);
	//gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.quit", quit_accels);
	
	//display listview
	GArray *evt_arry_day; //normal day events
	evt_arry_day = g_array_new(FALSE, FALSE, sizeof(CALENDAR_TYPE_EVENT)); // setup arraylist
	db_get_all_events_year_month_day(evt_arry_day, m_start_year,m_start_month, m_start_day);
	//print_array(evt_arry_day);	
	display_event_array(evt_arry_day); //display listbox day events
	g_array_free(evt_arry_day, FALSE); //clear the array 
	
	if(m_talk && m_talk_at_startup) {
		speak_events();		
	}
	
	set_marks_on_calendar(GTK_CALENDAR(calendar));
	
	//update_date_label(GTK_CALENDAR(calendar), label_date);	
	
	gtk_window_present (GTK_WINDOW (window)); 
	
	
}
//======================================================================
int main (int  argc, char **argv)
{
	GtkApplication *app;
	int status;

	app = gtk_application_new ("org.gtk.talkcalendar", G_APPLICATION_DEFAULT_FLAGS);

	g_signal_connect_swapped(app, "startup", G_CALLBACK (startup),app);

	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);

	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);

	return status;
}
