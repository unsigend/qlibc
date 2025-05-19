# qlibc - A light-weight and portable C standard library
# Copyright (C) 2025 Qiu Yixiang
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#

# Main Makefile for qlibc
# qlibc is a lightweight C library for embedded systems and kernel

# variables for paths
CUR_DIR         :=          .
SRC_PATH 		:= 			$(CUR_DIR)/src
ARCH_PATH       :=          $(CUR_DIR)/arch
INCLUDE_PATH 	:= 			$(CUR_DIR)/include
TEST_PATH 		:= 			$(CUR_DIR)/test
CONFIG_PATH 	:= 			$(CUR_DIR)/config
BUILD_PATH 		:= 			$(CUR_DIR)/build
OBJ_PATH 		:= 			$(BUILD_PATH)/obj
DEP_PATH 		:= 			$(BUILD_PATH)/dep
LIB_PATH 		:= 			$(BUILD_PATH)/lib

# include config
include $(CONFIG_PATH)/config.mk

# variables for source files
SRCS            :=          $(shell find $(SRC_PATH) -name "*.c")
SRCS_ARCH       :=          $(shell find $(ARCH_PATH)/$(ARCH) -name "*.c")

# variables for object files
OBJS            :=          $(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRCS))
OBJS_ARCH       :=          $(patsubst $(ARCH_PATH)/$(ARCH)/src/%.c,$(OBJ_PATH)/$(ARCH)/%.o, $(SRCS_ARCH))

# variables for dependency files
DEPS            :=          $(patsubst $(SRC_PATH)/%.c, $(DEP_PATH)/%.d, $(SRCS))
DEPS_ARCH       :=          $(patsubst $(ARCH_PATH)/$(ARCH)/src/%.c,$(DEP_PATH)/$(ARCH)/%.d, $(SRCS_ARCH))

# host OS 
HOST_OS         :=          $(shell uname -s)
# host architecture
HOST_ARCH       :=          $(shell uname -m)


# variables for tools
GCC 			:= 			$(TOOLCHAIN_PREFIX)gcc
LD 			    := 			$(GCC)
AR 			    := 			$(TOOLCHAIN_PREFIX)ar

# variables for GNU C Compiler flags
CC_FLAGS 		:= 		    -std=$(QLIBC_C_STANDARD)

# variables for GNU C Freestanding flags
CC_FREESTANDING	:= 		    -ffreestanding
CC_FREESTANDING +=          -fno-builtin

# variables for GNU C Warning flags
CC_WARNINGS 	:= 		    -Wall -Wextra -Werror
CC_WARNINGS 	+= 		    -Wno-unused-parameter

CC_OPTIMIZE     :=

# variables for GNU C Debugger flags
CC_DEBUGGER 	:= 

# variables for GNU C Optimize flags
CC_OPTIMIZE     :=

# variables for GNU C Debugger flags
ifeq ($(DEBUG), 1)
	CC_DEBUGGER  	+= 		    -g
	CC_OPTIMIZE    	+=          -O0
else
	CC_OPTIMIZE    	+=          -O2
endif

# variables for GNU C Include flags
CC_INCLUDES     :=
CC_INCLUDES     +=          -nostdinc
CC_INCLUDES 	+= 		    -I $(INCLUDE_PATH)
CC_INCLUDES     +=          -I $(ARCH_PATH)/$(ARCH)/include

# variables for GNU C Flags
CC_FLAGS        +=          $(CC_WARNINGS)
CC_FLAGS        +=          $(CC_FREESTANDING)
CC_FLAGS        +=          $(CC_OPTIMIZE)
CC_FLAGS        +=          $(CC_DEBUGGER)
CC_FLAGS        +=          $(CC_INCLUDES)

# variables for GNU C Dependency flags
CC_DEPS_FLAGS   :=          -MMD -MP -MF

