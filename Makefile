# Basic Project Properties
SRC_PATH := src
OBJ_PATH := bin
INC_PATH := include

# LibMy
LIBMY_PATH := lib/my
LIBMY_MODULES := core ascii io memory parsing printf
LIBMY_FLAGS := allow_malloc allow_open allow_read allow_write
LIBMY := $(LIBMY_PATH)/libmy.a

# Compiler Flags
CPPFLAGS := -iquote include
CFLAGS := -Wall -Wextra -Werror -Wshadow -Og -g
CLIBS := -L$(LIBMY_PATH) -lmy

# Sources
SRCS_BASE := \
main.c       \

INCS_BASE := \

SRCS := $(addprefix $(SRC_PATH)/, $(SRCS_BASE))
OBJS := $(addprefix $(OBJ_PATH)/, $(SRCS_BASE:.c=.o))
INCS := $(addprefix $(INC_PATH)/, $(INCS_BASE))
OBJS_DIRS := $(sort $(dir $(OBJS)))

# Commands
CC := gcc
RM := rm -f
RMDIR := rmdir -p
MKDIR := mkdir -p
LIBMY_CONFIG := $(LIBMY_PATH)/libmy-config

TARGET=mysh

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

all: $(TARGET)

$(OBJS_DIRS):
	$(MKDIR) $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCS)
	$(call retrieve_libmy_properties)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

$(LIBMY):
	make -C $(LIBMY_PATH) MODULES="$(LIBMY_MODULES)" FLAGS="$(LIBMY_FLAGS)"

$(TARGET): $(LIBMY) $(OBJS_DIRS) $(OBJS)
	$(call retrieve_libmy_properties)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $(OBJS) $(CLIBS)

clean:
	$(RM) $(OBJS)
	$(RMDIR) $(OBJ_PATH) || true 2> /dev/null
	make -C $(LIBMY_PATH) clean

fclean: clean
	$(RM) $(TARGET)
	make -C $(LIBMY_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
