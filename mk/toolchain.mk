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

ROOTDIR ?= .

AS     := $(CC)
LD     := $(CC)
AR     ?= ar
PYTHON ?= python3

HOST_OS   := $(shell uname -s)
HOST_ARCH := $(shell uname -m)

INCDIR  := $(ROOTDIR)/include
ARCHDIR := $(ROOTDIR)/arch
LIBDIR  := $(ROOTDIR)/lib

ifeq ($(ARCH),$(filter $(ARCH),i386 x86_64))
else
    $(error unsupported ARCH '$(ARCH)' — valid: i386, x86_64)
endif

ifeq ($(ARCH),i386)
    CFLAGS_ARCH := -m32
else
    CFLAGS_ARCH :=
endif

ifeq ($(DEBUG),1)
    CFLAGS_OPT := -O0 -g
else
    CFLAGS_OPT := -O2
endif

# freestanding
CFLAGS_FREESTANDING := -ffreestanding -fno-builtin -nostdinc

# warning
CFLAGS_WARN := -Wall -Wextra -Werror
CFLAGS_WARN += -Wstrict-prototypes
CFLAGS_WARN += -Wmissing-prototypes

# include
CFLAGS_INC  := -I $(INCDIR) -I $(ARCHDIR)/$(ARCH)/include

CFLAGS  := -std=$(STD_C) $(CFLAGS_WARN) $(CFLAGS_FREESTANDING) \
           $(CFLAGS_OPT) $(CFLAGS_ARCH) $(CFLAGS_INC)
LDFLAGS := -std=$(STD_C) -nostdlib -nolibc $(CFLAGS_ARCH)
ARFLAGS := -rcs

ifeq ($(BUILD_METHOD),static)
    LIB_SUFFIX := .a
else ifeq ($(HOST_OS),Darwin)
    LIB_SUFFIX := .dylib
else
    LIB_SUFFIX := .so
endif

LIB := $(LIBDIR)/lib$(LIBNAME)$(LIB_SUFFIX)
