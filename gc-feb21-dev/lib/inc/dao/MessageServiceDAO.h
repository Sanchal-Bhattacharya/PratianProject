#pragma once

#include <sstream>
#include <string>

#include "IMessageServiceDAO.h"

/**
* @File : IMessageServiceDAO
* @Author : Anurag Gupta
* @Brief : Its is an class extending from IMessageService through which Message Services and the methods to use the DAO for DB * * related operations are implemented and provided to the user through the interface.It is used by MessageServices of the * * * *business layer.
*/

namespace gc
{
	namespace dao
	{
		class MessageServiceDAO : public IMessageServiceDAO
		{
			db::IDBConnect *dbObj;

		public:
			/** @Brief : Used to create connection with the database framework.
			*/
			MessageServiceDAO();
			/** @Brief : Used to disconnect from the database.
			*/
			~MessageServiceDAO();

			std::vector<entities::Connection *> getConnectionTable();
			/** @Brief : Used to get all the users from email
			* @param : No parameters
			* @return : Vector of all the users pointers
 			*/
			std::vector<std::string> getAllUsers();

			std::string serialize(entities::Message *msg);

			entities::Message *deserialize(std::string og_msg);

			void addMessageDB(entities::Message *msg);

			void deleteMessageDB(entities::Message *msg);

			std::vector<entities::Message *> restore();
		};
	} // namespace dao
} // namespace gc
