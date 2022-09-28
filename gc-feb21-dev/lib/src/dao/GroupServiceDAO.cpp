#include "DBManager.h"
#include "DataTable.h"
#include "DAOConnectionException.h"
#include "DBQueryException.h"
#include "DAOQueryException.h"
#include "DBObjectException.h"
#include "DBDataColumnException.h"
#include "DBConfigFileException.h"
#include "DBQueryException.h"
#include "DBDataColumnException.h"

#include "Log.h"
#include "Connection.h"

#include "GroupServiceDAO.h"

using namespace gc::db;

namespace gc
{
	namespace dao
	{
		GroupServiceDAO::GroupServiceDAO()
		{
			try
			{
				dbObj = gc::db::DBManager::getIDBConnect();
			}
			catch (DBConfigFileException &dcfe)
			{
				util::Log::Error("GroupServiceDAOConnection", dcfe.what());
				dbObj = NULL;
				throw DAOConnectionException(dcfe.what());
			}
			catch (DBObjectException &doe)
			{
				util::Log::Error("GroupServiceDAOConnection", doe.what());
				dbObj = NULL;
				throw DAOConnectionException(doe.what());
			}
			catch (GCException &gce)
			{
				util::Log::Error("GroupServiceGCException", gce.what());
				dbObj = NULL;
				throw;
			}
			catch (...)
			{
				util::Log::Error("GroupServiceGeneralException", "Unexpected exception");
				dbObj = NULL;
				throw;
			}
			util::Log::Info("GroupServiceDAOConnection", "Connection to database successfully created");
		}

		GroupServiceDAO::~GroupServiceDAO()
		{
			dbObj = NULL;
			util::Log::Info("GroupServiceDAO", "dbObj turned to NULL");
		}

		void GroupServiceDAO::createGroup(entities::Group *group)
		{
			try
			{
				std::string Gname = group->getName();
				std::vector<string> email = group->getEmailList();

				std::stringstream ss;
				ss.clear();
				ss.str(string(""));
				ss << "call sp_createGroup('" << email[0] << "','" << Gname << "')"; //check this out
				const string &temp = ss.str();
				cout << temp << endl;
				cout << dbObj << endl;
				dbObj->execNonQuery(temp);
			}
			catch (DBQueryException &dqe)
			{
				util::Log::Error("GroupServiceDAOQueryException", dqe.what());
				dbObj = NULL;
				throw DAOQueryException(dqe.what());
			}
			catch (GCException &gce)
			{
				util::Log::Error("GroupServiceGCException", gce.what());
				dbObj = NULL;
				throw;
			}
			catch (...)
			{
				util::Log::Error("GroupServiceGeneralException", "Unexpected exception");
				dbObj = NULL;
				throw;
			}
		}

		void GroupServiceDAO::addMember(string GroupName, string email)
		{
			try
			{
				std::stringstream ss;
				ss.clear();
				ss.str(string(""));
				ss << "call sp_addUserToGroup('" << email << "','" << GroupName << "')"; //check this out
				const string &temp = ss.str();
				cout << temp << endl;
				cout << dbObj << endl;
				dbObj->execNonQuery(temp);
			}
			catch (DBQueryException &dqe)
			{
				util::Log::Error("GroupServiceDAOQueryException", dqe.what());
				dbObj = NULL;
				throw DAOQueryException(dqe.what());
			}
			catch (GCException &gce)
			{
				util::Log::Error("GroupServiceGCException", gce.what());
				dbObj = NULL;
				throw;
			}
			catch (...)
			{
				util::Log::Error("GroupServiceGeneralException", "Unexpected exception");
				dbObj = NULL;
				throw;
			}
		}

		void GroupServiceDAO::updateGroup(string OldGroupName, string NewGroupName)
		{
			try
			{
				std::stringstream ss;
				ss.clear();
				ss.str(string(""));
				ss << "call sp_updateGroupName('" << OldGroupName << "','" << NewGroupName << "')"; //check this out
				const string &temp = ss.str();
				cout << temp << endl;
				cout << dbObj << endl;
				dbObj->execNonQuery(temp);
			}
			catch (DBQueryException &dqe)
			{
				util::Log::Error("GroupServiceDAOQueryException", dqe.what());
				dbObj = NULL;
				throw DAOQueryException(dqe.what());
			}
			catch (GCException &gce)
			{
				util::Log::Error("GroupServiceGCException", gce.what());
				dbObj = NULL;
				throw;
			}
			catch (...)
			{
				util::Log::Error("GroupServiceGeneralException", "Unexpected exception");
				dbObj = NULL;
			}
		}

