.PHONY:test clean install debug default release
LOG_DIR		:= $(UTILS_DIR)/log

.DEFAULT_GOAL: all
all:
	$(MAKE) debug -C $(LOG_DIR)

debug:
	$(MAKE) debug -C $(LOG_DIR)

release:
	$(MAKE) release -C $(LOG_DIR)

clean:
	$(MAKE) clean -C $(LOG_DIR)
	-@ rm *.so > /dev/null 2>&1 || true
