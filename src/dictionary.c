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
#include <gtk/gtk.h> 
#include "dictionary.h"
#include "voice3.h"

//Word dictionary

void get_words_array(GList *speak_word_list, int word_number,unsigned char **word_arrays, unsigned int *word_arrays_sizes)
{
		
	gpointer word_list_pointer;
	gchar* word_str;
	gchar* word_str_lower;	
	
	//words
	for(int i=0; i < word_number; i++)
	{
		word_list_pointer=g_list_nth_data(speak_word_list,i);
		word_str=(gchar *)word_list_pointer;
		gchar* word_str_lower= g_ascii_strdown(word_str,-1);	//make sure lower			
		
		//add empty for any word not found		
		word_arrays[i] = (unsigned char*)malloc(empty_raw_len * sizeof(unsigned char));
		word_arrays[i] =  empty_raw;		
		word_arrays_sizes[i]=empty_raw_len; 
				
		if (g_strcmp0(word_str_lower,"monday")==0) {		
		word_arrays[i] = (unsigned char*)malloc(monday_raw_len * sizeof(unsigned char));
		word_arrays[i] = monday_raw;		
		word_arrays_sizes[i]=monday_raw_len;
	    } 
	    	    
		if (g_strcmp0(word_str_lower,"tuesday")==0) {			
		word_arrays[i] = (unsigned char*)malloc(tuesday_raw_len * sizeof(unsigned char));
		word_arrays[i] = tuesday_raw;
		word_arrays_sizes[i]=tuesday_raw_len; 	
	    }
	    
		if (g_strcmp0(word_str_lower,"wednesday")==0) {		
		word_arrays[i] = (unsigned char*)malloc(wednesday_raw_len * sizeof(unsigned char));
		word_arrays[i] = wednesday_raw;
		word_arrays_sizes[i]=wednesday_raw_len; 
	    }
		if (g_strcmp0(word_str_lower,"thursday")==0) {	
		word_arrays[i] = (unsigned char*)malloc(thursday_raw_len * sizeof(unsigned char));
		word_arrays[i] = thursday_raw;
		word_arrays_sizes[i]=thursday_raw_len; 
	    }
	    if (g_strcmp0(word_str_lower,"friday")==0) {	
		word_arrays[i] = (unsigned char*)malloc(friday_raw_len * sizeof(unsigned char));
		word_arrays[i] = friday_raw;
		word_arrays_sizes[i]=friday_raw_len;  
	    }
		if (g_strcmp0(word_str_lower,"saturday")==0) {		
		word_arrays[i] = (unsigned char*)malloc(saturday_raw_len * sizeof(unsigned char));
		word_arrays[i] = saturday_raw;
		word_arrays_sizes[i]=saturday_raw_len; 
	    }
	    if (g_strcmp0(word_str_lower,"sunday")==0) {		
		word_arrays[i] = (unsigned char*)malloc(sunday_raw_len * sizeof(unsigned char));
		word_arrays[i] = sunday_raw;
		word_arrays_sizes[i]=sunday_raw_len;
	    }
	    
	    if (g_strcmp0(word_str_lower,"first")==0) {		
		word_arrays[i] = (unsigned char*)malloc(first_raw_len * sizeof(unsigned char));
		word_arrays[i] = first_raw;
		word_arrays_sizes[i]=first_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"second")==0) {		
		word_arrays[i] = (unsigned char*)malloc(second_raw_len * sizeof(unsigned char));
		word_arrays[i] = second_raw;
		word_arrays_sizes[i]=second_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"third")==0) {		
		word_arrays[i] = (unsigned char*)malloc(third_raw_len * sizeof(unsigned char));
		word_arrays[i] = third_raw;
		word_arrays_sizes[i]=third_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"fourth")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fourth_raw_len * sizeof(unsigned char));
		word_arrays[i] = fourth_raw;
		word_arrays_sizes[i]=fourth_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"fifth")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fifth_raw_len * sizeof(unsigned char));
		word_arrays[i] = fifth_raw;
		word_arrays_sizes[i]=fifth_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"sixth")==0) {		
		word_arrays[i] = (unsigned char*)malloc(sixth_raw_len * sizeof(unsigned char));
		word_arrays[i] = sixth_raw;
		word_arrays_sizes[i]=sixth_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"seventh")==0) {		
		word_arrays[i] = (unsigned char*)malloc(seventh_raw_len * sizeof(unsigned char));
		word_arrays[i] = seventh_raw;
		word_arrays_sizes[i]=seventh_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"eighth")==0) {		
		word_arrays[i] = (unsigned char*)malloc(eighth_raw_len * sizeof(unsigned char));
		word_arrays[i] = eighth_raw;
		word_arrays_sizes[i]=eighth_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"ninth")==0) {		
		word_arrays[i] = (unsigned char*)malloc(ninth_raw_len * sizeof(unsigned char));
		word_arrays[i] = ninth_raw;
		word_arrays_sizes[i]=ninth_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"tenth")==0) {		
		word_arrays[i] = (unsigned char*)malloc(tenth_raw_len * sizeof(unsigned char));
		word_arrays[i] = tenth_raw;
		word_arrays_sizes[i]=tenth_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"eleventh")==0) {		
		word_arrays[i] = (unsigned char*)malloc(eleventh_raw_len * sizeof(unsigned char));
		word_arrays[i] = eleventh_raw;
		word_arrays_sizes[i]=eleventh_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"twelfth")==0) {		
		word_arrays[i] = (unsigned char*)malloc(twelfth_raw_len * sizeof(unsigned char));
		word_arrays[i] = twelfth_raw;
		word_arrays_sizes[i]=twelfth_raw_len;	
	    }
		if (g_strcmp0(word_str_lower,"thirteenth")==0) {		
		word_arrays[i] = (unsigned char*)malloc(thirteenth_raw_len * sizeof(unsigned char));
		word_arrays[i] = thirteenth_raw;;
		word_arrays_sizes[i]=thirteenth_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"fourteenth")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fourteenth_raw_len * sizeof(unsigned char));
		word_arrays[i] = fourteenth_raw;
		word_arrays_sizes[i]=fourteenth_raw_len;	
	    }		
		if (g_strcmp0(word_str_lower,"fifteenth")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fifteenth_raw_len * sizeof(unsigned char));
		word_arrays[i] = fifteenth_raw;;
		word_arrays_sizes[i]=fifteenth_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"sixteenth")==0) {		
		word_arrays[i] = (unsigned char*)malloc(sixteenth_raw_len * sizeof(unsigned char));
		word_arrays[i] = sixteenth_raw;
		word_arrays_sizes[i]=sixteenth_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"seventeenth")==0) {		
		word_arrays[i] = (unsigned char*)malloc(seventeenth_raw_len * sizeof(unsigned char));
		word_arrays[i] = seventeenth_raw;
		word_arrays_sizes[i]=seventeenth_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"eighteenth")==0) {		
		word_arrays[i] = (unsigned char*)malloc(eighteenth_raw_len * sizeof(unsigned char));
		word_arrays[i] = eighteenth_raw;
		word_arrays_sizes[i]=eighteenth_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"nineteenth")==0) {		
		word_arrays[i] = (unsigned char*)malloc(nineteenth_raw_len * sizeof(unsigned char));
		word_arrays[i] = nineteenth_raw;
		word_arrays_sizes[i]=nineteenth_raw_len;	
	    }						
		if (g_strcmp0(word_str_lower,"twentieth")==0) {		
		word_arrays[i] = (unsigned char*)malloc(twentieth_raw_len * sizeof(unsigned char));
		word_arrays[i] = twentieth_raw;
		word_arrays_sizes[i]=twentieth_raw_len;	
	    }
	  
	    if (g_strcmp0(word_str_lower,"thirtieth")==0) {	
		word_arrays[i] = (unsigned char*)malloc(thirtieth_raw_len * sizeof(unsigned char));
		word_arrays[i] = thirtieth_raw;
		word_arrays_sizes[i]=thirtieth_raw_len;	
	    }
	   					
		
		if (g_strcmp0(word_str_lower,"january")==0) {		
		word_arrays[i] = (unsigned char*)malloc(january_raw_len * sizeof(unsigned char));
		word_arrays[i] = january_raw;
		word_arrays_sizes[i]=january_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"february")==0) {		
		word_arrays[i] = (unsigned char*)malloc(february_raw_len * sizeof(unsigned char));
		word_arrays[i] = february_raw;
		word_arrays_sizes[i]=february_raw_len;	
	    }		
		if (g_strcmp0(word_str_lower,"march")==0) {		
		word_arrays[i] = (unsigned char*)malloc(march_raw_len * sizeof(unsigned char));
		word_arrays[i] = march_raw;
		word_arrays_sizes[i]=march_raw_len;	
	    }	
		if (g_strcmp0(word_str_lower,"april")==0) {		
		word_arrays[i] = (unsigned char*)malloc(april_raw_len * sizeof(unsigned char));
		word_arrays[i] = april_raw;
		word_arrays_sizes[i]=april_raw_len;	
	    }	
		if (g_strcmp0(word_str_lower,"may")==0) {		
		word_arrays[i] = (unsigned char*)malloc(may_raw_len * sizeof(unsigned char));
		word_arrays[i] = may_raw;
		word_arrays_sizes[i]=may_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"june")==0) {		
		word_arrays[i] = (unsigned char*)malloc(june_raw_len * sizeof(unsigned char));
		word_arrays[i] = june_raw;
		word_arrays_sizes[i]=june_raw_len;	
	    }		
		if (g_strcmp0(word_str_lower,"july")==0) {		
		word_arrays[i] = (unsigned char*)malloc(july_raw_len * sizeof(unsigned char));
		word_arrays[i] = july_raw;
		word_arrays_sizes[i]=july_raw_len;	
	    }	
		if (g_strcmp0(word_str_lower,"august")==0) {		
		word_arrays[i] = (unsigned char*)malloc(august_raw_len * sizeof(unsigned char));
		word_arrays[i] = august_raw;
		word_arrays_sizes[i]=august_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"september")==0) {		
		word_arrays[i] = (unsigned char*)malloc(september_raw_len * sizeof(unsigned char));
		word_arrays[i] = september_raw;
		word_arrays_sizes[i]=september_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"october")==0) {		
		word_arrays[i] = (unsigned char*)malloc(october_raw_len * sizeof(unsigned char));
		word_arrays[i] = october_raw;
		word_arrays_sizes[i]=october_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"november")==0) {		
		word_arrays[i] = (unsigned char*)malloc(november_raw_len * sizeof(unsigned char));
		word_arrays[i] = november_raw;
		word_arrays_sizes[i]=november_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"december")==0) {		
		word_arrays[i] = (unsigned char*)malloc(december_raw_len * sizeof(unsigned char));
		word_arrays[i] = december_raw;
		word_arrays_sizes[i]=december_raw_len;	
	    }					
		
	    //cardinals
	    if (g_strcmp0(word_str_lower,"one")==0) {		
		word_arrays[i] = (unsigned char*)malloc(one_raw_len * sizeof(unsigned char));
		word_arrays[i] = one_raw;
		word_arrays_sizes[i]=one_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"two")==0) {		
		word_arrays[i] = (unsigned char*)malloc(two_raw_len * sizeof(unsigned char));
		word_arrays[i] = two_raw;
		word_arrays_sizes[i]=two_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"three")==0) {		
		word_arrays[i] = (unsigned char*)malloc(three_raw_len * sizeof(unsigned char));
		word_arrays[i] = three_raw;
		word_arrays_sizes[i]=three_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"four")==0) {		
		word_arrays[i] = (unsigned char*)malloc(four_raw_len * sizeof(unsigned char));
		word_arrays[i] = four_raw;
		word_arrays_sizes[i]=four_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"five")==0) {		
		word_arrays[i] = (unsigned char*)malloc(five_raw_len * sizeof(unsigned char));
		word_arrays[i] = five_raw;
		word_arrays_sizes[i]=five_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"six")==0) {		
		word_arrays[i] = (unsigned char*)malloc(six_raw_len * sizeof(unsigned char));
		word_arrays[i] = six_raw;
		word_arrays_sizes[i]=six_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"seven")==0) {		
		word_arrays[i] = (unsigned char*)malloc(seven_raw_len * sizeof(unsigned char));
		word_arrays[i] = seven_raw;
		word_arrays_sizes[i]=seven_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"eight")==0) {		
		word_arrays[i] = (unsigned char*)malloc(eight_raw_len * sizeof(unsigned char));
		word_arrays[i] = eight_raw;
		word_arrays_sizes[i]=eight_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"nine")==0) {		
		word_arrays[i] = (unsigned char*)malloc(nine_raw_len * sizeof(unsigned char));
		word_arrays[i] = nine_raw;
		word_arrays_sizes[i]=nine_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"ten")==0) {		
		word_arrays[i] = (unsigned char*)malloc(ten_raw_len * sizeof(unsigned char));
		word_arrays[i] = ten_raw;
		word_arrays_sizes[i]=ten_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"eleven")==0) {		
		word_arrays[i] = (unsigned char*)malloc(eleven_raw_len * sizeof(unsigned char));
		word_arrays[i] = eleven_raw;
		word_arrays_sizes[i]=eleven_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"twelve")==0) {
		word_arrays[i] = (unsigned char*)malloc(twelve_raw_len * sizeof(unsigned char));
		word_arrays[i] = twelve_raw;
		word_arrays_sizes[i]=twelve_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"thirteen")==0) {		
		word_arrays[i] = (unsigned char*)malloc(thirteen_raw_len * sizeof(unsigned char));
		word_arrays[i] = thirteen_raw;
		word_arrays_sizes[i]=thirteen_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"fourteen")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fourteen_raw_len * sizeof(unsigned char));
		word_arrays[i] = fourteen_raw;
		word_arrays_sizes[i]=fourteen_raw_len;
	    }	
	     if (g_strcmp0(word_str_lower,"fifteen")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fifteen_raw_len * sizeof(unsigned char));
		word_arrays[i] = fifteen_raw;
		word_arrays_sizes[i]=fifteen_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"sixteen")==0) {		
		word_arrays[i] = (unsigned char*)malloc(sixteen_raw_len * sizeof(unsigned char));
		word_arrays[i] = sixteen_raw;
		word_arrays_sizes[i]=sixteen_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"seventeen")==0) {		
		word_arrays[i] = (unsigned char*)malloc(seventeen_raw_len * sizeof(unsigned char));
		word_arrays[i] = seventeen_raw;
		word_arrays_sizes[i]=seventeen_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"eighteen")==0) {		
		word_arrays[i] = (unsigned char*)malloc(eighteen_raw_len * sizeof(unsigned char));
		word_arrays[i] = eighteen_raw;
		word_arrays_sizes[i]=eighteen_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"nineteen")==0) {		
		word_arrays[i] = (unsigned char*)malloc(nineteen_raw_len * sizeof(unsigned char));
		word_arrays[i] = nineteen_raw;
		word_arrays_sizes[i]=nineteen_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"twenty")==0) {		
		word_arrays[i] = (unsigned char*)malloc(twenty_raw_len * sizeof(unsigned char));
		word_arrays[i] = twenty_raw;
		word_arrays_sizes[i]=twenty_raw_len;
	    }
	   
	     if (g_strcmp0(word_str_lower,"thirty")==0) {		
		word_arrays[i] = (unsigned char*)malloc(thirty_raw_len * sizeof(unsigned char));
		word_arrays[i] = thirty_raw;
		word_arrays_sizes[i]=thirty_raw_len;
	    }
	    
	   
	     if (g_strcmp0(word_str_lower,"forty")==0) {		
		word_arrays[i] = (unsigned char*)malloc(forty_raw_len * sizeof(unsigned char));
		word_arrays[i] = forty_raw;
		word_arrays_sizes[i]=forty_raw_len;
	    }
	     
	     if (g_strcmp0(word_str_lower,"fifty")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fifty_raw_len * sizeof(unsigned char));
		word_arrays[i] = fifty_raw;
		word_arrays_sizes[i]=fifty_raw_len;
	    }																																																																																																
	    	    
	    //words
	     //A words   
	    if (g_strcmp0(word_str_lower,"all")==0) {		
		word_arrays[i] = (unsigned char*)malloc(all_raw_len * sizeof(unsigned char));
		word_arrays[i] = all_raw;
		word_arrays_sizes[i]=all_raw_len;
	    }
	    if (g_strcmp0(word_str_lower,"am")==0) {		
		word_arrays[i] = (unsigned char*)malloc(am_raw_len * sizeof(unsigned char));
		word_arrays[i] = am_raw;
		word_arrays_sizes[i]=am_raw_len;
	    }
	    if (g_strcmp0(word_str_lower,"activity")==0) {		
		word_arrays[i] = (unsigned char*)malloc(activity_raw_len * sizeof(unsigned char));
		word_arrays[i] = activity_raw;
		word_arrays_sizes[i]=activity_raw_len;	
	    }	    
	    if (g_strcmp0(word_str_lower,"and")==0) {		
		word_arrays[i] = (unsigned char*)malloc(and_raw_len * sizeof(unsigned char));
		word_arrays[i] = and_raw;
		word_arrays_sizes[i]=and_raw_len;	
	    }	
	    if (g_strcmp0(word_str_lower,"anniversary")==0) {		
		word_arrays[i] = (unsigned char*)malloc(anniversary_raw_len * sizeof(unsigned char));
		word_arrays[i] = anniversary_raw;
		word_arrays_sizes[i]=anniversary_raw_len;	
	    }		
	    if (g_strcmp0(word_str_lower,"appointment")==0) {		
		word_arrays[i] = (unsigned char*)malloc(appointment_raw_len * sizeof(unsigned char));
		word_arrays[i] = appointment_raw;
		word_arrays_sizes[i]=appointment_raw_len;	
	    }	
	    
	    //B words
	     if (g_strcmp0(word_str_lower,"bank")==0) {		
		word_arrays[i] = (unsigned char*)malloc(bank_raw_len * sizeof(unsigned char));
		word_arrays[i] = bank_raw;
		word_arrays_sizes[i]=bank_raw_len;	
	    }
	     if (g_strcmp0(word_str_lower,"birthday")==0) {		
		word_arrays[i] = (unsigned char*)malloc(birthday_raw_len * sizeof(unsigned char));
		word_arrays[i] = birthday_raw;
		word_arrays_sizes[i]=birthday_raw_len;	
	    }
	     if (g_strcmp0(word_str_lower,"boxing")==0) {		
		word_arrays[i] = (unsigned char*)malloc(boxing_raw_len * sizeof(unsigned char));
		word_arrays[i] = boxing_raw;
		word_arrays_sizes[i]=boxing_raw_len;	
	    }		
	    //c-words
	    
	    if (g_strcmp0(word_str_lower,"cafe")==0) {		
		word_arrays[i] = (unsigned char*)malloc(cafe_raw_len * sizeof(unsigned char));
		word_arrays[i] = cafe_raw;
		word_arrays_sizes[i]=cafe_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"calendar")==0) {		
		word_arrays[i] = (unsigned char*)malloc(calendar_raw_len * sizeof(unsigned char));
		word_arrays[i] = calendar_raw;
		word_arrays_sizes[i]=calendar_raw_len;	
	    }
	     if (g_strcmp0(word_str_lower,"car")==0) {		
		word_arrays[i] = (unsigned char*)malloc(car_raw_len * sizeof(unsigned char));
		word_arrays[i] = car_raw;
		word_arrays_sizes[i]=car_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"christmas")==0) {		
		word_arrays[i] = (unsigned char*)malloc(christmas_raw_len * sizeof(unsigned char));
		word_arrays[i] = christmas_raw;
		word_arrays_sizes[i]=christmas_raw_len;	
	    }				
	    
	    //D words
	    if (g_strcmp0(word_str_lower,"day")==0) {		
		word_arrays[i] = (unsigned char*)malloc(day_raw_len * sizeof(unsigned char));
		word_arrays[i] = day_raw;
		word_arrays_sizes[i]=day_raw_len;
	    }
	    if (g_strcmp0(word_str_lower,"delivery")==0) {		
		word_arrays[i] = (unsigned char*)malloc(delivery_raw_len * sizeof(unsigned char));
		word_arrays[i] = delivery_raw;
		word_arrays_sizes[i]=delivery_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"dentist")==0) {		
		word_arrays[i] = (unsigned char*)malloc(dentist_raw_len * sizeof(unsigned char));
		word_arrays[i] = dentist_raw;
		word_arrays_sizes[i]=dentist_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"driver")==0) {		
		word_arrays[i] = (unsigned char*)malloc(driver_raw_len * sizeof(unsigned char));
		word_arrays[i] = driver_raw;
		word_arrays_sizes[i]=driver_raw_len;	
	    }
	    
	    // E words
	    if (g_strcmp0(word_str_lower,"easter")==0) {		
		word_arrays[i] = (unsigned char*)malloc(easter_raw_len * sizeof(unsigned char));
		word_arrays[i] = easter_raw;
		word_arrays_sizes[i]=easter_raw_len;
	    }
	    if (g_strcmp0(word_str_lower,"event")==0) {		
		word_arrays[i] = (unsigned char*)malloc(event_raw_len * sizeof(unsigned char));
		word_arrays[i] = event_raw;
		word_arrays_sizes[i]=event_raw_len;
	    }
	    if (g_strcmp0(word_str_lower,"events")==0) {		
		word_arrays[i] = (unsigned char*)malloc(events_raw_len * sizeof(unsigned char));
		word_arrays[i] = events_raw;
		word_arrays_sizes[i]=events_raw_len;
	    }
	    //F words
	    
	    if (g_strcmp0(word_str_lower,"family")==0) {		
		word_arrays[i] = (unsigned char*)malloc(family_raw_len * sizeof(unsigned char));
		word_arrays[i] = family_raw;
		word_arrays_sizes[i]=family_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"funeral")==0) {
		g_print("funeral detected\n");		
		word_arrays[i] = (unsigned char*)malloc(funeral_raw_len  * sizeof(unsigned char));
		word_arrays[i] = funeral_raw;
		word_arrays_sizes[i]=funeral_raw_len;	
	    }			
	    //H words
	     if (g_strcmp0(word_str_lower,"high")==0) {
		word_arrays[i] = (unsigned char*)malloc(high_raw_len * sizeof(unsigned char));
		word_arrays[i] = high_raw;
		word_arrays_sizes[i]=high_raw_len;	
	    }	   
	     if (g_strcmp0(word_str_lower,"holiday")==0) {
		word_arrays[i] = (unsigned char*)malloc(holiday_raw_len * sizeof(unsigned char));
		word_arrays[i] = holiday_raw;
		word_arrays_sizes[i]=holiday_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"hospital")==0) {
		word_arrays[i] = (unsigned char*)malloc(hospital_raw_len * sizeof(unsigned char));
		word_arrays[i] = hospital_raw;
		word_arrays_sizes[i]=hospital_raw_len;	
	    }
	    
	    //i words
	    if (g_strcmp0(word_str_lower,"is")==0) {
		word_arrays[i] = (unsigned char*)malloc(is_raw_len * sizeof(unsigned char));
		word_arrays[i] = is_raw;
		word_arrays_sizes[i]=is_raw_len;	
	    }
	    
	    //M words
	    if (g_strcmp0(word_str_lower,"medical")==0) {
		word_arrays[i] = (unsigned char*)malloc(medical_raw_len * sizeof(unsigned char));
		word_arrays[i] = medical_raw;
		word_arrays_sizes[i]=medical_raw_len;	
	    } 
	    	    
	    if (g_strcmp0(word_str_lower,"meeting")==0) {
		word_arrays[i] = (unsigned char*)malloc(meeting_raw_len * sizeof(unsigned char));
		word_arrays[i] = meeting_raw;
		word_arrays_sizes[i]=meeting_raw_len;	
	    } 
	     if (g_strcmp0(word_str_lower,"meetup")==0) {
		word_arrays[i] = (unsigned char*)malloc(meetup_raw_len * sizeof(unsigned char));
		word_arrays[i] = meetup_raw;
		word_arrays_sizes[i]=meetup_raw_len;	
	    } 
	    if (g_strcmp0(word_str_lower,"memo")==0) {		
		word_arrays[i] = (unsigned char*)malloc(memo_raw_len * sizeof(unsigned char));
		word_arrays[i] = memo_raw;
		word_arrays_sizes[i]=memo_raw_len;	
	    }
	    	    	    
	    //N words
	    if (g_strcmp0(word_str_lower,"new")==0) {
		word_arrays[i] = (unsigned char*)malloc(new_raw_len * sizeof(unsigned char));
		word_arrays[i] = new_raw;
		word_arrays_sizes[i]=new_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"no")==0) {
		word_arrays[i] = (unsigned char*)malloc(no_raw_len * sizeof(unsigned char));
		word_arrays[i] = no_raw;
		word_arrays_sizes[i]=no_raw_len;	
	    }
	    //o words
	    if (g_strcmp0(word_str_lower,"o")==0) {		
		word_arrays[i] = (unsigned char*)malloc(o_raw_len * sizeof(unsigned char));
		word_arrays[i] = o_raw;
		word_arrays_sizes[i]=o_raw_len;	
	    }
	     
	     //P words
	    if (g_strcmp0(word_str_lower,"party")==0) {		
		word_arrays[i] = (unsigned char*)malloc(party_raw_len * sizeof(unsigned char));
		word_arrays[i] = party_raw;
		word_arrays_sizes[i]=party_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"payment")==0) {
		word_arrays[i] = (unsigned char*)malloc(payment_raw_len * sizeof(unsigned char));
		word_arrays[i] = payment_raw;
		word_arrays_sizes[i]=payment_raw_len;	
	    } 
	    if (g_strcmp0(word_str_lower,"pm")==0) {
		word_arrays[i] = (unsigned char*)malloc(pm_raw_len * sizeof(unsigned char));
		word_arrays[i] = pm_raw;
		word_arrays_sizes[i]=pm_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"priority")==0) {
		word_arrays[i] = (unsigned char*)malloc(priority_raw_len * sizeof(unsigned char));
		word_arrays[i] = priority_raw;
		word_arrays_sizes[i]=priority_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"project")==0) {		
		word_arrays[i] = (unsigned char*)malloc(project_raw_len * sizeof(unsigned char));
		word_arrays[i] = project_raw;
		word_arrays_sizes[i]=project_raw_len;	
	    }
	    //R words
	    if (g_strcmp0(word_str_lower,"reminder")==0) {
		word_arrays[i] = (unsigned char*)malloc(reminder_raw_len * sizeof(unsigned char));
		word_arrays[i] = reminder_raw;
		word_arrays_sizes[i]=reminder_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"restaurant")==0) {
		word_arrays[i] = (unsigned char*)malloc(restaurant_raw_len * sizeof(unsigned char));
		word_arrays[i] = restaurant_raw;
		word_arrays_sizes[i]=restaurant_raw_len;	
	    }
	    //S words
	    if (g_strcmp0(word_str_lower,"space")==0) {
	    word_arrays[i] = (unsigned char*)malloc(empty_raw_len * sizeof(unsigned char));
		word_arrays[i] =  empty_raw;		
		word_arrays_sizes[i]=empty_raw_len; 
	    }
	    
	    if (g_strcmp0(word_str_lower,"sport")==0) {
		word_arrays[i] = (unsigned char*)malloc(sport_raw_len * sizeof(unsigned char));
		word_arrays[i] = sport_raw;
		word_arrays_sizes[i]=sport_raw_len;
		}	
	    
	    if (g_strcmp0(word_str_lower,"spring")==0) {
		word_arrays[i] = (unsigned char*)malloc(spring_raw_len * sizeof(unsigned char));
		word_arrays[i] = spring_raw;
		word_arrays_sizes[i]=spring_raw_len;
		}	
	    
	    //T words
	     if (g_strcmp0(word_str_lower,"talk")==0) {
		word_arrays[i] = (unsigned char*)malloc(talk_raw_len * sizeof(unsigned char));
		word_arrays[i] = talk_raw;
		word_arrays_sizes[i]=talk_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"task")==0) {
		word_arrays[i] = (unsigned char*)malloc(task_raw_len * sizeof(unsigned char));
		word_arrays[i] = task_raw;
		word_arrays_sizes[i]=task_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"television")==0) {		
		word_arrays[i] = (unsigned char*)malloc(television_raw_len * sizeof(unsigned char));
		word_arrays[i] = television_raw;
		word_arrays_sizes[i]=television_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"the")==0) {		
		word_arrays[i] = (unsigned char*)malloc(the_raw_len * sizeof(unsigned char));
		word_arrays[i] = the_raw;
		word_arrays_sizes[i]=the_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"theatre")==0) {		
		word_arrays[i] = (unsigned char*)malloc(theatre_raw_len * sizeof(unsigned char));
		word_arrays[i] = theatre_raw;
		word_arrays_sizes[i]=theatre_raw_len;	
	    }
	    
	    //if (g_strcmp0(word_str_lower,"then")==0) {		
		//word_arrays[i] = (unsigned char*)malloc(then_raw_len * sizeof(unsigned char));
		//word_arrays[i] = then_raw;
		//word_arrays_sizes[i]=then_raw_len;	
	    //}
	    
	    if (g_strcmp0(word_str_lower,"time")==0) {		
		word_arrays[i] = (unsigned char*)malloc(time_raw_len * sizeof(unsigned char));
		word_arrays[i] = time_raw;
		word_arrays_sizes[i]=time_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"today")==0) {
		word_arrays[i] = (unsigned char*)malloc(today_raw_len * sizeof(unsigned char));
		word_arrays[i] = today_raw;
		word_arrays_sizes[i]=today_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"travel")==0) {
		word_arrays[i] = (unsigned char*)malloc(travel_raw_len * sizeof(unsigned char));
		word_arrays[i] = travel_raw;
		word_arrays_sizes[i]=travel_raw_len;	
	    }
	    //U words	    
	    if (g_strcmp0(word_str_lower,"upcoming")==0) {
		word_arrays[i] = (unsigned char*)malloc(upcoming_raw_len * sizeof(unsigned char));
		word_arrays[i] = upcoming_raw;
		word_arrays_sizes[i]=upcoming_raw_len;
	    }	
	    
	    //V words
	    
	    if (g_strcmp0(word_str_lower,"visit")==0) {
		word_arrays[i] = (unsigned char*)malloc(visit_raw_len * sizeof(unsigned char));
		word_arrays[i] = visit_raw;
		word_arrays_sizes[i]=visit_raw_len;	
	    }
	    //W words
	    if (g_strcmp0(word_str_lower,"work")==0) {
		word_arrays[i] = (unsigned char*)malloc(work_raw_len * sizeof(unsigned char));
		word_arrays[i] = work_raw;
		word_arrays_sizes[i]=work_raw_len;	
	    }
	     //Y words
	    if (g_strcmp0(word_str_lower,"year")==0) {
		word_arrays[i] = (unsigned char*)malloc(year_raw_len * sizeof(unsigned char));		
		word_arrays[i] = year_raw;
		word_arrays_sizes[i]=year_raw_len;	
	    }	
	    //Z words
	    if (g_strcmp0(word_str_lower,"zero")==0) {
		word_arrays[i] = (unsigned char*)malloc(zero_raw_len * sizeof(unsigned char));		
		word_arrays[i] = zero_raw;
		word_arrays_sizes[i]=zero_raw_len;	
	    }																													
	
	}//for

} //get word arrays

