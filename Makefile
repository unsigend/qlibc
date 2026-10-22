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
ARCHSRC  := arch/$(ARCH) arch/generic

C_SRCS := $(sort $(shell find $(SRCDIR) $(ARCHSRC) -name '*.c' 2>/dev/null))
S_SRCS := $(sort $(shell find $(ARCHSRC) -name '*.S' 2>/dev/null))

C_OBJS := $(C_SRCS:%=$(OBJDIR)/%.o)
S_OBJS := $(S_SRCS:%=$(OBJDIR)/%.o)
DEPS   := $(C_SRCS:%.c=$(DEPDIR)/%.d)

-include $(DEPS)

$(OBJDIR)/%.c.o: %.c
	@mkdir -p $(dir $@) $(dir $(DEPDIR)/$*.d)
	@$(CC) $(CFLAGS) -MMD -MP -MF $(DEPDIR)/$*.d -MT $@ -c $< -o $@
	@echo "  CC    $<"

$(OBJDIR)/%.S.o: %.S
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "  AS    $<"

.PHONY: all lib crt test clean info flag clang format line version gen-config help
.DEFAULT_GOAL := help

all: lib crt

lib: $(C_OBJS)
	@mkdir -p $(LIBDIR)
ifeq ($(BUILD_METHOD),static)
	@$(AR) $(ARFLAGS) $(LIB) $(C_OBJS)
	@echo "  AR    $(LIB)"
else
	@$(CC) $(LDFLAGS) -shared $(C_OBJS) -o $(LIB)
	@echo "  LD    $(LIB)"
endif

crt: $(S_OBJS)
	@mkdir -p $(LIBDIR)
	@cp $(S_OBJS) $(LIBDIR)/
	@$(foreach s,$(S_SRCS),echo "  CRT   $(s)";)

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
	@echo "\tmake crt                 - build crt1.o"
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
