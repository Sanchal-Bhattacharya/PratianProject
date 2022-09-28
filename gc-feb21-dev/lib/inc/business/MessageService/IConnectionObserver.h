#pragma once
#include "Group.h"
#include "User.h"

namespace gc
{
	namespace business
	{
		struct IConnectionObserver
		{
			/**
			 * @param: A pointer to the user object
			 * @brief: Add the newly created user to the Connection Cache
			 * @return: It returns void
			*/
			virtual void notify(entities::User *user) = 0;

			/**
			 * @param: The email of the user
			 * @brief: It deletes all the connections for the user from the cache
			 * @return: It returns void
			*/

			virtual void userDeleted(std::string email) = 0;

			/**
			 * @param: The email ids of the 2 users.
			 * @brief: It removes the connection between 2 users when the connection has to be blocked.
			 * @return: It returns void
			*/
			virtual void onBlock(std::string user1, std::string user2) = 0;

			/**
			 * @param: The email ids of the 2 users.
			 * @brief: It adds the connection between 2 users when the connection has to be unblocked.
			 * @return: It returns void
			*/
			virtual void onUnblock(std::string user1, std::string user2) = 0;

			/**
			 * @param: A pointer to the group object
			 * @brief: Add the newly created group to the Group Connection Cache
			 * @return: It returns void
			*/

			virtual void newGroup(entities::Group *group) = 0;

			/**
			 * @param: The old group name and the updated group name
			 * @brief: Update the group in the Group Connection Cache
			 * @return: It returns void
			*/
			virtual void updateGroup(std::string oldName, std::string newName) = 0;

			/**
			 * @param: The name of the group
			 * @brief: Deletes the connections of the group from the group connection cache
			 * @return: It returns void
			*/
			virtual void deleteGroup(std::string groupName) = 0;

			/**
			 * @param: The group name and the email of the user
			 * @brief: It creates a connection between the group and the user from the group connection cache
			 * @return: It returns void
			*/
			virtual void newMember(std::string groupName, std::string email) = 0;

			/**
			 * @param: The group name and the email of the user
			 * @brief: It removes the connection between the group and the user from the group connection cache
			 * @return: It returns void
			*/
			virtual void removeMember(std::string groupName, std::string email) = 0;
			virtual ~IConnectionObserver();
		};

	} // namespace business
} // namespace gc
