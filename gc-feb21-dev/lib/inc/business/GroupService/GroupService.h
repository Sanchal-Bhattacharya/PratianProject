/**
* @File : GroupService.h
* @Author : Gurpreet Singh
* @Brief : This is the class file for various user management operations with database
* 
* This file contains the declaration for The UserService Class
* which is implemented by interface to carry on various user management tasks by interacting with database
*  it is class which is implemented by the interface.
*/

#pragma once
#include <string>
#include "IGroupService.h"

using namespace std;

namespace gc
{
	namespace business
	{
		class GroupService : public IGroupService
		{
		public:
			GroupService();
			~GroupService();

			/**
			 * Used to establish connection to the database and performing a create operation for a group into the system.
			*/
			void createGroup(entities::Group *);

			/**
			 * Used to establish connection to the database and perform a delete operation for a user into the system
			*/
			void deleteGroup(std::string GroupName);

			/**
			* Used to establish connection to the database and perform an update operation for a group in the system. 
			*/
			void updateGroup(std::string oldName, std::string newName);

			/**
			* Used to establish connection to the database and performing a add operation for a user into the group. 
			*/
			void addMember(string groupName, string email);

			/**
			* Used to establish connection to the database and remove the user from the group. 
			*/
			void removeMember(string groupName, string email);

			/**
			* Used to establish connection to the database and fetch the user emails for all group members. 
			*/
			std::vector<std::string> getUsers(std::string groupName);

			/**
			* Used to establish connection to the database and fetch all the groups in the system. 
			*/
			std::vector<std ::string> getAllGroups();
		};
	} // namespace business
} // namespace gc
