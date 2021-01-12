MODULE_NAME := memory
MODULE_DEPS := core

MODULE_SRCS :=         \
my_binary_search.c     \
my_cbuffer_get_parts.c \
my_cbuffer_init.c      \
my_cbuffer_pop.c       \
my_cbuffer_push.c      \
my_cbuffer_read.c      \
my_cbuffer_rotate.c    \
my_cbuffer_write.c     \
my_memcpy.c            \
my_memmove.c           \
my_memset.c            \
my_msort.c             \
my_swap_ptr.c          \

ifeq ($(findstring allow_malloc, $(FLAGS)), allow_malloc)
MODULE_SRCS +=         \
my_realloc.c
endif

MODULE_INCS := libmy/memory.h libmy/memory/cbuffer.h libmy/internal/memory.h

$(call addmodule)
