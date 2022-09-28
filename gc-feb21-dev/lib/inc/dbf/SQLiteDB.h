/**
* @File: SQLiteDB.h
* @Author: Hemant Baid
* @Brief: This is the class that implements the IDBConnect interface for the Oracle Database.
*/

#pragma once

#include "IDBConnect.h"
#include "SQLiteWrapper.h"

namespace gc
{
	namespace db
	{
		/**
		* The SQLiteDB class implements the IDBConnect interface to realize the functionalities required to connect to Sqlite DB
		* fire queries and close connection. We use SQLWrapper class to implement the required functionalities internally.
		*/
		class SQLiteDB : public IDBConnect
		{
			//Member Variables
			//Member Variables
			char *dbname;
			SQLiteWrapper *db;

		public:
			/**
			* Constructor SQLiteDB() connects to oracle database and accepts the Database name as a string parameter.
			* Also opens the DBConnection. 
			*/
			SQLiteDB(string dbname);

			/*
			* Used to open connection to the database by the class. Called in the constructor. The user should not call this function.
			*/
			int getConnection();

			/** 
			* Member function execQuerry() is used to execute Select Statements through the member object.
			* Takes select query in string format as parameters and returns a generic DataTable pointer to the
			* caller of this function otherwise throws error.
			*/
			DataTable *execQuery(string querry);

			/**
			* Member function execQuerry() is used to execute Create, Update and delete Statements through the member object.
			* Takes a query(stored proc or otherwise) in string format as parameters. Returns 1 on success otherwise throws 
			* error. 
			*/
			int execNonQuery(string querry);

			/** 
			* Used to close connection to the database by the class. Called in the destructor. The user should not call this function.
			*/
			int closeConnection();

			/**
			* Used to deallocate any resources used by the class. Also closes the DBConnection.
			*/
			~SQLiteDB();
		};
	} // namespace db
} // namespace gc
