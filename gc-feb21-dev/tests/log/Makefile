.PHONY:clean all debug debugBuild release releaseBuild buildMain

OUTPUT_OPTION =  -MMD -MP -o $@

SOURCES       =  $(wildcard *.cpp)
OBJS          =  $(SOURCES:.cpp=.o)
DEPS          =  $(SOURCES:.cpp=.d)

APPNAME       =  LogErrorTest

LDFLAGS       += -L$(DBIN) -L$(ORACLE_LIB)
LDLIBS        += -lboost_system -ldb -llog -lcppunit -lsqlite3 -lclntsh
CXXFLAGS      += -c -I../

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

buildMain: $(APPNAME)

-include $(DEPS)

$(APPNAME): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@  $^ $(LDLIBS)

clean:
	-@ rm *.o > /dev/null 2>&1 || true
	-@ rm *.d > /dev/null 2>&1 || true
	-@ rm LogErrorTest > /dev/null 2>&1 || true
	-@ rm *.txt > /dev/null 2>&1 || true
	-@ rm *.xml > /dev/null 2>&1 || true
	-@ rm *.json > /dev/null 2>&1 || true
	-@ rm $(DBIN)/LogErrorTest > /dev/null 2>&1 || true
