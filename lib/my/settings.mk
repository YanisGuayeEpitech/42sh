### PROJECT SETTINGS ###
# You can edit any value below

TARGET := libmy.a
COPY_PATH := ..
TEST_TARGET := unit_tests

VERSION_BASE := 0.2.0
VERSION := $(VERSION_BASE)

# The number of tasks Make will run at once
PARALLEL_JOBS := 10

# Basic Definitions
MODULES_PATH := modules
SRC_PATH := src
OBJ_PATH := bin
INC_PATH := include
DOC_PATH := doc
TEST_PATH := tests
TEST_OBJ_PATH := $(OBJ_PATH)/test

# Compiler Flags
ARFLAGS := -rcs
UNIT_TEST_CFLAGS :=-Wall -Wextra -Werror -Wshadow -Wno-abi -pedantic -O1 \
-fdiagnostics-color
TEST_CFLAGS := -Wall -Wextra -Werror -Wshadow -Wno-abi -pedantic -fprofile-arcs \
-ftest-coverage --coverage -O1 -fdiagnostics-color
CFLAGS := -Wall -Wextra -Werror -Wshadow -Wno-abi -pedantic -O1 -fdiagnostics-color
CPPFLAGS := -iquote include

# Dependencies
TEST_CLIBS := -lcriterion -lgcov

# Commands
AR := ar
CC := gcc
OPEN_DOCS := xdg-open
RM := rm -f
RMDIR := rmdir -p
MKDIR := mkdir -p
LIBMY_CONFIG := ./libmy-config
COVERAGE := gcovr

# Default modules if MODULES isn't set
#
# Available modules:
# - core
# - ascii
# - collections
# - io
# - math
# - parsing
# - printf
DEFAULT_MODULES := core ascii collections io math memory misc parsing printf

# Default flags if FLAGS isn't set
#
# Available flags:
# - allow_malloc
# - allow_open
# - allow_read
# - allow_close
DEFAULT_FLAGS := allow_malloc allow_open allow_read allow_close
