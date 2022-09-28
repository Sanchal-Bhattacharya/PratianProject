.PHONY:clean localinstall all debug debugBuild release releaseBuild buildMain

OUTPUT_OPTION =  -MMD -MP -o $@

SOURCES		=  $(wildcard *.cpp)
OBJS		=  $(SOURCES:.cpp=.o)
DEPS		=  $(SOURCES:.cpp=.d)

LIBNAME		=  libentities.so

CXXFLAGS	+= -fPIC
CXXFLAGS	+= -I$(ENTITIES_PUB_INC)
LDFLAGS		+= -shared -fPIC

all: debug

# debug
debug:debugBuild buildMain

debugBuild:
ifndef MKINC
	@echo "Pleas run the root Makefile!"
	@exit 1
endif
	$(eval CXXFLAGS += -Wall)

# release
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
	$(CXX) $(LDFLAGS) -o $@ $^

clean:
	-@ rm *.o >  /dev/null 2>&1 || true
	-@ rm $(LIBNAME) > /dev/null 2>&1 || true
	-@ rm *.d >  /dev/null 2>&1 || true

localinstall:
	-@ cp $(LIBNAME) $(BIN_DIR) > /dev/null 2>&1 || true

