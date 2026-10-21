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

MKDIR     := mk
SCRIPTDIR := scripts

include $(MKDIR)/config.mk
include $(MKDIR)/toolchain.mk

BUILDDIR := build
DEPDIR   := $(BUILDDIR)/dep
OBJDIR   := $(BUILDDIR)/obj
SRCDIR   := src
TESTDIR  := test

SRCS := $(shell find $(SRCDIR) -name "*.c")
OBJS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.c.o,$(SRCS))
DEPS := $(patsubst $(OBJDIR)/%.o,$(DEPDIR)/%.d,$(OBJS))

-include $(DEPS)

$(OBJDIR)/%.c.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@) $(dir $(DEPDIR)/$*.c.d)
	@$(CC) $(CFLAGS) -MMD -MP -MF $(DEPDIR)/$*.c.d -MT $@ -c $< -o $@
	@echo "  CC    $<"

.PHONY: all lib test clean info flag clang format line version gen-config help
.DEFAULT_GOAL := help

all: lib

lib: $(OBJS)
	@mkdir -p $(LIBDIR)
ifeq ($(BUILD_METHOD),static)
	@$(AR) $(ARFLAGS) $(LIB) $(OBJS)
	@echo "  AR    $(LIB)"
else
	@$(CC) $(LDFLAGS) -shared $(OBJS) -o $(LIB)
	@echo "  LD    $(LIB)"
endif

test: gen-config
	@$(MAKE) -C $(TESTDIR) test

clean:
	@rm -rf $(BUILDDIR) $(LIBDIR)
	@$(MAKE) -C $(TESTDIR) clean

info:
	@echo "qlibc v$(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH)"
	@echo "  arch          $(ARCH)"
	@echo "  host          $(HOST_OS)/$(HOST_ARCH)"
	@echo "  method        $(BUILD_METHOD)"
	@echo "  std           $(STD_C)"
	@echo "  cc            $(CC)"
	@echo "  ar            $(AR)"
	@echo "  debug         $(if $(filter 1,$(DEBUG)),on,off)"
	@echo "  host libc     $(if $(filter 1,$(USE_HOST_LIBC)),on,off)"

flag:
	@echo "CFLAGS:  $(CFLAGS)"
	@echo "LDFLAGS: $(LDFLAGS)"
	@echo "ARFLAGS: $(ARFLAGS)"

clang:
	@$(MAKE) clean
	@bear -- $(MAKE) test

format:
	@find $(SRCDIR) $(INCDIR) $(ARCHDIR) \
		\( -name "*.c" -o -name "*.h" \) -exec clang-format -i {} +
	@echo "  FORMAT   done"

line:
	@$(PYTHON) $(SCRIPTDIR)/linecount.py

version:
	@echo "qlibc v$(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH) arch=$(ARCH)"

gen-config:
	@$(PYTHON) $(SCRIPTDIR)/gen-config.py
	@echo "  GEN   config.cfg"

help:
	@echo "qlibc - A light-weight and portable C standard library v$(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH)"
	@echo "Copyright (C) 2025-2027 Yixiang Qiu"
	@echo ""
	@echo "USAGE:"
	@echo ""
	@echo "build:"
	@echo "\tmake all                 - build the library"
	@echo "\tmake lib                 - build the library"
	@echo ""
	@echo "test:"
	@echo "\tmake test                - build and run tests"
	@echo ""
	@echo "other:"
	@echo "\tmake clean               - clean the build directory"
	@echo "\tmake help                - show this help message"
	@echo "\tmake info                - show the build configuration"
	@echo "\tmake flag                - show compile and link flags"
	@echo "\tmake clang               - generate compile_commands.json"
	@echo "\tmake format              - format .c and .h files"
	@echo "\tmake line                - count source lines by module"
	@echo "\tmake version             - show the version of the library"
	@echo "\tmake gen-config          - generate mk/config.mk and include/config.h"
	@echo ""
