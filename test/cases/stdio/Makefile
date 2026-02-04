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

# makefile for stdio test cases

# qlibc variables
QLIBC_INCLUDE_PATH		:= 		../../../include
QLIBC_INCLUDE_ARCH_PATH	:= 		../../../arch/$(ARCH)/include
QLIBC_LIB_PATH			:= 		../../../lib
ifndef QLIBC_NAME
QLIBC_NAME				:= 		qlibc
endif

HOST_OS					:= 		$(shell uname -s)

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
BUILD_PATH				:= 		../../build/stdio
OBJ_PATH				:= 		$(BUILD_PATH)/obj
DEP_PATH				:= 		$(BUILD_PATH)/dep
BIN_PATH				:= 		$(BUILD_PATH)/bin

# Test variables
TEST_PATH				:= 		./tests

# source files and executables
SRCS                    :=      $(shell find $(TEST_PATH) -name "*.c")
EXECS_QLIBC             :=      $(patsubst $(TEST_PATH)/%.c, $(BIN_PATH)/%.qlibc.out, $(SRCS))
EXECS_GNU               :=      $(patsubst $(TEST_PATH)/%.c, $(BIN_PATH)/%.gnu.out, $(SRCS))
EXECS                   :=      $(EXECS_QLIBC) $(EXECS_GNU)

# dependency files
OBJS_QLIBC              :=      $(patsubst $(TEST_PATH)/%.c, $(OBJ_PATH)/%.qlibc.o, $(SRCS))
OBJS_GNU                :=      $(patsubst $(TEST_PATH)/%.c, $(OBJ_PATH)/%.gnu.o, $(SRCS))
OBJS                    :=      $(OBJS_QLIBC) $(OBJS_GNU)
DEPS_QLIBC              :=      $(patsubst $(OBJ_PATH)/%.qlibc.o, $(DEP_PATH)/%.qlibc.d, $(OBJS_QLIBC))
DEPS_GNU                :=      $(patsubst $(OBJ_PATH)/%.gnu.o, $(DEP_PATH)/%.gnu.d, $(OBJS_GNU))
DEPS                    :=      $(DEPS_QLIBC) $(DEPS_GNU)

# Compiler Tools
CC                      :=      $(GCC)
LD                      :=      $(CC)

# Compiler Flags
CC_WARNINGS             :=      -Wall -Wextra -Werror
CC_WARNINGS             +=      -Wno-memset-transposed-args
CC_WARNINGS             +=      -Wno-unused-function
CC_WARNINGS             +=      -Wno-implicitly-unsigned-literal
CC_WARNINGS             +=      -Wno-builtin-memcpy-chk-size
CC_WARNINGS             +=      -Wno-gnu-alignof-expression

# QLIBC Compiler Flags
QLIBC_CC_FLAGS          :=      -I$(QLIBC_INCLUDE_PATH)
QLIBC_CC_FLAGS          +=      -I$(QLIBC_INCLUDE_ARCH_PATH)
QLIBC_CC_FLAGS          +=      -std=$(QLIBC_C_STANDARD)
QLIBC_CC_FLAGS          +=      $(CC_WARNINGS)
QLIBC_CC_FLAGS          +=      -fno-builtin -ffreestanding

ifeq ($(DEBUG), 1)
QLIBC_CC_FLAGS          +=      -g
QLIBC_CC_FLAGS          +=      -O0
else
QLIBC_CC_FLAGS          +=      -O2
endif

ifeq ($(ARCH), i386)
QLIBC_CC_FLAGS          +=      -m32
endif

# GNU Compiler Flags
GNU_CC_FLAGS            :=      -std=$(QLIBC_C_STANDARD)
GNU_CC_FLAGS            +=      $(CC_WARNINGS)

ifeq ($(DEBUG), 1)
GNU_CC_FLAGS            +=      -g
GNU_CC_FLAGS            +=      -O0
else
GNU_CC_FLAGS            +=      -O2
endif

ifeq ($(ARCH), i386)
GNU_CC_FLAGS            +=      -m32
endif

# QLIBC Linker Flags
QLIBC_LD_FLAGS          :=      -L$(QLIBC_LIB_PATH) -l$(QLIBC_NAME)
QLIBC_LD_FLAGS          +=      -std=$(QLIBC_C_STANDARD)
ifeq ($(ARCH), i386)
QLIBC_LD_FLAGS          +=      -m32
endif

# GNU Linker Flags
GNU_LD_FLAGS            :=      -std=$(QLIBC_C_STANDARD)
ifeq ($(ARCH), i386)
GNU_LD_FLAGS            +=      -m32
endif

# general rules for qlibc objects
$(OBJ_PATH)/%.qlibc.o: $(TEST_PATH)/%.c
	@mkdir -p $(dir $@)
	@mkdir -p $(dir $(DEP_PATH)/$*)
	@$(CC) $(QLIBC_CC_FLAGS) -MMD -MP -MF $(DEP_PATH)/$*.qlibc.d -MT $@ -c $< -o $@
	@echo " + CC\t$@ (qlibc)"

# general rules for gnu objects
$(OBJ_PATH)/%.gnu.o: $(TEST_PATH)/%.c
	@mkdir -p $(dir $@)
	@mkdir -p $(dir $(DEP_PATH)/$*)
	@$(CC) $(GNU_CC_FLAGS) -MMD -MP -MF $(DEP_PATH)/$*.gnu.d -MT $@ -c $< -o $@
	@echo " + CC\t$@ (gnu)"

# general rules for qlibc executables
$(BIN_PATH)/%.qlibc.out: $(OBJ_PATH)/%.qlibc.o $(QLIBC_LIB_DEPS)
	@mkdir -p $(dir $@)
	@$(LD) $< $(QLIBC_LD_FLAGS) -o $@
	@echo " + LD\t$@"

# general rules for gnu executables
$(BIN_PATH)/%.gnu.out: $(OBJ_PATH)/%.gnu.o
	@mkdir -p $(dir $@)
	@$(LD) $< $(GNU_LD_FLAGS) -o $@
	@echo " + LD\t$@"

-include $(DEPS)

.SECONDARY: $(DEPS) $(OBJS)

.DEFAULT_GOAL := all
.PHONY: test clean all check-dep

check-dep:
	@mkdir -p $(DEP_PATH)
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(BIN_PATH)

# build all test cases
all: check-dep $(EXECS)
	@echo "Build stdio test cases (qlibc and gnu versions):"
	@echo "  QLIBC: $(EXECS_QLIBC)"
	@echo "  GNU:   $(EXECS_GNU)"
	@echo ""

# run all test cases
test: all
	@echo "Run ./test/cases/stdio/run.sh to execute stdio test cases"

clean:
	@rm -rf $(BUILD_PATH)
