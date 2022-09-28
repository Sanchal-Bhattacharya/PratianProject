#include <cppcms/service.h>
#include <cppcms/applications_pool.h>
#include <cppcms/application.h>
#include <cppcms/http_response.h>
#include <cppcms/json.h>
#include <iostream>
#include <sstream>
#include "WebService.h"
#include "UserService.h"
#include "GroupService.h"
#include "MessageService.h"
using namespace std;

int main(int argc,char **argv)
{
	try {
		cppcms::service srv(argc,argv);
        srv.applications_pool().mount(cppcms::applications_factory<gc::web::WebService>());
        srv.run();
	}
	catch(std::exception const &exception) {
		std::cerr<<exception.what()<<std::endl;
	}
}

