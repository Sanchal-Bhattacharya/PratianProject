#pragma once
#include <string>
#include <vector>

#include "Group.h"

using namespace std;

/**
* @File : IGroupServiceDAO
* @Author : Awinash Kumar Singh
* @Brief : It is an interface through which Group Services and the methods to use the DAO for DB related operations are    
* provided to the user.It is used for managing Group information in the databases.
*/
namespace gc
{
	namespace dao
	{
		struct IGroupServiceDAO
		{
			/** @Brief :Used to create a new GROUP profile and store the group information in the DB 
			* @param : group pointer which is to be created
			* @return : void
			*/
			virtual void createGroup(entities::Group *group) = 0;
			/** @Brief : Used to create add members to  group sent from the business layer and store the information in the DB
			* @param : A groupname and email of user
			* @return : void
 			*/
			virtual void addMember(string GroupName, string email) = 0;
			/** @Brief : Used to update group from groupname
			* @param : groupname and newgroupname
			* @return : void
 			*/
			virtual void updateGroup(string OldGroupName, string NewGroupName) = 0;
			/** @Brief : Used to delete group from db
			* @param : groupname which is to be deleted
			* @return : void
 			*/
			virtual void deleteGroup(string GroupName) = 0;
			/** @Brief : Used to get all users of the group
			* @param : groupname
			* @return : User pointer
 			*/
			virtual std::vector<string> getAllUsers(string GroupName) = 0;
			/** @Brief : Used to remove users from group
			* @param : No parameters
			* @return : Vector of all the users pointers
            */
			virtual void removeUser(string GroupName, string email) = 0;
			/** @Brief : Used to get names of all existing groups
			* @param : No parameters
			* @return : String vector of groupnames
			*/
			virtual std::vector<std::string> getAllGroups() = 0;
			/** @Brief : Used to disconnect from the DB
 			*/
			virtual ~IGroupServiceDAO();
		};
	} // namespace dao
} // namespace gc
