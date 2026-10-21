# qlibc - A light-weight and portable C standard library
# Copyright (C) 2025-2027 Yixiang Qiu
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

ROOTDIR := $(abspath ..)

include $(ROOTDIR)/mk/config.mk
include $(ROOTDIR)/mk/toolchain.mk

CASEDIR  := cases
EXTDIR   := external
BUILDDIR := build
OBJDIR   := $(BUILDDIR)/obj
DEPDIR   := $(BUILDDIR)/dep
BIN      := $(BUILDDIR)/qlibc-test

SRCS := $(shell find $(CASEDIR) $(EXTDIR) -name "*.c" 2>/dev/null)
OBJS := $(patsubst %.c,$(OBJDIR)/%.c.o,$(SRCS))
DEPS := $(patsubst $(OBJDIR)/%.o,$(DEPDIR)/%.d,$(OBJS))

CFLAGS_TEST := -I $(EXTDIR)/include
CFLAGS_WARN_TEST := -Wall -Wextra

BIN_DEPS := $(OBJS)

ifeq ($(USE_HOST_LIBC),1)
    CFLAGS  := -std=$(STD_C) $(CFLAGS_WARN_TEST) $(CFLAGS_OPT) $(CFLAGS_ARCH) \
               $(CFLAGS_TEST) -pthread
    LDFLAGS := -std=$(STD_C) $(CFLAGS_ARCH) -pthread
    LDLIBS  :=
else
    CFLAGS  := -std=$(STD_C) $(CFLAGS_WARN_TEST) $(CFLAGS_OPT) $(CFLAGS_ARCH) \
               $(CFLAGS_INC) $(CFLAGS_TEST) -pthread
    LDFLAGS := -std=$(STD_C) $(CFLAGS_ARCH) -pthread
    LDLIBS  := $(LIB)
    QLIBC_SRCS := $(shell find $(ROOTDIR)/src -name "*.c" 2>/dev/null)
    QLIBC_HDRS := $(shell find $(INCDIR) -name "*.h" 2>/dev/null)
    $(OBJS): $(QLIBC_SRCS) $(QLIBC_HDRS)
    BIN_DEPS += $(LIB)
    $(LIB): $(QLIBC_SRCS) $(QLIBC_HDRS)
	@$(MAKE) -C $(ROOTDIR) lib
endif

-include $(DEPS)

$(OBJDIR)/%.c.o: %.c
	@mkdir -p $(dir $@) $(dir $(DEPDIR)/$*.c.d)
	@$(CC) $(CFLAGS) -MMD -MP -MF $(DEPDIR)/$*.c.d -MT $@ -c $< -o $@
	@echo "  CC    $<"

$(BIN): $(BIN_DEPS)
	@mkdir -p $(dir $@)
	@$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@
	@echo "  LD    $@"

.PHONY: test clean

test: $(BIN)
	@echo "  RUN   $(BIN)"
	@$(BIN)

clean:
	@rm -rf $(BUILDDIR)
