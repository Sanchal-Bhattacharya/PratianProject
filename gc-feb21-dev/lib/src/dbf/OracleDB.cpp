#include "DBQueryException.h"
#include "DBConnectionException.h"

#include "OracleDB.h"

namespace gc
{
	namespace db
	{
		OracleDB::OracleDB(string dbname)
		{
			this->dbname = dbname;
			this->getConnection();
		}

		int OracleDB::getConnection()
		{
			try
			{
				otl_connect::otl_initialize(1); // Initialize the OTL Environment

				db.rlogon(dbname.c_str());
			}
			catch (otl_exception &e)
			{
				const char *str = reinterpret_cast<const char *>(e.msg);
				string msg = ":: DATABASE CONNECTION FAILED :: " + string(str);
				str = NULL;
				throw DBConnectionException(msg);
			}
		}

		DataTable *OracleDB::execQuery(string query)
		{
			DataTable *table = NULL;
			try
			{
				otl_stream i(300, query.c_str(), db);
				int nos_columns, nos_of_rows = 0;
				otl_column_desc *cols = i.describe_select(nos_columns);

				char char_column_content[50];
				int number_column_content;

				vector<int> types;
				vector<string> column_names;
				for (int j = 0; j < nos_columns; ++j)
				{
					switch ((cols + j)->otl_var_dbtype)
					{
					case STRING:
						types.push_back(1);
						column_names.push_back((cols + j)->name);
						break;
					case INT:
						types.push_back(2);
						column_names.push_back((cols + j)->name);
						break;
					}
				}

				Schema *schema = new Schema(nos_columns, types, column_names);
				table = new DataTable(schema);
				DataTable::DataRow *row;

				while (!i.eof())
				{
					row = new DataTable::DataRow(table);
					nos_of_rows++;
					for (int j = 0; j < nos_columns; ++j)
					{
						DataColumn *data;
						switch ((cols + j)->otl_var_dbtype)
						{
						case STRING:
							i >> char_column_content;
							data = new DataColumn(string(char_column_content));
							break;
						case INT:
							i >> number_column_content;
							data = new DataColumn(number_column_content);
							break;
						}
						row->addColumn(data);
						data = NULL;
					}
					table->addRow(row);
					row = NULL;
				}
				cols = NULL;

				if (nos_of_rows == 0)
				{
					//delete table;
					cout << ":: INVALID QUERY PASSED IN PARAMETERS :: Data for Select Query doesnot exist !";
					std::string emptyquerry = "SELECT * FROM GC_USER_TABLE";
					if (query == emptyquerry)
					{
						cout << "\n empty table \n";
						//DataTable *ntable ;
						return table;
					}
					else
						throw DBQueryException(":: INVALID QUERY PASSED IN PARAMETERS :: Data for Select Query does not exist !");
				}

				return table;
			}

			catch (otl_exception &e)
			{
				const char *str = reinterpret_cast<const char *>(e.msg);
				string msg = ":: INVALID QUERY PASSED IN PARAMETERS :: " + string(str);
				str = NULL;
				delete table;
				throw DBQueryException(msg);
			}
		}

		int OracleDB::execNonQuery(string query)
		{
			try
			{
				otl_cursor::direct_exec(db, query.c_str());
			}
			catch (otl_exception &e)
			{
				const char *str = reinterpret_cast<const char *>(e.msg);
				string msg = ":: INVALID QUERY PASSED IN PARAMETERS :: " + string(str);
				str = NULL;
				throw DBQueryException(msg);
			}
		}

		int OracleDB::closeConnection()
		{
			try
			{
				db.logoff();
			}
			catch (otl_exception &e)
			{
				const char *str = reinterpret_cast<const char *>(e.msg);
				string msg = string(str);
				str = NULL;
				throw DBConnectionException(msg);
			}
		}

		OracleDB::~OracleDB()
		{
			this->closeConnection();
		}
	} // namespace db
} // namespace gc
