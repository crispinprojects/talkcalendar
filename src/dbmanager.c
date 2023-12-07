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



#include "dbmanager.h"

#define CONFIG_DIRNAME "dbtest-gtk"

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i < argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

void remove_apostrophes(char* str)
{    
    int from, to;       
    for (from = 0, to = 0; str[from] != '\0'; ++from) {
        if (!(str[from] == '\'')) {
            str[to] = str[from];
            ++to;
        }
    }
    str[to] = '\0';
}


//-------------------------------------------------------------------
// Create Events table
//-------------------------------------------------------------------
const char *get_db_path(){
	
	//const char *path = "/home/alan/calendar.db"; //put database in home directory for testing WORKS
	const char *path = "calendar.db";
	return path;
}


void db_create_events_table() {
  
sqlite3 *db;
char *zErrMsg = NULL;
int rc=0;
char *sql;
	
	const char *path=get_db_path();
	
	rc = sqlite3_open(path, &db);

   if(rc) {
      printf("Can't open database: %s\n", sqlite3_errmsg(db));
      return;
   } else {
      printf("Opened database successfully\n");
   }
     
  sql = "CREATE TABLE EVENTS("\
        "ID 				INTEGER PRIMARY KEY AUTOINCREMENT,"\
        "SUMMARY      		TEXT,"\
        "LOCATION     		TEXT,"\
        "DESCRIPTION        TEXT,"\
        "STARTYEAR          INT,"\
        "STARTMONTH         INT,"\
        "STARTDAY           INT,"\
        "STARTHOUR      	INT,"\
        "STARTMIN       	INT,"\
        "ENDYEAR            INT,"\
        "ENDMONTH           INT,"\
        "ENDDAY            	INT,"\
        "ENDHOUR      		INT,"\
        "ENDMIN       		INT,"\
        "ISYEARLY			INT,"\
	    "ISALLDAY			INT,"\
        "ISPRIORITY			INT,"\
        "HASNOTIFICATION	INT,"\
        "HASREMINDER		INT,"\
        "REMINDERMINS		INT);" ;
        
      
   printf("Execute sql to create tables\n"); 
   
/* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
   if(rc != SQLITE_OK){
      printf("Sql1 message: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      printf(" Events table created successfully\n");
   }
      
   sqlite3_close(db); 
  
}

//---------------------------------------------------------------------
// Insert using CalendarEvent pointer
//---------------------------------------------------------------------
 
int db_insert_event(CalendarEvent *evt) {
	
	gint evt_id=0;
	gchar *summary_str="";
	gchar *location_str="";
	gchar *desc_str="";

	gint start_year=0;
	gint start_month=0;
	gint start_day=0;
	gint start_hour=0;
	gint start_min=0;
	
	gint end_year=0;
	gint end_month=0;
	gint end_day=0;
	gint end_hour=0;
	gint end_min=0;
	gint is_yearly=0;
	gint is_allday=0;
	gint is_priority =0;
	gint has_notification=0;
	gint has_reminder=0;
	gint reminder_min=0;
	
	g_object_get (evt, "eventid", &evt_id, NULL);
	g_object_get (evt, "summary", &summary_str, NULL);
	g_object_get (evt, "location", &location_str, NULL);
	g_object_get (evt, "description", &desc_str, NULL);
		
	g_object_get (evt, "startyear", &start_year, NULL);
	g_object_get (evt, "startmonth", &start_month, NULL);
	g_object_get (evt, "startday", &start_day, NULL);
	g_object_get (evt, "starthour", &start_hour, NULL);
	g_object_get (evt, "startmin", &start_min, NULL);
	
	g_object_get (evt, "endyear", &end_year, NULL);
	g_object_get (evt, "endmonth", &end_month, NULL);
	g_object_get (evt, "endday", &end_day, NULL);
	g_object_get (evt, "endhour", &end_hour, NULL);
	g_object_get (evt, "endmin", &end_min, NULL);
	
	g_object_get(evt, "isyearly", &is_yearly, NULL);
	g_object_get(evt, "isallday", &is_allday, NULL);
	g_object_get(evt, "ispriority", &is_priority, NULL);
	g_object_get (evt, "hasnotification", &has_notification, NULL);
	g_object_get (evt, "hasreminder", &has_reminder, NULL);
	g_object_get (evt, "remindermin", &reminder_min, NULL);

//remove_apostrophes(title); //clean to prevent sql crash
//remove_apostrophes(description);

//printf("dbInsert: summary = %s\n",summary_str);
//printf("dbInsert: location = %s\n",location_str);

//printf("dbInsert: start_year = %d\n",start_year);
//printf("dbInsert: start_month = %d\n", start_month);
//printf("dbInsert: start_day = %d\n",start_day);
//printf("dbInsert: start_hour = %d\n", start_hour);
//printf("dbInsert: start_min = %d\n",start_min);
 
sqlite3 *db;
int rc=0;
char sql_query[2048] = ""; //string on the stack (not heap)
 //Use statement to prevent injection errors  
sqlite3_stmt *stmt;

/* Open database */

	const char *path=get_db_path();
	rc = sqlite3_open(path, &db);
   
   if(rc) {
      printf("Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      printf("Opened database successfully\n");
   }

sprintf(sql_query, "INSERT INTO EVENTS (SUMMARY,LOCATION,DESCRIPTION,\
STARTYEAR,STARTMONTH,STARTDAY,STARTHOUR,STARTMIN,\
ENDYEAR,ENDMONTH,ENDDAY,ENDHOUR,ENDMIN,\
ISYEARLY,ISALLDAY,ISPRIORITY,HASNOTIFICATION,HASREMINDER,REMINDERMINS)\
VALUES  ('%s','%s','%s', %d,%d,%d,%d,%d, %d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d);",
        summary_str,location_str,desc_str,start_year,start_month,start_day,start_hour,start_min,\
        end_year, end_month, end_day, end_hour,end_min,\
        is_yearly,is_allday, is_priority,has_notification, has_reminder,reminder_min);

printf("sql = %s\n",sql_query);
printf("Length of sql_query =%ld\n",strlen(sql_query));

// Prepare the query
printf("Preparing the insert query..\n");
if (sqlite3_prepare_v2(db, sql_query, -1, &stmt, NULL) != SQLITE_OK){
     printf("SQL get events prepare error: %s\n", sqlite3_errmsg(db));
}

rc = sqlite3_step(stmt); // execute (step) insert
sqlite3_finalize(stmt);  // finialize insert query
int insert_id = sqlite3_last_insert_rowid(db);
printf("insert id = %d\n",insert_id);
sqlite3_close(db); //close db
return insert_id;
}  



//--------------------------------------------------------------------
// Update event
//---------------------------------------------------------------------

void db_update_event(CalendarEvent *evt){

//int idx=event->id;

    gint evt_id=0;
	gchar *summary_str="";
	gchar *location_str="";
	gchar *desc_str="";

	gint start_year=0;
	gint start_month=0;
	gint start_day=0;
	gint start_hour=0;
	gint start_min=0;
	
	gint end_year=0;
	gint end_month=0;
	gint end_day=0;
	gint end_hour=0;
	gint end_min=0;
	gint is_yearly=0;
	gint is_allday=0;
	gint is_priority =0;
	gint has_notification=0;
	gint has_reminder=0;
	gint reminder_min=0;
	
	g_object_get (evt, "eventid", &evt_id, NULL);
	
	int idx=evt_id;
	//g_print("updating event with id = %d\n",idx);
	
	g_object_get (evt, "summary", &summary_str, NULL);
	g_object_get (evt, "location", &location_str, NULL);
	g_object_get (evt, "description", &desc_str, NULL);
		
	g_object_get (evt, "startyear", &start_year, NULL);
	g_object_get (evt, "startmonth", &start_month, NULL);
	g_object_get (evt, "startday", &start_day, NULL);
	g_object_get (evt, "starthour", &start_hour, NULL);
	g_object_get (evt, "startmin", &start_min, NULL);
	
	g_object_get (evt, "endyear", &end_year, NULL);
	g_object_get (evt, "endmonth", &end_month, NULL);
	g_object_get (evt, "endday", &end_day, NULL);
	g_object_get (evt, "endhour", &end_hour, NULL);
	g_object_get (evt, "endmin", &end_min, NULL);
	
	g_object_get(evt, "isyearly", &is_yearly, NULL);
	g_object_get(evt, "isallday", &is_allday, NULL);
	g_object_get(evt, "ispriority", &is_priority, NULL);
	g_object_get (evt, "hasnotification", &has_notification, NULL);
	g_object_get (evt, "hasreminder", &has_reminder, NULL);
	g_object_get (evt, "remindermin", &reminder_min, NULL);

sqlite3 *db;
int rc=0;
sqlite3_stmt *stmt;
char query[2048] = "";

	const char *path=get_db_path();
	rc = sqlite3_open(path, &db);
   
   if(rc) {
      printf("Can't open database: %s\n", sqlite3_errmsg(db));
      return;
   } else {
      printf("Opened database successfully\n");
   }


sprintf(query, "UPDATE EVENTS SET SUMMARY ='%s',LOCATION ='%s', DESCRIPTION='%s',\
STARTYEAR=%i,STARTMONTH=%i,STARTDAY=%i,STARTHOUR=%i,STARTMIN=%i,\
         ENDYEAR=%i,ENDMONTH=%i,ENDDAY=%i,ENDHOUR=%i,ENDMIN=%i,\
         ISYEARLY=%i,ISALLDAY=%i,ISPRIORITY=%i,HASNOTIFICATION=%i,HASREMINDER=%i,REMINDERMINS=%i\
         WHERE ID ='%i'",summary_str,location_str,desc_str,start_year,start_month,start_day,start_hour,start_min,\
         end_year, end_month, end_day, end_hour,end_min,\
         is_yearly,is_allday, is_priority,has_notification,has_reminder,reminder_min,idx);
  
//sprintf(query, "UPDATE EVENTS SET TITLE ='%s',PRIORITY =%i, DESCRIPTION='%s',\
        //STARTHOUR=%i, STARTMIN=%i, ENDHOUR=%i, ENDMIN=%i, ISYEARLY=%i, ISALLDAY=%i\
        //WHERE ID ='%i'", title,priority,description,start_hour,start_min,end_hour,end_min,is_yearly,is_allday,idx);
         

// Prepare the query
rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
if (rc != SQLITE_OK) {
  // error handling -> statement not prepared
  printf("SQL prepare error: %s\n", sqlite3_errmsg(db));
}

 rc = sqlite3_step(stmt); // execute (step) insert
 sqlite3_finalize(stmt);// finialize
 
sqlite3_close(db);  	
}

//-------------------------------------------------------------------
// Get CalendarEvent
//-------------------------------------------------------------------

void db_get_event(int index, CalendarEvent *evt){


	sqlite3 *db;
	int rc=0;
	sqlite3_stmt *stmt;
	char sql[2048] = "";
	const char *path=get_db_path();
	rc = sqlite3_open(path, &db);	
	if(rc) {
	printf("Can't open database: %s\n", sqlite3_errmsg(db));
	return;
	} else {
	printf("Opened database successfully\n");
	}


sprintf(sql, "SELECT * FROM EVENTS WHERE ID = %i", index);

if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
     printf("SQL get events prepare error: %s\n", sqlite3_errmsg(db));
}

rc = sqlite3_step(stmt); // execute statement (query.first?)


gint evt_id = sqlite3_column_int(stmt, 0);  

const gchar *summary_str =sqlite3_column_text(stmt, 1);
const gchar *location_str =sqlite3_column_text(stmt, 2);
const gchar *desc_str =sqlite3_column_text(stmt, 3);

gint start_year=sqlite3_column_int(stmt, 4);
gint start_month=sqlite3_column_int(stmt, 5);
gint start_day=sqlite3_column_int(stmt, 6);
gint start_hour=sqlite3_column_int(stmt, 7);
gint start_min=sqlite3_column_int(stmt, 8);

gint end_year=sqlite3_column_int(stmt, 9);
gint end_month=sqlite3_column_int(stmt, 10);;
gint end_day=sqlite3_column_int(stmt, 11);
gint end_hour=sqlite3_column_int(stmt, 12);
gint end_min=sqlite3_column_int(stmt, 13);

gint is_yearly=sqlite3_column_int(stmt, 14);
gint is_allday=sqlite3_column_int(stmt, 15);
gint is_priority =sqlite3_column_int(stmt, 16);
gint has_notification=sqlite3_column_int(stmt, 17);
gint has_reminder=sqlite3_column_int(stmt, 18);
gint reminder_mins=sqlite3_column_int(stmt, 19);

g_object_set(evt, "eventid",evt_id, NULL);
g_object_set(evt, "summary", g_strdup(summary_str), NULL);
g_object_set(evt, "location", g_strdup(location_str), NULL);
g_object_set(evt, "description", g_strdup(desc_str), NULL);
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
g_object_set(evt, "hasnotification", has_notification, NULL);
g_object_set(evt, "hasreminder", 0, NULL);
g_object_set(evt, "remindermin", 0, NULL);
	
sqlite3_finalize(stmt); 
sqlite3_close(db);  
}


