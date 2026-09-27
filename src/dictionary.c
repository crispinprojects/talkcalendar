/* dictionary.c
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
#include "dictionary.h"
#include "voice3.h"

//Word dictionary

void get_words_array(GList *speak_word_list, int word_number, unsigned char **word_arrays, unsigned int *word_arrays_sizes)
{
	gpointer word_list_pointer;
	gchar* word_str;
	
	for(int i = 0; i < word_number; i++)
	{
	word_list_pointer = g_list_nth_data(speak_word_list, i);
	word_str = (gchar *)word_list_pointer;
	
	// Convert to lowercase to check matches safely
	gchar* word_str_lower = g_ascii_strdown(word_str, -1);
	
	// Default assignment to static global resource fallback, NO malloc needed!
	word_arrays[i] = (unsigned char*)empty_raw;
	word_arrays_sizes[i] = empty_raw_len; 
	
	if (g_strcmp0(word_str_lower, "monday") == 0) {        
	word_arrays[i] = (unsigned char*)monday_raw;        
	word_arrays_sizes[i] = monday_raw_len;
	} 
	else if (g_strcmp0(word_str_lower, "tuesday") == 0) {
	word_arrays[i] = (unsigned char*)tuesday_raw;
	word_arrays_sizes[i] = tuesday_raw_len; 
	}
	else if (g_strcmp0(word_str_lower, "wednesday") == 0) {
	word_arrays[i] = (unsigned char*)wednesday_raw;
	word_arrays_sizes[i] = wednesday_raw_len; 
	}
	else if (g_strcmp0(word_str_lower, "thursday") == 0) {
	word_arrays[i] = (unsigned char*)thursday_raw;
	word_arrays_sizes[i] = thursday_raw_len; 
	}
	else if (g_strcmp0(word_str_lower, "friday") == 0) {
	word_arrays[i] = (unsigned char*)friday_raw;
	word_arrays_sizes[i] = friday_raw_len; 
	}
	else if (g_strcmp0(word_str_lower, "saturday") == 0) {
	word_arrays[i] = (unsigned char*)saturday_raw;
	word_arrays_sizes[i] = saturday_raw_len; 
	}
	else if (g_strcmp0(word_str_lower, "sunday") == 0) {
	word_arrays[i] = (unsigned char*)sunday_raw;
	word_arrays_sizes[i] = sunday_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "first") == 0) {
	word_arrays[i] = (unsigned char*)first_raw;
	word_arrays_sizes[i] = first_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "second") == 0) {
	word_arrays[i] = (unsigned char*)second_raw;
	word_arrays_sizes[i] = second_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "third") == 0) {
	word_arrays[i] = (unsigned char*)third_raw;
	word_arrays_sizes[i] = third_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "fourth") == 0) {
	word_arrays[i] = (unsigned char*)fourth_raw;
	word_arrays_sizes[i] = fourth_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "fifth") == 0) {
	word_arrays[i] = (unsigned char*)fifth_raw;
	word_arrays_sizes[i] = fifth_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "sixth") == 0) {
	word_arrays[i] = (unsigned char*)sixth_raw;
	word_arrays_sizes[i] = sixth_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "seventh") == 0) {
	word_arrays[i] = (unsigned char*)seventh_raw;
	word_arrays_sizes[i] = seventh_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "eighth") == 0) {
	word_arrays[i] = (unsigned char*)eighth_raw;
	word_arrays_sizes[i] = eighth_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "ninth") == 0) {
	word_arrays[i] = (unsigned char*)ninth_raw;
	word_arrays_sizes[i] = ninth_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "tenth") == 0) {
	word_arrays[i] = (unsigned char*)tenth_raw;
	word_arrays_sizes[i] = tenth_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "eleventh") == 0) {
	word_arrays[i] = (unsigned char*)eleventh_raw;
	word_arrays_sizes[i] = eleventh_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "twelfth") == 0) {
	word_arrays[i] = (unsigned char*)twelfth_raw;
	word_arrays_sizes[i] = twelfth_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "thirteenth") == 0) {
	word_arrays[i] = (unsigned char*)thirteenth_raw;
	word_arrays_sizes[i] = thirteenth_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "fourteenth") == 0) {
	word_arrays[i] = (unsigned char*)fourteenth_raw;
	word_arrays_sizes[i] = fourteenth_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "fifteenth") == 0) {
	word_arrays[i] = (unsigned char*)fifteenth_raw;
	word_arrays_sizes[i] = fifteenth_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "sixteenth") == 0) {
	word_arrays[i] = (unsigned char*)sixteenth_raw;
	word_arrays_sizes[i] = sixteenth_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "seventeenth") == 0) {
	word_arrays[i] = (unsigned char*)seventeenth_raw;
	word_arrays_sizes[i] = seventeenth_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "eighteenth") == 0) {
	word_arrays[i] = (unsigned char*)eighteenth_raw;
	word_arrays_sizes[i] = eighteenth_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "nineteenth") == 0) {
	word_arrays[i] = (unsigned char*)nineteenth_raw;
	word_arrays_sizes[i] = nineteenth_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "twentieth") == 0) {
	word_arrays[i] = (unsigned char*)twentieth_raw;
	word_arrays_sizes[i] = twentieth_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "thirtieth") == 0) {
	word_arrays[i] = (unsigned char*)thirtieth_raw;
	word_arrays_sizes[i] = thirtieth_raw_len;
	} 
	else if (g_strcmp0(word_str_lower, "january") == 0) {
	word_arrays[i] = (unsigned char*)january_raw;
	word_arrays_sizes[i] = january_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "february") == 0) {
	word_arrays[i] = (unsigned char*)february_raw;
	word_arrays_sizes[i] = february_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "march") == 0) {
	word_arrays[i] = (unsigned char*)march_raw;
	word_arrays_sizes[i] = march_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "april") == 0) {
	word_arrays[i] = (unsigned char*)april_raw;
	word_arrays_sizes[i] = april_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "may") == 0) {
	word_arrays[i] = (unsigned char*)may_raw;
	word_arrays_sizes[i] = may_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "june") == 0) {
	word_arrays[i] = (unsigned char*)june_raw;
	word_arrays_sizes[i] = june_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "july") == 0) {
	word_arrays[i] = (unsigned char*)july_raw;
	word_arrays_sizes[i] = july_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "august") == 0) {
	word_arrays[i] = (unsigned char*)august_raw;
	word_arrays_sizes[i] = august_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "september") == 0) {
	word_arrays[i] = (unsigned char*)september_raw;
	word_arrays_sizes[i] = september_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "october") == 0) {
	word_arrays[i] = (unsigned char*)october_raw;
	word_arrays_sizes[i] = october_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "november") == 0) {
	word_arrays[i] = (unsigned char*)november_raw;
	word_arrays_sizes[i] = november_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "december") == 0) {
	word_arrays[i] = (unsigned char*)december_raw;
	word_arrays_sizes[i] = december_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "one") == 0) {
	word_arrays[i] = (unsigned char*)one_raw;
	word_arrays_sizes[i] = one_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "two") == 0) {
	word_arrays[i] = (unsigned char*)two_raw;
	word_arrays_sizes[i] = two_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "three") == 0) {
	word_arrays[i] = (unsigned char*)three_raw;
	word_arrays_sizes[i] = three_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "four") == 0) {
	word_arrays[i] = (unsigned char*)four_raw;
	word_arrays_sizes[i] = four_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "five") == 0) {
	word_arrays[i] = (unsigned char*)five_raw;
	word_arrays_sizes[i] = five_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "six") == 0) {
	word_arrays[i] = (unsigned char*)six_raw;
	word_arrays_sizes[i] = six_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "seven") == 0) {
	word_arrays[i] = (unsigned char*)seven_raw;
	word_arrays_sizes[i] = seven_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "eight") == 0) {
	word_arrays[i] = (unsigned char*)eight_raw;
	word_arrays_sizes[i] = eight_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "nine") == 0) {
	word_arrays[i] = (unsigned char*)nine_raw;
	word_arrays_sizes[i] = nine_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "ten") == 0) {
	word_arrays[i] = (unsigned char*)ten_raw;
	word_arrays_sizes[i] = ten_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "eleven") == 0) {
	word_arrays[i] = (unsigned char*)eleven_raw;
	word_arrays_sizes[i] = eleven_raw_len;
	}   
	
	if (g_strcmp0(word_str_lower, "twelve") == 0) {
	word_arrays[i] = (unsigned char*)twelfth_raw; // fix pointer mapping target
	word_arrays_sizes[i] = twelfth_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "thirteen") == 0) {
	word_arrays[i] = (unsigned char*)thirteen_raw;
	word_arrays_sizes[i] = thirteen_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "fourteen") == 0) {
	word_arrays[i] = (unsigned char*)fourteen_raw;
	word_arrays_sizes[i] = fourteen_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "fifteen") == 0) {
	word_arrays[i] = (unsigned char*)fifteen_raw;
	word_arrays_sizes[i] = fifteen_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "sixteen") == 0) {
	word_arrays[i] = (unsigned char*)sixteen_raw;
	word_arrays_sizes[i] = sixteen_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "seventeen") == 0) {
	word_arrays[i] = (unsigned char*)seventeen_raw;
	word_arrays_sizes[i] = seventeen_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "eighteen") == 0) {
	word_arrays[i] = (unsigned char*)eighteen_raw;
	word_arrays_sizes[i] = eighteen_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "nineteen") == 0) {
	word_arrays[i] = (unsigned char*)nineteen_raw;
	word_arrays_sizes[i] = nineteen_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "twenty") == 0) {
	word_arrays[i] = (unsigned char*)twenty_raw;
	word_arrays_sizes[i] = twenty_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "thirty") == 0) {
	word_arrays[i] = (unsigned char*)thirty_raw;
	word_arrays_sizes[i] = thirty_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "forty") == 0) {
	word_arrays[i] = (unsigned char*)forty_raw;
	word_arrays_sizes[i] = forty_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "fifty") == 0) {
	word_arrays[i] = (unsigned char*)fifty_raw;
	word_arrays_sizes[i] = fifty_raw_len;
	} 
	else if (g_strcmp0(word_str_lower, "all") == 0) {
	word_arrays[i] = (unsigned char*)all_raw;
	word_arrays_sizes[i] = all_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "am") == 0) {
	word_arrays[i] = (unsigned char*)am_raw;
	word_arrays_sizes[i] = am_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "activity") == 0) {
	word_arrays[i] = (unsigned char*)activity_raw;
	word_arrays_sizes[i] = activity_raw_len;
	} 
	else if (g_strcmp0(word_str_lower, "and") == 0) {
	word_arrays[i] = (unsigned char*)and_raw;
	word_arrays_sizes[i] = and_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "alert") == 0) {
	word_arrays[i] = (unsigned char*)alert_raw;
	word_arrays_sizes[i] = alert_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "anniversary") == 0) {
	word_arrays[i] = (unsigned char*)anniversary_raw;
	word_arrays_sizes[i] = anniversary_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "appointment") == 0) {
	word_arrays[i] = (unsigned char*)appointment_raw;
	word_arrays_sizes[i] = appointment_raw_len;
	} 
	else if (g_strcmp0(word_str_lower, "bank") == 0) {
	word_arrays[i] = (unsigned char*)bank_raw;
	word_arrays_sizes[i] = bank_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "birthday") == 0) {
	word_arrays[i] = (unsigned char*)birthday_raw;
	word_arrays_sizes[i] = birthday_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "boxing") == 0) {
	word_arrays[i] = (unsigned char*)boxing_raw;
	word_arrays_sizes[i] = boxing_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "cafe") == 0) {
	word_arrays[i] = (unsigned char*)cafe_raw;
	word_arrays_sizes[i] = cafe_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "calendar") == 0) {
	word_arrays[i] = (unsigned char*)calendar_raw;
	word_arrays_sizes[i] = calendar_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "car") == 0) {
	word_arrays[i] = (unsigned char*)car_raw;
	word_arrays_sizes[i] = car_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "christmas") == 0) {
	word_arrays[i] = (unsigned char*)christmas_raw;
	word_arrays_sizes[i] = christmas_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "day") == 0) {
	word_arrays[i] = (unsigned char*)day_raw;
	word_arrays_sizes[i] = day_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "delivery") == 0) {
	word_arrays[i] = (unsigned char*)delivery_raw;
	word_arrays_sizes[i] = delivery_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "dentist") == 0) {
	word_arrays[i] = (unsigned char*)dentist_raw;
	word_arrays_sizes[i] = dentist_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "doctor") == 0) {
	word_arrays[i] = (unsigned char*)doctor_raw;
	word_arrays_sizes[i] = doctor_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "driver") == 0) {
	word_arrays[i] = (unsigned char*)driver_raw;
	word_arrays_sizes[i] = driver_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "easter") == 0) {
	word_arrays[i] = (unsigned char*)easter_raw;
	word_arrays_sizes[i] = easter_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "event") == 0) {
	word_arrays[i] = (unsigned char*)event_raw;
	word_arrays_sizes[i] = event_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "events") == 0) {
	word_arrays[i] = (unsigned char*)events_raw;
	word_arrays_sizes[i] = events_raw_len;
	}	
	else if (g_strcmp0(word_str_lower, "family") == 0) {
	word_arrays[i] = (unsigned char*)family_raw;
	word_arrays_sizes[i] = family_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "fathers") == 0) {
	word_arrays[i] = (unsigned char*)fathers_raw;
	word_arrays_sizes[i] = fathers_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "funeral") == 0) {
	word_arrays[i] = (unsigned char*)funeral_raw;
	word_arrays_sizes[i] = funeral_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "have") == 0) {
	word_arrays[i] = (unsigned char*)have_raw;
	word_arrays_sizes[i] = have_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "high") == 0) {
	word_arrays[i] = (unsigned char*)high_raw;
	word_arrays_sizes[i] = high_raw_len;
	} 
	else if (g_strcmp0(word_str_lower, "holiday") == 0) {
	word_arrays[i] = (unsigned char*)holiday_raw;
	word_arrays_sizes[i] = holiday_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "hospital") == 0) {
	word_arrays[i] = (unsigned char*)hospital_raw;
	word_arrays_sizes[i] = hospital_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "is") == 0) {
	word_arrays[i] = (unsigned char*)is_raw;
	word_arrays_sizes[i] = is_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "medical") == 0) {
	word_arrays[i] = (unsigned char*)medical_raw;
	word_arrays_sizes[i] = medical_raw_len;
	} 
	else if (g_strcmp0(word_str_lower, "meeting") == 0) {
	word_arrays[i] = (unsigned char*)meeting_raw;
	word_arrays_sizes[i] = meeting_raw_len;
	} 
	else if (g_strcmp0(word_str_lower, "meetup") == 0) {
	word_arrays[i] = (unsigned char*)meetup_raw;
	word_arrays_sizes[i] = meetup_raw_len;
	} 
	else if (g_strcmp0(word_str_lower, "memo") == 0) {
	word_arrays[i] = (unsigned char*)memo_raw;
	word_arrays_sizes[i] = memo_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "mothers") == 0) {
	word_arrays[i] = (unsigned char*)mothers_raw;
	word_arrays_sizes[i] = mothers_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "new") == 0) {
	word_arrays[i] = (unsigned char*)new_raw;
	word_arrays_sizes[i] = new_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "no") == 0) {
	word_arrays[i] = (unsigned char*)no_raw;
	word_arrays_sizes[i] = no_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "o") == 0) {
	word_arrays[i] = (unsigned char*)o_raw;
	word_arrays_sizes[i] = o_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "party") == 0) {
	word_arrays[i] = (unsigned char*)party_raw;
	word_arrays_sizes[i] = party_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "payment") == 0) {
	word_arrays[i] = (unsigned char*)payment_raw;
	word_arrays_sizes[i] = payment_raw_len;
	} 
	else if (g_strcmp0(word_str_lower, "pm") == 0) {
	word_arrays[i] = (unsigned char*)pm_raw;
	word_arrays_sizes[i] = pm_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "priority") == 0) {
	word_arrays[i] = (unsigned char*)priority_raw;
	word_arrays_sizes[i] = priority_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "project") == 0) {
	word_arrays[i] = (unsigned char*)project_raw;
	word_arrays_sizes[i] = project_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "reminder") == 0) {
	word_arrays[i] = (unsigned char*)reminder_raw;
	word_arrays_sizes[i] = reminder_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "restaurant") == 0) {
	word_arrays[i] = (unsigned char*)restaurant_raw;
	word_arrays_sizes[i] = restaurant_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "space") == 0) {
	word_arrays[i] = (unsigned char*)empty_raw;
	word_arrays_sizes[i] = empty_raw_len; 
	}
	else if (g_strcmp0(word_str_lower, "sport") == 0) {
	word_arrays[i] = (unsigned char*)sport_raw;
	word_arrays_sizes[i] = sport_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "spring") == 0) {
	word_arrays[i] = (unsigned char*)spring_raw;
	word_arrays_sizes[i] = spring_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "talk") == 0) {
	word_arrays[i] = (unsigned char*)talk_raw;
	word_arrays_sizes[i] = talk_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "task") == 0) {
	word_arrays[i] = (unsigned char*)task_raw;
	word_arrays_sizes[i] = task_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "television") == 0) {
	word_arrays[i] = (unsigned char*)television_raw;
	word_arrays_sizes[i] = television_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "the") == 0) {
	word_arrays[i] = (unsigned char*)the_raw;
	word_arrays_sizes[i] = the_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "theatre") == 0) {
	word_arrays[i] = (unsigned char*)theatre_raw;
	word_arrays_sizes[i] = theatre_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "time") == 0) {
	word_arrays[i] = (unsigned char*)time_raw;
	word_arrays_sizes[i] = time_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "today") == 0) {
	word_arrays[i] = (unsigned char*)today_raw;
	word_arrays_sizes[i] = today_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "travel") == 0) {
	word_arrays[i] = (unsigned char*)travel_raw;
	word_arrays_sizes[i] = travel_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "upcoming") == 0) {
	word_arrays[i] = (unsigned char*)upcoming_raw;
	word_arrays_sizes[i] = upcoming_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "visit") == 0) {
	word_arrays[i] = (unsigned char*)visit_raw;
	word_arrays_sizes[i] = visit_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "walk") == 0) {
	word_arrays[i] = (unsigned char*)walk_raw;
	word_arrays_sizes[i] = walk_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "work") == 0) {
	word_arrays[i] = (unsigned char*)work_raw;
	word_arrays_sizes[i] = work_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "year") == 0) {
	word_arrays[i] = (unsigned char*)year_raw;
	word_arrays_sizes[i] = year_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "you") == 0) {
	word_arrays[i] = (unsigned char*)you_raw;
	word_arrays_sizes[i] = you_raw_len;
	}
	else if (g_strcmp0(word_str_lower, "zero") == 0) {
	word_arrays[i] = (unsigned char*)zero_raw;
	word_arrays_sizes[i] = zero_raw_len;
	}
	
	//  Clean up the temporary lower-cased conversion string
	g_free(word_str_lower);																												
	
	}//for

} //get word arrays
