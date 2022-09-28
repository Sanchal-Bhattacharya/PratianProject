#include <iostream>

#include <cppcms/http_response.h>
#include <cppcms/http_request.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>

#include "UserSecurity.h"
#include "Authenticator.h"

#include "User.h"
#include "GcBusinessManager.h"
#include "IUserService.h"
#include "GCException.h"
#include "BusinessQueryException.h"
#include "BusinessConnectionException.h"
#include "Log.h"
#include "Random.h"
#include "Hash.h"
#include "OnlineUsers.h"
#include "Validator.h"

#include "UserService.h"

using namespace std;
namespace cppcms
{
	namespace json
	{
		template <>
		struct traits<gc::entities::User *>
		{
			static gc::entities::User *get(value const &v)
			{
				if (v.type() != is_object)
					throw bad_value_cast();

				gc::entities::User *user = new gc::entities::User(v.get<std::string>("name"), v.get<std::string>("email"), v.get<std::string>("mobileNumber"), v.get<std::string>("password"), v.get<std::string>("salt"));
				return user;
			}

			static void set(value &v, gc::entities::User *const &in)
			{
				v.set("name", in->getName());
				v.set("email", in->getEmail());
				v.set("mobileNumber", in->getMobileNumber());
			}
		};
	} // namespace json
} // namespace cppcms

namespace
{
	string stripValue(string json)
	{
		size_t passindex = json.find("password\"");
		string value = "";
		int c = 0;
		for (int i = 11; i < json.size(); i++)
		{
			if (json[i + passindex] == '\"')
				break;
			value += json[i + passindex];
		}
		return value;
	}
	std::string getHashedJSON(std::string json, std::string passwdHash)
	{
		std::size_t passindex = json.find("password\"");
		std::size_t pass_length = 0;
		for (int i = 11; i < json.size(); i++)
		{
			if (json[i + passindex] == '\"')

				break;
			pass_length++;
		}

		json.replace(passindex + 11, pass_length, passwdHash);

		return json;
	}

	std::string addSaltToJSON(std::string json, std::string salt)
	{
		std::string saltKey = "\"salt\":" + std::string("\"") + salt + std::string("\"");
		json.replace(json.size() - 2, 2, "\", " + saltKey + "}");

		return json;
	}

} // namespace

/*namespace gc{
	namespace web{
	bool isAuthenticated(std::string postdata,std::string ip){
		
		cout<<"Entered isAuth()"<<endl;		
		std::istringstream iss (postdata);
		cppcms::json::value val1;
		val1.load(iss,true);
		std::string encoded = val1.get<string>("encoded_string");
		cout<<"CheckPoint 1\n";

		UserSecurity ob(encoded);
		cout<<"Checkpoint 2\n";
		bool isAuth=true;		
		if(ob.checkTime()){
			isAuth=isAuth && true;
		}

		cout<<"Checkpoint(afterchecktime) 3\n";
		if(isAuth){
			gc::entities::OnlineUsers* OnlineEntity= gc::entities::OnlineUsers::getInstance();
			cout<<"Checkpoint getinstance() 4\n";
			string authToken = ob.getAuthToken();
			
			std::pair<std::string,std::string> tokenPair(authToken,ip);
			cout<<"Check Point 5 map\n";
			cout<<tokenPair.first<<" "<<tokenPair.second<<"\n";
			cout<<OnlineEntity<<endl;
			cout<<OnlineEntity->isExists(tokenPair)<<endl;
			isAuth = isAuth && OnlineEntity->isExists(tokenPair);
		}

		

		cout<<"Check Point 6 isAuth: "<<isAuth<<"\n";

		return isAuth;
	}
}}*/

namespace gc
{
	namespace web
	{

