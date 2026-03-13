# qlibc

## Introduction
A minimal, freestanding C library for embedded systems and kernel use. Implements a subset of ISO C and POSIX with no host libc dependency. 


Current Release Version: **0.1.0**.

## Building

**Prerequisites:** GCC (or cross-compiler), GNU Make.

**Configuration:** Edit `config/config.mk` or set:

    ARCH              x86_64 | i386
    BUILD_METHOD      static | shared
    TOOLCHAIN_PREFIX  Cross-compiler prefix, or empty
    DEBUG             1 = debug, 0 = release
    USING_GNU         1 = glibc dry run test, 0 = qlibc

More details: [config/config.mk](https://github.com/unsigend/qlibc/blob/main/config/config.mk)


**Commands** :

    make all           Build library and CRT objects
    make lib           Build library only
    make crt           Build CRT only
    make test          Build and run tests
    make test-<module> Run tests for one module
    make info          Show build configuration
    make clean         Remove build and lib output
    make help          List targets
    make format        Format .c and .h with clang-format
    make clang         Generate compile_commands.json
    make flag          Show compile flags


## Headers

### ANSI/ISO C

| Header | Description |
|--------|-------------|
| [assert.h](https://github.com/unsigend/qlibc/blob/main/include/assert.h) | Assertion macro |
| [ctype.h](https://github.com/unsigend/qlibc/blob/main/include/ctype.h) | Character classification |
| [errno.h](https://github.com/unsigend/qlibc/blob/main/include/errno.h) | Error codes |
| [fcntl.h](https://github.com/unsigend/qlibc/blob/main/include/fcntl.h) | File control options |
| [inttypes.h](https://github.com/unsigend/qlibc/blob/main/include/inttypes.h) | Format specifiers for stdint |
| [limits.h](https://github.com/unsigend/qlibc/blob/main/include/limits.h) | Integer limits |
| [signal.h](https://github.com/unsigend/qlibc/blob/main/include/signal.h) | Signal handling |
| [stdalign.h](https://github.com/unsigend/qlibc/blob/main/include/stdalign.h) | alignas / alignof |
| [stdarg.h](https://github.com/unsigend/qlibc/blob/main/include/stdarg.h) | Variable arguments |
| [stdbool.h](https://github.com/unsigend/qlibc/blob/main/include/stdbool.h) | bool macro |
| [stddef.h](https://github.com/unsigend/qlibc/blob/main/include/stddef.h) | ptrdiff_t, size_t, NULL |
| [stdint.h](https://github.com/unsigend/qlibc/blob/main/include/stdint.h) | Fixed-width integers |
| [stdio.h](https://github.com/unsigend/qlibc/blob/main/include/stdio.h) | Stream I/O |
| [stdlib.h](https://github.com/unsigend/qlibc/blob/main/include/stdlib.h) | General utilities |
| [stdnoreturn.h](https://github.com/unsigend/qlibc/blob/main/include/stdnoreturn.h) | noreturn macro |
| [string.h](https://github.com/unsigend/qlibc/blob/main/include/string.h) | String and memory |
| [time.h](https://github.com/unsigend/qlibc/blob/main/include/time.h) | Time/date |
| [unistd.h](https://github.com/unsigend/qlibc/blob/main/include/unistd.h) | POSIX API |
| [elf.h](https://github.com/unsigend/qlibc/blob/main/include/elf.h) | ELF structures |
| [syscall.h](https://github.com/unsigend/qlibc/blob/main/include/syscall.h) | Syscall numbers |
| [termios.h](https://github.com/unsigend/qlibc/blob/main/include/termios.h) | Terminal I/O |
| [feature.h](https://github.com/unsigend/qlibc/blob/main/include/feature.h) | Feature macros |


### POSIX system

| Header | Description |
|--------|-------------|
| [sys/ioctl.h](https://github.com/unsigend/qlibc/blob/main/include/sys/ioctl.h) | ioctl constants |
| [sys/mman.h](https://github.com/unsigend/qlibc/blob/main/include/sys/mman.h) | mmap, munmap |
| [sys/stat.h](https://github.com/unsigend/qlibc/blob/main/include/sys/stat.h) | stat, fstat |
| [sys/syscall.h](https://github.com/unsigend/qlibc/blob/main/include/sys/syscall.h) | Syscall wrappers |
| [sys/types.h](https://github.com/unsigend/qlibc/blob/main/include/sys/types.h) | POSIX system types |
| [sys/uio.h](https://github.com/unsigend/qlibc/blob/main/include/sys/uio.h) | Scatter-gather I/O |
| [sys/wait.h](https://github.com/unsigend/qlibc/blob/main/include/sys/wait.h) | wait, waitpid |

### Extensions (Non-Standard)

| Header | Description |
|--------|-------------|
| [ext/itoa.h](https://github.com/unsigend/qlibc/blob/main/include/ext/itoa.h) | Integer-to-string |
| [ext/malloc.h](https://github.com/unsigend/qlibc/blob/main/include/ext/malloc.h) | Malloc extension API |
| [ext/printf.h](https://github.com/unsigend/qlibc/blob/main/include/ext/printf.h) | printf core |
| [ext/printfcore.h](https://github.com/unsigend/qlibc/blob/main/include/ext/printfcore.h) | printf core |
| [ext/scanf.h](https://github.com/unsigend/qlibc/blob/main/include/ext/scanf.h) | scanf core |
| [ext/scanfcore.h](https://github.com/unsigend/qlibc/blob/main/include/ext/scanfcore.h) | scanf core |

## Architectures

Supported targets: **x86_64** and **i386**. Set `ARCH` in `config/config.mk`; use a `TOOLCHAIN_PREFIX` when cross-compiling in a freestanding environment.

## License

qlibc is licensed under the **GNU General Public License v3.0**. See [LICENSE](LICENSE) for the full text. You may use, modify, and distribute it under the terms of the GPLv3.

## Contributing

Contributions are welcome. Please open an issue for bugs or feature requests, and submit pull requests against the main repository.
