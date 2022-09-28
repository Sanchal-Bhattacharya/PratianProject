#pragma once
#include <string>
#include <vector>

#include "User.h"

/**
* @File : IUserServiceDAO
* @Author : Anurag Gupta
* @Brief : Its is an interface through which User Services and the methods to use the DAO for DB related operations are    
* provided to the user.It is used for managing User information in the databases.
*/
namespace gc
{
	namespace dao
	{
		struct IUserServiceDAO
		{
			/** @Brief :Used to create a new user profile and store the user information in the DB 
			* @param : User pointer which is to be created
			* @return : void
			*/
			virtual void createUser(entities::User *user) = 0;
			/** @Brief : Used to create new users profiles from a list sent from the business layer and store the user 				* information in the DB
			* @param : A vector of Users which are to created 
			* @return : void
 			*/
			virtual void createUserFromList(std::vector<entities::User *> userlist) = 0;
			/** @Brief : Used to update user froam an email
			* @param : User pointer which is to be updated
			* @return : void
 			*/
			virtual void updateUser(entities::User *user) = 0;
			/** @Brief : Used to update user froam an email
			* @param : User pointer which is to be updated
			* @return : void
 			*/
			virtual void deleteUser(std::string email) = 0;
			/** @Brief : Used to get user from email
			* @param : email of the user
			* @return : User pointer
 			*/
			virtual entities::User *getUser(std::string email) = 0;
			/** @Brief : Used to get all the users from email
			* @param : No parameters
			* @return : Vector of all the users pointers
 			*/
			virtual std::pair<std::string, std::string> login(std::string email) = 0;
			/** @Brief : Used to return hash and salt of user
             ** @param : string parameter containing email id
             * @return : Pair of hash and salt of user
             **/
			virtual std::vector<entities::User *> getAllUsers() = 0;
			//virtual std::vector<entities::User*> getBuddies(std::string email)=0;
			virtual void blockconnection(std::string email1, std::string email2) = 0;
			
			virtual void unblockconnection(std::string email1, std::string email2) = 0;
			//virtual void mapconnection(std::string email1,std::string email2)=0;
			//virtual void unmapconnection(std::string email1,std::string email2)=0;
			/** @Brief : Used to disconnect from the DB
 			*/
			virtual bool isBlocked(std::string email1, std::string email2) = 0;
			virtual ~IUserServiceDAO();
		};
	} // namespace dao
} // namespace gc
