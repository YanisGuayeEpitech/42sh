MODULE_NAME := printf
MODULE_DEPS := ascii io

MODULE_SRCS :=                 \
my_asprintf.c                  \
my_dprintf.c                   \
my_fprintf.c                   \
my_printf.c                    \
my_printf_char.c               \
my_printf_boolean.c            \
my_printf_boolean_len.c        \
my_printf_conversion.c         \
my_printf_conversion_len.c     \
my_printf_count_parameters.c   \
my_printf_fill_args.c          \
my_printf_fill_types.c         \
my_printf_next_conversion.c    \
my_printf_get_conv_base.c      \
my_printf_get_conv_specifier.c \
my_printf_get_flags.c          \
my_printf_get_len_modifier.c   \
my_printf_get_position.c       \
my_printf_get_type.c           \
my_printf_pad.c                \
my_printf_parse_conversion.c   \
my_printf_percent.c            \
my_printf_pointer.c            \
my_printf_pointer_len.c        \
my_printf_sint.c               \
my_printf_sint_len.c           \
my_printf_string.c             \
my_printf_string_len.c         \
my_printf_uint.c               \
my_printf_uint_len.c           \
my_snprintf.c                  \
my_sprintf.c                   \
my_vasprintf.c                 \
my_vdprintf.c                  \
my_vfprintf.c                  \
my_vprintf.c                   \
my_vsnprintf.c                 \
my_vsprintf.c                  \

MODULE_INCS := libmy/printf.h libmy/internal/printf.h

$(call addmodule)
