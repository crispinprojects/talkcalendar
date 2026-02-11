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
#include <ctype.h> //whitespace
#include <glib/gstdio.h>  //needed for g_mkdir
#include <math.h>  //compile with -lm

#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "calendarevent.h"
#include "dbmanager.h"
#include "synthesizer.h"
#include "voice.h"


#define CONFIG_DIRNAME "talkcalendar"
#define CONFIG_FILENAME "talkcalendar-060"

static char * m_config_file = NULL;
static sqlite3 *db_handle = NULL;

//Declarations
//static void create_header(GtkWindow *window);

static void callbk_new_event(GSimpleAction *action, GVariant *parameter,  gpointer user_data);
static void callbk_add_new_event(GtkButton *button, gpointer user_data);
static void callbk_edit_event(GSimpleAction *action, GVariant *parameter,  gpointer user_data);
static void callbk_update_event(GtkButton *button, gpointer user_data);
static void callbk_delete_selected(GSimpleAction *action, GVariant *parameter,  gpointer user_data);
static int get_month_number(const char* month_str);

// Function prototypes for export/import functionality
static void callbk_export(GSimpleAction *action, GVariant *parameter, gpointer user_data);
static void file_save_response (GObject *source, GAsyncResult *result, void *user_data);
void export_file(char *file_name);

static void callbk_import(GSimpleAction *action, GVariant *parameter, gpointer user_data);
void import_ical_file(gpointer user_data);
static void file_open_response (GObject *source, GAsyncResult *result, void *user_data);
static char *ignore_first_zero(char *input);


gboolean file_exists(const char *file_name);

char* sanitize_text(const char* input_text);
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

//store
static void update_store(GtkCalendar *calendar, gpointer user_data);
static void callbk_listview (GtkListView *list, guint position, gpointer unused);
static void callbk_setup_listitem (GtkListItemFactory *factory,GtkListItem *list_item);
static void callbk_bind_listitem (GtkListItemFactory *factory, GtkListItem *list_item);

//ADPCM synthesizer and helper functions
void decode_word_to_buffer(VoiceWord word_id, int16_t *buffer, int *current_idx);
void append_word(VoiceWord word_id);
VoiceWord get_num_voice(int n);
VoiceWord get_num_enum(int n);
void play_time(int hour, int minute);
void build_time_phrase(int hour, int minute);
VoiceWord map_string_to_enum(const char *word);
static void speak_word_array(GPtrArray *words_array);

char* get_time_str(int hour, int min);
char* get_time_str_display(int hour, int min);

static void callbk_speak(GSimpleAction* action, GVariant *parameter,gpointer user_data);
static void callbk_speaktime(GSimpleAction * action, GVariant *parameter, gpointer user_data);
static void speak_events();
static void speak_time();

gboolean file_exists(const char *file_name);
static void play_audio_task_callbk(GObject *gobject,GAsyncResult *result,  gpointer  user_data);
static void play_audio_async (GTask *task, gpointer object, gpointer task_data, GCancellable *cancellable);


int  get_number_of_day_events();
static char* get_cardinal_string(int number);
static char* get_day_number_ordinal_string(int day);
static char* get_day_of_week(int day, int month, int year);

GArray*  get_upcoming_array(int upcoming_days);
int  get_total_number_of_events();


// Function prototypes for Easter calculation
static void callbk_easter(GSimpleAction *action, GVariant *parameter, gpointer user_data);
GDate* calculate_easter(gint year);
static void callbk_calc_easter(GtkButton *button, gpointer user_data);

//Search
// Function prototypes for search functionality
static void callbk_search(GSimpleAction *action, GVariant *parameter, gpointer user_data);
static void callbk_search_events(GtkButton *button, gpointer user_data);
static void search_events_location(const char* search_str);
static void search_events_summary(const char* search_str);

static void config_load_default();
static void config_read();
static void config_write();
void config_initialize();

//======================================================================

//window
static int m_window_width=800;
static int m_window_height=600;
static int m_paned_position=350; // Global

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
GtkWidget *m_calendar;
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

static const char* m_summary ="appointment";
static const char* m_location ="";
static const char* m_description ="";


static char* m_file_name = NULL;

//preferences
static int m_reset_preferences=0;
//listview display
static int m_12hour_format=1; //am pm hour format
static gboolean m_show_end_time=FALSE; //show end_time
static int m_show_location=1; //show location
static gboolean m_notable_dates=TRUE; //show notable dates in date label

//talk preferences
static gboolean m_talk =TRUE;
static gboolean m_talk_at_startup =TRUE;
gboolean m_talking=FALSE; //async
static int m_talk_priority=0;
static char* m_speak_file ="speak.wav";

//====================================================================

const GActionEntry app_actions[] = {
  { "speak", callbk_speak}, 
  { "speaktime", callbk_speaktime},   
  { "home", callbk_calendar_home}, 
  { "info", callbk_info},
  { "preferences", callbk_preferences} 
};
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


#define MAX_SPEAK_SECONDS 240
#define SILENCE_SECONDS 0.10  // 100ms pause between words
//ADPCM synthesizer
// Buffer for the full sentence
uint16_t *full_audio;
int current_sample_idx = 0;
int16_t* full_audio_buffer = NULL;
int   buffer_idx = 0;
// Global state for the ADPCM decoder (defined in synthesizer.c)
extern int     predicted_sample;
extern int     step_index;

//======================================================================
// TDPCM syntheiszer
//======================================================================
/**
 * @brief Decodes an ADPCM word
 *
 */
void decode_word_to_buffer(VoiceWord word_id, int16_t *buffer, int *current_idx) 
{
    AudioLookup word = voice_dictionary[word_id];
    predicted_sample = 0;
    step_index = 0;

    for (uint32_t i = 0; i < word.length; i++) {
        uint8_t byte = word.data[i];
        buffer[(*current_idx)++] = decode_adpcm_nibble(byte & 0x0F);
        buffer[(*current_idx)++] = decode_adpcm_nibble((byte >> 4) & 0x0F);
    }
}

/**
 * Decodes an ADPCM word and appends it to the global buffer with a short pause
 * Use by speak_word_array function
 */
void append_word(VoiceWord word_id) {
    if (word_id >= VOICE_COUNT) return;
    
    AudioLookup word = voice_dictionary[word_id];
    
    // IMPORTANT: Reset ADPCM state for EVERY word
    predicted_sample = 0;
    step_index = 0;

    for (uint32_t i = 0; i < word.length; i++) {
        uint8_t byte = word.data[i];
        
        // Decode low nibble
        full_audio_buffer[buffer_idx++] = decode_adpcm_nibble(byte & 0x0F);
        // Decode high nibble
        full_audio_buffer[buffer_idx++] = decode_adpcm_nibble((byte >> 4) & 0x0F);
    }

    // Add 100ms of true PCM silence (0) between words
    // This stops the 'sssh' or clicking between words
    int silence_samples = (int)(SAMPLE_RATE * 0.10); 
    for (int i = 0; i < silence_samples; i++) {
        full_audio_buffer[buffer_idx++] = 0;
    }
}


/**
 * @brief  Helper to map 0-59 to the correct Number Enum
 * Used by play_time function
 */
VoiceWord get_num_voice(int n) {
    static const VoiceWord nums[] = {
        VOICE_00, VOICE_01, VOICE_02, VOICE_03, VOICE_04, VOICE_05, VOICE_06, VOICE_07, VOICE_08, VOICE_09,
        VOICE_10, VOICE_11, VOICE_12, VOICE_13, VOICE_14, VOICE_15, VOICE_16, VOICE_17, VOICE_18, VOICE_19, VOICE_20
    };
    if (n <= 20) return nums[n];
    if (n < 30) return VOICE_20;
    if (n < 40) return VOICE_30;
    if (n < 50) return VOICE_40;
    return VOICE_50;
}

/**
 * @brief Maps an integer (0-59) to your specific Number Enums.
 * used by build time phrase
 */
VoiceWord get_num_enum(int n)
 {
    static const VoiceWord num_map[] = {
        VOICE_00, VOICE_01, VOICE_02, VOICE_03, VOICE_04, VOICE_05, VOICE_06, VOICE_07, 
        VOICE_08, VOICE_09, VOICE_10, VOICE_11, VOICE_12, VOICE_13, VOICE_14, VOICE_15, 
        VOICE_16, VOICE_17, VOICE_18, VOICE_19, VOICE_20
    };
    if (n <= 20) return num_map[n];
    if (n < 30)  return VOICE_20;
    if (n < 40)  return VOICE_30;
    if (n < 50)  return VOICE_40;
    return VOICE_50;
}

void play_time(int hour, int minute) 
{
    // 1. Speak Hour (12-hour format)
    int h12 = (hour == 0 || hour == 12) ? 12 : hour % 12;
    decode_word_to_buffer(get_num_voice(h12), full_audio, &current_sample_idx);

    // 2. Speak Minutes
    if (minute == 0) {
        decode_word_to_buffer(VOICE_CLOCK, full_audio, &current_sample_idx);
    } else {
        if (minute < 10) {
            decode_word_to_buffer(VOICE_O, full_audio, &current_sample_idx);
            decode_word_to_buffer(get_num_voice(minute), full_audio, &current_sample_idx);
        } else if (minute <= 20) {
            decode_word_to_buffer(get_num_voice(minute), full_audio, &current_sample_idx);
        } else {
            // DECOMPOSITION: e.g., 32 -> VOICE_30 then VOICE_02
            int tens = (minute / 10) * 10;
            int units = minute % 10;
            
            decode_word_to_buffer(get_num_voice(tens), full_audio, &current_sample_idx); // e.g. VOICE_30
            if (units > 0) {
                decode_word_to_buffer(get_num_voice(units), full_audio, &current_sample_idx); // e.g. VOICE_02
            }
        }
    }
    // 3. AM/PM
    decode_word_to_buffer((hour < 12) ? VOICE_AM : VOICE_PM, full_audio, &current_sample_idx);
}

/**
 * @brief Sentence Builder Time 
 */
void build_time_phrase(int hour, int minute) 
{
    int h12 = (hour == 0 || hour == 12) ? 12 : hour % 12;
    
    append_word(get_num_enum(h12));

    if (minute == 0) {
        append_word(VOICE_CLOCK);
    } else {
        if (minute < 10) append_word(VOICE_O); // "Ten Oh Five"
        
        if (minute <= 20) {
            append_word(get_num_enum(minute));
        } else {
            append_word(get_num_enum(minute)); // The Tens (20, 30, 40, 50)
            if (minute % 10 != 0) append_word(get_num_enum(minute % 10));
        }
    }

    append_word(hour < 12 ? VOICE_AM : VOICE_PM);
}



typedef struct {
    const char *text;
    VoiceWord id;
} StringToVoice;

/**
 * @brief Voice map (mini dictionary)
 */
