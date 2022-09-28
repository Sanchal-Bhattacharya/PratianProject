#pragma once

#include "IConnectionObserver.h"
#include "GroupConnectionCache.h"
#include "ConnectionCache.h"

namespace gc
{
	namespace business
	{
		class ConnectionObserver : public IConnectionObserver
		{
			static ConnectionObserver *observer;
			ConnectionObserver();

		public:
			/**
			 * Return a pointer to the instance of Connection Observer
			*/
			static ConnectionObserver *getObserverInstance();

			/**
			 * Add the newly created user to the Connection Cache
			*/
			void notify(entities::User *user);

			/**
			 * It deletes all the connections for the user from the cache when the user has been deleted.
			*/
			void userDeleted(std::string email);

			/**
			 * It removes the connection between 2 users when the connection has to be blocked.
			*/
			void onBlock(std::string user1, std::string user2);

			/**
			 * It adds the connection between 2 users when the connection has to be unblocked.
			*/
			void onUnblock(std::string user1, std::string user2);

			/**
			 * Add the newly created group to the Group Connection Cache
			*/
			void newGroup(entities::Group *group);

			/**
			 * Update the group in the Group Connection Cache
			*/
			void updateGroup(std::string oldName, std::string newName);

			/**
			 * Deletes the connections of the group from the group connection cache
			*/
			void deleteGroup(std::string groupName);

			/**
			 * It creates a connection between the group and the user from the group connection cache
			*/
			void newMember(std::string groupName, std::string email);

			/**
			 * It removes the connection between the group and the user from the group connection cache
			*/
			void removeMember(std::string groupName, std::string email);

			/**
             * Destructor for the connection observer
            */
			~ConnectionObserver();
		};

	} // namespace business
} // namespace gc
