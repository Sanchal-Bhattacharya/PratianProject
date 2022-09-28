#include <fstream>

#include "DataTable.h"
#include "DataColumn.h"

#include "DBQueryException.h"
#include "DBConnectionException.h"
#include "DBDataTableException.h"

#include "SQLiteWrapper.h"

using namespace std;

namespace gc
{
	namespace db
	{
		SQLiteWrapper::SQLiteWrapper(string dbname)
		{
			this->dbname = dbname;
			db = NULL;
		}

		int SQLiteWrapper::getConnection()
		{
			ifstream fin(dbname);
			if (!fin)
			{
				throw DBConnectionException("DATABASE DOES NOT EXIST");
			}
			else
			{
				fin.close();
			}
			int rc = sqlite3_open_v2(dbname.c_str(), &db, SQLITE_OPEN_READWRITE, NULL);
			if (rc == 0)
			{
				return 1;
			}
			else
			{
				sqlite3_close(db);
				throw DBConnectionException("DATABASE CONNECTION FAILED");
			}
		}

		int SQLiteWrapper::executeNonQuery(string query)
		{

			char *zErrMsg = 0;
			int rc = sqlite3_exec(db, query.c_str(), NULL, 0, &zErrMsg);

			if (rc != SQLITE_OK)
			{
				string msg = ":: QUERRY EXCEPTION RAISED :: " + string(zErrMsg);
				throw DBQueryException(msg);
				sqlite3_free(zErrMsg);
				return 0;
			}
			return 1;
		}

		DataTable *SQLiteWrapper::executeQuery(string query)
		{

			int i;
			vector<int> types;
			vector<string> column_names;
			sqlite3_stmt *selectStmt;
			sqlite3_prepare(db, query.c_str(), query.size(), &selectStmt, NULL);

			int nos_of_columns;
			const char *name;
			nos_of_columns = sqlite3_column_count(selectStmt);
			for (i = 0; i < nos_of_columns; i++)
			{
				const char *type_of_column = sqlite3_column_decltype(selectStmt, i);
				switch (type_of_column[0])
				{
				case 'i':
					types.push_back(INT);
					name = sqlite3_column_name(selectStmt, i);
					column_names.push_back(string(name));
					break;
				case 'v':
					types.push_back(STRING);
					name = sqlite3_column_name(selectStmt, i);
					column_names.push_back(string(name));
					break;
				}
				name = NULL;
			}

			Schema *schema = new Schema(nos_of_columns, types, column_names);
			DataTable *table = new DataTable(schema);
			DataTable::DataRow *row = NULL;

			int integer_type_data;
			const unsigned char *text_type_data;
			while (1)
			{
				int s;
				s = sqlite3_step(selectStmt);
				if (s == SQLITE_ROW)
				{
					row = new DataTable::DataRow(table);
					for (i = 0; i < nos_of_columns; i++)
					{
						DataColumn *data;
						switch (types[i])
						{
						case STRING:
							text_type_data = sqlite3_column_text(selectStmt, i);
							data = new DataColumn(string(reinterpret_cast<const char *>(text_type_data)));
							break;
						case INT:
							integer_type_data = sqlite3_column_int(selectStmt, i);
							data = new DataColumn(integer_type_data);
							break;
						}
						row->addColumn(data);
						text_type_data = NULL;
						data = NULL;
					}
					table->addRow(row);
					row = NULL;
				}
				else if (s == SQLITE_DONE)
				{
					break;
				}
				else
				{
					throw DBDataTableException("FAILED TO MAKE TABLE.");
				}
			}
			sqlite3_finalize(selectStmt);
			selectStmt = NULL;

			return table;
		}

		int SQLiteWrapper::closeConnection()
		{
			sqlite3_close(db);
			return 1;
		}
	} // namespace db
} // namespace gc
