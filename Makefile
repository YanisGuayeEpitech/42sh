# Basic Project Properties
SRC_PATH := src
TEST_PATH := tests
OBJ_PATH := bin
INC_PATH := include
DOC_PATH := doc
TEST_OBJ_PATH := bin/test

# LibMy
LIBMY_PATH := lib/my
LIBMY_MODULES := core ascii io memory parsing printf
LIBMY_FLAGS := allow_malloc allow_open allow_read allow_write
LIBMY := $(LIBMY_PATH)/libmy.a

# Compiler Flags
CPPFLAGS := -iquote include
CFLAGS := -Wall -Wextra -Werror -Wshadow -O1
DEBUG_CFLAGS := -Wall -Wextra -Og -g
UNIT_TEST_CFLAGS := -Wall -Wextra -Werror -Wshadow
TEST_CFLAGS := -Wall -Wextra -Werror -Wshadow \
-fprofile-arcs -ftest-coverage --coverage

CLIBS := -L$(LIBMY_PATH) -lmy
TEST_CLIBS := -lcriterion -lgcov -L$(LIBMY_PATH) -lmy

# Sources
SRCS_BASE :=       \
args.c             \
context.c          \
create_file_path.c \
env.c              \
error.c            \
parsing.c          \
read_line.c        \
reset_path.c       \
util.c             \

SRCS_OTHER :=      \
builtin/cd.c       \
builtin/dirs.c     \
builtin/env.c      \
builtin/exit.c     \
builtin/setenv.c   \
builtin/unsetenv.c \
builtin.c          \
cwd.c              \
exec.c             \
find_executable.c  \
main.c             \
print.c            \
start.c            \
status.c           \

INCS_BASE :=       \
builtin.h          \
context.h          \
definition.h       \
error.h            \
shell.h            \

TESTS_BASE := $(addprefix test_, $(SRCS_BASE))

SRCS := $(addprefix $(SRC_PATH)/, $(SRCS_BASE) $(SRCS_OTHER))
OBJS := $(addprefix $(OBJ_PATH)/, $(SRCS_BASE:.c=.o) $(SRCS_OTHER:.c=.o))
INCS := $(addprefix $(INC_PATH)/, $(INCS_BASE))
OBJS_DIRS := $(sort $(dir $(OBJS)))

TEST_OBJS := $(addprefix $(TEST_OBJ_PATH)/, $(TESTS_BASE:.c=.o) $(SRCS_BASE:.c=.o))
TEST_OBJS_DIRS := $(sort $(dir $(TEST_OBJS)))

# Commands
CC := gcc
OPEN_DOCS := xdg-open
RM := rm -f
RMDIR := rmdir -p
MKDIR := mkdir -p
LIBMY_CONFIG := $(LIBMY_PATH)/libmy-config
COVERAGE := gcovr

TARGET=mysh
TEST_TARGET=unit_tests

define retrieve_libmy_properties
$(eval
	ifndef LIBMY_DEFINED
		CFLAGS += $(addprefix -D , $(shell $(LIBMY_CONFIG) defines))
		TEST_CFLAGS += $(addprefix -D , $(shell $(LIBMY_CONFIG) defines))
		UNIT_TEST_CFLAGS += $(addprefix -D , $(shell $(LIBMY_CONFIG) defines))
		CPPFLAGS += -isystem $(shell $(LIBMY_CONFIG) include_path)
		LIBMY_DEFINED := 1
	endif
)
endef

all: $(TARGET) $(TEST_TARGET)

$(OBJS_DIRS) $(TEST_OBJS_DIRS):
	$(MKDIR) $@

# main object files
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCS)
	$(call retrieve_libmy_properties)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

# object files for testing targets
$(TEST_OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCS)
	$(call retrieve_libmy_properties)
	$(CC) $(CPPFLAGS) $(TEST_CFLAGS) $(TEST_CLIBS) -c -o $@ $<

# object files for testing functions
$(TEST_OBJ_PATH)/%.o: $(TEST_PATH)/%.c $(INCS)
	$(call retrieve_libmy_properties)
	$(CC) $(CPPFLAGS) $(UNIT_TEST_CFLAGS) $(TEST_CLIBS) -c -o $@ $<

$(LIBMY):
	make -C $(LIBMY_PATH) MODULES="$(LIBMY_MODULES)" FLAGS="$(LIBMY_FLAGS)"

$(TARGET): $(LIBMY) $(OBJS_DIRS) $(OBJS)
	$(call retrieve_libmy_properties)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $(OBJS) $(CLIBS)

$(TEST_TARGET): $(LIBMY) $(TEST_OBJS_DIRS) $(TEST_OBJS)
	$(call retrieve_libmy_properties)
	$(CC) $(TEST_CFLAGS) $(CPPFLAGS) -o $@ $(TEST_OBJS) $(TEST_CLIBS)

debug: CFLAGS += $(DEBUG_CFLAGS)
debug: all

clean:
	$(RM) $(OBJS)
	$(RM) $(TEST_OBJS)
	$(RM) $(TEST_OBJS:.o=.gcda)
	$(RM) $(TEST_OBJS:.o=.gcno)
	$(RMDIR) $(TEST_OBJ_PATH) || true 2> /dev/null
	$(RMDIR) $(OBJ_PATH) || true 2> /dev/null
	make -C $(LIBMY_PATH) clean

fclean: clean
	$(RM) $(TARGET)
	$(RM) $(TEST_TARGET)
	make -C $(LIBMY_PATH) fclean

docs:
	(cd $(DOC_PATH) && doxygen)

docs_open:
	$(OPEN_DOCS) $(DOC_PATH)/html/index.html > /dev/null

coverage:
	make -C $(LIBMY_PATH) coverage
	$(COVERAGE) $(OBJ_PATH)
	$(COVERAGE) --branch $(OBJ_PATH)

tests_run: $(TEST_TARGET)
	$(call retrieve_libmy_properties)
	@$(RM) $(TEST_OBJS:.o=.gcda) 2> /dev/null || true
	make -C $(LIBMY_PATH) MODULES="$(LIBMY_MODULES)" FLAGS="$(LIBMY_FLAGS)" tests_run
	./$(TEST_TARGET) --filter="$(filter)*"

test_run: tests_run

run_tests: tests_run

run_test: tests_run

re: fclean all

.PHONY: all debug clean fclean re docs docs_open coverage tests_run test_run run_tests run_test