# variables for GNU C Linker flags
LD_FLAGS 		:= 		    -std=$(QLIBC_C_STANDARD)
# the linker should not link any standard library
LD_FLAGS        +=          -nostdlib
LD_FLAGS        +=          -nolibc


# variables for GNU C Archive flags
AR_FLAGS 		:= 		    -rcs

# general rules for all objects
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	@$(GCC) $(CC_FLAGS) $(CC_DEPS_FLAGS) $(DEP_PATH)/$(notdir $(@F:.o=.d)) -c $< -o $@
	@echo " + CC\t$@"

$(OBJ_PATH)/$(ARCH)/%.o: $(ARCH_PATH)/$(ARCH)/src/%.c
	@mkdir -p $(dir $@)
	@$(GCC) $(CC_FLAGS) $(CC_DEPS_FLAGS) $(DEP_PATH)/$(notdir $(@F:.o=.d)) -c $< -o $@
	@echo " + CC\t$@"

# include dependency files
-include $(DEP_PATH)/*.d

# default goal
.DEFAULT_GOAL := help
.PHONY: all clean create_build_dir info help test gnu welcome lib

# target for creating build directory
create_build_dir:
	@mkdir -p $(BUILD_PATH)
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(DEP_PATH)
	@mkdir -p $(LIB_PATH)

# target for cleaning build directory
clean:
	@rm -rf $(BUILD_PATH)

# all target
all: welcome create_build_dir lib

# welcome target
welcome:
	@echo "Building qlibc for $(ARCH):"

# info target
info:
	@echo "Makefile Build Configuration for qlibc $(QLIBC_VERSION)"
	@echo " - Build Architecture : $(ARCH)"
	@echo " - Host OS            : $(HOST_OS)"
	@echo " - Host ARCH          : $(HOST_ARCH)"
	@echo " - Library path       : $(LIB_PATH)"
	@echo " - Build Method       : $(BUILD_METHOD)"
	@echo " - C Standard         : $(QLIBC_C_STANDARD)"
ifeq ($(TOOLCHAIN_PREFIX),)
	@echo " - Toolchain prefix   : NONE"
else
	@echo " - Toolchain prefix   : $(TOOLCHAIN_PREFIX)"
endif
ifeq ($(DEBUG), 1)
	@echo " - Debug mode         : ON"
else
	@echo " - Debug mode         : OFF"
endif
	@echo ""

# help target
help:
	@echo "Makefile Build System for qlibc $(QLIBC_VERSION)"
	@echo "USAGE:"
	@echo "\tmake all           - Build the qlibc library"
	@echo "\tmake info          - Show the build configuration"
	@echo "\tmake clean         - Clean the build directory"
	@echo "\tmake help          - Show this help message"
	@echo "\tmake test          - Run all the test cases"
	@echo "\tmake gnu           - Build the test cases with GNU glibc"
	@echo "\tmake test-<module> - Build the test cases for a specific module"
	@echo ""

# lib target
lib: $(OBJS) $(OBJS_ARCH)
ifeq ($(BUILD_METHOD), static)
	@$(AR) $(AR_FLAGS) $(LIB_PATH)/lib$(QLIBC_NAME).a $(OBJS) $(OBJS_ARCH)
	@echo " + AR\t$(LIB_PATH)/lib$(QLIBC_NAME).a"
else
	@$(GCC) $(LD_FLAGS) -shared $(OBJS) $(OBJS_ARCH) -o $(LIB_PATH)/lib$(QLIBC_NAME).so
	@echo " + LD\t$(LIB_PATH)/lib$(QLIBC_NAME).so"
endif

# export the variables to the sub-make
export QLIBC_NAME
export QLIBC_C_STANDARD
export QLIBC_VERSION
export ARCH
export BUILD_METHOD

# test target
# execute test-all command in sub-make
test: lib
	@$(MAKE) -C $(TEST_PATH) test-all

# test-module target
test-%: lib
	@$(MAKE) -C $(TEST_PATH) test-$*
