# qlibc

A minimal freestanding C library for Linux and qunix. Subset of ISO C and POSIX no host libc.

Current release: **0.2.0**.

## Building

GCC (or a cross-compiler) and GNU Make. Edit [config.cfg](config.cfg), then `make gen-config`. `CONFIG_*` keys go to `include/config.h` all keys go to `mk/config.mk` with the prefix stripped.

    make all             library and CRT
    make lib             library only
    make crt             CRT objects
    make test            build and run tests

    make clean           remove build and lib output
    make help            list targets
    make info            show build configuration
    make flag            show compile flags
    make format          format .c and .h with clang-format
    make clang           generate compile_commands.json
    make line            count source lines (arch, include, src)
    make version         show library version
    make gen-config      generate mk/config.mk and include/config.h

## Headers

### ANSI/ISO C

| Header | Description |
|--------|-------------|
| [assert.h](include/assert.h) | Assertions |
| [ctype.h](include/ctype.h) | Character classification |
| [errno.h](include/errno.h) | `errno` |
| [inttypes.h](include/inttypes.h) | `intmax_t` conversions |
| [limits.h](include/limits.h) | Integer limits |
| [stdalign.h](include/stdalign.h) | `alignas` / `alignof` |
| [stdarg.h](include/stdarg.h) | Variable arguments |
| [stdbool.h](include/stdbool.h) | `bool` |
| [stddef.h](include/stddef.h) | `size_t`, `NULL` |
| [stdint.h](include/stdint.h) | Fixed-width integers |
| [stdio.h](include/stdio.h) | Stream I/O |
| [stdlib.h](include/stdlib.h) | Utilities, malloc, env |
| [stdnoreturn.h](include/stdnoreturn.h) | `noreturn` |
| [string.h](include/string.h) | String and memory |
| [time.h](include/time.h) | Clocks and `nanosleep` |

### POSIX

| Header | Description |
|--------|-------------|
| [fcntl.h](include/fcntl.h) | `open`, `fcntl` |
| [sched.h](include/sched.h) | `sched_yield` |
| [signal.h](include/signal.h) | Signals |
| [unistd.h](include/unistd.h) | POSIX process and file APIs |
| [sys/ioctl.h](include/sys/ioctl.h) | `ioctl` |
| [sys/mman.h](include/sys/mman.h) | `mmap`, `mprotect`, `msync` |
| [sys/mount.h](include/sys/mount.h) | `mount`, `umount` |
| [sys/reboot.h](include/sys/reboot.h) | `reboot` |
| [sys/stat.h](include/sys/stat.h) | `stat`, `mkdir`, `chmod` |
| [sys/syscall.h](include/sys/syscall.h) | `SYS_*` aliases |
| [sys/types.h](include/sys/types.h) | POSIX types |
| [sys/uio.h](include/sys/uio.h) | `readv` / `writev` |
| [sys/wait.h](include/sys/wait.h) | `wait`, `waitpid` |

### Other

| Header | Description |
|--------|-------------|
| [elf.h](include/elf.h) | ELF types |
| [feature.h](include/feature.h) | Language-version macros |
| [syscall.h](include/syscall.h) | Syscall numbers |

### Extensions

| Header | Description |
|--------|-------------|
| [ext/atoi.h](include/ext/atoi.h) | `atoi` family |
| [ext/env.h](include/ext/env.h) | `setenv` family |
| [ext/itoa.h](include/ext/itoa.h) | Integer to string |
| [ext/malloc.h](include/ext/malloc.h) | Allocator |
| [ext/printf.h](include/ext/printf.h) | printf internals |
| [ext/scanf.h](include/ext/scanf.h) | scanf internals |
| [ext/strtol.h](include/ext/strtol.h) | `strto*` family |

## Architectures

**x86_64**, **i386**, and **aarch64**.

## Planning

### ANSI/ISO C

Will be added: `rand` / `srand` / `RAND_MAX`; calendar time (`time`, `struct tm`, `gmtime` / `localtime` / `mktime`, `asctime` / `ctime`, `strftime`); `setjmp` / `longjmp`.

### POSIX threads

`<pthread.h>`: create, join, detach, exit, self; mutex, condvar, rwlock, barrier; TLS keys.

### Allocator

Per-CPU cache and arena allocator, using thread/CPU identity from pthreads.

### Thread-safe stdio

Rebuild stdio around per-stream locks (`flockfile` / `funlockfile`) and a file-list lock. 

### Re-entrant interfaces

Add caller-owned / `_r` and bounds-checked `_s` variants (`strtok_r`, `gmtime_r`, `strerror_r`, and similar) once locking and TLS exist.

## License

qlibc is licensed under the **GNU General Public License v3.0**. See [LICENSE](LICENSE) for the full text. You may use, modify, and distribute it under the terms of the GPLv3.

## Contributing

Contributions are welcome. Please open an issue for bugs or feature requests, and submit pull requests against the main repository.
