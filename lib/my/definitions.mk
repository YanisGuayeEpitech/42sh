### INTERNAL DEFINITIONS, DO NOT EDIT ###
# For project settings, see 'settings.mk'

-include settings.mk

SRCS :=
INCS :=
OBJS :=
TEST_SRCS :=
TEST_OBJS :=
LOADED_MODULES :=

CURRENT_DIR := $(shell pwd -P)

# Set modules to default if the variable isn't defined
ifndef MODULES
	MODULES := $(DEFAULT_MODULES)
endif

# Set flags to default if the variable isn't defined
ifndef FLAGS
	FLAGS = $(DEFAULT_FLAGS)
endif

# Called by the makefiles of modules to register their sources, object and includes.
define addmodule
	$(eval SRCS += $(addprefix $(SRC_PATH)/$(MODULE_NAME)/, $(MODULE_SRCS)));
	$(eval INCS += $(addprefix $(INC_PATH)/, $(MODULE_INCS)));
	$(eval OBJS += $(addprefix $(OBJ_PATH)/$(MODULE_NAME)/, $(MODULE_SRCS:.c=.o)));
	$(eval TEST_SRCS += $(addprefix $(TEST_PATH)/$(MODULE_NAME)/test_, $(MODULE_SRCS)));
	$(eval TEST_OBJS += $(addprefix $(TEST_OBJ_PATH)/$(MODULE_NAME)/, $(MODULE_SRCS:.c=.o) $(addprefix test_, $(MODULE_SRCS:.c=.o))));
	$(eval LOADED_MODULES += $(MODULE_NAME));
	$(eval -include $(addprefix $(MODULES_PATH)/, $(addsuffix .mk, $(MODULE_DEPS))));
endef

# Add the sources of each module
-include $(addprefix $(MODULES_PATH)/, $(addsuffix .mk, $(MODULES)))

# Sort and remove duplicates
INCS := $(sort $(INCS))
SRCS := $(sort $(SRCS))
OBJS := $(sort $(OBJS))
TEST_SRCS := $(sort $(TEST_SRCS))
TEST_OBJS := $(sort $(TEST_OBJS))
OBJS_DIRS := $(sort $(dir $(OBJS)))
TEST_OBJS_DIRS := $(sort $(dir $(TEST_OBJS)))
LOADED_MODULES := $(sort $(LOADED_MODULES))

# Adding all modules to VPATH
COLON := :
EMPTY :=
SPACE := $(EMPTY) $(EMPTY)
VPATH = $(subst $(SPACE),$(COLON),$(addprefix $(SRC_PATH)/,$(strip $(LOADED_MODULES))))

VERSION_MAJOR := $(shell echo $(VERSION_BASE) | cut -d '.' -f 1)
VERSION_MINOR := $(shell echo $(VERSION_BASE) | cut -d '.' -f 2)
VERSION_PATCH := $(shell echo $(VERSION_BASE) | cut -d '.' -f 3)

# Definitions that will be passed to the compiler
MODULE_FLAGS := $(addprefix LIBMY_MODULE_, $(shell echo $(LOADED_MODULES) | tr '[:lower:]' '[:upper:]'))
UPPER_FLAGS := $(addprefix LIBMY_, $(shell echo $(FLAGS) | tr '[:lower:]' '[:upper:]'))
VERSION_FLAGS :=                     \
LIBMY_VERSION=$(VERSION_BASE)        \
LIBMY_VERSION_MAJOR=$(VERSION_MAJOR) \
LIBMY_VERSION_MINOR=$(VERSION_MINOR) \
LIBMY_VERSION_PATCH=$(VERSION_PATCH)

# Properties to pass to libmy-config
SPACE_PLACEHOLDER := /<space>/
CONFIG_PLACEHOLDER := SPACE_PLACEHOLDER="$(SPACE_PLACEHOLDER)"
CONFIG_DEFINES := CONFIG_DEFINES="$(subst $(SPACE),$(SPACE_PLACEHOLDER),$(MODULE_FLAGS) $(UPPER_FLAGS) $(VERSION_FLAGS))"
CONFIG_FLAGS := CONFIG_FLAGS="$(subst $(SPACE),$(SPACE_PLACEHOLDER),$(FLAGS))"
CONFIG_INCLUDE_PATH := CONFIG_INCLUDE_PATH="$(subst $(SPACE),$(SPACE_PLACEHOLDER),$(CURRENT_DIR)/$(INC_PATH))"
CONFIG_LIBRARY_PATH := CONFIG_LIBRARY_PATH="$(subst $(SPACE),$(SPACE_PLACEHOLDER),$(CURRENT_DIR))"
CONFIG_MODULES := CONFIG_MODULES="$(subst $(SPACE),$(SPACE_PLACEHOLDER),$(LOADED_MODULES))"
CONFIG_VERSION_MAJOR := CONFIG_VERSION_MAJOR=$(VERSION_MAJOR)
CONFIG_VERSION_MINOR := CONFIG_VERSION_MINOR=$(VERSION_MINOR)
CONFIG_VERSION_PATCH := CONFIG_VERSION_PATCH=$(VERSION_PATCH)

CONFIG :=               \
$(CONFIG_PLACEHOLDER)   \
$(CONFIG_DEFINES)       \
$(CONFIG_FLAGS)         \
$(CONFIG_INCLUDE_PATH)  \
$(CONFIG_LIBRARY_PATH)  \
$(CONFIG_MODULES)       \
$(CONFIG_VERSION_MAJOR) \
$(CONFIG_VERSION_MINOR) \
$(CONFIG_VERSION_PATCH) \


define retrieve_config
$(eval
	BUILD_CONFIG := $(shell make -C config re $(CONFIG))
	CFLAGS += $(addprefix -D , $(shell $(LIBMY_CONFIG) defines))
	TEST_CFLAGS += $(addprefix -D , $(shell $(LIBMY_CONFIG) defines))
	UNIT_TEST_CFLAGS += $(addprefix -D , $(shell $(LIBMY_CONFIG) defines))
)
endef
