#include "Connection.h"
#include "DBManager.h"
#include "DataTable.h"

#include "DBManager.h"
#include "DataTable.h"
#include "DAOConnectionException.h"
#include "DAOQueryException.h"
#include "DBQueryException.h"
#include "DBObjectException.h"
#include "DBDataColumnException.h"
#include "DBConfigFileException.h"
#include "Log.h"

#include "UserServiceDAO.h"

using namespace gc::db;

namespace gc
{
	namespace dao
	{
		UserServiceDAO::UserServiceDAO()
		{
			try
			{
				dbObj = gc::db::DBManager::getIDBConnect();
			}
			catch (DBConfigFileException &dcfe)
			{
				util::Log::Error("UserServiceDAOConnection", dcfe.what());
				dbObj = NULL;
				throw DAOConnectionException(dcfe.what());
			}
			catch (DBObjectException &doe)
			{
				util::Log::Error("UserServiceDAOConnection", doe.what());
				dbObj = NULL;
				throw DAOConnectionException(doe.what());
			}
			catch (GCException &gce)
			{
				util::Log::Error("UserServiceDAOQueryException", gce.what());
				dbObj = NULL;
				throw;
			}
			catch (...)
			{
				util::Log::Error("UserServiceDAOQueryException", "Unexpected exception");
				dbObj = NULL;
				throw;
			}
			util::Log::Info("UserServiceDAOConnection", "Connection to database successfully created");
		}

		void UserServiceDAO::createUser(entities::User *user)
		{
			try
			{
				//int userid = 1;
				std::string name = user->getName();
				std::string email = user->getEmail();
				std::string mobile = user->getMobileNumber();
				std::string password = user->getPassword();
				std::string salt = user->getSalt();
				std::stringstream ss;
				ss.clear();
				ss.str(string(""));
				ss << "call sp_create('" << email << "','" << name << "','" << mobile << "','" << password << "','" << salt << "')";
				const string &temp = ss.str();
				cout << temp << endl;
				cout << dbObj << endl;
				dbObj->execNonQuery(temp);
				//delete user;
				user = NULL;
				stringstream ss2;
				ss2.clear();
				ss2.str(string(""));
				ss2 << "User at address : " << user << "is deleted";
				string temp2 = ss2.str();
				util::Log::Info("UserServiceDAO", temp);
			}
			catch (DBQueryException &dqe)
			{
				util::Log::Error("UserServiceDAOQueryException", dqe.what());
				dbObj = NULL;
				delete user;
				user = NULL;
				throw DAOQueryException(dqe.what());
			}
			catch (GCException &gce)
			{
				util::Log::Error("UserServiceGCException", gce.what());
				dbObj = NULL;
				delete user;
				user = NULL;
				throw;
			}
			catch (...)
			{
				util::Log::Error("UserServiceDAOGeneralException", "Unexpected exception");
				dbObj = NULL;
				delete user;
				user = NULL;
				throw;
			}
		}

		void UserServiceDAO::createUserFromList(std::vector<entities::User *> userlist)
		{
			try
			{
				int i;
				for (i = 0; i < userlist.size(); i++)
				{
					this->createUser(userlist[i]);
				}
			}
			catch (DBQueryException &dqe)
			{
				util::Log::Error("UserServiceDAOQueryException", dqe.what());
				dbObj = NULL;
				throw DAOQueryException(dqe.what());
			}
			catch (GCException &gce)
			{
				util::Log::Error("UserServiceGCException", gce.what());
				dbObj = NULL;
				throw;
			}
			catch (...)
			{
				util::Log::Error("UserServiceDAOGeneralException", "Unexpected exception");
				dbObj = NULL;
				throw;
			}
		}

