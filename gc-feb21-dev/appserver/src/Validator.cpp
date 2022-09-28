#include <regex>
#include "Validator.h"

namespace gc
{
	namespace web
	{
		bool Validator::isEmailValid(std::string email)
		{
			std::regex re{"([a-zA-Z0-9_]*@[a-zA-Z]*\\.[a-z]{2}(\\.[a-z])?[a-z])"};
			if (!std::regex_match(email, re))
				return false;

			return true;
		}

		bool Validator::isNameValid(std::string name)
		{
			std::regex re{"[a-zA-Z]*"};
			if (!std::regex_match(name, re))
				return false;

			return true;
		}

		bool Validator::isMobileNumberValid(std::string mobno)
		{
			std::regex re{"[0-9]{10}"};
			if (!std::regex_match(mobno, re))
				return false;

			return true;
		}

		bool Validator::isPasswordValid(std::string password)
		{
			std::regex re{"[A-Za-z0-9_@$#%^&\\*!]{8}[A-Za-z0-9_@$#%^&\\*!]*"};
			if (!std::regex_match(password, re))
				return false;

			return true;
		}

		bool Validator::isEncodedStringValid(std::string encoded_string)
		{
			std::regex re{"[A-Za-z0-9/+]*"};
			if (!std::regex_match(encoded_string, re))
				return false;

			return true;
		}
	} // namespace web
} // namespace gc