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
#include "notabledates.h"

//======================================================================
static int first_day_of_month(int month, int year)
{
    if (month < 3) {
        month += 12;
        year--;
    }
    int century = year / 100;
    year = year % 100;
    return (((13 * (month + 1)) / 5) +
            (century / 4) + (5 * century) +
            year + (year / 4)) % 7;
}
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


//======================================================================

gboolean is_notable_date(int day, int month, int year) 
{

// UK public holidays
// New Year's Day: 1 January (DONE)
// Good Friday: March or April  (DONE)
// Easter Monday: March or April (DONE)
// Early May: First Monday of May (DONE)
// Spring Bank Holiday: Last Monday of May (DONE)
// Summer Bank Holiday: Last Monday of August (DONE)
// Christmas Day: 25 December (DONE)
// Boxing day: 26 December (DONE)

	//markup notable dates
	
	if (month==12 && day==25) {
	//christmas day
	return TRUE;
	}

	if (month==12 && day==26) {
	//boxing day
	return TRUE;
	}
	
	if (month==1 && day ==1) {
	//new year
	 return TRUE;
	}
	
	if (month==2 && day ==14) {
	//valentine
	 return TRUE;
	}
	
	if (month==3 && day ==1) {
		return TRUE; // " saint davids day ";	
	}
	
	if (month==3 && day ==17) {
		return TRUE; // " saint patricks day ";	
	}
		
	if (month==4 && day ==23) {
		return TRUE; //" saint georges day ";	
	}
	
	

	if (month == 5) {
     //May complicated
     GDate *first_monday_may;
     first_monday_may = g_date_new_dmy(1, month, year);

     while (g_date_get_weekday(first_monday_may) != G_DATE_MONDAY)
       g_date_add_days(first_monday_may,1);

     int may_day = g_date_get_day(first_monday_may);

     if( day==may_day) return TRUE;
     //else return FALSE;

     int days_in_may =g_date_get_days_in_month (month, year);
     int plus_days = 0;

     if (may_day + 28 <= days_in_may) {
       plus_days = 28;
     } else {
       plus_days = 21;
     }

     GDate *spring_bank =g_date_new_dmy (may_day, month, year);

     g_date_add_days(spring_bank,plus_days);

     int spring_bank_day = g_date_get_day(spring_bank);

     if (g_date_valid_dmy (spring_bank_day,month,year) && day ==spring_bank_day)
     return TRUE;
	} //month==5 (may)

	GDate *easter_date =calculate_easter(year);
	int easter_day = g_date_get_day(easter_date);
	int easter_month =g_date_get_month(easter_date);

	if(month==easter_month && day == easter_day)
	{
	//easter day
	return TRUE;
	}
	g_date_subtract_days(easter_date,2);
	int easter_friday = g_date_get_day(easter_date);
	int easter_friday_month =g_date_get_month(easter_date);

	if(month==easter_friday_month && day ==easter_friday)
	{
	//easter friday
	return TRUE;
	}

	g_date_add_days(easter_date,3);
	int easter_monday = g_date_get_day(easter_date); //easter monday
	int easter_monday_month =g_date_get_month(easter_date);

	if(month==easter_monday_month && day ==easter_monday)
	{
	//easter monday
	return TRUE;
	}

	if (month == 8) {
      //August complicated
    GDate *first_monday_august;
     first_monday_august = g_date_new_dmy(1, month, year);

     while (g_date_get_weekday(first_monday_august) != G_DATE_MONDAY)
       g_date_add_days(first_monday_august,1);

     int august_day = g_date_get_day(first_monday_august);
     int days_in_august =g_date_get_days_in_month (month, year);
     int plus_days = 0;

     if (august_day + 28 <= days_in_august) {
       plus_days = 28;
     } else {
       plus_days = 21;
     }

     GDate *august_bank =g_date_new_dmy (august_day, month, year);

     g_date_add_days(august_bank,plus_days);

     int august_bank_day = g_date_get_day(august_bank);

     if (g_date_valid_dmy (august_bank_day,month,year) && day ==august_bank_day)
     return TRUE;
    } //month==8
    
    if (month==10 && day ==25) {
		return TRUE; // " saint crispins day ";	
	}
	
	if (month==10 && day ==30) {
		return TRUE; // " st andrews";	
	}
	
	if (month==10 && day ==31) {
		return TRUE; // " halloween";	
	}
	
	if (month==11 && day ==5) {
		return TRUE; // " guy fawkes";	
	}

	return FALSE;
}
//=====================================================================

