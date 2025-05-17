# qlibc
A light-weight and portable C standard library. Designed for kernel.

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
make run
```

Basic build commands:
- `make all`           - Build the qlibc library
- `make info`          - Show the build configuration
- `make clean`         - Clean the build directory
- `make help`          - Show this help message
- `make test`          - Run all the test cases
- `make gnu`           - Build the test cases with GNU glibc
- `make test-<module>` - Build the test cases for a specific module




