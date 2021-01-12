TARGET := ../libmy-config

SRCS :=        \
get_endian.c   \
get_property.c \
main.c         \

CC := gcc
CFLAGS := -Wall -Werror -Wshadow -pedantic -O1
CMACROS := $(subst $(SPACE_PLACEHOLDER), ,$(addprefix -D , \
"CONFIG_DEFINES=\"$(CONFIG_DEFINES)\""                     \
"CONFIG_FLAGS=\"$(CONFIG_FLAGS)\""                         \
"CONFIG_INCLUDE_PATH=\"$(CONFIG_INCLUDE_PATH)\""           \
"CONFIG_LIBRARY_PATH=\"$(CONFIG_LIBRARY_PATH)\""           \
"CONFIG_MODULES=\"$(CONFIG_MODULES)\""                     \
"CONFIG_VERSION_MAJOR=\"$(CONFIG_VERSION_MAJOR)\""         \
"CONFIG_VERSION_MINOR=\"$(CONFIG_VERSION_MINOR)\""         \
"CONFIG_VERSION_PATCH=\"$(CONFIG_VERSION_PATCH)\""         \
))

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(CMACROS) $(SRCS) -o $@

clean:

fclean:
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean
