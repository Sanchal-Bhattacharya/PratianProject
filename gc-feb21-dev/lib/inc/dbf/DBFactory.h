/**
* @File : DBFactory.h
* @Author: Hemant Baid
* @Brief : This file contains the declaration for the DBFactory class
*/

#pragma once

#include <mutex>

#include "IDBConnect.h"

namespace gc
{
	namespace db
	{
		/**
		* This is the DB factory. It is a singleton class whose object is used throught the program. It instantiates the 
		* DB object for a particuar Database and once instantiated that object is again used throughout the program. 
		*/
		class DBFactory
		{
			static DBFactory dbObject;
			IDBConnect *dbObj;
			IDBConnect *logDbObj;
			std::mutex mtx_1, mtx_2;
			DBFactory();

		public:
			/**
			* This method is used to retrieve the singleton object of the class. A pointer poining to this singleton oject is
			* returned. Once called, after use donot call delete operator. Just reassign NULL.
			*/
			static DBFactory *getDBFactoryInstance(); // To get the DBFactory static object instance

			/**
			* This function is used to retrieve the Database instance of the instantiated object. One shouldnot call the delete operator
			* on the returned pointer. It is the responsibility of the DBFactory to delete the DBObject that has been instantiated. Just
			* reasign NULL after use and donot use it again.
			*/
			IDBConnect *getIDBaseInstance(); // To get the database instance

			/**
			* This function is used to retrieve the Log Database instance of the instantiated object. One shouldnot call the delete operator
			* on the returned pointer. It is the responsibility of the DBFactory to delete the DBObject that has been instantiated. Just
			* reasign NULL after use and donot use it again. It is used by logger utiliy in the project.
			*/
			IDBConnect *getLogDBaseInstance(); // To get the database instance for log util

			/**
			* Destructor for the DBFactory Class. Destroys the DBObject instantiated once the scope of the singleton object is over. Should 			* not be called by anyone.
			*/
			~DBFactory(); // Should be made private. Due for next release.
		};
	} // namespace db
} // namespace gc
