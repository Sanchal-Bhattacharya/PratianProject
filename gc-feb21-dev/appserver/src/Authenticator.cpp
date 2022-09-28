#include <iostream>
#include <sstream>
#include <string>

#include <cppcms/service.h>
#include <cppcms/applications_pool.h>
#include <cppcms/application.h>
#include <cppcms/http_response.h>
#include <cppcms/http_request.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>

#include "Authenticator.h"
#include "UserSecurity.h"
#include "OnlineUsers.h"

//using namespace std;
namespace gc
{
	namespace web
	{

		bool Authenticator::isAuthenticated(std::string postdata, std::string ip)
		{
			std::istringstream iss(postdata);
			cppcms::json::value val1;
			val1.load(iss, true);
			std::string encoded = val1.get<std::string>("encoded_string");

			UserSecurity ob(encoded);
			bool isAuth = true;

			if (ob.checkTime())
			{
				isAuth = isAuth && true;
			}

			if (isAuth)
			{
				gc::entities::OnlineUsers *OnlineEntity = gc::entities::OnlineUsers::getInstance();
				std::string authToken = ob.getAuthToken();
				std::pair<std::string, std::string> tokenPair(authToken, ip);
				isAuth = isAuth && OnlineEntity->isExists(tokenPair);
			}

			return isAuth;
		}
	} // namespace web
} // namespace gc