		void UserServiceDAO::updateUser(entities::User *user)
		{
			try
			{
				std::string name = user->getName();
				std::string email = user->getEmail();
				std::string mobile = user->getMobileNumber();
				std::string password = user->getPassword();
				std::string salt = user->getSalt();
				std::stringstream ss;
				ss.clear();
				ss.str(string(""));
				ss << "call sp_update('" << email << "','" << name << "','" << mobile << "','" << password << "','" << salt << "')";
				const string &temp = ss.str();
				dbObj->execNonQuery(temp);
				//delete user;

				user = NULL;
				stringstream ss2;
				ss2.clear();
				ss2.str(string(""));
				ss2 << "User at address : " << user << "is deleted";
				string temp2 = ss2.str();
				util::Log::Info("UserServiceDAO", temp2);
			}
			catch (DBQueryException &dqe)
			{
				util::Log::Error("UserServiceDAOQueryException", dqe.what());
				dbObj = NULL;
				delete user;
				user = NULL;
				throw DAOQueryException(dqe.what());
			}
			catch (GCException &gce)
			{
				util::Log::Error("UserServiceDAOGCException", gce.what());
				dbObj = NULL;
				throw;
			}
			catch (...)
			{
				util::Log::Error("UserServiceDAOGeneralException", "Unexpected exception");
				dbObj = NULL;
				throw;
			}
		}

		void UserServiceDAO::deleteUser(std::string email)
		{
			try
			{

				std::stringstream ss;
				ss.clear();
				ss.str(string(""));
				ss << "call sp_delete('" << email << "')";
				const string &temp = ss.str();
				dbObj->execNonQuery(temp);
			}
			catch (DBQueryException &dqe)
			{
				util::Log::Error("UserServiceDAOQueryException", dqe.what());
				dbObj = NULL;
				throw DAOQueryException(dqe.what());
			}
		}

		entities::User *UserServiceDAO::getUser(std::string email)
		{
			db::DataTable *table;
			try
			{
				std::stringstream ss;
				ss.clear();
				ss.str(string(""));
				ss << "SELECT * FROM GC_USER_TABLE WHERE EMAIL = '" << email << "'";
				const string &temp = ss.str();
				table = dbObj->execQuery(temp);
				std::vector<db::DataTable::DataRow *> row = table->getRows();
				entities::User *user = new entities::User(row[0]->getColumn<std::string, STRING>(2), row[0]->getColumn<std::string, STRING>(1), row[0]->getColumn<std::string, STRING>(3), row[0]->getColumn<std::string, STRING>(4), row[0]->getColumn<std::string, STRING>(5));
				delete table;
				table = NULL;
				stringstream ss2;
				ss2.clear();
				ss2.str(string(""));
				ss2 << "Table at address : " << table << "is deleted";
				string temp2 = ss2.str();
				util::Log::Info("UserServiceDAO", temp2);
				return user;
			}
			catch (DBQueryException &dqe)
			{
				util::Log::Error("UserServiceDAOQueryException", dqe.what());
				dbObj = NULL;
				throw DAOQueryException(dqe.what());
			}
			catch (DBDataColumnException &dce)
			{
				util::Log::Error("UserServiceDataColumnException", dce.what());
				dbObj = NULL;
				delete table;
				table = NULL;
				throw DBDataColumnException(dce.what());
			}
			catch (GCException &gce)
			{
				util::Log::Error("UserServiceGCException", gce.what());
				dbObj = NULL;
				throw;
			}
			catch (...)
			{
				util::Log::Error("UserServiceGeneralException", "Unexpected exception");
				dbObj = NULL;
				throw;
			}
		}

