#pragma once

#include <vector>
#include <string>
#include <mutex>

#include "User.h"

using namespace std;

namespace gc
{
	namespace business
	{
		class ConnectionCache
		{
			vector<string> ulist1;
			vector<string> ulist2;
			vector<unsigned int> qId;
			static int cId;
			ConnectionCache();
			std::mutex mtx_1;
			static ConnectionCache* connectionCache;
		public:
			void addNewUserToList(entities::User *user);
			void deleteUserFromList(string email);
			static ConnectionCache* getConnectionCacheInstance();
			unsigned int getConnectionId(string user1, string user2);// do not change unsigned int(throws exception if connection not)
			vector<unsigned int> getConnectionIdList(string id);			
			void addUserConnection(string user1, string user2);
			void removeUserConnection(string user1, string user2);
            ~ConnectionCache();
		};
	}
}
