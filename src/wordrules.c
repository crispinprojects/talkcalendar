/* wordrules.c
 *
 * Copyright 2025 Alan Crispin <crispinalan@gmail.com>
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
#include "wordrules.h"

char *word_rules(char *input_str)
{
	//TODO
	//g_print("word substitution rules called\n");	
	char* out_str="";
	gchar** word_str;		 
	word_str = g_strsplit (input_str, " ", 0); //split on space
	int j=0;			   
	while(word_str[j] != NULL)
	{
	char* word = g_ascii_strdown(word_str[j], -1); //convert to lower case
		
	//g_print("%s\n",word);
	
	//----------------------------------------------------
	//name spelling and abbreviation substitutions
	//----------------------------------------------------
	
	//------------------------------------------------------------------
	//A words
	//------------------------------------------------------------------
	if (g_strcmp0(word,"acct")==0)
	{
		word ="accountant";
	}
	
	if (g_strcmp0(word,"allison")==0)
	{
		word ="alison";
	}
	if (g_strcmp0(word,"allisons")==0)
	{
		word ="alisons";
	}
	
	//------------------------------------------------------------------
	//B words
	//------------------------------------------------------------------	
	if (g_strcmp0(word,"billie")==0)
	{
		word ="billy";
	}
	if (g_strcmp0(word,"bro")==0)
	{
		word ="brother";
	}
	if (g_strcmp0(word,"bros")==0)
	{
		word ="brothers";
	}
	//------------------------------------------------------------------
	//C words
	//------------------------------------------------------------------		
	if ((g_strcmp0(word,"katherine")==0) || (g_strcmp0(word,"kathryn")==0) || (g_strcmp0(word,"katharine")==0))
	{
		word ="catherine";
	}
	if ((g_strcmp0(word,"katherines")==0) || (g_strcmp0(word,"kathryns")==0) || (g_strcmp0(word,"katharines")==0))
	{
		word ="catherine";
	}
	
	//------------------------------------------------------------------
	//D words
	//------------------------------------------------------------------
	if (g_strcmp0(word,"dannie")==0)
	{
		word ="danny";
	}
	
	if (g_strcmp0(word,"dr.")==0)
	{
		word ="doctor";
	}
	
	//------------------------------------------------------------------
	//F words
	//------------------------------------------------------------------
		
	if (g_strcmp0(word,"freddy")==0)
	{
		word ="freddie";
	}
	
	//------------------------------------------------------------------
	//G words
	//------------------------------------------------------------------
	
	if ((g_strcmp0(word,"gaile")==0) || (g_strcmp0(word,"gail")==0) || (g_strcmp0(word,"gayle")==0))
	{
		word ="gale";
	}
	
	if (((g_strcmp0(word,"gailes")==0) || (g_strcmp0(word,"gails")==0) || (g_strcmp0(word,"gayles")==0)))
	{
		word ="gales";
	}
		
	
	
	//------------------------------------------------------------------
	//H words
	//------------------------------------------------------------------
	
	if (g_strcmp0(word,"hanna")==0)
	{
		word ="hannah";
	}
	if (g_strcmp0(word,"hannas")==0)
	{
		word ="hannahs";
	}
	
	//------------------------------------------------------------------
	//I words
	//------------------------------------------------------------------
	
	if (g_strcmp0(word,"ivie")==0)
	{
		word ="ivy";
	}
	
	//------------------------------------------------------------------
	//J words
	//------------------------------------------------------------------
	
	if (g_strcmp0(word,"jacky")==0)
	{
		word ="jackie";
	}
	
	if (g_strcmp0(word,"jeff")==0)
	{
		word ="geoff";
	}
	
	if (g_strcmp0(word,"jeffs")==0)
	{
		word ="geoffs";
	}
		
	if ((g_strcmp0(word,"jefferys")==0))
	{
		word ="geoffreys";
	}
		
	//------------------------------------------------------------------
	//K words
	//------------------------------------------------------------------
	
	if (g_strcmp0(word,"karren")==0)
	{
		word ="karen";
	}
	
	if (g_strcmp0(word,"karrens")==0)
	{
		word ="karens";
	}
	
	//------------------------------------------------------------------
	//L words
	//------------------------------------------------------------------
	if ((g_strcmp0(word,"lilly")==0) || (g_strcmp0(word,"lillie")==0))
	{
		word ="lily";
	}
	//------------------------------------------------------------------
	//M words
	//------------------------------------------------------------------
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
		word ="muhammads";
	}
	
	//------------------------------------------------------------------
	//P words
	//------------------------------------------------------------------		
	if (g_strcmp0(word,"prof")==0)
	{
		word ="professor";
	}
	//------------------------------------------------------------------
	//S words
	//------------------------------------------------------------------
	
	if (g_strcmp0(word,"sis")==0)
	{
		word ="sister";
	}
	if (g_strcmp0(word,"stephen")==0)
	{
		word ="steven";
	}
	
	//------------------------------------------------------------------
	//T words
	//------------------------------------------------------------------
	if (g_strcmp0(word,"tel")==0)
	{
		word ="telephone";
	}
	
	
	if (g_strcmp0(word,"tomas")==0)
	{
		word ="thomas";
	}
	
	
	//------------------------------------------------------------------
	//Z words
	//------------------------------------------------------------------
		
		
	if ((g_strcmp0(word,"zak")==0) || (g_strcmp0(word,"zakk")==0) || (g_strcmp0(word,"zac")==0))
	{
		word ="zach";
	}
	
	
	
	//----------------------------------------------------
	
	out_str= g_strconcat(out_str,word, " ", NULL);		
	j++;
	}
	return out_str;
	
}