//-------------------------------------------------------------------
// Get number of rows all events
//-------------------------------------------------------------------
int db_get_number_of_rows_all() {
	printf("Get number of  db rows all\n");
	sqlite3 *db;
	int rc=0;
	int row_count=0;
	sqlite3_stmt *stmt;
	char sql[200] = "";
	
	const char *path=get_db_path();
	rc = sqlite3_open(path, &db);
	
	if(rc) {
	printf("Can't open database: %s\n", sqlite3_errmsg(db));
	return 0;
	} else {
	printf("Opened database successfully\n");
	}
	
	sprintf(sql, "SELECT Count(*) FROM EVENTS"); 
	printf("sql = %s\n",sql);
	
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
	// error handling -> statement not prepared
	printf("SQL prepare error: %s\n", sqlite3_errmsg(db));
	}
	rc = sqlite3_step(stmt);
	if (rc != SQLITE_ROW) {
	// error handling -> no rows returned, or an error occurred
	// printf("SQL return no rows");
	return 0;
	}
	row_count = sqlite3_column_int(stmt, 0);
	
	sqlite3_finalize(stmt);  
	sqlite3_close(db); 
	return row_count;
}

//-----------------------------------------------------------------
// Get number of rows year month
//-----------------------------------------------------------------

int db_get_number_of_rows_month_year(int month, int year) {

sqlite3 *db;
int rc=0;
int row_count=0;
sqlite3_stmt *stmt;
char sql[200] = "";

/* Open database */
const char *path=get_db_path();
rc = sqlite3_open(path, &db);
if(rc) {
printf("Can't open database: %s\n", sqlite3_errmsg(db));
return 0;
} else {
printf("Opened database successfully\n");
}

sprintf(sql, "SELECT Count(*) FROM EVENTS WHERE STARTYEAR = '%i' AND STARTMONTH = '%i'", year, month); 
printf("sql = %s\n",sql);

rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
if (rc != SQLITE_OK) {
// error handling -> statement not prepared
printf("SQL prepare error: %s\n", sqlite3_errmsg(db));
}
rc = sqlite3_step(stmt);
if (rc != SQLITE_ROW) {
// error handling -> no rows returned, or an error occurred
return 0;
}
row_count = sqlite3_column_int(stmt, 0);
sqlite3_finalize(stmt);  
sqlite3_close(db); 
return row_count; 
}