char* get_notable_date_str(int day, int month, int year) 
{

// UK public holidays
// New Year's Day: 1 January (DONE)
// Good Friday: March or April  (DONE)
// Easter Monday: March or April (DONE)
// Early May: First Monday of May (TODO)
// Spring Bank Holiday: Last Monday of May (DONE)
// Summer Bank Holiday: Last Monday of August (DONE)
// Christmas Day: 25 December (DONE)
// Boxing day: 26 December (DONE)

	//markup public holidays
	if (month==1 && day ==1) {
	return " New Year";
	}

	if (month==12 && day==25) {
	//christmas day
	return " Christmas Day";
	}

	if (month==12 && day==26) {
	//boxing day
	return " Boxing Day";
	}
	
	if (month==2 && day ==14) {
	return " Valentine Day";
	}
	
	if (month==3 && day ==1) {
		return " St. Davids Day"; // " saint davids day ";	
	}
	
	if (month==3 && day ==17) {
		return " St. Patricks Day";  
	}
		
	if (month==4 && day ==23) {
		return " St. Georges Day";	
	}

	if (month == 5) {
     //May complicated
     GDate *first_monday_may;
     first_monday_may = g_date_new_dmy(1, month, year);


     while (g_date_get_weekday(first_monday_may) != G_DATE_MONDAY)
       g_date_add_days(first_monday_may,1);

     int may_day = g_date_get_day(first_monday_may);

     if( day==may_day) return " Public Holiday"; //may bank holiday

     int days_in_may =g_date_get_days_in_month (month, year);

     int plus_days = 0;

     if (may_day + 28 <= days_in_may) {
       plus_days = 28;
     } else {
       plus_days = 21;
     }

     GDate *spring_bank =g_date_new_dmy (may_day, month, year);
     g_date_add_days(spring_bank,plus_days);
     int spring_bank_day = g_date_get_day(spring_bank);
     if (g_date_valid_dmy (spring_bank_day,month,year) && day ==spring_bank_day)
     return " Spring Bank Holiday";   //spring bank holiday

	} //month ==5 (May)

	GDate *easter_date =calculate_easter(year);
	int easter_day = g_date_get_day(easter_date);
	int easter_month =g_date_get_month(easter_date);

	if(month==easter_month && day == easter_day)
	{
	//easter day
	return " Easter Day";
	}

	g_date_subtract_days(easter_date,2);
	int easter_friday = g_date_get_day(easter_date);
	int easter_friday_month =g_date_get_month(easter_date);

	if(month==easter_friday_month && day ==easter_friday)
	{
	//easter friday
	return " Easter Friday";
	}

	g_date_add_days(easter_date,3);
	int easter_monday = g_date_get_day(easter_date); //easter monday
	int easter_monday_month =g_date_get_month(easter_date);

	if(month==easter_monday_month && day ==easter_monday)
	{
	//easter monday
	return " Easter Monday";
	}

	if (month == 8) {
      //August complicated
    GDate *first_monday_august;
     first_monday_august = g_date_new_dmy(1, month, year);

     while (g_date_get_weekday(first_monday_august) != G_DATE_MONDAY)
       g_date_add_days(first_monday_august,1);

     int august_day = g_date_get_day(first_monday_august);


     int days_in_august =g_date_get_days_in_month (month, year);
     int plus_days = 0;

     if (august_day + 28 <= days_in_august) {
       plus_days = 28;
     } else {
       plus_days = 21;
     }

     GDate *august_bank =g_date_new_dmy (august_day, month, year);

     g_date_add_days(august_bank,plus_days);

     int august_bank_day = g_date_get_day(august_bank);

     if (g_date_valid_dmy (august_bank_day,month,year) && day ==august_bank_day)
     return " Public Holiday";   //august bank holiday

    } //month==8
    
    if (month==10 && day ==25) {
		return " St. Crispins Day";	
	}
	
	if (month==10 && day ==30) {
		return "St. Andrews Day"; // " st andrews";	
	}
	
	if (month==10 && day ==31) {
		return " Halloween ";	
	}
	
	if (month==11 && day ==5) 
	{
		return "Guy Fawkes"; // guy fawkes	
	}

	return "";
}

