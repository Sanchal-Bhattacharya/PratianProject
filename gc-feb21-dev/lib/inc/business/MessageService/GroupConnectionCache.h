#pragma once

#include <vector>
#include <string>
#include <boost/thread/mutex.hpp>

using namespace std;

namespace gc
{
	namespace business
	{
		class GroupConnectionCache
		{
			vector<string> groupList;
			vector<string> userList;
			vector<unsigned int> qId;
			static long int cId;
			GroupConnectionCache();
			boost::mutex mtx_1;
			static GroupConnectionCache *groupConnectionCache;

		public:
			/**
			 * Add a newly created group to the connection cache
			*/
			void addNewGroupToList(string groupName);

			/**
			 * Add a connection between the group and user
			*/
			void addNewUserToList(string groupName, string email);

			/** 
			 * Remove the connection between the group and user
			*/
			void removeUserFromList(string groupName, string email);

			/**
			 * Get a pointer to the instance of the group cache instance
			*/
			static GroupConnectionCache *getGroupConnectionCacheInstance();

			/**
			 * Get the conncetion Id of a group and user
			*/
			unsigned int getConnectionId(string groupName, string email); // do not change unsigned int(throws exception if connection not)

			/**
			 * Get all the connection ids for the groups a user is in
			*/
			vector<unsigned int> getConnectionIdList(string email);

			/**
			 * Delete the group from the cache
			*/
			void deleteGroupFromCache(string groupName);

			/**
			 * Update the group in the cache
			*/
			void updateGroupInCache(string oldName, string newName);

			/**
             * Destructor for the group connection cache
            */
			~GroupConnectionCache();
		};
	} // namespace business
} // namespace gc
