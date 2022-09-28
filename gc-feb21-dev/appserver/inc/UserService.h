/**
* @File : UserService.h
* @Author : Ankita Vats
* @Brief : This is the class which provides all the User Services. 
* 
*This contains the declaration for the UserService class which accepts the data sent by the client and passes it to the business layer for *further implementation.This class belongs to the web layer and implements the requested http methods: GET, PUT, POST and DELETE.  
*/

#pragma once
#include <cppcms/service.h>
#include <cppcms/applications_pool.h>
#include <cppcms/application.h>

#include <string>
#include <vector>


namespace gc
{
	namespace web
	{
		class UserService : public cppcms::application
		{
		public:
			/**
		*@Brief :This is the constructor which provides the dispatcher and mapper to reach the various http methods.
		*/
			UserService(cppcms::service &srv);
			/**
			*@Brief :Handler is used to call the methods which accept three parameters to resolve the conflict in calls to the requested 				*methods.
			*@param :An object of service class is accepted by reference 
			*@return :void
			*/
			void handler();
			void loginHandler();
			/**
			*@Brief :This method provides the implementation to accept the request of creating a new user through PUT http method and 				*passes it to the class of the business layer for further implementation.
			*@return :void
			*/
			void createUser();
			/**
			*Brief :This method provides the implementation to accept the request of updating the user details through POST method and 				*passes it to the class of the business layer for further implementation. 
			*@return :void
			*/
			void updateUser();
			/**
			*Brief :This method provides the implementation to accept the request of retrieving the user details through the GET method and
			*passses it to the class of business layer for further implementation.
			*@param :email It accepts the emailID of the user whose details need to be extracted.
			*@return :void
			*/
			void getUser(std::string email);
			/**
			*Brief :This method provides the implementation to accept the request of retrieving the details of all the users through the  				*GET method and passses it to the class of business layer for further implementation.
			*@return :void
			*/
			void getAllUsers();
			/**
			*This method provides the implementation to accept the request of deleting the user through the DELETE method and passses it to 			*the class of business layer for further implementation.
			*@param :email It accepts the emailID of the user whose details need to be extracted.
			*@return :void
			*/
			void deleteUser(std::string email);

			void login();
		};
	} // namespace web
} // namespace gc