static const StringToVoice voice_map[] = {
    {"0", VOICE_00}, {"zero", VOICE_00}, {"midnight", VOICE_00},
    {"1", VOICE_01}, {"one", VOICE_01},
    {"first", VOICE_01ST},
    {"2", VOICE_02}, {"two", VOICE_02},
    {"second", VOICE_02ND},
    {"3", VOICE_03}, {"three", VOICE_03},
    {"third", VOICE_03RD},
    {"4", VOICE_04}, {"four", VOICE_04},
    {"fourth", VOICE_04TH},
    {"5", VOICE_05}, {"five", VOICE_05},
    {"fifth", VOICE_05TH},
    {"6", VOICE_06}, {"six", VOICE_06},
    {"sixth", VOICE_06TH},
    {"7", VOICE_07}, {"seven", VOICE_07},
    {"seventh", VOICE_07TH},
    {"8", VOICE_08}, {"eight", VOICE_08},
    {"eighth", VOICE_08TH},
    {"9", VOICE_09}, {"nine", VOICE_09},
    {"ninth", VOICE_09TH},
    {"10", VOICE_10}, {"ten", VOICE_10},
    {"100", VOICE_100},
    {"tenth", VOICE_10TH},
    {"11", VOICE_11},
    {"eleventh", VOICE_11TH},
    {"12", VOICE_12},
    {"twelfth", VOICE_12TH},
    {"13", VOICE_13},
    {"thirteenth", VOICE_13TH},
    {"14", VOICE_14},
    {"fourteenth", VOICE_14TH},
    {"15", VOICE_15},
    {"fifteenth", VOICE_15TH},
    {"16", VOICE_16},
    {"sixteenth", VOICE_16TH},
    {"17", VOICE_17},
    {"seventeenth", VOICE_17TH},
    {"18", VOICE_18},
    {"eighteenth", VOICE_18TH},
    {"19", VOICE_19},
    {"nineteenth", VOICE_19TH},
    {"20", VOICE_20},
    {"twentieth", VOICE_20TH},
    {"21", VOICE_21},
    {"twentyfirst", VOICE_21ST},
    {"22", VOICE_22},
    {"twentysecond", VOICE_22ND},
    {"23", VOICE_23},
    {"twentythird", VOICE_23RD},
    {"24", VOICE_24},
    {"twentyfourth", VOICE_24TH},
    {"25", VOICE_25},
    {"twentyfifth", VOICE_25TH},
    {"26", VOICE_26},
    {"twentysixth", VOICE_26TH},
    {"27", VOICE_27},
    {"twentyseventh", VOICE_27TH},
    {"28", VOICE_28},
    {"twentyeighth", VOICE_28TH},
    {"29", VOICE_29},
    {"twentyninth", VOICE_29TH},
    {"30", VOICE_30},
    {"thirtieth", VOICE_30TH},
    {"31", VOICE_31},
    {"thirtyfirst", VOICE_31ST},
    {"32", VOICE_32},
    {"33", VOICE_33},
    {"34", VOICE_34},
    {"35", VOICE_35},
    {"36", VOICE_36},
    {"37", VOICE_37},
    {"38", VOICE_38},
    {"39", VOICE_39},
    {"40", VOICE_40},
    {"41", VOICE_41},
    {"42", VOICE_42},
    {"43", VOICE_43},
    {"44", VOICE_44},
    {"45", VOICE_45},
    {"46", VOICE_46},
    {"47", VOICE_47},
    {"48", VOICE_48},
    {"49", VOICE_49},
    {"50", VOICE_50},
    {"51", VOICE_51},
    {"52", VOICE_52},
    {"53", VOICE_53},
    {"54", VOICE_54},
    {"55", VOICE_55},
    {"56", VOICE_56},
    {"57", VOICE_57},
    {"58", VOICE_58},
    {"59", VOICE_59},
    {"60", VOICE_60},
    {"70", VOICE_70},
    {"80", VOICE_80},
    {"90", VOICE_90},
    {"a", VOICE_A},
    {"able", VOICE_ABLE},
    {"account", VOICE_ACCOUNT},
    {"activity", VOICE_ACTIVITY},
    {"adventure", VOICE_ADVENTURE},
    {"afternoon", VOICE_AFTERNOON},
    {"agm", VOICE_AGM},
    {"agree", VOICE_AGREE},
    {"alan", VOICE_ALAN},
    {"alarm", VOICE_ALARM},
    {"alex", VOICE_ALEX},
    {"alexander", VOICE_ALEXANDER},
    {"alf", VOICE_ALF},
    {"alfred", VOICE_ALFRED},
    {"alice", VOICE_ALICE},
    {"alison", VOICE_ALISON},
    {"alister", VOICE_ALISTER},
    {"all", VOICE_ALL},
    {"allotment", VOICE_ALLOTMENT},
    {"am", VOICE_AM}, {"a.m.", VOICE_AM},
    {"amazon", VOICE_AMAZON},
    {"amber", VOICE_AMBER},
    {"ambulance", VOICE_AMBULANCE},
    {"amelia", VOICE_AMELIA},
    {"amy", VOICE_AMY},
    {"and", VOICE_AND},
    {"andora", VOICE_ANDORA},
    {"andrea", VOICE_ANDREA},
    {"andrew", VOICE_ANDREW},
    {"andy", VOICE_ANDY},
    {"angela", VOICE_ANGELA},
    {"angelina", VOICE_ANGELINA},
    {"animal", VOICE_ANIMAL},
    {"anna", VOICE_ANNA},
    {"annabel", VOICE_ANNABEL},
    {"anne", VOICE_ANNE},
    {"anniversary", VOICE_ANNIVERSARY},
    {"anthony", VOICE_ANTHONY},
    {"appointment", VOICE_APPOINTMENT},
    {"april", VOICE_APRIL},
    {"archery", VOICE_ARCHERY},
    {"archie", VOICE_ARCHIE},
    {"art", VOICE_ART},
    {"arthur", VOICE_ARTHUR},
    {"assessment", VOICE_ASSESSMENT},
    {"at", VOICE_AT},
    {"aubrey", VOICE_AUBREY},
    {"audrey", VOICE_AUDREY},
    {"august", VOICE_AUGUST},
    {"aunt", VOICE_AUNT},
    {"auntie", VOICE_AUNTIE},
    {"autumn", VOICE_AUTUMN},
    {"ava", VOICE_AVA},
    {"baby", VOICE_BABY},
    {"badminton", VOICE_BADMINTON},
    {"band", VOICE_BAND},
    {"bank", VOICE_BANK},
    {"barber", VOICE_BARBER},
    {"baseball", VOICE_BASEBALL},
    {"be", VOICE_BE},
    {"bed", VOICE_BED},
    {"beer", VOICE_BEER},
    {"begins", VOICE_BEGINS},
    {"beth", VOICE_BETH},
    {"bethany", VOICE_BETHANY},
    {"betsy", VOICE_BETSY},
    {"betty", VOICE_BETTY},
    {"bettys", VOICE_BETTYS},
    {"big", VOICE_BIG},
    {"bike", VOICE_BIKE},
    {"billy", VOICE_BILLY},
    {"bird", VOICE_BIRD},
    {"birth", VOICE_BIRTH},
    {"birthday", VOICE_BIRTHDAY},
    {"bob", VOICE_BOB},
    {"book", VOICE_BOOK},
    {"bowling", VOICE_BOWLING},
    {"bowls", VOICE_BOWLS},
    {"box", VOICE_BOX},
    {"boxing", VOICE_BOXING},
    {"boy", VOICE_BOY},
    {"break", VOICE_BREAK},
    {"breakfast", VOICE_BREAKFAST},
    {"british", VOICE_BRITISH},
    {"brother", VOICE_BROTHER},
    {"brothers", VOICE_BROTHERS},
    {"brunch", VOICE_BRUNCH},
    {"bus", VOICE_BUS},
    {"business", VOICE_BUSINESS},
    {"busy", VOICE_BUSY},
    {"by", VOICE_BY},
    {"bye", VOICE_BYE},
    {"cabbie", VOICE_CABBIE},
    {"cafe", VOICE_CAFE},
    {"calendar", VOICE_CALENDAR},
    {"call", VOICE_CALL},
    {"camp", VOICE_CAMP},
    {"camping", VOICE_CAMPING},
    {"campus", VOICE_CAMPUS},
    {"car", VOICE_CAR},
    {"card", VOICE_CARD},
    {"care", VOICE_CARE},
    {"caroline", VOICE_CAROLINE},
    {"cat", VOICE_CAT},
    {"cath", VOICE_CATH},
    {"catherine", VOICE_CATHERINE},
    {"celebration", VOICE_CELEBRATION},
    {"certificate", VOICE_CERTIFICATE},
    {"charles", VOICE_CHARLES},
    {"charlotte", VOICE_CHARLOTTE},
    {"chat", VOICE_CHAT},
    {"chauffeur", VOICE_CHAUFFEUR},
    {"check", VOICE_CHECK},
    {"chemist", VOICE_CHEMIST},
    {"child", VOICE_CHILD},
    {"children", VOICE_CHILDREN},
    {"chips", VOICE_CHIPS},
    {"choir", VOICE_CHOIR},
    {"chore", VOICE_CHORE},
    {"christina", VOICE_CHRISTINA},
    {"christmas", VOICE_CHRISTMAS},
    {"church", VOICE_CHURCH},
    {"cinema", VOICE_CINEMA},
    {"circle", VOICE_CIRCLE},
    {"city", VOICE_CITY},
    {"claire", VOICE_CLAIRE},
    {"clara", VOICE_CLARA},
    {"clarence", VOICE_CLARENCE},
    {"clarissa", VOICE_CLARISSA},
    {"class", VOICE_CLASS},
    {"claude", VOICE_CLAUDE},
    {"cleaner", VOICE_CLEANER},
    {"climbing", VOICE_CLIMBING},
    {"clinic", VOICE_CLINIC},
    {"oclock", VOICE_CLOCK},
    {"clocks", VOICE_CLOCKS},
    {"close", VOICE_CLOSE},
    {"club", VOICE_CLUB},
    {"coach", VOICE_COACH},
    {"coast", VOICE_COAST},
    {"code", VOICE_CODE},
    {"coding", VOICE_CODING},
    {"coffee", VOICE_COFFEE},
    {"collection", VOICE_COLLECTION},
    {"college", VOICE_COLLEGE},
    {"coming", VOICE_COMING},
    {"computer", VOICE_COMPUTER},
    {"concert", VOICE_CONCERT},
    {"contact", VOICE_CONTACT},
    {"cottage", VOICE_COTTAGE},
    {"cousin", VOICE_COUSIN},
    {"crook", VOICE_CROOK},
    {"cyber", VOICE_CYBER},
    {"cycle", VOICE_CYCLE},
    {"dad", VOICE_DAD},
    {"dads", VOICE_DADS},
    {"daisy", VOICE_DAISY},
    {"dan", VOICE_DAN},
    {"dance", VOICE_DANCE},
    {"daniel", VOICE_DANIEL},
    {"danielle", VOICE_DANIELLE},
    {"danny", VOICE_DANNY},
    {"date", VOICE_DATE},
    {"daughter", VOICE_DAUGHTER},
    {"daughters", VOICE_DAUGHTERS},
    {"david", VOICE_DAVID},
    {"day", VOICE_DAY},
    {"days", VOICE_DAYS},
    {"dead", VOICE_DEAD},
    {"deadline", VOICE_DEADLINE},
    {"death", VOICE_DEATH},
    {"debbie", VOICE_DEBBIE},
    {"deborah", VOICE_DEBORAH},
    {"debs", VOICE_DEBS},
    {"december", VOICE_DECEMBER},
    {"decorate", VOICE_DECORATE},
    {"decorating", VOICE_DECORATING},
    {"delivery", VOICE_DELIVERY},
    {"dentist", VOICE_DENTIST},
    {"development", VOICE_DEVELOPMENT},
    {"diana", VOICE_DIANA},
    {"dinner", VOICE_DINNER},
    {"do", VOICE_DO},
    {"doctor", VOICE_DOCTOR},
    {"dog", VOICE_DOG},
    {"don", VOICE_DON},
    {"donald", VOICE_DONALD},
    {"donkey", VOICE_DONKEY},
    {"dora", VOICE_DORA},
    {"down", VOICE_DOWN},
    {"drinks", VOICE_DRINKS},
    {"driver", VOICE_DRIVER},
    {"dustbin", VOICE_DUSTBIN},
    {"ear", VOICE_EAR},
    {"early", VOICE_EARLY},
    {"east", VOICE_EAST},
    {"easter", VOICE_EASTER},
    {"education", VOICE_EDUCATION},
    {"electric", VOICE_ELECTRIC},
    {"electricity", VOICE_ELECTRICITY},
    {"eleven", VOICE_ELEVEN},
    {"eleventh", VOICE_ELEVENTH},
    {"elisha", VOICE_ELISHA},
    {"eliza", VOICE_ELIZA},
    {"elizabeth", VOICE_ELIZABETH},
    {"ellie", VOICE_ELLIE},
    {"elliot", VOICE_ELLIOT},
    {"elton", VOICE_ELTON},
    {"emailnotification", VOICE_EMAILNOTIFICATION},
    {"emma", VOICE_EMMA},
    {"engage", VOICE_ENGAGE},
    {"engineer", VOICE_ENGINEER},
    {"evan", VOICE_EVAN},
    {"evening", VOICE_EVENING},
    {"event", VOICE_EVENT},
    {"eventsss", VOICE_EVENTSSS},
    {"excursion", VOICE_EXCURSION},
    {"eye", VOICE_EYE},
    {"family", VOICE_FAMILY},
    {"father", VOICE_FATHER},
    {"fathers", VOICE_FATHERS},
    {"fawkes", VOICE_FAWKES},
    {"fear", VOICE_FEAR},
    {"february", VOICE_FEBRUARY},
    {"feed", VOICE_FEED},
    {"festival", VOICE_FESTIVAL},
    {"film", VOICE_FILM},
    {"fiona", VOICE_FIONA},
    {"fire", VOICE_FIRE},
    {"fish", VOICE_FISH},
    {"fishing", VOICE_FISHING},
    {"fitness", VOICE_FITNESS},
    {"five", VOICE_FIVE},
    {"fix", VOICE_FIX},
    {"flourence", VOICE_FLOURENCE},
    {"food", VOICE_FOOD},
    {"fools", VOICE_FOOLS},
    {"football", VOICE_FOOTBALL},
    {"forward", VOICE_FORWARD},
    {"frances", VOICE_FRANCES},
    {"francesca", VOICE_FRANCESCA},
    {"francis", VOICE_FRANCIS},
    {"frank", VOICE_FRANK},
    {"frankenstein", VOICE_FRANKENSTEIN},
    {"fred", VOICE_FRED},
    {"freddie", VOICE_FREDDIE},
    {"frederick", VOICE_FREDERICK},
    {"freeze", VOICE_FREEZE},
    {"freya", VOICE_FREYA},
    {"friday", VOICE_FRIDAY},
    {"friend", VOICE_FRIEND},
    {"frost", VOICE_FROST},
    {"funeral", VOICE_FUNERAL},
    {"gale", VOICE_GALE},
    {"gallery", VOICE_GALLERY},
    {"game", VOICE_GAME},
    {"garage", VOICE_GARAGE},
    {"garbage", VOICE_GARBAGE},
    {"garden", VOICE_GARDEN},
    {"gas", VOICE_GAS},
    {"gate", VOICE_GATE},
    {"geoff", VOICE_GEOFF},
    {"geoffrey", VOICE_GEOFFREY},
    {"george", VOICE_GEORGE},
    {"georges", VOICE_GEORGES},
    {"georgina", VOICE_GEORGINA},
    {"gift", VOICE_GIFT},
    {"girl", VOICE_GIRL},
    {"go", VOICE_GO},
    {"golf", VOICE_GOLF},
    {"good", VOICE_GOOD},
    {"grand", VOICE_GRAND},
    {"guy", VOICE_GUY},
    {"hairdresser", VOICE_HAIRDRESSER},
    {"halloween", VOICE_HALLOWEEN},
    {"hannah", VOICE_HANNAH},
    {"harold", VOICE_HAROLD},
    {"harry", VOICE_HARRY},
    {"have", VOICE_HAVE},
    {"hayley", VOICE_HAYLEY},
    {"head", VOICE_HEAD},
    {"health", VOICE_HEALTH},
    {"hear", VOICE_HEAR},
    {"heating", VOICE_HEATING},
    {"hector", VOICE_HECTOR},
    {"helen", VOICE_HELEN},
    {"hello", VOICE_HELLO},
    {"hen", VOICE_HEN},
    {"henry", VOICE_HENRY},
    {"herbert", VOICE_HERBERT},
    {"high", VOICE_HIGH},
    {"hobby", VOICE_HOBBY},
    {"hockey", VOICE_HOCKEY},
    {"holiday", VOICE_HOLIDAY},
    {"home", VOICE_HOME},
    {"honor", VOICE_HONOR},
    {"horse", VOICE_HORSE},
    {"hospital", VOICE_HOSPITAL},
    {"hotel", VOICE_HOTEL},
    {"hour", VOICE_HOUR},
    {"house", VOICE_HOUSE},
    {"humanoid", VOICE_HUMANOID},
    {"humphrey", VOICE_HUMPHREY},
    {"hundred", VOICE_HUNDRED},
    {"hundredth", VOICE_HUNDREDTH},
    {"husband", VOICE_HUSBAND},
    {"i", VOICE_I},
    {"ian", VOICE_IAN},
    {"important", VOICE_IMPORTANT},
    {"in", VOICE_IN},
    {"industry", VOICE_INDUSTRY},
    {"information", VOICE_INFORMATION},
    {"inn", VOICE_INN},
    {"insurance", VOICE_INSURANCE},
    {"inter", VOICE_INTER},
    {"interview", VOICE_INTERVIEW},
    {"investment", VOICE_INVESTMENT},
    {"invoice", VOICE_INVOICE},
    {"irene", VOICE_IRENE},
    {"is", VOICE_IS},
    {"isaac", VOICE_ISAAC},
    {"isabel", VOICE_ISABEL},
    {"isabella", VOICE_ISABELLA},
    {"isla", VOICE_ISLA},
    {"island", VOICE_ISLAND},
    {"item", VOICE_ITEM},
    {"ivan", VOICE_IVAN},
    {"ivy", VOICE_IVY},
    {"jack", VOICE_JACK},
    {"jackie", VOICE_JACKIE},
    {"jacob", VOICE_JACOB},
    {"jacqueline", VOICE_JACQUELINE},
    {"james", VOICE_JAMES},
    {"jamie", VOICE_JAMIE},
    {"january", VOICE_JANUARY},
    {"jason", VOICE_JASON},
    {"jet", VOICE_JET},
    {"jeweller", VOICE_JEWELLER},
    {"john", VOICE_JOHN},
    {"journey", VOICE_JOURNEY},
    {"joy", VOICE_JOY},
    {"july", VOICE_JULY},
    {"june", VOICE_JUNE},
    {"karen", VOICE_KAREN},
    {"kate", VOICE_KATE},
    {"ken", VOICE_KEN},
    {"kenneth", VOICE_KENNETH},
    {"king", VOICE_KING},
    {"laboratory", VOICE_LABORATORY},
    {"large", VOICE_LARGE},
    {"last", VOICE_LAST},
    {"laura", VOICE_LAURA},
    {"lawyer", VOICE_LAWYER},
    {"leave", VOICE_LEAVE},
    {"leaving", VOICE_LEAVING},
    {"lecture", VOICE_LECTURE},
    {"leisure", VOICE_LEISURE},
    {"leo", VOICE_LEO},
    {"lesson", VOICE_LESSON},
    {"liam", VOICE_LIAM},
    {"libby", VOICE_LIBBY},
    {"lift", VOICE_LIFT},
    {"lily", VOICE_LILY},
    {"line", VOICE_LINE},
    {"linux", VOICE_LINUX},
    {"location", VOICE_LOCATION},
    {"lock", VOICE_LOCK},
    {"lodge", VOICE_LODGE},
    {"long", VOICE_LONG},
    {"look", VOICE_LOOK},
    {"louisa", VOICE_LOUISA},
    {"low", VOICE_LOW},
    {"luca", VOICE_LUCA},
    {"lunch", VOICE_LUNCH},
    {"madeline", VOICE_MADELINE},
    {"magazine", VOICE_MAGAZINE},
    {"maintenance", VOICE_MAINTENANCE},
    {"man", VOICE_MAN},
    {"management", VOICE_MANAGEMENT},
    {"many", VOICE_MANY},
    {"march", VOICE_MARCH},
    {"marine", VOICE_MARINE},
    {"marjorie", VOICE_MARJORIE},
    {"market", VOICE_MARKET},
    {"mary", VOICE_MARY},
    {"master", VOICE_MASTER},
    {"mat", VOICE_MAT},
    {"matt", VOICE_MATT},
    {"matthew", VOICE_MATTHEW},
    {"matthias", VOICE_MATTHIAS},
    {"maurice", VOICE_MAURICE},
    {"may", VOICE_MAY},
    {"me", VOICE_ME},
    {"meal", VOICE_MEAL},
    {"mechanic", VOICE_MECHANIC},
    {"medical", VOICE_MEDICAL},
    {"meet", VOICE_MEET},
    {"meeting", VOICE_MEETING},
    {"memo", VOICE_MEMO},
    {"memorandum", VOICE_MEMORANDUM},
    {"message", VOICE_MESSAGE},
    {"mia", VOICE_MIA},
    {"midnight", VOICE_MIDNIGHT},
    {"mike", VOICE_MIKE},
    {"mini", VOICE_MINI},
    {"miriam", VOICE_MIRIAM},
    {"monday", VOICE_MONDAY},
    {"monster", VOICE_MONSTER},
    {"month", VOICE_MONTH},
    {"morning", VOICE_MORNING},
    {"mother", VOICE_MOTHER},
    {"mothers", VOICE_MOTHERS},
    {"motorcycle", VOICE_MOTORCYCLE},
    {"move", VOICE_MOVE},
    {"movie", VOICE_MOVIE},
    {"muhammad", VOICE_MUHAMMAD},
    {"mum", VOICE_MUM},
    {"mums", VOICE_MUMS},
    {"museum", VOICE_MUSEUM},
    {"music", VOICE_MUSIC},
    {"my", VOICE_MY},
    {"name", VOICE_NAME},
    {"names", VOICE_NAMES},
    {"naomi", VOICE_NAOMI},
    {"nat", VOICE_NAT},
    {"natalie", VOICE_NATALIE},
    {"nathan", VOICE_NATHAN},
    {"neighbour", VOICE_NEIGHBOUR},
    {"nephew", VOICE_NEPHEW},
    {"netball", VOICE_NETBALL},
    {"netflix", VOICE_NETFLIX},
    {"new", VOICE_NEW},
    {"news", VOICE_NEWS},
    {"newspaper", VOICE_NEWSPAPER},
    {"niece", VOICE_NIECE},
    {"night", VOICE_NIGHT},
    {"no", VOICE_NO},
    {"noah", VOICE_NOAH},
    {"norman", VOICE_NORMAN},
    {"north", VOICE_NORTH},
    {"not", VOICE_NOT},
    {"notable", VOICE_NOTABLE},
    {"november", VOICE_NOVEMBER},
    {"nurse", VOICE_NURSE},
    {"nursery", VOICE_NURSERY},
    {"o", VOICE_O}, {"oh", VOICE_O},
    {"october", VOICE_OCTOBER},
    {"of", VOICE_OF},
    {"office", VOICE_OFFICE},
    {"oliver", VOICE_OLIVER},
    {"olivia", VOICE_OLIVIA},
    {"on", VOICE_ON},
    {"one", VOICE_ONE},
    {"online", VOICE_ONLINE},
    {"open", VOICE_OPEN},
    {"or", VOICE_OR},
    {"orchestra", VOICE_ORCHESTRA},
    {"organise", VOICE_ORGANISE},
    {"oscar", VOICE_OSCAR},
    {"out", VOICE_OUT},
    {"over", VOICE_OVER},
    {"own", VOICE_OWN},
    {"pam", VOICE_PAM},
    {"pamela", VOICE_PAMELA},
    {"paper", VOICE_PAPER},
    {"parent", VOICE_PARENT},
    {"parrot", VOICE_PARROT},
    {"party", VOICE_PARTY},
    {"passport", VOICE_PASSPORT},
    {"pat", VOICE_PAT},
    {"patricia", VOICE_PATRICIA},
    {"patrick", VOICE_PATRICK},
    {"patricks", VOICE_PATRICKS},
    {"paul", VOICE_PAUL},
    {"paula", VOICE_PAULA},
    {"pauline", VOICE_PAULINE},
    {"pay", VOICE_PAY},
    {"paying", VOICE_PAYING},
    {"payment", VOICE_PAYMENT},
    {"penelope", VOICE_PENELOPE},
    {"penny", VOICE_PENNY},
    {"pension", VOICE_PENSION},
    {"percy", VOICE_PERCY},
    {"perry", VOICE_PERRY},
    {"person", VOICE_PERSON},
    {"personal", VOICE_PERSONAL},
    {"pet", VOICE_PET},
    {"peter", VOICE_PETER},
    {"phoebe", VOICE_PHOEBE},
    {"phone", VOICE_PHONE},
    {"piano", VOICE_PIANO},
    {"picnic", VOICE_PICNIC},
    {"picture", VOICE_PICTURE},
    {"pictures", VOICE_PICTURES},
    {"pilartes", VOICE_PILARTES},
    {"place", VOICE_PLACE},
    {"plan", VOICE_PLAN},
    {"planner", VOICE_PLANNER},
    {"planning", VOICE_PLANNING},
    {"pm", VOICE_PM}, {"p.m.", VOICE_PM},
    {"poetry", VOICE_POETRY},
    {"point", VOICE_POINT},
    {"pope", VOICE_POPE},
    {"port", VOICE_PORT},
    {"post", VOICE_POST},
    {"practice", VOICE_PRACTICE},
    {"premier", VOICE_PREMIER},
    {"prescription", VOICE_PRESCRIPTION},
    {"present", VOICE_PRESENT},
    {"pressure", VOICE_PRESSURE},
    {"priority", VOICE_PRIORITY},
    {"project", VOICE_PROJECT},
    {"pronounce", VOICE_PRONOUNCE},
    {"pronounced", VOICE_PRONOUNCED},
    {"public", VOICE_PUBLIC},
    {"purchase", VOICE_PURCHASE},
    {"queen", VOICE_QUEEN},
    {"quick", VOICE_QUICK},
    {"quiz", VOICE_QUIZ},
    {"quote", VOICE_QUOTE},
    {"radio", VOICE_RADIO},
    {"rail", VOICE_RAIL},
    {"railway", VOICE_RAILWAY},
    {"ray", VOICE_RAY},
    {"reminder", VOICE_REMINDER},
    {"rene", VOICE_RENE},
    {"renne", VOICE_RENNE},
    {"repair", VOICE_REPAIR},
    {"rest", VOICE_REST},
    {"restaurant", VOICE_RESTAURANT},
    {"retire", VOICE_RETIRE},
    {"retirement", VOICE_RETIREMENT},
    {"return", VOICE_RETURN},
    {"richard", VOICE_RICHARD},
    {"road", VOICE_ROAD},
    {"robbie", VOICE_ROBBIE},
    {"robert", VOICE_ROBERT},
    {"robin", VOICE_ROBIN},
    {"ron", VOICE_RON},
    {"ronnie", VOICE_RONNIE},
    {"room", VOICE_ROOM},
    {"rose", VOICE_ROSE},
    {"rosemary", VOICE_ROSEMARY},
    {"royal", VOICE_ROYAL},
    {"rugby", VOICE_RUGBY},
    {"russell", VOICE_RUSSELL},
    {"sabrina", VOICE_SABRINA},
    {"saint", VOICE_SAINT},
    {"sanctuary", VOICE_SANCTUARY},
    {"sarah", VOICE_SARAH},
    {"saturday", VOICE_SATURDAY},
    {"say", VOICE_SAY},
    {"says", VOICE_SAYS},
    {"schedule", VOICE_SCHEDULE},
    {"school", VOICE_SCHOOL},
    {"sea", VOICE_SEA},
    {"seasonal", VOICE_SEASONAL},
    {"semi", VOICE_SEMI},
    {"september", VOICE_SEPTEMBER},
    {"service", VOICE_SERVICE},
    {"session", VOICE_SESSION},
    {"shoe", VOICE_SHOE},
    {"shop", VOICE_SHOP},
    {"shopping", VOICE_SHOPPING},
    {"short", VOICE_SHORT},
    {"side", VOICE_SIDE},
    {"sister", VOICE_SISTER},
    {"sisters", VOICE_SISTERS},
    {"sky", VOICE_SKY},
    {"small", VOICE_SMALL},
    {"social", VOICE_SOCIAL},
    {"society", VOICE_SOCIETY},
    {"software", VOICE_SOFTWARE},
    {"son", VOICE_SON},
    {"sons", VOICE_SONS},
    {"south", VOICE_SOUTH},
    {"speaker", VOICE_SPEAKER},
    {"special", VOICE_SPECIAL},
    {"sport", VOICE_SPORT},
    {"spring", VOICE_SPRING},
    {"stag", VOICE_STAG},
    {"star", VOICE_STAR},
    {"start", VOICE_START},
    {"starts", VOICE_STARTS},
    {"station", VOICE_STATION},
    {"stay", VOICE_STAY},
    {"steve", VOICE_STEVE},
    {"steven", VOICE_STEVEN},
    {"stock", VOICE_STOCK},
    {"store", VOICE_STORE},
    {"study", VOICE_STUDY},
    {"sub", VOICE_SUB},
    {"summer", VOICE_SUMMER},
    {"summertime", VOICE_SUMMERTIME},
    {"sunday", VOICE_SUNDAY},
    {"super", VOICE_SUPER},
    {"susan", VOICE_SUSAN},
    {"synthesizer", VOICE_SYNTHESIZER},
    {"table", VOICE_TABLE},
    {"take", VOICE_TAKE},
    {"talk", VOICE_TALK},
    {"talking", VOICE_TALKING},
    {"task", VOICE_TASK},
    {"tax", VOICE_TAX},
    {"taxi", VOICE_TAXI},
    {"tea", VOICE_TEA},
    {"team", VOICE_TEAM},
    {"television", VOICE_TELEVISION},
    {"temperature", VOICE_TEMPERATURE},
    {"tennis", VOICE_TENNIS},
    {"test", VOICE_TEST},
    {"thankyou", VOICE_THANKYOU},
    {"that", VOICE_THAT},
    {"the", VOICE_THE},
    {"theatre", VOICE_THEATRE},
    {"then", VOICE_THEN},
    {"theo", VOICE_THEO},
    {"theodore", VOICE_THEODORE},
    {"thomas", VOICE_THOMAS},
    {"thursday", VOICE_THURSDAY},
    {"ticket", VOICE_TICKET},
    {"tiffany", VOICE_TIFFANY},
    {"tilda", VOICE_TILDA},
    {"tim", VOICE_TIM},
    {"time", VOICE_TIME},
    {"times", VOICE_TIMES},
    {"timothy", VOICE_TIMOTHY},
    {"tina", VOICE_TINA},
    {"tiny", VOICE_TINY},
    {"to", VOICE_TO},
    {"today", VOICE_TODAY},
    {"toll", VOICE_TOLL},
    {"tom", VOICE_TOM},
    {"tomorrow", VOICE_TOMORROW},
    {"tour", VOICE_TOUR},
    {"town", VOICE_TOWN},
    {"train", VOICE_TRAIN},
    {"training", VOICE_TRAINING},
    {"trans", VOICE_TRANS},
    {"travel", VOICE_TRAVEL},
    {"trevor", VOICE_TREVOR},
    {"trip", VOICE_TRIP},
    {"tuesday", VOICE_TUESDAY},
    {"tunnel", VOICE_TUNNEL},
    {"turn", VOICE_TURN},
    {"uma", VOICE_UMA},
    {"uncle", VOICE_UNCLE},
    {"under", VOICE_UNDER},
    {"university", VOICE_UNIVERSITY},
    {"unknown", VOICE_UNKNOWN},
    {"up", VOICE_UP},
    {"upcoming", VOICE_UPCOMING},
    {"ursula", VOICE_URSULA},
    {"val", VOICE_VAL},
    {"valentine", VOICE_VALENTINE},
    {"valentines", VOICE_VALENTINES},
    {"valerie", VOICE_VALERIE},
    {"vehicle", VOICE_VEHICLE},
    {"venue", VOICE_VENUE},
    {"version", VOICE_VERSION},
    {"victor", VOICE_VICTOR},
    {"village", VOICE_VILLAGE},
    {"visit", VOICE_VISIT},
    {"walk", VOICE_WALK},
    {"warm", VOICE_WARM},
    {"warming", VOICE_WARMING},
    {"wash", VOICE_WASH},
    {"washing", VOICE_WASHING},
    {"water", VOICE_WATER},
    {"way", VOICE_WAY},
    {"web", VOICE_WEB},
    {"webinar", VOICE_WEBINAR},
    {"wedding", VOICE_WEDDING},
    {"wednesday", VOICE_WEDNESDAY},
    {"week", VOICE_WEEK},
    {"west", VOICE_WEST},
    {"wife", VOICE_WIFE},
    {"wifes", VOICE_WIFES},
    {"willow", VOICE_WILLOW},
    {"window", VOICE_WINDOW},
    {"winnie", VOICE_WINNIE},
    {"winnifred", VOICE_WINNIFRED},
    {"winston", VOICE_WINSTON},
    {"winter", VOICE_WINTER},
    {"witch", VOICE_WITCH},
    {"woman", VOICE_WOMAN},
    {"word", VOICE_WORD},
    {"work", VOICE_WORK},
    {"workshop", VOICE_WORKSHOP},
    {"world", VOICE_WORLD},
    {"xavier", VOICE_XAVIER},
    {"xena", VOICE_XENA},
    {"yacht", VOICE_YACHT},
    {"year", VOICE_YEAR},
    {"yearly", VOICE_YEARLY},
    {"yoga", VOICE_YOGA},
    {"you", VOICE_YOU},
    {"zac", VOICE_ZAC},
    {"zachary", VOICE_ZACHARY},
    {"zara", VOICE_ZARA},
    {"zelda", VOICE_ZELDA},
    {"zero", VOICE_ZERO},
    {"zoe", VOICE_ZOE},
    {"zone", VOICE_ZONE},
    {"zoo", VOICE_ZOO},
    {NULL, VOICE_COUNT} 
};

