MODULE_NAME := io
MODULE_DEPS := ascii collections

MODULE_SRCS :=                 \
my_fclose.c                    \
my_feof.c                      \
my_fflush.c                    \
my_ffree.c                     \
my_fget_buffer.c               \
my_finit.c                     \
my_flush_iostream.c            \
my_fputc.c                     \
my_fputint.c                   \
my_fputintmax_t_base.c         \
my_fputs.c                     \
my_fputs_endl.c                \
my_fputuint.c                  \
my_fputuintmax_t_base.c        \
my_fread.c                     \
my_fread_to_string.c           \
my_free_iostream.c             \
my_frputc.c                    \
my_fset_buffer.c               \
my_fset_threshold.c            \
my_fwrite.c                    \
my_get_iostream.c              \
my_init_iostream.c             \
my_is_iostream.c               \
my_putchar.c                   \
my_put_nbr.c                   \
my_putstr.c                    \
my_putuint.c                   \
my_showmem.c                   \
my_showstr.c                   \
my_show_word_array.c           \

ifeq ($(findstring allow_close, $(FLAGS)), allow_close)
MODULE_SRCS +=                  \
my_fclose_allow_close.c
endif

ifeq ($(findstring allow_read, $(FLAGS)), allow_read)
MODULE_SRCS +=                  \
my_fread_allow_read.c           \
my_fread_to_string_allow_read.c
endif

ifeq ($(findstring allow_malloc, $(FLAGS)), allow_malloc)
MODULE_SRCS +=                  \
my_getdelim.c
endif

MODULE_INCS := libmy/io.h libmy/internal/iostream.h

$(call addmodule)
