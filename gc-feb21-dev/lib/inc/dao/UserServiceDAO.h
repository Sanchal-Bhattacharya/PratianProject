#pragma once
#include <sstream>
#include <string>

#include "IUserServiceDAO.h"
#include "IDBConnect.h"

/** @File : UserServiceDAO
*   @Author : Anurag Gupta
*   @Brief : It is an class through which  DB related operations are implemented and provided to the business layer through     *IUserService.   
*   It is used by both UserServices and MessageServices of the business layer.	
*/
namespace gc
{
	namespace dao
	{
		class UserServiceDAO : public IUserServiceDAO
		{
			db::IDBConnect *dbObj;

		public:
			/**
			* @Brief : Used to establish connection to the database by the class implementing this interface. 
			*/
			UserServiceDAO();
			/** @Brief : Used to disconnect from the DB
 			*/
			~UserServiceDAO();
			/** @Brief :Used to create a new user profile and store the user information in the DB 
			* @param : User pointer which is to be created
			* @return : void
			*/
			void createUser(entities::User *user);
			/** @Brief : Used to create new users profiles from a list sent from the business layer and store the user 				* information in the DB
			* @param : A vector of Users which are to created 
			* @return : void
 			*/
			void createUserFromList(std::vector<entities::User *> userlist);
			/** @Brief : Used to update user froam an email
			* @param : User pointer which is to be updated
			* @return : void
 			*/
			void updateUser(entities::User *user);
			/** @Brief : Used to update user froam an email
			* @param : User pointer which is to be updated
			* @return : void
 			*/
			void deleteUser(std::string email);
			/** @Brief : Used to get user from email
			* @param : email of the user
			* @return : User pointer
 			*/
			entities::User *getUser(std::string email);
			/** @Brief : Used to get all the users from email
			* @param : No parameters
			* @return : Vector of all the users pointers
 			*/
			std::pair<std::string, std::string> login(std::string email);
			/** @Brief : Used to return hash and salt of user
             ** @param : string parameter containing email id
             * @return : Pair of hash and salt of user
             **/

			std::vector<entities::User *> getAllUsers();
			//std::vector<entities::User*> getBuddies(std::string email);
			void blockconnection(std::string email1, std::string email2);
			void unblockconnection(std::string email1, std::string email2);
			//void mapconnection(std::string email1,std::string email2);
			//void unmapconnection(std::string email1,std::string email2);
			bool isBlocked(std::string email1, std::string email2);
		};
	} // namespace dao
} // namespace gc