/**
 * @brief Convert word to VoiceWord
 */
VoiceWord map_string_to_enum(const char *word) 
{
    if (!word) return VOICE_COUNT;

    // Convert to lowercase for comparison
    gchar *lower_word = g_ascii_strdown(word, -1);

    VoiceWord found_id = VOICE_COUNT;
    for (int i = 0; voice_map[i].text != NULL; i++) {
        if (g_strcmp0(lower_word, voice_map[i].text) == 0) {
            found_id = voice_map[i].id;
            break;
        }
    }

    g_free(lower_word);
    return found_id;
}
/**
 * @brief Speak words array
 */
static void speak_word_array(GPtrArray *words_array) 
{
    buffer_idx = 0; 
    uint32_t max_samples = SAMPLE_RATE * MAX_SPEAK_SECONDS;
    int silence_samples = (int)(SAMPLE_RATE * SILENCE_SECONDS);

    for (guint i = 0; i < words_array->len; i++) {
        char *full_entry = (char*)g_ptr_array_index(words_array, i);
        if (!full_entry) continue;

        char *safe_copy = g_strdup(full_entry);
        char *token = strtok(safe_copy, " -:;,.?!"); 
        
        while (token != NULL) {
            VoiceWord id = map_string_to_enum(token);
            if (id != VOICE_COUNT) {
                
                // --- CORRECTED SAFETY MATH ---
                // 1 byte of ADPCM = 2 PCM samples. 
                // Total space = (ADPCM bytes * 2) + silence samples.
                uint32_t samples_needed = (voice_dictionary[id].length * 2) + silence_samples;
                
                if (buffer_idx + samples_needed >= max_samples) {
                    g_print("Warning: Audio buffer full (%ds limit reached). Stopping at: %s\n", 
                             MAX_SPEAK_SECONDS, token);
                    g_free(safe_copy);
                    goto finalize_audio; 
                }

                append_word(id); 
            } else {
                g_print("Skipping unrecognized word: %s\n", token);
            }
            token = strtok(NULL, " -:;,.?!");
        }
        g_free(safe_copy);
    }

finalize_audio:
    if (buffer_idx > 0) {
        FILE* f = fopen(m_speak_file, "wb");
        if (f) {
            write_wav_header(f, buffer_idx, SAMPLE_RATE);
            fwrite(full_audio_buffer, sizeof(int16_t), buffer_idx, f);
            fclose(f);

            // Using GTask to play audio asynchronously
            GTask* task = g_task_new(NULL, NULL, play_audio_task_callbk, NULL);
            g_task_run_in_thread(task, play_audio_async);     
            g_object_unref(task);
        }
    }   
}