		UserService::UserService(cppcms::service &srv)
			: cppcms::application(srv)
		{
			dispatcher().assign("/users", &UserService::handler, this);
			dispatcher().assign("/users/", &UserService::handler, this);
			mapper().assign("users", "/users");

			dispatcher().assign("/users/(.*)", &UserService::getUser, this, 1);
			mapper().assign("users", "/users/(.*)");

			dispatcher().assign("/login", &UserService::loginHandler, this);
			dispatcher().assign("/login/", &UserService::loginHandler, this);

			mapper().assign("login", "/login");
		}

		void UserService::loginHandler()
		{
			if (request().request_method() == "POST")
			{
				login();
			}
		}

		void UserService::handler()
		{
			if (request().request_method() == "GET")

			{
				getAllUsers();
			}
			else if (request().request_method() == "POST")
			{
				updateUser();
			}
			else if (request().request_method() == "PUT")
			{
				createUser();
			}
			else
				response().status(cppcms::http::response::not_implemented);
		}

		void UserService::updateUser()
		{
			if (request().request_method() == "POST")
			{
				gc::business::IUserService *im = gc::business::GcBusinessManager::getUserService();
				try
				{
					std::pair<void *, size_t> data = request().raw_post_data();
					std::string postdata(reinterpret_cast<char *>(data.first), data.second);
					std::string pass = stripValue(postdata);
					if (!Validator::isPasswordValid(pass))
					{
						response().status(cppcms::http::response::precondition_failed);
						return;
					}

					Random r1;
					string Salt = r1.generateSalt();
					pass = pass + Salt;

					Hash h1(pass);
					pass = h1.sha256();
					postdata = getHashedJSON(postdata, pass);
					postdata = addSaltToJSON(postdata, Salt);

					std::istringstream iss(postdata);
					cppcms::json::value val1;
					val1.load(iss, true);
					if (!(Validator::isNameValid(val1.get<std::string>("name")) && Validator::isEmailValid(val1.get<std::string>("email")) && Validator::isMobileNumberValid(val1.get<std::string>("mobileNumber"))))
					{
						response().status(cppcms::http::response::precondition_failed);
						return;
					}
					gc::entities::User *user;
					user = val1.get_value<gc::entities::User *>();
					im->updateUser(user);
					util::Log::Info("Web User Service", "User service Instance successfully Created and user updated into the system");
					response().status(cppcms::http::response::ok);
					im = NULL;
				}

				catch (cppcms::json::bad_value_cast e)
				{
					util::Log::Error("Web User Service", "invalid json data (not an object)");
					response().status(cppcms::http::response::no_content);
				}

				catch (gc::business::BusinessQueryException &bqe)
				{
					util::Log::Error("WebUserService::UpdateUser()", bqe.what());
					im = NULL;
					response().status(cppcms::http::response::partial_content);
				}

				catch (gc::business::BusinessConnectionException &bce)
				{
					util::Log::Error("WebUserService::UpdateUser()", bce.what());
					im = NULL;
					response().status(cppcms::http::response::service_unavailable);
				}

				catch (gc::GCException &ge)
				{
					util::Log::Error("WebUserService::UpdateUser()", ge.what());
					im = NULL;
					response().status(cppcms::http::response::internal_server_error);
				}

				catch (...)
				{
					util::Log::Error("WebUserService::UpdateUser()", "Unexpected exception");
					im = NULL;
					response().status(cppcms::http::response::internal_server_error);
				}
			}
			else
				response().status(cppcms::http::response::method_not_allowed);
		}

