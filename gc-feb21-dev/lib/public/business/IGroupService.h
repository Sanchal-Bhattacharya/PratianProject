/**
* @File : IGroupService.h
* @Author : Gurpreet Singh
* @Breif : This is the Inteface file for various user management operations with database
* 
* This file contains the declaration for The IUserService Class
* which is implemented by web service to carry on various user management tasks by interacting with database
*  it is an interface which is implemented by the web Classes.
*/

#pragma once
#include <string>
#include <vector>
#include "Group.h"

namespace gc
{
	namespace business
	{
		struct IGroupService
		{
			/** 
			 * @param: It accepts as param a pointer to group object
             * @brief: Used to establish connection to the database and performing a create operation for a group into the system.
             * @return: It returns void
			*/
			virtual void createGroup(entities::Group *group) = 0;

			/**
			 * @param: It accepts as param GroupName of the Group
             * @brief: Used to establish connection to the database and perform a delete operation for a user into the system
             * @return: It returns void
            */
			virtual void deleteGroup(std::string GroupName) = 0;

			/**
			* @param: 2 stri	ngs containing the old and the new group names.
			* @return: It returns void.
			* @breif:Used to establish connection to the database and perform an update operation for the group in the system. 
			*/
			virtual void updateGroup(std::string oldName, std::string newName) = 0;

			/**
			* @param:it accepts as param a groupName and a email of a user
			* @breif:Used to establish connection to the database and add user to the group. 
			* @return: It returns void
			*/
			virtual void addMember(std::string groupName, std::string email) = 0;

			/**
			* @param: it accepts as param a groupName & a email of a user.
			* @return: It returns void
			* @breif:Used to establish connection to the database and remove the user from the group. 
			*/
			virtual void removeMember(std::string groupName, std::string email) = 0;

			/**
			* @param:it accepts as param name of the group
			* @return: it returns a vector containing email ids of all users in the group
			* @breif:Used to establish connection to the database and fetch all the users' email ids in the group. 
			*/
			virtual std::vector<std::string> getUsers(std::string groupName) = 0;

			/**
            * @return:It returns a vector of group pointers
            * @breif:Used to establish connection to the database and perform a fetch details for all groups in the system. 
            */
			virtual std::vector<std ::string> getAllGroups() = 0;

			virtual ~IGroupService();
		};
	} // namespace business
} // namespace gc
