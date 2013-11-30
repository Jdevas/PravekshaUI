#include "Praveksha.h"

using namespace cv;
using namespace std;
using namespace gpu;


void DatabaseHandler::initiateDB()
{
	sqlite3 *db; 
	char *zErrMsg = 0;
	int rc;
	char *sql;

	rc = sqlite3_open("praveksha.db", &db);

	if( rc ){
		printf("Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}else{
		printf("Opened database successfully\n");
    }

	sql = "CREATE TABLE Vehicles("  \
         "ID INTEGER PRIMARY KEY     NOT NULL," \
         "SPEED			 INT     NOT NULL," \
         "TIMESTAMP      INTEGER NOT NULL);";

	rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);

	if( rc != SQLITE_OK ){
		printf("SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}else{
		fprintf(stdout, "Table created successfully\n");
	}

	sql = "CREATE TABLE Violations("  \
         "ID INTEGER PRIMARY KEY     NOT NULL," \
         "VIOLATION			 TEXT    NOT NULL," \
         "TIMESTAMP			 INTEGER NOT NULL);";

	rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);

	if( rc != SQLITE_OK ){
		printf("SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}else{
		fprintf(stdout, "Table created successfully\n");
	}


	sqlite3_close(db);
}

void DatabaseHandler::insertVehicle(int speed)
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char sql [500];
   
   /* Open database */
   rc = sqlite3_open("praveksha.db", &db);
   if( rc ){
      printf("Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      printf("Opened database successfully\n");
   }

   /* Create SQL statement */
   sprintf(sql, "%s%d%s", "INSERT INTO 'Vehicles' ('SPEED','TIMESTAMP') VALUES (", speed, ", datetime('now'));");
   
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      printf("SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      printf("Records created successfully\n");
   }

   sqlite3_close(db);
}

void DatabaseHandler::insertViolation(String violation, int violationId)
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char sqlTemp [100];
   char *sqlTemp2 = new char[violation.length() + 1];
   char sql [500];
   
   /* Open database */
   rc = sqlite3_open("praveksha.db", &db);
   if( rc ){
      printf("Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      printf("Opened database successfully\n");
   }

	cout << violation << endl;
	strcpy(sqlTemp2,violation.c_str());
	/* Create SQL statement */
	sprintf(sql, "%s%d%s", "INSERT INTO 'Violations' ('ID', 'VIOLATION', 'TIMESTAMP') VALUES (", violationId, ", '");
	strcat(sql, sqlTemp2);
	strcat(sql, "' , datetime('now'));");
	
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
		printf("SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}else{
		printf("Records created successfully\n");
	}

	sqlite3_close(db);
	system("pause");
   
}