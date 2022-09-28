/**
* @File: OracleDB.h
* @Author: Hemant Baid
* @Brief: This is the class that implements the IDBConnect interface for the Oracle Database.
*/

#pragma once
#define OTL_ORA11G_R2
#include <vector>
#include <string>
#include "otlv4.h"

#include "IDBConnect.h"

using namespace std;

namespace gc
{
	namespace db
	{
		/**
		* The OracleDB class implements the IDBConnect interface to realize the functionalities required to connect to oracle DB
		* fire queries and close connection. We use OTL to connect to the OCCI internally.
		*/
		class OracleDB : public IDBConnect
		{
			//Member Variables
			//Member Variables
			otl_connect db;
			string dbname;

		public:
			/**
			* Constructor OracleDB() connects to oracle database and accepts the Database IP address as a string parameter.
			* Also opens the DBConnection. 
			*/
			OracleDB(string dbname); // parameter to constructor : string dbname, string user, string pwd

			/*
			* Used to open connection to the database by the class. Called in the constructor. The user should not call this function.
			*/
			int getConnection(); // Should be made private in furthur release

			/** 
			* Member function execQuerry() is used to execute Select Statements through the member object.
			* Takes select query in string format as parameters and returns a generic DataTable pointer to the
			* caller of this function otherwise throws error.
			*/
			DataTable *execQuery(string query);

			/**
			* Member function execQuerry() is used to execute Create, Update and delete Statements through the member object.
			* Takes a query(stored proc or otherwise) in string format as parameters. Returns 1 on success otherwise throws 
			* error. 
			*/
			int execNonQuery(string query);

			/** 
			* Used to close connection to the database by the class. Called in the destructor. The user should not call this function.
			*/
			int closeConnection(); // Should be made private in furthur release

			/**
			* Used to deallocate any resources used by the class. Also closes the DBConnection.
			*/
			~OracleDB();
		};
	} // namespace db
} // namespace gc
