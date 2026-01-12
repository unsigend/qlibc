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

# Configuration for qlibc

# Config for Tool chain
# TOOLCHAIN_PREFIX 	:= 	

# Config for architecture
# Supported architectures: i386, x86_64
ARCH                :=   	aarch64

# qlibc version
QLIBC_VERSION       :=   	0.1.0

# qlibc library name
QLIBC_NAME          :=   	qlibc

# qlibc ANSI/ISO C standard
QLIBC_C_STANDARD    :=   	c11

# debug mode
DEBUG               :=   	1

# Verbose mode
VERBOSE             :=   	0

# Config for build method
# Supported build methods: static, shared
BUILD_METHOD        :=   	static

# Make GNU (Only for test purpose)
USING_GNU           :=   	1
