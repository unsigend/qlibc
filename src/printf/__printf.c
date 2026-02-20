/* qlibc - A light-weight and portable C standard library
 * Copyright (C) 2025 Qiu Yixiang
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/* Internal implementation of printf family of functions. This source file
   should be a freestanding implementation of the core printf, which is
   independent of the standard library and no buffer related manipulation. */

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

/* Features supported:
   Specifiers: %c, %s, %d, %i, %o, %x, %X, %u, %p
   Flags:
      - left alignment: -
      - zero padding:   0
      - 0x prefix:      # (%x, %X, %o)
   Width:      fixed %Nd, dynamic %*d
   Precision:  fixed %.Nd, dynamic %.*d
   Length:     l (long), ll (long long), z (size_t), h (short)
   Format sequence is ordered: %[flags][width][precision][length][specifier]
*/

/* Specifiers */
enum {
  SPEC_C = 'c',
  SPEC_S = 's',
  SPEC_I = 'i',
  SPEC_D = 'd',
  SPEC_O = 'o',
  SPEC_X = 'x',
  SPEC_XX = 'X',
  SPEC_U = 'u',
  SPEC_P = 'p',
};

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define OUT_ERROR -1
#define INT_BUFFSZ                                                             \
  32 /* buffer size for integer conversion, enough for 64-bit integer */

/* State machine for the parser */
enum {
  STATE_NORMAL, /* Normal state, copy characters from format to buffer */
  STATE_FORMAT, /* Format state, parse the format string */
};

/* These enum values are used to pop arguments from the stack */
enum {
  ARG_PTR,
  ARG_SHORT,
  ARG_USHORT,
  ARG_CHAR,
  ARG_UCHAR,
  ARG_INT,
  ARG_UINT,
  ARG_LONG,
  ARG_ULONG,
  ARG_LLONG,
  ARG_ULLONG,
  ARG_IMAX,
  ARG_UMAX,
};

/* Output context */
struct _OUT_CTX {
  unsigned char *__buff; /* destination buffer */
  size_t __bufsz;        /* destination buffer size */
  size_t __pos;          /* current write position in __buff */
  int __total;           /* total bytes written */
};

/* Argument pack used for pop arguments from stack */
union __arg_pack {
  long double __f; /* float */
  uintmax_t __i;   /* integer */
  void *__p;       /* pointer */
};

/* forward declarations */
static void __fmt_uint(struct _OUT_CTX *__ctx, uintmax_t __u, int __base,
                       bool __upper);
/* %c specifier */
static void __out_c(struct _OUT_CTX *__ctx, unsigned char __ch);
/* %u specifier */
static void __out_u(struct _OUT_CTX *__ctx, uintmax_t __u);
/* %p specifier */
static void __out_p(struct _OUT_CTX *__ctx, void *__p);
/* %s specifier */
static void __out_s(struct _OUT_CTX *__ctx, const unsigned char *__str,
                    size_t __len);
/* %d specifier */
static void __out_i(struct _OUT_CTX *__ctx, intmax_t __i);
/* %o specifier */
static void __out_o(struct _OUT_CTX *__ctx, uintmax_t __o);
/* %x specifier */
static void __out_x(struct _OUT_CTX *__ctx, uintmax_t __x);
/* %X specifier */
static void __out_xx(struct _OUT_CTX *__ctx, uintmax_t __xx);

#define BUFF_IS_FULL(CTX)                                                      \
  (((CTX)->__pos >= (CTX)->__bufsz)) /* buffer is full */
#define BUFF_LEFT(CTX)                                                         \
  (((CTX)->__bufsz - (CTX)->__pos)) /* buffer left size                        \
                                     */

/* Format an unsigned integer to a string in the given base and write to the
   buffer */
static void __fmt_uint(struct _OUT_CTX *__ctx, uintmax_t __u, int __base,
                       bool __upper) {
  unsigned char __buff[INT_BUFFSZ];
  size_t __len = 0;
  do {
    int __digit = __u % __base;
    unsigned char __cw = __digit < 10 ? '0' + __digit
                         : __upper    ? 'A' + __digit - 10
                                      : 'a' + __digit - 10;
    __buff[__len++] = __cw;
    __u /= __base;
  } while (__u);

  // reverse the buffer
  for (size_t __i = 0, __j = __len - 1; __i < __j; __i++, __j--) {
    unsigned char __tmp = __buff[__i];
    __buff[__i] = __buff[__j];
    __buff[__j] = __tmp;
  }
  __out_s(__ctx, __buff, __len);
}

/* Write a single character to the buffer and update the context */
static void __out_c(struct _OUT_CTX *__ctx, unsigned char __ch) {
  __ctx->__total++;
  if (!BUFF_IS_FULL(__ctx))
    __ctx->__buff[__ctx->__pos++] = __ch;
}

/* Write a string to the buffer and update the context, truncate if the string
   is longer than the buffer */
static void __out_s(struct _OUT_CTX *__ctx, const unsigned char *__str,
                    size_t __len) {
  size_t __n = MIN(__len, BUFF_LEFT(__ctx));
  __ctx->__total += __len;
  if (__n) {
    memcpy(__ctx->__buff + __ctx->__pos, __str, __n);
    __ctx->__pos += __n;
  }
}

/* Write an signed integer to the buffer and update the context */
static void __out_i(struct _OUT_CTX *__ctx, intmax_t __i) {
  if (__i < 0) {
    __out_c(__ctx, '-');
    __fmt_uint(__ctx, -((uintmax_t)__i), 10, false);
  } else {
    __fmt_uint(__ctx, (uintmax_t)__i, 10, false);
  }
}

