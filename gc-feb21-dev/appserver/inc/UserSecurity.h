#pragma once
#include <string>

namespace gc
{
	namespace web
	{
		class UserSecurity
		{
		private:
			std::string time_stamp;
			std::string auth_token;

			std::string base64_chars =
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz"
				"0123456789+/";

			bool is_base64(unsigned char c);

			std::string base64_decode(std::string const &encoded_string);

			void setParameters(std::string);

		public:
			UserSecurity(std::string);
			bool checkTime();
			std::string getAuthToken();
			static std::string generateAuthToken();
		};
	} // namespace web
} // namespace gc