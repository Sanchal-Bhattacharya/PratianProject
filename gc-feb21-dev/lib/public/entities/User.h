/**
* @File : User.h
* @Author : Kiran Agrawal
* @Brief : This is the class file for User entity
* 
* This entity defines a user. The attributes of user defined are : name, email, mobile number.
* This is a common entity that is used by all the layers of project including web, business, dao, db.
*/

#pragma once
#include <string>

namespace gc
{
	namespace entities
	{
		class User
		{
			std::string _name;
			std::string _email;
			long long int _userID;
			std::string _mobileNumber;
			std::string _password;
			std::string _salt;

		public:
			/**
			* @brief creates an instance of User.
			*
			* This is paramaterized constructor that is used to create instance of User class
			* 
			* @param name,email,mobileNumber,password,salt the user attributes are passed as an argument
			*/
			User(std::string name, std::string email, std::string mobileNumber, std::string password, std::string salt);

			/**
			* @brief used to set the name of user.
			*
			* This function takes string as input and updates user name
			*
			* @param name This function takes name string as argument
			* @return This function returns void
			*/
			void setName(std::string name);

			/**
			* @brief used to set the mobile number of user.
			*
			* This function takes string as input and updates user mobile number
			*
			* @param mobileNumber This function takes mobileNumber string as argument
			* @return This function returns void
			*/
			void setMobileNumber(std::string mobileNumber);

			/**
			* @brief used to set the password of user.
			*
			* This function takes string as input and updates user password
			*
			* @param password This function takes password string as argument
			* @return This function returns void
			*/
			void setPassword(std::string password);

			/**
			* @brief used to set the salt of user.
			*
			* This function takes string as input and updates user salt
			*
			* @param salt This function takes salt string as argument
			* @return This function returns void
			*/
			void setSalt(std::string salt);

			/**
			* @brief used to retrieve the email of user.
			*
			* This function is used to retrieve the email id of user
			*
			* @return This function returns string email
			*/
			std::string getEmail() const;

			/**
			* @brief used to retrieve the name of user.
			*
			* This function is used to retrieve the name of user
			*
			* @return This function returns string name
			*/
			std::string getName() const;

			/**
			* @brief used to retrieve the mobile number of user.
			*
			* This function is used to retrieve the mobile number of user
			*
			* @return This function returns string mobile
			*/
			std::string getMobileNumber() const;

			/**
			* @brief used to retrieve the UserID of user.
			*
			* This function is used to retrieve the UserID of user
			*
			* @return This function returns long long int UserID
			*/
			long long int getUserID() const;

			/**
			* @brief used to retrieve the password of user.
			*
			* This function is used to retrieve the password of user
			*
			* @return This function returns string password
			*/
			std::string getPassword() const;

			/**
			* @brief used to retrieve the salt of user.
			*
			* This function is used to retrieve the salt of user
			*
			* @return This function returns string salt
			*/
			std::string getSalt() const;
		};
	} // namespace entities
} // namespace gc