/**
 * @brief Check if file exists
 */
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

/**
 * @brief Play audio task finish callbk function
 */
static void play_audio_task_callbk(GObject *gobject,GAsyncResult *result,  gpointer  user_data)
{		
	//the task callbk function is called back when the 
	//play_alarm audio_async function has completed		
	GTask *task = G_TASK(result);    
    gboolean success = GPOINTER_TO_INT(g_task_get_task_data(task));    
    if (success) {       
		g_print("playback finished.\n");		
    } else {      
		g_print("playback failed.\n");
    }    
    m_talking=FALSE; 
}

/**
 * @brief Play audio task (audio in a thread)
 */
static void play_audio_async (GTask *task, gpointer object, gpointer task_data, GCancellable *cancellable)
{
	
	m_talking=TRUE; //stop any new speaking 
	gchar * command_str ="aplay";  	
    command_str =g_strconcat(command_str," ", m_speak_file, NULL);     
    system(command_str); 
	g_task_set_task_data(task, GINT_TO_POINTER(TRUE), NULL);
}

/**
 * @brief Load configuration defaults
 */
static void config_load_default()
{
	//talking
	m_talk=TRUE;
	m_talk_at_startup=TRUE;
	//calendar
	m_12hour_format=TRUE;
	m_show_end_time=FALSE;		
	m_window_width = 800;
    m_window_height = 600;
    m_paned_position = 350; // A sensible default for 600 height
}


/**
 * @brief Reads configuration values from the global config file into global variables.
 */
