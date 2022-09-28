.PHONY:clean localinstall all debug debugBuild release releaseBuild buildMain

OUTPUT_OPTION =  -MMD -MP -o $@

SOURCES		+= DataColumn.cpp
SOURCES		+= DBFactory.cpp
SOURCES		+= IDBConnect.cpp
SOURCES		+= Schema.cpp
SOURCES		+= SQLiteWrapper.cpp
SOURCES		+= DataTable.cpp
SOURCES		+= DBManager.cpp
SOURCES		+= OracleDB.cpp
SOURCES		+= SQLiteDB.cpp
#SOURCES	 += MySqlDB.cpp
SOURCES		+= DBBadCastException.cpp
SOURCES		+= DBConfigFileException.cpp
SOURCES		+= DBDataColumnException.cpp
SOURCES		+= DBDataRowException.cpp
SOURCES		+= DBDataTableException.cpp
SOURCES		+= DBObjectException.cpp
SOURCES 	+= DBConnectionException.cpp
SOURCES		+= DBQueryException.cpp

DB_CONFIG	:= $(PROJECT_ROOT)/config/dbconfig.json
LOG_DB		:= $(PROJECT_ROOT)/data/log.db


OBJS          =  $(SOURCES:.cpp=.o)
DEPS          =  $(SOURCES:.cpp=.d)

LIBNAME       =  libdb.so

LDFLAGS       += -L$(BIN_DIR) -L$(ORACLE_LIB) -shared -fPIC
LDLIBS        += -lsqlite3 -lclntsh -lboost_system -lboost_thread
CXXFLAGS      += -fPIC -I$(EXP_PUB_INC) -I$(DBF_INC) -I$(ORACLE_INC)


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


$(LIBNAME): $(OBJS) $(EXPOBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

localinstall:
	- @cp $(LIBNAME)   $(BIN_DIR) > /dev/null 2>&1 || true
	- @cp $(DB_CONFIG) $(BIN_DIR) > /dev/null 2>&1 || true
	- @cp $(LOG_DB)    $(BIN_DIR) > /dev/null 2>&1 || true

clean:
	-@rm *.o >  /dev/null 2>&1 || true
	-@rm $(LIBNAME) > /dev/null 2>&1 || true
	-@rm *.d >  /dev/null 2>&1 ||  true
