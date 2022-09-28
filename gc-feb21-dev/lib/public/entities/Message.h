/**
* @File : Message.h
* @Author : Kiran Agrawal
* @Brief : This is the class file for message entity
* 
* This entity defines a message. The attributes of message defined are : toId, fromId,
* msgId, message description, acknowlegdement status, message type.
* This is a common entity that is used by all the layers of project including web, business, dao, db.
*/

#pragma once

#include <string>
namespace gc
{
	namespace entities
	{
		class Message
		{
			int msgId;
			std::string toId;
			std::string fromId;
			std::string message;
			int messageType;
			int ackStatus;
		
		public:
		
			/**
			* @brief creates an instance of Message.
			*
			* This is paramaterized constructor that is used to create instance of Message class
			* 
			* @param msgId,toId,fromId,message,msgtype,ackStatus the message attributes are passed as an argument
			*/
			Message(int _msgId, std::string _toId, std::string _fromId, std::string _message, int _messageType = 0, int _ackStatus = 0);
			
			/**
			* @brief used to retrieve the emailId of receiver.
			*
			* This function is used to retrieve the emailId of receiver
			*
			* @return This function returns string toId
			*/
			std::string getToId() const;
			
			/**
			* @brief used to retrieve the emailId of sender.
			*
			* This function is used to retrieve the emailId of sender
			*
			* @return This function returns string fromId
			*/
			std::string getFromId() const;
			
			/**
			* @brief used to retrieve the messageId.
			*
			* This function is used to retrieve the messageId which is in turn used 
			* by business messaging service to send acknowledgement
			*
			* @return This function returns int msgId
			*/
			int getMsgId() const;
			
			/**
			* @brief used to retrieve the message.
			*
			* This function is used to retrieve the body of message sent
			*
			* @return This function returns string Message
			*/
			std::string getMessage() const;
			
			/**
			* @brief used to retrieve the ackstatus.
			*
			* This function is used to retrieve the status of acknowledgement sent. This attribute is 
			* used by business messaging service to provide ack service so that the sent message can be 
			* deleted from system where ack status tells that message has been delivered to the intended user 
			*
			* @return This function returns string toId
			*/
			int getAckStatus() const;
			
			/**
			* @brief used to retrieve the messageType.
			*
			* This function is used to retrieve the messageType. If this parameter is set to 0, 
			* it means normal message while 1 denotes that it is an acknowledgement
			*
			* @return This function returns string messageType
			*/
			int getMessageType() const;
		};
	}
}

