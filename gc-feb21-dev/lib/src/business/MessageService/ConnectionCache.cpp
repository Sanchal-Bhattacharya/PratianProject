#include <string>
#include <iostream>

#include "ConnectionCache.h"
#include "DAOQueryException.h"
#include "User.h"
#include "DAOManager.h"
#include "ConnectionIdNotFound.h"
#include "Log.h"

using namespace std;

namespace gc
{
	namespace business
	{
		ConnectionCache *ConnectionCache::connectionCache = nullptr;
		int ConnectionCache::cId = 0;

		ConnectionCache::ConnectionCache()
		{
			util::Log::Info("Connection Cache Constructor", "Setting up Connection Cache");
			dao::IMessageServiceDAO *us = dao::DAOManager::getMessageServiceDAO();
			dao::IUserServiceDAO *userService = dao::DAOManager::getUserServiceDAO();
			util::Log::Info("Connection Cache Constructor", "Calling MessageServiceDAO::getAllUsers");

			try
			{
				vector<string> user = us->getAllUsers();
				for (int i = 0; i < user.size(); i++)
				{
					for (int j = i + 1; j < user.size(); j++)
					{
						util::Log::Info("Connection Cache Constructor", "Calling MessageServiceDAO::isBlocked");
						if (userService->isBlocked(user[i], user[j]))
						{
							util::Log::Info("Connection Cache Constructor", "Connection Blocked between " + user[i] + "," + user[j]);
							continue;
						}
						ulist1.push_back(user[i]);
						ulist2.push_back(user[j]);
						qId.push_back(cId);
						cId++;
					}
				}
				util::Log::Info("ConnectionCache Constructor", "ConnectionCache setup complete");
				delete userService;
				delete us;
				us = nullptr;
			}
			/*for(int i=0; i < ulist1.size() ; i++)
			{
				cout<<ulist1[i]<<"\t"<<ulist2[i]<<"\t"<<qId[i]<<endl;
			}*/
			catch (dao::DAOQueryException &dqe)
			{
				util::Log::Info("ConnectionCache Constructor", " User Table is empty so the DAOQuerryException was thrown");
				delete userService;
				delete us;
				us = nullptr;
				util::Log::Info("ConnectionCache Constructor", "ConnectionCache set up complete, no users exists");
				return;
			}
		}

		void ConnectionCache::addNewUserToList(entities::User *user)
		{
			int flag = 1;

			for (int i = 0; i < ulist1.size(); i++)
			{
				if ((user->getEmail() == ulist1[i]) || (user->getEmail() == ulist2[i]))
				{
					flag = 0;
					break;
				}
			}
			if (flag == 1)
			{
				dao::IMessageServiceDAO *us = dao::DAOManager::getMessageServiceDAO();
				vector<string> users = us->getAllUsers();
				util::Log::Info("ConnectionCache", "New user added to the connection cache ");
				mtx_1.lock();
				for (int i = 0; i < users.size(); i++)
				{
					if (users[i] != user->getEmail())
					{
						ulist1.push_back(user->getEmail());
						ulist2.push_back(users[i]);
						qId.push_back(cId);
						cId++;
					}
				}
				mtx_1.unlock();
				delete us;
				us = NULL;
			}
		}

		void ConnectionCache::deleteUserFromList(string email)
		{
			for (int i = 0; i < ulist1.size(); i++)
			{
				if (ulist1[i] == email || ulist2[i] == email)
				{
					mtx_1.lock();
					ulist1.erase(ulist1.begin() + i);
					ulist2.erase(ulist2.begin() + i);
					qId.erase(qId.begin() + i);
					mtx_1.unlock();
				}
			}
		}

		ConnectionCache *ConnectionCache::getConnectionCacheInstance()
		{
			if (connectionCache == nullptr)
			{
				connectionCache = new ConnectionCache();
			}
			return connectionCache;
		}

		unsigned int ConnectionCache::getConnectionId(string user1, string user2)
		{
			int conId = -1;

			mtx_1.lock();
			for (int i = 0; i < ulist1.size(); i++)
			{
				if ((ulist1[i] == user1 && ulist2[i] == user2) ||
					(ulist1[i] == user2 && ulist2[i] == user1))
				{
					conId = qId[i];
				}
			}
			mtx_1.unlock();

			if (conId >= 0)
			{
				return conId;
			}
			else
			{
				throw ConnectionIdNotFound("::INVALID CONNECTION ID:: Requested Connection not found ");
			}
		}

		vector<unsigned int> ConnectionCache::getConnectionIdList(string id)
		{
			vector<unsigned int> conId;

			mtx_1.lock();
			for (int i = 0; i < ulist1.size(); i++)
			{
				if (ulist1[i] == id || ulist2[i] == id)
				{
					conId.push_back(qId[i]);
				}
			}
			mtx_1.unlock();

			return conId;
		}

		void ConnectionCache::addUserConnection(string user1, string user2)
		{
			mtx_1.lock();
			ulist1.push_back(user1);
			ulist2.push_back(user2);
			qId.push_back(cId);
			cId++;
			mtx_1.unlock();
		}

		void ConnectionCache::removeUserConnection(string user1, string user2)
		{

			for (int i = 0; i < ulist1.size(); i++)
			{
				if ((ulist1[i] == user1 && ulist2[i] == user2) || (ulist1[i] == user2 && ulist2[i] == user1))
				{
					mtx_1.lock();
					ulist1.erase(ulist1.begin() + i);
					ulist2.erase(ulist2.begin() + i);
					qId.erase(qId.begin() + i);
					mtx_1.unlock();
					break;
				}
			}
		}
		ConnectionCache::~ConnectionCache()
		{
			connectionCache = nullptr;
		}

	} // namespace business
} // namespace gc
