.PHONY:clean localinstall all debug debugBuild release releaseBuild buildMain

OUTPUT_OPTION =  -MMD -MP -o $@

SOURCES       =  $(wildcard *.cpp)
OBJS          =  $(SOURCES:.cpp=.o)
DEPS          =  $(SOURCES:.cpp=.d)

LIBNAME       =  liblog.so
LOGCONFIG     =  $(PROJECT_ROOT)/config/logconfig.json

LDFLAGS       += -L$(BIN_DIR) -L$(ORACLE_LIB) -shared -fPIC
LDLIBS        += -lboost_date_time
CXXFLAGS      += -fPIC -I$(LOG_INC) -I$(LOG_PUB_INC) -I$(ENTITIES_PUB_INC) -I$(DAO_INC) -I$(DBF_INC) -I$(ORACLE_INC) -I$(EXP_PUB_INC) -I$(COMMON_INC)

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

$(LIBNAME): $(OBJS) $(LOGEXPOBJ) $(CEXPOBJ)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

localinstall:
	-@ cp $(LIBNAME) 	$(BIN_DIR) > /dev/null 2>&1 || true
	-@ cp $(LOGCONFIG)  $(BIN_DIR) > /dev/null 2>&1 || true

#clean	
clean:
	-@ rm *.o 			> 	/dev/null 2>&1 || true
	-@ rm $(LIBNAME) 	> 	/dev/null 2>&1 || true
	-@ rm *.d 			> 	/dev/null 2>&1 || true
