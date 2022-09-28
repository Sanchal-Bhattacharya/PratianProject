/**
* @File : MessageService.h
* @Author : Kiran Agrawal
* @Brief : This is the header file for web message service
* 
* This file contains the declaration for The MessageService class
* which implements the message service at web layer to provide services
* requested by http methods : GET and PUT. This class interacts with web client
* and is responsible for sending and reteiving messages.
* It interacts with business layer facade GcBusinessManager to provide
* messaging services.
*/

#pragma once

#include <string>
#include <cppcms/service.h>
#include <cppcms/applications_pool.h>
#include <cppcms/application.h>

namespace gc
{
	namespace web
	{
		class MessageService : public cppcms::application
		{
		public:
			/**
			* @brief creates an instance of MessageService.
			*
			* This is paramaterized constructor that is used to create instance of MessageService class
			* 
			* @param srv an instance of cppcms service is passed as an argument
			*/
			MessageService(cppcms::service &srv);

			/**
			* @brief used to send a message.
			*
			* This function takes json value as input in form of raw data, parses it to json converts it into an object of Message entity
			* and passes it to business layer by calling static getMessageService of facade
			*
			* @return This function returns void
			*/
			void sendMessage();

			/**
			* @brief used to retreive a message.
			*
			* This function takes string as input in url, calls the method of GcBusinessManager facade to retrieve all the messages
			* of that particular email and outputs them to client
			*
			* @param email This function takes email string as argument in form of url
			* @return This function returns void
			*/
			void messageHandler();
			void retrieveMessage(std::string email);
			void sendMessageToGroup();
			void retrieveMessageFromGroups(std::string email);
		};
	} // namespace web
} // namespace gc
