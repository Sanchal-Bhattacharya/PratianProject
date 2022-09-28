#include <iostream>
#include <string>

#include "DAOManager.h"
#include "User.h"
#include "ConnectionIdNotFound.h"
#include "Log.h"
#include "DAOQueryException.h"

#include "GroupConnectionCache.h"


using namespace std;

namespace gc
{
	namespace business
	{
		GroupConnectionCache *GroupConnectionCache::groupConnectionCache = nullptr;
		long int GroupConnectionCache::cId = 0;

		GroupConnectionCache::GroupConnectionCache()
		{
			util::Log::Info("GroupConnectionCache Constructor ", "Setting up the group connection cache");
			dao::IGroupServiceDAO *gs = dao::DAOManager::getGroupServiceDAO();
			try
			{
				util::Log::Info("GroupConnectionCache Constructor", " Calling get all groups");
				vector<string> groups = gs->getAllGroups();
				for (int i = 0; i < groups.size(); i++)
				{
					util::Log::Info("GroupConnectionCache Constructor", "Calling get all users");
					vector<string> users = gs->getAllUsers(groups[i]);
					for (int j = 0; j < users.size(); j++)
					{
						groupList.push_back(groups[i]);
						userList.push_back(users[j]);
						qId.push_back(cId);
						cId++;
					}
				}
				util::Log::Info("GroupConnectionCache Constructor", "GroupConnectionCache setup complete");
				delete gs;
				gs = nullptr;
			}
			catch (dao::DAOQueryException &dqe)
			{
				util::Log::Info("GroupConnectionCache Constructor", " Group Table is empty so the DAOQuerryException was thrown");
				delete gs;
				gs = nullptr;
				util::Log::Info("GroupConnectionCache Constructor", "GroupConnectionCache set up complete, no groups exists");
				return;
			}
		}

		void GroupConnectionCache::addNewGroupToList(std::string groupName)
		{
			int flag = 1;
			for (int i = 0; i < groupList.size(); i++)
			{
				if ((groupName == groupList[i]))
				{
					flag = 0;
					util::Log::Info("GroupConnectionCache addNewGroupToList", "Group already exists");
					break;
				}
			}
			if (flag == 1)
			{
				dao::IGroupServiceDAO *gs = dao::DAOManager::getGroupServiceDAO();
				try
				{
					vector<string> users = gs->getAllUsers(groupName);
					mtx_1.lock();
					for (int i = 0; i < users.size(); i++)
					{
						groupList.push_back(groupName);
						userList.push_back(users[i]);
						qId.push_back(cId);
						cId++;
					}
					mtx_1.unlock();
					util::Log::Info("GroupConnectionCache addNewGroupToList", "New group added to the connection cache");
					delete gs;
					gs = nullptr;
				}
				catch (dao::DAOQueryException &dqe)
				{
					util::Log::Error("GroupConnectionCache addNewGroupToList", "No users exist for this group");
					delete gs;
					gs = nullptr;
				}
			}
		}

		GroupConnectionCache *GroupConnectionCache::getGroupConnectionCacheInstance()
		{
			if (groupConnectionCache == nullptr)
			{
				groupConnectionCache = new GroupConnectionCache();
			}
			return groupConnectionCache;
		}

		unsigned int GroupConnectionCache::getConnectionId(string groupName, string email)
		{
			int conId = -1;
			mtx_1.lock();
			for (int i = 0; i < groupList.size(); i++)
			{
				if ((groupList[i] == groupName && userList[i] == email))
				{
					conId = qId[i];
					break;
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

		vector<unsigned int> GroupConnectionCache::getConnectionIdList(string email)
		{
			vector<unsigned int> conId;
			mtx_1.lock();
			for (int i = 0; i < userList.size(); i++)
			{
				if (userList[i] == email)
				{
					conId.push_back(qId[i]);
				}
			}
			mtx_1.unlock();
			return conId;
		}

		void GroupConnectionCache::addNewUserToList(string groupName, string email)
		{
			mtx_1.lock();
			groupList.push_back(groupName);
			userList.push_back(email);
			qId.push_back(cId);
			cId++;
			mtx_1.unlock();
		}

		void GroupConnectionCache::removeUserFromList(string groupName, string email)
		{
			for (int i = 0; i < groupList.size(); i++)
			{
				if ((groupList[i] == groupName && userList[i] == email))
				{
					mtx_1.lock();
					groupList.erase(groupList.begin() + i);
					userList.erase(userList.begin() + i);
					qId.erase(qId.begin() + i);
					mtx_1.unlock();
					break;
				}
			}
		}

		void GroupConnectionCache::deleteGroupFromCache(string groupName)
		{
			for (int i = 0; i < groupList.size(); i++)
			{
				if (groupList[i] == groupName)
				{
					mtx_1.lock();
					groupList.erase(groupList.begin() + i);
					userList.erase(userList.begin() + i);
					qId.erase(qId.begin() + i);
					mtx_1.unlock();
				}
			}
		}

		void GroupConnectionCache::updateGroupInCache(string oldName, string newName)
		{
			replace(groupList.begin(), groupList.end(), oldName, newName);
		}

		GroupConnectionCache::~GroupConnectionCache()
		{
			groupConnectionCache = nullptr;
		}
	} // namespace business
} // namespace gc
