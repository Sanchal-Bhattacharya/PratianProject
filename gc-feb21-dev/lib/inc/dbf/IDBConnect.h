/**
* @File : IDConnect.h
* @Author : Hemant Baid
* @Brief : This is the Inteface implemented by multiple databases.

*/
#pragma once
#include <string>
#include <iostream>
#include "DataTable.h"

using namespace std;
namespace gc
{
	namespace db
	{
		/** 
		* This file contains the declaration for The IDBConnect class
		* which is implemented by multiple databases to provide connection
		* accross multiple databases. It is an interface which is implemented
		* by the DB Classes : OracleDB, MySqlDB and SQLite. Any other DB that is
		* implemented needs to inherit this Interface to be used.
		*/
		struct IDBConnect
		{
			/**
			* Used to establish connection to the database by the class implementing this interface. 
			*/
			virtual int getConnection() =0 ; 
			
			/** 
			* Used to execute Select Statements by the class implementing this interface. 
			* Takes select query in string format as parameters. 
			*/
			virtual DataTable* execQuery(string querry) = 0 ;
			
			/**
			* Used to execute Insert, Update or Delete Statements by the class implementing this interface. 
			* Takes a select query in string format as parameters. 
			*/
			virtual int execNonQuery(string querry) = 0;
			
			/** 
			* Used to close connection to the database by the class implementing this interface.
			*/			
			virtual int closeConnection() = 0;
			
			/**
			* Virtual destructor used to destroy the interface pointer which points to derived class database object.
			*/
			virtual ~IDBConnect();
		};
	}
}
