#include <string>
namespace gc
{
	namespace web
	{
		class Validator
		{
		public:
			static bool isEmailValid(std::string email);
			static bool isNameValid(std::string name);
			static bool isMobileNumberValid(std::string phno);
			static bool isPasswordValid(std::string password);
			static bool isEncodedStringValid(std::string encoded_string);
		};
	} // namespace web
} // namespace gc