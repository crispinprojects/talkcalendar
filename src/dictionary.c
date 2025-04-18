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

#include "chipmunk.h"

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
	    if (g_strcmp0(word_str_lower,"a")==0) {		
		word_arrays[i] = (unsigned char*)malloc(a_raw_len * sizeof(unsigned char));
		word_arrays[i] = a_raw;
		word_arrays_sizes[i]=a_raw_len;
	    } 
	    if (g_strcmp0(word_str_lower,"account")==0) {		
		word_arrays[i] = (unsigned char*)malloc(account_raw_len * sizeof(unsigned char));
		word_arrays[i] = account_raw;
		word_arrays_sizes[i]=account_raw_len;	
	    }	
	    if (g_strcmp0(word_str_lower,"activity")==0) {		
		word_arrays[i] = (unsigned char*)malloc(activity_raw_len * sizeof(unsigned char));
		word_arrays[i] = activity_raw;
		word_arrays_sizes[i]=activity_raw_len;	
	    }	 
	    if (g_strcmp0(word_str_lower,"all")==0) {		
		word_arrays[i] = (unsigned char*)malloc(all_raw_len * sizeof(unsigned char));
		word_arrays[i] = all_raw;
		word_arrays_sizes[i]=all_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"allotment")==0) {		
		word_arrays[i] = (unsigned char*)malloc(allotment_raw_len * sizeof(unsigned char));
		word_arrays[i] = allotment_raw;
		word_arrays_sizes[i]=allotment_raw_len;	
	    }	
	    
	    if (g_strcmp0(word_str_lower,"am")==0) {		
		word_arrays[i] = (unsigned char*)malloc(am_raw_len * sizeof(unsigned char));
		word_arrays[i] = am_raw;
		word_arrays_sizes[i]=am_raw_len;
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
	     if (g_strcmp0(word_str_lower,"art")==0) {		
		word_arrays[i] = (unsigned char*)malloc(art_raw_len * sizeof(unsigned char));
		word_arrays[i] = art_raw;
		word_arrays_sizes[i]=art_raw_len;	
	    }	
	    if (g_strcmp0(word_str_lower,"aunt")==0) {		
		word_arrays[i] = (unsigned char*)malloc(aunt_raw_len * sizeof(unsigned char));
		word_arrays[i] = aunt_raw;
		word_arrays_sizes[i]=aunt_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"autumn")==0) {		
		word_arrays[i] = (unsigned char*)malloc(autumn_raw_len * sizeof(unsigned char));
		word_arrays[i] = autumn_raw;
		word_arrays_sizes[i]=autumn_raw_len;	
	    }		
	    
	    //B words
	    if (g_strcmp0(word_str_lower,"bank")==0) {		
		word_arrays[i] = (unsigned char*)malloc(bank_raw_len * sizeof(unsigned char));
		word_arrays[i] = bank_raw;
		word_arrays_sizes[i]=bank_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"barber")==0) {		
		word_arrays[i] = (unsigned char*)malloc(barber_raw_len * sizeof(unsigned char));
		word_arrays[i] = barber_raw;
		word_arrays_sizes[i]=barber_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"begins")==0) {		
		word_arrays[i] = (unsigned char*)malloc(begins_raw_len * sizeof(unsigned char));
		word_arrays[i] = begins_raw;
		word_arrays_sizes[i]=begins_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"birthday")==0) {		
		word_arrays[i] = (unsigned char*)malloc(birthday_raw_len * sizeof(unsigned char));
		word_arrays[i] = birthday_raw;
		word_arrays_sizes[i]=birthday_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"book")==0) {		
		word_arrays[i] = (unsigned char*)malloc(book_raw_len * sizeof(unsigned char));
		word_arrays[i] = book_raw;
		word_arrays_sizes[i]=book_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"boxing")==0) {		
		word_arrays[i] = (unsigned char*)malloc(boxing_raw_len * sizeof(unsigned char));
		word_arrays[i] = boxing_raw;
		word_arrays_sizes[i]=boxing_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"british")==0) {		
		word_arrays[i] = (unsigned char*)malloc(british_raw_len * sizeof(unsigned char));
		word_arrays[i] = british_raw;
		word_arrays_sizes[i]=british_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"brother")==0) {		
		word_arrays[i] = (unsigned char*)malloc(brother_raw_len * sizeof(unsigned char));
		word_arrays[i] = brother_raw;
		word_arrays_sizes[i]=brother_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"brothers")==0) {		
		word_arrays[i] = (unsigned char*)malloc(brothers_raw_len * sizeof(unsigned char));
		word_arrays[i] = brothers_raw;
		word_arrays_sizes[i]=brothers_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"business")==0) {		
		word_arrays[i] = (unsigned char*)malloc(business_raw_len * sizeof(unsigned char));
		word_arrays[i] = business_raw;
		word_arrays_sizes[i]=business_raw_len;	
	    }
	    		
	    //c-words
	    if (g_strcmp0(word_str_lower,"cabbie")==0) {		
		word_arrays[i] = (unsigned char*)malloc(cabbie_raw_len * sizeof(unsigned char));
		word_arrays[i] = cabbie_raw;
		word_arrays_sizes[i]=cabbie_raw_len;	
	    }
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
	    if (g_strcmp0(word_str_lower,"chauffeur")==0) {		
		word_arrays[i] = (unsigned char*)malloc(chauffeur_raw_len * sizeof(unsigned char));
		word_arrays[i] = chauffeur_raw;
		word_arrays_sizes[i]=chauffeur_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"children")==0) {		
		word_arrays[i] = (unsigned char*)malloc(children_raw_len * sizeof(unsigned char));
		word_arrays[i] = children_raw;
		word_arrays_sizes[i]=children_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"christmas")==0) {		
		word_arrays[i] = (unsigned char*)malloc(christmas_raw_len * sizeof(unsigned char));
		word_arrays[i] = christmas_raw;
		word_arrays_sizes[i]=christmas_raw_len;	
	    }	
	    if (g_strcmp0(word_str_lower,"church")==0) {		
		word_arrays[i] = (unsigned char*)malloc(church_raw_len * sizeof(unsigned char));
		word_arrays[i] = church_raw;
		word_arrays_sizes[i]=church_raw_len;	
	    }			
	    
	    if (g_strcmp0(word_str_lower,"cinema")==0) {		
		word_arrays[i] = (unsigned char*)malloc(cinema_raw_len * sizeof(unsigned char));
		word_arrays[i] = cinema_raw;
		word_arrays_sizes[i]=cinema_raw_len;	
	    }
	    
	     if (g_strcmp0(word_str_lower,"city")==0) {		
		word_arrays[i] = (unsigned char*)malloc(city_raw_len * sizeof(unsigned char));
		word_arrays[i] = city_raw;
		word_arrays_sizes[i]=city_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"clock")==0) {		
		word_arrays[i] = (unsigned char*)malloc(clock_raw_len * sizeof(unsigned char));
		word_arrays[i] = clock_raw;
		word_arrays_sizes[i]=clock_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"clocks")==0) {		
		word_arrays[i] = (unsigned char*)malloc(clocks_raw_len * sizeof(unsigned char));
		word_arrays[i] = clocks_raw;
		word_arrays_sizes[i]=clocks_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"code")==0) {		
		word_arrays[i] = (unsigned char*)malloc(code_raw_len * sizeof(unsigned char));
		word_arrays[i] = code_raw;
		word_arrays_sizes[i]=code_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"coding")==0) {		
		word_arrays[i] = (unsigned char*)malloc(coding_raw_len * sizeof(unsigned char));
		word_arrays[i] = coding_raw;
		word_arrays_sizes[i]=coding_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"computer")==0) {		
		word_arrays[i] = (unsigned char*)malloc(computer_raw_len * sizeof(unsigned char));
		word_arrays[i] = computer_raw;
		word_arrays_sizes[i]=computer_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"contact")==0) {		
		word_arrays[i] = (unsigned char*)malloc(contact_raw_len * sizeof(unsigned char));
		word_arrays[i] = contact_raw;
		word_arrays_sizes[i]=contact_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"cousin")==0) {		
		word_arrays[i] = (unsigned char*)malloc(cousin_raw_len * sizeof(unsigned char));
		word_arrays[i] = cousin_raw;
		word_arrays_sizes[i]=cousin_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"crispins")==0) {		
		word_arrays[i] = (unsigned char*)malloc(crispins_raw_len * sizeof(unsigned char));
		word_arrays[i] = crispins_raw;
		word_arrays_sizes[i]=crispins_raw_len;	
	    }
	    
	    //D words
	    if (g_strcmp0(word_str_lower,"dad")==0) {		
		word_arrays[i] = (unsigned char*)malloc(dad_raw_len * sizeof(unsigned char));
		word_arrays[i] = dad_raw;
		word_arrays_sizes[i]=dad_raw_len;
	    }
	    
	    if (g_strcmp0(word_str_lower,"dads")==0) {		
		word_arrays[i] = (unsigned char*)malloc(dads_raw_len * sizeof(unsigned char));
		word_arrays[i] = dads_raw;
		word_arrays_sizes[i]=dads_raw_len;
	    }
	    
	    if (g_strcmp0(word_str_lower,"daughter")==0) {		
		word_arrays[i] = (unsigned char*)malloc(daughter_raw_len * sizeof(unsigned char));
		word_arrays[i] = daughter_raw;
		word_arrays_sizes[i]=daughter_raw_len;
	    }
	    
	    if (g_strcmp0(word_str_lower,"daughters")==0) {		
		word_arrays[i] = (unsigned char*)malloc(daughters_raw_len * sizeof(unsigned char));
		word_arrays[i] = daughters_raw;
		word_arrays_sizes[i]=daughters_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"date")==0) {		
		word_arrays[i] = (unsigned char*)malloc(date_raw_len * sizeof(unsigned char));
		word_arrays[i] = date_raw;
		word_arrays_sizes[i]=date_raw_len;
	    }
	    
	    if (g_strcmp0(word_str_lower,"day")==0) {		
		word_arrays[i] = (unsigned char*)malloc(day_raw_len * sizeof(unsigned char));
		word_arrays[i] = day_raw;
		word_arrays_sizes[i]=day_raw_len;
	    }
	    
	     if (g_strcmp0(word_str_lower,"deadline")==0) {		
		word_arrays[i] = (unsigned char*)malloc(deadline_raw_len * sizeof(unsigned char));
		word_arrays[i] = deadline_raw;
		word_arrays_sizes[i]=deadline_raw_len;
	    }
	    if (g_strcmp0(word_str_lower,"decorating")==0) {		
		word_arrays[i] = (unsigned char*)malloc(decorating_raw_len * sizeof(unsigned char));
		word_arrays[i] = decorating_raw;
		word_arrays_sizes[i]=decorating_raw_len;
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
	    if (g_strcmp0(word_str_lower,"development")==0) {		
		word_arrays[i] = (unsigned char*)malloc(development_raw_len * sizeof(unsigned char));
		word_arrays[i] = development_raw;
		word_arrays_sizes[i]=development_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"doctor")==0) {		
		word_arrays[i] = (unsigned char*)malloc(doctor_raw_len * sizeof(unsigned char));
		word_arrays[i] = doctor_raw;
		word_arrays_sizes[i]=doctor_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"driver")==0) {		
		word_arrays[i] = (unsigned char*)malloc(driver_raw_len * sizeof(unsigned char));
		word_arrays[i] = driver_raw;
		word_arrays_sizes[i]=driver_raw_len;	
	    }
	    
	    // E words
	    if (g_strcmp0(word_str_lower,"early")==0) {		
		word_arrays[i] = (unsigned char*)malloc(early_raw_len * sizeof(unsigned char));
		word_arrays[i] = early_raw;
		word_arrays_sizes[i]=early_raw_len;
	    }
	    
	    if (g_strcmp0(word_str_lower,"easter")==0) {		
		word_arrays[i] = (unsigned char*)malloc(easter_raw_len * sizeof(unsigned char));
		word_arrays[i] = easter_raw;
		word_arrays_sizes[i]=easter_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"education")==0) {		
		word_arrays[i] = (unsigned char*)malloc(education_raw_len * sizeof(unsigned char));
		word_arrays[i] = education_raw;
		word_arrays_sizes[i]=education_raw_len;
	    }
	     
	    if (g_strcmp0(word_str_lower,"electric")==0) {		
		word_arrays[i] = (unsigned char*)malloc(electric_raw_len * sizeof(unsigned char));
		word_arrays[i] = electric_raw;
		word_arrays_sizes[i]=electric_raw_len;
	    }
	    
	    if (g_strcmp0(word_str_lower,"ends")==0) {		
		word_arrays[i] = (unsigned char*)malloc(ends_raw_len * sizeof(unsigned char));
		word_arrays[i] = ends_raw;
		word_arrays_sizes[i]=ends_raw_len;
	    }
	    
	    if (g_strcmp0(word_str_lower,"evening")==0) {		
		word_arrays[i] = (unsigned char*)malloc(evening_raw_len * sizeof(unsigned char));
		word_arrays[i] = evening_raw;
		word_arrays_sizes[i]=evening_raw_len;
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
	    if (g_strcmp0(word_str_lower,"father")==0) {		
		word_arrays[i] = (unsigned char*)malloc(father_raw_len * sizeof(unsigned char));
		word_arrays[i] = father_raw;
		word_arrays_sizes[i]=father_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"fathers")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fathers_raw_len * sizeof(unsigned char));
		word_arrays[i] = fathers_raw;
		word_arrays_sizes[i]=fathers_raw_len;	
	    }
	    
	     if (g_strcmp0(word_str_lower,"faukes")==0) {		
		word_arrays[i] = (unsigned char*)malloc(faukes_raw_len * sizeof(unsigned char));
		word_arrays[i] = faukes_raw;
		word_arrays_sizes[i]=faukes_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"festival")==0) {		
		word_arrays[i] = (unsigned char*)malloc(festival_raw_len * sizeof(unsigned char));
		word_arrays[i] = festival_raw;
		word_arrays_sizes[i]=festival_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"film")==0) {		
		word_arrays[i] = (unsigned char*)malloc(film_raw_len * sizeof(unsigned char));
		word_arrays[i] = film_raw;
		word_arrays_sizes[i]=film_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"fools")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fools_raw_len * sizeof(unsigned char));
		word_arrays[i] = fools_raw;
		word_arrays_sizes[i]=fools_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"forward")==0) {		
		word_arrays[i] = (unsigned char*)malloc(forward_raw_len * sizeof(unsigned char));
		word_arrays[i] = forward_raw;
		word_arrays_sizes[i]=forward_raw_len;	
	    }
	    
	     if (g_strcmp0(word_str_lower,"friend")==0) {		
		word_arrays[i] = (unsigned char*)malloc(friend_raw_len * sizeof(unsigned char));
		word_arrays[i] = friend_raw;
		word_arrays_sizes[i]=friend_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"funeral")==0) {
		g_print("funeral detected\n");		
		word_arrays[i] = (unsigned char*)malloc(funeral_raw_len  * sizeof(unsigned char));
		word_arrays[i] = funeral_raw;
		word_arrays_sizes[i]=funeral_raw_len;	
	    }
	    			
	    //H words
	    if (g_strcmp0(word_str_lower,"hello")==0) {
		word_arrays[i] = (unsigned char*)malloc(hello_raw_len * sizeof(unsigned char));
		word_arrays[i] = hello_raw;
		word_arrays_sizes[i]=hello_raw_len;	
	    }
	    	   
	     if (g_strcmp0(word_str_lower,"high")==0) {
		word_arrays[i] = (unsigned char*)malloc(high_raw_len * sizeof(unsigned char));
		word_arrays[i] = high_raw;
		word_arrays_sizes[i]=high_raw_len;	
	    }
	    
	    //G Words
	    
	     if (g_strcmp0(word_str_lower,"garage")==0) {
		word_arrays[i] = (unsigned char*)malloc(garage_raw_len * sizeof(unsigned char));
		word_arrays[i] = garage_raw;
		word_arrays_sizes[i]=garage_raw_len;	
	    }
	    
	     if (g_strcmp0(word_str_lower,"garden")==0) {
		word_arrays[i] = (unsigned char*)malloc(garden_raw_len * sizeof(unsigned char));
		word_arrays[i] = garden_raw;
		word_arrays_sizes[i]=garden_raw_len;	
	    }
	    
	     if (g_strcmp0(word_str_lower,"gas")==0) {
		word_arrays[i] = (unsigned char*)malloc(gas_raw_len * sizeof(unsigned char));
		word_arrays[i] = gas_raw;
		word_arrays_sizes[i]=gas_raw_len;	
	    }
	    
	     if (g_strcmp0(word_str_lower,"georges")==0) {
		word_arrays[i] = (unsigned char*)malloc(georges_raw_len * sizeof(unsigned char));
		word_arrays[i] = georges_raw;
		word_arrays_sizes[i]=georges_raw_len;	
	    }
	    
	     if (g_strcmp0(word_str_lower,"good")==0) {
		word_arrays[i] = (unsigned char*)malloc(good_raw_len * sizeof(unsigned char));
		word_arrays[i] = good_raw;
		word_arrays_sizes[i]=good_raw_len;	
	    }
	    
	     //if (g_strcmp0(word_str_lower,"goodbye")==0) {
		//word_arrays[i] = (unsigned char*)malloc(goodbye_raw_len * sizeof(unsigned char));
		//word_arrays[i] = goodbye_raw;
		//word_arrays_sizes[i]=goodbye_raw_len;		
	    //} 
	    
	    if (g_strcmp0(word_str_lower,"grand")==0) {
		word_arrays[i] = (unsigned char*)malloc(grand_raw_len * sizeof(unsigned char));
		word_arrays[i] = grand_raw;
		word_arrays_sizes[i]=grand_raw_len;	
	    }
	    
	     if (g_strcmp0(word_str_lower,"guy")==0) {
		word_arrays[i] = (unsigned char*)malloc(guy_raw_len * sizeof(unsigned char));
		word_arrays[i] = guy_raw;
		word_arrays_sizes[i]=guy_raw_len;	
	    }
	    	    
	    //H words
	    if (g_strcmp0(word_str_lower,"hairdresser")==0) {
		word_arrays[i] = (unsigned char*)malloc(hairdresser_raw_len * sizeof(unsigned char));
		word_arrays[i] = hairdresser_raw;
		word_arrays_sizes[i]=hairdresser_raw_len;	
	    }	
	   
	   if (g_strcmp0(word_str_lower,"halloween")==0) {
		word_arrays[i] = (unsigned char*)malloc(halloween_raw_len * sizeof(unsigned char));
		word_arrays[i] = halloween_raw;
		word_arrays_sizes[i]=halloween_raw_len;	
	    }	
	   
	    if (g_strcmp0(word_str_lower,"have")==0) {
		word_arrays[i] = (unsigned char*)malloc(have_raw_len * sizeof(unsigned char));
		word_arrays[i] = have_raw;
		word_arrays_sizes[i]=have_raw_len;	
	    }	
	    
	    if (g_strcmp0(word_str_lower,"hello")==0) {
		word_arrays[i] = (unsigned char*)malloc(hello_raw_len * sizeof(unsigned char));
		word_arrays[i] = hello_raw;
		word_arrays_sizes[i]=hello_raw_len;	
	    }	
	    
	    
	    if (g_strcmp0(word_str_lower,"high")==0) {
		word_arrays[i] = (unsigned char*)malloc(high_raw_len * sizeof(unsigned char));
		word_arrays[i] = high_raw;
		word_arrays_sizes[i]=high_raw_len;	
	    }	
	    
	    if (g_strcmp0(word_str_lower,"hobby")==0) {
		word_arrays[i] = (unsigned char*)malloc(hobby_raw_len * sizeof(unsigned char));
		word_arrays[i] = hobby_raw;
		word_arrays_sizes[i]=hobby_raw_len;	
	    }	     
	     if (g_strcmp0(word_str_lower,"holiday")==0) {
		word_arrays[i] = (unsigned char*)malloc(holiday_raw_len * sizeof(unsigned char));
		word_arrays[i] = holiday_raw;
		word_arrays_sizes[i]=holiday_raw_len;	
	    }
	    
	     if (g_strcmp0(word_str_lower,"home")==0) {
		word_arrays[i] = (unsigned char*)malloc(home_raw_len * sizeof(unsigned char));
		word_arrays[i] = home_raw;
		word_arrays_sizes[i]=home_raw_len;	
	    }	
	    
	    if (g_strcmp0(word_str_lower,"hospital")==0) {
		word_arrays[i] = (unsigned char*)malloc(hospital_raw_len * sizeof(unsigned char));
		word_arrays[i] = hospital_raw;
		word_arrays_sizes[i]=hospital_raw_len;	
	    }
	    
	     if (g_strcmp0(word_str_lower,"hour")==0) {
		word_arrays[i] = (unsigned char*)malloc(hour_raw_len * sizeof(unsigned char));
		word_arrays[i] = hour_raw;
		word_arrays_sizes[i]=hour_raw_len;	
	    }	
	    
	     if (g_strcmp0(word_str_lower,"house")==0) {
		word_arrays[i] = (unsigned char*)malloc(house_raw_len * sizeof(unsigned char));
		word_arrays[i] = house_raw;
		word_arrays_sizes[i]=house_raw_len;	
	    }	
	    
	     if (g_strcmp0(word_str_lower,"husband")==0) {
		word_arrays[i] = (unsigned char*)malloc(husband_raw_len * sizeof(unsigned char));
		word_arrays[i] = husband_raw;
		word_arrays_sizes[i]=husband_raw_len;	
	    }	
	    
	    //i words
	    if (g_strcmp0(word_str_lower,"i")==0) {
		word_arrays[i] = (unsigned char*)malloc(i_raw_len * sizeof(unsigned char));
		word_arrays[i] = i_raw;
		word_arrays_sizes[i]=i_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"iam")==0) {
		word_arrays[i] = (unsigned char*)malloc(iam_raw_len * sizeof(unsigned char));
		word_arrays[i] = iam_raw;
		word_arrays_sizes[i]=iam_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"in")==0) {
		word_arrays[i] = (unsigned char*)malloc(in_raw_len * sizeof(unsigned char));
		word_arrays[i] = in_raw;
		word_arrays_sizes[i]=in_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"industry")==0) {
		word_arrays[i] = (unsigned char*)malloc(industry_raw_len * sizeof(unsigned char));
		word_arrays[i] = industry_raw;
		word_arrays_sizes[i]=industry_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"insurance")==0) {
		word_arrays[i] = (unsigned char*)malloc(insurance_raw_len * sizeof(unsigned char));
		word_arrays[i] = insurance_raw;
		word_arrays_sizes[i]=insurance_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"investment")==0) {
		word_arrays[i] = (unsigned char*)malloc(investment_raw_len * sizeof(unsigned char));
		word_arrays[i] = investment_raw;
		word_arrays_sizes[i]=investment_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"is")==0) {
		word_arrays[i] = (unsigned char*)malloc(is_raw_len * sizeof(unsigned char));
		word_arrays[i] = is_raw;
		word_arrays_sizes[i]=is_raw_len;	
	    }
	    
	    //J words
	    
	    if (g_strcmp0(word_str_lower,"jeweler")==0) {
		word_arrays[i] = (unsigned char*)malloc(jeweler_raw_len * sizeof(unsigned char));
		word_arrays[i] = jeweler_raw;
		word_arrays_sizes[i]=jeweler_raw_len;	
	    }
	    
	    //M words
	    if (g_strcmp0(word_str_lower,"many")==0) {
		word_arrays[i] = (unsigned char*)malloc(many_raw_len * sizeof(unsigned char));
		word_arrays[i] = many_raw;
		word_arrays_sizes[i]=many_raw_len;	
	    }
	    
	     if (g_strcmp0(word_str_lower,"master")==0) {
		word_arrays[i] = (unsigned char*)malloc(master_raw_len * sizeof(unsigned char));
		word_arrays[i] = master_raw;
		word_arrays_sizes[i]=master_raw_len;	
	    }
	    
	     if (g_strcmp0(word_str_lower,"meal")==0) {
		word_arrays[i] = (unsigned char*)malloc(meal_raw_len * sizeof(unsigned char));
		word_arrays[i] = meal_raw;
		word_arrays_sizes[i]=meal_raw_len;	
	    }
	    
	     if (g_strcmp0(word_str_lower,"mechanic")==0) {
		word_arrays[i] = (unsigned char*)malloc(mechanic_raw_len * sizeof(unsigned char));
		word_arrays[i] = mechanic_raw;
		word_arrays_sizes[i]=mechanic_raw_len;	
	    }
	    
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
	    
	     if (g_strcmp0(word_str_lower,"month")==0) {
		word_arrays[i] = (unsigned char*)malloc(month_raw_len * sizeof(unsigned char));
		word_arrays[i] = month_raw;
		word_arrays_sizes[i]=month_raw_len;	
	    }
	    
	     if (g_strcmp0(word_str_lower,"morning")==0) {
		word_arrays[i] = (unsigned char*)malloc(morning_raw_len * sizeof(unsigned char));
		word_arrays[i] = morning_raw;
		word_arrays_sizes[i]=morning_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"mother")==0) {		
		word_arrays[i] = (unsigned char*)malloc(mother_raw_len * sizeof(unsigned char));
		word_arrays[i] = mother_raw;
		word_arrays_sizes[i]=mother_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"mothers")==0) {		
		word_arrays[i] = (unsigned char*)malloc(mothers_raw_len * sizeof(unsigned char));
		word_arrays[i] = mothers_raw;
		word_arrays_sizes[i]=mothers_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"movie")==0) {		
		word_arrays[i] = (unsigned char*)malloc(movie_raw_len * sizeof(unsigned char));
		word_arrays[i] = movie_raw;
		word_arrays_sizes[i]=movie_raw_len;	
	    }
	    
	     if (g_strcmp0(word_str_lower,"movie")==0) {		
		word_arrays[i] = (unsigned char*)malloc(movie_raw_len * sizeof(unsigned char));
		word_arrays[i] = movie_raw;
		word_arrays_sizes[i]=movie_raw_len;	
	    }
	    
	     if (g_strcmp0(word_str_lower,"move")==0) {		
		word_arrays[i] = (unsigned char*)malloc(move_raw_len * sizeof(unsigned char));
		word_arrays[i] = move_raw;
		word_arrays_sizes[i]=move_raw_len;	
	    }
	    
	     if (g_strcmp0(word_str_lower,"mum")==0) {		
		word_arrays[i] = (unsigned char*)malloc(mum_raw_len * sizeof(unsigned char));
		word_arrays[i] = mum_raw;
		word_arrays_sizes[i]=mum_raw_len;	
	    }
	    
	     if (g_strcmp0(word_str_lower,"mums")==0) {		
		word_arrays[i] = (unsigned char*)malloc(mums_raw_len * sizeof(unsigned char));
		word_arrays[i] = mums_raw;
		word_arrays_sizes[i]=mums_raw_len;	
	    }
	    
	     if (g_strcmp0(word_str_lower,"music")==0) {		
		word_arrays[i] = (unsigned char*)malloc(music_raw_len * sizeof(unsigned char));
		word_arrays[i] = music_raw;
		word_arrays_sizes[i]=music_raw_len;	
	    }
	    
	     if (g_strcmp0(word_str_lower,"my")==0) {		
		word_arrays[i] = (unsigned char*)malloc(my_raw_len * sizeof(unsigned char));
		word_arrays[i] = my_raw;
		word_arrays_sizes[i]=my_raw_len;	
	    }
	    	    	    
	    //N words
	      if (g_strcmp0(word_str_lower,"neighbour")==0) {
		word_arrays[i] = (unsigned char*)malloc(neighbour_raw_len * sizeof(unsigned char));
		word_arrays[i] = neighbour_raw;
		word_arrays_sizes[i]=neighbour_raw_len;	
	    }
	    
	     if (g_strcmp0(word_str_lower,"nephew")==0) {
		word_arrays[i] = (unsigned char*)malloc(nephew_raw_len * sizeof(unsigned char));
		word_arrays[i] = nephew_raw;
		word_arrays_sizes[i]=nephew_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"new")==0) {
		word_arrays[i] = (unsigned char*)malloc(new_raw_len * sizeof(unsigned char));
		word_arrays[i] = new_raw;
		word_arrays_sizes[i]=new_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"news")==0) {
		word_arrays[i] = (unsigned char*)malloc(news_raw_len * sizeof(unsigned char));
		word_arrays[i] = news_raw;
		word_arrays_sizes[i]=news_raw_len;	
	    }
	    
	    //if (g_strcmp0(word_str_lower,"newspaper")==0) {
		//word_arrays[i] = (unsigned char*)malloc(newspaper_raw_len * sizeof(unsigned char));
		//word_arrays[i] = newspaper_raw;
		//word_arrays_sizes[i]=newspaper_raw_len;	
	    //}
	    
	    if (g_strcmp0(word_str_lower,"night")==0) {
		word_arrays[i] = (unsigned char*)malloc(night_raw_len * sizeof(unsigned char));
		word_arrays[i] = night_raw;
		word_arrays_sizes[i]=night_raw_len;	
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
	    
	      if (g_strcmp0(word_str_lower,"on")==0) {		
		word_arrays[i] = (unsigned char*)malloc(on_raw_len * sizeof(unsigned char));
		word_arrays[i] = on_raw;
		word_arrays_sizes[i]=on_raw_len;	
	    }
	     
	      if (g_strcmp0(word_str_lower,"online")==0) {		
		word_arrays[i] = (unsigned char*)malloc(online_raw_len * sizeof(unsigned char));
		word_arrays[i] = online_raw;
		word_arrays_sizes[i]=online_raw_len;	
	    }
	    
	    
	     //P words
	     
	    if (g_strcmp0(word_str_lower,"paper")==0) {		
		word_arrays[i] = (unsigned char*)malloc(paper_raw_len * sizeof(unsigned char));
		word_arrays[i] = paper_raw;
		word_arrays_sizes[i]=paper_raw_len;	
	    }
	    
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
	    
	    if (g_strcmp0(word_str_lower,"pension")==0) {
		word_arrays[i] = (unsigned char*)malloc(pension_raw_len * sizeof(unsigned char));
		word_arrays[i] = pension_raw;
		word_arrays_sizes[i]=pension_raw_len;	
	    } 
	    
	    if (g_strcmp0(word_str_lower,"phone")==0) {
		word_arrays[i] = (unsigned char*)malloc(phone_raw_len * sizeof(unsigned char));
		word_arrays[i] = phone_raw;
		word_arrays_sizes[i]=phone_raw_len;	
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
	    
	    if (g_strcmp0(word_str_lower,"public")==0) {		
		word_arrays[i] = (unsigned char*)malloc(public_raw_len * sizeof(unsigned char));
		word_arrays[i] = public_raw;
		word_arrays_sizes[i]=public_raw_len;	
	    }
	    
	    
	     if (g_strcmp0(word_str_lower,"pictures")==0) {		
		word_arrays[i] = (unsigned char*)malloc(pictures_raw_len * sizeof(unsigned char));
		word_arrays[i] = pictures_raw;
		word_arrays_sizes[i]=pictures_raw_len;	
	    }
	    
	    //Q Words
	     if (g_strcmp0(word_str_lower,"quiz")==0) {		
		word_arrays[i] = (unsigned char*)malloc(quiz_raw_len * sizeof(unsigned char));
		word_arrays[i] = quiz_raw;
		word_arrays_sizes[i]=quiz_raw_len;	
	    }
	    
	    
	    //R words
	    
	     if (g_strcmp0(word_str_lower,"radio")==0) {
		word_arrays[i] = (unsigned char*)malloc(radio_raw_len * sizeof(unsigned char));
		word_arrays[i] = radio_raw;
		word_arrays_sizes[i]=radio_raw_len;	
	    }
	    	    
		if (g_strcmp0(word_str_lower,"reminder")==0) {
		word_arrays[i] = (unsigned char*)malloc(reminder_raw_len * sizeof(unsigned char));
		word_arrays[i] = reminder_raw;
		word_arrays_sizes[i]=reminder_raw_len;	
		}
	    
	       if (g_strcmp0(word_str_lower,"repair")==0) {
		word_arrays[i] = (unsigned char*)malloc(repair_raw_len * sizeof(unsigned char));
		word_arrays[i] = repair_raw;
		word_arrays_sizes[i]=repair_raw_len;	
	    }
	    	    
	    if (g_strcmp0(word_str_lower,"restaurant")==0) {
		word_arrays[i] = (unsigned char*)malloc(restaurant_raw_len * sizeof(unsigned char));
		word_arrays[i] = restaurant_raw;
		word_arrays_sizes[i]=restaurant_raw_len;	
	    }
	    
	       if (g_strcmp0(word_str_lower,"return")==0) {
		word_arrays[i] = (unsigned char*)malloc(return_raw_len * sizeof(unsigned char));
		word_arrays[i] = return_raw;
		word_arrays_sizes[i]=return_raw_len;	
	    }
	    
	       if (g_strcmp0(word_str_lower,"royal")==0) {
		word_arrays[i] = (unsigned char*)malloc(royal_raw_len * sizeof(unsigned char));
		word_arrays[i] = royal_raw;
		word_arrays_sizes[i]=royal_raw_len;	
	    }
	    
	    //S words
	    if (g_strcmp0(word_str_lower,"saint")==0) {
	    word_arrays[i] = (unsigned char*)malloc(saint_raw_len * sizeof(unsigned char));
		word_arrays[i] =  saint_raw;		
		word_arrays_sizes[i]=saint_raw_len; 
	    }
	    
	    if (g_strcmp0(word_str_lower,"service")==0) {
	    word_arrays[i] = (unsigned char*)malloc(service_raw_len * sizeof(unsigned char));
		word_arrays[i] =  service_raw;		
		word_arrays_sizes[i]=service_raw_len; 
	    }
	    
	    if (g_strcmp0(word_str_lower,"shop")==0) {
	    word_arrays[i] = (unsigned char*)malloc(shop_raw_len * sizeof(unsigned char));
		word_arrays[i] =  shop_raw;		
		word_arrays_sizes[i]=shop_raw_len; 
	    }
	    
	    if (g_strcmp0(word_str_lower,"shopping")==0) {
	    word_arrays[i] = (unsigned char*)malloc(shopping_raw_len * sizeof(unsigned char));
		word_arrays[i] =  shopping_raw;		
		word_arrays_sizes[i]=shopping_raw_len; 
	    }
	    
	    if (g_strcmp0(word_str_lower,"sister")==0) {
	    word_arrays[i] = (unsigned char*)malloc(sister_raw_len * sizeof(unsigned char));
		word_arrays[i] =  sister_raw;		
		word_arrays_sizes[i]=sister_raw_len; 
	    }
	    
	    if (g_strcmp0(word_str_lower,"sisters")==0) {
	    word_arrays[i] = (unsigned char*)malloc(sisters_raw_len * sizeof(unsigned char));
		word_arrays[i] =  sisters_raw;		
		word_arrays_sizes[i]=sisters_raw_len; 
	    }    
	    
	    if (g_strcmp0(word_str_lower,"software")==0) {
	    word_arrays[i] = (unsigned char*)malloc(software_raw_len * sizeof(unsigned char));
		word_arrays[i] =  software_raw;		
		word_arrays_sizes[i]=software_raw_len; 
	    }
	    
	    if (g_strcmp0(word_str_lower,"son")==0) {
	    word_arrays[i] = (unsigned char*)malloc(son_raw_len * sizeof(unsigned char));
		word_arrays[i] =  son_raw;		
		word_arrays_sizes[i]=son_raw_len; 
	    }
	    if (g_strcmp0(word_str_lower,"sons")==0) {
	    word_arrays[i] = (unsigned char*)malloc(sons_raw_len * sizeof(unsigned char));
		word_arrays[i] =  sons_raw;		
		word_arrays_sizes[i]=sons_raw_len; 
	    }
	    
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
		
		if (g_strcmp0(word_str_lower,"start")==0) {
		word_arrays[i] = (unsigned char*)malloc(start_raw_len * sizeof(unsigned char));
		word_arrays[i] = start_raw;
		word_arrays_sizes[i]=start_raw_len;
		}
		
		if (g_strcmp0(word_str_lower,"starts")==0) {
		word_arrays[i] = (unsigned char*)malloc(starts_raw_len * sizeof(unsigned char));
		word_arrays[i] = starts_raw;
		word_arrays_sizes[i]=starts_raw_len;
		}
		
		if (g_strcmp0(word_str_lower,"station")==0) {
		word_arrays[i] = (unsigned char*)malloc(station_raw_len * sizeof(unsigned char));
		word_arrays[i] = station_raw;
		word_arrays_sizes[i]=station_raw_len;
		}	
		
		if (g_strcmp0(word_str_lower,"study")==0) {
		word_arrays[i] = (unsigned char*)malloc(study_raw_len * sizeof(unsigned char));
		word_arrays[i] = study_raw;
		word_arrays_sizes[i]=study_raw_len;
		}
		
		if (g_strcmp0(word_str_lower,"summer")==0) {
		word_arrays[i] = (unsigned char*)malloc(summer_raw_len * sizeof(unsigned char));
		word_arrays[i] = summer_raw;
		word_arrays_sizes[i]=summer_raw_len;
		}
		
		if (g_strcmp0(word_str_lower,"summertime")==0) {
		word_arrays[i] = (unsigned char*)malloc(summertime_raw_len * sizeof(unsigned char));
		word_arrays[i] = summertime_raw;
		word_arrays_sizes[i]=summertime_raw_len;
		}
		
	    
	    //T words
	     if (g_strcmp0(word_str_lower,"talk")==0) {
		word_arrays[i] = (unsigned char*)malloc(talk_raw_len * sizeof(unsigned char));
		word_arrays[i] = talk_raw;
		word_arrays_sizes[i]=talk_raw_len;	
	    }
	    
	     if (g_strcmp0(word_str_lower,"talking")==0) {
		word_arrays[i] = (unsigned char*)malloc(talking_raw_len * sizeof(unsigned char));
		word_arrays[i] = talking_raw;
		word_arrays_sizes[i]=talking_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"task")==0) {
		word_arrays[i] = (unsigned char*)malloc(task_raw_len * sizeof(unsigned char));
		word_arrays[i] = task_raw;
		word_arrays_sizes[i]=task_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"tax")==0) {
		word_arrays[i] = (unsigned char*)malloc(tax_raw_len * sizeof(unsigned char));
		word_arrays[i] = tax_raw;
		word_arrays_sizes[i]=tax_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"team")==0) {
		word_arrays[i] = (unsigned char*)malloc(team_raw_len * sizeof(unsigned char));
		word_arrays[i] = team_raw;
		word_arrays_sizes[i]=team_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"television")==0) {		
		word_arrays[i] = (unsigned char*)malloc(television_raw_len * sizeof(unsigned char));
		word_arrays[i] = television_raw;
		word_arrays_sizes[i]=television_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"thankyou")==0) {
		word_arrays[i] = (unsigned char*)malloc(thankyou_raw_len * sizeof(unsigned char));
		word_arrays[i] = thankyou_raw;
		word_arrays_sizes[i]=thankyou_raw_len;	
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
	    
	    if (g_strcmp0(word_str_lower,"then")==0) {		
		word_arrays[i] = (unsigned char*)malloc(then_raw_len * sizeof(unsigned char));
		word_arrays[i] = then_raw;
		word_arrays_sizes[i]=then_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"time")==0) {		
		word_arrays[i] = (unsigned char*)malloc(time_raw_len * sizeof(unsigned char));
		word_arrays[i] = time_raw;
		word_arrays_sizes[i]=time_raw_len;	
	    }
	    
	     if (g_strcmp0(word_str_lower,"to")==0) {
		word_arrays[i] = (unsigned char*)malloc(to_raw_len * sizeof(unsigned char));
		word_arrays[i] = to_raw;
		word_arrays_sizes[i]=to_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"today")==0) {
		word_arrays[i] = (unsigned char*)malloc(today_raw_len * sizeof(unsigned char));
		word_arrays[i] = today_raw;
		word_arrays_sizes[i]=today_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"todo")==0) {
		word_arrays[i] = (unsigned char*)malloc(todo_raw_len * sizeof(unsigned char));
		word_arrays[i] = todo_raw;
		word_arrays_sizes[i]=todo_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"tommorrow")==0) {
		word_arrays[i] = (unsigned char*)malloc(tommorrow_raw_len * sizeof(unsigned char));
		word_arrays[i] = tommorrow_raw;
		word_arrays_sizes[i]=tommorrow_raw_len;	
	    }	    
	    if (g_strcmp0(word_str_lower,"travel")==0) {
		word_arrays[i] = (unsigned char*)malloc(travel_raw_len * sizeof(unsigned char));
		word_arrays[i] = travel_raw;
		word_arrays_sizes[i]=travel_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"tv")==0) {
		word_arrays[i] = (unsigned char*)malloc(tv_raw_len * sizeof(unsigned char));
		word_arrays[i] = tv_raw;
		word_arrays_sizes[i]=tv_raw_len;	
	    }
	    
	    //U words	
	    
	     if (g_strcmp0(word_str_lower,"uncle")==0) {
		word_arrays[i] = (unsigned char*)malloc(uncle_raw_len * sizeof(unsigned char));
		word_arrays[i] = uncle_raw;
		word_arrays_sizes[i]=uncle_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"unknown")==0) {
		word_arrays[i] = (unsigned char*)malloc(unknown_raw_len * sizeof(unsigned char));
		word_arrays[i] = unknown_raw;
		word_arrays_sizes[i]=unknown_raw_len;
	    }	  
	    	    
	    if (g_strcmp0(word_str_lower,"upcoming")==0) {
		word_arrays[i] = (unsigned char*)malloc(upcoming_raw_len * sizeof(unsigned char));
		word_arrays[i] = upcoming_raw;
		word_arrays_sizes[i]=upcoming_raw_len;
	    }	
	    
	    //V words
	    if (g_strcmp0(word_str_lower,"valentine")==0) {
		word_arrays[i] = (unsigned char*)malloc(valentine_raw_len * sizeof(unsigned char));
		word_arrays[i] = valentine_raw;
		word_arrays_sizes[i]=valentine_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"version")==0) {
		word_arrays[i] = (unsigned char*)malloc(version_raw_len * sizeof(unsigned char));
		word_arrays[i] = version_raw;
		word_arrays_sizes[i]=version_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"visit")==0) {
		word_arrays[i] = (unsigned char*)malloc(visit_raw_len * sizeof(unsigned char));
		word_arrays[i] = visit_raw;
		word_arrays_sizes[i]=visit_raw_len;	
	    }
	    //W words
	     if (g_strcmp0(word_str_lower,"walk")==0) {
		word_arrays[i] = (unsigned char*)malloc(walk_raw_len * sizeof(unsigned char));
		word_arrays[i] = walk_raw;
		word_arrays_sizes[i]=walk_raw_len;	
	    }
	    
	      if (g_strcmp0(word_str_lower,"washing")==0) {
		word_arrays[i] = (unsigned char*)malloc(washing_raw_len * sizeof(unsigned char));
		word_arrays[i] = washing_raw;
		word_arrays_sizes[i]=washing_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"wedding")==0) {
		word_arrays[i] = (unsigned char*)malloc(wedding_raw_len * sizeof(unsigned char));
		word_arrays[i] = wedding_raw;
		word_arrays_sizes[i]=wedding_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"wife")==0) {
		word_arrays[i] = (unsigned char*)malloc(wife_raw_len * sizeof(unsigned char));
		word_arrays[i] = wife_raw;
		word_arrays_sizes[i]=wife_raw_len;	
	    }
	    
	     if (g_strcmp0(word_str_lower,"wifes")==0) {
		word_arrays[i] = (unsigned char*)malloc(wifes_raw_len * sizeof(unsigned char));
		word_arrays[i] = wifes_raw;
		word_arrays_sizes[i]=wifes_raw_len;	
	    }
	    
	     if (g_strcmp0(word_str_lower,"winter")==0) {
		word_arrays[i] = (unsigned char*)malloc(winter_raw_len * sizeof(unsigned char));
		word_arrays[i] = winter_raw;
		word_arrays_sizes[i]=winter_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"work")==0) {
		word_arrays[i] = (unsigned char*)malloc(work_raw_len * sizeof(unsigned char));
		word_arrays[i] = work_raw;
		word_arrays_sizes[i]=work_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"workshop")==0) {
		word_arrays[i] = (unsigned char*)malloc(workshop_raw_len * sizeof(unsigned char));
		word_arrays[i] = workshop_raw;
		word_arrays_sizes[i]=workshop_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"world")==0) {
		word_arrays[i] = (unsigned char*)malloc(world_raw_len * sizeof(unsigned char));
		word_arrays[i] = world_raw;
		word_arrays_sizes[i]=world_raw_len;	
	    }
	     //Y words
	    if (g_strcmp0(word_str_lower,"year")==0) {
		word_arrays[i] = (unsigned char*)malloc(year_raw_len * sizeof(unsigned char));		
		word_arrays[i] = year_raw;
		word_arrays_sizes[i]=year_raw_len;	
	    }	
	    
	     if (g_strcmp0(word_str_lower,"you")==0) {
		word_arrays[i] = (unsigned char*)malloc(you_raw_len * sizeof(unsigned char));		
		word_arrays[i] = you_raw;
		word_arrays_sizes[i]=you_raw_len;	
	    }	
	    //Z words
	    if (g_strcmp0(word_str_lower,"zero")==0) {
		word_arrays[i] = (unsigned char*)malloc(zero_raw_len * sizeof(unsigned char));		
		word_arrays[i] = zero_raw;
		word_arrays_sizes[i]=zero_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"zoo")==0) {
		word_arrays[i] = (unsigned char*)malloc(zoo_raw_len * sizeof(unsigned char));		
		word_arrays[i] = zoo_raw;
		word_arrays_sizes[i]=zoo_raw_len;	
	    }	
	    																													
	
	}//for

} //get word arrays

