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

MKDIR     := mk
SCRIPTDIR := scripts

include $(MKDIR)/config.mk
include $(MKDIR)/toolchain.mk

BUILDDIR := build
DEPDIR   := $(BUILDDIR)/dep
OBJDIR   := $(BUILDDIR)/obj
SRCDIR   := src

SRCS      := $(shell find $(SRCDIR) -name "*.c")
SRCS_ARCH := $(shell find $(ARCHDIR)/$(ARCH)/src -name "*.c")
SRCS_CRT  := $(shell find $(ARCHDIR)/$(ARCH)/crt -name "*.S")

OBJS      := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.c.o,$(SRCS))
OBJS_ARCH := $(patsubst $(ARCHDIR)/$(ARCH)/src/%.c,$(OBJDIR)/$(ARCH)/%.c.o,$(SRCS_ARCH))
OBJS_CRT  := $(patsubst $(ARCHDIR)/$(ARCH)/crt/%.S,$(OBJDIR)/$(ARCH)/crt/%.S.o,$(SRCS_CRT))
DEPS      := $(patsubst $(OBJDIR)/%.o,$(DEPDIR)/%.d,$(OBJS) $(OBJS_ARCH))

-include $(DEPS)

$(OBJDIR)/%.c.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@) $(dir $(DEPDIR)/$*.c.d)
	@$(CC) $(CFLAGS) -MMD -MP -MF $(DEPDIR)/$*.c.d -MT $@ -c $< -o $@
	@echo "  CC    $<"

$(OBJDIR)/$(ARCH)/%.c.o: $(ARCHDIR)/$(ARCH)/src/%.c
	@mkdir -p $(dir $@) $(dir $(DEPDIR)/$(ARCH)/$*.c.d)
	@$(CC) $(CFLAGS) -MMD -MP -MF $(DEPDIR)/$(ARCH)/$*.c.d -MT $@ -c $< -o $@
	@echo "  CC    $<"

$(OBJDIR)/$(ARCH)/crt/%.S.o: $(ARCHDIR)/$(ARCH)/crt/%.S
	@mkdir -p $(dir $@)
	@$(AS) $(CFLAGS) -c $< -o $@
	@echo "  AS    $<"

.PHONY: all lib crt clean info flag clang format line version gen-config help
.DEFAULT_GOAL := help

all: lib crt

lib: $(OBJS) $(OBJS_ARCH)
	@mkdir -p $(LIBDIR)
ifeq ($(BUILD_METHOD),static)
	@$(AR) $(ARFLAGS) $(LIB) $(OBJS) $(OBJS_ARCH)
	@echo "  AR    $(LIB)"
else
	@$(CC) $(LDFLAGS) -shared $(OBJS) $(OBJS_ARCH) -o $(LIB)
	@echo "  LD    $(LIB)"
endif

crt: $(OBJS_CRT)
	@mkdir -p $(LIBDIR)
	@cp $(OBJS_CRT) $(LIBDIR)/
	@echo "  CRT   $(LIBDIR)"

clean:
	@rm -rf $(BUILDDIR) $(LIBDIR)

info:
	@echo "qlibc v$(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH)"
	@echo "  arch          $(ARCH)"
	@echo "  host          $(HOST_OS)/$(HOST_ARCH)"
	@echo "  method        $(BUILD_METHOD)"
	@echo "  std           $(STD_C)"
	@echo "  cc            $(CC)"
	@echo "  ar            $(AR)"
	@echo "  debug         $(if $(filter 1,$(DEBUG)),on,off)"

flag:
	@echo "CFLAGS:  $(CFLAGS)"
	@echo "LDFLAGS: $(LDFLAGS)"
	@echo "ARFLAGS: $(ARFLAGS)"

clang:
	@$(MAKE) clean
	@bear -- $(MAKE) all

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
	@echo "Copyright (C) 2025 Qiu Yixiang"
	@echo ""
	@echo "USAGE:"
	@echo "\tmake all                 - build the library and CRT objects"
	@echo "\tmake lib                 - build the library"
	@echo "\tmake crt                 - build the CRT objects"
	@echo ""
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
