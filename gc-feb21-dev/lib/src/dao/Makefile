.PHONY:clean localinstall all debug debugBuild release releaseBuild buildMain

OUTPUT_OPTION 	=  -MMD -MP -o $@

# Sources files
SOURCES			+= DAOManager.cpp
SOURCES			+= IGroupServiceDAO.cpp
SOURCES			+= IUserServiceDAO.cpp
SOURCES			+= MessageServiceDAO.cpp
SOURCES			+= GroupServiceDAO.cpp
SOURCES			+= IMessageServiceDAO.cpp
SOURCES			+= UserServiceDAO.cpp
SOURCES			+= DAOAuthenticationException.cpp
SOURCES			+= DAOConnectionException.cpp
SOURCES			+= DAOInstanceException.cpp
SOURCES			+= DAOProfileException.cpp
SOURCES			+= DAOQueryException.cpp


OBJS			=  $(SOURCES:.cpp=.o)
DEPS          	=  $(SOURCES:.cpp=.d)

LIBNAME       	=  libdao.so

LDFLAGS       	+= -L$(BIN_DIR) -L$(ORACLE_LIB) -shared -fPIC
LDLIBS        	+= -ldb -lsqlite3 -lclntsh -lboost_system -llog -lentities
CXXFLAGS      	+= -fPIC -I$(ENTITIES_PUB_INC) -I$(DBF_INC) -I$(DAO_INC) -I$(ORACLE_INC) -I$(LOG_PUB_INC) -I$(EXP_PUB_INC)

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

$(LIBNAME): $(OBJS) $(EXPOBJS) $(CEOBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)


localinstall:
	-@cp $(LIBNAME) $(BIN_DIR) > /dev/null 2>&1 || true
			
clean: 
	-@rm *.o > 			/dev/null 2>&1 || true
	-@rm $(LIBNAME) > 	/dev/null 2>&1 || true 
	-@rm *.d > 			/dev/null 2>&1 || true 	
