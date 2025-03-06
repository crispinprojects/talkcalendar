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
#include "voice2.h"

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
	    if (g_strcmp0(word_str_lower,"twentyfirst")==0) {		
		word_arrays[i] = (unsigned char*)malloc(twentyfirst_raw_len * sizeof(unsigned char));
		word_arrays[i] = twentyfirst_raw;
		word_arrays_sizes[i]=twentyfirst_raw_len;	
	    }		
		if (g_strcmp0(word_str_lower,"twentysecond")==0) {		
		word_arrays[i] = (unsigned char*)malloc(twentysecond_raw_len * sizeof(unsigned char));
		word_arrays[i] = twentysecond_raw;
		word_arrays_sizes[i]=twentysecond_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"twentythird")==0) {		
		word_arrays[i] = (unsigned char*)malloc(twentythird_raw_len * sizeof(unsigned char));
		word_arrays[i] = twentythird_raw;
		word_arrays_sizes[i]=twentythird_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"twentyfourth")==0) {		
		word_arrays[i] = (unsigned char*)malloc(twentyfourth_raw_len * sizeof(unsigned char));
		word_arrays[i] = twentyfourth_raw;
		word_arrays_sizes[i]=twentyfourth_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"twentyfifth")==0) {		
		word_arrays[i] = (unsigned char*)malloc(twentyfifth_raw_len * sizeof(unsigned char));
		word_arrays[i] = twentyfifth_raw;
		word_arrays_sizes[i]=twentyfifth_raw_len;	
	    }		
		if (g_strcmp0(word_str_lower,"twentysixth")==0) {		
		word_arrays[i] = (unsigned char*)malloc(twentysixth_raw_len * sizeof(unsigned char));
		word_arrays[i] = twentysixth_raw;
		word_arrays_sizes[i]=twentysixth_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"twentyseventh")==0) {		
		word_arrays[i] = (unsigned char*)malloc(twentyseventh_raw_len * sizeof(unsigned char));
		word_arrays[i] = twentyseventh_raw;
		word_arrays_sizes[i]=twentyseventh_raw_len;	
	    }		
		if (g_strcmp0(word_str_lower,"twentyeighth")==0) {		
		word_arrays[i] = (unsigned char*)malloc(twentyeighth_raw_len * sizeof(unsigned char));
		word_arrays[i] = twentyeighth_raw;
		word_arrays_sizes[i]=twentyeighth_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"twentynineth")==0) {		
		word_arrays[i] = (unsigned char*)malloc(twentynineth_raw_len * sizeof(unsigned char));
		word_arrays[i] = twentynineth_raw;
		word_arrays_sizes[i]=twentynineth_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"thirtieth")==0) {	
		word_arrays[i] = (unsigned char*)malloc(thirtieth_raw_len * sizeof(unsigned char));
		word_arrays[i] = thirtieth_raw;
		word_arrays_sizes[i]=thirtieth_raw_len;	
	    }
	    if (g_strcmp0(word_str_lower,"thirtyfirst")==0) {
		word_arrays[i] = (unsigned char*)malloc(thirtyfirst_raw_len * sizeof(unsigned char));
		word_arrays[i] = thirtyfirst_raw;
		word_arrays_sizes[i]=thirtyfirst_raw_len;	
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
	     if (g_strcmp0(word_str_lower,"twentyone")==0) {		
		word_arrays[i] = (unsigned char*)malloc(twentyone_raw_len * sizeof(unsigned char));
		word_arrays[i] = twentyone_raw;
		word_arrays_sizes[i]=twentyone_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"twentytwo")==0) {		
		word_arrays[i] = (unsigned char*)malloc(twentytwo_raw_len * sizeof(unsigned char));
		word_arrays[i] = twentytwo_raw;
		word_arrays_sizes[i]=twentytwo_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"twentythree")==0) {		
		word_arrays[i] = (unsigned char*)malloc(twentythree_raw_len * sizeof(unsigned char));
		word_arrays[i] = twentythree_raw;
		word_arrays_sizes[i]=twentythree_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"twentyfour")==0) {
		word_arrays[i] = (unsigned char*)malloc(twentyfour_raw_len * sizeof(unsigned char));
		word_arrays[i] = twentyfour_raw;
		word_arrays_sizes[i]=twentyfour_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"twentyfive")==0) {		
		word_arrays[i] = (unsigned char*)malloc(twentyfive_raw_len * sizeof(unsigned char));
		word_arrays[i] = twentyfive_raw;
		word_arrays_sizes[i]=twentyfive_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"twentysix")==0) {		
		word_arrays[i] = (unsigned char*)malloc(twentysix_raw_len * sizeof(unsigned char));
		word_arrays[i] = twentysix_raw;
		word_arrays_sizes[i]=twentysix_raw_len;
	    }	
	     if (g_strcmp0(word_str_lower,"twentyseven")==0) {		
		word_arrays[i] = (unsigned char*)malloc(twentyseven_raw_len * sizeof(unsigned char));
		word_arrays[i] = twentyseven_raw;
		word_arrays_sizes[i]=twentyseven_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"twentyeight")==0) {		
		word_arrays[i] = (unsigned char*)malloc(twentyeight_raw_len * sizeof(unsigned char));
		word_arrays[i] = twentyeight_raw;
		word_arrays_sizes[i]=twentyeight_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"twentynine")==0) {		
		word_arrays[i] = (unsigned char*)malloc(twentynine_raw_len * sizeof(unsigned char));
		word_arrays[i] = twentynine_raw;
		word_arrays_sizes[i]=twentynine_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"thirty")==0) {		
		word_arrays[i] = (unsigned char*)malloc(thirty_raw_len * sizeof(unsigned char));
		word_arrays[i] = thirty_raw;
		word_arrays_sizes[i]=thirty_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"thirtyone")==0) {		
		word_arrays[i] = (unsigned char*)malloc(thirtyone_raw_len * sizeof(unsigned char));
		word_arrays[i] = thirtyone_raw;
		word_arrays_sizes[i]=thirtyone_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"thirtytwo")==0) {		
		word_arrays[i] = (unsigned char*)malloc(thirtytwo_raw_len * sizeof(unsigned char));
		word_arrays[i] = thirtytwo_raw;
		word_arrays_sizes[i]=thirtytwo_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"thirtythree")==0) {		
		word_arrays[i] = (unsigned char*)malloc(thirtythree_raw_len * sizeof(unsigned char));
		word_arrays[i] = thirtythree_raw;
		word_arrays_sizes[i]=thirtythree_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"thirtyfour")==0) {		
		word_arrays[i] = (unsigned char*)malloc(thirtyfour_raw_len * sizeof(unsigned char));
		word_arrays[i] = thirtyfour_raw;
		word_arrays_sizes[i]=thirtyfour_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"thirtyfive")==0) {		
		word_arrays[i] = (unsigned char*)malloc(thirtyfive_raw_len * sizeof(unsigned char));
		word_arrays[i] = thirtyfive_raw;
		word_arrays_sizes[i]=thirtyfive_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"thirtysix")==0) {		
		word_arrays[i] = (unsigned char*)malloc(thirtysix_raw_len * sizeof(unsigned char));
		word_arrays[i] = thirtysix_raw;
		word_arrays_sizes[i]=thirtysix_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"thirtyseven")==0) {		
		word_arrays[i] = (unsigned char*)malloc(thirtyseven_raw_len * sizeof(unsigned char));
		word_arrays[i] = thirtyseven_raw;
		word_arrays_sizes[i]=thirtyseven_raw_len;
	    }
	    if (g_strcmp0(word_str_lower,"thirtyeight")==0) {		
		word_arrays[i] = (unsigned char*)malloc(thirtyeight_raw_len * sizeof(unsigned char));
		word_arrays[i] = thirtyeight_raw;
		word_arrays_sizes[i]=thirtyeight_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"thirtynine")==0) {		
		word_arrays[i] = (unsigned char*)malloc(thirtynine_raw_len * sizeof(unsigned char));
		word_arrays[i] = thirtynine_raw;
		word_arrays_sizes[i]=thirtynine_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"forty")==0) {		
		word_arrays[i] = (unsigned char*)malloc(forty_raw_len * sizeof(unsigned char));
		word_arrays[i] = forty_raw;
		word_arrays_sizes[i]=forty_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"fortyone")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fortyone_raw_len * sizeof(unsigned char));
		word_arrays[i] = fortyone_raw;
		word_arrays_sizes[i]=fortyone_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"fortytwo")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fortytwo_raw_len * sizeof(unsigned char));
		word_arrays[i] = fortytwo_raw;
		word_arrays_sizes[i]=fortythree_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"fortythree")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fortythree_raw_len * sizeof(unsigned char));
		word_arrays[i] = fortythree_raw;
		word_arrays_sizes[i]=fortythree_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"fortyfour")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fortyfour_raw_len * sizeof(unsigned char));
		word_arrays[i] = fortyfour_raw;
		word_arrays_sizes[i]=fortyfour_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"fortyfive")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fortyfive_raw_len * sizeof(unsigned char));
		word_arrays[i] = fortyfive_raw;
		word_arrays_sizes[i]=fortyfive_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"fortysix")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fortysix_raw_len * sizeof(unsigned char));
		word_arrays[i] = fortysix_raw;
		word_arrays_sizes[i]=fortysix_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"fortyseven")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fortyseven_raw_len * sizeof(unsigned char));
		word_arrays[i] = fortyseven_raw;
		word_arrays_sizes[i]=fortyseven_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"fortyeight")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fortyeight_raw_len * sizeof(unsigned char));
		word_arrays[i] = fortyeight_raw;
		word_arrays_sizes[i]=fortyeight_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"fortynine")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fortynine_raw_len * sizeof(unsigned char));
		word_arrays[i] = fortynine_raw;
		word_arrays_sizes[i]=fortynine_raw_len;
	    }
	     if (g_strcmp0(word_str_lower,"fifty")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fifty_raw_len * sizeof(unsigned char));
		word_arrays[i] = fifty_raw;
		word_arrays_sizes[i]=fifty_raw_len;
	    }																																																																																																
	      if (g_strcmp0(word_str_lower,"fiftyone")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fiftyone_raw_len * sizeof(unsigned char));
		word_arrays[i] = fiftyone_raw;
		word_arrays_sizes[i]=fiftyone_raw_len;
	    }
	      if (g_strcmp0(word_str_lower,"fiftytwo")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fiftytwo_raw_len * sizeof(unsigned char));
		word_arrays[i] = fiftytwo_raw;
		word_arrays_sizes[i]=fiftytwo_raw_len;
	    }
	      if (g_strcmp0(word_str_lower,"fiftythree")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fiftythree_raw_len * sizeof(unsigned char));
		word_arrays[i] = fiftythree_raw;
		word_arrays_sizes[i]=fiftythree_raw_len;
	    }
	      if (g_strcmp0(word_str_lower,"fiftyfour")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fiftyfour_raw_len * sizeof(unsigned char));
		word_arrays[i] = fiftyfour_raw;
		word_arrays_sizes[i]=fiftyfour_raw_len;
	    }
	      if (g_strcmp0(word_str_lower,"fiftyfive")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fiftyfive_raw_len * sizeof(unsigned char));
		word_arrays[i] = fiftyfive_raw;
		word_arrays_sizes[i]=fiftyfive_raw_len;
	    }
	      if (g_strcmp0(word_str_lower,"fiftysix")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fiftysix_raw_len * sizeof(unsigned char));
		word_arrays[i] = fiftysix_raw;
		word_arrays_sizes[i]=fiftysix_raw_len;
	    }
	      if (g_strcmp0(word_str_lower,"fiftyseven")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fiftyseven_raw_len * sizeof(unsigned char));
		word_arrays[i] = fiftyseven_raw;
		word_arrays_sizes[i]=fiftyseven_raw_len;
	    }
	      if (g_strcmp0(word_str_lower,"fiftyeight")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fiftyeight_raw_len * sizeof(unsigned char));
		word_arrays[i] = fiftyeight_raw;
		word_arrays_sizes[i]=fiftyeight_raw_len;
	    }
	      if (g_strcmp0(word_str_lower,"fiftynine")==0) {		
		word_arrays[i] = (unsigned char*)malloc(fiftynine_raw_len * sizeof(unsigned char));
		word_arrays[i] = fiftynine_raw;
		word_arrays_sizes[i]=fiftynine_raw_len;
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
	    
	    if (g_strcmp0(word_str_lower,"theatre")==0) {		
		word_arrays[i] = (unsigned char*)malloc(theatre_raw_len * sizeof(unsigned char));
		word_arrays[i] = theatre_raw;
		word_arrays_sizes[i]=theatre_raw_len;	
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
	
	}//for

} //get word arrays

