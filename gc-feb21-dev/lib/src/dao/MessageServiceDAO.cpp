#include "DBManager.h"
#include "DataTable.h"
#include "DAOConnectionException.h"
#include "DAOQueryException.h"
#include "DBQueryException.h"
#include "DBConfigFileException.h"
#include "DBObjectException.h"
#include "DBDataColumnException.h"
#include "Log.h"
#include "DataTable.h"
#include "User.h"

#include "MessageServiceDAO.h"

using namespace gc::db;
namespace gc
{
	namespace dao
	{
		MessageServiceDAO::MessageServiceDAO()
		{
			try
			{
				dbObj = gc::db::DBManager::getIDBConnect();
			}
			catch (DBConfigFileException &dcfe)
			{
				util::Log::Error("MessageServiceDAOConnection", dcfe.what());
				dbObj = NULL;
				throw DAOConnectionException(dcfe.what());
			}
			catch (DBObjectException &doe)
			{
				util::Log::Error("MessageServiceDAOConnection", doe.what());
				dbObj = NULL;
				throw DAOConnectionException(doe.what());
			}
			util::Log::Info("MessageServiceDAOConnection", "Connection to database successfully created");
		}

		std::vector<entities::Connection *> MessageServiceDAO::getConnectionTable()
		{
		}

		std::vector<std::string> MessageServiceDAO::getAllUsers()
		{
			db::DataTable *table;
			try
			{
				std::vector<std::string> emaillist;
				table = dbObj->execQuery("SELECT * FROM GC_USER_TABLE");
				std::vector<db::DataTable::DataRow *> row = table->getRows();
				for (int i = 0; i < row.size(); i++)
				{
					std::string s1 = row[i]->getColumn<std::string, STRING>(1);
					emaillist.push_back(s1);
				}
				delete table;
				stringstream ss;
				ss.clear();
				ss.str(string(""));
				ss << "Table at address : " << table << "is deleted";
				std::string temp = ss.str();
				util::Log::Info("MessageServiceDAO", temp);
				return emaillist;
			}
			catch (DBQueryException &dqe)
			{
				util::Log::Error("MessageServiceDAOQueryException", dqe.what());
				dbObj = NULL;
				throw DAOQueryException(dqe.what());
			}
			catch (DBDataColumnException &dce)
			{
				util::Log::Error("MessageServiceDataColumnException", dce.what());
				delete table;
				table = NULL;
				dbObj = NULL;
				throw DBDataColumnException(dce.what());
			}
			catch (GCException &gce)
			{
				util::Log::Error("MessageServiceGCException", gce.what());
				dbObj = NULL;
				throw;
			}
			catch (...)
			{
				util::Log::Error("MessageServiceGeneralException", "Unexpected exception");
				dbObj = NULL;
				throw;
			}
		}

		void MessageServiceDAO::addMessageDB(entities::Message *msg)
		{
			try
			{
				std::stringstream ss;
				ss.clear();
				ss.str(string(""));
				long int msg_id = msg->getMsgId();
				string serializedMsg = serialize(msg);
				ss << "call sp_insertObject(" << msg_id << ",'" << serializedMsg << "')"; //check this out
				const string &temp = ss.str();
				cout << temp << endl;
				cout << dbObj << endl;
				dbObj->execNonQuery(temp);
			}
			catch (DBQueryException &dqe)
			{
				util::Log::Error("MessageServiceDAOQueryException", dqe.what());
				dbObj = NULL;
				throw DAOQueryException(dqe.what());
			}
			catch (GCException &gce)
			{
				util::Log::Error("MessageServiceGCException", gce.what());
				dbObj = NULL;
				throw;
			}
			catch (...)
			{
				util::Log::Error("MessageServiceGeneralException", "Unexpected exception");
				dbObj = NULL;
				throw;
			}
		}

