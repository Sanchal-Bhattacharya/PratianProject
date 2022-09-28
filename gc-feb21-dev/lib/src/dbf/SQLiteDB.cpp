#include "SQLiteDB.h"
#include "DBQueryException.h"
#include "DBConnectionException.h"
#include "DBDataTableException.h"

namespace gc
{
	namespace db
	{
		SQLiteDB::SQLiteDB(string dbname)
		{
			this->dbname = new char[dbname.size() + 1];
			strcpy(this->dbname, dbname.c_str());
			db = new SQLiteWrapper(this->dbname);
			this->getConnection();
		}

		int SQLiteDB::getConnection()
		{
			try
			{
				int val = db->getConnection();
				return val;
			}
			catch (DBConnectionException &e)
			{
				throw e;
			}
		}

		DataTable *SQLiteDB::execQuery(string querry)
		{
			char *str = NULL;
			DataTable *table = NULL;
			try
			{
				str = new char[querry.size() + 1];
				strcpy(str, querry.c_str());
				table = db->executeQuery(str);
				delete[] str;
				str = NULL;
				return table; //    return the table from here
			}
			catch (DBQueryException &e)
			{
				delete[] str;
				str = NULL;
				delete table;
				throw e;
			}
		}
		int SQLiteDB::execNonQuery(string querry)
		{
			char *str = NULL;
			try
			{
				str = new char[querry.size() + 1];
				strcpy(str, querry.c_str());
				int val = db->executeNonQuery(str);
				delete[] str;
				str = NULL;
				return val;
			}
			catch (DBQueryException &e)
			{
				delete[] str;
				str = NULL;
				throw e;
			}
		}

		int SQLiteDB::closeConnection()
		{
			int val = db->closeConnection();
			return val;
		}

		SQLiteDB::~SQLiteDB()
		{
			this->closeConnection();
			delete db;
			db = NULL;
			delete[] dbname;
			dbname = NULL;
		}
	} // namespace db
} // namespace gc
