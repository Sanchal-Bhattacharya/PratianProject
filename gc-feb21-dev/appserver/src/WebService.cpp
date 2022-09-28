#include <cppcms/http_response.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>
#include <cppcms/json.h>
#include "UserService.h"
#include "GroupService.h"
#include "MessageService.h"
#include "User.h"

#include "WebService.h"

namespace gc
{
	namespace web
	{
		WebService::WebService(cppcms::service &srv)
			: cppcms::application(srv)
		{
			attach(new UserService(srv), "userservice", "/userservice{1}", "/userservice(/(.*))?", 1);

			attach(new MessageService(srv), "messageservice", "/messageservice{1}", "/messageservice(/(.*))?", 1);

			attach(new GroupService(srv), "groupservice", "/groupservice{1}", "/groupservice(/(.*))?", 1);
			mapper().root("/gc");
		}
	} // namespace web
} // namespace gc
