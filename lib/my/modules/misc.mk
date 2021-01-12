MODULE_NAME := misc
MODULE_DEPS := core

MODULE_SRCS :=      \
my_ptr_array_len.c  \
my_sort_int_array.c \
my_swap.c           \

MODULE_INCS := libmy/misc.h

$(call addmodule)
