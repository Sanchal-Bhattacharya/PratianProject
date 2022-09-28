#pragma once

#include <sstream>
#include <string>

#include "IGroupServiceDAO.h"

/** @File : GroupServiceDAO
*   @Author : Arushi Tandon
*   @Brief : It is a class through which DB related operations are implemented and provided to the business layer through *IGroupService.   
*   It is used by both GroupServices and MessageServices of the business layer.	
*/

namespace gc
{
	namespace dao
	{
		class GroupServiceDAO : public IGroupServiceDAO
		{
			db::IDBConnect *dbObj;
			public:
			/**
			* @Brief : Used to establish connection to the database by the class implementing this interface. 
			*/
			GroupServiceDAO();
			/** @Brief : Used to disconnect from the DB
 			*/
			~GroupServiceDAO();
			/** @Brief :Used to create a new GROUP profile and store the group information in the DB 
			* @param : group pointer which is to be created
			* @return : void
			*/	
			void createGroup(entities::Group *group);
			/** @Brief : Used to add a member to  group sent from the business layer and store the information in the DB
			* @param : A groupname and email of user
			* @return : void
 			*/
			void addMember(string GroupName,string email);
			/** @Brief : Used to update name of a group
			* @param : oldgroupname and newgroupname
			* @return : void
 			*/
			void updateGroup(string OldGroupName,string NewGroupName);
			/** @Brief : Used to delete group from db
			* @param : groupname which is to be deleted
			* @return : void
 			*/
			void deleteGroup(string GroupName);
			/** @Brief : Used to get all users of the group
			* @param : groupname
			* @return : User pointer
 			*/
			std::vector<std::string> getAllUsers(string GroupName);
			/** @Brief : Used to remove users from group
			* @param : groupname, email of user
			* @return : Vector of all the users pointers
            */
			void removeUser(string GroupName,string email);
			/** @Brief : Used to get names of all existing groups
			* @param : No parameters
			* @return : String vector of groupnames
			*/
			std::vector<std::string> getAllGroups();

		};
	}
}