/* Write an unsigned integer to the buffer and update the context */
static void __out_u(struct _OUT_CTX *__ctx, uintmax_t __u) {
  __fmt_uint(__ctx, __u, 10, false);
}

/* Write a pointer to the buffer and update the context */
static void __out_p(struct _OUT_CTX *__ctx, void *__p) {
  __out_c(__ctx, '0');
  __out_c(__ctx, 'x');
  __fmt_uint(__ctx, (uintmax_t)__p, 16, false);
}

/* Write a hexadecimal integer to the buffer and update the context, in lower
   case */
static void __out_x(struct _OUT_CTX *__ctx, uintmax_t __x) {
  __fmt_uint(__ctx, __x, 16, false);
}

/* Write a hexadecimal integer to the buffer and update the context, in upper
   case */
static void __out_xx(struct _OUT_CTX *__ctx, uintmax_t __xx) {
  __fmt_uint(__ctx, __xx, 16, true);
}

/* Write an octal integer to the buffer and update the context */
static void __out_o(struct _OUT_CTX *__ctx, uintmax_t __o) {
  __fmt_uint(__ctx, __o, 8, false);
}

/* Pop arguments from the argument list based on promotion rules, the
   implementation is based on the reference implementation of the musl C
   library 1.2.5 */
static void __pop_arg(union __arg_pack *__arg, int __type, va_list *__ap) {
  switch (__type) {
  case ARG_PTR:
    __arg->__p = va_arg(*__ap, void *);
    break;
  case ARG_SHORT:
    __arg->__i = va_arg(*__ap, int);
    break;
  case ARG_USHORT:
    __arg->__i = va_arg(*__ap, unsigned int);
    break;
  case ARG_CHAR:
    __arg->__i = va_arg(*__ap, int);
    break;
  case ARG_UCHAR:
    __arg->__i = va_arg(*__ap, unsigned int);
    break;
  case ARG_INT:
    __arg->__i = va_arg(*__ap, int);
    break;
  case ARG_UINT:
    __arg->__i = va_arg(*__ap, unsigned int);
    break;
  case ARG_LONG:
    __arg->__i = va_arg(*__ap, long);
    break;
  case ARG_ULONG:
    __arg->__i = va_arg(*__ap, unsigned long);
    break;
  case ARG_LLONG:
    __arg->__i = va_arg(*__ap, long long);
    break;
  case ARG_ULLONG:
    __arg->__i = va_arg(*__ap, unsigned long long);
    break;
  case ARG_IMAX:
    __arg->__i = va_arg(*__ap, intmax_t);
    break;
  case ARG_UMAX:
    __arg->__i = va_arg(*__ap, uintmax_t);
    break;
  }
}

/* Internal core implementation of formatted output. With parser and
   formatter support. */
int __printf_core(char *restrict __buffer, size_t __bufsz,
                  const char *restrict __format, va_list __vlist) {
  struct _OUT_CTX __ctx = {
      .__buff = (unsigned char *)__buffer,
      .__pos = 0,
      .__total = 0,
  };
  int __stat = STATE_NORMAL;
  union __arg_pack __arg;
  va_list __ap;
  size_t __w = 0, __p = 0;
  (void)__w;
  (void)__p;

  /* the copy allows passing va_list* even if va_list is an array */
  va_copy(__ap, __vlist);

  if (!__ctx.__buff || !__bufsz)
    __ctx.__bufsz = 0;
  else
    __ctx.__bufsz = __bufsz - 1;

  while (__format && *__format) {
    switch (__stat) {
    case STATE_NORMAL: {
      if (*__format == '%')
        __stat = STATE_FORMAT;
      else
        __out_c(&__ctx, *__format);
      break;
    }
    case STATE_FORMAT: {
      switch (*__format) {
      case '%':
        __out_c(&__ctx, '%');
        __stat = STATE_NORMAL;
        break;
      case SPEC_C:
        __pop_arg(&__arg, ARG_CHAR, &__ap);
        __out_c(&__ctx, (unsigned char)__arg.__i);
        __stat = STATE_NORMAL;
        break;
      case SPEC_S:
        __pop_arg(&__arg, ARG_PTR, &__ap);
        if (!__arg.__p)
          __out_s(&__ctx, (unsigned char *)"(null)", 6);
        else
          __out_s(&__ctx, (unsigned char *)__arg.__p,
                  strlen((char *)__arg.__p));
        __stat = STATE_NORMAL;
        break;
      case SPEC_I:
      case SPEC_D:
        __pop_arg(&__arg, ARG_INT, &__ap);
        __out_i(&__ctx, (intmax_t)__arg.__i);
        __stat = STATE_NORMAL;
        break;
      case SPEC_O:
        // TODO: implement %o specifier
        break;
      case SPEC_X:
        // TODO: implement %x specifier
        break;
      case SPEC_XX:
        // TODO: implement %X specifier
        break;
      case SPEC_U:
        // TODO: implement %u specifier
        break;
      case SPEC_P:
        // TODO: implement %p specifier
        break;
      }
      break;
    }
    }
    __format++;
  }

  if (__buffer && __bufsz)
    __ctx.__buff[MIN(__ctx.__pos, __ctx.__bufsz)] = '\0';

  va_end(__ap);
  return __ctx.__total;
}