//----------------------------------------------------------------
// Get number of rows YEAR MONTH DAY
//-----------------------------------------------------------------

int db_get_number_of_rows_year_month_day(int year, int month, int day) {
	
	sqlite3 *db;
	int rc=0;
	int row_count=0;
	sqlite3_stmt *stmt;
	char sql[200] = "";
	
	/* Open database */
	const char *path=get_db_path();
	rc = sqlite3_open(path, &db);
	
	if(rc) {
	printf("Can't open database: %s\n", sqlite3_errmsg(db));
	return(0);
	} else {
	printf("Opened database successfully\n");
	}
	
	sprintf(sql, "SELECT Count(*) FROM EVENTS WHERE STARTYEAR = '%i' AND STARTMONTH = '%i' AND STARTDAY = '%i'", year, month, day); 
	
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
	// error handling -> statement not prepared
	printf("SQL prepare error: %s\n", sqlite3_errmsg(db));
	return 0;
	}
rc = sqlite3_step(stmt);
if (rc != SQLITE_ROW) {
  // error handling -> no rows returned, or an error occurred
  return 0;
}
row_count = sqlite3_column_int(stmt, 0);
sqlite3_finalize(stmt);  
sqlite3_close(db); 
return row_count; 	
}

//-----------------------------------------------------------------
// Get number of isyearly events in month
//-----------------------------------------------------------------

