.PHONY:clean localinstall all debug release debugBuild releaseBuild buildMain

OUTPUT_OPTION =  -MMD -MP -o $@

#SOURCES		=  $(wildcard *.cpp)
EXP_DIR			= ExceptionFramework
MSGSVC_DIR		= MessageService
GRPSVC_DIR		= GroupService
USERSVC_DIR		= UserService

SOURCES			+= $(EXP_DIR)/BusinessAuthenticationException.cpp
SOURCES			+= $(EXP_DIR)/BusinessConnectionException.cpp
SOURCES			+= $(EXP_DIR)/BusinessInstanceException.cpp
SOURCES			+= $(EXP_DIR)/BusinessProfileException.cpp
SOURCES			+= $(EXP_DIR)/ConnectionIdNotFound.cpp
SOURCES			+= $(EXP_DIR)/BusinessQueryException.cpp
SOURCES			+= GcBusinessManager.cpp
SOURCES			+= $(GRPSVC_DIR)/GroupService.cpp
SOURCES			+= $(GRPSVC_DIR)/IGroupService.cpp
SOURCES			+= $(MSGSVC_DIR)/ConnectionCache.cpp
SOURCES			+= $(MSGSVC_DIR)/ConnectionObserver.cpp
SOURCES			+= $(MSGSVC_DIR)/ConnectionObserverFactory.cpp
SOURCES			+= $(MSGSVC_DIR)/GroupConnectionCache.cpp
SOURCES			+= $(MSGSVC_DIR)/IConnectionObserver.cpp
SOURCES			+= $(MSGSVC_DIR)/IMessageService.cpp
SOURCES			+= $(MSGSVC_DIR)/MQueue.cpp
SOURCES			+= $(MSGSVC_DIR)/MQueueManager.cpp
SOURCES			+= $(MSGSVC_DIR)/MessageService.cpp
SOURCES			+= $(USERSVC_DIR)/IUserService.cpp
SOURCES			+= $(USERSVC_DIR)/UserService.cpp

OBJS			=  $(SOURCES:.cpp=.o)
DEPS			=  $(SOURCES:.cpp=.d)

LIBNAME			=  libbusiness.so

GRPSVC_INC		= $(BUSINESS_INC_DIR)/GroupService
USERSVC_INC		= $(BUSINESS_INC_DIR)/UserService
MESSAGESVC_INC	= $(BUSINESS_INC_DIR)/MessageService
EXP_INC			= $(BUSINESS_INC_DIR)/ExceptionFramework

LDFLAGS			+= -L$(BIN_DIR) -L$(ORACLE_LIB) -shared -fPIC
LDLIBS			+= -llog -ldao -lentities -ldb -lsqlite3 -lclntsh -lboost_system
CXXFLAGS		+= -fPIC -I$(GRPSVC_INC) -I$(USERSVC_INC) -I$(MESSAGESVC_INC) -I$(EXP_INC) -I$(DAO_INC) 
CXXFLAGS		+= -I$(LOG_PUB_INC) -I$(DAO_INC) -I$(ENTITIES_PUB_INC) -I$(EXP_PUB_INC) -I$(COMMON_INC)
CXXFLAGS		+= -I$(BUSINESS_PUB_INC)

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

buildMain: $(LIBNAME) localinstall

-include $(DEPS)

$(LIBNAME): $(OBJS) 
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

localinstall: $(LIBNAME)
	-@cp $(LIBNAME) $(BIN_DIR) > /dev/null 2>&1 || true

clean:
	-@rm *.o > 					/dev/null 2>&1 || true
	-@rm *.d > 					/dev/null 2>&1 || true
	-@rm $(EXP_DIR)/*.o > 		/dev/null 2>&1 || true
	-@rm $(GRPSVC_DIR)/*.o >	/dev/null 2>&1 || true
	-@rm $(MSGSVC_DIR)/*.o > 	/dev/null 2>&1 || true
	-@rm $(USERSVC_DIR)/*.o > 		/dev/null 2>&1 || true
	-@rm $(EXP_DIR)/*.d > 		/dev/null 2>&1 || true
	-@rm $(GRPSVC_DIR)/*.d >	/dev/null 2>&1 || true
	-@rm $(MSGSVC_DIR)/*.d > 	/dev/null 2>&1 || true
	-@rm $(USERSVC_DIR)/*.d > 		/dev/null 2>&1 || true
	-@rm $(LIBNAME) > 			/dev/null 2>&1 || true
	
