#pragma once
#include <string>
#include <map>

namespace gc
{
	namespace entities
	{
		class OnlineUsers
		{
		private:
			std::map<std::string, std::pair<std::string, std::string>> AuthIPmap;
			static OnlineUsers *instance;
			OnlineUsers();
		public:
			static OnlineUsers *getInstance();

			/*@ brief used to get an instance of this singleton class
			*
			*
			* @return an object of the OnlineUsers class */
			std::pair<std::string, std::string> getAuth_IP(std::string email);

			/*@brief: used to retrieve the (authToken,IP)pair
			* 
			*
			* @returns the AuthIP pair*/
			void setAuth_IP(std::string email, std::string authToken, std::string IP);
			
			/*@brief: used to set the values of the AuthIPmap
			*
			*
			* @return void*/
			void logout(std::string email);

			/*@brief deletes the AuthIPmap of the entered email
			*
			*
			*@return void */
			bool isOnline(std::string email);

			/*@brief: used to indicate if the user is online
			*
			*
			*@return bool */
			bool isExists(std::pair<std::string, std::string> x);

			/**@brief: used to indicate if the user exists 
			 *
			 * @return bool*/
			std::string fetchEmail(std::pair<std::string, std::string> AU_IP);

			/**@brief: used to indicate if the user exists 
			 *
			 * @return bool*/
			~OnlineUsers();
		};
	} // namespace entities
} // namespace gc
