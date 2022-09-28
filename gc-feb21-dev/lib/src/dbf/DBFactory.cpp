
#include <rapidjson/filereadstream.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <cstdio>

#include "OracleDB.h"
#include "SQLiteDB.h"
//#include "MySqlDB.h"
#include "DBObjectException.h"
#include "DBConfigFileException.h"

#include "DBFactory.h"

using namespace rapidjson;

namespace gc
{
	namespace db
	{
		DBFactory DBFactory::dbObject;

		DBFactory::DBFactory()
		{
			dbObj = NULL;
			logDbObj = NULL;
		}

		DBFactory *DBFactory::getDBFactoryInstance()
		{
			return &dbObject;
		}

		IDBConnect *DBFactory::getIDBaseInstance()
		{
			try
			{
				int ch;
				rapidjson::Document configFile;

				FILE *conf = fopen("dbconfig.json", "r");

				if (conf == NULL)
				{
					throw DBConfigFileException(" ::DBConfigFileException:: COULD NOT OPEN CONFIGURATION FILE !");
				}
				else
				{
					char *readBuffer = new char[100];

					if (NULL == readBuffer)
					{
						throw DBConfigFileException(" ::DBConfigFileException:: CONFIGURATION FILE EMPTY !");
					}
					rapidjson::FileReadStream readStream(conf, readBuffer, sizeof(readBuffer));
					configFile.ParseStream(readStream);
					delete readBuffer;
					readBuffer = NULL;
				}

				if (configFile.HasParseError())
				{
					throw DBConfigFileException(" ::DBConfigFileException:: CONFIGURATION FILE CORRUPTED ! ");
				}

				if (false == configFile.HasMember("choice"))
				{
					throw DBConfigFileException(" ::DBConfigFileException:: CONFIGURATION FILE HAS NO CHOICE TAG !");
				}

				if (configFile["choice"].IsInt() == true)
					ch = configFile["choice"].GetInt();
				else
				{
					throw DBConfigFileException(" ::DBConfigFileException:: CONFIGURATION FILE HAS CORRUPT VALUE FOR CHOICE !");
				}

				string dbname;
				mtx_1.lock();
				if (dbObj == NULL)
				{
					switch (ch)
					{
					case 1:
						if (false == configFile.HasMember("ORACLE"))
						{
							throw DBConfigFileException(" ::DBConfigFileException:: CONFIGURATION FILE HAS NO ORACLE TAG !");
						}

						if (configFile["ORACLE"].IsString() == true)
						{
							dbname = configFile["ORACLE"].GetString();
						}
						else
						{
							throw DBConfigFileException(" ::DBConfigFileException:: CORRUPT VALUE FOR ORACLE IN DBCONFIG.JSON !");
						}

						dbObj = new OracleDB(dbname); // create instance of Oracle DB if not created.
						break;

						/*
						 * Support for mysql is disabled ...
						 * case 2:
							dbObj = new MySqlDB("test","","root","wonderfulday");	// create instance of MySql DB if not created. // read config pass db 
							break;
						*/

					case 3:
						if (false == configFile.HasMember("SQLITE"))
						{
							throw DBConfigFileException(" ::DBConfigFileException:: CONFIGURATION FILE HAS NO SQLITE TAG !");
						}

						if (configFile["SQLITE"].IsString() == true)
						{
							dbname = configFile["SQLITE"].GetString();
						}
						else
						{
							throw DBConfigFileException(" ::DBConfigFileException:: CORRUPT VALUE FOR SQLITE IN DBCONFIG.JSON !");
						}

						dbObj = new SQLiteDB(dbname); // create instance of SQLite DB if not created.
						break;
					}
				}
				mtx_1.unlock();
				if (dbObj == NULL)
				{
					mtx_1.unlock();
					throw DBObjectException(" ::DBObjectException:: INVALID CONFIG FILE ATTRIBUTES !");
				}
				return dbObj;
			}
			catch (DBObjectException &e)
			{
				mtx_1.unlock();
				throw DBObjectException("::DBObjectException:: DB OBJECT COULD NOT BE INSTANTIATED ! ");
			}
			catch (...)
			{
				mtx_1.unlock();
				throw;
			}
		}

		IDBConnect *DBFactory::getLogDBaseInstance()
		{
			try
			{
				string dbname;
				rapidjson::Document configFile;

				FILE *conf = fopen("DBConfig.json", "r");

				if (conf == NULL)
				{
					throw DBConfigFileException(" ::DBConfigFileException:: COULD NOT OPEN CONFIGURATION FILE !");
				}
				else
				{
					char *readBuffer = new char[100];

					if (NULL == readBuffer)
					{
						throw DBConfigFileException(" ::DBConfigFileException:: CONFIGURATION FILE EMPTY !");
					}
					rapidjson::FileReadStream readStream(conf, readBuffer, sizeof(readBuffer));
					configFile.ParseStream(readStream);
					delete readBuffer;
					readBuffer = NULL;
				}

				if (configFile.HasParseError())
				{
					throw DBConfigFileException(" ::DBConfigFileException:: CONFIGURATION FILE CORRUPTED ! ");
				}

				if (false == configFile.HasMember("LOGDB"))
				{
					throw DBConfigFileException(" ::DBConfigFileException:: CONFIGURATION FILE HAS NO SQLITE TAG !");
				}

				if (configFile["LOGDB"].IsString() == true)
				{
					dbname = configFile["LOGDB"].GetString();
				}
				else
				{
					throw DBConfigFileException(" ::DBConfigFileException:: CORRUPT VALUE FOR LOGDB IN DBCONFIG.JSON !");
				}
				//read the configuration file for dbname

				mtx_2.lock();
				if (logDbObj == NULL)
				{
					logDbObj = new SQLiteDB(dbname); // pass the db read from the above configuration file
				}
				mtx_2.unlock();
				if (logDbObj == NULL)
				{
					mtx_2.unlock();
				}
				return logDbObj;
			}
			catch (DBObjectException &e)
			{
				mtx_2.unlock();
				throw DBObjectException("::DBObjectException:: DB OBJECT COULD NOT BE INSTANTIATED ! ");
			}
		}

		DBFactory::~DBFactory()
		{
			delete dbObj;
			dbObj = NULL;
			delete logDbObj;
			logDbObj = NULL;
		}
	} // namespace db
} // namespace gc
