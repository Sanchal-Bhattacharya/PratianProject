#include <iostream>

#include <cppcms/http_response.h>
#include <cppcms/http_request.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>

#include "GroupService.h"

#include "UserSecurity.h"
#include "Authenticator.h"
#include "Group.h"
#include "GcBusinessManager.h"
#include "IGroupService.h"
#include "GCException.h"
#include "BusinessQueryException.h"
#include "BusinessConnectionException.h"
#include "Log.h"
#include "OnlineUsers.h"

using namespace std;

namespace cppcms
{
	namespace json
	{
		template <>
		struct traits<gc::entities::Group *>
		{
			static gc::entities::Group *get(value const &v)
			{
				if (v.type() != is_object)
					throw bad_value_cast();

				gc::entities::Group *group = new gc::entities::Group(v.get<std::string>("name"), v.get<std::string>("email"));
				return group;
			}

			static void set(value &v, gc::entities::Group *const &in)
			{
				v.set("name", in->getName());
				v.set("email", in->getEmailList());
			}

			static void set(value &v, std::vector<std::string> const &users)
			{
				v.set("email", users);
			}
		};
	} // namespace json
} // namespace cppcms

namespace gc
{
	namespace web
	{

		GroupService::GroupService(cppcms::service &srv)
			: cppcms::application(srv)
		{
			dispatcher().assign("/groups", &GroupService::handler, this);
			dispatcher().assign("/groups/", &GroupService::handler, this);
			mapper().assign("groups", "/groups");

			dispatcher().assign("/groups/(.*)", &GroupService::getGroup, this, 1);
			mapper().assign("groups", "/groups/(.*)");

			dispatcher().assign("/addtogroup", &GroupService::userHandler, this);
			dispatcher().assign("/addtogroup/", &GroupService::userHandler, this);
			mapper().assign("addtogroup", "/addtogroup");
		}

		void GroupService::handler()
		{
			if (request().request_method() == "GET")

			{
				getAllGroups();
			}
			else if (request().request_method() == "POST")
			{
				updateGroup();
			}
			else if (request().request_method() == "PUT")
			{
				createGroup();
			}
			else
				response().status(cppcms::http::response::not_implemented);
		}

		void GroupService::userHandler()
		{
			if (request().request_method() == "PUT")
			{
				addUser();
			}
			else if (request().request_method() == "DELETE")
			{
				removeUser();
			}
			else
			{
				response().status(cppcms::http::response::not_implemented);
			}
		}

		void GroupService::updateGroup()
		{
			if (request().request_method() == "POST")
			{
				gc::business::IGroupService *im = gc::business::GcBusinessManager::getGroupService();
				try
				{
					std::pair<void *, size_t> data = request().raw_post_data();
					std::string postdata(reinterpret_cast<char *>(data.first), data.second);
					std::istringstream iss(postdata);
					cppcms::json::value val1;
					val1.load(iss, true);

					string ip = request().remote_addr();
					if (!Authenticator::isAuthenticated(postdata, ip))
					{
						response().status(cppcms::http::response::bad_request);
						return;
					}
					UserSecurity us(val1.get<std::string>("encoded_string"));
					std::pair<std::string, std::string> AU_IP;
					AU_IP.first = us.getAuthToken();
					AU_IP.second = ip;
					gc::entities::OnlineUsers *o = gc::entities::OnlineUsers::getInstance();
					std::string email = o->fetchEmail(AU_IP);
					if (email == "")
					{
						response().status(cppcms::http::response::bad_request);
						return;
					}

					im->updateGroup(val1.get<std::string>("oldname"), val1.get<std::string>("newname"));
					util::Log::Info("Web Group Service", "Group service Instance successfully Created and group updated into the system");
					response().status(cppcms::http::response::ok);
					im = NULL;
				}

				catch (cppcms::json::bad_value_cast e)
				{
					util::Log::Error("Web Group Service", "invalid json data (not an object)");
					response().status(cppcms::http::response::no_content);
				}

				catch (gc::business::BusinessQueryException &bqe)
				{
					util::Log::Error("WebGroupService::UpdateGroup()", bqe.what());
					im = NULL;
					response().status(cppcms::http::response::partial_content);
				}

				catch (gc::business::BusinessConnectionException &bce)
				{
					util::Log::Error("WebGroupService::UpdateGroup()", bce.what());
					im = NULL;
					response().status(cppcms::http::response::service_unavailable);
				}

				catch (gc::GCException &ge)
				{
					util::Log::Error("WebGroupService::UpdateGroup()", ge.what());
					im = NULL;
					response().status(cppcms::http::response::internal_server_error);
				}

				catch (...)
				{
					util::Log::Error("WebGroupService::UpdateGroup()", "Unexpected exception");
					im = NULL;
					response().status(cppcms::http::response::internal_server_error);
				}
			}
			else
				response().status(cppcms::http::response::method_not_allowed);
		}