		void UserService::createUser()
		{
			if (request().request_method() == "PUT")
			{
				gc::business::IUserService *im = gc::business::GcBusinessManager::getUserService();

				try
				{
					std::pair<void *, size_t> data = request().raw_post_data();
					std::string postdata(reinterpret_cast<char *>(data.first), data.second);

					string pass = stripValue(postdata);
					if (!Validator::isPasswordValid(pass))
					{
						response().status(cppcms::http::response::precondition_failed);
						return;
					}

					Random r1;
					string Salt = r1.generateSalt();
					pass = pass + Salt;
					Hash h1(pass);
					pass = h1.sha256();
					postdata = getHashedJSON(postdata, pass);
					postdata = addSaltToJSON(postdata, Salt);
					std::istringstream iss(postdata);

					cppcms::json::value val1;

					val1.load(iss, true);
					if (!(Validator::isNameValid(val1.get<std::string>("name")) && Validator::isEmailValid(val1.get<std::string>("email")) && Validator::isMobileNumberValid(val1.get<std::string>("mobileNumber"))))
					{
						response().status(cppcms::http::response::precondition_failed);
						return;
					}
					gc::entities::User *user;
					user = val1.get_value<gc::entities::User *>();
					im->createUser(user);
					response().status(cppcms::http::response::ok);
					util::Log::Info("Web User Service", "User service Instance successfully Created and user created into the system");
					im = NULL;
				}

				catch (cppcms::json::bad_value_cast e)
				{
					util::Log::Error("Web User Service", "invalid json data (not an object)");
					response().status(cppcms::http::response::no_content);
				}

				catch (gc::business::BusinessQueryException &bqe)
				{
					util::Log::Error("WebUserService::CreateUser()", bqe.what());
					im = NULL;
					response().status(cppcms::http::response::conflict);
				}

				catch (gc::business::BusinessConnectionException &bce)
				{
					util::Log::Error("WebUserService::CreateUser()", bce.what());
					im = NULL;
					response().status(cppcms::http::response::service_unavailable);
				}

				catch (gc::GCException &ge)
				{
					util::Log::Error("WebUserService::CreateUser()", ge.what());
					im = NULL;
					response().status(cppcms::http::response::internal_server_error);
				}

				catch (...)
				{
					util::Log::Error("WebUserService::CreateUser()", "Unexpected exception");
					im = NULL;
					response().status(cppcms::http::response::internal_server_error);
				}
			}
			else
				response().status(cppcms::http::response::method_not_allowed);
		}

		void UserService::getAllUsers()
		{
			gc::business::IUserService *im = gc::business::GcBusinessManager::getUserService();

			try
			{
				std::vector<gc::entities::User *> users = im->getAllUsers();
				cppcms::json::array _jsonData;
				for (int i = 0; i < users.size(); i++)
				{
					cppcms::json::value val1;
					val1.set_value(users[i]);
					_jsonData.push_back(val1);
				}
				response().content_type("application/json");
				response().out() << _jsonData;
				response().status(cppcms::http::response::ok);
				delete im;
				im = NULL;
			}
			catch (gc::business::BusinessQueryException &bqe)
			{
				util::Log::Error("WebUserService::GetAllUsers()", bqe.what());
				delete im;
				im = NULL;
				response().status(cppcms::http::response::bad_request);
			}

			catch (gc::business::BusinessConnectionException &bce)
			{
				util::Log::Error("WebUserService::GetAllUsers()", bce.what());
				delete im;
				im = NULL;
				response().status(cppcms::http::response::service_unavailable);
			}

			catch (gc::GCException &ge)
			{
				util::Log::Error("WebUserService::GetAllUsers()", ge.what());
				delete im;
				im = NULL;
				response().status(cppcms::http::response::internal_server_error);
			}

			catch (...)
			{
				util::Log::Error("WebUserService::GetAllUsers()", "Unexpected exception");
				delete im;
				im = NULL;
				response().status(cppcms::http::response::internal_server_error);
			}
		}

