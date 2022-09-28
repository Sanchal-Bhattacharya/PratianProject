/**
* @File : WebService.h
* @Author : Kiran Agrawal
* @Brief : This is the header file for web service
* 
* This file contains the declaration for The WebService class
* which is responsible for creating an instance of userservice and 
* messageservice depending on the request obtained in url
*/


#pragma once

#include <cppcms/service.h>
#include <cppcms/applications_pool.h>
#include <cppcms/application.h>


using namespace std;

namespace gc
{
	namespace web
	{
		class WebService : public cppcms::application
		{
		public:
			/**
			* @brief creates an instance of WebService.
			*
			* This is paramaterized constructor that is used to create instance of WebService class. 
			* It uses attach method of application that creates an anonymous instance of userService and 
			* messageService depending on the requset obtained in the url.
			* 
			* @param srv an instance of cppcms service is passed as an argument
			*/
			WebService(cppcms::service &srv);
		};
	}
}