int db_get_number_of_isyearly_events_month(int month) {
	
	sqlite3 *db;
	int rc=0;
	sqlite3_stmt *stmt;
	char sql[2048] = "";
	/* Open database */
	const char *path=get_db_path();
	rc = sqlite3_open(path, &db); 
	if(rc) {
	printf("Can't open database: %s\n", sqlite3_errmsg(db));
	return  0;
	} else {
	printf("Opened database successfully\n");
	}
	
	sprintf(sql, "SELECT Count(*) FROM EVENTS WHERE STARTMONTH = '%i' AND ISYEARLY = '%i'", month,1); 
	printf("sql = %s\n",sql);
	
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {  
	printf("SQL prepare error: %s\n", sqlite3_errmsg(db));
	}
	rc = sqlite3_step(stmt);
	if (rc != SQLITE_ROW) {
	// error handling -> no rows returned, or an error occurred
	return 0;
	}
	int row_count = sqlite3_column_int(stmt, 0);
	sqlite3_finalize(stmt);  
	sqlite3_close(db); 
	return row_count; 	
}




//-------------------------------------------------------------------
// Get all events 
//-------------------------------------------------------------------
void db_get_all_events(GArray *evt_arry) {
	
	sqlite3 *db;
	int rc=0;
	sqlite3_stmt *stmt;
	char sql[2048] = "";
	/* Open database */
	const char *path=get_db_path();
	rc = sqlite3_open(path, &db); 
	if(rc) {
	printf("Can't open database: %s\n", sqlite3_errmsg(db));
	return;
	} else {
	printf("Opened database successfully\n");
	}
	
	sprintf(sql, "SELECT * FROM EVENTS");

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
	printf("SQL get events prepare error: %s\n", sqlite3_errmsg(db));
	}
			
		
	while (sqlite3_step(stmt) == SQLITE_ROW) {
	
	CalendarEvent *tmp_evt = g_object_new(CALENDAR_TYPE_EVENT, 0);
	
	g_object_set(tmp_evt, "eventid", sqlite3_column_int(stmt, 0), NULL);
	g_object_set(tmp_evt, "summary", sqlite3_column_text(stmt, 1), NULL);
	g_object_set(tmp_evt, "location", sqlite3_column_text(stmt, 2), NULL);
	g_object_set(tmp_evt, "description", sqlite3_column_text(stmt, 3), NULL);
	g_object_set(tmp_evt, "startyear", sqlite3_column_int(stmt, 4), NULL);
	g_object_set(tmp_evt, "startmonth", sqlite3_column_int(stmt, 5), NULL);
	g_object_set(tmp_evt, "startday", sqlite3_column_int(stmt, 6), NULL);
	g_object_set(tmp_evt, "starthour", sqlite3_column_int(stmt, 7), NULL);
	g_object_set(tmp_evt, "startmin", sqlite3_column_int(stmt, 8), NULL);
	
	g_object_set(tmp_evt, "endyear", sqlite3_column_int(stmt, 9), NULL);
	g_object_set(tmp_evt, "endmonth", sqlite3_column_int(stmt,10), NULL);
	g_object_set(tmp_evt, "endday", sqlite3_column_int(stmt, 11), NULL);
	g_object_set(tmp_evt, "endhour", sqlite3_column_int(stmt, 12), NULL);
	g_object_set(tmp_evt, "endmin", sqlite3_column_int(stmt, 13), NULL);
	
	g_object_set(tmp_evt, "isyearly", sqlite3_column_int(stmt, 14), NULL);
	g_object_set(tmp_evt, "isallday", sqlite3_column_int(stmt, 15), NULL);
	g_object_set(tmp_evt, "ispriority", sqlite3_column_int(stmt, 16), NULL);
	
	g_object_set(tmp_evt, "hasnotification", sqlite3_column_int(stmt, 17), NULL);
	g_object_set(tmp_evt, "hasreminder", sqlite3_column_int(stmt, 18), NULL);
	g_object_set(tmp_evt, "remindermin", sqlite3_column_int(stmt, 19), NULL);	
	g_array_append_val(evt_arry, tmp_evt);	
	} //while
	 
	sqlite3_finalize(stmt);
	sqlite3_close(db); 
}	