		void GroupService::createGroup()
		{
			if (request().request_method() == "PUT")
			{
				gc::business::IGroupService *im = gc::business::GcBusinessManager::getGroupService();

				try
				{
					std::pair<void *, size_t> data = request().raw_post_data();
					std::string postdata(reinterpret_cast<char *>(data.first), data.second);

					std::istringstream iss(postdata);

					string ip = request().remote_addr();
					if (!Authenticator::isAuthenticated(postdata, ip))
					{
						response().status(cppcms::http::response::bad_request);
						return;
					}

					cppcms::json::value val1;

					val1.load(iss, true);

					gc::entities::Group *group;
					group = val1.get_value<gc::entities::Group *>();
					im->createGroup(group);
					response().status(cppcms::http::response::ok);
					util::Log::Info("Web Group Service", "Group service Instance successfully Created and user created into the system");
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

		void GroupService::getAllGroups()
		{
			gc::business::IGroupService *im = gc::business::GcBusinessManager::getGroupService();

			try
			{
				std::vector<std::string> groups = im->getAllGroups();
				cppcms::json::array _jsonData;
				for (int i = 0; i < groups.size(); i++)
				{
					cppcms::json::value val1;
					val1.set_value(groups[i]);
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
				util::Log::Error("WebGroupService::GetAllGroups()", bqe.what());
				delete im;
				im = NULL;
				response().status(cppcms::http::response::bad_request);
			}

			catch (gc::business::BusinessConnectionException &bce)
			{
				util::Log::Error("WebGroupService::GetAlls()", bce.what());
				delete im;
				im = NULL;
				response().status(cppcms::http::response::service_unavailable);
			}

			catch (gc::GCException &ge)
			{
				util::Log::Error("WebGroupService::GetAllGroups()", ge.what());
				delete im;
				im = NULL;
				response().status(cppcms::http::response::internal_server_error);
			}

			catch (...)
			{
				util::Log::Error("WebGroupService::GetAllGroups()", "Unexpected exception");
				delete im;
				im = NULL;
				response().status(cppcms::http::response::internal_server_error);
			}
		}

		void GroupService::getGroup(std::string name)
		{
			if (request().request_method() == "GET")
			{
				gc::business::IGroupService *im = gc::business::GcBusinessManager::getGroupService();

				try
				{
					std::pair<void *, size_t> data = request().raw_post_data();
					std::string postdata(reinterpret_cast<char *>(data.first), data.second);
					cppcms::json::value val1;

					string ip = request().remote_addr();
					if (!Authenticator::isAuthenticated(postdata, ip))
					{
						response().status(cppcms::http::response::bad_request);
						return;
					}

					std::istringstream iss(postdata);
					val1.load(iss, true);

					UserSecurity us(val1.get<std::string>("encoded_string"));
					std::pair<std::string, std::string> AU_IP;
					AU_IP.first = us.getAuthToken();
					AU_IP.second = ip;
					gc::entities::OnlineUsers *o = gc::entities::OnlineUsers::getInstance();
					std::string email = o->fetchEmail(AU_IP);
					if (email == "")
					{
						response().status(cppcms::http::response::bad_request);
						return;
					}

					std::vector<std::string> group = im->getUsers(name);

					val1.set_value(group);
					response().content_type("application/json");
					response().out() << val1;
					response().status(cppcms::http::response::ok);
					delete im;
					im = NULL;
				}

				catch (gc::business::BusinessQueryException &bqe)
				{
					util::Log::Error("WebGroupService::GetGroup()", bqe.what());
					delete im;
					im = NULL;
					response().status(cppcms::http::response::bad_request);
				}

				catch (gc::business::BusinessConnectionException &bce)
				{
					util::Log::Error("WebGroupService::GetGroup()", bce.what());
					delete im;
					im = NULL;
					response().status(cppcms::http::response::service_unavailable);
				}

				catch (gc::GCException &ge)
				{
					util::Log::Error("WebGroupService::GetGroup()", ge.what());
					delete im;
					im = NULL;
					response().status(cppcms::http::response::internal_server_error);
				}

				catch (...)
				{
					util::Log::Error("WebGroupService::GetGroup()", "Unexpected exception");
					delete im;
					im = NULL;
					response().status(cppcms::http::response::internal_server_error);
				}
			}
			else if (request().request_method() == "DELETE")
			{
				deleteGroup(name);
			}
		}

		void GroupService::addUser()
		{
			if (request().request_method() == "PUT")
			{
				gc::business::IGroupService *im = gc::business::GcBusinessManager::getGroupService();
				try
				{
					std::pair<void *, size_t> data = request().raw_post_data();
					std::string postdata(reinterpret_cast<char *>(data.first), data.second);

					std::istringstream iss(postdata);
					cppcms::json::value val1;
					val1.load(iss, true);
					string ip = request().remote_addr();
					if (!Authenticator::isAuthenticated(postdata, ip))
					{
						response().status(cppcms::http::response::bad_request);
						return;
					}
					UserSecurity us(val1.get<std::string>("encoded_string"));
					std::pair<std::string, std::string> AU_IP;
					AU_IP.first = us.getAuthToken();
					AU_IP.second = ip;
					gc::entities::OnlineUsers *o = gc::entities::OnlineUsers::getInstance();
					std::string email = o->fetchEmail(AU_IP);

					if (email == "")
					{
						response().status(cppcms::http::response::bad_request);
						return;
					}

					//	val1.load(iss,true);
					im->addMember(val1.get<std::string>("name"), val1.get<std::string>("email"));

					response().status(cppcms::http::response::ok);
					util::Log::Info("Web Group Service", "Group service Instance successfully Created and user created into the system");
					im = NULL;
				}

				catch (cppcms::json::bad_value_cast e)
				{
					util::Log::Error("Web Group Service", "invalid json data (not an object)");
					response().status(cppcms::http::response::no_content);
				}

				catch (gc::business::BusinessQueryException &bqe)
				{
					util::Log::Error("WebGroupService::AddUser()", bqe.what());
					im = NULL;
					response().status(cppcms::http::response::conflict);
				}

				catch (gc::business::BusinessConnectionException &bce)
				{
					util::Log::Error("WebGroupService::AddUser()", bce.what());
					im = NULL;
					response().status(cppcms::http::response::service_unavailable);
				}

				catch (gc::GCException &ge)
				{
					util::Log::Error("WebGroupService::AddUser()", ge.what());
					im = NULL;
					response().status(cppcms::http::response::internal_server_error);
				}

				catch (...)
				{
					util::Log::Error("WebGroupService::AddUser()", "Unexpected exception");
					im = NULL;
					response().status(cppcms::http::response::internal_server_error);
				}
			}
			else
				response().status(cppcms::http::response::method_not_allowed);
		}

		void GroupService::removeUser()
		{
			if (request().request_method() == "DELETE")
			{
				gc::business::IGroupService *im = gc::business::GcBusinessManager::getGroupService();

				try
				{
					std::pair<void *, size_t> data = request().raw_post_data();
					std::string postdata(reinterpret_cast<char *>(data.first), data.second);

					std::istringstream iss(postdata);

					string ip = request().remote_addr();
					if (!Authenticator::isAuthenticated(postdata, ip))
					{
						response().status(cppcms::http::response::bad_request);
						return;
					}

					cppcms::json::value val1;
					val1.load(iss, true);

					UserSecurity us(val1.get<std::string>("encoded_string"));
					std::pair<std::string, std::string> AU_IP;
					AU_IP.first = us.getAuthToken();
					AU_IP.second = ip;
					gc::entities::OnlineUsers *o = gc::entities::OnlineUsers::getInstance();
					std::string email = o->fetchEmail(AU_IP);
					if (email == "")
					{
						response().status(cppcms::http::response::bad_request);
						return;
					}

					im->removeMember(val1.get<std::string>("name"), val1.get<std::string>("email"));
					response().status(cppcms::http::response::ok);
					util::Log::Info("Web Group Service", "Group service Instance successfully Created and user deleted from the system");
					im = NULL;
				}

				catch (cppcms::json::bad_value_cast e)
				{
					util::Log::Error("Web Group Service", "invalid json data (not an object)");
					response().status(cppcms::http::response::no_content);
				}

				catch (gc::business::BusinessQueryException &bqe)
				{
					util::Log::Error("WebGroupService::RemoveUser()", bqe.what());
					im = NULL;
					response().status(cppcms::http::response::conflict);
				}

				catch (gc::business::BusinessConnectionException &bce)
				{
					util::Log::Error("WebGroupService::removeUser()", bce.what());
					im = NULL;
					response().status(cppcms::http::response::service_unavailable);
				}

				catch (gc::GCException &ge)
				{
					util::Log::Error("WebGroupService::removeUser()", ge.what());
					im = NULL;
					response().status(cppcms::http::response::internal_server_error);
				}

				catch (...)
				{
					util::Log::Error("WebGroupService::removeUser()", "Unexpected exception");
					im = NULL;
					response().status(cppcms::http::response::internal_server_error);
				}
			}
			else
				response().status(cppcms::http::response::method_not_allowed);
		}

		void GroupService::deleteGroup(std::string name)
		{
			if (request().request_method() == "DELETE")
			{
				gc::business::IGroupService *im = gc::business::GcBusinessManager::getGroupService();

				try
				{
					std::pair<void *, size_t> data = request().raw_post_data();
					std::string postdata(reinterpret_cast<char *>(data.first), data.second);
					cppcms::json::value val1;

					std::istringstream iss(postdata);
					val1.load(iss, true);

					string ip = request().remote_addr();
					if (!Authenticator::isAuthenticated(postdata, ip))
					{
						response().status(cppcms::http::response::bad_request);
						return;
					}
					UserSecurity us(val1.get<std::string>("encoded_string"));
					std::pair<std::string, std::string> AU_IP;
					AU_IP.first = us.getAuthToken();
					AU_IP.second = ip;
					gc::entities::OnlineUsers *o = gc::entities::OnlineUsers::getInstance();
					std::string email = o->fetchEmail(AU_IP);
					if (email == "")
					{
						response().status(cppcms::http::response::bad_request);
						return;
					}

					im->deleteGroup(name);
					response().status(cppcms::http::response::ok);
					util::Log::Info("Web Group Service", "Group service Instance successfully Created and user deleted from the system");
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

	} // namespace web
} // namespace gc
