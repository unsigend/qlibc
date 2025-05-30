# qlibc
A light-weight and portable C standard library. Designed for kernel and embedded system.

## Table of Contents


- [Introduction](#introduction)
- [Building](#building)
    - [Prerequisites](#prerequisites)
    - [Build Configuration](#build-configuration)
    - [Build Commands](#build-commands)
- [Headers](#headers)
- [Architecture Support](#architecture-support)
- [License](#license)
- [Contributing](#contributing)


## Introduction

qlibc is a lightweight and portable C standard library specifically designed for embedded systems and kernel development. It provides essential C standard library functions while maintaining minimal dependencies and a small footprint.

Key features:
- Freestanding implementation (no dependencies on host OS)
- Architecture-independent core with architecture-specific optimizations
- Supports both static and shared library builds
- Comprehensive test suite using Utest Library
- Original designed for kernel

## Building

qlibc use a simple and modular Makefile to build this project.

### Prerequisites

- GCC toolchain (or cross-compiler for target architecture)
- GNU Make

### Build Configuration

The build can be configured through environment variables or the `config/config.mk` file:

- `ARCH`: Target architecture (default: host architecture)
- `BUILD_METHOD`: Build method - "static" or "shared" (default: static) 
- `TOOLCHAIN_PREFIX`: Cross-compiler prefix if building for different architecture
- `DEBUG`: Enable debug build - 1 or 0 (default: 0)

### Build Commands

After finished configuration, to build qlibc, simply run:

```bash
make all
```

Basic build commands:
- `make all`           - Build the qlibc library
- `make info`          - Show the build configuration
- `make clean`         - Clean the build directory
- `make help`          - Show this help message
- `make test`          - Run all the test cases
- `make gnu`           - Build the test cases with GNU glibc
- `make test-<module>` - Build the test cases for a specific module


## Headers

The following standard C headers are supported in qlibc v0.1.0:

- [<assert.h>](https://github.com/unsigend/qlibc/blob/main/include/assert.h) 
- [<ctype.h>](https://github.com/unsigend/qlibc/blob/main/include/ctype.h) 
- <errno.h> 
- [<limits.h>](https://github.com/unsigend/qlibc/blob/main/include/limits.h) 
- <setjmp.h> 
- <signal.h>
- [<stdalign.h>](https://github.com/unsigend/qlibc/blob/main/include/stdalign.h) 
- <stdarg.h>
- [<stdbool.h>](https://github.com/unsigend/qlibc/blob/main/include/limits.h)
- [<stddef.h>](https://github.com/unsigend/qlibc/blob/main/include/stddef.h)
- [<stdint.h>](https://github.com/unsigend/qlibc/blob/main/include/stdint.h)
- <stdio.h> 
- <stdlib.h> 
- <stdnoreturn.h> 
- <string.h> 
- <time.h>


## Architecture Support

Currently qlibc supports the following hardware architectures:
- x86: 32-bit
- x86-64: 64-bit

Support for additional architectures may be added in future releases.


## License

qlibc is licensed under the GNU General Public License v3.0 (GPLv3). This means you are free to:

- Use the library for any purpose
- Study how it works and modify it
- Redistribute copies of the original
- Distribute modified versions

See the [LICENSE](LICENSE) file for the complete license text.

## Contributing

Contributions to qlibc are welcome! 
For bug reports and feature requests, please use the GitHub issue tracker.