		void UserService::getUser(std::string email)
		{
			if (!Validator::isEmailValid(email))
			{
				response().status(cppcms::http::response::precondition_failed);
				return;
			}
			if (request().request_method() == "GET")
			{
				gc::business::IUserService *im = gc::business::GcBusinessManager::getUserService();

				try
				{
					gc::entities::User *user = im->getUser(email);
					cppcms::json::value val1;
					val1.set_value(user);
					response().content_type("application/json");
					response().out() << val1;
					response().status(cppcms::http::response::ok);
					delete im;
					im = NULL;
				}

				catch (gc::business::BusinessQueryException &bqe)
				{
					util::Log::Error("WebUserService::GetUser()", bqe.what());
					delete im;
					im = NULL;
					response().status(cppcms::http::response::bad_request);
				}

				catch (gc::business::BusinessConnectionException &bce)
				{
					util::Log::Error("WebUserService::GetUser()", bce.what());
					delete im;
					im = NULL;
					response().status(cppcms::http::response::service_unavailable);
				}

				catch (gc::GCException &ge)
				{
					util::Log::Error("WebUserService::GetUser()", ge.what());
					delete im;
					im = NULL;
					response().status(cppcms::http::response::internal_server_error);
				}

				catch (...)
				{
					util::Log::Error("WebUserService::GetUser()", "Unexpected exception");
					delete im;
					im = NULL;
					response().status(cppcms::http::response::internal_server_error);
				}
			}
			else if (request().request_method() == "DELETE")
			{
				deleteUser(email);
			}
		}

		void UserService::deleteUser(std::string email)
		{
			if (request().request_method() == "DELETE")
			{
				gc::business::IUserService *im = gc::business::GcBusinessManager::getUserService();

				try
				{
					im->deleteUser(email);
					response().status(cppcms::http::response::ok);
					util::Log::Info("Web User Service", "User service Instance successfully Created and user deleted from the system");
					im = NULL;
				}

				catch (gc::business::BusinessQueryException &bqe)
				{
					util::Log::Error("WebUserService::DeleteUser()", bqe.what());
					im = NULL;
					response().status(cppcms::http::response::bad_request);
				}

				catch (gc::business::BusinessConnectionException &bce)
				{
					util::Log::Error("WebUserService::DeleteUser()", bce.what());
					im = NULL;
					response().status(cppcms::http::response::service_unavailable);
				}

				catch (gc::GCException &ge)
				{
					util::Log::Error("WebUserService::DeleteUser()", ge.what());
					im = NULL;
					response().status(cppcms::http::response::internal_server_error);
				}

				catch (...)
				{
					util::Log::Error("WebUserService::DeleteUser()", "Unexpected exception");
					im = NULL;
					response().status(cppcms::http::response::internal_server_error);
				}
			}
		}

		void UserService::login()
		{
			if (request().request_method() == "POST")
			{
				gc::business::IUserService *im = gc::business::GcBusinessManager::getUserService();
				try
				{
					pair<void *, size_t> data = request().raw_post_data();
					string postdata(reinterpret_cast<char *>(data.first), data.second);

					istringstream iss(postdata);

					cppcms::json::value v1;
					v1.load(iss, true);

					string email = v1.get<string>("email");
					string password = v1.get<string>("password");

					std::pair<std::string, std::string> s = im->login(email);
					std::string hashPass = s.first;
					std::string salt = s.second;

					password = password + salt;
					Hash h1(password);
					std::string hashedServer = h1.sha256();
					if (hashedServer == hashPass)
					{
						std::string auth_token = UserSecurity::generateAuthToken();
						std::string ip = request().remote_addr();
						gc::entities::OnlineUsers *instance = gc::entities::OnlineUsers::getInstance();

						instance->setAuth_IP(email, auth_token, ip);
						instance = nullptr;

						cppcms::json::value v1;
						v1.set("auth_token", auth_token);
						response().content_type("application/json");
						response().out() << v1;

						util::Log::Info("WebUserService::login()", " Successful");
						response().status(cppcms::http::response::ok);
					}
					else
					{
						response().status(cppcms::http::response::unauthorized);
					}
				}

				catch (gc::business::BusinessQueryException &bqe)
				{
					util::Log::Error("WebUserService::login()", "Invalid Email ID");
					im = NULL;
					response().status(cppcms::http::response::unauthorized);
				}

				catch (...)
				{
					util::Log::Error("WebUserService::login()", "Unexpected exception");
					im = NULL;
					response().status(cppcms::http::response::internal_server_error);
				}
			}
		}
	} // namespace web
} // namespace gc