//-------------------------------------------------------------------
// Get events for month year (with isYearly)
//-------------------------------------------------------------------
void db_get_all_events_year_month(GArray *evt_arry, int year, int month)
{
	sqlite3 *db;
	int rc=0;
	sqlite3_stmt *stmt;
	char sql[2048] = "";
	/* Open database */
	const char *path=get_db_path();
	rc = sqlite3_open(path, &db); 
	if(rc) {
	printf("Can't open database: %s\n", sqlite3_errmsg(db));
	return;
	} else {
	printf("Opened database successfully\n");
	}
	
	sprintf(sql, "SELECT * FROM EVENTS WHERE (STARTYEAR = '%i' OR ISYEARLY = '%i') AND STARTMONTH = '%i'", year, 1, month);

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
     printf("SQL get events prepare error: %s\n", sqlite3_errmsg(db));
	}

	while (sqlite3_step(stmt) == SQLITE_ROW) {
	
	CalendarEvent *tmp_evt = g_object_new(CALENDAR_TYPE_EVENT, 0);
	
	g_object_set(tmp_evt, "eventid", sqlite3_column_int(stmt, 0), NULL);
	g_object_set(tmp_evt, "summary", sqlite3_column_text(stmt, 1), NULL);
	g_object_set(tmp_evt, "location", sqlite3_column_text(stmt, 2), NULL);
	g_object_set(tmp_evt, "description", sqlite3_column_text(stmt, 3), NULL);
	g_object_set(tmp_evt, "startyear", sqlite3_column_int(stmt, 4), NULL);
	g_object_set(tmp_evt, "startmonth", sqlite3_column_int(stmt, 5), NULL);
	g_object_set(tmp_evt, "startday", sqlite3_column_int(stmt, 6), NULL);
	g_object_set(tmp_evt, "starthour", sqlite3_column_int(stmt, 7), NULL);
	g_object_set(tmp_evt, "startmin", sqlite3_column_int(stmt, 8), NULL);
	g_object_set(tmp_evt, "endyear", sqlite3_column_int(stmt, 9), NULL);
	g_object_set(tmp_evt, "endmonth", sqlite3_column_int(stmt,10), NULL);
	g_object_set(tmp_evt, "endday", sqlite3_column_int(stmt, 11), NULL);
	g_object_set(tmp_evt, "endhour", sqlite3_column_int(stmt, 12), NULL);
	g_object_set(tmp_evt, "endmin", sqlite3_column_int(stmt, 13), NULL);
	g_object_set(tmp_evt, "isyearly", sqlite3_column_int(stmt, 14), NULL);
	g_object_set(tmp_evt, "isallday", sqlite3_column_int(stmt, 15), NULL);
	g_object_set(tmp_evt, "ispriority", sqlite3_column_int(stmt, 16), NULL);	
	g_object_set(tmp_evt, "hasnotification", sqlite3_column_int(stmt, 17), NULL);
	g_object_set(tmp_evt, "hasreminder", sqlite3_column_int(stmt, 18), NULL);
	g_object_set(tmp_evt, "remindermin", sqlite3_column_int(stmt, 19), NULL);	
	g_array_append_val(evt_arry, tmp_evt);	
	
	} //while
	sqlite3_finalize(stmt);
	sqlite3_close(db); 
	
}

