#pragma once
#include <string>
#include <vector>

namespace gc
{
	namespace entities
	{
		class Group
		{
			std::string _name;
			long long int _groupID;
			std::vector<std::string> _emailList;

		public:
			/**
			* @brief creates an instance of Group.
			*
			* This is paramaterized constructor that is used to create instance of Group class
			*
			* @param name,email the group attributes is passed as an argument
			*/
			Group(std::string name, std::string email);

			/**
			* @brief used to set the user email in the group.
			*
			* This function takes vector of strings as input and updates _emailList vector in the groups
			*
			* @param name This function takes email vector of string as argument
			* @return This function returns void
			*/
			//    void setEmail(std::vector<std::string> email);

			/**
			* @brief used to set the name of group.
			*
			* This function takes string as input and updates group name
			*
			* @param name This function takes name string as argument
			* @return This function returns void
			*/
			void setName(std::string name);

			/**
			* @brief used to get the email of users in the group.
			*
			* This function is used to retrieve the email of the users in the group
			* 
			* @return This function returns vector emailList
			*/
			std::vector<std::string> getEmailList() const;

			/**
			* @brief used to retrieve the name of user.
			*
			* This function is used to retrieve the name of user
			*
			* @return This function returns string name
			*/
			std::string getName() const;

			/**
			* @brief used to retrieve the GroupID of group.
			*
			* This function is used to retrieve the GroupID of group
			*
			* @return This function returns long long int GroupID
			*/
			long long int getGroupID() const;
		};
	} // namespace entities
} // namespace gc