static void config_read() {    
    GKeyFile *kf = g_key_file_new();
    GError *error = NULL; // Our "Messenger"

    if (!g_key_file_load_from_file(kf, m_config_file, G_KEY_FILE_NONE, &error)) {
        g_warning("Could not load config: %s", error->message);
        g_error_free(error); // Clean up the messenger
        g_key_file_free(kf);
        return;
    }       

   
    m_talk = g_key_file_get_boolean(kf, "calendar_settings", "talk", &error);
    if (error) { m_talk = TRUE; g_clear_error(&error); }
    
	m_talk_at_startup=g_key_file_get_boolean(kf, "calendar_settings", "talk_startup", NULL);
	if (error) { m_talk_at_startup = TRUE; g_clear_error(&error); }
	
	m_12hour_format=g_key_file_get_boolean(kf, "calendar_settings", "hour_format", NULL);
	if (error) { m_12hour_format = 1; g_clear_error(&error); }
	
	m_show_end_time=g_key_file_get_boolean(kf, "calendar_settings", "show_end_time", NULL);
	if (error) { m_show_end_time = FALSE; g_clear_error(&error); }
	
	m_notable_dates=g_key_file_get_boolean(kf, "calendar_settings", "notable_dates", NULL);
	if (error) {m_notable_dates = TRUE; g_clear_error(&error); }
	
    m_window_width = g_key_file_get_integer(kf, "calendar_settings", "window_width", &error);
    if (error) { m_window_width = 800; g_clear_error(&error); }

    m_window_height = g_key_file_get_integer(kf, "calendar_settings", "window_height", &error);
    if (error) { m_window_height = 600; g_clear_error(&error); }

    m_paned_position = g_key_file_get_integer(kf, "calendar_settings", "paned_position", &error);
    if (error) { m_paned_position = 350; g_clear_error(&error); }

    // Final safety check
    if (m_paned_position <= 0) m_paned_position = 350;    

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
		
	//listview
	g_key_file_set_boolean(kf, "calendar_settings", "hour_format", m_12hour_format);
	g_key_file_set_boolean(kf, "calendar_settings", "show_end_time", m_show_end_time);
	
	g_key_file_set_boolean(kf, "calendar_settings", "notable_dates", m_notable_dates);
				
	//window size	
	g_key_file_set_integer(kf, "calendar_settings", "window_width", m_window_width);
	g_key_file_set_integer(kf, "calendar_settings", "window_height", m_window_height); 
	g_key_file_set_integer(kf, "calendar_settings", "paned_position", m_paned_position);
	
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

 
/**
 * @brief Gets number of day events from database.
 * @return The total count of day events.
 */
int  get_number_of_day_events(){	
	int event_count= db_get_number_day_events(db_handle, m_start_year,m_start_month,m_start_day);	
	return event_count;
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
 * @brief Gets the time strig for the list view display
 * @return list view time string
 */
char* get_time_str_display(int hour, int min) {
    if (m_12hour_format) {
        int h12 = (hour == 0 || hour == 12) ? 12 : hour % 12;
        const char* ampm = (hour < 12) ? "AM " : "PM ";
        
        // Formats as "3:02 PM" or "12:30 AM"
        return g_strdup_printf("%d:%02d %s", h12, min, ampm);
    } else {
        // Formats as "15:02" or "00:30"
        return g_strdup_printf("%02d:%02d", hour, min);
    }
}

/**
 * @brief Gets a formatted time string (e.g., "10:30" or "10:30 am").
 * @param hour The hour.
 * @param min The minute.
 * @return A newly allocated time string. The caller is responsible for freeing this.
 */
 
char* get_time_str(int hour, int min) {
    GString *ts = g_string_new("");
    int display_hour = hour;
    char *ampm = "";

    if (m_12hour_format) {
        if (hour == 0 && min == 0) return g_strdup("midnight");
        //if (hour == 12 && min == 0) return g_strdup("noon");

        if (hour == 0) { display_hour = 12; ampm = "am"; }
        else if (hour == 12) { ampm = "pm"; }
        else if (hour > 12) { display_hour = hour - 12; ampm = "pm"; }
        else { ampm = "am"; }
    }

    // 1. Append the Hour (Decompose if using 24h format and > 20)
    if (display_hour <= 20) {
        g_string_append_printf(ts, "%d ", display_hour);
    } else {
        g_string_append_printf(ts, "%d %d ", (display_hour / 10) * 10, display_hour % 10);
    }

    // 2. Append Minutes or O'clock
    if (min == 0) {
        //g_string_append(ts, "oclock ");
    } else if (min < 10) {
        // For 10:05, say "Ten Oh Five"
        g_string_append_printf(ts, "o %d ", min); 
    } else if (min <= 20) {
        // 10-20 are unique enums in your file
        g_string_append_printf(ts, "%d ", min);
    } else {
        // Decompose 21-59 (e.g., 32 -> "30 2")
        int tens = (min / 10) * 10;
        int units = min % 10;
        if (units == 0) g_string_append_printf(ts, "%d ", tens);
        else g_string_append_printf(ts, "%d %d ", tens, units);
    }

    if (m_12hour_format) {
        g_string_append(ts, ampm);
    }

    return g_string_free(ts, FALSE);
}

/**
 * @brief Gets day of week using day, month year values
 * @return Week day string
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
 * @brief Convert integer month value to month string.
 * @return Month string.
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
 * @brief Converts ordinal day number to single string for ADPCM
 * @return Day string (single word for date reader).
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
		day_str="twentyfirst";
		break;
		case 22:
		day_str="twentysecond";
		break;
		case 23:
		day_str="twentythird";
		break;
		case 24:
		day_str="twentyfourth";
		break;
		case 25:
		day_str="twentyfifth";
		break;
		case 26:
		day_str="twentysixth";
		break;
		case 27:
		day_str="twentyseventh";
		break;
		case 28:
		day_str="twentyeighth";
		break;
		case 29:
		day_str="twentyninth";
		break;
		case 30:
		day_str="thirtieth";
		break;
		case 31:
		day_str="thirtyfirst";
		break;
		default:
		//Unknown day ordinal
		day_str="unknown";
		break;
	  } //day switch
	return day_str;
}

/**
 * @brief Converts cardinal number to string
 * @return Cardinal number string.
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
/**
 * @brief Cleans text input for entry into database to prevent 
 * SQL errors or attacks
 * @return Clean string.
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
	
	
	//update calendar (also updates listbox)	
	set_marks_on_calendar(GTK_CALENDAR(calendar));
	update_calendar(GTK_CALENDAR(calendar), GTK_LABEL(label_date));		
	update_store(GTK_CALENDAR(calendar), store);	
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
	
	
	g_object_set_data(G_OBJECT(button_add_event), "day-key",GINT_TO_POINTER(m_start_day));
	g_object_set_data(G_OBJECT(button_add_event), "month-key",GINT_TO_POINTER(m_start_month));
	g_object_set_data(G_OBJECT(button_add_event), "year-key",GINT_TO_POINTER(m_start_year));
	
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
              
        // prevent a memory leak.
        free(clean_location);
        clean_location = NULL; // Best practice to set the pointer to NULL after freeing.
    }
    
    if (clean_description != NULL) {
               
        //prevent a memory leak.
        free(clean_description);
        clean_description = NULL; // Best practice to set the pointer to NULL after freeing.
    }
	
	//update calendar (also updates listbox)	
	set_marks_on_calendar(GTK_CALENDAR(calendar));
	update_calendar(GTK_CALENDAR(calendar), GTK_LABEL(label_date));	
	update_store(GTK_CALENDAR(calendar), store);	
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
	g_print("callbk edit event\n");
		
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
	
	time_str =get_time_str_display(start_hour,start_min);
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
	GtkWidget *calendar = g_object_get_data(G_OBJECT(selection), "selection-calendar-key");	
	GtkWidget *label_date=g_object_get_data(G_OBJECT(store), "store_label-date-key");
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
/**
 * @brief Confirm delete ALL from the database 
 * @param button The GSimpleAction that triggered the callback.
 * @param user_data A pointer to the Window.
 */
static void callbk_confirm_delete_all(GtkButton *button, gpointer  user_data)
{	
	GtkWindow *window =user_data;	
	GtkWidget *calendar =g_object_get_data(G_OBJECT(window), "window-calendar-key");
	GListStore *store =g_object_get_data(G_OBJECT(window), "window-store-key");
	GtkWidget *dialog = g_object_get_data(G_OBJECT(button), "dialog-key");
	GtkWidget *label_date = g_object_get_data(G_OBJECT(window), "window-label-date-key");

	if (db_delete_all_events(db_handle) == 0) 
	{
		//g_print("Successfully removed all events.\n");
	} else 
	{
		g_warning("Failed to remove all events.\n");
	}

	g_list_store_remove_all(G_LIST_STORE(store));
	
	//goto today
	GDateTime *today;
	today = g_date_time_new_now_local();
	m_start_year = g_date_time_get_year(today);
	m_start_month = g_date_time_get_month(today);
	m_start_day = g_date_time_get_day_of_month(today);	
	g_print("Delete All:  Set Date : %d-%d-%d \n", m_start_day, m_start_month,m_start_year);	
	gtk_calendar_select_day (GTK_CALENDAR(calendar), today);
	update_calendar(GTK_CALENDAR(calendar), GTK_LABEL(label_date));
	update_store(GTK_CALENDAR(calendar), store);
	g_date_time_unref(today);
		
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
	g_free(file_name); // <--- ADD THIS LINE!
	}
}
//======================================================================

/**
 * @brief Exports all calendar events to an iCal file.
 * * @param file_name The path to the file to export to.
 */
 void export_file(char *file_name) 
{
    GFile *file = g_file_new_for_path(file_name);
    GError *err = NULL;
    GFileOutputStream *file_stream = g_file_replace(file, 0, TRUE, G_FILE_CREATE_NONE, NULL, &err);
    
    if (!file_stream) {       
        g_warning ("Error: %s", err->message);
        g_error_free (err);
        g_object_unref (file);
        return;
    }

    GDataOutputStream *data_stream = g_data_output_stream_new(G_OUTPUT_STREAM(file_stream));
    GArray* all_events = db_get_all_events(db_handle);
    
    if (all_events) {
        g_data_output_stream_put_string(data_stream, "BEGIN:VCALENDAR\n", NULL, NULL);
        
        for (guint i = 0; i < all_events->len; ++i) {
            CalendarEvent* event = g_array_index(all_events, CalendarEvent*, i);
            
            // Note: g_object_get for strings (summary, location) ALLOCATES memory.
            // We MUST free these after use.
            gchar *summary = NULL, *location = NULL, *description = NULL;
            gint start_year, start_month, start_day, start_hour, start_min;
            gint end_year, end_month, end_day, end_hour, end_min;
            gint is_yearly, is_priority;

            g_object_get(event, 
                "summary", &summary, "location", &location, "description", &description,
                "startyear", &start_year, "startmonth", &start_month, "startday", &start_day,
                "starthour", &start_hour, "startmin", &start_min,
                "endyear", &end_year, "endmonth", &end_month, "endday", &end_day,
                "endhour", &end_hour, "endmin", &end_min,
                "isyearly", &is_yearly, "ispriority", &is_priority, NULL);

            // Using g_strdup_printf directly in the output stream is safer
            char *dts = g_strdup_printf("DTSTART:%d%02d%02dT%02d%02d00\n", start_year, start_month, start_day, start_hour, start_min);
            char *dte = g_strdup_printf("DTEND:%d%02d%02dT%02d%02d00\n", end_year, end_month, end_day, end_hour, end_min);
            
            g_data_output_stream_put_string(data_stream, "BEGIN:VEVENT\n", NULL, NULL);
            g_data_output_stream_put_string(data_stream, dts, NULL, NULL);
            g_data_output_stream_put_string(data_stream, dte, NULL, NULL);
            
            // Formatting lines
            char *loc_line = g_strdup_printf("LOCATION:%s\n", location ? location : "");
            char *sum_line = g_strdup_printf("SUMMARY:%s\n", summary ? summary : "");
            g_data_output_stream_put_string(data_stream, loc_line, NULL, NULL);
            g_data_output_stream_put_string(data_stream, sum_line, NULL, NULL);

            if(is_yearly) {
                char *rrule = g_strdup_printf("RRULE:FREQ=YEARLY;INTERVAL=1;BYMONTH=%d;BYMONTHDAY=%d\n", start_month, start_day);
                g_data_output_stream_put_string(data_stream, rrule, NULL, NULL);
                g_free(rrule);
            }

            g_data_output_stream_put_string(data_stream, "END:VEVENT\n", NULL, NULL);

            // --- CRITICAL CLEANUP ---
            g_free(summary); g_free(location); g_free(description);
            g_free(dts); g_free(dte); g_free(loc_line); g_free(sum_line);
            g_object_unref(event);
        }
        g_data_output_stream_put_string(data_stream, "END:VCALENDAR\n", NULL, NULL);
        g_array_unref(all_events);
    }
        
    g_object_unref(data_stream);
    g_object_unref(file_stream);
    g_object_unref(file);
}
 

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

/**
 * @brief Helper
 * @param string with first zero removed.
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
 * @brief Imports events from an iCal file.
 * @param gpointer to GtkWindow to get data
 */ 
void import_ical_file(gpointer user_data) 
{
    GtkWidget *window = user_data;
    // [FIX] Checking keys. If you use global m_calendar, ensure these keys are actually set on the window!
    GtkWidget *calendar = g_object_get_data(G_OBJECT(window), "window-calendar-key");
    GListStore *store = g_object_get_data(G_OBJECT(window), "window-store-key");
    GtkWidget *label_date = g_object_get_data(G_OBJECT(window), "window-label-date-key");

    if (!calendar || !store) {
        g_critical("Could not find calendar or store via window keys!");
        return;
    }

    GFile *file = g_file_new_for_path(m_file_name);
    GFileInputStream *file_stream = g_file_read(file, NULL, NULL);

    if (!file_stream) {
        g_warning("CRITICAL: unable to open file: %s", m_file_name);
        g_object_unref(file);
        return;
    }

    GDataInputStream *input_stream = g_data_input_stream_new(G_INPUT_STREAM(file_stream));

    // Initialize to empty strings rather than NULL to prevent strcmp crashes
    char *summary_str = g_strdup("");   
    char *location_str = g_strdup("");
    char *description_str = g_strdup("");
    char *timezone_str = g_strdup("");

    int start_day=0, start_month=0, start_year=0, start_hour=0, start_min=0;
    int end_day=0, end_month=0, end_year=0, end_hour=0, end_min=0;
    int is_allday=0, is_priority=0, is_yearly=0;

    char *line;
    while ((line = g_data_input_stream_read_line(input_stream, NULL, NULL, NULL))) {
        g_strstrip(line);
        gchar** tokens = g_strsplit(line, ":", -1);
        
        if (tokens[0] && tokens[1]) {
            char *key = tokens[0];
            char *value = tokens[1];

            if (g_str_has_prefix(key, "DTSTART")) {
                char *y = g_utf8_substring(value, 0, 4);
                char *m = g_utf8_substring(value, 4, 6);
                char *d = g_utf8_substring(value, 6, 8);
                // Simple safety check for time string length
                char *h = (strlen(value) >= 11) ? g_utf8_substring(value, 9, 11) : g_strdup("0");
                char *mi = (strlen(value) >= 13) ? g_utf8_substring(value, 11, 13) : g_strdup("0");

                start_year = (int)g_ascii_strtoll(y, NULL, 10);
                start_month = (int)g_ascii_strtoll(ignore_first_zero(m), NULL, 10);
                start_day = (int)g_ascii_strtoll(ignore_first_zero(d), NULL, 10);
                start_hour = (int)g_ascii_strtoll(ignore_first_zero(h), NULL, 10);
                start_min = (int)g_ascii_strtoll(ignore_first_zero(mi), NULL, 10);

                g_free(y); g_free(m); g_free(d); g_free(h); g_free(mi);
            }

            if (g_str_has_prefix(key, "DTEND")) {
                char *y = g_utf8_substring(value, 0, 4);
                char *m = g_utf8_substring(value, 4, 6);
                char *d = g_utf8_substring(value, 6, 8);
                char *h = (strlen(value) >= 11) ? g_utf8_substring(value, 9, 11) : g_strdup("0");
                char *mi = (strlen(value) >= 13) ? g_utf8_substring(value, 11, 13) : g_strdup("0");

                end_year = (int)g_ascii_strtoll(y, NULL, 10);
                end_month = (int)g_ascii_strtoll(ignore_first_zero(m), NULL, 10);
                end_day = (int)g_ascii_strtoll(ignore_first_zero(d), NULL, 10);
                end_hour = (int)g_ascii_strtoll(ignore_first_zero(h), NULL, 10);
                end_min = (int)g_ascii_strtoll(ignore_first_zero(mi), NULL, 10);

                g_free(y); g_free(m); g_free(d); g_free(h); g_free(mi);
            }

            if (g_strcmp0(key, "SUMMARY") == 0) {
                g_free(summary_str);
                summary_str = g_strdup(value);
            }
            if (g_strcmp0(key, "LOCATION") == 0) {
                g_free(location_str);
                location_str = g_strdup(value);
            }
            if (g_strcmp0(key, "DESCRIPTION") == 0) {
                g_free(description_str);
                description_str = g_strdup(value);
            }

            if (g_strcmp0(key, "END") == 0 && g_strcmp0(value, "VEVENT") == 0) {
                is_allday = (start_hour == 0 && start_min == 0) ? 1 : 0;
                CalendarEvent *evt = g_object_new(CALENDAR_TYPE_EVENT, NULL);
                
                // Reverting to g_strdup here to ensure the Object gets a clean copy
                g_object_set(evt, 
                    "summary", g_strdup(summary_str), 
                    "location", g_strdup(location_str), 
                    "description", g_strdup(description_str),
                    "startyear", start_year, "startmonth", start_month, "startday", start_day,
                    "starthour", start_hour, "startmin", start_min,
                    "endyear", end_year, "endmonth", end_month, "endday", end_day,
                    "endhour", end_hour, "endmin", end_min,
                    "isyearly", is_yearly, "isallday", is_allday, "ispriority", is_priority, NULL);

                db_insert_event(db_handle, evt);
                g_object_unref(evt);

                // Reset for next event - keep them as empty strings
                g_free(summary_str); summary_str = g_strdup("");
                g_free(location_str); location_str = g_strdup("");
                g_free(description_str); description_str = g_strdup("");
            }
        }
        g_strfreev(tokens);
        g_free(line);
    }

    // Refresh UI
    GDateTime *today = g_date_time_new_now_local();
    gtk_calendar_select_day(GTK_CALENDAR(calendar), today);
    update_calendar(GTK_CALENDAR(calendar), GTK_LABEL(label_date));
    update_store(GTK_CALENDAR(calendar), store);

    // Final Cleanup
    g_free(summary_str);
    g_free(location_str);
    g_free(description_str);
    g_free(timezone_str);
    g_date_time_unref(today);
    g_object_unref(input_stream);
    g_object_unref(file_stream);
    g_object_unref(file);
}


/**
 * @brief Callback for the file open response after an import operation.
 * @param source The GObject that initiated the open operation.
 * @param result The GAsyncResult object.
 * @param user_data (not used)
 */
////working
//static void file_open_response (GObject *source, GAsyncResult *result, void *user_data)
//{
	//GtkFileDialog *dialog = GTK_FILE_DIALOG (source);    
	//GtkWidget *window = g_object_get_data(G_OBJECT(dialog), "dialog-window-key");	
	//GFile *file;	
	//file = gtk_file_dialog_open_finish (dialog, result, NULL);
	//if (file)
	//{ 
	//m_file_name = g_file_get_path(file);
	//import_ical_file(window);	  
	//g_object_unref (file);
	//}
//}   

/**
 * @brief file open response
 * @param GObject source
 */ 
static void file_open_response (GObject *source, GAsyncResult *result, void *user_data)
{
	GtkFileDialog *dialog = GTK_FILE_DIALOG (source);    
	GtkWidget *window = g_object_get_data(G_OBJECT(dialog), "dialog-window-key");	
	GFile *file;	
	file = gtk_file_dialog_open_finish(dialog, result, NULL);	
	if (file) {
	//Free the OLD path if it exists before storing the NEW one
	if (m_file_name != NULL) g_free(m_file_name);
	m_file_name = g_file_get_path(file);
	import_ical_file(window);      
	g_object_unref (file);
	}
}   

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



static void jump_to_date(int day, int month, int year) {
    // Assuming 'm_calendar' is your global GtkCalendar widget
    GDateTime *target = g_date_time_new_local(year, month, day, 12, 0, 0);
    gtk_calendar_select_day(GTK_CALENDAR(m_calendar), target);
    g_date_time_unref(target);
}

static void on_search_row_activated(GtkListBox *box, GtkListBoxRow *row, gpointer user_data) {
    // We store the date inside the row object using g_object_set_data
    int d = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(row), "d"));
    int m = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(row), "m"));
    int y = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(row), "y"));

    jump_to_date(d, m, y);
    
    // Optional: Close the search results window after clicking
    GtkWidget *toplevel = GTK_WIDGET(gtk_widget_get_native(GTK_WIDGET(box)));
    gtk_window_destroy(GTK_WINDOW(toplevel));
}

