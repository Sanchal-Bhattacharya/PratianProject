#include <iostream>

#include <boost/lexical_cast.hpp>

#include <cppcms/http_response.h>
#include <cppcms/http_request.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>

#include "Message.h"
#include "GcBusinessManager.h"
#include "IMessageService.h"
#include "MessageService.h"
#include "ConnectionIdNotFound.h"
#include "UserService.h"
#include "Authenticator.h"

#include "BusinessQueryException.h"
#include "BusinessConnectionException.h"

#include "Log.h"

using namespace std;
void printMsg( gc::entities::Message & msg )
{
	 	  msg.getMessage() << "  " <<  msg.getMessageType() << "  " <<  msg.getAckStatus() << endl;
	 cout << msg.getToId() << "  " << msg.getFromId() << "  " <<  msg.getMsgId() << "  " <<
}

namespace cppcms
{
	namespace json
	{

		template <>
		struct traits<gc::entities::Message *>
		{

			static gc::entities::Message *get(value const &v)
			{
				if (v.type() != is_object)
					throw bad_value_cast();

				gc::entities::Message *msg = new gc::entities::Message(v.get<int>("MsgId"), v.get<std::string>("ToId"), v.get<std::string>("FromId"),
																	   v.get<std::string>("Msg"), v.get<int>("Type"), v.get<int>("Ack"));
				return msg;
			}

			static void set(value &v, gc::entities::Message *const &in)
			{
				v.set("MsgId", in->getMsgId());
				v.set("ToId", in->getToId());
				v.set("FromId", in->getFromId());
				v.set("Msg", in->getMessage());
				v.set("Ack", in->getAckStatus());
				v.set("Type", in->getMessageType());
			}
		};
	} // namespace json
} // namespace cppcms

namespace gc
{
	namespace web
	{

		MessageService::MessageService(cppcms::service &srv)
			: cppcms::application(srv)
		{

			dispatcher().assign("/users", &MessageService::sendMessage, this);
			dispatcher().assign("/users/", &MessageService::sendMessage, this);
			mapper().assign("users", "/users");

			dispatcher().assign("/users/(.*)", &MessageService::retrieveMessage, this, 1);
			mapper().assign("users", "/users");
			dispatcher().assign("/groups", &MessageService::sendMessageToGroup, this);
			dispatcher().assign("/groups/", &MessageService::sendMessageToGroup, this);
			mapper().assign("groups", "/groups");

			dispatcher().assign("/groups/(.*)", &MessageService::retrieveMessageFromGroups, this, 1);
			mapper().assign("groups", "/groups");

			dispatcher().assign("/forwardmessage",&MessageService::messageHandler,this);
			dispatcher().assign("/forwardmessage/",&MessageService::messageHandler,this);
			mapper().assign("forwardmessage","/forwardmessage");
		}
		
		void MessageService::messageHandler()
		{
			if(requests().request_method()=="PUT")
			{
				forwardMessage();
			}
			else
			{
				response().status(cppcms::http::response::not_implemented);
			}
		}
		
		void MessageService::retrieveMessage(std::string email)
		{

			if (request().request_method() == "GET")
			{
				try
				{
					std::pair<void *, size_t> data = request().raw_post_data();
					std::string postdata(reinterpret_cast<char *>(data.first), data.second);
					std::string ip = request().remote_addr();

					if (!Authenticator::isAuthenticated(postdata, ip))
					{
						response().status(cppcms::http::response::unauthorized);
						return;
					}
					gc::business::IMessageService *im = gc::business::GcBusinessManager::getMessageService();
					std::vector<gc::entities::Message *> message = im->removeMessage(email);
					cppcms::json::array my_json;
					for (int i = 0; i < message.size(); i++)
					{
						cppcms::json::value val1;
						val1.set_value(message[i]);
						my_json.push_back(val1);
						printMsg(*message[i]);
						//delete message[i];
						message[i] = NULL;
					}

					response().content_type("application/json");
					response().out() << my_json;
					util::Log::Info("Web", "<MessageService>removed message : " + boost::lexical_cast<string>(message.size()));
				}

				catch (business::ConnectionIdNotFound &cid)
				{
					util::Log::Error("GCMessageService::getMessage()", cid.what());
					response().status(cppcms::http::response::not_found);
				}

				catch (GCException &gc)
				{
					util::Log::Error("GCMessageService::getMessage()", gc.what());
					response().status(cppcms::http::response::internal_server_error);
				}

				catch (...)
				{
					util::Log::Error("GCUserService::GetUser()", "Uncaught exception");
					response().status(cppcms::http::response::internal_server_error);
				}
			}
		}

