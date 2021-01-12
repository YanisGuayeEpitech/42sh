MODULE_NAME := math
MODULE_DEPS := core

MODULE_SRCS :=           \
my_compute_power.c       \
my_compute_square_root.c \
my_find_prime_sup.c      \
my_isneg.c               \
my_is_prime.c            \

MODULE_INCS := libmy/math.h

$(call addmodule)
