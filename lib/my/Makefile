### DO NOT EDIT, for project settings, see 'settings.mk' ###

-include definitions.mk

$(call retrieve_config)

### RULES ###

all:
	@if make -sq $(TARGET) $(TEST_TARGET); then  \
		echo "make: Nothing to be done for 'all'"; \
	else \
		make -sq $(TARGET) || make -j $(PARALLEL_JOBS) -Oline --no-print-directory $(TARGET); \
		make -sq $(TEST_TARGET) || make -j $(PARALLEL_JOBS) -Oline --no-print-directory $(TEST_TARGET); \
	fi

$(TARGET): $(OBJS_DIRS) $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

$(TEST_TARGET): $(TEST_OBJS_DIRS) $(TEST_OBJS)
	$(CC) $(CMACROS) $(TEST_CFLAGS) $(CPPFLAGS) $(TEST_CLIBS) $(TEST_OBJS) -o $@

$(OBJS_DIRS) $(TEST_OBJS_DIRS):
	$(MKDIR) $@

# main object files
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCS)
	$(CC) $(CMACROS) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# object files for testing targets
$(TEST_OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCS)
	$(CC) $(CMACROS) $(CPPFLAGS) $(TEST_CFLAGS) $(TEST_CLIBS) -c $< -o $@

# object files for testing functions
$(TEST_OBJ_PATH)/%.o: $(TEST_PATH)/%.c $(INCS)
	$(CC) $(CMACROS) $(CPPFLAGS) $(UNIT_TEST_CFLAGS) $(TEST_CLIBS) -c $< -o $@

clean:
	$(RM) $(OBJS) 2> /dev/null || true
	$(RM) $(TEST_OBJS) 2> /dev/null || true
	$(RM) $(TEST_OBJS:.o=.gcda) 2> /dev/null || true
	$(RM) $(TEST_OBJS:.o=.gcno) 2> /dev/null || true
	$(RMDIR) $(OBJS_DIRS) 2> /dev/null || true
	$(RMDIR) $(TEST_OBJS_DIRS) 2> /dev/null || true

fclean: clean
	$(RM) $(TARGET) 2> /dev/null || true
	$(RM) $(TEST_TARGET) 2> /dev/null || true
	make -C config fclean

re: fclean before_all all

before_all:
	make -C config re $(CONFIG)

docs: $(INCS)
	(cd $(DOC_PATH) && doxygen)

docs_open:
	$(OPEN_DOCS) $(DOC_PATH)/html/index.html > /dev/null

coverage:
	$(COVERAGE) $(TEST_OBJ_PATH)
	$(COVERAGE) --branch $(TEST_OBJ_PATH)

tests_run:
	@make -sq $(TEST_TARGET) || make -j $(PARALLEL_JOBS) -Oline --no-print-directory $(TEST_TARGET);
	@$(RM) $(TEST_OBJS:.o=.gcda) 2> /dev/null || true
	./$(TEST_TARGET) --filter="$(filter)*"

run_tests: tests_run

.PHONY: before_all all fclean clean re before_all tests_run run_tests