		void GroupServiceDAO::deleteGroup(string GroupName)
		{
			try
			{
				std::stringstream ss;
				ss.clear();
				ss.str(string(""));
				ss << "call sp_deleteGroup('" << GroupName << "')"; //check this out
				const string &temp = ss.str();
				cout << temp << endl;
				cout << dbObj << endl;
				dbObj->execNonQuery(temp);
			}
			catch (DBQueryException &dqe)
			{
				util::Log::Error("GroupServiceDAOQueryException", dqe.what());
				dbObj = NULL;
				throw DAOQueryException(dqe.what());
			}
			catch (GCException &gce)
			{
				util::Log::Error("GroupServiceGCException", gce.what());
				dbObj = NULL;
				throw;
			}
			catch (...)
			{
				util::Log::Error("GroupServiceGeneralException", "Unexpected exception");
				dbObj = NULL;
				throw;
			}
		}

		void GroupServiceDAO::removeUser(string GroupName, string email)
		{
			try
			{
				std::stringstream ss;
				ss.clear();
				ss.str(string(""));
				ss << "call sp_removeUserFromGroup('" << email << "','" << GroupName << "')"; //check this out
				const string &temp = ss.str();
				cout << temp << endl;
				cout << dbObj << endl;
				dbObj->execNonQuery(temp);
			}
			catch (DBQueryException &dqe)
			{
				util::Log::Error("GroupServiceDAOQueryException", dqe.what());
				dbObj = NULL;
				throw DAOQueryException(dqe.what());
			}
			catch (GCException &gce)
			{
				util::Log::Error("GroupServiceGCException", gce.what());
				dbObj = NULL;
				throw;
			}
			catch (...)
			{
				util::Log::Error("GroupServiceGeneralException", "Unexpected exception");
				dbObj = NULL;
				throw;
			}
		}

		std::vector<std::string> GroupServiceDAO::getAllUsers(string GroupName)
		{
			db::DataTable *table;
			try
			{
				std::vector<std::string> userlist;

				std::stringstream ss;
				ss.clear();
				ss.str(string(""));
				// ss << "SELECT email FROM GC_GROUP_TABLE join GC_USERGROUP_TABLE WHERE groupname = '" << GroupName << "'";
				ss << "SELECT email from GC_USERGROUP_TABLE WHERE groupid in (SELECT groupid from GC_GROUP_TABLE where groupname = '" << GroupName << "')";
				const string &temp = ss.str();
				cout << temp << endl;
				cout << dbObj << endl;
				table = dbObj->execQuery(temp);
				std::vector<db::DataTable::DataRow *> row = table->getRows();
				for (int i = 0; i < row.size(); i++)
				{
					userlist.push_back(row[i]->getColumn<std::string, STRING>(0)); //change index
				}
				delete table;
				table = NULL;
				return userlist;
			}
			catch (DBQueryException &dqe)
			{
				util::Log::Error("GroupServiceDAOQueryException", dqe.what());
				dbObj = NULL;
				throw DAOQueryException(dqe.what());
			}
			catch (DBDataColumnException &dce)
			{
				util::Log::Error("GroupServiceDataColumnException", dce.what());
				dbObj = NULL;
				delete table;
				table = NULL;
				throw DBDataColumnException(dce.what());
			}
			catch (GCException &gce)
			{
				util::Log::Error("GroupServiceGCException", gce.what());
				dbObj = NULL;
				throw;
			}
			catch (...)
			{
				util::Log::Error("GroupServiceGeneralException", "Unexpected exception");
				dbObj = NULL;
				throw;
			}
		}

		std::vector<std::string> GroupServiceDAO::getAllGroups()
		{
			db::DataTable *table;
			try
			{
				std::vector<std::string> grouplist;
				table = dbObj->execQuery("SELECT groupname FROM GC_GROUP_TABLE"); //change this
				std::vector<db::DataTable::DataRow *> row = table->getRows();
				for (int i = 0; i < row.size(); i++)
				{
					grouplist.push_back(row[i]->getColumn<std::string, STRING>(0)); //change index
				}
				delete table;
				table = NULL;
				return grouplist;
			}
			catch (DBQueryException &dqe)
			{
				util::Log::Error("GroupServiceDAOQueryException", dqe.what());
				dbObj = NULL;
				throw DAOQueryException(dqe.what());
			}
			catch (DBDataColumnException &dce)
			{
				util::Log::Error("GroupServiceDataColumnException", dce.what());
				dbObj = NULL;
				delete table;
				table = NULL;
				throw DAOQueryException(dce.what());
			}
			catch (GCException &gce)
			{
				util::Log::Error("GroupServiceGCException", gce.what());
				dbObj = NULL;
				throw;
			}
			catch (...)
			{
				util::Log::Error("GroupServiceGeneralException", "Unexpected exception");
				dbObj = NULL;
				throw;
			}
		}

	} // namespace dao
} // namespace gc