//-------------------------------------------------------------------
// Get events for year month day (day events with isYearly)
//-------------------------------------------------------------------
void db_get_all_events_year_month_day(GArray *evt_arry, int year, int month, int day)
{
	sqlite3 *db;
	int rc=0;
	sqlite3_stmt *stmt;
	char sql[2048] = "";
	/* Open database */
	const char *path=get_db_path();
	rc = sqlite3_open(path, &db); 
	if(rc) {
	printf("Can't open database: %s\n", sqlite3_errmsg(db));
	return;
	} else {
	printf("Opened database successfully\n");
	}
		
	sprintf(sql, "SELECT * FROM EVENTS WHERE (STARTYEAR = '%i' OR ISYEARLY = '%i') AND STARTMONTH = '%i' AND STARTDAY = '%i' ORDER BY STARTHOUR, STARTMIN asc", year, 1, month, day);	
	
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
     printf("SQL get events prepare error: %s\n", sqlite3_errmsg(db));
	}

	while (sqlite3_step(stmt) == SQLITE_ROW) {
	
	CalendarEvent *tmp_evt = g_object_new(CALENDAR_TYPE_EVENT, 0);
	
	g_object_set(tmp_evt, "eventid", sqlite3_column_int(stmt, 0), NULL);
	g_object_set(tmp_evt, "summary", sqlite3_column_text(stmt, 1), NULL);
	g_object_set(tmp_evt, "location", sqlite3_column_text(stmt, 2), NULL);
	g_object_set(tmp_evt, "description", sqlite3_column_text(stmt, 3), NULL);
	g_object_set(tmp_evt, "startyear", sqlite3_column_int(stmt, 4), NULL);
	g_object_set(tmp_evt, "startmonth", sqlite3_column_int(stmt, 5), NULL);
	g_object_set(tmp_evt, "startday", sqlite3_column_int(stmt, 6), NULL);
	g_object_set(tmp_evt, "starthour", sqlite3_column_int(stmt, 7), NULL);
	g_object_set(tmp_evt, "startmin", sqlite3_column_int(stmt, 8), NULL);
	g_object_set(tmp_evt, "endyear", sqlite3_column_int(stmt, 9), NULL);
	g_object_set(tmp_evt, "endmonth", sqlite3_column_int(stmt,10), NULL);
	g_object_set(tmp_evt, "endday", sqlite3_column_int(stmt, 11), NULL);
	g_object_set(tmp_evt, "endhour", sqlite3_column_int(stmt, 12), NULL);
	g_object_set(tmp_evt, "endmin", sqlite3_column_int(stmt, 13), NULL);
	g_object_set(tmp_evt, "isyearly", sqlite3_column_int(stmt, 14), NULL);
	g_object_set(tmp_evt, "isallday", sqlite3_column_int(stmt, 15), NULL);
	g_object_set(tmp_evt, "ispriority", sqlite3_column_int(stmt, 16), NULL);	
	g_object_set(tmp_evt, "hasnotification", sqlite3_column_int(stmt, 17), NULL);
	g_object_set(tmp_evt, "hasreminder", sqlite3_column_int(stmt, 18), NULL);
	g_object_set(tmp_evt, "remindermin", sqlite3_column_int(stmt, 19), NULL);		
	g_array_append_val(evt_arry, tmp_evt);	
	} 
	sqlite3_finalize(stmt);
	sqlite3_close(db); 
}

//-----------------------------------------------------------------
// Get DAY isYearly events
//-----------------------------------------------------------------

void db_get_isyearly_events_day(GArray *evt_arry, int month, int day)
{
	sqlite3 *db;
	int rc=0;
	sqlite3_stmt *stmt;
	char sql[2048] = "";
	/* Open database */
	const char *path=get_db_path();
	rc = sqlite3_open(path, &db); 
	if(rc) {
	printf("Can't open database: %s\n", sqlite3_errmsg(db));
	return;
	} else {
	printf("Opened database successfully\n");
	}
	
	sprintf(sql, "SELECT * FROM EVENTS WHERE STARTMONTH = '%i' AND STARTDAY = '%i' AND ISYEARLY = '%i'",month,day,1);
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
	printf("SQL get events prepare error: %s\n", sqlite3_errmsg(db));
	return;
	}	
	
	while (sqlite3_step(stmt) == SQLITE_ROW) {
	
	CalendarEvent *tmp_evt = g_object_new(CALENDAR_TYPE_EVENT, 0);
	
	g_object_set(tmp_evt, "eventid", sqlite3_column_int(stmt, 0), NULL);
	g_object_set(tmp_evt, "summary", sqlite3_column_text(stmt, 1), NULL);
	g_object_set(tmp_evt, "location", sqlite3_column_text(stmt, 2), NULL);
	g_object_set(tmp_evt, "description", sqlite3_column_text(stmt, 3), NULL);
	g_object_set(tmp_evt, "startyear", sqlite3_column_int(stmt, 4), NULL);
	g_object_set(tmp_evt, "startmonth", sqlite3_column_int(stmt, 5), NULL);
	g_object_set(tmp_evt, "startday", sqlite3_column_int(stmt, 6), NULL);
	g_object_set(tmp_evt, "starthour", sqlite3_column_int(stmt, 7), NULL);
	g_object_set(tmp_evt, "startmin", sqlite3_column_int(stmt, 8), NULL);
	g_object_set(tmp_evt, "endyear", sqlite3_column_int(stmt, 9), NULL);
	g_object_set(tmp_evt, "endmonth", sqlite3_column_int(stmt,10), NULL);
	g_object_set(tmp_evt, "endday", sqlite3_column_int(stmt, 11), NULL);
	g_object_set(tmp_evt, "endhour", sqlite3_column_int(stmt, 12), NULL);
	g_object_set(tmp_evt, "endmin", sqlite3_column_int(stmt, 13), NULL);
	g_object_set(tmp_evt, "isyearly", sqlite3_column_int(stmt, 14), NULL);
	g_object_set(tmp_evt, "isallday", sqlite3_column_int(stmt, 15), NULL);
	g_object_set(tmp_evt, "ispriority", sqlite3_column_int(stmt, 16), NULL);	
	g_object_set(tmp_evt, "hasnotification", sqlite3_column_int(stmt, 17), NULL);
	g_object_set(tmp_evt, "hasreminder", sqlite3_column_int(stmt, 18), NULL);
	g_object_set(tmp_evt, "remindermin", sqlite3_column_int(stmt, 19), NULL);
		
	g_array_append_val(evt_arry, tmp_evt);	
	} //while
	
	sqlite3_finalize(stmt);
	sqlite3_close(db); 	
	
}