		std::vector<entities::User *> UserServiceDAO::getAllUsers()
		{
			db::DataTable *table;
			try
			{
				std::vector<entities::User *> userlist;
				table = dbObj->execQuery("SELECT * FROM GC_USER_TABLE");
				std::vector<db::DataTable::DataRow *> row = table->getRows();
				for (int i = 0; i < row.size(); i++)
				{
					entities::User *user = new entities::User(row[i]->getColumn<std::string, STRING>(2), row[i]->getColumn<std::string, STRING>(1), row[i]->getColumn<std::string, STRING>(3), row[i]->getColumn<std::string, STRING>(4), row[i]->getColumn<std::string, STRING>(5));
					userlist.push_back(user);
					user = NULL;
				}
				delete table;
				table = NULL;
				stringstream ss2;
				ss2.clear();
				ss2.str(string(""));
				ss2 << "Table at address : " << table << "is deleted";
				string temp2 = ss2.str();
				util::Log::Info("UserServiceDAO", temp2);
				return userlist;
			}
			catch (DBQueryException &dqe)
			{
				util::Log::Error("UserServiceDAOQueryException", dqe.what());
				dbObj = NULL;
				throw DAOQueryException(dqe.what());
			}
			catch (DBDataColumnException &dce)
			{
				util::Log::Error("UserServiceDataColumnException", dce.what());
				dbObj = NULL;
				delete table;
				table = NULL;
				throw DBDataColumnException(dce.what());
			}
			catch (GCException &gce)
			{
				util::Log::Error("UserServiceGCException", gce.what());
				dbObj = NULL;
				throw;
			}
			catch (...)
			{
				util::Log::Error("UserServiceGeneralException", "Unexpected exception");
				dbObj = NULL;
				throw;
			}
		}

		std::pair<std::string, std::string> UserServiceDAO::login(std::string email)
		{
			db::DataTable *table;
			try
			{
				std::stringstream ss;
				ss.clear();
				ss.str(string(""));
				ss << "SELECT hash,salt FROM GC_USER_TABLE WHERE EMAIL = '" << email << "'";
				const string &temp = ss.str();
				table = dbObj->execQuery(temp);
				std::vector<db::DataTable::DataRow *> row = table->getRows();
				//entities::User *user =  new entities::User(row[0]->getColumn<std::string,STRING>(3),row[0]->getColumn<std::string,STRING>(2),row[0]->getColumn<std::string,STRING>(4),row[0]->getColumn<std::string,STRING>(5),row[0]->getColumn<std::string,STRING>(6));
				std::pair<std::string, std::string> Hash_Salt = std::make_pair(row[0]->getColumn<std::string, STRING>(0), row[0]->getColumn<std::string, STRING>(1));
				delete table;
				table = NULL;
				stringstream ss2;
				ss2.clear();
				ss2.str(string(""));
				ss2 << "Table at address : " << table << "is deleted";
				string temp2 = ss2.str();
				util::Log::Info("UserServiceDAO", temp2);
				return Hash_Salt;
			}
			catch (DBQueryException &dqe)
			{
				util::Log::Error("UserServiceDAOQueryException", dqe.what());
				dbObj = NULL;
				throw DAOQueryException(dqe.what());
			}
			catch (DBDataColumnException &dce)
			{
				util::Log::Error("UserServiceDataColumnException", dce.what());
				dbObj = NULL;
				delete table;
				table = NULL;
				throw DBDataColumnException(dce.what());
			}
			catch (GCException &gce)
			{
				util::Log::Error("UserServiceGCException", gce.what());
				dbObj = NULL;
				throw;
			}
			catch (...)
			{
				util::Log::Error("UserServiceGeneralException", "Unexpected exception");
				dbObj = NULL;
				throw;
			}
		}
		// std::vector<entities::User*> UserServiceDAO::getBuddies(std::string email)
		// {
		// }

