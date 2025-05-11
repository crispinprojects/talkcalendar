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

//#include "robovoice.h"
//

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
				
		if (g_strcmp0(word_str_lower,"empty")==0) {		
		word_arrays[i] = (unsigned char*)malloc(empty_raw_len * sizeof(unsigned char));
		word_arrays[i] = empty_raw;		
		word_arrays_sizes[i]=empty_raw_len;
	    } 
		
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
	    //--------------------------------------------------------------
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
	    if (g_strcmp0(word_str_lower,"adventure")==0) {		
		word_arrays[i] = (unsigned char*)malloc(adventure_raw_len * sizeof(unsigned char));
		word_arrays[i] = adventure_raw;
		word_arrays_sizes[i]=adventure_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"afternoon")==0) {		
		word_arrays[i] = (unsigned char*)malloc(afternoon_raw_len * sizeof(unsigned char));
		word_arrays[i] = afternoon_raw;
		word_arrays_sizes[i]=afternoon_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"agree")==0) {	//agreement	
		word_arrays[i] = (unsigned char*)malloc(agree_raw_len * sizeof(unsigned char));
		word_arrays[i] = agree_raw;
		word_arrays_sizes[i]=agree_raw_len;	
	    }
	     if (g_strcmp0(word_str_lower,"alarm")==0) {		
		word_arrays[i] = (unsigned char*)malloc(alarm_raw_len * sizeof(unsigned char));
		word_arrays[i] = alarm_raw;
		word_arrays_sizes[i]=alarm_raw_len;
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
	    if (g_strcmp0(word_str_lower,"amazon")==0) {		
		word_arrays[i] = (unsigned char*)malloc(amazon_raw_len * sizeof(unsigned char));
		word_arrays[i] = amazon_raw;
		word_arrays_sizes[i]=amazon_raw_len;
	    }
	    
	    if (g_strcmp0(word_str_lower,"ambulance")==0) {		
		word_arrays[i] = (unsigned char*)malloc(ambulance_raw_len * sizeof(unsigned char));
		word_arrays[i] = ambulance_raw;
		word_arrays_sizes[i]=ambulance_raw_len;
	    }	   
	    if (g_strcmp0(word_str_lower,"amm")==0) {		
		word_arrays[i] = (unsigned char*)malloc(amm_raw_len * sizeof(unsigned char));
		word_arrays[i] = amm_raw;
		word_arrays_sizes[i]=amm_raw_len;
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
	    if (g_strcmp0(word_str_lower,"archery")==0) {		
		word_arrays[i] = (unsigned char*)malloc(archery_raw_len * sizeof(unsigned char));
		word_arrays[i] = archery_raw;
		word_arrays_sizes[i]=archery_raw_len;	
	    }	
	    if (g_strcmp0(word_str_lower,"art")==0) {		
		word_arrays[i] = (unsigned char*)malloc(art_raw_len * sizeof(unsigned char));
		word_arrays[i] = art_raw;
		word_arrays_sizes[i]=art_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"assessment")==0) {		
		word_arrays[i] = (unsigned char*)malloc(assessment_raw_len * sizeof(unsigned char));
		word_arrays[i] = assessment_raw;
		word_arrays_sizes[i]=assessment_raw_len;	
	    }		
	    if (g_strcmp0(word_str_lower,"aunt")==0) {		
		word_arrays[i] = (unsigned char*)malloc(aunt_raw_len * sizeof(unsigned char));
		word_arrays[i] = aunt_raw;
		word_arrays_sizes[i]=aunt_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"auntie")==0) {		
		word_arrays[i] = (unsigned char*)malloc(auntie_raw_len * sizeof(unsigned char));
		word_arrays[i] = auntie_raw;
		word_arrays_sizes[i]=auntie_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"autumn")==0) {		
		word_arrays[i] = (unsigned char*)malloc(autumn_raw_len * sizeof(unsigned char));
		word_arrays[i] = autumn_raw;
		word_arrays_sizes[i]=autumn_raw_len;	
	    }		
	    
	    //--------------------------------------------------------------
	    //B words
	    if (g_strcmp0(word_str_lower,"baby")==0) {		
		word_arrays[i] = (unsigned char*)malloc(baby_raw_len * sizeof(unsigned char));
		word_arrays[i] = baby_raw;
		word_arrays_sizes[i]=baby_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"badminton")==0) {		
		word_arrays[i] = (unsigned char*)malloc(badminton_raw_len * sizeof(unsigned char));
		word_arrays[i] = badminton_raw;
		word_arrays_sizes[i]=badminton_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"band")==0) {		
		word_arrays[i] = (unsigned char*)malloc(band_raw_len * sizeof(unsigned char));
		word_arrays[i] = band_raw;
		word_arrays_sizes[i]=band_raw_len;	
	    }
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
	     if (g_strcmp0(word_str_lower,"bed")==0) {		
		word_arrays[i] = (unsigned char*)malloc(bed_raw_len * sizeof(unsigned char));
		word_arrays[i] = bed_raw;
		word_arrays_sizes[i]=bed_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"begins")==0) {		
		word_arrays[i] = (unsigned char*)malloc(begins_raw_len * sizeof(unsigned char));
		word_arrays[i] = begins_raw;
		word_arrays_sizes[i]=begins_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"big")==0) {		
		word_arrays[i] = (unsigned char*)malloc(big_raw_len * sizeof(unsigned char));
		word_arrays[i] = big_raw;
		word_arrays_sizes[i]=big_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"bike")==0) {		
		word_arrays[i] = (unsigned char*)malloc(bike_raw_len * sizeof(unsigned char));
		word_arrays[i] = bike_raw;
		word_arrays_sizes[i]=bike_raw_len;	
	    }
	     if (g_strcmp0(word_str_lower,"bird")==0) {
		word_arrays[i] = (unsigned char*)malloc(bird_raw_len * sizeof(unsigned char));		
		word_arrays[i] = bird_raw;
		word_arrays_sizes[i]=bird_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"birth")==0) {		
		word_arrays[i] = (unsigned char*)malloc(birth_raw_len * sizeof(unsigned char));
		word_arrays[i] = birth_raw;
		word_arrays_sizes[i]=birth_raw_len;	
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
	    if (g_strcmp0(word_str_lower,"bowls")==0) {		
		word_arrays[i] = (unsigned char*)malloc(bowls_raw_len * sizeof(unsigned char));
		word_arrays[i] = bowls_raw;
		word_arrays_sizes[i]=bowls_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"box")==0) {		
		word_arrays[i] = (unsigned char*)malloc(box_raw_len * sizeof(unsigned char));
		word_arrays[i] = box_raw;
		word_arrays_sizes[i]=box_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"boxing")==0) {		
		word_arrays[i] = (unsigned char*)malloc(boxing_raw_len * sizeof(unsigned char));
		word_arrays[i] = boxing_raw;
		word_arrays_sizes[i]=boxing_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"boy")==0) {		
		word_arrays[i] = (unsigned char*)malloc(boy_raw_len * sizeof(unsigned char));
		word_arrays[i] = boy_raw;
		word_arrays_sizes[i]=boy_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"break")==0) {		
		word_arrays[i] = (unsigned char*)malloc(break_raw_len * sizeof(unsigned char));
		word_arrays[i] = break_raw;
		word_arrays_sizes[i]=break_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"breakfast")==0) {		
		word_arrays[i] = (unsigned char*)malloc(breakfast_raw_len * sizeof(unsigned char));
		word_arrays[i] = breakfast_raw;
		word_arrays_sizes[i]=breakfast_raw_len;	
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
	    if (g_strcmp0(word_str_lower,"brunch")==0) {		
		word_arrays[i] = (unsigned char*)malloc(brunch_raw_len * sizeof(unsigned char));
		word_arrays[i] = brunch_raw;
		word_arrays_sizes[i]=brunch_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"bus")==0) {		
		word_arrays[i] = (unsigned char*)malloc(bus_raw_len * sizeof(unsigned char));
		word_arrays[i] = bus_raw;
		word_arrays_sizes[i]=bus_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"business")==0) {		
		word_arrays[i] = (unsigned char*)malloc(business_raw_len * sizeof(unsigned char));
		word_arrays[i] = business_raw;
		word_arrays_sizes[i]=business_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"busy")==0) {		
		word_arrays[i] = (unsigned char*)malloc(busy_raw_len * sizeof(unsigned char));
		word_arrays[i] = busy_raw;
		word_arrays_sizes[i]=busy_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"by")==0) {		
		word_arrays[i] = (unsigned char*)malloc(by_raw_len * sizeof(unsigned char));
		word_arrays[i] = by_raw;
		word_arrays_sizes[i]=by_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"bye")==0) {		
		word_arrays[i] = (unsigned char*)malloc(bye_raw_len * sizeof(unsigned char));
		word_arrays[i] = bye_raw;
		word_arrays_sizes[i]=bye_raw_len;	
	    }
	    
	    //--------------------------------------------------------------		
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
	    if (g_strcmp0(word_str_lower,"camp")==0) {		
		word_arrays[i] = (unsigned char*)malloc(camp_raw_len * sizeof(unsigned char));
		word_arrays[i] = camp_raw;
		word_arrays_sizes[i]=camp_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"camping")==0) {		
		word_arrays[i] = (unsigned char*)malloc(camping_raw_len * sizeof(unsigned char));
		word_arrays[i] = camping_raw;
		word_arrays_sizes[i]=camping_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"campus")==0) {		
		word_arrays[i] = (unsigned char*)malloc(campus_raw_len * sizeof(unsigned char));
		word_arrays[i] = campus_raw;
		word_arrays_sizes[i]=campus_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"car")==0) {		
		word_arrays[i] = (unsigned char*)malloc(car_raw_len * sizeof(unsigned char));
		word_arrays[i] = car_raw;
		word_arrays_sizes[i]=car_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"card")==0) {		
		word_arrays[i] = (unsigned char*)malloc(card_raw_len * sizeof(unsigned char));
		word_arrays[i] = card_raw;
		word_arrays_sizes[i]=card_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"care")==0) {		
		word_arrays[i] = (unsigned char*)malloc(care_raw_len * sizeof(unsigned char));
		word_arrays[i] = care_raw;
		word_arrays_sizes[i]=care_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"cat")==0) {		
		word_arrays[i] = (unsigned char*)malloc(cat_raw_len * sizeof(unsigned char));
		word_arrays[i] = cat_raw;
		word_arrays_sizes[i]=cat_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"celebration")==0) {		
		word_arrays[i] = (unsigned char*)malloc(celebration_raw_len * sizeof(unsigned char));
		word_arrays[i] = celebration_raw;
		word_arrays_sizes[i]=celebration_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"certificate")==0) {		
		word_arrays[i] = (unsigned char*)malloc(certificate_raw_len * sizeof(unsigned char));
		word_arrays[i] = certificate_raw;
		word_arrays_sizes[i]=certificate_raw_len;	
	    }
	     if (g_strcmp0(word_str_lower,"chat")==0) {		
		word_arrays[i] = (unsigned char*)malloc(chat_raw_len * sizeof(unsigned char));
		word_arrays[i] = chat_raw;
		word_arrays_sizes[i]=chat_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"chauffeur")==0) {		
		word_arrays[i] = (unsigned char*)malloc(chauffeur_raw_len * sizeof(unsigned char));
		word_arrays[i] = chauffeur_raw;
		word_arrays_sizes[i]=chauffeur_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"chemist")==0) {		
		word_arrays[i] = (unsigned char*)malloc(chemist_raw_len * sizeof(unsigned char));
		word_arrays[i] = chemist_raw;
		word_arrays_sizes[i]=chemist_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"child")==0) {		
		word_arrays[i] = (unsigned char*)malloc(child_raw_len * sizeof(unsigned char));
		word_arrays[i] = child_raw;
		word_arrays_sizes[i]=child_raw_len;	
	    }	 	
	    if (g_strcmp0(word_str_lower,"children")==0) {		
		word_arrays[i] = (unsigned char*)malloc(children_raw_len * sizeof(unsigned char));
		word_arrays[i] = children_raw;
		word_arrays_sizes[i]=children_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"chips")==0) {		
		word_arrays[i] = (unsigned char*)malloc(chips_raw_len * sizeof(unsigned char));
		word_arrays[i] = chips_raw;
		word_arrays_sizes[i]=chips_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"choir")==0) {		
		word_arrays[i] = (unsigned char*)malloc(choir_raw_len * sizeof(unsigned char));
		word_arrays[i] = choir_raw;
		word_arrays_sizes[i]=choir_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"chore")==0) {		
		word_arrays[i] = (unsigned char*)malloc(chore_raw_len * sizeof(unsigned char));
		word_arrays[i] = chore_raw;
		word_arrays_sizes[i]=chore_raw_len;	
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
	    if (g_strcmp0(word_str_lower,"circle")==0) {		
		word_arrays[i] = (unsigned char*)malloc(circle_raw_len * sizeof(unsigned char));
		word_arrays[i] = circle_raw;
		word_arrays_sizes[i]=circle_raw_len;	
	    }	    
	    if (g_strcmp0(word_str_lower,"city")==0) {		
		word_arrays[i] = (unsigned char*)malloc(city_raw_len * sizeof(unsigned char));
		word_arrays[i] = city_raw;
		word_arrays_sizes[i]=city_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"class")==0) {		
		word_arrays[i] = (unsigned char*)malloc(class_raw_len * sizeof(unsigned char));
		word_arrays[i] = class_raw;
		word_arrays_sizes[i]=class_raw_len;	
	    }
	     if (g_strcmp0(word_str_lower,"climbing")==0) {		
		word_arrays[i] = (unsigned char*)malloc(climbing_raw_len * sizeof(unsigned char));
		word_arrays[i] = climbing_raw;
		word_arrays_sizes[i]=climbing_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"clinic")==0) {		
		word_arrays[i] = (unsigned char*)malloc(clinic_raw_len * sizeof(unsigned char));
		word_arrays[i] = clinic_raw;
		word_arrays_sizes[i]=clinic_raw_len;	
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
	     if (g_strcmp0(word_str_lower,"close")==0) {		
		word_arrays[i] = (unsigned char*)malloc(close_raw_len * sizeof(unsigned char));
		word_arrays[i] = close_raw;
		word_arrays_sizes[i]=close_raw_len;	
	    }	
	     if (g_strcmp0(word_str_lower,"club")==0) {		
		word_arrays[i] = (unsigned char*)malloc(club_raw_len * sizeof(unsigned char));
		word_arrays[i] = club_raw;
		word_arrays_sizes[i]=club_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"coach")==0) {		
		word_arrays[i] = (unsigned char*)malloc(coach_raw_len * sizeof(unsigned char));
		word_arrays[i] = coach_raw;
		word_arrays_sizes[i]=coach_raw_len;	
	    }
	     if (g_strcmp0(word_str_lower,"coast")==0) {		
		word_arrays[i] = (unsigned char*)malloc(coast_raw_len * sizeof(unsigned char));
		word_arrays[i] = coast_raw;
		word_arrays_sizes[i]=coast_raw_len;	
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
	    if (g_strcmp0(word_str_lower,"coffee")==0) {		
		word_arrays[i] = (unsigned char*)malloc(coffee_raw_len * sizeof(unsigned char));
		word_arrays[i] = coffee_raw;
		word_arrays_sizes[i]=coffee_raw_len;	
	    }
	     if (g_strcmp0(word_str_lower,"collection")==0) {		
		word_arrays[i] = (unsigned char*)malloc(collection_raw_len * sizeof(unsigned char));
		word_arrays[i] = collection_raw;
		word_arrays_sizes[i]=collection_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"college")==0) {		
		word_arrays[i] = (unsigned char*)malloc(college_raw_len * sizeof(unsigned char));
		word_arrays[i] = college_raw;
		word_arrays_sizes[i]=college_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"coming")==0) {		
		word_arrays[i] = (unsigned char*)malloc(coming_raw_len * sizeof(unsigned char));
		word_arrays[i] = coming_raw;
		word_arrays_sizes[i]=coming_raw_len;	
	    }				    
	    if (g_strcmp0(word_str_lower,"computer")==0) {		
		word_arrays[i] = (unsigned char*)malloc(computer_raw_len * sizeof(unsigned char));
		word_arrays[i] = computer_raw;
		word_arrays_sizes[i]=computer_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"concert")==0) {		
		word_arrays[i] = (unsigned char*)malloc(concert_raw_len * sizeof(unsigned char));
		word_arrays[i] = concert_raw;
		word_arrays_sizes[i]=concert_raw_len;	
	    }		    
	    if (g_strcmp0(word_str_lower,"contact")==0) {		
		word_arrays[i] = (unsigned char*)malloc(contact_raw_len * sizeof(unsigned char));
		word_arrays[i] = contact_raw;
		word_arrays_sizes[i]=contact_raw_len;	
	    }
	     if (g_strcmp0(word_str_lower,"cottage")==0) {		
		word_arrays[i] = (unsigned char*)malloc(cottage_raw_len * sizeof(unsigned char));
		word_arrays[i] = cottage_raw;
		word_arrays_sizes[i]=cottage_raw_len;	
	    }		    
	    if (g_strcmp0(word_str_lower,"cousin")==0) {		
		word_arrays[i] = (unsigned char*)malloc(cousin_raw_len * sizeof(unsigned char));
		word_arrays[i] = cousin_raw;
		word_arrays_sizes[i]=cousin_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"crispin")==0) {		
		word_arrays[i] = (unsigned char*)malloc(crispin_raw_len * sizeof(unsigned char));
		word_arrays[i] = crispin_raw;
		word_arrays_sizes[i]=crispin_raw_len;	
	    }	    
	    if (g_strcmp0(word_str_lower,"crispins")==0) {		
		word_arrays[i] = (unsigned char*)malloc(crispins_raw_len * sizeof(unsigned char));
		word_arrays[i] = crispins_raw;
		word_arrays_sizes[i]=crispins_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"crook")==0) {		
		word_arrays[i] = (unsigned char*)malloc(crook_raw_len * sizeof(unsigned char));
		word_arrays[i] = crook_raw;
		word_arrays_sizes[i]=crook_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"cycle")==0) {		
		word_arrays[i] = (unsigned char*)malloc(cycle_raw_len * sizeof(unsigned char));
		word_arrays[i] = cycle_raw;
		word_arrays_sizes[i]=cycle_raw_len;	
	    }
	    //--------------------------------------------------------------
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
	    if (g_strcmp0(word_str_lower,"dance")==0) {		
		word_arrays[i] = (unsigned char*)malloc(dance_raw_len * sizeof(unsigned char));
		word_arrays[i] = dance_raw;
		word_arrays_sizes[i]=dance_raw_len;
	    }
	    if (g_strcmp0(word_str_lower,"date")==0) {		
		word_arrays[i] = (unsigned char*)malloc(date_raw_len * sizeof(unsigned char));
		word_arrays[i] = date_raw;
		word_arrays_sizes[i]=date_raw_len;
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
	       
	    if (g_strcmp0(word_str_lower,"day")==0) {		
		word_arrays[i] = (unsigned char*)malloc(day_raw_len * sizeof(unsigned char));
		word_arrays[i] = day_raw;
		word_arrays_sizes[i]=day_raw_len;
	    }
	    if (g_strcmp0(word_str_lower,"days")==0) {		
		word_arrays[i] = (unsigned char*)malloc(days_raw_len * sizeof(unsigned char));
		word_arrays[i] = days_raw;
		word_arrays_sizes[i]=days_raw_len;
	    }
	    if (g_strcmp0(word_str_lower,"dead")==0) {		
		word_arrays[i] = (unsigned char*)malloc(dead_raw_len * sizeof(unsigned char));
		word_arrays[i] = dead_raw;
		word_arrays_sizes[i]=dead_raw_len;
	    }	    
	    if (g_strcmp0(word_str_lower,"deadline")==0) {		
		word_arrays[i] = (unsigned char*)malloc(deadline_raw_len * sizeof(unsigned char));
		word_arrays[i] = deadline_raw;
		word_arrays_sizes[i]=deadline_raw_len;
	    }
	    if (g_strcmp0(word_str_lower,"death")==0) {		
		word_arrays[i] = (unsigned char*)malloc(death_raw_len * sizeof(unsigned char));
		word_arrays[i] = death_raw;
		word_arrays_sizes[i]=death_raw_len;
	    }
	    if (g_strcmp0(word_str_lower,"decorate")==0) {		
		word_arrays[i] = (unsigned char*)malloc(decorate_raw_len * sizeof(unsigned char));
		word_arrays[i] = decorate_raw;
		word_arrays_sizes[i]=decorate_raw_len;
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
	    if (g_strcmp0(word_str_lower,"dinner")==0) {		
		word_arrays[i] = (unsigned char*)malloc(dinner_raw_len * sizeof(unsigned char));
		word_arrays[i] = dinner_raw;
		word_arrays_sizes[i]=dinner_raw_len;
	    }
	    if (g_strcmp0(word_str_lower,"do")==0) {		
		word_arrays[i] = (unsigned char*)malloc(do_raw_len * sizeof(unsigned char));
		word_arrays[i] = do_raw;
		word_arrays_sizes[i]=do_raw_len;
	    }	  	  	    
	    if (g_strcmp0(word_str_lower,"doctor")==0) {		
		word_arrays[i] = (unsigned char*)malloc(doctor_raw_len * sizeof(unsigned char));
		word_arrays[i] = doctor_raw;
		word_arrays_sizes[i]=doctor_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"dog")==0) {		
		word_arrays[i] = (unsigned char*)malloc(dog_raw_len * sizeof(unsigned char));
		word_arrays[i] = dog_raw;
		word_arrays_sizes[i]=dog_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"down")==0) {		
		word_arrays[i] = (unsigned char*)malloc(down_raw_len * sizeof(unsigned char));
		word_arrays[i] = down_raw;
		word_arrays_sizes[i]=down_raw_len;
	    }	  
	    if (g_strcmp0(word_str_lower,"driver")==0) {		
		word_arrays[i] = (unsigned char*)malloc(driver_raw_len * sizeof(unsigned char));
		word_arrays[i] = driver_raw;
		word_arrays_sizes[i]=driver_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"dustbin")==0) {		
		word_arrays[i] = (unsigned char*)malloc(dustbin_raw_len * sizeof(unsigned char));
		word_arrays[i] = dustbin_raw;
		word_arrays_sizes[i]=dustbin_raw_len;	
	    }
	    //--------------------------------------------------------------
	    // E words
	    if (g_strcmp0(word_str_lower,"ear")==0) {		
		word_arrays[i] = (unsigned char*)malloc(ear_raw_len * sizeof(unsigned char));
		word_arrays[i] = ear_raw;
		word_arrays_sizes[i]=ear_raw_len;
	    }	
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
	    if (g_strcmp0(word_str_lower,"electricity")==0) {		
		word_arrays[i] = (unsigned char*)malloc(electricity_raw_len * sizeof(unsigned char));
		word_arrays[i] = electricity_raw;
		word_arrays_sizes[i]=electricity_raw_len;
	    }	    
	    if (g_strcmp0(word_str_lower,"ends")==0) {		
		word_arrays[i] = (unsigned char*)malloc(ends_raw_len * sizeof(unsigned char));
		word_arrays[i] = ends_raw;
		word_arrays_sizes[i]=ends_raw_len;
	    }
	    if (g_strcmp0(word_str_lower,"engage")==0) {	//engage + ment	
		word_arrays[i] = (unsigned char*)malloc(engage_raw_len * sizeof(unsigned char));
		word_arrays[i] = engage_raw;
		word_arrays_sizes[i]=engage_raw_len;
	    }
	    if (g_strcmp0(word_str_lower,"engineer")==0) {	//engage + ment	
		word_arrays[i] = (unsigned char*)malloc(engineer_raw_len * sizeof(unsigned char));
		word_arrays[i] = engineer_raw;
		word_arrays_sizes[i]=engineer_raw_len;
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
	     if (g_strcmp0(word_str_lower,"excursion")==0) {		
		word_arrays[i] = (unsigned char*)malloc(excursion_raw_len * sizeof(unsigned char));
		word_arrays[i] = excursion_raw;
		word_arrays_sizes[i]=excursion_raw_len;
	    }
	    //--------------------------------------------------------------
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
	    if (g_strcmp0(word_str_lower,"fawkes")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fawkes_raw_len * sizeof(unsigned char));
		word_arrays[i] = fawkes_raw;
		word_arrays_sizes[i]=fawkes_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"fear")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fear_raw_len * sizeof(unsigned char));
		word_arrays[i] = fear_raw;
		word_arrays_sizes[i]=fear_raw_len;	
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
	    if (g_strcmp0(word_str_lower,"fire")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fire_raw_len * sizeof(unsigned char));
		word_arrays[i] = fire_raw;
		word_arrays_sizes[i]=fire_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"fish")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fish_raw_len * sizeof(unsigned char));
		word_arrays[i] = fish_raw;
		word_arrays_sizes[i]=fish_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"fishing")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fishing_raw_len * sizeof(unsigned char));
		word_arrays[i] = fishing_raw;
		word_arrays_sizes[i]=fishing_raw_len;	
	    }	
	    if (g_strcmp0(word_str_lower,"fitness")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fitness_raw_len * sizeof(unsigned char));
		word_arrays[i] = fitness_raw;
		word_arrays_sizes[i]=fitness_raw_len;	
	    }		
	    if (g_strcmp0(word_str_lower,"fix")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fix_raw_len * sizeof(unsigned char));
		word_arrays[i] = fix_raw;
		word_arrays_sizes[i]=fix_raw_len;	
	    }		
	    
	    if (g_strcmp0(word_str_lower,"food")==0) {		
		word_arrays[i] = (unsigned char*)malloc(food_raw_len * sizeof(unsigned char));
		word_arrays[i] = food_raw;
		word_arrays_sizes[i]=food_raw_len;	
	    }    
	    if (g_strcmp0(word_str_lower,"fools")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fools_raw_len * sizeof(unsigned char));
		word_arrays[i] = fools_raw;
		word_arrays_sizes[i]=fools_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"football")==0) {		
		word_arrays[i] = (unsigned char*)malloc(football_raw_len * sizeof(unsigned char));
		word_arrays[i] = football_raw;
		word_arrays_sizes[i]=football_raw_len;	
	    }	     
	    if (g_strcmp0(word_str_lower,"forward")==0) {		
		word_arrays[i] = (unsigned char*)malloc(forward_raw_len * sizeof(unsigned char));
		word_arrays[i] = forward_raw;
		word_arrays_sizes[i]=forward_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"frankenstein")==0) {		
		word_arrays[i] = (unsigned char*)malloc(frankenstein_raw_len * sizeof(unsigned char));
		word_arrays[i] = frankenstein_raw;
		word_arrays_sizes[i]=frankenstein_raw_len;	
	    }	
	    if (g_strcmp0(word_str_lower,"freeze")==0) {		
		word_arrays[i] = (unsigned char*)malloc(freeze_raw_len * sizeof(unsigned char));
		word_arrays[i] = freeze_raw;
		word_arrays_sizes[i]=freeze_raw_len;	
	    }	    
	    if (g_strcmp0(word_str_lower,"friend")==0) {		
		word_arrays[i] = (unsigned char*)malloc(friend_raw_len * sizeof(unsigned char));
		word_arrays[i] = friend_raw;
		word_arrays_sizes[i]=friend_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"frost")==0) {		
		word_arrays[i] = (unsigned char*)malloc(frost_raw_len * sizeof(unsigned char));
		word_arrays[i] = frost_raw;
		word_arrays_sizes[i]=frost_raw_len;	
	    }	    
	    if (g_strcmp0(word_str_lower,"funeral")==0) {
		g_print("funeral detected\n");		
		word_arrays[i] = (unsigned char*)malloc(funeral_raw_len  * sizeof(unsigned char));
		word_arrays[i] = funeral_raw;
		word_arrays_sizes[i]=funeral_raw_len;	
	    }
	   
	    //--------------------------------------------------------------
	    //G Words
	    
	    if (g_strcmp0(word_str_lower,"gallery")==0) {
		word_arrays[i] = (unsigned char*)malloc(gallery_raw_len * sizeof(unsigned char));
		word_arrays[i] = gallery_raw;
		word_arrays_sizes[i]=gallery_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"garage")==0) {
		word_arrays[i] = (unsigned char*)malloc(garage_raw_len * sizeof(unsigned char));
		word_arrays[i] = garage_raw;
		word_arrays_sizes[i]=garage_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"garbage")==0) {
		word_arrays[i] = (unsigned char*)malloc(garbage_raw_len * sizeof(unsigned char));
		word_arrays[i] = garbage_raw;
		word_arrays_sizes[i]=garbage_raw_len;	
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
	    if (g_strcmp0(word_str_lower,"gift")==0) { 
		word_arrays[i] = (unsigned char*)malloc(gift_raw_len * sizeof(unsigned char));
		word_arrays[i] = gift_raw;
		word_arrays_sizes[i]=gift_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"girl")==0) { //good + bye
		word_arrays[i] = (unsigned char*)malloc(girl_raw_len * sizeof(unsigned char));
		word_arrays[i] = girl_raw;
		word_arrays_sizes[i]=girl_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"go")==0) { //good + bye
		word_arrays[i] = (unsigned char*)malloc(go_raw_len * sizeof(unsigned char));
		word_arrays[i] = go_raw;
		word_arrays_sizes[i]=go_raw_len;	
	    }
	     if (g_strcmp0(word_str_lower,"golf")==0) { //good + bye
		word_arrays[i] = (unsigned char*)malloc(golf_raw_len * sizeof(unsigned char));
		word_arrays[i] = golf_raw;
		word_arrays_sizes[i]=golf_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"good")==0) { //good + bye
		word_arrays[i] = (unsigned char*)malloc(good_raw_len * sizeof(unsigned char));
		word_arrays[i] = good_raw;
		word_arrays_sizes[i]=good_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"grand")==0) {
		word_arrays[i] = (unsigned char*)malloc(grand_raw_len * sizeof(unsigned char));
		word_arrays[i] = grand_raw;
		word_arrays_sizes[i]=grand_raw_len;	
	    }	    
	    if (g_strcmp0(word_str_lower,"guy")==0) { //guy faukes
		word_arrays[i] = (unsigned char*)malloc(guy_raw_len * sizeof(unsigned char));
		word_arrays[i] = guy_raw;
		word_arrays_sizes[i]=guy_raw_len;	
	    }
	    //--------------------------------------------------------------	    
	    
	     //--------------------------------------------------------------			
	    //H words
	    	   	    
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
	    if (g_strcmp0(word_str_lower,"head")==0) {
		word_arrays[i] = (unsigned char*)malloc(head_raw_len * sizeof(unsigned char));
		word_arrays[i] = head_raw;
		word_arrays_sizes[i]=head_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"health")==0) {
		word_arrays[i] = (unsigned char*)malloc(health_raw_len * sizeof(unsigned char));
		word_arrays[i] = health_raw;
		word_arrays_sizes[i]=health_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"hear")==0) {
		word_arrays[i] = (unsigned char*)malloc(hear_raw_len * sizeof(unsigned char));
		word_arrays[i] = hear_raw;
		word_arrays_sizes[i]=hear_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"heating")==0) {
		word_arrays[i] = (unsigned char*)malloc(heating_raw_len * sizeof(unsigned char));
		word_arrays[i] = heating_raw;
		word_arrays_sizes[i]=heating_raw_len;	
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
	     if (g_strcmp0(word_str_lower,"hockey")==0) {
		word_arrays[i] = (unsigned char*)malloc(hockey_raw_len * sizeof(unsigned char));
		word_arrays[i] = hockey_raw;
		word_arrays_sizes[i]=hockey_raw_len;	
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
	    if (g_strcmp0(word_str_lower,"hotel")==0) {
		word_arrays[i] = (unsigned char*)malloc(hotel_raw_len * sizeof(unsigned char));
		word_arrays[i] = hotel_raw;
		word_arrays_sizes[i]=hotel_raw_len;	
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
	    if (g_strcmp0(word_str_lower,"humanoid")==0) {
		word_arrays[i] = (unsigned char*)malloc(humanoid_raw_len * sizeof(unsigned char));
		word_arrays[i] = humanoid_raw;
		word_arrays_sizes[i]=humanoid_raw_len;	
	    }	
	    if (g_strcmp0(word_str_lower,"husband")==0) {
		word_arrays[i] = (unsigned char*)malloc(husband_raw_len * sizeof(unsigned char));
		word_arrays[i] = husband_raw;
		word_arrays_sizes[i]=husband_raw_len;	
	    }	
	    //--------------------------------------------------------------
	    //i words
	    if (g_strcmp0(word_str_lower,"i")==0) {
		word_arrays[i] = (unsigned char*)malloc(i_raw_len * sizeof(unsigned char));
		word_arrays[i] = i_raw;
		word_arrays_sizes[i]=i_raw_len;	
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
	    if (g_strcmp0(word_str_lower,"information")==0) {
		word_arrays[i] = (unsigned char*)malloc(information_raw_len * sizeof(unsigned char));
		word_arrays[i] = information_raw;
		word_arrays_sizes[i]=information_raw_len;	
	    }	 	    
	    if (g_strcmp0(word_str_lower,"insurance")==0) {
		word_arrays[i] = (unsigned char*)malloc(insurance_raw_len * sizeof(unsigned char));
		word_arrays[i] = insurance_raw;
		word_arrays_sizes[i]=insurance_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"interview")==0) {
		word_arrays[i] = (unsigned char*)malloc(interview_raw_len * sizeof(unsigned char));
		word_arrays[i] = interview_raw;
		word_arrays_sizes[i]=interview_raw_len;	
	    }		    
	    if (g_strcmp0(word_str_lower,"investment")==0) {
		word_arrays[i] = (unsigned char*)malloc(investment_raw_len * sizeof(unsigned char));
		word_arrays[i] = investment_raw;
		word_arrays_sizes[i]=investment_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"invoice")==0) {
		word_arrays[i] = (unsigned char*)malloc(invoice_raw_len * sizeof(unsigned char));
		word_arrays[i] = invoice_raw;
		word_arrays_sizes[i]=invoice_raw_len;	
	    }	    
	    if (g_strcmp0(word_str_lower,"is")==0) {
		word_arrays[i] = (unsigned char*)malloc(is_raw_len * sizeof(unsigned char));
		word_arrays[i] = is_raw;
		word_arrays_sizes[i]=is_raw_len;	
	    }
	    
	    //--------------------------------------------------------------
	    //J words
	    
	    if (g_strcmp0(word_str_lower,"jeweler")==0) {
		word_arrays[i] = (unsigned char*)malloc(jeweler_raw_len * sizeof(unsigned char));
		word_arrays[i] = jeweler_raw;
		word_arrays_sizes[i]=jeweler_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"journey")==0) {
		word_arrays[i] = (unsigned char*)malloc(journey_raw_len * sizeof(unsigned char));
		word_arrays[i] = journey_raw;
		word_arrays_sizes[i]=journey_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"joy")==0) {
		word_arrays[i] = (unsigned char*)malloc(joy_raw_len * sizeof(unsigned char));
		word_arrays[i] = joy_raw;
		word_arrays_sizes[i]=joy_raw_len;	
	    }
	     //--------------------------------------------------------------
	    //K words
	    if (g_strcmp0(word_str_lower,"king")==0) {
		word_arrays[i] = (unsigned char*)malloc(king_raw_len * sizeof(unsigned char));
		word_arrays[i] = king_raw;
		word_arrays_sizes[i]=king_raw_len;	
	    }
	    
	     //--------------------------------------------------------------
	    //L words
	    if (g_strcmp0(word_str_lower,"large")==0) {
		word_arrays[i] = (unsigned char*)malloc(large_raw_len * sizeof(unsigned char));
		word_arrays[i] = large_raw;
		word_arrays_sizes[i]=large_raw_len;	
	    }	    
	    if (g_strcmp0(word_str_lower,"last")==0) {
		word_arrays[i] = (unsigned char*)malloc(last_raw_len * sizeof(unsigned char));
		word_arrays[i] = last_raw;
		word_arrays_sizes[i]=last_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"lawyer")==0) {
		word_arrays[i] = (unsigned char*)malloc(lawyer_raw_len * sizeof(unsigned char));
		word_arrays[i] = lawyer_raw;
		word_arrays_sizes[i]=lawyer_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"leave")==0) {
		word_arrays[i] = (unsigned char*)malloc(leave_raw_len * sizeof(unsigned char));
		word_arrays[i] = leave_raw;
		word_arrays_sizes[i]=leave_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"leaving")==0) {
		word_arrays[i] = (unsigned char*)malloc(leaving_raw_len * sizeof(unsigned char));
		word_arrays[i] = leaving_raw;
		word_arrays_sizes[i]=leaving_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"lesson")==0) {
		word_arrays[i] = (unsigned char*)malloc(lesson_raw_len * sizeof(unsigned char));
		word_arrays[i] = lesson_raw;
		word_arrays_sizes[i]=lesson_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"line")==0) {
		word_arrays[i] = (unsigned char*)malloc(line_raw_len * sizeof(unsigned char));
		word_arrays[i] = line_raw;
		word_arrays_sizes[i]=line_raw_len;	
	    }
	     if (g_strcmp0(word_str_lower,"linux")==0) {
		word_arrays[i] = (unsigned char*)malloc(linux_raw_len * sizeof(unsigned char));
		word_arrays[i] = linux_raw;
		word_arrays_sizes[i]=linux_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"location")==0) {
		word_arrays[i] = (unsigned char*)malloc(location_raw_len * sizeof(unsigned char));
		word_arrays[i] = location_raw;
		word_arrays_sizes[i]=location_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"lock")==0) {
		word_arrays[i] = (unsigned char*)malloc(lock_raw_len * sizeof(unsigned char));
		word_arrays[i] = lock_raw;
		word_arrays_sizes[i]=lock_raw_len;	
	    }
	     if (g_strcmp0(word_str_lower,"lodge")==0) {
		word_arrays[i] = (unsigned char*)malloc(lodge_raw_len * sizeof(unsigned char));
		word_arrays[i] = lodge_raw;
		word_arrays_sizes[i]=lodge_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"look")==0) {
		word_arrays[i] = (unsigned char*)malloc(look_raw_len * sizeof(unsigned char));
		word_arrays[i] = look_raw;
		word_arrays_sizes[i]=look_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"low")==0) {
		word_arrays[i] = (unsigned char*)malloc(low_raw_len * sizeof(unsigned char));
		word_arrays[i] = low_raw;
		word_arrays_sizes[i]=low_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"lunch")==0) {
		word_arrays[i] = (unsigned char*)malloc(lunch_raw_len * sizeof(unsigned char));
		word_arrays[i] = lunch_raw;
		word_arrays_sizes[i]=lunch_raw_len;	
	    }
	    
	    //--------------------------------------------------------------
	    //M words
	    if (g_strcmp0(word_str_lower,"maintenance")==0) {
		word_arrays[i] = (unsigned char*)malloc(maintenance_raw_len * sizeof(unsigned char));
		word_arrays[i] = maintenance_raw;
		word_arrays_sizes[i]=maintenance_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"man")==0) {
		word_arrays[i] = (unsigned char*)malloc(man_raw_len * sizeof(unsigned char));
		word_arrays[i] = man_raw;
		word_arrays_sizes[i]=man_raw_len;	
	    }
	     if (g_strcmp0(word_str_lower,"management")==0) {
		word_arrays[i] = (unsigned char*)malloc(management_raw_len * sizeof(unsigned char));
		word_arrays[i] = management_raw;
		word_arrays_sizes[i]=management_raw_len;	
	    }			 
	    if (g_strcmp0(word_str_lower,"many")==0) {
		word_arrays[i] = (unsigned char*)malloc(many_raw_len * sizeof(unsigned char));
		word_arrays[i] = many_raw;
		word_arrays_sizes[i]=many_raw_len;	
	    }	    
	    if (g_strcmp0(word_str_lower,"marine")==0) {
		word_arrays[i] = (unsigned char*)malloc(marine_raw_len * sizeof(unsigned char));
		word_arrays[i] = marine_raw;
		word_arrays_sizes[i]=marine_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"market")==0) {
		word_arrays[i] = (unsigned char*)malloc(market_raw_len * sizeof(unsigned char));
		word_arrays[i] = market_raw;
		word_arrays_sizes[i]=market_raw_len;	
	    }	 
	    if (g_strcmp0(word_str_lower,"master")==0) {
		word_arrays[i] = (unsigned char*)malloc(master_raw_len * sizeof(unsigned char));
		word_arrays[i] = master_raw;
		word_arrays_sizes[i]=master_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"mat")==0) {
		word_arrays[i] = (unsigned char*)malloc(mat_raw_len * sizeof(unsigned char));
		word_arrays[i] = mat_raw;
		word_arrays_sizes[i]=mat_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"me")==0) {
		word_arrays[i] = (unsigned char*)malloc(me_raw_len * sizeof(unsigned char));
		word_arrays[i] = me_raw;
		word_arrays_sizes[i]=me_raw_len;	
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
	    if (g_strcmp0(word_str_lower,"meet")==0) {
		word_arrays[i] = (unsigned char*)malloc(meet_raw_len * sizeof(unsigned char));
		word_arrays[i] = meet_raw;
		word_arrays_sizes[i]=meet_raw_len;	
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
	    if (g_strcmp0(word_str_lower,"memorandum")==0) {		
		word_arrays[i] = (unsigned char*)malloc(memorandum_raw_len * sizeof(unsigned char));
		word_arrays[i] = memorandum_raw;
		word_arrays_sizes[i]=memorandum_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"message")==0) {
		word_arrays[i] = (unsigned char*)malloc(message_raw_len * sizeof(unsigned char));
		word_arrays[i] = message_raw;
		word_arrays_sizes[i]=message_raw_len;	
	    } 
	    if (g_strcmp0(word_str_lower,"mini")==0) {
		word_arrays[i] = (unsigned char*)malloc(mini_raw_len * sizeof(unsigned char));
		word_arrays[i] = mini_raw;
		word_arrays_sizes[i]=mini_raw_len;	
	    } 
	    if (g_strcmp0(word_str_lower,"monster")==0) {
		word_arrays[i] = (unsigned char*)malloc(monster_raw_len * sizeof(unsigned char));
		word_arrays[i] = monster_raw;
		word_arrays_sizes[i]=monster_raw_len;	
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
	    if (g_strcmp0(word_str_lower,"move")==0) {		
		word_arrays[i] = (unsigned char*)malloc(move_raw_len * sizeof(unsigned char));
		word_arrays[i] = move_raw;
		word_arrays_sizes[i]=move_raw_len;	
	    }
	   if (g_strcmp0(word_str_lower,"movie")==0) {		
		word_arrays[i] = (unsigned char*)malloc(movie_raw_len * sizeof(unsigned char));
		word_arrays[i] = movie_raw;
		word_arrays_sizes[i]=movie_raw_len;	
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
	    if (g_strcmp0(word_str_lower,"museum")==0) {		
		word_arrays[i] = (unsigned char*)malloc(museum_raw_len * sizeof(unsigned char));
		word_arrays[i] = museum_raw;
		word_arrays_sizes[i]=museum_raw_len;	
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
	    //--------------------------------------------------------------	    	    
	    //N words
	    if (g_strcmp0(word_str_lower,"name")==0) {
		word_arrays[i] = (unsigned char*)malloc(name_raw_len * sizeof(unsigned char));
		word_arrays[i] = name_raw;
		word_arrays_sizes[i]=name_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"names")==0) {
		word_arrays[i] = (unsigned char*)malloc(names_raw_len * sizeof(unsigned char));
		word_arrays[i] = names_raw;
		word_arrays_sizes[i]=names_raw_len;	
	    }		
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
	    if (g_strcmp0(word_str_lower,"netball")==0) {
		word_arrays[i] = (unsigned char*)malloc(netball_raw_len * sizeof(unsigned char));
		word_arrays[i] = netball_raw;
		word_arrays_sizes[i]=netball_raw_len;	
	    }	
	    if (g_strcmp0(word_str_lower,"netflix")==0) {
		word_arrays[i] = (unsigned char*)malloc(netflix_raw_len * sizeof(unsigned char));
		word_arrays[i] = netflix_raw;
		word_arrays_sizes[i]=netflix_raw_len;	
	    }		    
	    if (g_strcmp0(word_str_lower,"new")==0) {
		word_arrays[i] = (unsigned char*)malloc(new_raw_len * sizeof(unsigned char));
		word_arrays[i] = new_raw;
		word_arrays_sizes[i]=new_raw_len;	
	    }	    
	    if (g_strcmp0(word_str_lower,"news")==0) { //news + paper
		word_arrays[i] = (unsigned char*)malloc(news_raw_len * sizeof(unsigned char));
		word_arrays[i] = news_raw;
		word_arrays_sizes[i]=news_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"newspaper")==0) { //news + paper
		word_arrays[i] = (unsigned char*)malloc(newspaper_raw_len * sizeof(unsigned char));
		word_arrays[i] = newspaper_raw;
		word_arrays_sizes[i]=newspaper_raw_len;	
	    }	     
	    if (g_strcmp0(word_str_lower,"niece")==0) {
		word_arrays[i] = (unsigned char*)malloc(niece_raw_len * sizeof(unsigned char));
		word_arrays[i] = niece_raw;
		word_arrays_sizes[i]=niece_raw_len;	
	    }	    
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
	     if (g_strcmp0(word_str_lower,"not")==0) {
		word_arrays[i] = (unsigned char*)malloc(not_raw_len * sizeof(unsigned char));
		word_arrays[i] = not_raw;
		word_arrays_sizes[i]=not_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"notable")==0) {
		word_arrays[i] = (unsigned char*)malloc(notable_raw_len * sizeof(unsigned char));
		word_arrays[i] = notable_raw;
		word_arrays_sizes[i]=notable_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"nursery")==0) {
		word_arrays[i] = (unsigned char*)malloc(nursery_raw_len * sizeof(unsigned char));
		word_arrays[i] = nursery_raw;
		word_arrays_sizes[i]=nursery_raw_len;	
	    }
	    
	    //--------------------------------------------------------------
	    //o words
	    if (g_strcmp0(word_str_lower,"o")==0) {		
		word_arrays[i] = (unsigned char*)malloc(o_raw_len * sizeof(unsigned char));
		word_arrays[i] = o_raw;
		word_arrays_sizes[i]=o_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"of")==0) {		
		word_arrays[i] = (unsigned char*)malloc(of_raw_len * sizeof(unsigned char));
		word_arrays[i] = of_raw;
		word_arrays_sizes[i]=of_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"office")==0) {		
		word_arrays[i] = (unsigned char*)malloc(office_raw_len * sizeof(unsigned char));
		word_arrays[i] = office_raw;
		word_arrays_sizes[i]=office_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"on")==0) {		
		word_arrays[i] = (unsigned char*)malloc(on_raw_len * sizeof(unsigned char));
		word_arrays[i] = on_raw;
		word_arrays_sizes[i]=on_raw_len;	
	    }	     
	    if (g_strcmp0(word_str_lower,"online")==0) {	//on+line?	
		word_arrays[i] = (unsigned char*)malloc(online_raw_len * sizeof(unsigned char));
		word_arrays[i] = online_raw;
		word_arrays_sizes[i]=online_raw_len;	
	    }
	     if (g_strcmp0(word_str_lower,"open")==0) {		
		word_arrays[i] = (unsigned char*)malloc(open_raw_len * sizeof(unsigned char));
		word_arrays[i] = open_raw;
		word_arrays_sizes[i]=open_raw_len;	
	    }	
	    if (g_strcmp0(word_str_lower,"or")==0) {		
		word_arrays[i] = (unsigned char*)malloc(or_raw_len * sizeof(unsigned char));
		word_arrays[i] = or_raw;
		word_arrays_sizes[i]=or_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"orchestra")==0) {		
		word_arrays[i] = (unsigned char*)malloc(orchestra_raw_len * sizeof(unsigned char));
		word_arrays[i] = orchestra_raw;
		word_arrays_sizes[i]=orchestra_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"out")==0) {		
		word_arrays[i] = (unsigned char*)malloc(out_raw_len * sizeof(unsigned char));
		word_arrays[i] = out_raw;
		word_arrays_sizes[i]=out_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"over")==0) {		
		word_arrays[i] = (unsigned char*)malloc(over_raw_len * sizeof(unsigned char));
		word_arrays[i] = over_raw;
		word_arrays_sizes[i]=over_raw_len;	
	    }
	     if (g_strcmp0(word_str_lower,"own")==0) {		
		word_arrays[i] = (unsigned char*)malloc(own_raw_len * sizeof(unsigned char));
		word_arrays[i] = own_raw;
		word_arrays_sizes[i]=own_raw_len;	
	    }			 
	    
	    //--------------------------------------------------------------
	     //P words
	     
	    if (g_strcmp0(word_str_lower,"paper")==0) {		
		word_arrays[i] = (unsigned char*)malloc(paper_raw_len * sizeof(unsigned char));
		word_arrays[i] = paper_raw;
		word_arrays_sizes[i]=paper_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"parent")==0) {		
		word_arrays[i] = (unsigned char*)malloc(parent_raw_len * sizeof(unsigned char));
		word_arrays[i] = parent_raw;
		word_arrays_sizes[i]=parent_raw_len;	
	    }
	     if (g_strcmp0(word_str_lower,"parrot")==0) {
		word_arrays[i] = (unsigned char*)malloc(parrot_raw_len * sizeof(unsigned char));		
		word_arrays[i] = parrot_raw;
		word_arrays_sizes[i]=parrot_raw_len;	
	    }	    
	    if (g_strcmp0(word_str_lower,"party")==0) {		
		word_arrays[i] = (unsigned char*)malloc(party_raw_len * sizeof(unsigned char));
		word_arrays[i] = party_raw;
		word_arrays_sizes[i]=party_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"passport")==0) {		
		word_arrays[i] = (unsigned char*)malloc(passport_raw_len * sizeof(unsigned char));
		word_arrays[i] = passport_raw;
		word_arrays_sizes[i]=passport_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"pay")==0) {
		word_arrays[i] = (unsigned char*)malloc(pay_raw_len * sizeof(unsigned char));
		word_arrays[i] = pay_raw;
		word_arrays_sizes[i]=pay_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"paying")==0) {
		word_arrays[i] = (unsigned char*)malloc(paying_raw_len * sizeof(unsigned char));
		word_arrays[i] = paying_raw;
		word_arrays_sizes[i]=paying_raw_len;	
	    } 	 	
	    if (g_strcmp0(word_str_lower,"payment")==0) {
		word_arrays[i] = (unsigned char*)malloc(payment_raw_len * sizeof(unsigned char));
		word_arrays[i] = payment_raw;
		word_arrays_sizes[i]=payment_raw_len;	
	    }
	     
	    if (g_strcmp0(word_str_lower,"person")==0) {
		word_arrays[i] = (unsigned char*)malloc(person_raw_len * sizeof(unsigned char));
		word_arrays[i] = person_raw;
		word_arrays_sizes[i]=person_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"personal")==0) {
		word_arrays[i] = (unsigned char*)malloc(personal_raw_len * sizeof(unsigned char));
		word_arrays[i] = personal_raw;
		word_arrays_sizes[i]=personal_raw_len;	
	    } 	    
	    if (g_strcmp0(word_str_lower,"pension")==0) {
		word_arrays[i] = (unsigned char*)malloc(pension_raw_len * sizeof(unsigned char));
		word_arrays[i] = pension_raw;
		word_arrays_sizes[i]=pension_raw_len;	
	    } 
	    if (g_strcmp0(word_str_lower,"pet")==0) {
		word_arrays[i] = (unsigned char*)malloc(pet_raw_len * sizeof(unsigned char));
		word_arrays[i] = pet_raw;
		word_arrays_sizes[i]=pet_raw_len;	
	    } 	    
	    if (g_strcmp0(word_str_lower,"phone")==0) {
		word_arrays[i] = (unsigned char*)malloc(phone_raw_len * sizeof(unsigned char));
		word_arrays[i] = phone_raw;
		word_arrays_sizes[i]=phone_raw_len;	
	    } 
	      
	    if (g_strcmp0(word_str_lower,"picture")==0) {		
		word_arrays[i] = (unsigned char*)malloc(picture_raw_len * sizeof(unsigned char));
		word_arrays[i] = picture_raw;
		word_arrays_sizes[i]=picture_raw_len;	
	    }	      
	    if (g_strcmp0(word_str_lower,"pictures")==0) {		
		word_arrays[i] = (unsigned char*)malloc(pictures_raw_len * sizeof(unsigned char));
		word_arrays[i] = pictures_raw;
		word_arrays_sizes[i]=pictures_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"pilates")==0) {		
		word_arrays[i] = (unsigned char*)malloc(pilates_raw_len * sizeof(unsigned char));
		word_arrays[i] = pilates_raw;
		word_arrays_sizes[i]=pilates_raw_len;	
	    }	  	    	      
	    if (g_strcmp0(word_str_lower,"place")==0) {		
		word_arrays[i] = (unsigned char*)malloc(place_raw_len * sizeof(unsigned char));
		word_arrays[i] = place_raw;
		word_arrays_sizes[i]=place_raw_len;	
	    }	    
	    if (g_strcmp0(word_str_lower,"pmm")==0) {
		word_arrays[i] = (unsigned char*)malloc(pmm_raw_len * sizeof(unsigned char));
		word_arrays[i] = pmm_raw;
		word_arrays_sizes[i]=pmm_raw_len;
	    }
	    if (g_strcmp0(word_str_lower,"point")==0) { //trans+port
		word_arrays[i] = (unsigned char*)malloc(point_raw_len * sizeof(unsigned char));
		word_arrays[i] = point_raw;
		word_arrays_sizes[i]=point_raw_len;
	    }
	    if (g_strcmp0(word_str_lower,"pope")==0) { //trans+port
		word_arrays[i] = (unsigned char*)malloc(pope_raw_len * sizeof(unsigned char));
		word_arrays[i] = pope_raw;
		word_arrays_sizes[i]=pope_raw_len;
	    }
	    if (g_strcmp0(word_str_lower,"port")==0) { //trans+port
		word_arrays[i] = (unsigned char*)malloc(port_raw_len * sizeof(unsigned char));
		word_arrays[i] = port_raw;
		word_arrays_sizes[i]=port_raw_len;
	    }
	    if (g_strcmp0(word_str_lower,"post")==0) { //post+office
		word_arrays[i] = (unsigned char*)malloc(post_raw_len * sizeof(unsigned char));
		word_arrays[i] = post_raw;
		word_arrays_sizes[i]=post_raw_len;
	    }
	    
	    if (g_strcmp0(word_str_lower,"practice")==0) {
		word_arrays[i] = (unsigned char*)malloc(practice_raw_len * sizeof(unsigned char));
		word_arrays[i] = practice_raw;
		word_arrays_sizes[i]=practice_raw_len;
	    }
	    
	    if (g_strcmp0(word_str_lower,"prescription")==0) {
		word_arrays[i] = (unsigned char*)malloc(prescription_raw_len * sizeof(unsigned char));
		word_arrays[i] = prescription_raw;
		word_arrays_sizes[i]=prescription_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"present")==0) {
		word_arrays[i] = (unsigned char*)malloc(present_raw_len * sizeof(unsigned char));
		word_arrays[i] = present_raw;
		word_arrays_sizes[i]=present_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"premier")==0) { //post+office
		word_arrays[i] = (unsigned char*)malloc(premier_raw_len * sizeof(unsigned char));
		word_arrays[i] = premier_raw;
		word_arrays_sizes[i]=premier_raw_len;
	    }
	    
	    if (g_strcmp0(word_str_lower,"pressure")==0) {
		word_arrays[i] = (unsigned char*)malloc(pressure_raw_len * sizeof(unsigned char));
		word_arrays[i] = pressure_raw;
		word_arrays_sizes[i]=pressure_raw_len;
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
	    if (g_strcmp0(word_str_lower,"pronounce")==0) {		
		word_arrays[i] = (unsigned char*)malloc(pronounce_raw_len * sizeof(unsigned char));
		word_arrays[i] = pronounce_raw;
		word_arrays_sizes[i]=pronounce_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"pronounced")==0) {		
		word_arrays[i] = (unsigned char*)malloc(pronounced_raw_len * sizeof(unsigned char));
		word_arrays[i] = pronounced_raw;
		word_arrays_sizes[i]=pronounced_raw_len;	
	    }			    
	    if (g_strcmp0(word_str_lower,"public")==0) {		
		word_arrays[i] = (unsigned char*)malloc(public_raw_len * sizeof(unsigned char));
		word_arrays[i] = public_raw;
		word_arrays_sizes[i]=public_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"purchase")==0) {
		word_arrays[i] = (unsigned char*)malloc(purchase_raw_len * sizeof(unsigned char));
		word_arrays[i] = purchase_raw;
		word_arrays_sizes[i]=purchase_raw_len;
	    }
	    //--------------------------------------------------------------	    
	    //Q Words
	    if (g_strcmp0(word_str_lower,"queen")==0) {		
		word_arrays[i] = (unsigned char*)malloc(queen_raw_len * sizeof(unsigned char));
		word_arrays[i] = queen_raw;
		word_arrays_sizes[i]=queen_raw_len;	
	    } 
	    if (g_strcmp0(word_str_lower,"quick")==0) {		
		word_arrays[i] = (unsigned char*)malloc(quick_raw_len * sizeof(unsigned char));
		word_arrays[i] = quick_raw;
		word_arrays_sizes[i]=quick_raw_len;	
	    } 
	    if (g_strcmp0(word_str_lower,"quiz")==0) {		
		word_arrays[i] = (unsigned char*)malloc(quiz_raw_len * sizeof(unsigned char));
		word_arrays[i] = quiz_raw;
		word_arrays_sizes[i]=quiz_raw_len;	
	    }
	     if (g_strcmp0(word_str_lower,"quote")==0) {		
		word_arrays[i] = (unsigned char*)malloc(quote_raw_len * sizeof(unsigned char));
		word_arrays[i] = quote_raw;
		word_arrays_sizes[i]=quote_raw_len;	
	    }
	    //--------------------------------------------------------------
	    //R words
	    
	    if (g_strcmp0(word_str_lower,"radio")==0) {
		word_arrays[i] = (unsigned char*)malloc(radio_raw_len * sizeof(unsigned char));
		word_arrays[i] = radio_raw;
		word_arrays_sizes[i]=radio_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"rail")==0) {
		word_arrays[i] = (unsigned char*)malloc(rail_raw_len * sizeof(unsigned char));
		word_arrays[i] = rail_raw;
		word_arrays_sizes[i]=rail_raw_len;	
	    }
	     if (g_strcmp0(word_str_lower,"railway")==0) {
		word_arrays[i] = (unsigned char*)malloc(railway_raw_len * sizeof(unsigned char));
		word_arrays[i] = railway_raw;
		word_arrays_sizes[i]=railway_raw_len;	
	    }			    	    
		if (g_strcmp0(word_str_lower,"reminder")==0) {
		word_arrays[i] = (unsigned char*)malloc(reminder_raw_len * sizeof(unsigned char));
		word_arrays[i] = reminder_raw;
		word_arrays_sizes[i]=reminder_raw_len;	
		}
	    if (g_strcmp0(word_str_lower,"repair")==0) { //repair+shop
		word_arrays[i] = (unsigned char*)malloc(repair_raw_len * sizeof(unsigned char));
		word_arrays[i] = repair_raw;
		word_arrays_sizes[i]=repair_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"rest")==0) {
		word_arrays[i] = (unsigned char*)malloc(rest_raw_len * sizeof(unsigned char));
		word_arrays[i] = rest_raw;
		word_arrays_sizes[i]=rest_raw_len;	
	    }	    	    
	    if (g_strcmp0(word_str_lower,"restaurant")==0) {
		word_arrays[i] = (unsigned char*)malloc(restaurant_raw_len * sizeof(unsigned char));
		word_arrays[i] = restaurant_raw;
		word_arrays_sizes[i]=restaurant_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"retire")==0) {
		word_arrays[i] = (unsigned char*)malloc(retire_raw_len * sizeof(unsigned char));
		word_arrays[i] = retire_raw;
		word_arrays_sizes[i]=retire_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"retirement")==0) {
		word_arrays[i] = (unsigned char*)malloc(retirement_raw_len * sizeof(unsigned char));
		word_arrays[i] = retirement_raw;
		word_arrays_sizes[i]=retirement_raw_len;	
	    }	 	 	    
	    if (g_strcmp0(word_str_lower,"return")==0) {
		word_arrays[i] = (unsigned char*)malloc(return_raw_len * sizeof(unsigned char));
		word_arrays[i] = return_raw;
		word_arrays_sizes[i]=return_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"road")==0) {
		word_arrays[i] = (unsigned char*)malloc(road_raw_len * sizeof(unsigned char));
		word_arrays[i] = road_raw;
		word_arrays_sizes[i]=road_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"room")==0) {
		word_arrays[i] = (unsigned char*)malloc(room_raw_len * sizeof(unsigned char));
		word_arrays[i] = room_raw;
		word_arrays_sizes[i]=room_raw_len;	
	    }			    
	    if (g_strcmp0(word_str_lower,"royal")==0) {
		word_arrays[i] = (unsigned char*)malloc(royal_raw_len * sizeof(unsigned char));
		word_arrays[i] = royal_raw;
		word_arrays_sizes[i]=royal_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"rugby")==0) {
		word_arrays[i] = (unsigned char*)malloc(rugby_raw_len * sizeof(unsigned char));
		word_arrays[i] = rugby_raw;
		word_arrays_sizes[i]=rugby_raw_len;	
	    }	
	    
	    //--------------------------------------------------------------
	    //S words
	    if (g_strcmp0(word_str_lower,"saint")==0) {
	    word_arrays[i] = (unsigned char*)malloc(saint_raw_len * sizeof(unsigned char));
		word_arrays[i] =  saint_raw;		
		word_arrays_sizes[i]=saint_raw_len; 
	    }
	    if (g_strcmp0(word_str_lower,"say")==0) {
	    word_arrays[i] = (unsigned char*)malloc(say_raw_len * sizeof(unsigned char));
		word_arrays[i] =  say_raw;		
		word_arrays_sizes[i]=say_raw_len; 
	    }
	    if (g_strcmp0(word_str_lower,"says")==0) {
	    word_arrays[i] = (unsigned char*)malloc(says_raw_len * sizeof(unsigned char));
		word_arrays[i] =  says_raw;		
		word_arrays_sizes[i]=says_raw_len; 
	    }
	        
	    if (g_strcmp0(word_str_lower,"sanctuary")==0) {
	    word_arrays[i] = (unsigned char*)malloc(sanctuary_raw_len * sizeof(unsigned char));
		word_arrays[i] =  sanctuary_raw;		
		word_arrays_sizes[i]=sanctuary_raw_len; 
	    }
	    if (g_strcmp0(word_str_lower,"school")==0) {
	    word_arrays[i] = (unsigned char*)malloc(school_raw_len * sizeof(unsigned char));
		word_arrays[i] =  school_raw;		
		word_arrays_sizes[i]=school_raw_len; 
	    }
	    if (g_strcmp0(word_str_lower,"sea")==0) {
	    word_arrays[i] = (unsigned char*)malloc(sea_raw_len * sizeof(unsigned char));
		word_arrays[i] =  sea_raw;		
		word_arrays_sizes[i]=sea_raw_len; 
	    }	    	    
	    if (g_strcmp0(word_str_lower,"service")==0) {
	    word_arrays[i] = (unsigned char*)malloc(service_raw_len * sizeof(unsigned char));
		word_arrays[i] =  service_raw;		
		word_arrays_sizes[i]=service_raw_len; 
	    }
	     if (g_strcmp0(word_str_lower,"session")==0) {
	    word_arrays[i] = (unsigned char*)malloc(session_raw_len * sizeof(unsigned char));
		word_arrays[i] =  session_raw;		
		word_arrays_sizes[i]=session_raw_len; 
	    }
	    if (g_strcmp0(word_str_lower,"shoe")==0) {
	    word_arrays[i] = (unsigned char*)malloc(shoe_raw_len * sizeof(unsigned char));
		word_arrays[i] =  shoe_raw;		
		word_arrays_sizes[i]=shoe_raw_len; 
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
	    if (g_strcmp0(word_str_lower,"sky")==0) {
	    word_arrays[i] = (unsigned char*)malloc(sky_raw_len * sizeof(unsigned char));
		word_arrays[i] =  sky_raw;		
		word_arrays_sizes[i]=sky_raw_len; 
	    } 
	     if (g_strcmp0(word_str_lower,"small")==0) {
	    word_arrays[i] = (unsigned char*)malloc(small_raw_len * sizeof(unsigned char));
		word_arrays[i] =  small_raw;		
		word_arrays_sizes[i]=small_raw_len; 
	    } 
	    if (g_strcmp0(word_str_lower,"society")==0) {
	    word_arrays[i] = (unsigned char*)malloc(society_raw_len * sizeof(unsigned char));
		word_arrays[i] =  society_raw;		
		word_arrays_sizes[i]=society_raw_len; 
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
	     if (g_strcmp0(word_str_lower,"speaker")==0) {
	    word_arrays[i] = (unsigned char*)malloc(speaker_raw_len * sizeof(unsigned char));
		word_arrays[i] =  speaker_raw;		
		word_arrays_sizes[i]=speaker_raw_len; 
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
		if (g_strcmp0(word_str_lower,"star")==0) {
		word_arrays[i] = (unsigned char*)malloc(star_raw_len * sizeof(unsigned char));
		word_arrays[i] = star_raw;
		word_arrays_sizes[i]=star_raw_len;
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
		if (g_strcmp0(word_str_lower,"stay")==0) {
		word_arrays[i] = (unsigned char*)malloc(stay_raw_len * sizeof(unsigned char));
		word_arrays[i] = stay_raw;
		word_arrays_sizes[i]=stay_raw_len;
		}	
		if (g_strcmp0(word_str_lower,"stock")==0) {
		word_arrays[i] = (unsigned char*)malloc(stock_raw_len * sizeof(unsigned char));
		word_arrays[i] = stock_raw;
		word_arrays_sizes[i]=stock_raw_len;
		}
		if (g_strcmp0(word_str_lower,"store")==0) {
		word_arrays[i] = (unsigned char*)malloc(store_raw_len * sizeof(unsigned char));
		word_arrays[i] = store_raw;
		word_arrays_sizes[i]=store_raw_len;
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
		
		if (g_strcmp0(word_str_lower,"synthesizer")==0) {
		word_arrays[i] = (unsigned char*)malloc(synthesizer_raw_len * sizeof(unsigned char));
		word_arrays[i] = synthesizer_raw;
		word_arrays_sizes[i]=synthesizer_raw_len;
		}
		
	    //--------------------------------------------------------------
	    //T words
	    if (g_strcmp0(word_str_lower,"table")==0) { //timetable
		word_arrays[i] = (unsigned char*)malloc(table_raw_len * sizeof(unsigned char));
		word_arrays[i] = table_raw;
		word_arrays_sizes[i]=table_raw_len;	
	    }	
	    
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
	    if (g_strcmp0(word_str_lower,"taxi")==0) {
		word_arrays[i] = (unsigned char*)malloc(taxi_raw_len * sizeof(unsigned char));
		word_arrays[i] = taxi_raw;
		word_arrays_sizes[i]=taxi_raw_len;	
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
	     if (g_strcmp0(word_str_lower,"temperature")==0) { //future updates		
		word_arrays[i] = (unsigned char*)malloc(temperature_raw_len * sizeof(unsigned char));
		word_arrays[i] = temperature_raw;
		word_arrays_sizes[i]=temperature_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"tennis")==0) {
		word_arrays[i] = (unsigned char*)malloc(tennis_raw_len * sizeof(unsigned char));
		word_arrays[i] = tennis_raw;
		word_arrays_sizes[i]=tennis_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"test")==0) {
		word_arrays[i] = (unsigned char*)malloc(test_raw_len * sizeof(unsigned char));
		word_arrays[i] = test_raw;
		word_arrays_sizes[i]=test_raw_len;	
	    }		
	    if (g_strcmp0(word_str_lower,"thankyou")==0) {
		word_arrays[i] = (unsigned char*)malloc(thankyou_raw_len * sizeof(unsigned char));
		word_arrays[i] = thankyou_raw;
		word_arrays_sizes[i]=thankyou_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"that")==0) {
		word_arrays[i] = (unsigned char*)malloc(that_raw_len * sizeof(unsigned char));
		word_arrays[i] = that_raw;
		word_arrays_sizes[i]=that_raw_len;	
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
	    if (g_strcmp0(word_str_lower,"ticket")==0) {		
		word_arrays[i] = (unsigned char*)malloc(ticket_raw_len * sizeof(unsigned char));
		word_arrays[i] = ticket_raw;
		word_arrays_sizes[i]=ticket_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"time")==0) {		
		word_arrays[i] = (unsigned char*)malloc(time_raw_len * sizeof(unsigned char));
		word_arrays[i] = time_raw;
		word_arrays_sizes[i]=time_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"tiny")==0) {		
		word_arrays[i] = (unsigned char*)malloc(tiny_raw_len * sizeof(unsigned char));
		word_arrays[i] = tiny_raw;
		word_arrays_sizes[i]=tiny_raw_len;	
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
	    if (g_strcmp0(word_str_lower,"toll")==0) {
		word_arrays[i] = (unsigned char*)malloc(toll_raw_len * sizeof(unsigned char));
		word_arrays[i] = toll_raw;
		word_arrays_sizes[i]=toll_raw_len;	
	    }	 
	    if (g_strcmp0(word_str_lower,"tomorrow")==0) {
		word_arrays[i] = (unsigned char*)malloc(tomorrow_raw_len * sizeof(unsigned char));
		word_arrays[i] = tomorrow_raw;
		word_arrays_sizes[i]=tomorrow_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"tour")==0) {
		word_arrays[i] = (unsigned char*)malloc(tour_raw_len * sizeof(unsigned char));
		word_arrays[i] = tour_raw;
		word_arrays_sizes[i]=tour_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"train")==0) {
		word_arrays[i] = (unsigned char*)malloc(train_raw_len * sizeof(unsigned char));
		word_arrays[i] = train_raw;
		word_arrays_sizes[i]=train_raw_len;	
	    }
	     if (g_strcmp0(word_str_lower,"training")==0) {
		word_arrays[i] = (unsigned char*)malloc(training_raw_len * sizeof(unsigned char));
		word_arrays[i] = training_raw;
		word_arrays_sizes[i]=training_raw_len;	
	    }	  	    
	    if (g_strcmp0(word_str_lower,"travel")==0) {
		word_arrays[i] = (unsigned char*)malloc(travel_raw_len * sizeof(unsigned char));
		word_arrays[i] = travel_raw;
		word_arrays_sizes[i]=travel_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"trip")==0) {
		word_arrays[i] = (unsigned char*)malloc(trip_raw_len * sizeof(unsigned char));
		word_arrays[i] = trip_raw;
		word_arrays_sizes[i]=trip_raw_len;	
	    }
	     if (g_strcmp0(word_str_lower,"tunnel")==0) {
		word_arrays[i] = (unsigned char*)malloc(tunnel_raw_len * sizeof(unsigned char));
		word_arrays[i] = tunnel_raw;
		word_arrays_sizes[i]=tunnel_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"turn")==0) {
		word_arrays[i] = (unsigned char*)malloc(turn_raw_len * sizeof(unsigned char));
		word_arrays[i] = turn_raw;
		word_arrays_sizes[i]=turn_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"tv")==0) {
		word_arrays[i] = (unsigned char*)malloc(tv_raw_len * sizeof(unsigned char));
		word_arrays[i] = tv_raw;
		word_arrays_sizes[i]=tv_raw_len;	
	    }
	    //--------------------------------------------------------------
	    //U words	
	    if (g_strcmp0(word_str_lower,"u3a")==0) {
		word_arrays[i] = (unsigned char*)malloc(u3a_raw_len * sizeof(unsigned char));
		word_arrays[i] = u3a_raw;
		word_arrays_sizes[i]=u3a_raw_len;
	    }
	    if (g_strcmp0(word_str_lower,"uncle")==0) {
		word_arrays[i] = (unsigned char*)malloc(uncle_raw_len * sizeof(unsigned char));
		word_arrays[i] = uncle_raw;
		word_arrays_sizes[i]=uncle_raw_len;
	    }
	    if (g_strcmp0(word_str_lower,"under")==0) {
		word_arrays[i] = (unsigned char*)malloc(under_raw_len * sizeof(unsigned char));
		word_arrays[i] = under_raw;
		word_arrays_sizes[i]=under_raw_len;
	    }
	    if (g_strcmp0(word_str_lower,"university")==0) {
		word_arrays[i] = (unsigned char*)malloc(university_raw_len * sizeof(unsigned char));
		word_arrays[i] = university_raw;
		word_arrays_sizes[i]=university_raw_len;
	    }
	    if (g_strcmp0(word_str_lower,"unknown")==0) {
		word_arrays[i] = (unsigned char*)malloc(unknown_raw_len * sizeof(unsigned char));
		word_arrays[i] = unknown_raw;
		word_arrays_sizes[i]=unknown_raw_len;
	    } 
	    if (g_strcmp0(word_str_lower,"up")==0) {
		word_arrays[i] = (unsigned char*)malloc(up_raw_len * sizeof(unsigned char));
		word_arrays[i] = up_raw;
		word_arrays_sizes[i]=up_raw_len;
	    }     
	    if (g_strcmp0(word_str_lower,"upcoming")==0) {
		word_arrays[i] = (unsigned char*)malloc(upcoming_raw_len * sizeof(unsigned char));
		word_arrays[i] = upcoming_raw;
		word_arrays_sizes[i]=upcoming_raw_len;
	    }	
	    //--------------------------------------------------------------
	    //V words
	    if (g_strcmp0(word_str_lower,"valentine")==0) {
		word_arrays[i] = (unsigned char*)malloc(valentine_raw_len * sizeof(unsigned char));
		word_arrays[i] = valentine_raw;
		word_arrays_sizes[i]=valentine_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"valentines")==0) {
		word_arrays[i] = (unsigned char*)malloc(valentines_raw_len * sizeof(unsigned char));
		word_arrays[i] = valentines_raw;
		word_arrays_sizes[i]=valentines_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"vehicle")==0) {
		word_arrays[i] = (unsigned char*)malloc(vehicle_raw_len * sizeof(unsigned char));
		word_arrays[i] = vehicle_raw;
		word_arrays_sizes[i]=vehicle_raw_len;	
	    }	
	    if (g_strcmp0(word_str_lower,"venue")==0) {
		word_arrays[i] = (unsigned char*)malloc(venue_raw_len * sizeof(unsigned char));
		word_arrays[i] = venue_raw;
		word_arrays_sizes[i]=venue_raw_len;	
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
	    //--------------------------------------------------------------
	    //W words
	     if (g_strcmp0(word_str_lower,"walk")==0) {
		word_arrays[i] = (unsigned char*)malloc(walk_raw_len * sizeof(unsigned char));
		word_arrays[i] = walk_raw;
		word_arrays_sizes[i]=walk_raw_len;	
	    }	
	    if (g_strcmp0(word_str_lower,"warm")==0) {
		word_arrays[i] = (unsigned char*)malloc(warm_raw_len * sizeof(unsigned char));
		word_arrays[i] = warm_raw;
		word_arrays_sizes[i]=warm_raw_len;	
	    }  
	    if (g_strcmp0(word_str_lower,"warming")==0) {
		word_arrays[i] = (unsigned char*)malloc(warming_raw_len * sizeof(unsigned char));
		word_arrays[i] = warming_raw;
		word_arrays_sizes[i]=warming_raw_len;	
	    } 
	     if (g_strcmp0(word_str_lower,"wash")==0) {
		word_arrays[i] = (unsigned char*)malloc(wash_raw_len * sizeof(unsigned char));
		word_arrays[i] = wash_raw;
		word_arrays_sizes[i]=wash_raw_len;	
	    }   
	    if (g_strcmp0(word_str_lower,"washing")==0) {
		word_arrays[i] = (unsigned char*)malloc(washing_raw_len * sizeof(unsigned char));
		word_arrays[i] = washing_raw;
		word_arrays_sizes[i]=washing_raw_len;	
	    }
	     if (g_strcmp0(word_str_lower,"water")==0) {
		word_arrays[i] = (unsigned char*)malloc(water_raw_len * sizeof(unsigned char));
		word_arrays[i] = water_raw;
		word_arrays_sizes[i]=water_raw_len;	
	    }	
	    if (g_strcmp0(word_str_lower,"way")==0) {
		word_arrays[i] = (unsigned char*)malloc(way_raw_len * sizeof(unsigned char));
		word_arrays[i] = way_raw;
		word_arrays_sizes[i]=way_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"web")==0) {
		word_arrays[i] = (unsigned char*)malloc(web_raw_len * sizeof(unsigned char));
		word_arrays[i] = web_raw;
		word_arrays_sizes[i]=web_raw_len;	
	    }
	     if (g_strcmp0(word_str_lower,"webinar")==0) {
		word_arrays[i] = (unsigned char*)malloc(webinar_raw_len * sizeof(unsigned char));
		word_arrays[i] = webinar_raw;
		word_arrays_sizes[i]=webinar_raw_len;	
	    }			    
	    if (g_strcmp0(word_str_lower,"wedding")==0) {
		word_arrays[i] = (unsigned char*)malloc(wedding_raw_len * sizeof(unsigned char));
		word_arrays[i] = wedding_raw;
		word_arrays_sizes[i]=wedding_raw_len;	
	    }
	     if (g_strcmp0(word_str_lower,"week")==0) {
		word_arrays[i] = (unsigned char*)malloc(week_raw_len * sizeof(unsigned char));
		word_arrays[i] = week_raw;
		word_arrays_sizes[i]=week_raw_len;	
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
	    if (g_strcmp0(word_str_lower,"witch")==0) {
		word_arrays[i] = (unsigned char*)malloc(witch_raw_len * sizeof(unsigned char));
		word_arrays[i] = witch_raw;
		word_arrays_sizes[i]=witch_raw_len;	
	    }    
	    if (g_strcmp0(word_str_lower,"winter")==0) {
		word_arrays[i] = (unsigned char*)malloc(winter_raw_len * sizeof(unsigned char));
		word_arrays[i] = winter_raw;
		word_arrays_sizes[i]=winter_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"word")==0) {
		word_arrays[i] = (unsigned char*)malloc(word_raw_len * sizeof(unsigned char));
		word_arrays[i] = word_raw;
		word_arrays_sizes[i]=word_raw_len;	
	    }	
	    if (g_strcmp0(word_str_lower,"woman")==0) {
		word_arrays[i] = (unsigned char*)malloc(woman_raw_len * sizeof(unsigned char));
		word_arrays[i] = woman_raw;
		word_arrays_sizes[i]=woman_raw_len;	
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
	    
	    //--------------------------------------------------------------
	    //Y words
	     if (g_strcmp0(word_str_lower,"yacht")==0) {
		word_arrays[i] = (unsigned char*)malloc(yacht_raw_len * sizeof(unsigned char));		
		word_arrays[i] = yacht_raw;
		word_arrays_sizes[i]=yacht_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"year")==0) {
		word_arrays[i] = (unsigned char*)malloc(year_raw_len * sizeof(unsigned char));		
		word_arrays[i] = year_raw;
		word_arrays_sizes[i]=year_raw_len;	
	    }
	     if (g_strcmp0(word_str_lower,"yearly")==0) {
		word_arrays[i] = (unsigned char*)malloc(yearly_raw_len * sizeof(unsigned char));		
		word_arrays[i] = yearly_raw;
		word_arrays_sizes[i]=yearly_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"you")==0) {
		word_arrays[i] = (unsigned char*)malloc(you_raw_len * sizeof(unsigned char));		
		word_arrays[i] = you_raw;
		word_arrays_sizes[i]=you_raw_len;	
	    }
	    //--------------------------------------------------------------	
	    //Z words
	    if (g_strcmp0(word_str_lower,"zero")==0) {
		word_arrays[i] = (unsigned char*)malloc(zero_raw_len * sizeof(unsigned char));		
		word_arrays[i] = zero_raw;
		word_arrays_sizes[i]=zero_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"zone")==0) {
		word_arrays[i] = (unsigned char*)malloc(zoo_raw_len * sizeof(unsigned char));		
		word_arrays[i] = zone_raw;
		word_arrays_sizes[i]=zone_raw_len;	
	    }		    
	    if (g_strcmp0(word_str_lower,"zoo")==0) {
		word_arrays[i] = (unsigned char*)malloc(zoo_raw_len * sizeof(unsigned char));		
		word_arrays[i] = zoo_raw;
		word_arrays_sizes[i]=zoo_raw_len;	
	    }	
	    //--------------------------------------------------------------
	    // some common names
	    //--------------------------------------------------------------
	    //names
	    
	    //A names
	   
	    if (g_strcmp0(word_str_lower,"alan")==0) {
		word_arrays[i] = (unsigned char*)malloc(alan_raw_len * sizeof(unsigned char));		
		word_arrays[i] = alan_raw;
		word_arrays_sizes[i]=alan_raw_len;	
	    }
	   
	    if (g_strcmp0(word_str_lower,"alex")==0) {
		word_arrays[i] = (unsigned char*)malloc(alex_raw_len * sizeof(unsigned char));		
		word_arrays[i] = alex_raw;
		word_arrays_sizes[i]=alex_raw_len;	
	    }
	   
	    if (g_strcmp0(word_str_lower,"alexander")==0) {
		word_arrays[i] = (unsigned char*)malloc(alexander_raw_len * sizeof(unsigned char));		
		word_arrays[i] = alexander_raw;
		word_arrays_sizes[i]=alexander_raw_len;	
	    }
	   
	    if (g_strcmp0(word_str_lower,"alf")==0) {
		word_arrays[i] = (unsigned char*)malloc(alf_raw_len * sizeof(unsigned char));		
		word_arrays[i] = alf_raw;
		word_arrays_sizes[i]=alf_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"alfred")==0) {
		word_arrays[i] = (unsigned char*)malloc(alfred_raw_len * sizeof(unsigned char));		
		word_arrays[i] = alfred_raw;
		word_arrays_sizes[i]=alfred_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"alice")==0) {
		word_arrays[i] = (unsigned char*)malloc(alice_raw_len * sizeof(unsigned char));		
		word_arrays[i] = alice_raw;
		word_arrays_sizes[i]=alice_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"alison")==0) {
		word_arrays[i] = (unsigned char*)malloc(alison_raw_len * sizeof(unsigned char));		
		word_arrays[i] = alison_raw;
		word_arrays_sizes[i]=alison_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"alister")==0) {
		word_arrays[i] = (unsigned char*)malloc(alister_raw_len * sizeof(unsigned char));		
		word_arrays[i] = alister_raw;
		word_arrays_sizes[i]=alister_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"amber")==0) {
		word_arrays[i] = (unsigned char*)malloc(amber_raw_len * sizeof(unsigned char));		
		word_arrays[i] = amber_raw;
		word_arrays_sizes[i]=amber_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"amelia")==0) {
		word_arrays[i] = (unsigned char*)malloc(amelia_raw_len * sizeof(unsigned char));		
		word_arrays[i] = amelia_raw;
		word_arrays_sizes[i]=amelia_raw_len;	
	    }
	    
	     if (g_strcmp0(word_str_lower,"andora")==0) {
		word_arrays[i] = (unsigned char*)malloc(andora_raw_len * sizeof(unsigned char));		
		word_arrays[i] = andora_raw;
		word_arrays_sizes[i]=andora_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"andrea")==0) {
		word_arrays[i] = (unsigned char*)malloc(andrea_raw_len * sizeof(unsigned char));		
		word_arrays[i] = andrea_raw;
		word_arrays_sizes[i]=andrea_raw_len;	
	    }
	     if (g_strcmp0(word_str_lower,"andrew")==0) {
		word_arrays[i] = (unsigned char*)malloc(andrew_raw_len * sizeof(unsigned char));		
		word_arrays[i] = andrew_raw;
		word_arrays_sizes[i]=andrew_raw_len;	
	    }
	     if (g_strcmp0(word_str_lower,"andrews")==0) {	//saint day	
		word_arrays[i] = (unsigned char*)malloc(andrews_raw_len * sizeof(unsigned char));
		word_arrays[i] = andrews_raw;
		word_arrays_sizes[i]=andrews_raw_len;	
	    }	
	    if (g_strcmp0(word_str_lower,"andy")==0) {
		word_arrays[i] = (unsigned char*)malloc(andy_raw_len * sizeof(unsigned char));		
		word_arrays[i] = andy_raw;
		word_arrays_sizes[i]=andy_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"angela")==0) {
		word_arrays[i] = (unsigned char*)malloc(angela_raw_len * sizeof(unsigned char));		
		word_arrays[i] = angela_raw;
		word_arrays_sizes[i]=angela_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"angelina")==0) {
		word_arrays[i] = (unsigned char*)malloc(angelina_raw_len * sizeof(unsigned char));		
		word_arrays[i] = angelina_raw;
		word_arrays_sizes[i]=angelina_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"anna")==0) {
		word_arrays[i] = (unsigned char*)malloc(anna_raw_len * sizeof(unsigned char));		
		word_arrays[i] = anna_raw;
		word_arrays_sizes[i]=anna_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"annabel")==0) {
		word_arrays[i] = (unsigned char*)malloc(annabel_raw_len * sizeof(unsigned char));		
		word_arrays[i] = annabel_raw;
		word_arrays_sizes[i]=annabel_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"anne")==0) {
		word_arrays[i] = (unsigned char*)malloc(anne_raw_len * sizeof(unsigned char));		
		word_arrays[i] = anne_raw;
		word_arrays_sizes[i]=anne_raw_len;	
	    }	    
	    if (g_strcmp0(word_str_lower,"anthony")==0) {
		word_arrays[i] = (unsigned char*)malloc(anthony_raw_len * sizeof(unsigned char));		
		word_arrays[i] = anthony_raw;
		word_arrays_sizes[i]=anthony_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"archie")==0) {
		word_arrays[i] = (unsigned char*)malloc(archie_raw_len * sizeof(unsigned char));		
		word_arrays[i] = archie_raw;
		word_arrays_sizes[i]=archie_raw_len;
	    }
	    if (g_strcmp0(word_str_lower,"arthur")==0) {
		word_arrays[i] = (unsigned char*)malloc(arthur_raw_len * sizeof(unsigned char));		
		word_arrays[i] = arthur_raw;
		word_arrays_sizes[i]=arthur_raw_len;
	    }
	    if (g_strcmp0(word_str_lower,"aubrey")==0) {
		word_arrays[i] = (unsigned char*)malloc(aubrey_raw_len * sizeof(unsigned char));		
		word_arrays[i] = aubrey_raw;
		word_arrays_sizes[i]=aubrey_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"audrey")==0) {
		word_arrays[i] = (unsigned char*)malloc(audrey_raw_len * sizeof(unsigned char));		
		word_arrays[i] = audrey_raw;
		word_arrays_sizes[i]=audrey_raw_len;	
	    }
	     if (g_strcmp0(word_str_lower,"ava")==0) {
		word_arrays[i] = (unsigned char*)malloc(ava_raw_len * sizeof(unsigned char));		
		word_arrays[i] = ava_raw;
		word_arrays_sizes[i]=ava_raw_len;	
	    }	  			
		//B names
		
		if (g_strcmp0(word_str_lower,"beth")==0) {
		word_arrays[i] = (unsigned char*)malloc(beth_raw_len * sizeof(unsigned char));		
		word_arrays[i] = beth_raw;
		word_arrays_sizes[i]=beth_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"bethany")==0) {
		word_arrays[i] = (unsigned char*)malloc(bethany_raw_len * sizeof(unsigned char));		
		word_arrays[i] = bethany_raw;
		word_arrays_sizes[i]=bethany_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"betsy")==0) {
		word_arrays[i] = (unsigned char*)malloc(betsy_raw_len * sizeof(unsigned char));		
		word_arrays[i] = betsy_raw;
		word_arrays_sizes[i]=betsy_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"billy")==0) {
		word_arrays[i] = (unsigned char*)malloc(billy_raw_len * sizeof(unsigned char));		
		word_arrays[i] = billy_raw;
		word_arrays_sizes[i]=billy_raw_len;	
	    }
	    
		//C names
		 if (g_strcmp0(word_str_lower,"cath")==0) {
		word_arrays[i] = (unsigned char*)malloc(cath_raw_len * sizeof(unsigned char));		
		word_arrays[i] = cath_raw;
		word_arrays_sizes[i]=cath_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"catherine")==0) {
		word_arrays[i] = (unsigned char*)malloc(catherine_raw_len * sizeof(unsigned char));		
		word_arrays[i] = catherine_raw;
		word_arrays_sizes[i]=catherine_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"charles")==0) {
		word_arrays[i] = (unsigned char*)malloc(charles_raw_len * sizeof(unsigned char));		
		word_arrays[i] = charles_raw;
		word_arrays_sizes[i]=charles_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"charlotte")==0) {
		word_arrays[i] = (unsigned char*)malloc(charlotte_raw_len * sizeof(unsigned char));		
		word_arrays[i] = charlotte_raw;
		word_arrays_sizes[i]=charlotte_raw_len;	
	    }
	        
	    if (g_strcmp0(word_str_lower,"claire")==0) {
		word_arrays[i] = (unsigned char*)malloc(claire_raw_len * sizeof(unsigned char));		
		word_arrays[i] = claire_raw;
		word_arrays_sizes[i]=claire_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"clara")==0) {
		word_arrays[i] = (unsigned char*)malloc(clara_raw_len * sizeof(unsigned char));		
		word_arrays[i] = clara_raw;
		word_arrays_sizes[i]=clara_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"clarence")==0) {
		word_arrays[i] = (unsigned char*)malloc(clarence_raw_len * sizeof(unsigned char));		
		word_arrays[i] = clarence_raw;
		word_arrays_sizes[i]=clarence_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"clarissa")==0) {
		word_arrays[i] = (unsigned char*)malloc(clarissa_raw_len * sizeof(unsigned char));		
		word_arrays[i] = clarissa_raw;
		word_arrays_sizes[i]=clarissa_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"claude")==0) {
		word_arrays[i] = (unsigned char*)malloc(claude_raw_len * sizeof(unsigned char));		
		word_arrays[i] = claude_raw;
		word_arrays_sizes[i]=claude_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"crispin")==0) {
		word_arrays[i] = (unsigned char*)malloc(crispin_raw_len * sizeof(unsigned char));		
		word_arrays[i] = crispin_raw;
		word_arrays_sizes[i]=crispin_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"christina")==0) {
		word_arrays[i] = (unsigned char*)malloc(christina_raw_len * sizeof(unsigned char));		
		word_arrays[i] = christina_raw;
		word_arrays_sizes[i]=christina_raw_len;	
	    }	
	  
	  //D names
	    if (g_strcmp0(word_str_lower,"daisy")==0) {
		word_arrays[i] = (unsigned char*)malloc(daisy_raw_len * sizeof(unsigned char));		
		word_arrays[i] = daisy_raw;
		word_arrays_sizes[i]=daisy_raw_len;	
	    } 
	    if (g_strcmp0(word_str_lower,"dan")==0) {
		word_arrays[i] = (unsigned char*)malloc(dan_raw_len * sizeof(unsigned char));		
		word_arrays[i] = dan_raw;
		word_arrays_sizes[i]=dan_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"daniel")==0) {
		word_arrays[i] = (unsigned char*)malloc(daniel_raw_len * sizeof(unsigned char));		
		word_arrays[i] = daniel_raw;
		word_arrays_sizes[i]=daniel_raw_len;	
	    }		
	    if (g_strcmp0(word_str_lower,"danielle")==0) {
		word_arrays[i] = (unsigned char*)malloc(danielle_raw_len * sizeof(unsigned char));		
		word_arrays[i] = danielle_raw;
		word_arrays_sizes[i]=danielle_raw_len;	
	    } 
	    if (g_strcmp0(word_str_lower,"danny")==0) {
		word_arrays[i] = (unsigned char*)malloc(danny_raw_len * sizeof(unsigned char));		
		word_arrays[i] = danny_raw;
		word_arrays_sizes[i]=danny_raw_len;	
	    }	
	    if (g_strcmp0(word_str_lower,"david")==0) {		//saint day
		word_arrays[i] = (unsigned char*)malloc(david_raw_len * sizeof(unsigned char));
		word_arrays[i] = david_raw;
		word_arrays_sizes[i]=david_raw_len;
	    }	     
	    if (g_strcmp0(word_str_lower,"davids")==0) {		//saint day
		word_arrays[i] = (unsigned char*)malloc(davids_raw_len * sizeof(unsigned char));
		word_arrays[i] = davids_raw;
		word_arrays_sizes[i]=davids_raw_len;
	    }	 
	    if (g_strcmp0(word_str_lower,"debbie")==0) {
		word_arrays[i] = (unsigned char*)malloc(debbie_raw_len * sizeof(unsigned char));		
		word_arrays[i] = debbie_raw;
		word_arrays_sizes[i]=debbie_raw_len;	
	    }		
	    if (g_strcmp0(word_str_lower,"debs")==0) {
		word_arrays[i] = (unsigned char*)malloc(debs_raw_len * sizeof(unsigned char));		
		word_arrays[i] = debs_raw;
		word_arrays_sizes[i]=debs_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"deborah")==0) {
		word_arrays[i] = (unsigned char*)malloc(deborah_raw_len * sizeof(unsigned char));		
		word_arrays[i] = deborah_raw;
		word_arrays_sizes[i]=deborah_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"don")==0) {
		word_arrays[i] = (unsigned char*)malloc(don_raw_len * sizeof(unsigned char));		
		word_arrays[i] = don_raw;
		word_arrays_sizes[i]=don_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"donald")==0) {
		word_arrays[i] = (unsigned char*)malloc(donald_raw_len * sizeof(unsigned char));		
		word_arrays[i] = donald_raw;
		word_arrays_sizes[i]=donald_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"donkey")==0) {
		word_arrays[i] = (unsigned char*)malloc(donkey_raw_len * sizeof(unsigned char));		
		word_arrays[i] = donkey_raw;
		word_arrays_sizes[i]=donkey_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"dora")==0) {
		word_arrays[i] = (unsigned char*)malloc(dora_raw_len * sizeof(unsigned char));		
		word_arrays[i] = dora_raw;
		word_arrays_sizes[i]=dora_raw_len;	
	    }							
	    //E names
	    if (g_strcmp0(word_str_lower,"elton")==0) {
		word_arrays[i] = (unsigned char*)malloc(elton_raw_len * sizeof(unsigned char));		
		word_arrays[i] = elton_raw;
		word_arrays_sizes[i]=elton_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"elisha")==0) {
		word_arrays[i] = (unsigned char*)malloc(elisha_raw_len * sizeof(unsigned char));		
		word_arrays[i] = elisha_raw;
		word_arrays_sizes[i]=elisha_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"eliza")==0) {
		word_arrays[i] = (unsigned char*)malloc(eliza_raw_len * sizeof(unsigned char));		
		word_arrays[i] = eliza_raw;
		word_arrays_sizes[i]=eliza_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"elizabeth")==0) {
		word_arrays[i] = (unsigned char*)malloc(elizabeth_raw_len * sizeof(unsigned char));		
		word_arrays[i] = elizabeth_raw;
		word_arrays_sizes[i]=elizabeth_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"elliot")==0) {
		word_arrays[i] = (unsigned char*)malloc(elliot_raw_len * sizeof(unsigned char));		
		word_arrays[i] = elliot_raw;
		word_arrays_sizes[i]=elliot_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"emma")==0) {
		word_arrays[i] = (unsigned char*)malloc(emma_raw_len * sizeof(unsigned char));		
		word_arrays[i] = emma_raw;
		word_arrays_sizes[i]=emma_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"evan")==0) {
		word_arrays[i] = (unsigned char*)malloc(evan_raw_len * sizeof(unsigned char));		
		word_arrays[i] = evan_raw;
		word_arrays_sizes[i]=evan_raw_len;	
	    }			
	 
		//F names
		
		if (g_strcmp0(word_str_lower,"flourence")==0) {
		word_arrays[i] = (unsigned char*)malloc(flourence_raw_len * sizeof(unsigned char));		
		word_arrays[i] = flourence_raw;
		word_arrays_sizes[i]=flourence_raw_len;	
	    }
		
		if (g_strcmp0(word_str_lower,"fiona")==0) {
		word_arrays[i] = (unsigned char*)malloc(fiona_raw_len * sizeof(unsigned char));		
		word_arrays[i] = fiona_raw;
		word_arrays_sizes[i]=fiona_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"frances")==0) {
		word_arrays[i] = (unsigned char*)malloc(frances_raw_len * sizeof(unsigned char));		
		word_arrays[i] = frances_raw;
		word_arrays_sizes[i]=frances_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"francesca")==0) {
		word_arrays[i] = (unsigned char*)malloc(francesca_raw_len * sizeof(unsigned char));		
		word_arrays[i] = francesca_raw;
		word_arrays_sizes[i]=francesca_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"francis")==0) {
		word_arrays[i] = (unsigned char*)malloc(francis_raw_len * sizeof(unsigned char));		
		word_arrays[i] = francis_raw;
		word_arrays_sizes[i]=francis_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"frank")==0) {
		word_arrays[i] = (unsigned char*)malloc(frank_raw_len * sizeof(unsigned char));		
		word_arrays[i] = frank_raw;
		word_arrays_sizes[i]=frank_raw_len;	
	    }	    
	    if (g_strcmp0(word_str_lower,"fred")==0) {
		word_arrays[i] = (unsigned char*)malloc(fred_raw_len * sizeof(unsigned char));		
		word_arrays[i] = fred_raw;
		word_arrays_sizes[i]=fred_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"freddie")==0) {
		word_arrays[i] = (unsigned char*)malloc(freddie_raw_len * sizeof(unsigned char));		
		word_arrays[i] = freddie_raw;
		word_arrays_sizes[i]=freddie_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"freya")==0) {
		word_arrays[i] = (unsigned char*)malloc(freya_raw_len * sizeof(unsigned char));		
		word_arrays[i] = freya_raw;
		word_arrays_sizes[i]=freya_raw_len;	
	    }
	   
	   if (g_strcmp0(word_str_lower,"frederick")==0) {
		word_arrays[i] = (unsigned char*)malloc(frederick_raw_len * sizeof(unsigned char));		
		word_arrays[i] = frederick_raw;
		word_arrays_sizes[i]=frederick_raw_len;	
	    }
		
		//G Names
		if (g_strcmp0(word_str_lower,"gale")==0) {
		word_arrays[i] = (unsigned char*)malloc(gale_raw_len * sizeof(unsigned char));		
		word_arrays[i] = gale_raw;
		word_arrays_sizes[i]=gale_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"geoff")==0) {
		word_arrays[i] = (unsigned char*)malloc(geoff_raw_len * sizeof(unsigned char));		
		word_arrays[i] = geoff_raw;
		word_arrays_sizes[i]=geoff_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"geoffrey")==0) {
		word_arrays[i] = (unsigned char*)malloc(geoffrey_raw_len * sizeof(unsigned char));		
		word_arrays[i] = geoffrey_raw;
		word_arrays_sizes[i]=geoffrey_raw_len;	
	    }
	   if (g_strcmp0(word_str_lower,"george")==0) {
		word_arrays[i] = (unsigned char*)malloc(george_raw_len * sizeof(unsigned char));
		word_arrays[i] = george_raw;
		word_arrays_sizes[i]=george_raw_len;	
	    }	    
	    if (g_strcmp0(word_str_lower,"georges")==0) {  //saint day
		word_arrays[i] = (unsigned char*)malloc(georges_raw_len * sizeof(unsigned char));
		word_arrays[i] = georges_raw;
		word_arrays_sizes[i]=georges_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"georgina")==0) {
		word_arrays[i] = (unsigned char*)malloc(georgina_raw_len * sizeof(unsigned char));		
		word_arrays[i] = georgina_raw;
		word_arrays_sizes[i]=georgina_raw_len;	
	    }
	    //H words
	    
	    if (g_strcmp0(word_str_lower,"hannah")==0) {
		word_arrays[i] = (unsigned char*)malloc(hannah_raw_len * sizeof(unsigned char));		
		word_arrays[i] = hannah_raw;
		word_arrays_sizes[i]=hannah_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"harold")==0) {
		word_arrays[i] = (unsigned char*)malloc(harold_raw_len * sizeof(unsigned char));		
		word_arrays[i] = harold_raw;
		word_arrays_sizes[i]=harold_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"harry")==0) {
		word_arrays[i] = (unsigned char*)malloc(harry_raw_len * sizeof(unsigned char));		
		word_arrays[i] = harry_raw;
		word_arrays_sizes[i]=harry_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"hector")==0) {
		word_arrays[i] = (unsigned char*)malloc(hector_raw_len * sizeof(unsigned char));		
		word_arrays[i] = hector_raw;
		word_arrays_sizes[i]=hector_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"helen")==0) {
		word_arrays[i] = (unsigned char*)malloc(helen_raw_len * sizeof(unsigned char));		
		word_arrays[i] = helen_raw;
		word_arrays_sizes[i]=helen_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"henry")==0) {
		word_arrays[i] = (unsigned char*)malloc(henry_raw_len * sizeof(unsigned char));		
		word_arrays[i] = henry_raw;
		word_arrays_sizes[i]=henry_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"herbert")==0) {
		word_arrays[i] = (unsigned char*)malloc(herbert_raw_len * sizeof(unsigned char));		
		word_arrays[i] = herbert_raw;
		word_arrays_sizes[i]=herbert_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"humphrey")==0) {
		word_arrays[i] = (unsigned char*)malloc(humphrey_raw_len * sizeof(unsigned char));		
		word_arrays[i] = humphrey_raw;
		word_arrays_sizes[i]=humphrey_raw_len;	
	    }
	    
	    //I names
	    if (g_strcmp0(word_str_lower,"ian")==0) {
		word_arrays[i] = (unsigned char*)malloc(ian_raw_len * sizeof(unsigned char));		
		word_arrays[i] = ian_raw;
		word_arrays_sizes[i]=ian_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"irene")==0) {
		word_arrays[i] = (unsigned char*)malloc(irene_raw_len * sizeof(unsigned char));		
		word_arrays[i] = irene_raw;
		word_arrays_sizes[i]=irene_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"isaac")==0) {
		word_arrays[i] = (unsigned char*)malloc(isaac_raw_len * sizeof(unsigned char));		
		word_arrays[i] = isaac_raw;
		word_arrays_sizes[i]=isaac_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"isabel")==0) {
		word_arrays[i] = (unsigned char*)malloc(isabel_raw_len * sizeof(unsigned char));		
		word_arrays[i] = isabel_raw;
		word_arrays_sizes[i]=isabel_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"isabella")==0) {
		word_arrays[i] = (unsigned char*)malloc(isabella_raw_len * sizeof(unsigned char));		
		word_arrays[i] = isabella_raw;
		word_arrays_sizes[i]=isabella_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"isla")==0) {
		word_arrays[i] = (unsigned char*)malloc(isla_raw_len * sizeof(unsigned char));		
		word_arrays[i] = isla_raw;
		word_arrays_sizes[i]=isla_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"ivan")==0) {
		word_arrays[i] = (unsigned char*)malloc(ivan_raw_len * sizeof(unsigned char));		
		word_arrays[i] = ivan_raw;
		word_arrays_sizes[i]=ivan_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"ivy")==0) {
		word_arrays[i] = (unsigned char*)malloc(ivy_raw_len * sizeof(unsigned char));		
		word_arrays[i] = ivy_raw;
		word_arrays_sizes[i]=ivy_raw_len;	
	    }
	
		//J names		    
	    if (g_strcmp0(word_str_lower,"jack")==0) {
		word_arrays[i] = (unsigned char*)malloc(jack_raw_len * sizeof(unsigned char));		
		word_arrays[i] = jack_raw;
		word_arrays_sizes[i]=jack_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"jackie")==0) {
		word_arrays[i] = (unsigned char*)malloc(jackie_raw_len * sizeof(unsigned char));		
		word_arrays[i] = jackie_raw;
		word_arrays_sizes[i]=jackie_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"jacob")==0) {
		word_arrays[i] = (unsigned char*)malloc(jacob_raw_len * sizeof(unsigned char));		
		word_arrays[i] = jacob_raw;
		word_arrays_sizes[i]=jacob_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"jacqueline")==0) {
		word_arrays[i] = (unsigned char*)malloc(jacqueline_raw_len * sizeof(unsigned char));		
		word_arrays[i] = jacqueline_raw;
		word_arrays_sizes[i]=jacqueline_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"james")==0) {
		word_arrays[i] = (unsigned char*)malloc(james_raw_len * sizeof(unsigned char));		
		word_arrays[i] = james_raw;
		word_arrays_sizes[i]=james_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"jamie")==0) {
		word_arrays[i] = (unsigned char*)malloc(jamie_raw_len * sizeof(unsigned char));		
		word_arrays[i] = jamie_raw;
		word_arrays_sizes[i]=jamie_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"jason")==0) {
		word_arrays[i] = (unsigned char*)malloc(jason_raw_len * sizeof(unsigned char));		
		word_arrays[i] = jason_raw;
		word_arrays_sizes[i]=jason_raw_len;	
	    }
	    
	    
	    if (g_strcmp0(word_str_lower,"john")==0) {
		word_arrays[i] = (unsigned char*)malloc(john_raw_len * sizeof(unsigned char));		
		word_arrays[i] = john_raw;
		word_arrays_sizes[i]=john_raw_len;	
	    }
	
		//K names
		if (g_strcmp0(word_str_lower,"karen")==0) {
		word_arrays[i] = (unsigned char*)malloc(karen_raw_len * sizeof(unsigned char));		
		word_arrays[i] = karen_raw;
		word_arrays_sizes[i]=karen_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"kate")==0) {
		word_arrays[i] = (unsigned char*)malloc(kate_raw_len * sizeof(unsigned char));		
		word_arrays[i] = kate_raw;
		word_arrays_sizes[i]=kate_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"ken")==0) {
		word_arrays[i] = (unsigned char*)malloc(ken_raw_len * sizeof(unsigned char));		
		word_arrays[i] = ken_raw;
		word_arrays_sizes[i]=ken_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"kenneth")==0) {
		word_arrays[i] = (unsigned char*)malloc(kenneth_raw_len * sizeof(unsigned char));		
		word_arrays[i] = kenneth_raw;
		word_arrays_sizes[i]=kenneth_raw_len;	
	    }
	 
		//L names
		 if (g_strcmp0(word_str_lower,"leo")==0) {
		word_arrays[i] = (unsigned char*)malloc(leo_raw_len * sizeof(unsigned char));		
		word_arrays[i] = leo_raw;
		word_arrays_sizes[i]=leo_raw_len;	
	    }
	    
		if (g_strcmp0(word_str_lower,"liam")==0) {
		word_arrays[i] = (unsigned char*)malloc(liam_raw_len * sizeof(unsigned char));		
		word_arrays[i] = liam_raw;
		word_arrays_sizes[i]=liam_raw_len;	
	    }
		if (g_strcmp0(word_str_lower,"lily")==0) {
		word_arrays[i] = (unsigned char*)malloc(lily_raw_len * sizeof(unsigned char));		
		word_arrays[i] = lily_raw;
		word_arrays_sizes[i]=lily_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"louisa")==0) {
		word_arrays[i] = (unsigned char*)malloc(louisa_raw_len * sizeof(unsigned char));		
		word_arrays[i] = louisa_raw;
		word_arrays_sizes[i]=louisa_raw_len;	
	    }
	     if (g_strcmp0(word_str_lower,"luca")==0) {
		word_arrays[i] = (unsigned char*)malloc(luca_raw_len * sizeof(unsigned char));		
		word_arrays[i] = luca_raw;
		word_arrays_sizes[i]=luca_raw_len;	
	    }
		
		//M names
		if (g_strcmp0(word_str_lower,"madeline")==0) {
		word_arrays[i] = (unsigned char*)malloc(madeline_raw_len * sizeof(unsigned char));		
		word_arrays[i] = madeline_raw;
		word_arrays_sizes[i]=madeline_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"mary")==0) {
		word_arrays[i] = (unsigned char*)malloc(mary_raw_len * sizeof(unsigned char));		
		word_arrays[i] = mary_raw;
		word_arrays_sizes[i]=mary_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"matt")==0) {
		word_arrays[i] = (unsigned char*)malloc(matt_raw_len * sizeof(unsigned char));		
		word_arrays[i] = matt_raw;
		word_arrays_sizes[i]=matt_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"matthew")==0) {
		word_arrays[i] = (unsigned char*)malloc(matthew_raw_len * sizeof(unsigned char));		
		word_arrays[i] = matthew_raw;
		word_arrays_sizes[i]=matthew_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"matthias")==0) {
		word_arrays[i] = (unsigned char*)malloc(matthias_raw_len * sizeof(unsigned char));		
		word_arrays[i] = matthias_raw;
		word_arrays_sizes[i]=matthias_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"mia")==0) {
		word_arrays[i] = (unsigned char*)malloc(mia_raw_len * sizeof(unsigned char));		
		word_arrays[i] = mia_raw;
		word_arrays_sizes[i]=mia_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"muhammad")==0) {
		word_arrays[i] = (unsigned char*)malloc(muhammad_raw_len * sizeof(unsigned char));		
		word_arrays[i] = muhammad_raw;
		word_arrays_sizes[i]=muhammad_raw_len;	
	    }			
		//N names
	    if (g_strcmp0(word_str_lower,"naomi")==0) {
		word_arrays[i] = (unsigned char*)malloc(naomi_raw_len * sizeof(unsigned char));		
		word_arrays[i] = naomi_raw;
		word_arrays_sizes[i]=naomi_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"noah")==0) {
		word_arrays[i] = (unsigned char*)malloc(noah_raw_len * sizeof(unsigned char));		
		word_arrays[i] = noah_raw;
		word_arrays_sizes[i]=noah_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"norman")==0) {
		word_arrays[i] = (unsigned char*)malloc(norman_raw_len * sizeof(unsigned char));		
		word_arrays[i] = norman_raw;
		word_arrays_sizes[i]=norman_raw_len;	
	    }
	 
	    //O names	    
	    if (g_strcmp0(word_str_lower,"oscar")==0) {
		word_arrays[i] = (unsigned char*)malloc(oscar_raw_len * sizeof(unsigned char));		
		word_arrays[i] = oscar_raw;
		word_arrays_sizes[i]=oscar_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"oliver")==0) {
		word_arrays[i] = (unsigned char*)malloc(oliver_raw_len * sizeof(unsigned char));		
		word_arrays[i] = oliver_raw;
		word_arrays_sizes[i]=oliver_raw_len;	
	    }
	    
	    if (g_strcmp0(word_str_lower,"olivia")==0) {
		word_arrays[i] = (unsigned char*)malloc(olivia_raw_len * sizeof(unsigned char));		
		word_arrays[i] = olivia_raw;
		word_arrays_sizes[i]=olivia_raw_len;	
	    }
	    
	  	    
	    // P names
	    if (g_strcmp0(word_str_lower,"pam")==0) {
		word_arrays[i] = (unsigned char*)malloc(pam_raw_len * sizeof(unsigned char));		
		word_arrays[i] = pam_raw;
		word_arrays_sizes[i]=pam_raw_len;	
	    }	    
	    if (g_strcmp0(word_str_lower,"pamela")==0) {
		word_arrays[i] = (unsigned char*)malloc(pamela_raw_len * sizeof(unsigned char));		
		word_arrays[i] = pamela_raw;
		word_arrays_sizes[i]=pamela_raw_len;	
	    }
	     if (g_strcmp0(word_str_lower,"patrick")==0) {		
		word_arrays[i] = (unsigned char*)malloc(patrick_raw_len * sizeof(unsigned char));
		word_arrays[i] = patrick_raw;
		word_arrays_sizes[i]=patrick_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"patricks")==0) {	//saint day	
		word_arrays[i] = (unsigned char*)malloc(patricks_raw_len * sizeof(unsigned char));
		word_arrays[i] = patricks_raw;
		word_arrays_sizes[i]=patricks_raw_len;	
	    }	    
	    if (g_strcmp0(word_str_lower,"paul")==0) {
		word_arrays[i] = (unsigned char*)malloc(paul_raw_len * sizeof(unsigned char));		
		word_arrays[i] = paul_raw;
		word_arrays_sizes[i]=paul_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"paula")==0) {
		word_arrays[i] = (unsigned char*)malloc(paula_raw_len * sizeof(unsigned char));		
		word_arrays[i] = paula_raw;
		word_arrays_sizes[i]=paula_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"pauline")==0) {
		word_arrays[i] = (unsigned char*)malloc(pauline_raw_len * sizeof(unsigned char));		
		word_arrays[i] = pauline_raw;
		word_arrays_sizes[i]=pauline_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"penelope")==0) {
		word_arrays[i] = (unsigned char*)malloc(penelope_raw_len * sizeof(unsigned char));		
		word_arrays[i] = penelope_raw;
		word_arrays_sizes[i]=penelope_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"penny")==0) {
		word_arrays[i] = (unsigned char*)malloc(penny_raw_len * sizeof(unsigned char));		
		word_arrays[i] = penny_raw;
		word_arrays_sizes[i]=penny_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"percy")==0) {
		word_arrays[i] = (unsigned char*)malloc(percy_raw_len * sizeof(unsigned char));		
		word_arrays[i] = percy_raw;
		word_arrays_sizes[i]=percy_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"perry")==0) {
		word_arrays[i] = (unsigned char*)malloc(perry_raw_len * sizeof(unsigned char));		
		word_arrays[i] = perry_raw;
		word_arrays_sizes[i]=perry_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"peter")==0) {
		word_arrays[i] = (unsigned char*)malloc(peter_raw_len * sizeof(unsigned char));		
		word_arrays[i] = peter_raw;
		word_arrays_sizes[i]=peter_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"phoebe")==0) {
		word_arrays[i] = (unsigned char*)malloc(phoebe_raw_len * sizeof(unsigned char));		
		word_arrays[i] = phoebe_raw;
		word_arrays_sizes[i]=phoebe_raw_len;	
	    }
	
	    
	    //Q Names
	    
	    //R names
	    if (g_strcmp0(word_str_lower,"richard")==0) {
		word_arrays[i] = (unsigned char*)malloc(richard_raw_len * sizeof(unsigned char));		
		word_arrays[i] = richard_raw;
		word_arrays_sizes[i]=richard_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"rose")==0) {
		word_arrays[i] = (unsigned char*)malloc(rose_raw_len * sizeof(unsigned char));		
		word_arrays[i] = rose_raw;
		word_arrays_sizes[i]=rose_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"rosemary")==0) {
		word_arrays[i] = (unsigned char*)malloc(rosemary_raw_len * sizeof(unsigned char));		
		word_arrays[i] = rosemary_raw;
		word_arrays_sizes[i]=rosemary_raw_len;	
	    }	   
	    
	    //S names
	    if (g_strcmp0(word_str_lower,"sabrina")==0) {
		word_arrays[i] = (unsigned char*)malloc(sabrina_raw_len * sizeof(unsigned char));		
		word_arrays[i] = sabrina_raw;
		word_arrays_sizes[i]=sabrina_raw_len;	
	    }
	    	   
	    if (g_strcmp0(word_str_lower,"steve")==0) {
		word_arrays[i] = (unsigned char*)malloc(steve_raw_len * sizeof(unsigned char));		
		word_arrays[i] = steve_raw;
		word_arrays_sizes[i]=steve_raw_len;	
	    }	
	    if (g_strcmp0(word_str_lower,"steven")==0) {
		word_arrays[i] = (unsigned char*)malloc(steven_raw_len * sizeof(unsigned char));		
		word_arrays[i] = steven_raw;
		word_arrays_sizes[i]=steven_raw_len;	
	    }	    	    
	    //T names
	    if (g_strcmp0(word_str_lower,"theo")==0) {
		word_arrays[i] = (unsigned char*)malloc(theo_raw_len * sizeof(unsigned char));		
		word_arrays[i] = theo_raw;
		word_arrays_sizes[i]=theo_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"theodore")==0) {
		word_arrays[i] = (unsigned char*)malloc(theodore_raw_len * sizeof(unsigned char));		
		word_arrays[i] = theodore_raw;
		word_arrays_sizes[i]=theodore_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"thomas")==0) {
		word_arrays[i] = (unsigned char*)malloc(thomas_raw_len * sizeof(unsigned char));		
		word_arrays[i] = thomas_raw;
		word_arrays_sizes[i]=thomas_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"tiffany")==0) {
		word_arrays[i] = (unsigned char*)malloc(tiffany_raw_len * sizeof(unsigned char));		
		word_arrays[i] = tiffany_raw;
		word_arrays_sizes[i]=tiffany_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"tilda")==0) {
		word_arrays[i] = (unsigned char*)malloc(tilda_raw_len * sizeof(unsigned char));		
		word_arrays[i] = tilda_raw;
		word_arrays_sizes[i]=tilda_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"tim")==0) {
		word_arrays[i] = (unsigned char*)malloc(tim_raw_len * sizeof(unsigned char));		
		word_arrays[i] = tim_raw;
		word_arrays_sizes[i]=tim_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"timothy")==0) {
		word_arrays[i] = (unsigned char*)malloc(timothy_raw_len * sizeof(unsigned char));		
		word_arrays[i] = timothy_raw;
		word_arrays_sizes[i]=timothy_raw_len;	
	    }
	     if (g_strcmp0(word_str_lower,"tina")==0) {
		word_arrays[i] = (unsigned char*)malloc(tina_raw_len * sizeof(unsigned char));		
		word_arrays[i] = tina_raw;
		word_arrays_sizes[i]=tina_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"tom")==0) {
		word_arrays[i] = (unsigned char*)malloc(tom_raw_len * sizeof(unsigned char));		
		word_arrays[i] = tom_raw;
		word_arrays_sizes[i]=tom_raw_len;	
	    }	    
	    if (g_strcmp0(word_str_lower,"trevor")==0) {
		word_arrays[i] = (unsigned char*)malloc(trevor_raw_len * sizeof(unsigned char));		
		word_arrays[i] = trevor_raw;
		word_arrays_sizes[i]=trevor_raw_len;	
	    }
	   	    
	    //U names
	    if (g_strcmp0(word_str_lower,"uma")==0) {
		word_arrays[i] = (unsigned char*)malloc(uma_raw_len * sizeof(unsigned char));		
		word_arrays[i] = uma_raw;
		word_arrays_sizes[i]=uma_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"ursula")==0) {
		word_arrays[i] = (unsigned char*)malloc(ursula_raw_len * sizeof(unsigned char));		
		word_arrays[i] = ursula_raw;
		word_arrays_sizes[i]=ursula_raw_len;	
	    }
	    
	    //V names	    
	    if (g_strcmp0(word_str_lower,"val")==0) {
		word_arrays[i] = (unsigned char*)malloc(val_raw_len * sizeof(unsigned char));		
		word_arrays[i] = val_raw;
		word_arrays_sizes[i]=val_raw_len;	
	    }	
	    if (g_strcmp0(word_str_lower,"valerie")==0) {
		word_arrays[i] = (unsigned char*)malloc(valerie_raw_len * sizeof(unsigned char));		
		word_arrays[i] = valerie_raw;
		word_arrays_sizes[i]=valerie_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"victor")==0) {
		word_arrays[i] = (unsigned char*)malloc(victor_raw_len * sizeof(unsigned char));		
		word_arrays[i] = victor_raw;
		word_arrays_sizes[i]=victor_raw_len;	
	    }		
	    
	    //W names
	    if (g_strcmp0(word_str_lower,"winnie")==0) {
		word_arrays[i] = (unsigned char*)malloc(winnie_raw_len * sizeof(unsigned char));		
		word_arrays[i] = winnie_raw;
		word_arrays_sizes[i]=winnie_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"winnifred")==0) {
		word_arrays[i] = (unsigned char*)malloc(winnifred_raw_len * sizeof(unsigned char));		
		word_arrays[i] = winnifred_raw;
		word_arrays_sizes[i]=winnifred_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"winston")==0) {
		word_arrays[i] = (unsigned char*)malloc(winston_raw_len * sizeof(unsigned char));		
		word_arrays[i] = winston_raw;
		word_arrays_sizes[i]=winston_raw_len;	
	    }
	    	    
	   //X names
	    if (g_strcmp0(word_str_lower,"xavier")==0) {
		word_arrays[i] = (unsigned char*)malloc(xavier_raw_len * sizeof(unsigned char));		
		word_arrays[i] = xavier_raw;
		word_arrays_sizes[i]=xavier_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"xena")==0) {
		word_arrays[i] = (unsigned char*)malloc(xena_raw_len * sizeof(unsigned char));		
		word_arrays[i] = xena_raw;
		word_arrays_sizes[i]=xena_raw_len;	
	    }
	   
	   //Y names
	   //Z names
	   if (g_strcmp0(word_str_lower,"zara")==0) {
		word_arrays[i] = (unsigned char*)malloc(zara_raw_len * sizeof(unsigned char));		
		word_arrays[i] = zara_raw;
		word_arrays_sizes[i]=zara_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"zoe")==0) {
		word_arrays[i] = (unsigned char*)malloc(zoe_raw_len * sizeof(unsigned char));		
		word_arrays[i] = zoe_raw;
		word_arrays_sizes[i]=zoe_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"zelda")==0) {
		word_arrays[i] = (unsigned char*)malloc(zelda_raw_len * sizeof(unsigned char));		
		word_arrays[i] = zelda_raw;
		word_arrays_sizes[i]=zelda_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"zac")==0) {
		word_arrays[i] = (unsigned char*)malloc(zac_raw_len * sizeof(unsigned char));		
		word_arrays[i] = zac_raw;
		word_arrays_sizes[i]=zac_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"zachary")==0) {
		word_arrays[i] = (unsigned char*)malloc(zachary_raw_len * sizeof(unsigned char));		
		word_arrays[i] = zachary_raw;
		word_arrays_sizes[i]=zachary_raw_len;	
	    }
	    										
	    	    
	    //some prefixes
	    
	    if (g_strcmp0(word_str_lower,"anti")==0) {
		word_arrays[i] = (unsigned char*)malloc(anti_raw_len * sizeof(unsigned char));		
		word_arrays[i] = anti_raw;
		word_arrays_sizes[i]=anti_raw_len;	
	    }	
	    if (g_strcmp0(word_str_lower,"inn")==0) {
		word_arrays[i] = (unsigned char*)malloc(inn_raw_len * sizeof(unsigned char));		
		word_arrays[i] = inn_raw;
		word_arrays_sizes[i]=inn_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"inter")==0) {
		word_arrays[i] = (unsigned char*)malloc(inter_raw_len * sizeof(unsigned char));		
		word_arrays[i] = inter_raw;
		word_arrays_sizes[i]=inter_raw_len;	
	    }	   
	    if (g_strcmp0(word_str_lower,"over")==0) {
		word_arrays[i] = (unsigned char*)malloc(over_raw_len * sizeof(unsigned char));		
		word_arrays[i] = over_raw;
		word_arrays_sizes[i]=over_raw_len;	
	    }	   
	    if (g_strcmp0(word_str_lower,"semi")==0) {
		word_arrays[i] = (unsigned char*)malloc(semi_raw_len * sizeof(unsigned char));		
		word_arrays[i] = semi_raw;
		word_arrays_sizes[i]=semi_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"sub")==0) {
		word_arrays[i] = (unsigned char*)malloc(sub_raw_len * sizeof(unsigned char));		
		word_arrays[i] = sub_raw;
		word_arrays_sizes[i]=sub_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"super")==0) {
		word_arrays[i] = (unsigned char*)malloc(super_raw_len * sizeof(unsigned char));		
		word_arrays[i] = super_raw;
		word_arrays_sizes[i]=super_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"trans")==0) {
		word_arrays[i] = (unsigned char*)malloc(trans_raw_len * sizeof(unsigned char));		
		word_arrays[i] = trans_raw;
		word_arrays_sizes[i]=trans_raw_len;	
	    }	   
	    if (g_strcmp0(word_str_lower,"under")==0) {
		word_arrays[i] = (unsigned char*)malloc(under_raw_len * sizeof(unsigned char));		
		word_arrays[i] = under_raw;
		word_arrays_sizes[i]=under_raw_len;	
	    }
	    
	    		
	    //--------------------------------------------------------------
	    
	    // some suffixes
	    
	    if (g_strcmp0(word_str_lower,"able")==0) {
		word_arrays[i] = (unsigned char*)malloc(able_raw_len * sizeof(unsigned char));		
		word_arrays[i] = able_raw;
		word_arrays_sizes[i]=able_raw_len;	
	    }	
	    if (g_strcmp0(word_str_lower,"ment")==0) {
		word_arrays[i] = (unsigned char*)malloc(ment_raw_len * sizeof(unsigned char));		
		word_arrays[i] = ment_raw;
		word_arrays_sizes[i]=ment_raw_len;	
	    }											
	    if (g_strcmp0(word_str_lower,"ness")==0) {
		word_arrays[i] = (unsigned char*)malloc(ness_raw_len * sizeof(unsigned char));		
		word_arrays[i] = ness_raw;
		word_arrays_sizes[i]=ness_raw_len;	
	    }
	   if (g_strcmp0(word_str_lower,"tion")==0) {
		word_arrays[i] = (unsigned char*)malloc(tion_raw_len * sizeof(unsigned char));		
		word_arrays[i] = tion_raw;
		word_arrays_sizes[i]=tion_raw_len;	
	    }
	    
	    //--------------------------------------------------------------
	    
	    																													
	
	}//for

} //get word arrays