//======================================================================

char* get_notable_date_speak_str(int day, int month, int year)
{
	

	if (month==12 && day==25) {
	//christmas day
	return " christmas day ";
	}

	if (month==12 && day==26) {
	//boxing day
	return " boxing day ";
	}
	
	if (month==1 && day ==1) {
	return " new year ";
	}
	
	if (month==2 && day ==14) {
	return " valentine day ";
	}
	
	
	if (month==3 && day ==1) {
		return " saint davids day "; // " saint davids day ";	
	}
	
	if (month==3 && day ==17) {
		return " saint patricks day "; // " saint patricks day ";	
	}
	
		
	if (month==4 && day ==23) {
		return " saint georges day ";	
	}
	
	if (month == 5) {
     //May complicated
     GDate *first_monday_may;
     first_monday_may = g_date_new_dmy(1, month, year);


     while (g_date_get_weekday(first_monday_may) != G_DATE_MONDAY)
       g_date_add_days(first_monday_may,1);

     int may_day = g_date_get_day(first_monday_may);

     if( day==may_day) return " public holiday "; //may bank holiday

     int days_in_may =g_date_get_days_in_month (month, year);

     int plus_days = 0;

     if (may_day + 28 <= days_in_may) {
       plus_days = 28;
     } else {
       plus_days = 21;
     }

     GDate *spring_bank =g_date_new_dmy (may_day, month, year);
     g_date_add_days(spring_bank,plus_days);
     int spring_bank_day = g_date_get_day(spring_bank);
     if (g_date_valid_dmy (spring_bank_day,month,year) && day ==spring_bank_day)
     return " spring bank holiday ";   //spring bank holiday

	} //month ==5 (May)

	GDate *easter_date =calculate_easter(year);
	int easter_day = g_date_get_day(easter_date);
	int easter_month =g_date_get_month(easter_date);

	if(month==easter_month && day == easter_day)
	{
	//easter day
	return " easter day ";
	}

	g_date_subtract_days(easter_date,2);
	int easter_friday = g_date_get_day(easter_date);
	int easter_friday_month =g_date_get_month(easter_date);

	if(month==easter_friday_month && day ==easter_friday)
	{
	//easter friday
	return " easter friday ";
	}

	g_date_add_days(easter_date,3);
	int easter_monday = g_date_get_day(easter_date); //easter monday
	int easter_monday_month =g_date_get_month(easter_date);

	if(month==easter_monday_month && day ==easter_monday)
	{
	//easter monday
	return " easter monday ";
	}

	if (month == 8) {
      //August complicated
    GDate *first_monday_august;
     first_monday_august = g_date_new_dmy(1, month, year);

     while (g_date_get_weekday(first_monday_august) != G_DATE_MONDAY)
       g_date_add_days(first_monday_august,1);

     int august_day = g_date_get_day(first_monday_august);


     int days_in_august =g_date_get_days_in_month (month, year);
     int plus_days = 0;

     if (august_day + 28 <= days_in_august) {
       plus_days = 28;
     } else {
       plus_days = 21;
     }

     GDate *august_bank =g_date_new_dmy (august_day, month,year);

     g_date_add_days(august_bank,plus_days);

     int august_bank_day = g_date_get_day(august_bank);

     if (g_date_valid_dmy (august_bank_day,month,year) && day ==august_bank_day)
     return " public holiday ";   //august bank holiday

    } //month==8
    
    if (month==10 && day ==25) {
		return " saint crispins day ";	
	}
	
	if (month==10 && day ==30) {
		return " saint andrews day "; // " st andrews";	
	}
	
	if (month==10 && day ==31) {
		return " halloween ";	
	}
	
	if (month==11 && day ==5) 
	{
		return " guy fawkes night "; // guy fawkes	
	}


	return "";
	
}