		void MessageServiceDAO::deleteMessageDB(entities::Message *msg)
		{
			try
			{
				std::stringstream ss;
				ss.clear();
				ss.str(string(""));
				long int msg_id = msg->getMsgId();
				string serializedMsg = serialize(msg);
				ss << "call sp_deleteObject(" << msg_id << ",'" << serializedMsg << "')"; //check this out
				const string &temp = ss.str();
				cout << temp << endl;
				cout << dbObj << endl;
				dbObj->execNonQuery(temp);
			}
			catch (DBQueryException &dqe)
			{
				util::Log::Error("MessageServiceDAOQueryException", dqe.what());
				dbObj = NULL;
				throw DAOQueryException(dqe.what());
			}
			catch (GCException &gce)
			{
				util::Log::Error("MessageServiceGCException", gce.what());
				dbObj = NULL;
				throw;
			}
			catch (...)
			{
				util::Log::Error("MessageServiceGeneralException", "Unexpected exception");
				dbObj = NULL;
				throw;
			}
		}

		std::vector<entities::Message *> MessageServiceDAO::restore()
		{
			db::DataTable *table;
			try
			{
				std ::cout << "calling query SELECT * FROM GC_PERSISTENCE_TABLE\n";
				std::vector<entities::Message *> MsgObjects;
				table = dbObj->execQuery("SELECT * FROM GC_PERSISTENCE_TABLE");
				std::vector<db::DataTable::DataRow *> row = table->getRows();
				std ::cout << "Restoring table rows\n";
				for (int i = 0; i < row.size(); i++)
				{
					std::string s1 = row[i]->getColumn<std::string, STRING>(1);
					MsgObjects.push_back(deserialize(s1));
				}
				delete table;
				stringstream ss;
				ss.clear();
				ss.str(string(""));
				ss << "Table at address : " << table << "is deleted";
				std::string temp = ss.str();
				util::Log::Info("MessageServiceDAO", temp);
				return MsgObjects;
			}
			catch (DBQueryException &dqe)
			{
				util::Log::Error("MessageServiceDAOQueryException", dqe.what());
				dbObj = NULL;
				throw DAOQueryException(dqe.what());
			}
			catch (DBDataColumnException &dce)
			{
				util::Log::Error("MessageServiceDataColumnException", dce.what());
				delete table;
				table = NULL;
				dbObj = NULL;
				throw DBDataColumnException(dce.what());
			}
			catch (GCException &gce)
			{
				util::Log::Error("MessageServiceGCException", gce.what());
				dbObj = NULL;
				throw;
			}
			catch (...)
			{
				util::Log::Error("MessageServiceGeneralException", "Unexpected exception");
				dbObj = NULL;
				throw;
			}
		}

		std::string MessageServiceDAO::serialize(entities::Message *msg)
		{
			return (std::to_string(msg->getMsgId()) + ">=" + msg->getToId() + ">=" + msg->getFromId() + ">=" + msg->getMessage() + ">=" + std::to_string(msg->getMessageType()) + ">=" + std::to_string(msg->getAckStatus()) + ">=");
		}

		entities::Message *MessageServiceDAO::deserialize(string serializedMsg)
		{
			//cout<<serializedMsg<<"\n\n\n";
			std::string delimiter = ">=";
			size_t pos = 0;
			vector<std::string> tokens;
			while ((pos = serializedMsg.find(delimiter)) != std::string::npos)
			{
				//cout<<serializedMsg.substr(0, pos)<<"\n\n\n";
				tokens.push_back(serializedMsg.substr(0, pos));
				serializedMsg.erase(0, pos + delimiter.length());
			}

			entities::Message *msg = new entities::Message(stoi(tokens[0]), tokens[1], tokens[2], tokens[3], stoi(tokens[4]), stoi(tokens[5]));
			return msg;
		}

		MessageServiceDAO::~MessageServiceDAO()
		{
			dbObj = NULL;
			util::Log::Info("MessageServiceDAO", "dbObj turned to NULL");
		}
	} // namespace dao
} // namespace gc
