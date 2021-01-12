MODULE_NAME := ascii
MODULE_DEPS := core memory

MODULE_SRCS :=         \
my_revstr.c            \
my_strcapitalize.c     \
my_strcat.c            \
my_strchr.c            \
my_strcmp.c            \
my_strcpy.c            \
my_stricmp.c           \
my_strincmp.c          \
my_str_isalpha.c       \
my_str_islower.c       \
my_str_isnum.c         \
my_str_isprintable.c   \
my_str_isupper.c       \
my_strlen.c            \
my_strlowcase.c        \
my_strncat.c           \
my_strncmp.c           \
my_strncpy.c           \
my_strstr.c            \
my_strstr_n.c          \
my_strupcase.c         \

ifeq ($(findstring allow_malloc, $(FLAGS)), allow_malloc)
MODULE_SRCS +=         \
my_free_str_array.c    \
my_strdup.c            \
my_str_to_word_array.c
endif

MODULE_INCS := libmy/ascii.h

$(call addmodule)
