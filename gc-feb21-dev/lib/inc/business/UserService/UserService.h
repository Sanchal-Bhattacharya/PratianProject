/**
* @File : UserService.h
* @Author : Gurpreet Singh
* @Brief : This is the class file for various user management operations with database
* 
* This file contains the declaration for The UserService Class
* which is implemented by interface to carry on various user management tasks by interacting with database
*  it is class which is implemented by the interface.
*/

#pragma once
#include "IUserService.h"

namespace gc
{
	namespace business
	{
		class UserService : public IUserService
		{
		public:
			UserService();
			~UserService();

			/**
			* Used to establish connection to the database and performing a create operation for a user into the system. 
			*/
			void createUser(entities::User *user);

			/**
			* Used to establish connection to the database and create a list of users into the system. 
			*/
			void createUserFromList(std::vector<entities::User *> userlist);

			/**
			* Used to establish connection to the database and perform an update operation for a user in the system. 
			*/
			void updateUser(entities::User *user);

			/**
			* Used to establish connection to the database and perform a delete operation for a user into the system. 
			*/
			void deleteUser(std::string email);

			/**
			* Used to establish connection to the database and perform a fetch details for a user in the system based on his/her email id. 
			*/
			entities::User *getUser(std::string email);

			/**
			* Used to establish connection to the database and performing a fetch for all users in the system. 
			*/
			std::vector<entities::User *> getAllUsers();

			/**
            * Used to establish a connection block between 2 users
            */
			void blockConnection(std::string email1, std::string email2);

			/**
            * Used to remove the connection block between the 2 users
            */
			void unblockConnection(std::string email1, std::string email2);

			/**
            * Used to check if the connection between the 2 users is blocked.
            */
			bool isBlocked(std::string email1, std::string email2);

			/**
            * Used to login to the application and perform the operations as expected by the user of a system.
            */
			std::pair<std::string, std::string> login(std::string email);
		};
	} // namespace business
} // namespace gc