//-------------------------------------------------------------------
// Get MONTH isYearly events
//-------------------------------------------------------------------


void db_get_isyearly_events_month(GArray *evt_arry, int month) 
{
	sqlite3 *db;
	int rc=0;
	sqlite3_stmt *stmt;
	char sql[2048] = "";
	/* Open database */
	const char *path=get_db_path();
	rc = sqlite3_open(path, &db); 
	if(rc) {
	printf("Can't open database: %s\n", sqlite3_errmsg(db));
	return;
	} else {
	printf("Opened database successfully\n");
	}
	
	sprintf(sql, "SELECT * FROM EVENTS WHERE STARTMONTH = '%i' AND ISYEARLY = '%i'", month, 1);
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
	printf("SQL get events prepare error: %s\n", sqlite3_errmsg(db));
	return;
	}	
	
	while (sqlite3_step(stmt) == SQLITE_ROW) {
	
	CalendarEvent *tmp_evt = g_object_new(CALENDAR_TYPE_EVENT, 0);
	
	g_object_set(tmp_evt, "eventid", sqlite3_column_int(stmt, 0), NULL);
	g_object_set(tmp_evt, "summary", sqlite3_column_text(stmt, 1), NULL);
	g_object_set(tmp_evt, "location", sqlite3_column_text(stmt, 2), NULL);
	g_object_set(tmp_evt, "description", sqlite3_column_text(stmt, 3), NULL);
	g_object_set(tmp_evt, "startyear", sqlite3_column_int(stmt, 4), NULL);
	g_object_set(tmp_evt, "startmonth", sqlite3_column_int(stmt, 5), NULL);
	g_object_set(tmp_evt, "startday", sqlite3_column_int(stmt, 6), NULL);
	g_object_set(tmp_evt, "starthour", sqlite3_column_int(stmt, 7), NULL);
	g_object_set(tmp_evt, "startmin", sqlite3_column_int(stmt, 8), NULL);
	g_object_set(tmp_evt, "endyear", sqlite3_column_int(stmt, 9), NULL);
	g_object_set(tmp_evt, "endmonth", sqlite3_column_int(stmt,10), NULL);
	g_object_set(tmp_evt, "endday", sqlite3_column_int(stmt, 11), NULL);
	g_object_set(tmp_evt, "endhour", sqlite3_column_int(stmt, 12), NULL);
	g_object_set(tmp_evt, "endmin", sqlite3_column_int(stmt, 13), NULL);
	g_object_set(tmp_evt, "isyearly", sqlite3_column_int(stmt, 14), NULL);
	g_object_set(tmp_evt, "isallday", sqlite3_column_int(stmt, 15), NULL);
	
	g_object_set(tmp_evt, "ispriority", sqlite3_column_int(stmt, 16), NULL);	
	g_object_set(tmp_evt, "hasnotification", sqlite3_column_int(stmt, 17), NULL);
	g_object_set(tmp_evt, "hasreminder", sqlite3_column_int(stmt, 18), NULL);
	g_object_set(tmp_evt, "remindermin", sqlite3_column_int(stmt, 19), NULL);
	
	g_array_append_val(evt_arry, tmp_evt);	
	} //while
	sqlite3_finalize(stmt);
	sqlite3_close(db); 
}	