		void UserServiceDAO::blockconnection(std::string email1, std::string email2)
		{
			try
			{
				std::stringstream ss;
				ss.clear();
				ss.str(string(""));
				ss << "call sp_blockUser('" << email1 << "','" << email2 << "')";
				const string &temp = ss.str();
				dbObj->execNonQuery(temp);
				//delete user;

				//user = NULL;
				//stringstream ss2;
				// ss2.clear();
				// ss2.str(string(""));
				// ss2<<"User at address : "<<user<<"is deleted";
				// string temp2 = ss2.str();
				// util::Log::Info("UserServiceDAO",temp2);
			}
			catch (DBQueryException &dqe)
			{
				util::Log::Error("UserServiceDAOQueryException", dqe.what());
				dbObj = NULL;
				// delete user;
				// user=NULL;
				throw DAOQueryException(dqe.what());
			}
			catch (GCException &gce)
			{
				util::Log::Error("UserServiceGCException", gce.what());
				dbObj = NULL;
				throw;
			}
			catch (...)
			{
				util::Log::Error("UserServiceGeneralException", "Unexpected exception");
				dbObj = NULL;
				throw;
			}
		}

		void UserServiceDAO::unblockconnection(std::string email1, std::string email2)
		{
			try
			{
				std::stringstream ss;
				ss.clear();
				ss.str(string(""));
				ss << "call sp_unblockUser('" << email1 << "','" << email2 << "')";
				const string &temp = ss.str();
				dbObj->execNonQuery(temp);
				//delete user;

				// user = NULL;
				// stringstream ss2;
				// ss2.clear();
				// ss2.str(string(""));
				// ss2<<"User at address : "<<user<<"is deleted";
				// string temp2 = ss2.str();
				// util::Log::Info("UserServiceDAO",temp2);
			}
			catch (DBQueryException &dqe)
			{
				util::Log::Error("UserServiceDAOQueryException", dqe.what());
				dbObj = NULL;
				// delete user;
				// user=NULL;
				throw DAOQueryException(dqe.what());
			}
			catch (GCException &gce)
			{
				util::Log::Error("UserServiceGCException", gce.what());
				dbObj = NULL;
				throw;
			}
			catch (...)
			{
				util::Log::Error("UserServiceGeneralException", "Unexpected exception");
				dbObj = NULL;
				throw;
			}
		}

		bool UserServiceDAO::isBlocked(std::string email1, std::string email2)
		{
			db::DataTable *table;
			try
			{
				std::stringstream ss;
				ss.clear();
				ss.str(string(""));
				ss << "SELECT count(*) FROM gc_blocked_table WHERE (blocker, blockee) IN (('" << email1 << "','" << email2 << "'),('" << email2 << "','" << email1 << "'))";
				const string &temp = ss.str();
				table = dbObj->execQuery(temp);
				std::vector<db::DataTable::DataRow *> row = table->getRows();
				bool value;
				if ((row[0]->getColumn<int, INT>(0)) == 1)
					value = true;
				else
					value = false;
				delete table;
				table = NULL;
				stringstream ss2;
				ss2.clear();
				ss2.str(string(""));
				ss2 << "Table at address : " << table << "is deleted";
				string temp2 = ss2.str();
				util::Log::Info("UserServiceDAO", temp2);
				return value;
			}
			catch (DBQueryException &dqe)
			{
				util::Log::Error("UserServiceGeneralException", dqe.what());
				dbObj = NULL;
				throw DBQueryException(dqe.what());
			}
			catch (DBDataColumnException &dce)
			{
				util::Log::Error("UserServiceDataColumnException", dce.what());
				dbObj = NULL;
				delete table;
				table = NULL;
				throw DBDataColumnException(dce.what());
			}
			catch (GCException &gce)
			{
				util::Log::Error("UserServiceGCException", gce.what());
				dbObj = NULL;
				throw;
			}
			catch (...)
			{
				util::Log::Error("UserServiceGeneralException", "Unexpected exception");
				dbObj = NULL;
				throw;
			}
		}

		// void UserServiceDAO::mapconnection(std::string email1,std::string email2)
		// {
		// }

		// void UserServiceDAO::unmapconnection(std::string email1,std::string email2)
		// {
		// }

		UserServiceDAO::~UserServiceDAO()
		{
			dbObj = NULL;
			util::Log::Info("UserServiceDAO", "dbObj turned to NULL");
		}

	} // namespace dao
} // namespace gc
