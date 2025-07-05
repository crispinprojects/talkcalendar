/* main.c
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

#include <gtk/gtk.h>

#include "calendarevent.h"
#include "dbmanager.h"

#define CONFIG_DIRNAME "talkcalendar"
#define CONFIG_FILENAME "talkcalendar-045"
static char * m_config_file = NULL;


int file_exists(const char *file_name);
GListStore *load_store(void);


static void callbk_about(GSimpleAction* action, GVariant *parameter, gpointer user_data);
static void callbk_info(GSimpleAction *action, GVariant *parameter,  gpointer user_data);
int  get_total_number_of_events(void);

static void callbk_new_event(GtkButton *button, gpointer  user_data);
static void callbk_add_new_event(GtkButton *button, gpointer user_data);

static void callbk_edit_event(GtkButton *button, gpointer user_data);
static void callbk_update_event(GtkButton *button, gpointer user_data);

static void callbk_search(GSimpleAction *action, GVariant *parameter,  gpointer user_data);

static char *remove_commas(const char *text);
static char* remove_semicolons (const char *text);
static char* remove_punctuations(const char *text);
static char* remove_ampersand (const char *text);

static void callbk_calendar_day_selected(GtkCalendar *calendar, gpointer user_data);
static void callbk_calendar_next_month(GtkCalendar *calendar, gpointer user_data);
static void callbk_calendar_prev_month(GtkCalendar *calendar, gpointer user_data);
static void callbk_calendar_next_year(GtkCalendar *calendar, gpointer user_data);
static void callbk_calendar_prev_year(GtkCalendar *calendar, gpointer user_data);
static void update_calendar(GtkCalendar *calendar, gpointer user_data);
static void callbk_calendar_home(GSimpleAction * action, GVariant *parameter, gpointer user_data);

static void callbk_find_event(GtkButton *button, gpointer user_data);

static char* get_cardinal_string(int number);
static char* get_day_number_ordinal_string(int day);
static char* get_day_of_week(int day, int month, int year);
char* get_month_string(int month);

static void callbk_speak(GSimpleAction* action, GVariant *parameter,gpointer user_data);
static void callbk_speaktime(GSimpleAction * action, GVariant *parameter, gpointer user_data);
//static void speak_events(gpointer user_data);
static void speak_events(int day, int month, int year);
static void speak_time(gint hour, gint min);
char* get_time_str(int hour, int min);


static void play_audio_async (GTask *task,
                          gpointer object,
                          gpointer task_data,
                          GCancellable *cancellable);
                          
static void task_callbk(GObject *gobject,GAsyncResult *res,  gpointer  user_data);



static void callbk_easter(GSimpleAction *action, GVariant *parameter,  gpointer user_data);
GDate* calculate_easter(gint year);
static void callbk_calc_easter(GtkButton *button, gpointer user_data);

static void callbk_export(GSimpleAction *action, GVariant *parameter,  gpointer user_data);
static void file_save_response (GObject *source, GAsyncResult *result, void *user_data);
void export_file(char *file_name);

static void callbk_import(GSimpleAction *action, GVariant *parameter,  gpointer user_data);
static void file_open_response (GObject *source, GAsyncResult *result, void *user_data);
void import_ical_file(gpointer user_data);
static char *ignore_first_zero(char *input);

static void callbk_preferences(GSimpleAction* action, GVariant *parameter,gpointer user_data);
static void callbk_set_preferences(GtkButton *button, gpointer  user_data);

//old style text preferences 
//TODO need to work out how to use gsettings xml schema
static void config_load_default(void);
static void config_read(void);
static void config_write(void);
void config_initialize(void);

//user preferences
static int m_reset_preferences=0;
static int m_12hour_format=1; //am pm hour format
static int m_talk =1;
static int m_talk_description=0; 
static int m_talk_location=0; 


static int m_window_width=900;
static int m_window_height=500;
 
gboolean m_talking=FALSE; //gtask
static char* m_file_name="talkcalendar.ical"; //import default

const GActionEntry app_actions[] = {
  { "speak", callbk_speak}, 
  { "speaktime", callbk_speaktime},   
  { "home", callbk_calendar_home}, 
  { "info", callbk_info},
  { "preferences", callbk_preferences}  
};

//=====================================================================
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
gtk_about_dialog_set_version (GTK_ABOUT_DIALOG(about_dialog), "Version 0.4.5");
gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(about_dialog),"Copyright © 2024");
gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(about_dialog),"Talking Calendar");
gtk_about_dialog_set_license_type (GTK_ABOUT_DIALOG(about_dialog), GTK_LICENSE_LGPL_2_1);
gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(about_dialog),"https://github.com/crispinprojects/");
gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(about_dialog),"Talking Calendar Website");
gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(about_dialog), authors);
gtk_about_dialog_set_logo_icon_name(GTK_ABOUT_DIALOG(about_dialog), "x-office-calendar");
gtk_widget_set_visible (about_dialog, TRUE);
}
//======================================================================
static void callbk_info(GSimpleAction *action, GVariant *parameter,  gpointer user_data)
{
	GtkWidget *window =user_data;
	GtkWidget *calendar =g_object_get_data(G_OBJECT(window), "window-calendar-key");
	GtkWidget *dialog;
	GtkWidget *box;
	
	GtkWidget *label_keyboard_shortcuts;	
	GtkWidget *label_home_shortcut;
	
	GtkWidget *label_preferences_shortcut;
	GtkWidget *label_info_shortcut;
	GtkWidget *label_speak_shortcut;
	GtkWidget *label_time_shortcut;
	
	GtkWidget *label_record_info;
	GtkWidget *label_record_number;
	GtkWidget *label_sqlite_version;
	
	GtkWidget *label_speech_synthesizer;
	GtkWidget *label_flite_detected;
	
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
	
	label_preferences_shortcut=gtk_label_new("Ctrl+Alt+P: Preferences");
	label_info_shortcut=gtk_label_new("F1: Information");
	label_speak_shortcut=gtk_label_new("spacebar: Speak selected day events");
	label_time_shortcut=gtk_label_new("t: Speak time");
	
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
	
	label_speech_synthesizer=gtk_label_new("Speech Synthesizer");
	gtk_label_set_attributes (GTK_LABEL (label_speech_synthesizer), attrs);
	char* flite_str="Local Flite voice: ";
		
	gchar *cur_dir;	
	cur_dir = g_get_current_dir();	
	//g_print("current directory = %s\n", cur_dir);
	
	if (!g_file_test(g_build_filename(cur_dir, "flite_cmu_us_kal16", NULL), G_FILE_TEST_IS_REGULAR)) 
	{
	//g_print("flite does not exist\n");
	flite_str = g_strconcat(flite_str, "not detected.",NULL);   
	}
	else 
	{   
	//g_print("flite exists\n");
	flite_str = g_strconcat(flite_str, "detected.",NULL);
	}
	
	label_flite_detected =gtk_label_new(flite_str);	
	
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
	gtk_box_append(GTK_BOX(box),label_preferences_shortcut);
	gtk_box_append(GTK_BOX(box),label_info_shortcut);
	gtk_box_append(GTK_BOX(box), label_speak_shortcut);	
	gtk_box_append(GTK_BOX(box), label_time_shortcut);
	
	gtk_box_append(GTK_BOX(box), label_record_info);
	gtk_box_append(GTK_BOX(box), label_record_number);
	gtk_box_append(GTK_BOX(box), label_sqlite_version);	
	
	gtk_box_append(GTK_BOX(box), label_speech_synthesizer);	
	gtk_box_append(GTK_BOX(box), label_flite_detected);
	
	gtk_box_append(GTK_BOX(box),label_font_info);
	gtk_box_append(GTK_BOX(box),label_desktop_font);
	gtk_box_append(GTK_BOX(box),label_gnome_text_scale);
	
	pango_attr_list_unref(attrs);
	
	gtk_window_present (GTK_WINDOW (dialog));
	
	gtk_window_set_focus(GTK_WINDOW(window), GTK_WIDGET(calendar));

}
//======================================================================
int  get_total_number_of_events(void){
return db_get_number_of_rows_all();
}
//======================================================================
// Save load preferences
//======================================================================

static void config_load_default()
{
//talking
m_talk=1;
m_talk_description=0;
m_talk_location=0;	
m_12hour_format=1;	
m_window_width=900;
m_window_height=500;
}

static void config_read()
{
//talking
m_talk=1;
m_talk_description=0;
m_talk_location=0;	
m_12hour_format=1;	
m_window_width=900;
m_window_height=500;

// Load keys from keyfile
GKeyFile * kf = g_key_file_new();
g_key_file_load_from_file(kf, m_config_file, G_KEY_FILE_NONE, NULL);
//talk general
m_talk = g_key_file_get_integer(kf, "calendar_settings", "talk", NULL);
m_talk_location = g_key_file_get_integer(kf, "calendar_settings", "talk_location", NULL);
m_talk_description= g_key_file_get_integer(kf, "calendar_settings", "talk_description", NULL);	
//time format
m_12hour_format=g_key_file_get_integer(kf, "calendar_settings", "hour_format", NULL);
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
g_key_file_set_integer(kf, "calendar_settings", "talk", m_talk);
g_key_file_set_integer(kf, "calendar_settings", "talk_location", m_talk_location);
g_key_file_set_integer(kf, "calendar_settings", "talk_description", m_talk_description);
//time format
g_key_file_set_integer(kf, "calendar_settings", "hour_format", m_12hour_format);
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

//======================================================================
//removers
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

static char* remove_ampersand (const char *text)
{
GString *str;
const char *p;
str = g_string_new ("");
p = text;
while (*p)
{
gunichar cp = g_utf8_get_char(p);
if ( cp != '&' ){ 
g_string_append_unichar (str, *p);
}//if
++p;
}
return g_string_free (str, FALSE);
}


//======================================================================
//Export ical
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
//gint is_multiday = 0;
gint is_priority = 0;

//gint has_reminder = 0;
//gint reminder_hour = 0;
//gint reminder_min = 0;
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
//=======================================================================

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


//======================================================================
//Import
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
gtk_file_dialog_open (dialog, NULL, NULL, file_open_response, NULL); //no longer signal based

g_object_set_data(G_OBJECT(dialog), "dialog-window-key",window);	
g_object_unref (dialog);

}
//======================================================================
static void file_open_response (GObject *source, GAsyncResult *result, void *user_data)
{
//GtkWidget *window = user_data;
GtkFileDialog *dialog = GTK_FILE_DIALOG (source);    
GtkWidget *window = g_object_get_data(G_OBJECT(dialog), "dialog-window-key");

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
void import_ical_file(gpointer user_data) 
{	
	GtkWidget *window = user_data; //need window to get calendar
	GtkWidget *calendar = g_object_get_data(G_OBJECT(window), "window-calendar-key");
	
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

	GDateTime *today;
	today = g_date_time_new_now_local();
	int today_year = g_date_time_get_year(today);
	int today_month = g_date_time_get_month(today);
	int today_day = g_date_time_get_day_of_month(today);	

		
	gtk_calendar_select_day (GTK_CALENDAR(calendar), today); //being depreciated and replaced by		
		//gtk_calendar_set_date (GTK_CALENDAR(calendar), today); //gtk4.20 onwards -unstable do not use
	
	update_calendar(GTK_CALENDAR(calendar), window);
	
	g_date_time_unref(today);
	g_object_unref(file);   	
	g_object_unref (input_stream);
	g_object_unref (file_stream);

}
//======================================================================
//Delete all (danger zone) -ask for confirmation
//======================================================================
static void callbk_confirm_delete_all(GtkButton *button, gpointer  user_data)
{	
GtkWindow *window =user_data;	
GtkWidget *calendar =g_object_get_data(G_OBJECT(window), "window-calendar-key");

GtkWidget *dialog = g_object_get_data(G_OBJECT(button), "dialog-key");

db_delete_all();
  		
update_calendar(GTK_CALENDAR(calendar), window);
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
// Get strings
//======================================================================

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
//=====================================================================
char* get_month_string(int month) {

	char* result ="";
	
	switch(month) {
	case 1:
	result = "January";
	break;
	case 2:
	result = "February";
	break;
	case 3:
	result= "March";
	break;
	case 4:
	result = "April";
	break;
	case 5:
	result ="May";
	break;
	case 6:
	result = "June";
	break;
	case 7:
	result ="July";
	break;
	case 8:
	result ="August";
	break;
	case 9:
	result= "September";
	break;
	case 10:
	result = "October";
	break;
	case 11:
	result = "November";
	break;
	case 12:
	result = "December";
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
//GTASK talking
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

  char* text =task_data;
   
   if (m_talk ==0) 
   {
   m_talking=FALSE;
   return;
   }
   
   
   gchar *cur_dir;	
   cur_dir = g_get_current_dir ();	
   //g_print("current directory = %s\n", cur_dir);
   
   if (!g_file_test(g_build_filename(cur_dir, "flite_cmu_us_kal16", NULL), G_FILE_TEST_IS_REGULAR)) 
   {
   //g_print("flite does not exist\n");
   return;
   }
   else 
   {   
  // g_print("flite exists\n");
   m_talking=TRUE; //stop any new speaking 
   gchar * command_str ="./flite_cmu_us_kal16"; //rms voice
   command_str= g_strconcat(command_str," -t "," '",text,"' ", NULL);
   system(command_str);
   }  
   
   g_task_return_boolean(task, TRUE);	  
}


//=====================================================================
static void callbk_speaktime(GSimpleAction * action, GVariant *parameter, gpointer user_data)
{	
	GDateTime *dt = g_date_time_new_now_local(); 
	gint hour =g_date_time_get_hour(dt);	
	gint min= g_date_time_get_minute(dt);	
	
	if(m_talking==FALSE) speak_time(hour,min);
	g_date_time_unref (dt);
}
//=====================================================================
static void speak_time(gint hour, gint min) 
{	
	
	if(m_talk==0) return;
	if (m_talking ==TRUE) return;
	
	char* speak_str ="";
	
	speak_str= g_strconcat(speak_str, " the time is ", NULL);
	
	gchar* hour_str="";
	gchar* min_str="";
	gchar* ampm_str="";
	//GList *speak_word_list = NULL;
	
	if(m_12hour_format) {
	
	if (hour >= 13 && hour <= 23)
	{
	int s_hour = hour - 12;
	ampm_str = " p.m. ";					
	hour_str =get_cardinal_string(s_hour);
	}
	if(hour == 12)
	{
	ampm_str = " p.m. ";					
	hour_str =get_cardinal_string(hour);
	}
	if(hour <12)
	{
	ampm_str = " a.m. ";					
	hour_str =get_cardinal_string(hour);
	}	
	
	speak_str= g_strconcat(speak_str, hour_str, " ", NULL);
	
	if (min > 0 && min < 10)
	{	
	//speak_str= g_strconcat(speak_str, "zero ", NULL);
	speak_str= g_strconcat(speak_str, "O ", NULL);
	min_str=get_cardinal_string(min);	
	speak_str= g_strconcat(speak_str, min_str, " ", NULL);
	}
	else if(min >=10)
	{
	min_str=get_cardinal_string(min);
	
	speak_str= g_strconcat(speak_str, min_str, " ", NULL);
	}	
	
	speak_str= g_strconcat(speak_str, ampm_str, " ", NULL);
	
	} //12hour format
	
	else
	{				
	hour_str =get_cardinal_string(hour);	
	speak_str= g_strconcat(speak_str, hour_str, " ", NULL);
	
	if (min > 0 && min < 10)
	{	
	speak_str= g_strconcat(speak_str, " o ", NULL);
	min_str=get_cardinal_string(min);	
	speak_str= g_strconcat(speak_str, min_str, " ", NULL);
	}
	else if(min >=10)
	{
	min_str=get_cardinal_string(min);	
	speak_str= g_strconcat(speak_str, min_str, " ", NULL);
	}			    				
	} //24 hour format
	
	GTask* task = g_task_new(NULL, NULL, task_callbk, NULL);
	g_task_set_task_data (task,speak_str,NULL);
	
	g_task_run_in_thread(task, play_audio_async);     
	g_object_unref(task);
}

//=====================================================================
static void callbk_speak(GSimpleAction* action, GVariant *parameter,gpointer user_data)
{	
	GtkWidget *calendar =user_data;
	
	GDateTime *cal_date = gtk_calendar_get_date(GTK_CALENDAR(calendar));
	
	int day = g_date_time_get_day_of_month(cal_date);
	int month =g_date_time_get_month(cal_date);
	int year=g_date_time_get_year(cal_date);
	g_date_time_unref(cal_date);	
	
	speak_events(day,month,year);
	
}

//=====================================================================
static void speak_events(int day, int month, int year)
{	
	if(m_talk==0) return;
	if (m_talking ==TRUE) return;
	
	char* speak_str ="";
				
	gchar *dow_str=get_day_of_week(day, month, year);	//get day of week	
	gchar *day_number_str=get_day_number_ordinal_string(day); //get day number
	gchar *month_str=get_month_string(month); //get month
	
	speak_str= g_strconcat(speak_str, dow_str," ", NULL);
	speak_str= g_strconcat(speak_str, day_number_str," ", NULL);
	speak_str= g_strconcat(speak_str, month_str,". ", NULL);
	
	GArray *day_events_arry =g_array_new(FALSE, FALSE, sizeof(CALENDAR_TYPE_EVENT));
	db_get_all_events_year_month_day(day_events_arry ,year,month,day);
	//int event_number = day_events_arry->len;
	
	for (int i = 0; i < day_events_arry->len; i++)
	{
	//gint evt_id = 0;
	gchar *summary_str = "";
	gchar *location_str = "";
	gchar *description_str = "";
	gint start_hour = 0;
	gint start_min = 0;
	gint is_allday = 0;
	gint is_priority = 0;
	
	CalendarEvent *evt = g_array_index(day_events_arry, CalendarEvent *, i);
	
	g_object_get(evt, "summary", &summary_str, NULL);
	g_object_get(evt, "description", &description_str, NULL);
	g_object_get(evt, "location", &location_str, NULL);		
	g_object_get(evt, "starthour", &start_hour, NULL);
	g_object_get(evt, "startmin", &start_min, NULL);		
	g_object_get(evt, "isallday", &is_allday, NULL);
	g_object_get(evt, "ispriority", &is_priority, NULL);		
	
	//Get time first
	gchar* hour_str="";
	gchar* min_str="";
	gchar* ampm_str="";
	
	if(!is_allday) {		
	
	if(m_12hour_format) {
	
	if (start_hour >= 13 && start_hour <= 23)
	{
	int s_hour = start_hour - 12;
	ampm_str = " p.m. ";					
	hour_str =get_cardinal_string(s_hour);
	}
	if(start_hour == 12)
	{
	ampm_str = " p.m. ";					
	hour_str =get_cardinal_string(start_hour);
	}
	if(start_hour <12)
	{
	ampm_str = " a.m. ";					
	hour_str =get_cardinal_string(start_hour);
	}
	
	speak_str= g_strconcat(speak_str, hour_str," ", NULL);
	
	if (start_min > 0 && start_min< 10)
	{				
	
	//speak_str= g_strconcat(speak_str, "zero ", NULL);
	speak_str= g_strconcat(speak_str, "O ", NULL);
	min_str=get_cardinal_string(start_min);		
	speak_str= g_strconcat(speak_str, min_str," ", NULL);
	}
	else if(start_min >=10)
	{
	min_str=get_cardinal_string(start_min);	
	speak_str= g_strconcat(speak_str, min_str," ", NULL);
	}
	
	speak_str= g_strconcat(speak_str, ampm_str," ", NULL);
	
	} //12hour format
	
	else
	{				
	hour_str =get_cardinal_string(start_hour);		
	speak_str= g_strconcat(speak_str, hour_str," ", NULL);
	
	if (start_min > 0 && start_min < 10)
	{
	speak_str= g_strconcat(speak_str, "zero ", NULL);
	min_str=get_cardinal_string(start_min);		
	speak_str= g_strconcat(speak_str, min_str," ", NULL);
	}
	else if(start_min >=10)
	{
	min_str=get_cardinal_string(start_min);		
	speak_str= g_strconcat(speak_str, min_str," ", NULL);
	}			    				
	} //24 hour format
	
	} //not allday	
	
	//now add event summary	to speak str		
	speak_str= g_strconcat(speak_str,summary_str,". ", NULL);
	
	if(m_talk_description)
	{
	speak_str= g_strconcat(speak_str,description_str,". ", NULL);
	}
	
	if(m_talk_location)
	{
	speak_str= g_strconcat(speak_str,location_str,". ", NULL);
	}
	
	if(is_priority) {		
	speak_str= g_strconcat(speak_str,"  high priority ", NULL);
	}
	
	//speak_str= g_strconcat(speak_str," ", NULL);//space between events
	
	if(i < day_events_arry->len-1)
    {
		speak_str= g_strconcat(speak_str,". and. ", NULL);//then events    
    }
	
	} //for day events
	
	g_array_free(day_events_arry, TRUE);
	
	GTask* task = g_task_new(NULL, NULL, task_callbk, NULL);
	g_task_set_task_data (task,speak_str,NULL);
	
	g_task_run_in_thread(task, play_audio_async);     
	g_object_unref(task);
}

//======================================================================
//======================================================================
//Search
//======================================================================
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
//gint evt_id = 0;
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

//if (m_show_end_time)
//{

//if (m_12hour_format)
//{
//ampm_str = "";

//if (end_hour >= 13 && end_hour <= 23)
//{
//end_hour = end_hour - 12;
//ampm_str = "pm ";
//endhour_str = g_strdup_printf("%d", end_hour);
//}
//else
//{
//ampm_str = "am ";
//endhour_str = g_strdup_printf("%d", end_hour);
//}
//} // 12
//else
//{
//endhour_str = g_strdup_printf("%d", end_hour);
//} // 24

//endmin_str = g_strdup_printf("%d", end_min);

//if (end_min < 10)
//{
//time_str = g_strconcat(time_str, "to ", endhour_str, ":0", endmin_str, NULL);
//}
//else
//{
//time_str = g_strconcat(time_str, "to ", endhour_str, ":", endmin_str, NULL);
//}
//time_str = g_strconcat(time_str, ampm_str, NULL);
//} // show_end_time	

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

	//GtkWidget *window = user_data;
	
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
//gint response;

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

//======================================================================
// Easter tool
//======================================================================
GDate* calculate_easter(gint year) {

GDate *edate;

gint Yr = year;
gint a = Yr % 19;
gint b = Yr / 100;
gint c = Yr % 100;
gint d = b / 4;
gint e = b % 4;
gint f = (b + 8) / 25;
gint g = (b - f + 1) / 3;
gint h = (19 * a + b - d - g + 15) % 30;
gint i = c / 4;
gint k = c % 4;
gint L = (32 + 2 * e + 2 * i - h - k) % 7;
gint m = (a + 11 * h + 22 * L) / 451;
gint month = (h + L - 7 * m + 114) / 31;
gint day = ((h + L - 7 * m + 114) % 31) + 1;
edate = g_date_new_dmy(day, month, year);

return edate;
}
//=====================================================================

static void callbk_calc_easter(GtkButton *button, gpointer user_data)
{

GtkWidget *label_result= g_object_get_data(G_OBJECT(button), "label-result-key");
GtkWidget *spin_button_year=g_object_get_data(G_OBJECT(button), "spin-year-key");;

int easter_year= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_year));

GDate *easter_date =calculate_easter(easter_year);
int easter_day = g_date_get_day(easter_date);
int easter_month =g_date_get_month(easter_date);


char* easter_month_str = get_month_string(easter_month);
char *easter_day_str = g_strdup_printf("%i",easter_day);
char *easter_year_str = g_strdup_printf("%i",easter_year);

char *weekday=get_day_of_week(easter_day, easter_month, easter_year);
//weekday must be a sunday

const char* result_str="";

result_str = g_strconcat(weekday, " ", easter_day_str, " ", easter_month_str, " ", easter_year_str, NULL);

gtk_label_set_text(GTK_LABEL(label_result),result_str);

}
//======================================================================

//static void callbk_spin_easter_year(GtkSpinButton *button, gpointer user_data)
//{	
//m_easter_year = gtk_spin_button_get_value_as_int (button);	
//}
//======================================================================
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
//g_signal_connect(GTK_SPIN_BUTTON(spin_button_year), "value_changed", G_CALLBACK(callbk_spin_easter_year), NULL);		
//gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_button_year), start_year);

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
int file_exists(const char *file_name)
{
    FILE *file;
    file = fopen(file_name, "r");
    if (file){       
        fclose(file);
        return 1; //file exists return 1
    }
    return 0; //file does not exist
}

GListStore *load_store()
{		
	GListStore *store=NULL;
	store = g_list_store_new(G_TYPE_OBJECT);
	
	GArray *all_events_arry =g_array_new(FALSE, FALSE, sizeof(CALENDAR_TYPE_EVENT));
	
	db_get_all_events(all_events_arry);
	
	int event_number = all_events_arry->len;	
		
	for (int i = 0; i < event_number; i++)
	{
		
		gchar *summary_str = "";
		gchar *location_str = "";
		gchar *description_str = "";
		
		gint start_day=0;
		gint start_month=0;
		gint start_year =0;
		gint start_hour = 0;
		gint start_min = 0;
		
		gint end_day=0;
		gint end_month=0;
		gint end_year =0;
		gint end_hour = 0;
		gint end_min = 0;
		
		gint is_yearly =0;
		gint is_allday = 0;
		gint is_priority = 0;
		
		CalendarEvent *evt = g_array_index(all_events_arry, CalendarEvent *, i);
		
		g_object_get(evt, "summary", &summary_str, NULL);
		g_object_get(evt, "description", &description_str, NULL);
		g_object_get(evt, "location", &location_str, NULL);		
		
		g_object_get(evt, "startday", &start_day, NULL);
		g_object_get(evt, "startmonth", &start_month, NULL);
		g_object_get(evt, "startyear", &start_year, NULL);		
		g_object_get(evt, "starthour", &start_hour, NULL);
		g_object_get(evt, "startmin", &start_min, NULL);
		
		g_object_get(evt, "endday", &end_day, NULL);
		g_object_get(evt, "endmonth", &end_month, NULL);
		g_object_get(evt, "endyear", &end_year, NULL);	
		g_object_get(evt, "isyearly", &is_yearly, NULL);		
		g_object_get(evt, "isallday", &is_allday, NULL);
		g_object_get(evt, "ispriority", &is_priority, NULL);	
		
		g_list_store_append(store,evt);
	}
	
	return store;	
}

//======================================================================


static void callbk_setup_listitem (GtkListItemFactory *factory,
                   GtkListItem        *list_item)
{
 
  GtkWidget *label = gtk_label_new ("");
  gtk_list_item_set_child (list_item, label);
}


//======================================================================
static void callbk_bind_listitem (GtkListItemFactory *factory,
                  GtkListItem        *list_item)
{
  GtkWidget *label;
  //MyObject *obj;
  CalendarEvent *event;

  label = gtk_list_item_get_child (list_item);
  gtk_widget_set_halign (GTK_WIDGET(label), GTK_ALIGN_START);
  gtk_label_set_use_markup(GTK_LABEL(label), TRUE);

  event = gtk_list_item_get_item (list_item);
  
  const char *summary = calendar_event_get_summary(CALENDAR_EVENT(event));
  const char *description = calendar_event_get_description(CALENDAR_EVENT(event));
  const char  *location =calendar_event_get_location(CALENDAR_EVENT(event));
  
  int start_day =calendar_event_get_start_day(CALENDAR_EVENT(event));
  int start_month =calendar_event_get_start_month(CALENDAR_EVENT(event));
  int start_year =calendar_event_get_start_year(CALENDAR_EVENT(event));
  
  //char* day_str =g_strdup_printf("%d",day);
  //char* month_str =g_strdup_printf("%d",month);
  //char* year_str =g_strdup_printf("%d",year);
  //char* date_str="";
  //char* dow =get_day_of_week(start_day,start_month,start_year);
  char* day_str = g_strdup_printf("%d",start_day);
  //char* month_str = g_strdup_printf("%d",month);	
  char *month_str =get_month_string(start_month);	
  char* year_str = g_strdup_printf("%d",start_year);
  char* date_str="";
  
  date_str= g_strconcat(date_str,day_str, " ",month_str, " ",year_str, NULL);
  
  char *date_str_markup = g_strdup_printf("%s%s%s", "<b>", date_str, "</b>");
  
  int start_hour =calendar_event_get_start_hour(CALENDAR_EVENT(event));
  int start_min = calendar_event_get_start_min(CALENDAR_EVENT(event));
  int is_allday = calendar_event_get_is_allday(CALENDAR_EVENT(event));
  //char* start_hour_str =g_strdup_printf("%d",start_hour);
  //char* start_min_str =g_strdup_printf("%d",start_min);
  
  char *des_loc_str="";
  char *time_str = "";
  char* display_str="";
  
  display_str =g_strconcat(display_str, date_str_markup, "\n",NULL);
  
  if(!is_allday)
   {		
	//calendar display
	time_str =get_time_str(start_hour,start_min);
	display_str = g_strconcat(display_str, time_str, summary, "\n",NULL);
	
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
	else //alday
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
		des_loc_str = g_strconcat(des_loc_str, location, ".",NULL);
		}		
	}  
	
	  display_str =g_strconcat(display_str,des_loc_str,NULL);
  
  //display_str =g_strconcat(display_str,
  //day_str, "-",month_str,"-",year_str, "\n",
  //start_hour_str,":",start_min_str," ",
  //summary, "\n",
  //description,". ", location,NULL);
  
  gtk_label_set_label (GTK_LABEL (label), display_str);
                       //my_object_get_string (obj));
}

//======================================================================
static void callbk_listview (GtkListView  *list,
             guint         position,
             gpointer      unused)
{
	//g_print("callbk_listview_acitvated (setup)\n");
	
}
//======================================================================

//======================================================================
//Add new event
//======================================================================
static void callbk_add_new_event(GtkButton *button, gpointer user_data)
{	
	//g_return_if_fail(GTK_IS_BUTTON(button));
	GListStore *store =user_data;
	
	GtkWidget *window = g_object_get_data(G_OBJECT(button), "button-add-window-key");
	GtkWidget *calendar = g_object_get_data(G_OBJECT(button), "button-add-calendar-key");
	
	
	int start_day =GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "day-key"));
	int start_month =GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "month-key"));
	int start_year =GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "year-key"));
	
	int end_day =start_day;
	int end_month =start_month;
	int end_year =start_year;
	
	//GtkWidget *window = g_object_get_data(G_OBJECT(button), "window-key");
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
	
	//buffer_summary = gtk_entry_get_buffer (GTK_ENTRY(entry_summary));
	//const char* summary= gtk_entry_buffer_get_text (buffer_summary);
	
	//buffer_description = gtk_entry_get_buffer (GTK_ENTRY(entry_description));
	//const char* description= gtk_entry_buffer_get_text (buffer_description);
	
	//buffer_location = gtk_entry_get_buffer (GTK_ENTRY(entry_location));
	//const char* location= gtk_entry_buffer_get_text (buffer_location);
	
	buffer_summary = gtk_entry_get_buffer(GTK_ENTRY(entry_summary));
	const char* summary = gtk_entry_buffer_get_text(buffer_summary);
	summary = remove_semicolons(summary);
	summary = remove_commas(summary);
	summary =remove_punctuations(summary);
	summary =remove_ampersand(summary); //& cause markup error
	
	
	buffer_description = gtk_entry_get_buffer(GTK_ENTRY(entry_description));
	const char* description = gtk_entry_buffer_get_text(buffer_description);
	description = remove_semicolons(description);
	description = remove_commas(description);
	description =remove_punctuations(description);
	description =remove_ampersand(description);
	
	buffer_location = gtk_entry_get_buffer(GTK_ENTRY(entry_location));
	const char* location = gtk_entry_buffer_get_text(buffer_location);
	location = gtk_entry_buffer_get_text(buffer_location);
	location = remove_semicolons(location);
	location = remove_commas(location);
	location =remove_punctuations(location);
	location =remove_ampersand(location);
	
	int start_hour= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_start_hour));
	int start_min= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_start_min));
	int end_hour= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_end_hour));
	int end_min= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_end_min));
	
	int is_allday = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_allday));	
	int is_yearly = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_isyearly));	
	int is_priority = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_priority));
		
	CalendarEvent *event_new= g_object_new(CALENDAR_TYPE_EVENT,0);
	
	g_object_set(event_new, "summary", g_strdup(summary), NULL);
	g_object_set(event_new, "location", g_strdup(location), NULL);
	g_object_set(event_new, "description", g_strdup(description), NULL);
	g_object_set(event_new, "startyear", start_year, NULL);
	g_object_set(event_new, "startmonth", start_month, NULL);
	g_object_set(event_new, "startday", start_day, NULL);
	g_object_set(event_new, "starthour", start_hour, NULL);
	g_object_set(event_new, "startmin", start_min, NULL);
	g_object_set(event_new, "endyear", end_year, NULL); // to do
	g_object_set(event_new, "endmonth", end_month, NULL);
	g_object_set(event_new, "endday", end_day, NULL);
	g_object_set(event_new, "endhour", end_hour, NULL);
	g_object_set(event_new, "endmin", end_min, NULL);
	g_object_set(event_new, "isyearly", is_yearly, NULL);
	g_object_set(event_new, "isallday", is_allday, NULL);			
	g_object_set(event_new, "ispriority", is_priority, NULL);
	
	db_insert_event(event_new); //insert event into database
	
	g_list_store_append(G_LIST_STORE(store),event_new);      
		
	update_calendar(GTK_CALENDAR(calendar),window);
		
	gtk_window_destroy(GTK_WINDOW(dialog));	

}


//======================================================================
// New event
//======================================================================

static void callbk_new_event(GtkButton *button, gpointer user_data)
{	
	GListStore *store =user_data;		
	GtkWidget *window = g_object_get_data(G_OBJECT(button), "button-new-window-key");
	GtkWidget *calendar = g_object_get_data(G_OBJECT(button), "button-new-calendar-key");
	
	//get selected date
	GDateTime* cal_date;  
	cal_date = gtk_calendar_get_date(GTK_CALENDAR(calendar));
	
	int day = g_date_time_get_day_of_month(cal_date);
	int month =g_date_time_get_month(cal_date);
	int year=g_date_time_get_year(cal_date);	
	char* day_str = g_strdup_printf("%d",day);
	char* month_str = g_strdup_printf("%d",month);
	char* year_str = g_strdup_printf("%d",year);
	char* date_str="";
	date_str= g_strconcat(date_str, day_str, "-",month_str, "-",year_str, NULL);
	g_date_time_unref(cal_date);
	
	
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
	//GtkWidget *label_spacer5;
		
	// Check buttons
	GtkWidget *check_button_allday;	
	GtkWidget *check_button_isyearly;
	GtkWidget *check_button_priority;
	//GtkWidget *check_button_notification;
	
	GtkWidget *label_start_time;
	GtkWidget *spin_button_start_hour;	
	GtkWidget *spin_button_start_min;
	//end time
	GtkWidget *label_end_time;
	GtkWidget *spin_button_end_hour;	
	GtkWidget *spin_button_end_min;	
		
	//GtkAdjustment *adjustment_year_end = gtk_adjustment_new(2024.00, 0.0, 5000.00, 1.0, 1.0, 0.0);
	dialog = gtk_window_new(); // gtk_dialog_new_with_buttons deprecated gtk4.10
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
	//label_spacer5 = gtk_label_new("");
	
	button_add_event = gtk_button_new_with_label ("Add Event");
	//g_signal_connect (button_add, "clicked", G_CALLBACK (callbk_add_new_contact), store);
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
	
	gtk_window_set_child (GTK_WINDOW (dialog), grid);	
	gtk_window_present(GTK_WINDOW(dialog));

}
//======================================================================
// update event
//======================================================================
static void callbk_update_event(GtkButton *button, gpointer user_data)
{
	GtkWidget *window =user_data;
	GtkWidget *calendar = g_object_get_data(G_OBJECT(window), "window-calendar-key");
	GtkWidget *dialog = g_object_get_data(G_OBJECT(button), "dialog-key");
	
	int id =GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "id-key"));
	
	int start_day =GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "day-key"));
	int start_month =GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "month-key"));
	int start_year =GPOINTER_TO_INT(g_object_get_data(G_OBJECT(button), "year-key"));
	
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
	
	//buffer_summary = gtk_entry_get_buffer (GTK_ENTRY(entry_summary));
	//const char* summary= gtk_entry_buffer_get_text (buffer_summary);
	
	//buffer_description = gtk_entry_get_buffer (GTK_ENTRY(entry_description));
	//const char* description= gtk_entry_buffer_get_text (buffer_description);
	
	//buffer_location = gtk_entry_get_buffer (GTK_ENTRY(entry_location));
	//const char* location= gtk_entry_buffer_get_text (buffer_location);
	
	buffer_summary = gtk_entry_get_buffer(GTK_ENTRY(entry_summary));
	const char* summary = gtk_entry_buffer_get_text(buffer_summary);
	summary = remove_semicolons(summary);
	summary = remove_commas(summary);
	summary =remove_punctuations(summary);
	summary =remove_ampersand(summary);
	
	buffer_description = gtk_entry_get_buffer(GTK_ENTRY(entry_description));
	const char* description = gtk_entry_buffer_get_text(buffer_description);
	description = remove_semicolons(description);
	description = remove_commas(description);
	description =remove_punctuations(description);
	description =remove_ampersand(description);
	
	buffer_location = gtk_entry_get_buffer(GTK_ENTRY(entry_location));
	const char* location = gtk_entry_buffer_get_text(buffer_location);
	location = gtk_entry_buffer_get_text(buffer_location);
	location = remove_semicolons(location);
	location = remove_commas(location);
	location =remove_punctuations(location);
	location =remove_ampersand(location);
	
	int start_hour= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_start_hour));
	int start_min= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_start_min));
	int end_hour= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_end_hour));
	int end_min= gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin_button_end_min));
	
	int is_allday = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_allday));	
	int is_yearly = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_isyearly));	
	int is_priority = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_priority));
		
	CalendarEvent *event_update= g_object_new(CALENDAR_TYPE_EVENT,0);
	
	g_object_set(event_update, "summary", g_strdup(summary), NULL);
	g_object_set(event_update, "location", g_strdup(location), NULL);
	g_object_set(event_update, "description", g_strdup(description), NULL);
	g_object_set(event_update, "startyear", start_year, NULL);
	g_object_set(event_update, "startmonth", start_month, NULL);
	g_object_set(event_update, "startday", start_day, NULL);
	g_object_set(event_update, "starthour", start_hour, NULL);
	g_object_set(event_update, "startmin", start_min, NULL);
	g_object_set(event_update, "endyear", end_year, NULL); // to do
	g_object_set(event_update, "endmonth", end_month, NULL);
	g_object_set(event_update, "endday", end_day, NULL);
	g_object_set(event_update, "endhour", end_hour, NULL);
	g_object_set(event_update, "endmin", end_min, NULL);
	g_object_set(event_update, "isyearly", is_yearly, NULL);
	g_object_set(event_update, "isallday", is_allday, NULL);			
	g_object_set(event_update, "ispriority", is_priority, NULL);
		
	db_update_event(event_update,id);
	
	update_calendar(GTK_CALENDAR(calendar), window);
	
	gtk_window_destroy(GTK_WINDOW(dialog));
}



//======================================================================
// Edit event
//======================================================================
static void callbk_edit_event(GtkButton *button, gpointer user_data)
{	
	GtkSingleSelection *selection=user_data;			
	GListStore *store = g_object_get_data(G_OBJECT(button), "button-edit-store-key");
	GtkWidget *window = g_object_get_data(G_OBJECT(button), "button-edit-window-key");;
	CalendarEvent* selectedevent = gtk_single_selection_get_selected_item (GTK_SINGLE_SELECTION(selection));
	
	int id_key =db_get_id(selectedevent);
	char* id_key_str =g_strdup_printf("%d",id_key);
	
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
	
	//char* start_hour_str =g_strdup_printf("%d",start_hour);
	//char* start_min_str =g_strdup_printf("%d",start_min);
	
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
	//GtkWidget *label_spacer5;
		
	// Check buttons
	GtkWidget *check_button_allday;	
	GtkWidget *check_button_isyearly;
	GtkWidget *check_button_priority;
	//GtkWidget *check_button_notification;
	
	GtkWidget *label_start_time;
	GtkWidget *spin_button_start_hour;	
	GtkWidget *spin_button_start_min;
	//end time
	GtkWidget *label_end_time;
	GtkWidget *spin_button_end_hour;	
	GtkWidget *spin_button_end_min;	
		
	//GtkAdjustment *adjustment_year_end = gtk_adjustment_new(2024.00, 0.0, 5000.00, 1.0, 1.0, 0.0);
	dialog = gtk_window_new(); // gtk_dialog_new_with_buttons deprecated gtk4.10
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
	//label_spacer5 = gtk_label_new("");
	
	button_update = gtk_button_new_with_label ("Update Selected Event");
    g_signal_connect (GTK_BUTTON (button_update),"clicked", G_CALLBACK (callbk_update_event), G_OBJECT (window));
	
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
	
	g_object_set_data(G_OBJECT(button_update), "id-key",GINT_TO_POINTER(id_key));
	g_object_set_data(G_OBJECT(button_update), "day-key",GINT_TO_POINTER(start_day));
	g_object_set_data(G_OBJECT(button_update), "month-key",GINT_TO_POINTER(start_month));
	g_object_set_data(G_OBJECT(button_update), "year-key",GINT_TO_POINTER(start_year));
	
	g_object_set_data(G_OBJECT(button_update), "dialog-key",dialog);
	g_object_set_data(G_OBJECT(button_update), "window-key",window);
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
	
	gtk_window_set_child (GTK_WINDOW (dialog), grid);	
	gtk_window_present(GTK_WINDOW(dialog));
	
	
}

static void callbk_find_event(GtkButton *button, gpointer user_data)
{
	GtkWidget *window = g_object_get_data(G_OBJECT(button), "button-find-window-key");
	GtkWidget *calendar = g_object_get_data(G_OBJECT(button), "button-find-calendar-key");	
	GtkSingleSelection *selection=user_data;	
	CalendarEvent* selectedevent = gtk_single_selection_get_selected_item (GTK_SINGLE_SELECTION(selection));
	  
	 if(selectedevent==NULL) return;
	 
	 int start_day=0;
	 int start_month=0;
	 int start_year =0;	 
	 
	 g_object_get(selectedevent, "startday", &start_day, NULL);
	 g_object_get(selectedevent, "startmonth", &start_month, NULL);
	 g_object_get(selectedevent, "startyear", &start_year, NULL);	
	
	 gtk_calendar_set_day(GTK_CALENDAR(calendar),start_day);
	 gtk_calendar_set_month(GTK_CALENDAR(calendar),start_month-1);
	 gtk_calendar_set_year(GTK_CALENDAR(calendar),start_year);
	
	 speak_events(start_day,start_month,start_year); 
	
}

//======================================================================
// Delete event
//======================================================================

static void callbk_delete_event(GtkButton *button, gpointer user_data)
{	
	GtkWidget *window = g_object_get_data(G_OBJECT(button), "button-delete-window-key");
	GtkWidget *calendar = g_object_get_data(G_OBJECT(button), "button-delete-calendar-key");
	GtkSingleSelection *selection=user_data;
	
	GListModel *model = gtk_single_selection_get_model(selection);
    GListStore *store = G_LIST_STORE(model);
    
	guint p = gtk_single_selection_get_selected((GtkSingleSelection*)selection);	
	
	CalendarEvent* selectedevent = gtk_single_selection_get_selected_item (GTK_SINGLE_SELECTION(selection));

	 gchar *summary_str = "";
	 gchar *description_str = "";	
	 gchar *location_str = "";	
	 
	 g_object_get(selectedevent, "summary", &summary_str, NULL);
	 g_object_get(selectedevent, "description", &description_str, NULL);
	 g_object_get(selectedevent, "location", &location_str, NULL);
	
	 g_print("Selected Event: summary = %s description = %s location = %s \n",summary_str,description_str,location_str); 
          
     //remove from store
     g_list_store_remove(G_LIST_STORE(store),p); 
     //remove from db
     db_delete_event(selectedevent); 
     
     update_calendar(GTK_CALENDAR(calendar), window);	 
}
//======================================================================
// Calendar
//======================================================================
static void update_calendar(GtkCalendar *calendar, gpointer user_data)
{
	 //GtkWidget *label_date = (GtkWidget *)user_data;
	GtkWidget *window = user_data;
	GListStore *store =g_object_get_data(G_OBJECT(window), "window-store-key");
	GtkWidget *label_date=g_object_get_data(G_OBJECT(window), "window-label-date-key");
	
	GDateTime *cal_date = gtk_calendar_get_date(GTK_CALENDAR(calendar));
	
	int selected_day = g_date_time_get_day_of_month(cal_date);
	int selected_month =g_date_time_get_month(cal_date);
	int selected_year=g_date_time_get_year(cal_date);
	g_date_time_unref(cal_date);
		
	char* dow =get_day_of_week(selected_day, selected_month,selected_year);
	
	char* day_str = g_strdup_printf("%d",selected_day);
	//char* month_str = g_strdup_printf("%d",month);	
	char *month_str =get_month_string(selected_month);	
	char* year_str = g_strdup_printf("%d",selected_year);
	char* date_str="";
	
	date_str= g_strconcat(date_str, dow, " ",day_str, " ",month_str, " ",year_str, NULL);
	//gtk_label_set_text(GTK_LABEL(label_date), date_str);	
	
    char *date_str_markup = g_strdup_printf("%s%s%s", "<b>", date_str, "</b>");
	gtk_label_set_label (GTK_LABEL (label_date), date_str_markup);
	
	
	//update store with month events
	GArray *evt_arry_month; //standard month events
	evt_arry_month = g_array_new(FALSE, FALSE, sizeof(CALENDAR_TYPE_EVENT));	
	db_get_all_events_year_month(evt_arry_month, selected_year,selected_month);
	
	gtk_calendar_clear_marks(GTK_CALENDAR(calendar));
	g_list_store_remove_all(G_LIST_STORE(store));
	
	for (int i=0; i<evt_arry_month->len; i++) {  
		
		gint day=0;
		gint month=0;
		gint year=0;
			
		CalendarEvent *evt =g_array_index(evt_arry_month, CalendarEvent*, i);
		
		g_object_get (evt, "startday", &day, NULL);
		g_object_get (evt, "startmonth", &month, NULL);
		g_object_get (evt, "startyear", &year, NULL);
		
		//append event to store
		g_list_store_append(G_LIST_STORE(store),evt);   
		//place a visual marker on day of the current month
		gtk_calendar_mark_day(GTK_CALENDAR(calendar),day);
  	
     }//for
   	
	g_array_free(evt_arry_month, FALSE); 
	speak_events(selected_day,selected_month,selected_year);	
}
//======================================================================

static void callbk_calendar_home(GSimpleAction * action, GVariant *parameter, gpointer user_data)
{
	GtkWindow *window =user_data;	
	GtkWidget *calendar =g_object_get_data(G_OBJECT(window), "window-calendar-key");

	GDateTime *today;
	today = g_date_time_new_now_local();
	//int year = g_date_time_get_year(today);
	//int month = g_date_time_get_month(today);
	//int day = g_date_time_get_day_of_month(today);	
	
	gtk_calendar_select_day (GTK_CALENDAR(calendar), today); //being depreciated and replaced by		
	//gtk_calendar_set_date (GTK_CALENDAR(calendar), today); //gtk4.20 onwards -unstable do not use	
	update_calendar(GTK_CALENDAR(calendar), window);
	g_date_time_unref(today);
}




//======================================================================


static void callbk_calendar_day_selected(GtkCalendar *calendar, gpointer user_data)
{	
	GtkWidget *window=user_data;
	update_calendar(calendar,window);	
}
//======================================================================	
static void callbk_calendar_next_month(GtkCalendar *calendar, gpointer user_data)
{	
	GtkWidget *window = user_data;
	update_calendar(calendar, window);	
}
//======================================================================
static void callbk_calendar_prev_month(GtkCalendar *calendar, gpointer user_data)
{	
	GtkWidget *window = user_data;
	update_calendar(calendar, window);		
}
//======================================================================
static void callbk_calendar_next_year(GtkCalendar *calendar, gpointer user_data)
{
	GtkWidget *window = user_data;
	update_calendar(calendar, window);	
}
//======================================================================
static void callbk_calendar_prev_year(GtkCalendar *calendar, gpointer user_data)
{
	GtkWidget *window = user_data;
	update_calendar(calendar, window);
}

//======================================================================
// Preferences
//======================================================================
static void callbk_set_preferences(GtkButton *button, gpointer  user_data)
{
	GtkWidget *window = user_data;   
	GtkWidget *calendar =g_object_get_data(G_OBJECT(window), "window-calendar-key");	
	GtkWidget *dialog = g_object_get_data(G_OBJECT(button), "dialog-key");
	
	GtkWidget *check_button_hour_format= g_object_get_data(G_OBJECT(button), "check-button-hour-format-key");
	GtkWidget *check_button_talk= g_object_get_data(G_OBJECT(button), "check-button-talk-key");	
	GtkWidget *check_button_talk_description= g_object_get_data(G_OBJECT(button), "check-button-talk-description-key");
	GtkWidget *check_button_talk_location= g_object_get_data(G_OBJECT(button), "check-button-talk-location-key");
	GtkWidget *check_button_reset_all= g_object_get_data(G_OBJECT(button), "check-button-reset-all-key");
	
	m_12hour_format=gtk_check_button_get_active (GTK_CHECK_BUTTON(check_button_hour_format));
	m_talk=gtk_check_button_get_active (GTK_CHECK_BUTTON(check_button_talk));	
	m_talk_description=gtk_check_button_get_active (GTK_CHECK_BUTTON(check_button_talk_description));
	m_talk_location =gtk_check_button_get_active (GTK_CHECK_BUTTON(check_button_talk_location));
	m_reset_preferences=gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_reset_all));
	
	if(m_reset_preferences) {
	//reset preferences
	m_12hour_format=1;
	m_talk=1;	
	m_talk_description=0;
	m_talk_location =0;
	m_reset_preferences=0; //toggle
	}
	config_write();	//save preferences
	update_calendar(GTK_CALENDAR(calendar),window);
	
	gtk_window_destroy(GTK_WINDOW(dialog));

}

//======================================================================
// Preferences
//======================================================================

static void callbk_preferences(GSimpleAction* action, GVariant *parameter,gpointer user_data)
{
	GtkWidget *window =user_data;
	GtkWidget *dialog;
	GtkWidget *grid;
	GtkWidget *button_set;
		
	GtkWidget *check_button_hour_format;	
	GtkWidget *check_button_talk;		
	GtkWidget *check_button_talk_description;
	GtkWidget *check_button_talk_location;
	GtkWidget *check_button_reset_all;
	
	GtkWidget *label_spacer1;
	GtkWidget *label_spacer2;
	GtkWidget *label_spacer3;
	GtkWidget *label_spacer4;		
	
	label_spacer1 = gtk_label_new("");
	label_spacer2 = gtk_label_new("");
	label_spacer3 = gtk_label_new("");
	label_spacer4 = gtk_label_new("");	
	
	dialog =gtk_window_new(); 
	gtk_window_set_title (GTK_WINDOW (dialog), "Preferences");
	gtk_window_set_modal(GTK_WINDOW (dialog),TRUE);
	gtk_window_set_transient_for(GTK_WINDOW (dialog),GTK_WINDOW(window));
		
	grid = gtk_grid_new();	
	gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	button_set = gtk_button_new_with_label ("Set Preferences");
	g_signal_connect (button_set, "clicked", G_CALLBACK (callbk_set_preferences), window);
	g_object_set_data(G_OBJECT(button_set), "dialog-key",dialog);
	
	check_button_hour_format = gtk_check_button_new_with_label ("12 Hour Format");
	check_button_talk = gtk_check_button_new_with_label ("Enable Talking");	
	check_button_talk_description = gtk_check_button_new_with_label ("Talk Description");
	check_button_talk_location = gtk_check_button_new_with_label ("Talk Location");	
	check_button_reset_all = gtk_check_button_new_with_label ("Reset All");
	
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_hour_format), m_12hour_format);
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_talk), m_talk);	
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_talk_description), m_talk_description);
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_talk_location), m_talk_location);
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_reset_all), m_reset_preferences);
	
	g_object_set_data(G_OBJECT(button_set), "dialog-key",dialog);
	g_object_set_data(G_OBJECT(button_set), "check-button-hour-format-key",check_button_hour_format);
	
	g_object_set_data(G_OBJECT(button_set), "check-button-talk-key",check_button_talk);	
	g_object_set_data(G_OBJECT(button_set), "check-button-talk-description-key",check_button_talk_description);
	g_object_set_data(G_OBJECT(button_set), "check-button-talk-location-key",check_button_talk_location);	
	
	g_object_set_data(G_OBJECT(button_set), "check-button-reset-all-key",check_button_reset_all);
	
	gtk_grid_attach(GTK_GRID(grid), check_button_hour_format,   	1, 1, 1, 1);			
	gtk_grid_attach(GTK_GRID(grid), label_spacer1,            		 1, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), check_button_talk,  			1, 3, 1, 1);	
	gtk_grid_attach(GTK_GRID(grid), label_spacer2,      			 1, 4, 1, 1);	
	gtk_grid_attach(GTK_GRID(grid), check_button_talk_description,  1, 5, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), check_button_talk_location,  	2, 5, 1, 1);	
	gtk_grid_attach(GTK_GRID(grid), label_spacer3,      	 		1, 6, 1, 1);	
	gtk_grid_attach(GTK_GRID(grid), check_button_reset_all,  		1, 7, 1, 1);	
	gtk_grid_attach(GTK_GRID(grid), label_spacer4,      	 1, 8, 1, 1);		
	gtk_grid_attach(GTK_GRID(grid), button_set,  			1, 9, 3, 1);
	
	gtk_window_set_child (GTK_WINDOW (dialog), grid);	
	gtk_window_present(GTK_WINDOW(dialog));
	
		
}
//======================================================================
void callbk_shutdown(GtkWindow *window, gint response_id, gpointer user_data)
{
gtk_window_get_default_size(GTK_WINDOW(window), &m_window_width,&m_window_height);	
config_write();	
}

//======================================================================

static void startup(GtkApplication *app)
{		
	 config_initialize();	  	
	 db_create_events_table(); //startup database 
}

//======================================================================
static void activate (GtkApplication* app, gpointer user_data)
{
	GtkWidget *window;
	GtkWidget *header;
	GtkWidget *paned;
	GtkWidget *menu_button;
	
	GtkWidget *calendar; 
	GtkWidget *box1;
	GtkWidget *box2;
	//GtkWidget *box3;
	GtkWidget *label_month_events; //display selected date
	GtkWidget *label_date; //display selected date
	GtkWidget *scrolled_window;
	
	GtkListItemFactory *factory;
	GListModel *model;
	GtkSingleSelection *selection;
	
	GtkWidget *list_view; //month view
	GtkWidget *button_new_event;
	GtkWidget *button_edit_event;
	GtkWidget *button_delete_event;
	GtkWidget *button_find_event;
	
	window = gtk_application_window_new(app);
	gtk_window_set_title (GTK_WINDOW(window), "Talk Calendar");
	gtk_window_set_default_size (GTK_WINDOW(window), m_window_width, m_window_height);
	g_signal_connect (window, "destroy", G_CALLBACK (callbk_shutdown), NULL);
	header = gtk_header_bar_new();
	gtk_window_set_titlebar(GTK_WINDOW(window), header);
	
	
	label_date = gtk_label_new("");
	gtk_label_set_xalign(GTK_LABEL(label_date), 0.5);
	gtk_label_set_use_markup(GTK_LABEL(label_date), TRUE);	
	
	calendar =gtk_calendar_new(); 
	gtk_calendar_set_show_heading(GTK_CALENDAR(calendar),TRUE);
	gtk_calendar_set_show_day_names(GTK_CALENDAR(calendar),TRUE);
	
	gtk_widget_set_hexpand (GTK_WIDGET (calendar), true);
	gtk_widget_set_vexpand (GTK_WIDGET (calendar), true); 
	//gtk_widget_set_halign(GTK_WIDGET (calendar), GTK_ALIGN_START);
	//gtk_widget_set_halign(GTK_WIDGET (calendar), GTK_ALIGN_FILL);
	//gtk_widget_set_valign(GTK_WIDGET (calendar), GTK_ALIGN_FILL);
	
	g_signal_connect(GTK_CALENDAR(calendar), "day-selected", G_CALLBACK(callbk_calendar_day_selected),window);	
	g_signal_connect(GTK_CALENDAR(calendar), "next-month", G_CALLBACK(callbk_calendar_next_month), window);
	g_signal_connect(GTK_CALENDAR(calendar), "prev-month", G_CALLBACK(callbk_calendar_prev_month), window);
	g_signal_connect(GTK_CALENDAR(calendar), "next-year", G_CALLBACK(callbk_calendar_next_year), window);
	g_signal_connect(GTK_CALENDAR(calendar), "prev-year", G_CALLBACK(callbk_calendar_prev_year), window);
	g_signal_connect(GTK_CALENDAR(calendar), "day-selected", G_CALLBACK(callbk_calendar_day_selected),window);
	
	g_object_set_data(G_OBJECT(calendar), "calendar-label-date-key",label_date);
	
	//GDateTime *cal_date = gtk_calendar_get_date(GTK_CALENDAR(calendar));	
	//int day = g_date_time_get_day_of_month(cal_date);
	//int month =g_date_time_get_month(cal_date);
	//int year=g_date_time_get_year(cal_date);
	////g_print("Date is : %d-%d-%d \n", day, month,year);
	//g_date_time_unref(cal_date);
	//char* day_str = g_strdup_printf("%d",day);
	//char* month_str = g_strdup_printf("%d",month);
	//char* year_str = g_strdup_printf("%d",year);
	//char* date_str="";
	//date_str= g_strconcat(date_str, day_str, "-",month_str, "-",year_str, NULL);
	//gtk_label_set_text(GTK_LABEL(label_date), date_str);	
		
	box2 =gtk_box_new(GTK_ORIENTATION_VERTICAL,1);	
	gtk_box_append(GTK_BOX(box2), label_date);
	gtk_box_append(GTK_BOX(box2), calendar); 
    
	label_month_events = gtk_label_new("");
	gtk_label_set_use_markup(GTK_LABEL(label_month_events), TRUE);
	char* header_str ="Month Events";
    char *header_str_markup = g_strdup_printf("%s%s%s", "<u>", header_str, "</u>");
	//gtk_label_set_text(GTK_LABEL(label_month_events), header_str_markup);
	gtk_label_set_label (GTK_LABEL (label_month_events), header_str_markup);
	gtk_label_set_xalign(GTK_LABEL(label_month_events), 0.5);
	gtk_widget_add_css_class (GTK_WIDGET(label_month_events), "frame");
	
	scrolled_window = gtk_scrolled_window_new();
	gtk_widget_set_hexpand (GTK_WIDGET (scrolled_window), true);
	gtk_widget_set_vexpand (GTK_WIDGET (scrolled_window), true);	
	
	GListStore *store=NULL;
	store = g_list_store_new(G_TYPE_OBJECT);
	
	////load up store if events.csv exists
	if(file_exists("calendar.db"))
	{
	g_print("calendar.dbv exists\n");
	store =load_store();
	}
	else
	{
	g_print("calendar.db does not exist\n");
	}
	
	selection = gtk_single_selection_new(G_LIST_MODEL(store));
	gtk_single_selection_set_autoselect(selection,FALSE);
	//create model 
	//model = create_event_model();
	
	//setup factory
	factory = gtk_signal_list_item_factory_new ();
    g_signal_connect (factory, "setup", G_CALLBACK (callbk_setup_listitem), NULL);
    g_signal_connect (factory, "bind", G_CALLBACK (callbk_bind_listitem), NULL);

	list_view = gtk_list_view_new(GTK_SELECTION_MODEL (selection),factory);
	//setup listview
	//list_view = gtk_list_view_new (GTK_SELECTION_MODEL (gtk_single_selection_new (model)), factory);
	g_signal_connect (list_view, "activate", G_CALLBACK (callbk_listview), NULL);		
	gtk_list_view_set_show_separators (GTK_LIST_VIEW(list_view),TRUE);	
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window),list_view);
	
	box1 =gtk_box_new(GTK_ORIENTATION_VERTICAL,1);
	gtk_box_append(GTK_BOX(box1), label_month_events);
	gtk_box_append(GTK_BOX(box1), scrolled_window); 
	
	g_object_set_data(G_OBJECT(window), "window-store-key",store);
	g_object_set_data(G_OBJECT(window), "window-calendar-key",calendar);
	g_object_set_data(G_OBJECT(window), "window-label-date-key",label_date);
	
	//Keyboard accelerators	
	const gchar *speak_accels[2] = { "space", NULL };
	const gchar *time_accels[2] = {"t", NULL };
	const gchar *home_accels[2] = { "Home", NULL };
	const gchar *info_accels[2] = {"F1", NULL };		
	const gchar * preferences_accels[2] = { "<Ctrl><Alt>P", NULL };
	
	
	//Actions
	GSimpleAction *preferences_action;
	preferences_action=g_simple_action_new("preferences",NULL); //app.preferences
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(preferences_action)); //make visible
	g_signal_connect(preferences_action, "activate",  G_CALLBACK(callbk_preferences), window);	
	
	GSimpleAction *home_action;	
	home_action=g_simple_action_new("home",NULL); //app.home
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(home_action)); //make visible	
	g_signal_connect(home_action, "activate",  G_CALLBACK(callbk_calendar_home), window);
	
	GSimpleAction *export_action;
	export_action=g_simple_action_new("export",NULL); //app.export
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(export_action)); //make visible
	g_signal_connect(export_action, "activate",  G_CALLBACK(callbk_export), window);
	
	GSimpleAction *import_action;
	import_action=g_simple_action_new("import",NULL); //app.import
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(import_action)); //make visible
	g_signal_connect(import_action, "activate",  G_CALLBACK(callbk_import), window);
	
	GSimpleAction *deleteall_action;
	deleteall_action=g_simple_action_new("deleteall",NULL); //app.deleteall
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(deleteall_action)); //make visible
	g_signal_connect(deleteall_action, "activate",  G_CALLBACK(callbk_delete_all), window);
	
	GSimpleAction *info_action;
	info_action=g_simple_action_new("info",NULL); //app.info
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(info_action)); //make visible
	g_signal_connect(info_action, "activate",  G_CALLBACK(callbk_info), window);
	
	GSimpleAction *about_action;
	about_action=g_simple_action_new("about",NULL); //app.about
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(about_action)); //make visible
	g_signal_connect(about_action, "activate",  G_CALLBACK(callbk_about), window);
	
	//speak actions
	GSimpleAction *speak_action;	
	speak_action=g_simple_action_new("speak",NULL); //app.speak
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(speak_action)); //make visible	
	g_signal_connect(speak_action, "activate",  G_CALLBACK(callbk_speak), calendar);
	
	GSimpleAction *speaktime_action;	
	speaktime_action=g_simple_action_new("speaktime",NULL); //app.speaktime
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(speaktime_action)); //make visible	
	g_signal_connect(speaktime_action, "activate",  G_CALLBACK(callbk_speaktime), window);
	
	GSimpleAction *search_action;
	search_action=g_simple_action_new("search",NULL); //app.search
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(search_action)); //make visible
	g_signal_connect(search_action, "activate",  G_CALLBACK(callbk_search), window);
	
	GSimpleAction *easter_action;
	easter_action=g_simple_action_new("easter",NULL); //app.easter
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(easter_action)); //make visible
	g_signal_connect(easter_action, "activate",  G_CALLBACK(callbk_easter), window);
	
	
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.speak", speak_accels);		
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.speaktime", time_accels);	
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.home", home_accels);
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.info", info_accels);
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.preferences", preferences_accels);
			
	
	//button_new_event = gtk_button_new_with_label("New Event");
	button_new_event= gtk_button_new_from_icon_name("appointment-new-symbolic");
	gtk_widget_set_tooltip_text(button_new_event, "New Event");		
	g_signal_connect(button_new_event, "clicked", G_CALLBACK(callbk_new_event), store);	
	g_object_set_data(G_OBJECT(button_new_event), "button-new-window-key",window);
	g_object_set_data(G_OBJECT(button_new_event), "button-new-calendar-key",calendar);
	gtk_header_bar_pack_start(GTK_HEADER_BAR(header), button_new_event);
	
	//button_edit_event = gtk_button_new_with_label("Edit Event");	
	button_edit_event= gtk_button_new_from_icon_name("edit-symbolic");	
	gtk_widget_set_tooltip_text(button_edit_event, "Edit Event");		
	g_signal_connect(button_edit_event, "clicked", G_CALLBACK(callbk_edit_event), selection);
	g_object_set_data(G_OBJECT(button_edit_event), "button-edit-window-key",window);
	g_object_set_data(G_OBJECT(button_edit_event), "button-edit-store-key",store);	
	gtk_header_bar_pack_start(GTK_HEADER_BAR(header), button_edit_event);
	
		
	//button_delete_event = gtk_button_new_with_label("Delete Event");
	button_delete_event= gtk_button_new_from_icon_name("edit-delete-symbolic");		
	gtk_widget_set_tooltip_text(button_delete_event, "Delete Event");			
	g_signal_connect(button_delete_event, "clicked", G_CALLBACK(callbk_delete_event), selection);
	g_object_set_data(G_OBJECT(button_delete_event), "button-delete-window-key",window);
	g_object_set_data(G_OBJECT(button_delete_event), "button-delete-calendar-key",calendar);	
	g_object_set_data(G_OBJECT(button_edit_event), "button-delete-store-key",store);		
	gtk_header_bar_pack_start(GTK_HEADER_BAR(header), button_delete_event);
	
	button_find_event= gtk_button_new_from_icon_name("find-location-symbolic");		
	gtk_widget_set_tooltip_text(button_find_event, "Find On Calendar");			
	g_signal_connect(button_find_event, "clicked", G_CALLBACK(callbk_find_event), selection);
	g_object_set_data(G_OBJECT(button_find_event), "button-find-window-key",window);
	g_object_set_data(G_OBJECT(button_find_event), "button-find-calendar-key",calendar);	
	g_object_set_data(G_OBJECT(button_find_event), "button-find-store-key",store);		
	gtk_header_bar_pack_start(GTK_HEADER_BAR(header), button_find_event);
		
	// Menu model
	GMenu *menu, *section;
	menu = g_menu_new();
	
	GMenu *tools_menu; 
	GMenuItem *item;

	
	section = g_menu_new ();
	g_menu_append (section, "Export", "app.export"); 	
	g_menu_append_section (menu, NULL, G_MENU_MODEL (section));
	g_object_unref (section);
	
	section = g_menu_new ();
	g_menu_append (section, "Import", "app.import"); 	
	g_menu_append_section (menu, NULL, G_MENU_MODEL (section));
	g_object_unref (section);
	
	section = g_menu_new ();
	g_menu_append (section, "Delete All", "app.deleteall"); 	
	g_menu_append_section (menu, NULL, G_MENU_MODEL (section));
	g_object_unref (section);
	
	section = g_menu_new();
	g_menu_append(section, "Speak", "app.speak");
	g_menu_append_section(menu, NULL, G_MENU_MODEL(section));
	g_object_unref(section);
	
	section = g_menu_new();
	g_menu_append(section, "Speak Time", "app.speaktime");
	g_menu_append_section(menu, NULL, G_MENU_MODEL(section));
	g_object_unref(section);
	
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
	
	update_calendar(GTK_CALENDAR(calendar),window);	
	
	paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
   
    gtk_paned_set_start_child(GTK_PANED(paned), box1);
    gtk_paned_set_end_child(GTK_PANED(paned), box2);
	
	gtk_window_set_child (GTK_WINDOW (window), paned);
	gtk_window_present(GTK_WINDOW (window));		
}

int main (int argc, char **argv)
{
	GtkApplication *app;
	int status;
	app = gtk_application_new ("org.gtk.myevents", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect_swapped(app, "startup", G_CALLBACK (startup),app);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);
	return status;
}
