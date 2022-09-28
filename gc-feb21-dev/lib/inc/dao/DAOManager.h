#pragma once

#include "IUserServiceDAO.h"
#include "IMessageServiceDAO.h"
#include "IGroupServiceDAO.h"

/** @File : DAOManager
*   @Author : Anurag Gupta
*   @Brief : It is an class used by business layer for getting dao interfaces so as to use dao methods in them.This represents *Facade Pattern.    
*   It is used by both UserServices and MessageServices of the business layer.	
*/
namespace gc
{
	namespace dao
	{
		class DAOManager
		{
		public:
			/** @Brief : Used to get the interface of IUserServiceDAO 
			* @param : No parameters
			* @return : Pointer to IUserServiceDAO interface
			*/
			static IUserServiceDAO *getUserServiceDAO();
			/** @Brief : Used to get the interface of IMessageServiceDAO 
			* @param : No parameters
			* @return : Pointer to IMessageServiceDAO interface
			*/
			static IMessageServiceDAO *getMessageServiceDAO();
			/** @Brief : Used to get the interface of IGroupServiceDAO 
			** @param : No parameters
			** @return : Pointer to IMessageServiceDAO interface
			**/
			static IGroupServiceDAO *getGroupServiceDAO();
		};
	} // namespace dao
} // namespace gc
