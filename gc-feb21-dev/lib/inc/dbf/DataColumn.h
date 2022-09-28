/**
* @File : DataColumn.h
* @Author : Hemant Baid
* @Brief : This is the Inteface implemented by multiple databases.
*/
#pragma once
#include <boost/any.hpp>
#include <string>
#include <iostream>

using namespace std;

namespace gc
{
	namespace db
	{
		/**
		* This is a genric column that encapsulates the column generated by any of our Databases : 
		* OracleDB, MySqlDB or SQLiteDB. It is used by the DataTable::DataRow. It is used to build 
		* the columns that is used by the DAO classes and the DBFramework. 
		*/
		class DataColumn
		{
			boost::any data;

		public:
			/**
			* Constructor for the DataColumn. It takes any type of arguments as parameters and stores
			* it in a boost::any type member variable.
			*/
			DataColumn(boost::any data);

			/**
			* This method returns the value stored in the column. It returns a boost::any type. This 
			* method is used internally by the DataTable::DataRow class which type casts it to the original
			* value using template function.
			*/
			boost::any getColumnData() const;

			/**
			* Setter function for Column. To be used by the internal DBFramework if need. This function should
			* not be used outside the DBFramework. 
			*/
			void setColumnData(boost::any data);
		};
	} // namespace db
} // namespace gc