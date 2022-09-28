#pragma once

#include <string>
namespace gc
{
	namespace web
	{
		class Authenticator
		{
		public:
			static bool isAuthenticated(std::string postdata, std::string ip);
		};
	} // namespace web
} // namespace gc
