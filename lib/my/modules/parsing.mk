MODULE_NAME := parsing
MODULE_DEPS := ascii

MODULE_SRCS :=   \
my_getnbr.c      \
my_getnbr_base.c \
my_next_size_t.c \

MODULE_INCS := libmy/parsing.h

$(call addmodule)
