/**
* @File : Schema.h
* @Author : Hemant Baid
* @Brief : This is the Inteface implemented by multiple databases.
*/

#pragma once	
#include <vector>
#include <string>
#include <cstring>

using namespace std;

namespace gc
{
	namespace db
	{
		/**
		* Class Schema is used to construct the Schema for the dataTable queried.It conatins the column type,
		* column name and nos of columns in a particular table It is a helper to the DataTable class and is used
		* in the constructor when a DataTable is created in the DBFramework.
		*/
		class Schema
		{
			int nos_of_columns;
			vector<int> column_types;
			vector<string> column_names;
		public:
			/**
			* Schema() Constructor takes the number of columns, a vector<int> of column types and a vector<string> of column
			* names as parameters to construct a Schema object.
			*/
			Schema(int nos, vector<int> &column_types, vector<string> &column_names);
			
			/**
			* Member function getColumnType() is used to extract the type of column for a particular table. Returns the 
			* type of the column at index i.
			*/
			int getColumnType(int index);
			
			/**
			* Member function getNumberOfColumns() is used to get the number of columns in the schema for a table. It returns
			* the total number of columns in any data table.
			*/
			int getNumberOfColumns();
			
			/**
			* Member function getColumnName() is used to extract the name of column for a particular table. Returns the 
			* name of the column at index i.
			*/
			string getColumnName(int index);
			
			/**
			* Member function getColumnIndex() is used to extract the index of column based on column name. Returns the index of 
			* the column and takes name of column as parameter in string format. 
			*/
			int getColumnIndex(string name);
		};
	}
}