/**
 * @brief Performs a search for events and displays results in a clickable list view.
 */
static void execute_event_search(const char* search_str, gboolean search_location) {
    char* search_str_lower = g_ascii_strdown(search_str, -1);
    
    GtkWidget *dialog = gtk_window_new(); 
    gtk_window_set_title(GTK_WINDOW(dialog), "Search Results (Click to View)");
    gtk_window_set_default_size(GTK_WINDOW(dialog), 400, 400);
    
    GtkWidget *list_box = gtk_list_box_new();
    gtk_list_box_set_selection_mode(GTK_LIST_BOX(list_box), GTK_SELECTION_SINGLE);
    g_signal_connect(list_box, "row-activated", G_CALLBACK(on_search_row_activated), NULL);

    GArray* search_results = db_get_events_by_search(db_handle, 
                             search_location ? NULL : search_str_lower, 
                             search_location ? search_str_lower : NULL);
     
    if (search_results && search_results->len > 0) {
        for (guint i = 0; i < search_results->len; ++i) {
            CalendarEvent* event = g_array_index(search_results, CalendarEvent*, i);
            
            int d = calendar_event_get_start_day(event);
            int m = calendar_event_get_start_month(event);
            int y = calendar_event_get_start_year(event);

            // Create a nice label for the row
            char *label_text = g_strdup_printf("%02d/%02d/%d - %s", d, m, y, calendar_event_get_summary(event));
            GtkWidget *row_label = gtk_label_new(label_text);
            gtk_widget_set_halign(row_label, GTK_ALIGN_START);
            
            GtkWidget *row = gtk_list_box_row_new();
            gtk_list_box_row_set_child(GTK_LIST_BOX_ROW(row), row_label);
            
            // ATTACH DATE DATA TO THE ROW so the callback knows where to go
            g_object_set_data(G_OBJECT(row), "d", GINT_TO_POINTER(d));
            g_object_set_data(G_OBJECT(row), "m", GINT_TO_POINTER(m));
            g_object_set_data(G_OBJECT(row), "y", GINT_TO_POINTER(y));
            
            gtk_list_box_append(GTK_LIST_BOX(list_box), row);

            g_free(label_text);
            g_object_unref(event);
        }
    } else {
        gtk_list_box_append(GTK_LIST_BOX(list_box), gtk_label_new("No events found."));
    }

    GtkWidget *scrolled = gtk_scrolled_window_new();    
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled), list_box);
    gtk_window_set_child(GTK_WINDOW(dialog), scrolled);
    
    if (search_results) g_array_unref(search_results);
    g_free(search_str_lower);
    
    gtk_window_present(GTK_WINDOW(dialog));   
}

/**
 * @brief Search events.
 */
static void callbk_search_events(GtkButton *button, gpointer user_data)
{
    GtkWidget *entry_search = g_object_get_data(G_OBJECT(button), "entry-search-key");
    GtkWidget *check_loc = g_object_get_data(G_OBJECT(button), "check-button-search-location-key");

    const char* raw_text = gtk_editable_get_text(GTK_EDITABLE(entry_search));
    char* clean_str = sanitize_text(raw_text);
    
    gboolean do_location = gtk_check_button_get_active(GTK_CHECK_BUTTON(check_loc));
    
    execute_event_search(clean_str, do_location);
    
    // sanitize_text likely uses malloc/g_malloc
    g_free(clean_str); 
}

/**
 * @brief Helper
 */
static void on_entry_activate(GtkEntry *entry, gpointer user_data) {
    GtkButton *search_button = GTK_BUTTON(user_data);
    // Physically trigger the button click logic
    g_signal_emit_by_name(search_button, "clicked");
}

/**
 * @brief Helper
 */
static void on_clear_clicked(GtkButton *btn, gpointer user_data) {
    GtkEditable *entry = GTK_EDITABLE(user_data);
    gtk_editable_set_text(entry, "");
}

/**
 * @brief Callback for the search action, which opens a search dialog.
 * @param action The GSimpleAction that triggered the callback.
 * @param parameter The GVariant parameter (unused).
 * @param user_data A pointer to the GtkWindow.
 */
static void callbk_search(GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
    GtkWidget *window = user_data;
    GtkWidget *dialog_search = gtk_window_new(); 
    gtk_window_set_title(GTK_WINDOW(dialog_search), "Search Events");
    gtk_window_set_default_size(GTK_WINDOW(dialog_search), 350, -1);
    
    gtk_window_set_transient_for(GTK_WINDOW(dialog_search), GTK_WINDOW(window));

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    //GTK4 requires individual margin settings
    gtk_widget_set_margin_start(box, 15);
    gtk_widget_set_margin_end(box, 15);
    gtk_widget_set_margin_top(box, 15);
    gtk_widget_set_margin_bottom(box, 15);
    
    gtk_window_set_child(GTK_WINDOW(dialog_search), box);
    
    GtkWidget *entry_search = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_search), "Enter search text...");
    // Auto-focus the entry so the user can just start typing immediately
	gtk_widget_grab_focus(entry_search);

    GtkWidget *check_button_search_location = gtk_check_button_new_with_label("Search Location only");

    GtkWidget *button_group = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_add_css_class(button_group, "linked");
    gtk_widget_set_halign(button_group, GTK_ALIGN_CENTER);

    GtkWidget *button_search = gtk_button_new_with_label("Search");
    GtkWidget *button_clear = gtk_button_new_from_icon_name("edit-clear-symbolic");
    gtk_widget_set_tooltip_text(button_clear, "Clear search text");
    
    // When Enter is pressed in the text box, 'click' the search button automatically
	//g_signal_connect_swapped(entry_search, "activate", G_CALLBACK(g_signal_emit_by_name), button_search);
	// When Enter is pressed, call our helper and pass the search button to it
	g_signal_connect(entry_search, "activate", G_CALLBACK(on_entry_activate), button_search);

    gtk_box_append(GTK_BOX(button_group), button_search);
    gtk_box_append(GTK_BOX(button_group), button_clear);

    // --- SIGNALS ---
    g_signal_connect(button_search, "clicked", G_CALLBACK(callbk_search_events), window);
    // Use your custom function for clarity
    g_signal_connect(button_clear, "clicked", G_CALLBACK(on_clear_clicked), entry_search);

    // Data for the search callback
    g_object_set_data(G_OBJECT(button_search), "check-button-search-location-key", check_button_search_location);
    g_object_set_data(G_OBJECT(button_search), "entry-search-key", entry_search);
    
    gtk_box_append(GTK_BOX(box), gtk_label_new("Search for events:"));
    gtk_box_append(GTK_BOX(box), entry_search);    
    gtk_box_append(GTK_BOX(box), check_button_search_location);    
    gtk_box_append(GTK_BOX(box), button_group);

    gtk_window_present(GTK_WINDOW(dialog_search));    
}

/**
 * @brief Callback for the About dialog.
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
	gtk_about_dialog_set_version (GTK_ABOUT_DIALOG(about_dialog), "Version 0.6 Series");
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(about_dialog),"Copyright © 2026");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(about_dialog),"Talk Calendar (TDPCM Synthesizer)");
	gtk_about_dialog_set_license_type (GTK_ABOUT_DIALOG(about_dialog), GTK_LICENSE_LGPL_2_1);
	gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(about_dialog),"https://github.com/crispinprojects/");
	gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(about_dialog),"Talk Calendar Website");
	gtk_about_dialog_set_authors(GTK_ABOUT_DIALOG(about_dialog), authors);
	//gtk_about_dialog_set_logo_icon_name(GTK_ABOUT_DIALOG(about_dialog), NULL);	
	gtk_about_dialog_set_logo_icon_name(GTK_ABOUT_DIALOG(about_dialog), "gtk-about");
	gtk_widget_set_visible (about_dialog, TRUE);		
	
}

/**
 * @brief Day of week helper
 */
int dayOfWeek(int day, int month, int year) {
    // Zeller's congruence algorithm
    if (month < 3) {
        month += 12;
        year--;
    }
    
    int k = year % 100;
    int j = year / 100;
    
    int h = (day + (13 * (month + 1)) / 5 + k + k/4 + j/4 - 2*j) % 7;
    
    // Convert to standard day numbering (0 = Sunday, 1 = Monday, ..., 6 = Saturday)
    return (h + 5) % 7;
}

/**
 * @brief Speak events call back
 */
static void callbk_speak(GSimpleAction* action, GVariant *parameter,gpointer user_data)
{	
	//callbk speak
	g_print("callbk speak\n");
	if(m_talking == FALSE) speak_events();	
}


/**Speak events (core)
 */
static void speak_events() {    
    if(m_talk == 0 || m_talking == TRUE) return;

    //full_audio_buffer = malloc(SAMPLE_RATE * 240 * sizeof(int16_t));    //240 seconds
    GPtrArray *words_array = g_ptr_array_new_with_free_func(g_free);

    // 1. Add Date Components
    g_ptr_array_add(words_array, g_strdup(get_day_of_week(m_start_day, m_start_month, m_start_year)));
    g_ptr_array_add(words_array, g_strdup(get_day_number_ordinal_string(m_start_day)));
    g_ptr_array_add(words_array, g_strdup(get_month_string(m_start_month)));    

    // 2. Fetch Events
    GArray* events_for_day = db_get_all_events_year_month_day(db_handle, m_start_year, m_start_month, m_start_day);
    
    if (events_for_day) {      
        for (guint i = 0; i < events_for_day->len; i++) {
            CalendarEvent* day_event = g_array_index(events_for_day, CalendarEvent*, i);
            char *summary_str = NULL;
            gint start_hour, start_min, is_allday, is_priority;
            
            g_object_get(day_event, 
                "summary", &summary_str, 
                "starthour", &start_hour, 
                "startmin", &start_min, 
                "isallday", &is_allday, 
                "ispriority", &is_priority, 
                NULL);
            
            // Add Time (if not all day)
            if(!is_allday) {
                // get_time_str returns a new string; we just add it directly
                g_ptr_array_add(words_array, get_time_str(start_hour, start_min));
            }

            // Add Summary (lowercased)
            if (summary_str) {
                g_ptr_array_add(words_array, g_ascii_strdown(summary_str, -1));
                g_free(summary_str); // Free the copy created by g_object_get
            }

            // Add Priority
            if(is_priority) {    
                g_ptr_array_add(words_array, g_strdup("high priority"));
            }      
            
            g_object_unref(day_event); 
        }
        g_array_free(events_for_day, TRUE);
    }
    
    g_print("Words array: ");
    for (guint i = 0; i < words_array->len; i++) {
        g_print("%s ", (char*)g_ptr_array_index(words_array, i));
    }
    g_print("\n"); 

    // 3. Play everything
    speak_word_array(words_array);

    g_ptr_array_unref(words_array);
    //free(full_audio_buffer);
}


/**
 * @brief Speak time call back
 */
static void callbk_speaktime(GSimpleAction * action, GVariant *parameter, gpointer user_data)
{	
	g_print("callbk time\n");
	speak_time();
}

/**
 * @brief Speak time
 * @param hour 
 * @param minute
 */
static void speak_time(gint hour, gint min) 
{	
	if(m_talk==0) return;
	if (m_talking ==TRUE) return;	
	 // Large buffer for full sentence (approx 15 seconds)
    full_audio = malloc(SAMPLE_RATE * 15 * sizeof(int16_t));
    current_sample_idx = 0;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    // Time Section
    decode_word_to_buffer(VOICE_THE, full_audio, &current_sample_idx);
    decode_word_to_buffer(VOICE_TIME, full_audio, &current_sample_idx);
    decode_word_to_buffer(VOICE_IS, full_audio, &current_sample_idx);    
    play_time(tm.tm_hour, tm.tm_min);
    // Save and play
    FILE *f = fopen(m_speak_file, "wb");
    if (f) {
        write_wav_header(f, current_sample_idx, SAMPLE_RATE);
        fwrite(full_audio, sizeof(int16_t), current_sample_idx, f);
        fclose(f);
    } 
    GTask* task = g_task_new(NULL, NULL, play_audio_task_callbk, NULL);			
	g_task_run_in_thread(task, play_audio_async);     
	g_object_unref(task);
    free(full_audio);
	 

}

