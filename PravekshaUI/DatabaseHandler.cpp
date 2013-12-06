#include "DatabaseHandler.h"

typedef struct ViolationData
{
  String violation;
  int violationId;
  int violationType;
} ;

DatabaseHandler::DatabaseHandler(){

}

DWORD WINAPI Thread_initiate_DB( LPVOID lpParam ) 
{
	ofstream fi;
	fi.open("debug.txt");

    int     Data = 0;
    int     count = 0;
    HANDLE  hStdout = NULL;
    
    // Get Handle To screen.
    // Else how will we print?
    if( (hStdout = 
         GetStdHandle(STD_OUTPUT_HANDLE)) 
         == INVALID_HANDLE_VALUE )  
    return 1;

    // Cast the parameter to the correct
    // data type passed by callee i.e main() in our case.
    Data = *((int*)lpParam); 
	
	sqlite3 *db; 
	char *zErrMsg = 0;
	int rc;
	char *sql;

	rc = sqlite3_open("praveksha.db", &db);

	if( rc ){
		fi << "Can't open database" << endl;
		sqlite3_free(zErrMsg);
		exit(0);
	}

	sql = "CREATE TABLE Vehicles("  \
         "ID INTEGER PRIMARY KEY     NOT NULL," \
         "SPEED			 INT     NOT NULL," \
         "TIMESTAMP      INTEGER NOT NULL);";

	rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);

	if( rc != SQLITE_OK ){
		fi << "Can't create table" << endl;
		sqlite3_free(zErrMsg);
	}

	sql = "CREATE TABLE Violations("  \
         "ID INTEGER PRIMARY KEY     NOT NULL," \
		 "VIOLATION_ID		 INTEGER NOT NULL," \
		 "VIOLATION_TYPE	 INTEGER NOT NULL," \
         "VIOLATION			 TEXT    NOT NULL," \
         "TIMESTAMP			 INTEGER NOT NULL);";

	rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);

	if( rc != SQLITE_OK ){
		fi << "Can't create table" << endl;
		sqlite3_free(zErrMsg);
	}

	sqlite3_close(db);
	fi.close();
    return 0; 
} 

DWORD WINAPI Thread_insertVehicle( LPVOID lpParam ) 
{
	int speed = 0;
	speed = (int)lpParam; 
	sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char sql [500];

   ofstream fi;
	fi.open("debug.txt");
   
   /* Open database */
   rc = sqlite3_open("praveksha.db", &db);
   if( rc ){
      fi << "Can't open database" << endl;
      exit(0);
   }

   /* Create SQL statement */
   sprintf(sql, "%s%d%s", "INSERT INTO 'Vehicles' ('SPEED','TIMESTAMP') VALUES (", speed, ", datetime('now'));");
   
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      fi << "Can't insert vehicle details" << endl;
      sqlite3_free(zErrMsg);
   }

   sqlite3_close(db);
   fi.close();
    return 0; 
} 

DWORD WINAPI Thread_insertViolation( LPVOID lpParam ) 
{
	ViolationData* violationData = (ViolationData*)lpParam;
	
	String violation = violationData->violation;
	int violationId = violationData->violationId;
	int violationType = violationData->violationType;

	delete violationData;
	//speed = (int)lpParam; 
	sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char sqlTemp [100];
   char *sqlTemp2 = new char[violation.length() + 1];
   char sql [500];

   ofstream fi;
	fi.open("debug.txt");
   
   /* Open database */
   rc = sqlite3_open("praveksha.db", &db);
   if( rc ){
      fi << "Can't open DB" << endl;
      exit(0);
   }

	strcpy(sqlTemp2,violation.c_str());
	/* Create SQL statement */
	sprintf(sql, "%s%d%s%d%s", "INSERT INTO 'Violations' ('VIOLATION_ID', 'VIOLATION_TYPE', 'VIOLATION', 'TIMESTAMP') VALUES (", violationId, ",", violationType,", '");
	strcat(sql, sqlTemp2);
	strcat(sql, "' , datetime('now'));");
	
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
		fi << "Can't Insert Violation data" << endl;
		sqlite3_free(zErrMsg);
	}

	sqlite3_close(db);
	fi.close();

    return 0; 
} 

void DatabaseHandler::initiateDB()
{
	HANDLE Handle_Of_Thread_1 = 0;
	int Data_Of_Thread_1 = 1;
	Handle_Of_Thread_1 = CreateThread( NULL, 0, Thread_initiate_DB, &Data_Of_Thread_1, 0, NULL);  
    if ( Handle_Of_Thread_1 == NULL)
        ExitProcess(Data_Of_Thread_1);
}

void DatabaseHandler::insertVehicle(int speed)
{
	HANDLE Handle_Of_Thread_1 = 0;
	int Data_Of_Thread_1 = 1;
	Handle_Of_Thread_1 = CreateThread( NULL, 0, Thread_insertVehicle, (LPVOID)speed, 0, NULL);  
    if ( Handle_Of_Thread_1 == NULL)
        ExitProcess(Data_Of_Thread_1);
}

void DatabaseHandler::insertViolation(String violation, int inViolationId, int violationType)
{
	ViolationData* violationData;
	violationData = new ViolationData;
	
	violationData->violation = violation;
	violationData->violationId = inViolationId;
	violationData->violationType = violationType;
		
	HANDLE Handle_Of_Thread_1 = 0;
	int Data_Of_Thread_1 = 1;
	Handle_Of_Thread_1 = CreateThread( NULL, 0, Thread_insertViolation, violationData, 0, NULL);  
    if ( Handle_Of_Thread_1 == NULL)
        ExitProcess(Data_Of_Thread_1);

 
}

vector<vector <int>> DatabaseHandler::retrieveTodayData(){
	int totVehicles;
	sqlite3 *db;
	sqlite3_stmt *res;
	const char *tail;
	int count = 0;
	
	ofstream fi;
	fi.open("debug.txt");
	
	if(sqlite3_open("praveksha.db", &db))
	{
		fi << "Can't open DB" << endl;
		sqlite3_close(db);
	}

	if(sqlite3_prepare_v2(db, "SELECT Count(ID) FROM Vehicles WHERE TIMESTAMP >= date('now','-1 day')", 128, &res, &tail) != SQLITE_OK)
	{
		fi << "SQL error" << endl;
		sqlite3_close(db);
	}else{
		while(sqlite3_step(res) == SQLITE_ROW)
		{
			totVehicles = sqlite3_column_int(res,0);
		}
	}

	if(sqlite3_prepare_v2(db, "SELECT COUNT(distinct VIOLATION_TYPE) from violations", 128, &res, &tail) != SQLITE_OK)
	{
		fi << "SQL error" << endl;
		sqlite3_close(db);
	}else{
		
		while(sqlite3_step(res) == SQLITE_ROW)
		{
			count = sqlite3_column_int(res,0);
		}
	}
	
	vector<vector <int>> violations(count+1, vector<int>(2));
	violations[0][0] = totVehicles;
	count = 1;

	if(sqlite3_prepare_v2(db, "SELECT VIOLATION_TYPE, Count(ID) FROM Violations WHERE TIMESTAMP >= date('now','-1 day') group by VIOLATION_TYPE", 128, &res, &tail) != SQLITE_OK)
	{
		fi << "SQL error" << endl;
		sqlite3_close(db);
	}else{
		
		while(sqlite3_step(res) == SQLITE_ROW)
		{
			violations[count][0] = sqlite3_column_int(res,0);
			violations[count][1] = sqlite3_column_int(res,1);
			count++;
		}
	}

	sqlite3_finalize(res);
	sqlite3_close(db);
	fi.close();
	return violations;
}