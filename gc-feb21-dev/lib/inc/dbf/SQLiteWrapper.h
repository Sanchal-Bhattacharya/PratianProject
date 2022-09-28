/**
* @File: SQLiteWrapper.h
* @Author: Hemant Baid
* @Brief: This is the class that implements the IDBConnect interface for the Oracle Database.
*/

#pragma once

#include <string>
#include <sqlite3.h>

#include "DataTable.h"

using namespace std;

namespace gc
{
	namespace db
	{
		/**
		* The SQLiteWrapper class wraps the SQLite C interface to realize the functionalities required by SQLiteDB class 
		* to connect to Sqlite DB, fire queries and close connection. We use SQLiteC interface to implement the required 
		* functionalities and make it available to SQLiteDB through this C++ class.
		*/
		class SQLiteWrapper
		{
			sqlite3 *db;
			string dbname;

		public:
			/**
			* Constructor SQLiteDB() connects to oracle database and accepts the Database name as a char* parameter.
			* Also opens the DBConnection. 
			*/
			SQLiteWrapper(string dbname);

			/*
			* Used to open connection to the database by the class.
			*/
			int getConnection();

			/** 
			* Member function execQuerry() is used to execute Select Statements through the member object.
			* Takes select query in string format as parameters and returns a generic DataTable pointer to the
			* caller of this function otherwise throws error.
			*/
			int executeNonQuery(string query);

			/**
			* Member function execQuerry() is used to execute Create, Update and delete Statements through the member object.
			* Takes a query(stored proc or otherwise) in string format as parameters. Returns 1 on success otherwise throws 
			* error. 
			*/
			DataTable *executeQuery(string query);

			/** 
			* Used to close connection to the database by the class. Called in the destructor. The user should not call this function.
			*/
			int closeConnection();
		};
	} // namespace db
} // namespace gc
