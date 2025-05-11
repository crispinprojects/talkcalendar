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
#include "wordrules.h"

char *word_rules(char *input_str)
{
	
	//g_print("word substitution rules called\n");	
	char* out_str="";
	gchar** word_str;		 
	word_str = g_strsplit (input_str, " ", 0); //split on space
	int j=0;			   
	while(word_str[j] != NULL)
	{
	char* word = g_ascii_strdown(word_str[j], -1); //convert to lower case
	
	//a-words
	
	if (g_strcmp0(word,"accounting")==0)
	{
		word ="account ing";
	}
	if (g_strcmp0(word,"accountable")==0)
	{
		word ="account able";
	}
	if (g_strcmp0(word,"agreement")==0)
	{
		word ="agree ment";
	}
		
	
	if (g_strcmp0(word,"antifreeze")==0)
	{
		word ="anti freeze";
	}
	
	if (g_strcmp0(word,"appointments")==0)
	{
		word ="appointment";
	}
	
	if (g_strcmp0(word,"aunts")==0)
	{
		word ="aunt";
		
	}	
	if (g_strcmp0(word,"aunty")==0)
	{
		word ="auntie";
	}
	
	//b words
	if (g_strcmp0(word,"bankable")==0)
	{
		word ="bank able";
	}
	
	if (g_strcmp0(word,"bedroom")==0)
	{
		word ="bed room";
	}
	if (g_strcmp0(word,"books")==0)
	{
		word ="book";
	}
	
	if (g_strcmp0(word,"bookable")==0)
	{
		word ="book able";
	}
	
	if (g_strcmp0(word,"booking")==0)
	{
		//word ="book ing";
		word ="book ing";
	}
	
	if (g_strcmp0(word,"boyfriend")==0)
	{
		
		word ="boy friend";
	}
	//c-words
		
	if (g_strcmp0(word,"careful")==0)
	{
		word ="care";
	}
	if (g_strcmp0(word,"childrens")==0)
	{
		word ="children";
	}
	if (g_strcmp0(word,"contacts")==0)
	{
		word ="contact";
	}
	if (g_strcmp0(word,"cousins")==0)
	{
		word ="cousin";
	}
	
	//d-words
	
	if (g_strcmp0(word,"dateline")==0)
	{
		word ="date line";
	}
		
	if (g_strcmp0(word,"dating")==0)
	{
		word ="date ing";
	}
	
	if (g_strcmp0(word,"daybook")==0)
	{
		word ="day book";
	}
	
	if (g_strcmp0(word,"daycare")==0)
	{
		word ="day care";
	}
	
	if (g_strcmp0(word,"daytime")==0)
	{
		word ="day time";
	}
	
	if (g_strcmp0(word,"daystar")==0)
	{
		word ="day star";
	}
	
	if (g_strcmp0(word,"daywork")==0)
	{
		word ="day work";
	}
	
	if (g_strcmp0(word,"deadlines")==0)
	{
		word ="deadline";
	}
	
	//e-words
	if (g_strcmp0(word,"engaged")==0)
	{
		word ="engage";
	}
	
	if (g_strcmp0(word,"engaging")==0)
	{
		word ="engage ing";
	}
	if (g_strcmp0(word,"engagement")==0)
	{
		word ="engage ment";
	}
	
	
	//f-words
	if (g_strcmp0(word,"freds")==0)
	{
		word ="fred";
	}
	
		
	if (g_strcmp0(word,"fireplace")==0)
	{
		word ="fire place";
	}
	
	if (g_strcmp0(word,"firestation")==0)
	{
		word ="fire station";
	}
	
	if ((g_strcmp0(word,"firework")==0) || (g_strcmp0(word,"fireworks")==0))
	{
		word ="fire work";
	}
	
	if (g_strcmp0(word,"friends")==0)
	{
		word ="friend";
	}
	
	//g-words
	if ((g_strcmp0(word,"giftshop")==0) || (g_strcmp0(word,"giftshops")==0))
	{
		word ="gift shop";
	}
	
	if ((g_strcmp0(word,"girlfriend")==0) || (g_strcmp0(word,"girlfriends")==0))
	{
		word ="girl friend";
	}	
	
	if ((g_strcmp0(word,"grandchildren")==0) || (g_strcmp0(word,"grandchildrens")==0))
	{
		word ="grand children";
	}
	
	if ((g_strcmp0(word,"granddad")==0) || (g_strcmp0(word,"grandad")==0))
	{
		word ="grand dad";
	}	
	if ((g_strcmp0(word,"granddads")==0) || (g_strcmp0(word,"grandads")==0))
	{
		word ="grand dads";
	}	
	if (g_strcmp0(word,"grandmother")==0)
	{
		word ="grand mother";
	}	
	if (g_strcmp0(word,"grandmothers")==0)
	{
		word ="grand mothers";
	}
	
	//h words
	if (g_strcmp0(word,"higher")==0)
	{
		word ="high";
	}
	if (g_strcmp0(word,"hearing")==0)
	{
		word ="hear ing";
	}
	//i words
	
	//j words
	if (g_strcmp0(word,"jeweller")==0)
	{
		word ="jeweler";
	}
	
	if (g_strcmp0(word,"lastly")==0)
	{
		word ="last"; 
	}
	
	if (g_strcmp0(word,"lasting")==0)
	{
		word ="last ing"; 
	}
		
	
	if (g_strcmp0(word,"looked")==0)
	{
		word ="look"; 
	}
	
	if (g_strcmp0(word,"looker")==0)
	{
		word ="look"; 
	}
	
	if (g_strcmp0(word,"lookover")==0)
	{
		word ="look over"; //use over prefix
	}
	
	if ((g_strcmp0(word,"lunchtime")==0) || (g_strcmp0(word,"lunchtimes")==0))
	{
		word ="lunch time"; 
	}
	
	
	//m-words
	
	if (g_strcmp0(word,"mayday")==0)
	{
		word ="may day";
	}
	
	if (g_strcmp0(word,"meetings")==0)
	{
		word ="meeting";
	}
	
	if (g_strcmp0(word,"minimarket")==0)
	{
		word ="mini market";
	}
	
	if (g_strcmp0(word,"ministore")==0)
	{
		word ="mini store";
	}
	

	
	if (g_strcmp0(word,"moving")==0)
	{
		word ="move ing";
	}
	//n-words
	if (g_strcmp0(word,"neighbours")==0)
	{
		word ="neighbour";
	}
	
	if (g_strcmp0(word,"netflixs")==0)
	{
		word ="netflix";
	}
	
	//o words
	if (g_strcmp0(word,"outofoffice")==0)
	{
		word ="out of office";
	}
	
	if (g_strcmp0(word,"overdevelopment")==0)
	{
		word ="over development";
	}
	
	//if (g_strcmp0(word,"online")==0) //single word recording
	//{
		//word ="on line";
	//}
	
	if (g_strcmp0(word,"opening")==0)
	{
		word ="open ing";
	}
	
	if (g_strcmp0(word,"onlooking")==0)
	{
		word ="on look ing";
	}
	
	if (g_strcmp0(word,"overlook")==0)
	{
		word ="over look";
	}
	
		
	if (g_strcmp0(word,"overpayment")==0)
	{
		word ="over payment";
	}
	
	// p words
	if (g_strcmp0(word,"placement")==0)
	{
		word ="place ment";
	}
	if (g_strcmp0(word,"postoffice")==0)
	{
		word ="post office";
	}
	
		
	
	// r words
	
		
	//s-words
	
	if ((g_strcmp0(word,"seafood")==0) || (g_strcmp0(word,"seafoods")==0))
	{
		word ="sea food";
	}
	
	if ((g_strcmp0(word,"seaside")==0) || (g_strcmp0(word,"seafoods")==0))
	{
		word ="sea side";
	}
	
	if (g_strcmp0(word,"semicircle")==0)
	{
		word ="semi circle";
	}
	
	if (g_strcmp0(word,"shoezone")==0)
	{
		word ="shoe zone";
	}
	
	if ((g_strcmp0(word,"st")==0) || (g_strcmp0(word,"st.")==0))
	{
		word ="saint";
	}
	
	if (g_strcmp0(word,"subagreement")==0)
	{
		word ="sub agree ment";
	}
	
	if (g_strcmp0(word,"subdevelopment")==0)
	{
		word ="sub development";
	}
	
    if (g_strcmp0(word,"submarine")==0)
	{
		word ="sub marine";
	}
	
	if (g_strcmp0(word,"subpostoffice")==0)
	{
		word ="sub post office";
	}
	
	if (g_strcmp0(word,"supercar")==0)
	{
		word ="super car";
	}
	
	if (g_strcmp0(word,"supermarket")==0)
	{
		word ="super market";
	}
		
	if (g_strcmp0(word,"superstar")==0)
	{
		word ="super star";
	}
		
	//t words
	
	//t words
	if ((g_strcmp0(word,"timetable")==0) || (g_strcmp0(word,"timetables")==0))
	{
		
		word ="time table";
	}
	
	if ((g_strcmp0(word,"traveling")==0) || (g_strcmp0(word,"travelling")==0))
	{
		//word ="travel ing";
		word ="travel";
	}
	
	if ((g_strcmp0(word,"travelodge")==0) || (g_strcmp0(word,"travelling")==0))
	{
		//word ="travel ing";
		word ="travel lodge";
	}
	
	
	if (g_strcmp0(word,"transport")==0)
	{
		word ="trans port";
	}
		
	//u-words
	if (g_strcmp0(word,"uncles")==0)
	{
		word ="uncle";
	}
	
		
	if (g_strcmp0(word,"underline")==0)
	{
		word ="under line";
	}
	
	if (g_strcmp0(word,"undersea")==0)
	{
		word ="under sea";
	}
	
	
	if (g_strcmp0(word,"workday")==0)
	{
		word ="work day";
	}
	
	if (g_strcmp0(word,"workdays")==0)
	{
		word ="work days";
	}
	
	//name rules
	
	if (g_strcmp0(word,"alans")==0)
	{
		word ="alan";
	}
	if (g_strcmp0(word,"alexs")==0)
	{
		word ="alex";
	}
	if (g_strcmp0(word,"alexanders")==0)
	{
		word ="alexander";
	}
	if (g_strcmp0(word,"alfs")==0)
	{
		word ="alf";
	}
	if (g_strcmp0(word,"alfreds")==0)
	{
		word ="alfred";
	}
	if (g_strcmp0(word,"alices")==0)
	{
		word ="alice";
	}
	if (g_strcmp0(word,"alisons")==0)
	{
		word ="alison";
	}
	if (g_strcmp0(word,"allison")==0)
	{
		word ="alison";
	}
	if (g_strcmp0(word,"allisons")==0)
	{
		word ="alison";
	}
	if (g_strcmp0(word,"alisters")==0)
	{
		word ="alister";
	}
	if (g_strcmp0(word,"ambers")==0)
	{
		word ="amber";
	}
	if (g_strcmp0(word,"amelias")==0)
	{
		word ="amelia";
	}
	if (g_strcmp0(word,"annes")==0)
	{
		word ="annes";
	}	
	if (g_strcmp0(word,"andoras")==0)
	{
		word ="andora";
	}
	if (g_strcmp0(word,"andreas")==0)
	{
		word ="andrea";
	}
	if (g_strcmp0(word,"andrews")==0)
	{
		word ="andrew";
	}	
	if (g_strcmp0(word,"andys")==0)
	{
		word ="andy";
	}
	if (g_strcmp0(word,"angelas")==0)
	{
		word ="angela";
	}
	if (g_strcmp0(word,"angelinas")==0)
	{
		word ="angelina";
	}
	if (g_strcmp0(word,"annas")==0)
	{
		word ="anna";
	}
	if (g_strcmp0(word,"annabel")==0)
	{
		word ="annabel";
	}	
	if (g_strcmp0(word,"annes")==0)
	{
		word ="anne";
	}
	if (g_strcmp0(word,"anthonys")==0)
	{
		word ="anthony";
	}
	if (g_strcmp0(word,"aubreys")==0)
	{
		word ="aubrey";
	}
	if (g_strcmp0(word,"audreys")==0)
	{
		word ="audrey";
	}
	
	if (g_strcmp0(word,"beths")==0)
	{
		word ="beth";
	}
	if (g_strcmp0(word,"bethanys")==0)
	{
		word ="bethany";
	}
	if (g_strcmp0(word,"betsy")==0)
	{
		word ="betsy";
	}
	if (g_strcmp0(word,"billie")==0)
	{
		word ="billy";
	}
	if ((g_strcmp0(word,"billys")==0)|| (g_strcmp0(word,"billies")==0))
	{
		word ="billy";
	}
		
	if ((g_strcmp0(word,"katherine")==0) || (g_strcmp0(word,"kathryn")==0) || (g_strcmp0(word,"katharine")==0))
	{
		word ="catherine";
	}
	if ((g_strcmp0(word,"katherines")==0) || (g_strcmp0(word,"kathryns")==0) || (g_strcmp0(word,"katharines")==0))
	{
		word ="catherine";
	}
	if (g_strcmp0(word,"catherines")==0)
	{
		word ="catherine";
	}
	
	if (g_strcmp0(word,"charlottes")==0)
	{
		word ="charlotte";
	}
	if (g_strcmp0(word,"claires")==0)
	{
		word ="claire";
	}
	if (g_strcmp0(word,"claras")==0)
	{
		word ="clara";
	}
	if (g_strcmp0(word,"clarences")==0)
	{
		word ="clarence";
	}
	if (g_strcmp0(word,"clarissas")==0)
	{
		word ="clarissa";
	}
	if (g_strcmp0(word,"claudes")==0)
	{
		word ="claude";
	}
	
	if (g_strcmp0(word,"daisy")==0)
	{
		word ="daisy";
	}
	if (g_strcmp0(word,"danielles")==0)
	{
		word ="danielle";
	}
	if (g_strcmp0(word,"dans")==0)
	{
		word ="dan";
	}
	if (g_strcmp0(word,"dannie")==0)
	{
		word ="danny";
	}
	if ((g_strcmp0(word,"dannys")==0) || (g_strcmp0(word,"dannies")==0))
	{
		word ="danny";
	}
	if (g_strcmp0(word,"debbies")==0)
	{
		word ="debbie";
	}
	if (g_strcmp0(word,"debbys")==0)
	{
		word ="debby";
	}
	if (g_strcmp0(word,"deborahs")==0)
	{
		word ="deborah";
	}
	if (g_strcmp0(word,"dons")==0)
	{
		word ="don";
	}
	if (g_strcmp0(word,"donalds")==0)
	{
		word ="donald";
	}
	if (g_strcmp0(word,"doras")==0)
	{
		word ="dora";
	}
	
	
	if (g_strcmp0(word,"eltons")==0)
	{
		word ="elton";
	}
	
	if (g_strcmp0(word,"elishas")==0)
	{
		word ="elisha";
	}
	
	if (g_strcmp0(word,"elizas")==0)
	{
		word ="eliza";
	}
	if (g_strcmp0(word,"elizabeths")==0)
	{
		word ="elizabeth";
	}
	if (g_strcmp0(word,"elliots")==0)
	{
		word ="elliot";
	}
	if (g_strcmp0(word,"emmas")==0)
	{
		word ="emma";
	}
	if (g_strcmp0(word,"evans")==0)
	{
		word ="evan";
	}
	if (g_strcmp0(word,"fionas")==0)
	{
		word ="fiona";
	}
	if (g_strcmp0(word,"francescas")==0)
	{
		word ="francesca";
	}	
	if (g_strcmp0(word,"franks")==0)
	{
		word ="frank";
	}
	if (g_strcmp0(word,"freds")==0)
	{
		word ="fred";
	}
	
	if (g_strcmp0(word,"freddy")==0)
	{
		word ="fredie";
	}
	if ((g_strcmp0(word,"freddies")==0) || (g_strcmp0(word,"freddys")==0))
	{
		word ="freddie";
	}
	if (g_strcmp0(word,"fredericks")==0)
	{
		word ="frederick";
	}
	
	if ((g_strcmp0(word,"gaile")==0) || (g_strcmp0(word,"gail")==0) || (g_strcmp0(word,"gayle")==0))
	{
		word ="gale";
	}
	
	if ((g_strcmp0(word,"gales")==0) || (g_strcmp0(word,"gailes")==0) || (g_strcmp0(word,"gails")==0) || (g_strcmp0(word,"gayles")==0))
	{
		word ="gale";
	}
	
	if ((g_strcmp0(word,"freddies")==0) || (g_strcmp0(word,"freddys")==0))
	{
		word ="freddie";
	}
	
	//G names
	
	if (g_strcmp0(word,"jeff")==0)
	{
		word ="geoff";
	}
	
	if ((g_strcmp0(word,"geoffs")==0) || (g_strcmp0(word,"jeffs")==0))
	{
		word ="geoff";
	}
	
	if ((g_strcmp0(word,"geoffreys")==0) || (g_strcmp0(word,"jefferys")==0))
	{
		word ="geoffrey";
	}
	if (g_strcmp0(word,"georginas")==0)
	{
		word ="georgina";
	}
	
	//H names
	
	if (g_strcmp0(word,"hanna")==0)
	{
		word ="hannah";
	}
	if ((g_strcmp0(word,"hannas")==0) || (g_strcmp0(word,"hannahs")==0))
	{
		word ="hannah";
	}
	if (g_strcmp0(word,"harolds")==0)
	{
		word ="harold";
	}
	if (g_strcmp0(word,"harrys")==0)
	{
		word ="harry";
	}
	if (g_strcmp0(word,"hectors")==0)
	{
		word ="hector";
	}
	if (g_strcmp0(word,"helens")==0)
	{
		word ="helen";
	}
	if (g_strcmp0(word,"herberts")==0)
	{
		word ="herbert";
	}
	if (g_strcmp0(word,"humphreys")==0)
	{
		word ="humphrey";
	}
	
	//I names
	if (g_strcmp0(word,"ians")==0)
	{
		word ="ian";
	}
	if (g_strcmp0(word,"irenes")==0)
	{
		word ="irene";
	}
	if (g_strcmp0(word,"isaacs")==0)
	{
		word ="isaac";
	}
	if (g_strcmp0(word,"isabels")==0)
	{
		word ="isabel";
	}
	if (g_strcmp0(word,"isabellas")==0)
	{
		word ="isabella";
	}
	if (g_strcmp0(word,"ivans")==0)
	{
		word ="ivan";
	}
	if ((g_strcmp0(word,"ivys")==0) || (g_strcmp0(word,"ivies")==0))
	{
		word ="ivy";
	}
	
	//J words
	if (g_strcmp0(word,"jacks")==0)
	{
		word ="jack";
	}
	
	if (g_strcmp0(word,"jacky")==0)
	{
		word ="jackie";
	}
	
	if ((g_strcmp0(word,"jackies")==0) || (g_strcmp0(word,"jackys")==0))
	{
		word ="jackie";
	}
	
	if (g_strcmp0(word,"jacobs")==0)
	{
		word ="jacob";
	}
	
	if (g_strcmp0(word,"jacquelines")==0)
	{
		word ="jacqueline";
	}
	
	if (g_strcmp0(word,"jamies")==0)
	{
		word ="jamie";
	}
	
	if (g_strcmp0(word,"johns")==0)
	{
		word ="john";
	}
	
	//K words
	
	if (g_strcmp0(word,"karren")==0)
	{
		word ="karen";
	}
	
	if ((g_strcmp0(word,"karens")==0) || (g_strcmp0(word,"karrens")==0))
	{
		word ="karen";
	}
	
	if (g_strcmp0(word,"kates")==0)
	{
		word ="kate";
	}
	
	
	
	if (g_strcmp0(word,"kens")==0)
	{
		word ="ken";
	}
	if (g_strcmp0(word,"kenneths")==0)
	{
		word ="kenneth";
	}
	
	//L names
	if ((g_strcmp0(word,"lillys")==0) || (g_strcmp0(word,"lillies")==0))
	{
		word ="lilly";
	}
	if (g_strcmp0(word,"louisas")==0)
	{
		word ="louisa";
	}
	
	//M names
	
	if (g_strcmp0(word,"madelines")==0)
	{
		word ="madeline";
	}
	if (g_strcmp0(word,"marys")==0)
	{
		word ="mary";
	}
	if (g_strcmp0(word,"matts")==0)
	{
		word ="matt";
	}
	if (g_strcmp0(word,"matthews")==0)
	{
		word ="matthew";
	}
	if ((g_strcmp0(word,"matthiass")==0) || (g_strcmp0(word,"mattathias")==0))
	{
		word ="matthias";
	}
	
	
	if (
	(g_strcmp0(word,"muhammed")==0) 
	|| (g_strcmp0(word,"muhamad")==0) 
	|| (g_strcmp0(word,"mohammad")==0)
	|| (g_strcmp0(word,"mahammad")==0)
	|| (g_strcmp0(word,"maxammed")==0)
	|| (g_strcmp0(word,"mehemmed")==0)
	|| (g_strcmp0(word,"mohamad")==0)
	|| (g_strcmp0(word,"mohamed")==0)	
	)
	{
		word ="muhammad";
	}
	
	if (
	(g_strcmp0(word,"muhammeds")==0) 
	|| (g_strcmp0(word,"muhamads")==0) 
	|| (g_strcmp0(word,"mohammads")==0)
	|| (g_strcmp0(word,"mahammads")==0)
	|| (g_strcmp0(word,"maxammeds")==0)
	|| (g_strcmp0(word,"mehemmeds")==0)
	|| (g_strcmp0(word,"mohamads")==0)
	|| (g_strcmp0(word,"mohameds")==0)	
	)
	{
		word ="muhammad";
	}
	
	
	
	if (g_strcmp0(word,"muhammads")==0)
	{
		word ="muhammad";
	}
	
	//N names
	if (g_strcmp0(word,"naomis")==0)
	{
		word ="naomi";
	}
	if (g_strcmp0(word,"normans")==0)
	{
		word ="norman";
	}
	
	//O names
	if (g_strcmp0(word,"olivers")==0)
	{
		word ="oliver";
	}
	if (g_strcmp0(word,"olivias")==0)
	{
		word ="olivia";
	}
	
	if (g_strcmp0(word,"pams")==0)
	{
		word ="pam";
	}
	if (g_strcmp0(word,"pamelas")==0)
	{
		word ="pamela";
	}
	if (g_strcmp0(word,"pauls")==0)
	{
		word ="paul";
	}	
	if (g_strcmp0(word,"paulas")==0)
	{
		word ="paula";
	}
	if (g_strcmp0(word,"paulines")==0)
	{
		word ="pauline";
	}
	if (g_strcmp0(word,"penelopes")==0)
	{
		word ="penelope";
	}
	if (g_strcmp0(word,"pennys")==0)
	{
		word ="penny";
	}
	if (g_strcmp0(word,"percys")==0)
	{
		word ="percy";
	}
	if (g_strcmp0(word,"perrys")==0)
	{
		word ="perry";
	}
	if (g_strcmp0(word,"peters")==0)
	{
		word ="peter";
	}
	if (g_strcmp0(word,"phoebes")==0)
	{
		word ="phoebe";
	}
	
	//R names
	
	if (g_strcmp0(word,"richards")==0)
	{
		word ="richard";
	}
	if (g_strcmp0(word,"roses")==0)
	{
		word ="rose";
	}
	if (g_strcmp0(word,"rosemarys")==0)
	{
		word ="rosemary";
	}
	
	//S words
	
	if (g_strcmp0(word,"sabrinas")==0)
	{
		word ="sabrina";
	}
	
	if (g_strcmp0(word,"steves")==0)
	{
		word ="steve";
	}
	
	if ((g_strcmp0(word,"stevens")==0) || (g_strcmp0(word,"stephen")==0) || (g_strcmp0(word,"stephens")==0))
	{
		word ="steven";
	}
	
	//T words
	if (g_strcmp0(word,"thomass")==0)
	{
		word ="thomas";
	}
	if (g_strcmp0(word,"tiffanys")==0)
	{
		word ="tiffany";
	}
	if (g_strcmp0(word,"tildas")==0)
	{
		word ="tilda";
	}
	if (g_strcmp0(word,"tims")==0)
	{
		word ="tim";
	}
	if (g_strcmp0(word,"timothys")==0)
	{
		word ="timothy";
	}
	if (g_strcmp0(word,"toms")==0)
	{
		word ="tom";
	}
	
	if (g_strcmp0(word,"tomas")==0)
	{
		word ="thomas";
	}
	if (g_strcmp0(word,"trevors")==0)
	{
		word ="trevor";
	}
	
	//V names
	if (g_strcmp0(word,"vals")==0)
	{
		word ="val";
	}
	if (g_strcmp0(word,"valeries")==0)
	{
		word ="valerie";
	}
	
	//W names
	if (g_strcmp0(word,"winnies")==0)
	{
		word ="winnie";
	}
	if (g_strcmp0(word,"winnifreds")==0)
	{
		word ="winnifred";
	}
	if (g_strcmp0(word,"winstons")==0)
	{
		word ="winston";
	}
	
	//Z words
	if (g_strcmp0(word,"zaras")==0)
	{
		word ="zara";
	}
	if (g_strcmp0(word,"zoes")==0)
	{
		word ="zoe";
	}
	if (g_strcmp0(word,"zeldas")==0)
	{
		word ="zelda";
	}
	
	if ((g_strcmp0(word,"zak")==0) || (g_strcmp0(word,"zakk")==0) || (g_strcmp0(word,"zach")==0))
	{
		word ="zac";
	}
	
	if ((g_strcmp0(word,"zaks")==0) || (g_strcmp0(word,"zakks")==0) || (g_strcmp0(word,"zachs")==0))
	{
		word ="zac";
	}
	if (g_strcmp0(word,"zacs")==0)
	{
		word ="zac";
	}
	if (g_strcmp0(word,"zacharys")==0)
	{
		word ="zachary";
	}
	
		
	//g_print("%s\n",word);
	out_str= g_strconcat(out_str,word, " ", NULL);		
	j++;
	} //while loop words
		
	
	return out_str;
}