/**
 * @brief Set preferences
 */
static void callbk_set_preferences(GtkButton *button, gpointer  user_data)
{
	//callbk preferences
	//g_print("set preferences\n");
	GtkWidget *window = user_data;
	GtkWidget *calendar =g_object_get_data(G_OBJECT(window), "window-calendar-key");
	GtkWidget *label_date =g_object_get_data(G_OBJECT(window), "window-label-date-key");
	GtkWidget *dialog = g_object_get_data(G_OBJECT(button), "dialog-key");
	//calendar listbox
	GtkWidget *check_button_hour_format= g_object_get_data(G_OBJECT(button), "check-button-hour-format-key");
	GtkWidget *check_button_show_end_time= g_object_get_data(G_OBJECT(button), "check-button-show-end-time-key");	
	GtkWidget *check_button_notable_dates= g_object_get_data(G_OBJECT(button), "check-button-notable-dates-key");	//general talk preferences	
	GtkWidget *check_button_talk= g_object_get_data(G_OBJECT(button), "check-button-talk-key");
    GtkWidget *check_button_talk_startup= g_object_get_data(G_OBJECT(button), "check-button-talk-startup-key");     
   
    GtkWidget *check_button_reset_all= g_object_get_data(G_OBJECT(button), "check-button-reset-all-key");
	//calendar
	m_12hour_format=gtk_check_button_get_active (GTK_CHECK_BUTTON(check_button_hour_format));
	m_show_end_time=gtk_check_button_get_active (GTK_CHECK_BUTTON(check_button_show_end_time));
	m_notable_dates=gtk_check_button_get_active (GTK_CHECK_BUTTON(check_button_notable_dates));		
	//talk general
	m_talk=gtk_check_button_get_active (GTK_CHECK_BUTTON(check_button_talk));
	m_talk_at_startup=gtk_check_button_get_active (GTK_CHECK_BUTTON(check_button_talk_startup));	

	m_reset_preferences=gtk_check_button_get_active(GTK_CHECK_BUTTON(check_button_reset_all));
	if(m_reset_preferences) {
	//reset everything
	//calendar
	m_12hour_format=1;
	m_show_end_time=0;
	m_notable_dates=TRUE;		
	//speaking
	m_talk=TRUE;
	m_talk_at_startup=FALSE; 
	m_window_width=800;
    m_window_height=600;
    m_paned_position=350;
	m_reset_preferences=0; //toggle
	}		
	config_write();	//save preferences	
	set_marks_on_calendar(GTK_CALENDAR(calendar));
	update_calendar(GTK_CALENDAR(calendar), GTK_LABEL(label_date));
	gtk_window_destroy(GTK_WINDOW(dialog));    
}

/**
 * @brief Set preferences call back
 */
static void callbk_preferences(GSimpleAction* action, GVariant *parameter,gpointer user_data)
{		
	g_print("callbk preferences\n");
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
	
		
	check_button_reset_all = gtk_check_button_new_with_label ("Reset All");			 
	//set calendar preferences
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_hour_format),m_12hour_format);
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_show_end_time), m_show_end_time);	
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_notable_dates),m_notable_dates);			
	//set speak
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_talk), m_talk);
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_talk_startup), m_talk_at_startup);	
	gtk_check_button_set_active (GTK_CHECK_BUTTON(check_button_reset_all), m_reset_preferences);
	//data setters	
	g_object_set_data(G_OBJECT(button_set), "dialog-key",dialog);
	//connections
	//speaking
	g_object_set_data(G_OBJECT(button_set), "check-button-talk-key",check_button_talk);
	g_object_set_data(G_OBJECT(button_set), "check-button-talk-startup-key",check_button_talk_startup);	
	//display
	g_object_set_data(G_OBJECT(button_set), "check-button-hour-format-key",check_button_hour_format);
	g_object_set_data(G_OBJECT(button_set), "check-button-show-end-time-key",check_button_show_end_time);
	g_object_set_data(G_OBJECT(button_set), "check-button-notable-dates-key",check_button_notable_dates);
		
	g_object_set_data(G_OBJECT(button_set), "check-button-reset-all-key",check_button_reset_all);			
	//Calendar preferences	
	gtk_grid_attach(GTK_GRID(grid), check_button_hour_format,          1,1,1,1);			
	gtk_grid_attach(GTK_GRID(grid), check_button_show_end_time,        2,1,1,1);
	gtk_grid_attach(GTK_GRID(grid), check_button_notable_dates,        3,1,1,1);		
	gtk_grid_attach(GTK_GRID(grid), label_spacer1,                     1, 2, 1, 1);	
	//speak preferences
	gtk_grid_attach(GTK_GRID(grid), check_button_talk,      		    1, 3, 1, 1);	
	gtk_grid_attach(GTK_GRID(grid), check_button_talk_startup,        	2, 3, 1, 1);		
	gtk_grid_attach(GTK_GRID(grid), label_spacer2,                      1, 4, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), check_button_reset_all,             1, 5, 1, 1);	
	gtk_grid_attach(GTK_GRID(grid), label_spacer3,                      1, 6, 1, 1);	
	gtk_grid_attach(GTK_GRID(grid), button_set,                         1, 7, 3, 1);	
    gtk_window_set_child (GTK_WINDOW (dialog), grid);	
	gtk_window_present(GTK_WINDOW(dialog));		
}

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
    
    int easter_year = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_button_year));
    
    // 1. Calculate the date
    GDate* easter_date = calculate_easter(easter_year);    
    
    // 2. Convert GDate to GDateTime so we can use the easy formatter
    // (We use 12:00:00 to be safe with timezones)
    GDateTime *dt = g_date_time_new_local(
        g_date_get_year(easter_date), 
        g_date_get_month(easter_date), 
        g_date_get_day(easter_date), 
        12, 0, 0
    );

    // 3. Format everything in one go: %A (Weekday) %e (Day) %B (Month) %Y (Year)
    char *result_str = g_date_time_format(dt, "%A %e %B %Y");
    
    // 4. Update the UI
    gtk_label_set_text(GTK_LABEL(label_result), result_str);    
    
    // 5. CLEANUP - No more leaks!
    g_free(result_str);    
    g_date_time_unref(dt);
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
	
	//dialog_easter = gtk_window_new();
	dialog_easter = gtk_window_new(); 
	gtk_window_set_transient_for(GTK_WINDOW(dialog_easter), GTK_WINDOW(window));
	gtk_window_set_modal(GTK_WINDOW(dialog_easter), TRUE); // Optional: makes it so you must close this before using main window
		 
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
 * @brief Callback for information (provide user with application information)
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
	gint response;
	
	GtkWidget *label_keyboard_shortcuts;	
	GtkWidget *label_home_shortcut;
	
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
		
	label_home_shortcut=gtk_label_new("Home: Go to today");		
	label_preferences_shortcut=gtk_label_new("Ctrl+Alt+P: Preferences");
	label_info_shortcut=gtk_label_new("F1: Information");
	label_speak_shortcut=gtk_label_new("Spacebar: Speak day events");
	label_time_shortcut=gtk_label_new("T Key: Speak time");
	
		
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
	gtk_box_append(GTK_BOX(box),label_info_shortcut);
	gtk_box_append(GTK_BOX(box),label_preferences_shortcut);	
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

/**
 * @brief Updates the date label
 * @param calendar The GtkCalendar
 * @param user_data A pointer to the  date GtkLabel.
 */

static void update_date_label(GtkCalendar *calendar, gpointer user_data)
{
    GtkWidget *label_date = (GtkWidget *) user_data;
    
    GDateTime *dt = g_date_time_new_local(m_start_year, m_start_month, m_start_day, 12, 0, 0);
    if (!dt) return;

    char *base_str = g_date_time_format(dt, "%A %e %B %Y");
    g_date_time_unref(dt);

    char *final_str = g_strdup(base_str);
    g_free(base_str);

    if (m_notable_dates) {
        GDate *curr = g_date_new_dmy(m_start_day, m_start_month, m_start_year);
        const char *holiday_name = NULL;

        // --- FIXED DATE CHECKS ---
        if (m_start_month == 1 && m_start_day == 1)        holiday_name = "New Year's Day";
        else if (m_start_month == 2 && m_start_day == 14)  holiday_name = "Valentines Day";
        else if (m_start_month == 3 && m_start_day == 1)   holiday_name = "St. Davids Day";
        else if (m_start_month == 3 && m_start_day == 17)  holiday_name = "St. Patricks Day";
        else if (m_start_month == 4 && m_start_day == 23)  holiday_name = "St. Georges Day";
        else if (m_start_month == 10 && m_start_day == 25) holiday_name = "St. Crispins Day";
        else if (m_start_month == 11 && m_start_day == 5)  holiday_name = "Guy Fawkes Night";
        else if (m_start_month == 11 && m_start_day == 30) holiday_name = "St. Andrews Day";
        else if (m_start_month == 12 && m_start_day == 25) holiday_name = "Christmas Day";
        else if (m_start_month == 12 && m_start_day == 26) holiday_name = "Boxing Day";
       
        // --- EASTER RELATED CHECKS ---
        if (!holiday_name) {
            GDate *easter = calculate_easter(m_start_year);
            
            // Good Friday (Easter - 2 days)
            GDate *good_friday = g_date_copy(easter);
            g_date_subtract_days(good_friday, 2);
            
            // Easter Monday (Easter + 1 day)
            GDate *easter_monday = g_date_copy(easter);
            g_date_add_days(easter_monday, 1);

            if (g_date_compare(curr, easter) == 0) holiday_name = "Easter Sunday";
            else if (g_date_compare(curr, good_friday) == 0) holiday_name = "Good Friday";
            else if (g_date_compare(curr, easter_monday) == 0) holiday_name = "Easter Monday";

            g_date_free(easter);
            g_date_free(good_friday);
            g_date_free(easter_monday);
        }

        // --- UK BANK HOLIDAY LOGIC ---
        if (!holiday_name) {
            if (m_start_month == 5) {
                GDate *may1 = g_date_new_dmy(1, 5, m_start_year);
                while (g_date_get_weekday(may1) != G_DATE_MONDAY) g_date_add_days(may1, 1);
                if (m_start_day == g_date_get_day(may1)) holiday_name = "Early May Bank Holiday";
                g_date_free(may1);

                if (!holiday_name) {
                    GDate *last_may = g_date_new_dmy(31, 5, m_start_year);
                    while (g_date_get_weekday(last_may) != G_DATE_MONDAY) g_date_subtract_days(last_may, 1);
                    if (m_start_day == g_date_get_day(last_may)) holiday_name = "Spring Bank Holiday";
                    g_date_free(last_may);
                }
            }
            else if (m_start_month == 8) {
                GDate *last_aug = g_date_new_dmy(31, 8, m_start_year);
                while (g_date_get_weekday(last_aug) != G_DATE_MONDAY) g_date_subtract_days(last_aug, 1);
                if (m_start_day == g_date_get_day(last_aug)) holiday_name = "August Bank Holiday";
                g_date_free(last_aug);
            }
        }

        if (holiday_name) {
            char *temp = final_str;
            final_str = g_strconcat(temp, " (", holiday_name, ")", NULL);
            g_free(temp);
        }

        g_date_free(curr);
    }

    if (get_number_of_day_events() > 0) {
        char *temp = final_str;
        final_str = g_strconcat(temp, " *", NULL);
        g_free(temp);
    }

    gtk_label_set_text(GTK_LABEL(label_date), final_str);
    g_free(final_str);
}

/**
 * @brief Updates the Calendar
 * @param GtkCalendar
 * @param user_data A pointer to the date GtkLabel.
 */
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
}

/**
 * @brief Next month call back
 * @param GtkCalendar
 * @param user_data A pointer to the date GtkLabel.
 */
static void callbk_calendar_next_month(GtkCalendar *calendar, gpointer user_data)
{
	g_print("next month\n");
	GtkWidget *label_date = (GtkWidget *)user_data;	
	update_calendar(GTK_CALENDAR(calendar), GTK_LABEL(label_date));		
	GListStore *store =g_object_get_data(G_OBJECT(calendar), "calendar-store-key");	
	update_store(GTK_CALENDAR(calendar), store);
}

/**
 * @brief Previous month call back
 * @param GtkCalendar
 * @param user_data A pointer to the date GtkLabel.
 */
static void callbk_calendar_prev_month(GtkCalendar *calendar, gpointer user_data)
{
	g_print("prev month\n");		
    GtkWidget *label_date = (GtkWidget *)user_data;	
	update_calendar(GTK_CALENDAR(calendar), GTK_LABEL(label_date));		
	GListStore *store =g_object_get_data(G_OBJECT(calendar), "calendar-store-key");	
	update_store(GTK_CALENDAR(calendar), store);
}

/**
 * @brief Next year call back
 * @param GtkCalendar
 * @param user_data A pointer to the date GtkLabel.
 */
static void callbk_calendar_next_year(GtkCalendar *calendar, gpointer user_data)
{
	g_print("next year\n");
	GtkWidget *label_date = (GtkWidget *)user_data;	
	update_calendar(GTK_CALENDAR(calendar), GTK_LABEL(label_date));		
	GListStore *store =g_object_get_data(G_OBJECT(calendar), "calendar-store-key");	
	update_store(GTK_CALENDAR(calendar), store);
}

/**
 * @brief Previous year call back
 * @param GtkCalendar
 * @param user_data A pointer to the date GtkLabel.
 */
static void callbk_calendar_prev_year(GtkCalendar *calendar, gpointer user_data)
{
	g_print("prev year\n");
	GtkWidget *label_date = (GtkWidget *)user_data;	
	update_calendar(GTK_CALENDAR(calendar), GTK_LABEL(label_date));		
	GListStore *store =g_object_get_data(G_OBJECT(calendar), "calendar-store-key");	
	update_store(GTK_CALENDAR(calendar), store);
}


