include Makefile.inc

.DEFAULT_GOAL: all
all:
	@echo "Building GLOBAL CONNECT"
	$(MAKE) debug -C $(ENTITIES_DIR)
	$(MAKE) debug -C $(UTILS_DIR)
	$(MAKE) debug -C $(DBF_DIR)
	$(MAKE) debug -C $(DAO_DIR)
	$(MAKE) debug -C $(BUSINESS_DIR)
	$(MAKE) debug -C $(APPSERVER_DIR)

debug:
	$(MAKE) debug -C $(ENTITIES_DIR)
	$(MAKE) debug -C $(UTILS_DIR)
	$(MAKE) debug -C $(DBF_DIR)
	$(MAKE) debug -C $(DAO_DIR)
	$(MAKE) debug -C $(BUSINESS_DIR)
	$(MAKE) debug -C $(APPSERVER_DIR)

release:
	$(MAKE) release -C $(ENTITIES_DIR)
	$(MAKE) release -C $(UTILS_DIR)
	$(MAKE) release -C $(DBF_DIR)
	$(MAKE) release -C $(DAO_DIR)
	$(MAKE) release -C $(BUSINESS_DIR)
	$(MAKE) release -C $(APPSERVER_DIR)

clean:
	-@ rm -rf bin > /dev/null 2>&1 || true
	-@ mkdir bin > /dev/null 2>&1 || true
	-@ cp scripts/_gitignore.bin bin/.gitignore > /dev/null 2>&1 || true 
	-@ rm -rf /opt/gcApp > /dev/null 2>&1 || true
	$(MAKE) clean -C $(ENTITIES_DIR)
	$(MAKE) clean -C $(UTILS_DIR)
	$(MAKE) clean -C $(DBF_DIR)
	$(MAKE) clean -C $(DAO_DIR)
	$(MAKE) clean -C $(BUSINESS_DIR)
	$(MAKE) clean -C $(APPSERVER_DIR)


install:
	./install.sh

	
