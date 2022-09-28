/**
* @File : IUserService.h
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
#include "User.h"
namespace gc
{
	namespace business
	{
		struct IUserService
		{
			/**
			* @param:it accepts as param a pointer to user object
			* @breif:Used to establish connection to the database and performing a create operation for a user into the system. 
			* @return: It returns void
			*/
			virtual void createUser(entities::User *user) = 0;

			/**
			* @param:it accepts as param a pointer to user object
			* @breif:Used to establish connection to the database and create a list of users into the system. 
			* @return: It returns void
			*/
			virtual void createUserFromList(std::vector<entities::User *> userlist) = 0;

			/**
			* @param: a pointer vector of user objects
			* @return: It returns void
			* @breif:Used to establish connection to the database and perform an update operation for a user in the system. 
			*/
			virtual void updateUser(entities::User *user) = 0;

			/**
			* @param: it accepts as param a pointer to user object
			* @return: It returns void
			* @breif:Used to establish connection to the database and perform a delete operation for a user into the system. 
			*/
			virtual void deleteUser(std::string email) = 0;

			/**
			* @param:It accepts as param emailid of the user
			* @return: It returns void
			* @breif:Used to establish connection to the database and perform a fetch details for a user in the system based on his/her email id. 
			*/
			virtual entities::User *getUser(std::string email) = 0;

			/**
			* @param:it accepts as param emailid of the user
			* @return:It returns user pointer
			* @breif:Used to establish connection to the database and perform a fetch details for a user in the system based on his/her email id. 
			*/
			virtual std::vector<entities::User *> getAllUsers() = 0;

			/**
			* @param:it accepts as param a string containing the email of the user
			* @return: a pair containing the hash and the salt for the user
            * @brief:Used to fetch the stored salt and hash of the password for the user
			*/
			virtual std::pair<std::string, std::string> login(std::string email) = 0;

			/**
            * @param:it accepts as param 2 strings containing the emails of the blocker and the blockee
            * @return: it returns void
            * @brief: Used to establish a connection block between the 2 users.
            */
			virtual void blockConnection(std::string email1, std::string email2) = 0;

			/**
            * @param: it accepts as param 2 strings conatining the emails of the blocker and the blockee
            * @return: it returns void
            * @breif: Used to remove the connection block between the 2 users.
            */
			virtual void unblockConnection(std::string email1, std::string email2) = 0;

			/**
            * @param: it accepts as param 2 strings conataining the emails of 2 users.
            * @return: it returns true if the connection is blocked else return false.
            * @brief: it checks if the connection between the 2 users is blocked.
            */
			virtual bool isBlocked(std::string email1, std::string email2) = 0;
			virtual ~IUserService();
		};
	} // namespace business
} // namespace gc
