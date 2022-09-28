# .PHONY:clean localinstall all debug debugBuild release releaseBuild buildMain

OUTPUT_OPTION =  -MMD -MP -o $@

#SOURCES       =  $(wildcard *.cpp)

SOURCES			+= Authenticator.cpp
SOURCES			+= gcserver.cpp
SOURCES			+= GroupService.cpp
SOURCES			+= hash.cpp
SOURCES			+= MessageService.cpp
SOURCES			+= Random.cpp
SOURCES			+= UserSecurity.cpp
SOURCES			+= UserService.cpp
SOURCES			+= Validator.cpp
SOURCES			+= WebAuthenticationException.cpp
SOURCES			+= WebConnectionException.cpp
SOURCES			+= WebProfileException.cpp
SOURCES			+= WebService.cpp


OBJS          	=  $(SOURCES:.cpp=.o)
DEPS          	=  $(SOURCES:.cpp=.d)

APPNAME       	=  gcserver
APPSCRIPT	 	=  gcserver.sh
APPCONFIG     	=  $(CONFIG_DIR)/webconfig.js

GRPSVC_INC		= $(BUSINESS_INC_DIR)/GroupService
USERSVC_INC		= $(BUSINESS_INC_DIR)/UserService
MESSAGESVC_INC	= $(BUSINESS_INC_DIR)/MessageService
EXP_INC			= $(BUSINESS_INC_DIR)/ExceptionFramework

LDFLAGS       	+= -L$(BIN_DIR) -L$(ORACLE_LIB)
LDLIBS        	+= -lbusiness -llog -lentities -ldao -ldb -lsqlite3 -ldl -lcppcms -lclntsh -lboost_date_time -lboost_thread -lboost_system -lssl -lcrypto
CXXFLAGS      	+= -I$(APPSERVER_INC) -I$(GRPSVC_INC) -I$(USERSVC_INC) -I$(MESSAGESVC_INC) -I$(EXP_INC)
CXXFLAGS 		+= -I$(ENTITIES_PUB_INC) -I$(LOG_PUB_INC) -I$(EXP_PUB_INC) -I$(BUSINESS_PUB_INC)

all: debug

# debug
debug:debugBuild buildMain

debugBuild:
ifndef MKINC
	@echo "Pleas run the root Makefile!"
	@exit 1
endif
	$(eval CXXFLAGS += -Wall)

#release
release:releaseBuild buildMain

releaseBuild:
ifndef MKINC
	@echo "Pleas run the root Makefile!"
	@exit 1
endif
	$(eval CXXFLAGS += -O)

buildMain: $(APPNAME) localinstall

-include $(DEPS)

$(APPNAME): $(OBJS)
	@echo "Linking $(APPNAME)..."
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

#install
localinstall:
	-@ cp $(APPNAME)   $(BIN_DIR) > /dev/null 2>&1 || true
	-@ cp $(APPCONFIG) $(BIN_DIR) > /dev/null 2>&1 || true
	-@ cp $(APPSCRIPT) $(BIN_DIR) > /dev/null 2>&1 || true

#clean
clean:
	- @rm *.o > /dev/null 2>&1 || true
	- @rm $(APPNAME) > /dev/null 2>&1 || true
	- @rm *.d > /dev/null 2>&1 || true
