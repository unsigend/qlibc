# qlibc

A lightweight, portable C library for kernel and embedded systems.

## Table of Contents

- [Introduction](#introduction)
- [Building](#building)
  - [Prerequisites](#prerequisites)
  - [Configuration](#configuration)
  - [Build commands](#build-commands)
- [Headers](#headers)
  - [ANSI/ISO C Standard](#ansioso-c-standard-headers-support)
  - [Unix POSIX](#unix-posix-support)
  - [Extensions](#extensions-non-standard)
- [Design](#design)
  - [malloc](#malloc)
  - [stdio](#stdio)
- [Architecture support](#architecture-support)
- [License](#license)
- [Contributing](#contributing)

## Introduction

qlibc is a minimal C library aimed at embedded systems and kernel development. It provides a subset of ISO C and POSIX APIs with few dependencies and a small footprint.

**Features:**

- **Freestanding** — No reliance on a host libc; suitable for kernels and bare metal.
- **Portable** — Architecture-agnostic core with optional arch-specific code (e.g. `arch/$(ARCH)/`).
- **Flexible build** — Static (`.a`) or shared (`.so`/`.dylib`) via `config/config.mk`.
- **Tested** — Test suite (Utest) with optional comparison against GNU glibc.

## Building

### Prerequisites

- **GCC** (or a cross-compiler if targeting another architecture)
- **GNU Make**

### Configuration

Edit `config/config.mk` or use environment variables:

| Variable | Description | Example |
|----------|-------------|---------|
| `ARCH` | Target architecture | `x86_64`, `i386` |
| `BUILD_METHOD` | Library type | `static`, `shared` |
| `TOOLCHAIN_PREFIX` | Cross-compiler prefix | `x86_64-elf-gcc` |
| `DEBUG` | Debug build | `1` (debug), `0` (release) |
| `USING_GNU` | Link tests against glibc instead of qlibc | `1` (glibc), `0` (qlibc) |

### Build commands

From the project root:

```bash
make all    # Build the library (default)
make test   # Build and run all tests
```

| Command | Description |
|---------|-------------|
| `make all` | Build the qlibc library |
| `make info` | Show build configuration (arch, C standard, paths, etc.) |
| `make clean` | Remove build and lib output (and test build) |
| `make help` | Print this help |
| `make test` | Build qlibc (if needed) and run all test cases |
| `make test-<module>` | Build and run tests for one module (e.g. `make test-printf`) |
| `make clang` | Generate `compile_commands.json` via Bear (`bear -- make test -j4`) |

To run tests against **GNU glibc** for comparison, set `USING_GNU := 1` in `config/config.mk`, then run `make test`.

## Headers

### ANSI/ISO C Standard Headers Support

| Header | Description |
|--------|--------------|
| [<assert.h>](https://github.com/unsigend/qlibc/blob/main/include/assert.h) | Conditionally compiled macro that compares its argument to zero |
| [<ctype.h>](https://github.com/unsigend/qlibc/blob/main/include/ctype.h) | Functions to determine the type contained in character data |
| [<errno.h>](https://github.com/unsigend/qlibc/blob/main/include/errno.h) | Macros reporting error conditions |
| [<limits.h>](https://github.com/unsigend/qlibc/blob/main/include/limits.h) | Ranges of integer types |
| <setjmp.h> | Nonlocal jumps |
| [<signal.h>](https://github.com/unsigend/qlibc/blob/main/include/signal.h) | Signal handling |
| [<stdalign.h>](https://github.com/unsigend/qlibc/blob/main/include/stdalign.h) | alignas and alignof convenience macros |
| [<stdarg.h>](https://github.com/unsigend/qlibc/blob/main/include/stdarg.h) | Variable arguments |
| [<stdbool.h>](https://github.com/unsigend/qlibc/blob/main/include/stdbool.h) | Macros for boolean type |
| [<stddef.h>](https://github.com/unsigend/qlibc/blob/main/include/stddef.h) | Common macro definitions |
| [<stdint.h>](https://github.com/unsigend/qlibc/blob/main/include/stdint.h) | Fixed-width integer types |
| <stdio.h> | Standard input/output |
| [<stdlib.h>](https://github.com/unsigend/qlibc/blob/main/include/stdlib.h) | General utilities library |
| [<stdnoreturn.h>](https://github.com/unsigend/qlibc/blob/main/include/stdnoreturn.h) | noreturn convenience macro |
| [<string.h>](https://github.com/unsigend/qlibc/blob/main/include/string.h) | String handling |
| [<time.h>](https://github.com/unsigend/qlibc/blob/main/include/time.h) | Time/date utilities |

### Unix POSIX Support

| Header | Description |
|--------|--------------|
| [<elf.h>](https://github.com/unsigend/qlibc/blob/main/include/elf.h) | ELF header structures and macros |

### Extensions (Non-Standard)

| Header | Description |
|--------|--------------|
| [<ext/itoa.h>](https://github.com/unsigend/qlibc/blob/main/include/ext/itoa.h) | Integer-to-string conversion (e.g. ltostr, lltostr, ultostr, ulltostr) |

## Design

High-level design of selected subsystems. Details and APIs are in the source and headers.

### malloc

The allocator uses a **segregated free list**: 64 size classes (buckets) from a few dozen bytes up to several megabytes. Allocation picks the right bucket, then **best-fit** within that bucket; blocks can be split and the remainder is reinserted. Freed blocks are **coalesced** with adjacent free blocks to reduce fragmentation. Small allocations are served from a single **sbrk** grown heap, requests above the mmap threshold (128 KiB) use **mmap** directly and are freed with **munmap** (realloc uses **mremap** when possible). There is a single global heap, no arenas, and **no thread-safety** yet; locking and an arena-based design are planned for later.

### stdio

The stdio layer is built on POSIX file descriptors (read/write/open). Each **FILE** has a mode (read/write/append), optional internal buffer (full, line, or unbuffered), and separate read/write buffer pointers so the same stream can support both directions. Streams are linked into a global list so **fflush(NULL)** can flush all. **stdin**, **stdout**, and **stderr** are initialized at startup via a constructor: stdin/stdout are line-buffered, stderr is unbuffered. Buffers are allocated on first use with lazy loading, with **malloc**. The core helpers are **__refillbuf** (fill read buffer via read()) and **__flushbuf** (write buffered data with **__writeall**, which retries on EINTR/EAGAIN). This keeps the design minimal.

## Architecture support

- **x86** (i386, 32-bit)
- **x86-64** (64-bit)

Further architectures may be added later.

## License

qlibc is licensed under the GNU General Public License v3.0 (GPLv3). You may use, study, modify, and redistribute it under the terms of the license. See [LICENSE](LICENSE) for the full text.

## Contributing

Contributions are welcome. For bugs and feature requests, please open an issue on the GitHub issue tracker.
