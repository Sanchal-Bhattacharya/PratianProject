#include "User.h"

namespace gc
{
	namespace entities
	{
		User::User(std::string name, std::string email, std::string mobileNumber, std::string password, std::string salt)
			: _name(name), _email(email), _mobileNumber(mobileNumber), _password(password), _salt(salt)
		{
		}
		void User::setName(std::string name)
		{
			_name = name;
		}
		void User::setMobileNumber(std::string mobileNumber)
		{
			_mobileNumber = mobileNumber;
		}
		void User::setPassword(std::string password)
		{
			_password = password;
		}
		void User::setSalt(std::string salt)
		{
			_salt = salt;
		}
		std::string User::getEmail() const
		{
			return _email;
		}
		std::string User::getName() const
		{
			return _name;
		}
		std::string User::getMobileNumber() const
		{
			return _mobileNumber;
		}
		long long int User::getUserID() const
		{
			return _userID;
		}
		std::string User::getPassword() const
		{
			return _password;
		}
		std::string User::getSalt() const
		{
			return _salt;
		}
	} // namespace entities
} // namespace gc
