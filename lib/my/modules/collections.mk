MODULE_NAME := collections
MODULE_DEPS := core memory

MODULE_SRCS :=

ifeq ($(findstring allow_malloc, $(FLAGS)), allow_malloc)
MODULE_SRCS +=            \
my_vec_copy.c             \
my_vec_ensure_capacity.c  \
my_vec_extend_to_length.c \
my_vec_free.c             \
my_vec_init_capacity.c    \
my_vec_pop.c              \
my_vec_push.c             \
my_vec_reserve.c          \
my_vec_set_capacity.c     \
my_vec_shrink_to_fit.c
endif

MODULE_INCS := libmy/collections/collections.h libmy/collections/vec.h

$(call addmodule)