/**
 * @brief Day selected call back
 * @param GtkCalendar
 * @param user_data A pointer to the GListStore  store.
 */
static void callbk_calendar_day_selected(GtkCalendar *calendar, gpointer user_data)
{
	g_print("day selected\n");
	GListStore *store =user_data;	
	GtkWidget *label_date =g_object_get_data(G_OBJECT(store), "store_label-date-key");
	//g_object_set_data(G_OBJECT(store), "store_label-date-key", label_date);	
	update_calendar(GTK_CALENDAR(calendar), GTK_LABEL(label_date));	
	update_store(GTK_CALENDAR(calendar), store);		
}


/**
 * @brief Set marks on calendar
 * @param GtkCalendar
 */
static void set_marks_on_calendar(GtkCalendar *calendar)
{
	//g_print("calling set marks on calendar\n");
	
	GArray* evt_arry_month = db_get_all_events_year_month(db_handle, m_start_year,m_start_month);
    
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
		
		//places a visual marker on day of the current month.
		gtk_calendar_mark_day(GTK_CALENDAR(calendar),start_day);
  	
     }//for
     
	g_array_free(evt_arry_month, FALSE); //clear standard month events
}
 
 /**
 * @brief Go home to today date
 * @param action The GSimpleAction that triggered the callback.
 * @param parameter The GVariant parameter (unused).
 * @param user_data A pointer to the GtkWindow.
 */
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


/**
 * @brief Updates the GListStore with events for the currently selected day.
 * @param calendar The CustomCalendar widget.
 * @param user_data A pointer to the GListStore.
 */
static void update_store(GtkCalendar *calendar, gpointer user_data)
{	
	g_print("update store\n");
	
	GListStore *store = user_data;
	g_list_store_remove_all(G_LIST_STORE(store));
	
	GDateTime *cal_date = gtk_calendar_get_date(GTK_CALENDAR(calendar));
	
	m_start_day = g_date_time_get_day_of_month(cal_date);
	m_start_month =g_date_time_get_month(cal_date);
	m_start_year=g_date_time_get_year(cal_date);
	//g_print("Update_Store: Date is : %d-%d-%d \n", m_start_day, m_start_month,m_start_year);
	
	
	//get all events for selected day
	GArray* events_for_day = db_get_all_events_year_month_day(db_handle, m_start_year, m_start_month, m_start_day);
    
    if (events_for_day) {
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
	time_str_start =get_time_str_display(start_hour,start_min);
	time_str_end =get_time_str_display(end_hour,end_min);
	if(m_show_end_time) display_str = g_strconcat(display_str, time_str_start," to ",time_str_end, " ", summary, "\n",NULL);
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
 * @brief Helper to save current state
 * @param window The GtkWindow.
 */
static void save_current_state(GtkWindow *window) {
    // 1. Find the Paned widget
    GtkWidget *paned = g_object_get_data(G_OBJECT(window), "window-paned-key");
    if (paned && GTK_IS_PANED(paned)) {
        m_paned_position = gtk_paned_get_position(GTK_PANED(paned));
    }

    // 2. Save window dimensions
    gtk_window_get_default_size(window, &m_window_width, &m_window_height);
    
    // 3. Write to file
    config_write();
}

/**
 * @brief Helper to free resources
 */
static void finalize_resources() {
    if (full_audio_buffer) {
        free(full_audio_buffer);
        full_audio_buffer = NULL;
    }
    // free m_config_file, etc.
    g_free(m_config_file);
}


/**
 * @brief Helper to handles the [X] button or Alt+F4
 * @param window The GtkWindow.
 */
static gboolean callbk_window_closed(GtkWindow *window, gpointer user_data) {
    g_print("Window closing. Saving state...\n");
    save_current_state(window);
    finalize_resources(); // Free your audio buffer here
    return FALSE; // Return FALSE to let the window actually close
}

/**
 * @brief Callback function to quit Talk Calendar.
 * @param action The GSimpleAction that triggered the callback.
 * @param parameter The GVariant parameter (unused).
 * @param user_data A pointer to the GtkWidow.
 */
static void callbk_quit(GSimpleAction *action, GVariant *parameter, gpointer user_data) {     
    GtkWindow *window = GTK_WINDOW(user_data);  
    save_current_state(window);
    finalize_resources();
    
    GtkApplication* app = gtk_window_get_application(window); 
    g_application_quit(G_APPLICATION(app)); 
}

/**
 * @brief Helper to create menu
 * @param app The GtkApplication
 */
static GMenu *create_menu(const GtkApplication *app) 
{
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
	 
	 section = g_menu_new ();
	 g_menu_append (section, "Calculate Easter", "app.easter"); 
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
	
	return menu;

}

/**
 * @brief Active the application
 * @param app The GtkApplication
 */
static void activate (GtkApplication *app, gpointer  user_data)
{
	
	GtkWidget *window;
	GtkWidget *label_date;
	GMenu *menu;
	GtkWidget *menu_button;	
	GtkWidget *scrolled_window;
	GtkWidget *paned;	
	GtkWidget *box;	
	GtkWidget *box_listview;
	GtkWidget *box_calendar;	
	GtkListItemFactory *factory;
	GListModel *model;
	GtkSingleSelection *selection;
	GtkWidget *list_view;	
	//header
	GtkWidget *header;
	GtkWidget *button_new_event;
	GtkWidget *button_edit_event;
	GtkWidget *button_delete_selected;
		
	// create a new window, and set its title
	window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (window), "Talk Calendar ");

	gtk_window_set_default_size (GTK_WINDOW (window),m_window_width,m_window_height); 	
	// Change "destroy" to "close-request" which  expects a gboolean return value
	g_signal_connect (window, "close-request", G_CALLBACK (callbk_window_closed), NULL);	
	header = gtk_header_bar_new();
	gtk_window_set_titlebar(GTK_WINDOW(window), header);

	//setup selected date label
	label_date = gtk_label_new("");
	gtk_label_set_xalign(GTK_LABEL(label_date), 0.5);
	
	//Keyboard accelerators	
	const gchar *speak_accels[2] = { "space", NULL };
	const gchar *time_accels[2] = {"t", NULL };
	const gchar *home_accels[2] = { "Home", NULL };
	const gchar *info_accels[2] = {"F1", NULL };		
	const gchar * preferences_accels[2] = { "<Ctrl><Alt>P", NULL };	
		
	m_file_name = g_strdup("talkcalendar.ical"); // the calendar is on the heap and has to be freed on shutdown
	
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
	m_calendar =gtk_calendar_new();	
    g_signal_connect(GTK_CALENDAR(m_calendar), "day-selected", G_CALLBACK(callbk_calendar_day_selected), store);	
	g_signal_connect(GTK_CALENDAR(m_calendar), "next-month", G_CALLBACK(callbk_calendar_next_month), label_date);
	g_signal_connect(GTK_CALENDAR(m_calendar), "prev-month", G_CALLBACK(callbk_calendar_prev_month), label_date);
	g_signal_connect(GTK_CALENDAR(m_calendar), "next-year", G_CALLBACK(callbk_calendar_next_year), label_date);
	g_signal_connect(GTK_CALENDAR(m_calendar), "prev-year", G_CALLBACK(callbk_calendar_prev_year), label_date);
	
	g_object_set_data(G_OBJECT(store), "store_label-date-key", label_date);
	
	GDateTime* cal_date;  
	cal_date = gtk_calendar_get_date(GTK_CALENDAR(m_calendar));
	
	m_start_day = g_date_time_get_day_of_month(cal_date);
	m_start_month =g_date_time_get_month(cal_date);
	m_start_year=g_date_time_get_year(cal_date);
	g_print("Date is : %d-%d-%d \n", m_start_day, m_start_month,m_start_year);		
	update_date_label(GTK_CALENDAR(m_calendar), label_date);	
	
	scrolled_window = gtk_scrolled_window_new();	
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window),list_view);
	   
    gtk_widget_set_hexpand (GTK_WIDGET (list_view), TRUE);
    gtk_widget_set_vexpand (GTK_WIDGET (list_view), TRUE);
    gtk_widget_set_halign(list_view, GTK_ALIGN_FILL); 
	gtk_widget_set_valign(list_view, GTK_ALIGN_FILL);
	
	box_listview =gtk_box_new(GTK_ORIENTATION_VERTICAL,1);	
	gtk_box_append(GTK_BOX(box_listview), scrolled_window); 
	
	box_calendar =gtk_box_new(GTK_ORIENTATION_VERTICAL,1);	
	gtk_box_append(GTK_BOX(box_calendar), label_date);		
	gtk_box_append(GTK_BOX(box_calendar), m_calendar); 
	gtk_widget_set_vexpand (m_calendar, TRUE);
    gtk_widget_set_hexpand (m_calendar, TRUE);
    gtk_widget_set_halign(m_calendar, GTK_ALIGN_FILL); // ensure it fills horizontally
	
	//setup key-value pairs
	g_object_set_data(G_OBJECT(m_calendar), "calendar-window-key",window);
	g_object_set_data(G_OBJECT(store), "store-window-key",window);
	g_object_set_data(G_OBJECT(selection), "selection-window-key",window);
	
	g_object_set_data(G_OBJECT(m_calendar), "calendar-store-key",store);	
	g_object_set_data(G_OBJECT(window), "window-store-key",store);
	
	g_object_set_data(G_OBJECT(selection), "selection-calendar-key",m_calendar);
	g_object_set_data(G_OBJECT(window), "window-calendar-key",m_calendar);
	g_object_set_data(G_OBJECT(window), "window-calendar-key",m_calendar);
	g_object_set_data(G_OBJECT(store), "store-calendar-key",m_calendar);
	
	g_object_set_data(G_OBJECT(window), "window-label-date-key",label_date);	
	
	button_new_event = gtk_button_new_from_icon_name("list-add-symbolic");
	button_edit_event = gtk_button_new_from_icon_name("document-edit-symbolic");
	button_delete_selected = gtk_button_new_from_icon_name("user-trash-symbolic");

	// Set tooltips
	gtk_widget_set_tooltip_text(button_new_event, "New calendar event");
	gtk_widget_set_tooltip_text(button_edit_event, "Edit selected event");
	gtk_widget_set_tooltip_text(button_delete_selected, "Delete selected event");

	// Create the group box and add the "linked" class
	GtkWidget *button_group = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_widget_add_css_class(button_group, "linked");
	// Add 4 pixels of margin to the left of the whole group
	gtk_widget_set_margin_start(button_group, 4); 

	// Append the actual buttons to the box
	gtk_box_append(GTK_BOX(button_group), button_new_event);
	gtk_box_append(GTK_BOX(button_group), button_edit_event);
	gtk_box_append(GTK_BOX(button_group), button_delete_selected);

	// Pack the box into the header bar (only do this ONCE)
	gtk_header_bar_pack_start(GTK_HEADER_BAR(header), button_group);

	// Connect  signals
	g_signal_connect(button_new_event, "clicked", G_CALLBACK(callbk_new_event), store);
	g_signal_connect(button_edit_event, "clicked", G_CALLBACK(callbk_edit_event), selection);
	g_signal_connect(button_delete_selected, "clicked", G_CALLBACK(callbk_delete_event), selection);
	
	//Actions
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
	g_signal_connect(newevent_action, "activate",  G_CALLBACK(callbk_new_event),store);
	
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
	
	//Calendar easter
	GSimpleAction *easter_action;
	easter_action=g_simple_action_new("easter",NULL); //app.easter
	g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(easter_action)); //make visible
	g_signal_connect(easter_action, "activate",  G_CALLBACK(callbk_easter), window);
	
	
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
	    
    menu=create_menu(app);
    menu_button = gtk_menu_button_new();
	gtk_widget_set_tooltip_text(menu_button, "Menu");
	gtk_menu_button_set_icon_name(GTK_MENU_BUTTON(menu_button), "open-menu-symbolic");
	gtk_menu_button_set_menu_model(GTK_MENU_BUTTON(menu_button), G_MENU_MODEL(menu));
	gtk_header_bar_pack_end(GTK_HEADER_BAR(header), menu_button);
		
	// connect keyboard accelerators	
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.speak", speak_accels);		
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.speaktime", time_accels);	
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.home", home_accels);
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.info", info_accels);
	gtk_application_set_accels_for_action(GTK_APPLICATION(app),"app.preferences", preferences_accels);
	
    if(m_talk && m_talk_at_startup) {
		speak_events();		
	}
	
	paned = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
	gtk_paned_set_start_child(GTK_PANED(paned), box_calendar);
	gtk_paned_set_end_child(GTK_PANED(paned), box_listview); 

	// Use the loaded config value!
	gtk_paned_set_position(GTK_PANED(paned), m_paned_position);

	// Store a pointer to the paned widget in the window 
	// so callbk_quit can find it later to save the position.
	g_object_set_data(G_OBJECT(window), "window-paned-key", paned);

	gtk_window_set_child(GTK_WINDOW(window), paned);
		
	set_marks_on_calendar(GTK_CALENDAR(m_calendar));	
	update_date_label(GTK_CALENDAR(m_calendar), label_date);	
	update_store(GTK_CALENDAR(m_calendar), store);
	gtk_window_present(GTK_WINDOW (window));	
}

/**
 * @brief main function defines applcation name "org.gtk.talkcalendar"
 * @param argc
 * @param argv
 */
int main (int  argc, char **argv)
{
	GtkApplication *app;
	int status;	
	config_initialize();	
	db_handle = db_open("talkcalendar.db");
    if (!db_handle) {
        g_critical("Failed to open database.");
        return 1;
    }    
    // Allocate MAX_SPEAK_SECONDS seconds worth of samples
    full_audio_buffer = malloc(SAMPLE_RATE * MAX_SPEAK_SECONDS * sizeof(int16_t));
	app = gtk_application_new ("org.gtk.talkcalendar", G_APPLICATION_DEFAULT_FLAGS);
	
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);
	return status;
}
