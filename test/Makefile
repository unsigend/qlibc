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

# makefile for test qlibc implementation

# external path variables
EXTERNAL_PATH  			:= 		./external
EXTERNAL_INCLUDE_PATH	:= 		$(EXTERNAL_PATH)/include
EXTERNAL_SRC_PATH		:= 		$(EXTERNAL_PATH)/src

HOST_OS					:= 		$(shell uname -s)

# qlibc variables
QLIBC_INCLUDE_PATH		:= 		../include
QLIBC_INCLUDE_ARCH_PATH	:= 		../arch/$(ARCH)/include
QLIBC_LIB_PATH			:= 		../lib
ifndef QLIBC_NAME
QLIBC_NAME				:= 		qlibc
endif

ifeq ($(BUILD_METHOD), static)
QLIBC_LIB_POSTFIX		:= 		.a
else
ifeq ($(HOST_OS), Darwin)
QLIBC_LIB_POSTFIX		:= 		.dylib
else
QLIBC_LIB_POSTFIX		:= 		.so
endif
endif
QLIBC_LIB_DEPS          :=      $(QLIBC_LIB_PATH)/lib$(QLIBC_NAME)$(QLIBC_LIB_POSTFIX)

# Build Path
BUILD_PATH				:= 		./build
OBJ_PATH				:= 		$(BUILD_PATH)/obj
DEP_PATH				:= 		$(BUILD_PATH)/dep

# Test variables
TEST_PATH				:= 		./cases

# source files and objects
SRCS                    :=      $(shell find $(TEST_PATH) -name "*.c")
OBJS                    :=      $(patsubst $(TEST_PATH)/%.c, $(BUILD_PATH)/%.o, $(SRCS))
EXTERNAL_SRCS           :=      $(shell find $(EXTERNAL_SRC_PATH) -name "*.c")
EXTERNAL_OBJS           :=      $(patsubst $(EXTERNAL_SRC_PATH)/%.c, $(BUILD_PATH)/external/%.o, $(EXTERNAL_SRCS))
OBJS                    +=      $(EXTERNAL_OBJS)

# Compiler Tools
CC                      :=      gcc
AR                      :=      ar
LD                      :=      $(CC)

# Compiler Flags
CC_FLAGS                :=      -isystem$(EXTERNAL_INCLUDE_PATH)
ifeq ($(USING_GNU), 0)
CC_FLAGS                +=      -I$(QLIBC_INCLUDE_PATH)
CC_FLAGS                +=      -I$(QLIBC_INCLUDE_ARCH_PATH)
endif
CC_FLAGS                +=      -std=$(QLIBC_C_STANDARD)
CC_FLAGS                +=      -Wall -Wextra -Werror
CC_FLAGS                +=      -Wno-memset-transposed-args
CC_FLAGS                +=      -g
CC_FLAGS                +=      -O0
ifeq ($(USING_GNU), 0)
# CC_FLAGS                +=      -nostdinc -nostdlib -nostdlib-headers
CC_FLAGS                +=      -fno-builtin -ffreestanding
endif
ifeq ($(ARCH), i386)
CC_FLAGS                +=      -m32
endif

# Linker Flags
ifeq ($(USING_GNU), 0)
LD_FLAGS                :=      -L$(QLIBC_LIB_PATH) -l$(QLIBC_NAME)
endif
LD_FLAGS                +=      -std=$(QLIBC_C_STANDARD)
ifeq ($(USING_GNU), 0)
# LD_FLAGS                +=      -nostdlib
# LD_FLAGS                +=      -nolibc
endif
ifeq ($(ARCH), i386)
LD_FLAGS                +=      -m32
endif

# general rules for all objects
$(BUILD_PATH)/%.o: $(TEST_PATH)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CC_FLAGS) -MMD -MP -MF $(DEP_PATH)/$(@F:.o=.d) -c $< -o $@
	@echo " + CC\t$@"

$(BUILD_PATH)/external/%.o: $(EXTERNAL_SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CC_FLAGS) -c $< -o $@
	@echo " + CC\t$@"

-include $(DEP_PATH)/*.d

.DEFAULT_GOAL := test
.PHONY: test clean all check-dep

check-dep:
	@mkdir -p $(DEP_PATH)

# build all test cases
all: check-dep $(OBJS)
	@$(LD) $(OBJS) $(LD_FLAGS) -o $(BUILD_PATH)/test
	@echo " + LD\t$(BUILD_PATH)/test"
	@echo "Build qlibc test cases: $(BUILD_PATH)/test"
	@echo ""

# run all test cases 
test: all
ifeq ($(BUILD_METHOD), static)
	@$(BUILD_PATH)/test
else
	@echo "Run ./test/build/test to see qlibc test result"
endif

# run specific test case
test-%: all
	@./$(BUILD_PATH)/test $*

clean:
	@rm -rf $(BUILD_PATH)