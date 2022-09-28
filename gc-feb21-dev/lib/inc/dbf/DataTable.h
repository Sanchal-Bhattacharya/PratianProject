/**
* @File : DataTable.h
* @Author : Hemant Baid
* @Brief : This is the Inteface implemented by multiple databases.
*/

#pragma once
#include "Schema.h"
#include "DataColumn.h"
#include "DBMacro.h"
#include "DBDataColumnException.h"

using namespace std;

namespace gc
{
	namespace db
	{
		/**
		* This is the generic DataTable that maps to tables of the underlying databases in the DBFramework.
		* It is used both by DAO and DBFramework. The DBFramework uses it to build the table requested and 
		* return this table to the DAO layer. The DAO uses it to iterate through the various rows that the table
		* might contain. This class has an internal DataRow class which is used to populate the DataColumns. Every 
		* DataTable encaplsulates a Schema object pointer which points to the Scehma that defines the nos of columns, 
		* the types of columns and the name of columns.
		*/
		class DataTable
		{
		public:
			/**
			* This is an internal class to DataTable. It is used to build columns by the DBFramework and DAO uses
			* its template function T getColumn<typename T,int type>() which return the column data based on either Index of colum
			* or name of coulmn. Every DataRow object contains a pointer to the DataTable it belongs to.
			*/
			class DataRow;

		private:
			vector<DataTable::DataRow *> tuple;
			Schema *schema;

		public:
			class DataRow
			{
				vector<DataColumn *> column;
				DataTable *table;

			public:
				/**
					* Constructor for DataRow which constructs a DataRow object that points to the table it belongs.
					* It is used by the DBFramework in generating the genertic DataRow and each row encapsulates a 
					* vector of columns. To construct a DataRow pass a pointer to DataTable as parameter.
					*/
				DataRow(DataTable *table);

				/** 
					* Member function addColumn() takes a DataColumn object as paraeters and builds a particular column in a row.
					* Currently we support String and Int type of data to be querried and stored.
					*/
				void addColumn(DataColumn *data);

				/**
					* Template member function T getColumn<class T,int type>(int index) takes the column index as function parameter
					* and returns the data either in String or Int format. It take TYPE as parameters which can either be INT or STRING.
					* When calling the user needs to provide type of data and the expected column type as parameter to the respective 						* function. If the user enters incorrect type of data or column type for the column index it throws a 
					* bad cast exception. 
					*/
				template <class T, int type>
				T getColumn(int index)
				{
					T column_data;

					if (index <= table->getNumberOfColumns())
					{
						int column_type = table->getColumnType(index);
						if (type == column_type)
						{
							column_data = boost::any_cast<T>(column[index]->getColumnData());
						}
						else
						{
							throw DBDataColumnException("::DBDataColumnException:: BAD CAST WHEN CALL TO FUNCTION getColumn<T,type>()!");
						}
						return column_data;
					}
					else
					{
						throw DBDataColumnException("::DBDataColumnException:: INVALID INDEX FOR COLUMN PASSED IN PARAMETERS !");
					}
				}

				/**
					* Template member function T getColumn<class T,int type>(string name) takes the column name as function parameter
					* and returns the data either in String or Int format. It take TYPE as parameters which can either be INT or STRING.
					* When calling the user needs to provide type of data and the expected column type as parameter to the respective 						* function. If the user enters incorrect type of data or column type for the column names it throws a bad cast 						* exception. 
					*/
				template <class T, int type>
				T getColumn(string name)
				{
					T column_data;

					int index = table->getColumnIndex(name);
					if (index <= table->getNumberOfColumns())
					{
						int column_type = table->getColumnType(index);
						if (type == column_type)
						{
							column_data = boost::any_cast<T>(column[index]->getColumnData());
						}
						else
						{
							throw DBDataColumnException("::DBDataColumnException:: BAD CAST WHEN CALL TO FUNCTION getColumn<T,type>()!");
						}
						return column_data;
					}
					else
					{
						throw DBDataColumnException("::DBDataColumnException:: INVALID INDEX FOR COLUMN PASSED IN PARAMETERS !");
					}
				}
				~DataRow();
			};

			/**
			* Constructor for DataTable which constructs a DataTable object that points to the Schema it belongs.
			* It is used by the DBFramework in generating the genertic DataTable and each table encapsulates a 
			* vector of rows. To construct a DataTable pass a pointer to Schema as parameter.
			*/
			DataTable(Schema *data);

			/** 
			* Member function addRow() takes a DataRow object as paraeters and builds a particular row in a table.
			* Each row contains a vector of DataColumn pointers that store the data present in he column.
			*/
			void addRow(DataTable::DataRow *row);

			/** 
			* Member function getRow() returns all the rows that are present in the DataTable querried by the user.
			* It returns a vector<DataTable::DataRow *> contains all the data rows.
			*/
			vector<DataTable::DataRow *> getRows();

			/**
			* Member function geColumnType() returns the type of columns stored in the table. It takes the index of the
			* column querried as parameter.
			*/
			int getColumnType(int index);

			/**
			* Member function geColumnIndex() returns the index of columns stored in the table based on the column name. 
			* It takes the index of the column querried as parameter.
			*/
			int getColumnIndex(string name);

			/**
			* Member function getNumberOfColumns() returns the number of columns stored in a particular table.
			*/
			int getNumberOfColumns();

			/**
			* Destructor od DataTable object. Destroys the memory allocated to the table. It is the responsibilty of the user
			* using this object to destroy the table and call the destructor after use. Otherwise it will lead to memory leaks.
			*/
			~DataTable();
		};

	} // namespace db
} // namespace gc