//-------------------------------------------------------------------
// Get upcoming events 
//-------------------------------------------------------------------
void db_get_upcoming_events(GArray *evt_arry, int year, int month, int from ,int to)
{
	sqlite3 *db;
	int rc=0;
	sqlite3_stmt *stmt;
	char sql[2048] = "";
	/* Open database */
	const char *path=get_db_path();
	rc = sqlite3_open(path, &db); 
	if(rc) {
	printf("Can't open database: %s\n", sqlite3_errmsg(db));
	return;
	} else {
	printf("Opened database successfully\n");
	}
	
	
	sprintf(sql, "SELECT * FROM EVENTS WHERE STARTYEAR ='%i' AND STARTMONTH = '%i' AND\
	STARTDAY BETWEEN '%i' AND '%i' ORDER BY STARTDAY asc ", year, month, from,to);	
	
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
     printf("SQL get events prepare error: %s\n", sqlite3_errmsg(db));
	}

	while (sqlite3_step(stmt) == SQLITE_ROW) {
	
	CalendarEvent *tmp_evt = g_object_new(CALENDAR_TYPE_EVENT, 0);
	
	g_object_set(tmp_evt, "eventid", sqlite3_column_int(stmt, 0), NULL);
	g_object_set(tmp_evt, "summary", sqlite3_column_text(stmt, 1), NULL);
	g_object_set(tmp_evt, "location", sqlite3_column_text(stmt, 2), NULL);
	g_object_set(tmp_evt, "description", sqlite3_column_text(stmt, 3), NULL);
	g_object_set(tmp_evt, "startyear", sqlite3_column_int(stmt, 4), NULL);
	g_object_set(tmp_evt, "startmonth", sqlite3_column_int(stmt, 5), NULL);
	g_object_set(tmp_evt, "startday", sqlite3_column_int(stmt, 6), NULL);
	g_object_set(tmp_evt, "starthour", sqlite3_column_int(stmt, 7), NULL);
	g_object_set(tmp_evt, "startmin", sqlite3_column_int(stmt, 8), NULL);
	g_object_set(tmp_evt, "endyear", sqlite3_column_int(stmt, 9), NULL);
	g_object_set(tmp_evt, "endmonth", sqlite3_column_int(stmt,10), NULL);
	g_object_set(tmp_evt, "endday", sqlite3_column_int(stmt, 11), NULL);
	g_object_set(tmp_evt, "endhour", sqlite3_column_int(stmt, 12), NULL);
	g_object_set(tmp_evt, "endmin", sqlite3_column_int(stmt, 13), NULL);
	g_object_set(tmp_evt, "isyearly", sqlite3_column_int(stmt, 14), NULL);
	g_object_set(tmp_evt, "isallday", sqlite3_column_int(stmt, 15), NULL);
	g_object_set(tmp_evt, "ispriority", sqlite3_column_int(stmt, 16), NULL);	
	g_object_set(tmp_evt, "hasnotification", sqlite3_column_int(stmt, 17), NULL);
	g_object_set(tmp_evt, "hasreminder", sqlite3_column_int(stmt, 18), NULL);
	g_object_set(tmp_evt, "remindermin", sqlite3_column_int(stmt, 19), NULL);	
	g_array_append_val(evt_arry, tmp_evt);	
	} //while
	sqlite3_finalize(stmt);
	sqlite3_close(db); 
}

//-------------------------------------------------------------------
// Delete row (single event)
//-------------------------------------------------------------------		
void db_delete_row(int id){
	
	printf("Delete row  %d\n", id);
	
	sqlite3 *db;
	int rc=0;
	sqlite3_stmt *stmt;
	char sql[2048] = "";
	
	/* Open database */
	const char *path=get_db_path();
	rc = sqlite3_open(path, &db);	
	if(rc) {
	printf("Can't open database: %s\n", sqlite3_errmsg(db));
	return;
	} else {
	printf("Opened database successfully\n");
	}
	
	sprintf(sql, "DELETE FROM EVENTS WHERE ID=%i", id);
	
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
	printf("SQL get events prepare error: %s\n", sqlite3_errmsg(db));
	}
	
	rc = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}
//------------------------------------------------------------------
// Delete all events
//------------------------------------------------------------------
void db_delete_all(){
	
	sqlite3 *db;
	int rc=0;
	sqlite3_stmt *stmt;
	char sql[2048] = "";
	
	/* Open database */
	const char *path=get_db_path();
	rc = sqlite3_open(path, &db); 
	if(rc) {
	printf("Can't open database: %s\n", sqlite3_errmsg(db));
	return;
	} else {
	printf("Opened database successfully\n");
	}
	
	sprintf(sql, "DELETE FROM EVENTS");	
	
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
	printf("SQL get events prepare error: %s\n", sqlite3_errmsg(db));
	}
	
	rc = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db); 
}

//---------------------------------------------------------------------
// Reset sequence
//----------------------------------------------------------------------

void db_reset_sequence(){
	
	sqlite3 *db;
	int rc=0;
	sqlite3_stmt *stmt;
	char sql[2048] = "";
	
	/* Open database */
	const char *path=get_db_path();
	rc = sqlite3_open(path, &db);	
	if(rc) {
	printf("Can't open database: %s\n", sqlite3_errmsg(db));
	return;
	} else {
	printf("Opened database successfully\n");
	}
	
	sprintf(sql, "DELETE FROM SQLITE_SEQUENCE WHERE NAME= 'EVENTS'");
	
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK){
	printf("SQL get events prepare error: %s\n", sqlite3_errmsg(db));
	}
	
	rc = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);  
}

