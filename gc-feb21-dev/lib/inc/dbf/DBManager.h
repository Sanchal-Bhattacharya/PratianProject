/**
* @File : DBManager.h
* @Author : Hemant Baid
* @Brief : This is the boundary class used to get the Database object from the  DBFactory
*/

#pragma once

#include "DBFactory.h"
#include "IDBConnect.h"

namespace gc
{
	namespace db
	{
	/**
	* This is the boundary class with static methods to retrieve an Interface pointer to the DB object used to fire 
	* queries.
	*/
		class DBManager
		{
		public:
			/**
			* Static Member function used to instantiate and return a Database object that can be used by the interface IDBConnect
			* pointer to fire querries.
			*/
			static IDBConnect* getIDBConnect();		// Returns the DB-Class object w.r.t. the configyuration set in DBFactory
			
			/**
			* Static Member function used to instantiate and return a Database object that can be used by the interface IDBConnect
			* pointer to fire querries on the logger database.
			*/
			static IDBConnect* getLoggerDB();		// Returns an SQLite Conncetion  to the Log Factory. To be used only by logger.
		};
	}
}	
