#pragma once
#include <string>
#include <vector>

#include "Connection.h"
#include "Message.h"
/**
* @File : IMessageServiceDAO
* @Author : Anurag Gupta
* @Brief : Its is an interface through which Message Services and the methods to use the DAO for DB related operations are    
* provided to the user.It is used by MessageServices of the business layer.
*/
namespace gc
{
	namespace dao
	{
		struct IMessageServiceDAO
		{
			virtual std::vector<entities::Connection *> getConnectionTable() = 0;
			/** @Brief : Used to get all the users from email
			* @param : No parameters
			* @return : Vector of all the users pointers
 			*/
			virtual std::vector<std::string> getAllUsers() = 0;
			/** @Brief : Used to disconnect from the DB
 			*/
			virtual ~IMessageServiceDAO();

			virtual std::vector<entities::Message *> restore() = 0;
			virtual std::string serialize(entities::Message *msg) = 0;
			virtual entities::Message *deserialize(std::string og_msg) = 0;
			virtual void addMessageDB(entities::Message *msg) = 0;
			virtual void deleteMessageDB(entities::Message *msg) = 0;
		};
	} // namespace dao
} // namespace gc