		void MessageService::sendMessage()
		{

			gc::business::IMessageService *im = gc::business::GcBusinessManager::getMessageService();
			
			

			if (request().request_method() == "PUT")
			{
				try
				{

					std::pair<void *, size_t> data = request().raw_post_data();
					std::string postdata(reinterpret_cast<char *>(data.first), data.second);
					
					std::string ip = request().remote_addr();
					if (!Authenticator::isAuthenticated(postdata, ip))
					{
						response().status(cppcms::http::response::unauthorized);
						return;
					}

					std::stringstream ss(postdata);
					cppcms::json::value v1;

					bool val = v1.load(ss, true);

					if (v1.type() != cppcms::json::is_object)
						util::Log::Error("Web", "<MessageService>invalid json data (not an object)");

					gc::entities::Message *obj = NULL;

					try
					{
						obj = v1.get_value<gc::entities::Message *>();
					}
					catch (cppcms::json::bad_value_cast e)
					{
						util::Log::Error("Web", "<MessageService>invalid json data (cast exception)");
					}
					catch (...)
					{
						util::Log::Error("Web", "<MessageService>Unknown Exception");
					}

					if (obj == NULL)
					{
						response().status(cppcms::http::response::not_found);
					}
					else
					{
						im->addMessage(obj);
					}
					delete im;
					//donot deallocate message
					obj = NULL;

					util::Log::Info("Web", "<MessageService>posted a message");
				}

				catch (business::BusinessQueryException &bq)
				{
					util::Log::Error("GCMessageService::putMessage()", bq.what());
					response().status(cppcms::http::response::conflict);
				}

				catch (GCException &gc)
				{
					util::Log::Error("GCMessageService::putMessage()", gc.what());
					response().status(cppcms::http::response::internal_server_error);
					//500
				}

				catch (...)
				{
					util::Log::Error("GCUserService::putMessage()", "Uncaught exception");
					response().status(cppcms::http::response::internal_server_error);
				}
			}
		}

		void MessageService::forwardMessage()
		{
			
		}
		void MessageService::retrieveMessageFromGroups(std::string email)
		{

			if (request().request_method() == "GET")
			{
				try
				{
					std::pair<void *, size_t> data = request().raw_post_data();
					std::string postdata(reinterpret_cast<char *>(data.first), data.second);
					std::string ip = request().remote_addr();

					if (!Authenticator::isAuthenticated(postdata, ip))
					{
						response().status(cppcms::http::response::bad_request);
						return;
					}

					gc::business::IMessageService *im = gc::business::GcBusinessManager::getMessageService();
					std::vector<gc::entities::Message *> message = im->removeMessagesFromGroups(email);
					cppcms::json::array my_json;
					for (int i = 0; i < message.size(); i++)
					{
						cppcms::json::value val1;
						val1.set_value(message[i]);
						my_json.push_back(val1);
						//printMsg(*message[i]);
						delete message[i];
						message[i] = NULL;
					}

					response().content_type("application/json");
					response().out() << my_json;
					util::Log::Info("Web", "<MessageService>removed message : " + boost::lexical_cast<string>(message.size()));
				}

				catch (business::ConnectionIdNotFound &cid)
				{
					util::Log::Error("GCMessageService::getMessage()", cid.what());
					response().status(cppcms::http::response::not_found);
				}

				catch (GCException &gc)
				{
					util::Log::Error("GCMessageService::getMessage()", gc.what());
					response().status(cppcms::http::response::internal_server_error);
				}

				catch (...)
				{
					util::Log::Error("GCUserService::GetUser()", "Uncaught exception");
					response().status(cppcms::http::response::internal_server_error);
				}
			}
		}

		void MessageService::sendMessageToGroup()
		{

			gc::business::IMessageService *im = gc::business::GcBusinessManager::getMessageService();
			if (request().request_method() == "PUT")
			{
				try
				{

					std::pair<void *, size_t> data = request().raw_post_data();
					std::string postdata(reinterpret_cast<char *>(data.first), data.second);
					std::string ip = request().remote_addr();
					if (!Authenticator::isAuthenticated(postdata, ip))
					{
						response().status(cppcms::http::response::bad_request);
						return;
					}

					std::stringstream ss(postdata);
					cppcms::json::value v1;

					bool val = v1.load(ss, true);

					if (v1.type() != cppcms::json::is_object)
						util::Log::Error("Web", "<MessageService>invalid json data (not an object)");

					gc::entities::Message *obj = NULL;

					try
					{

						obj = v1.get_value<gc::entities::Message *>();
					}
					catch (cppcms::json::bad_value_cast e)
					{
						util::Log::Error("Web", "<MessageService>invalid json data (cast exception)");
					}
					catch (...)
					{
						util::Log::Error("Web", "<MessageService>Unknown Exception");
					}

					if (obj == NULL)
					{
						response().status(cppcms::http::response::not_found);
					}
					else
					{
						util ::Log ::Error(obj->getFromId(), obj->getToId());
						im->addMessageToGroup(obj);
					}
					delete im;
					//donot deallocate message
					obj = NULL;

					util::Log::Info("Web", "<MessageService>posted a message");
				}

				catch (business::BusinessQueryException &bq)
				{
					util::Log::Error("GCMessageService::putMessage()", bq.what());
					response().status(cppcms::http::response::conflict);
				}

				catch (GCException &gc)
				{
					util::Log::Error("GCMessageService::putMessage()", gc.what());
					response().status(cppcms::http::response::internal_server_error);
					//500
				}

				catch (...)
				{
					util::Log::Error("GCUserService::putMessage()", "Uncaught exception");
					response().status(cppcms::http::response::internal_server_error);
				}
			}
		}
	} // namespace web
} // namespace gc
