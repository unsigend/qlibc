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

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>

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
  ARG_SIZE_T,
  ARG_SSIZE_T,
};

/* Length modifiers */
enum {
  LEN_NONE,
  LEN_H,
  LEN_HH,
  LEN_L,
  LEN_LL,
  LEN_Z,
};

/* Output context */
struct _OUT_CTX {
  unsigned char *__buff; /* destination buffer */
  size_t __bufsz;        /* destination buffer size */
  size_t __pos;          /* current write position in __buff */
  int __total;           /* total bytes written */
};

#define BUFF_IS_FULL(CTX)                                                      \
  (((CTX)->__pos >= (CTX)->__bufsz)) /* buffer is full */
#define BUFF_LEFT(CTX)                                                         \
  (((CTX)->__bufsz - (CTX)->__pos)) /* buffer left size                        \
                                     */

/* Argument pack used for pop arguments from stack */
union __arg_pack {
  long double __f; /* float */
  uintmax_t __i;   /* integer */
  void *__p;       /* pointer */
};

/* Format specification */
struct __fmt_spec {
  int __width;     /* width specifier */
  int __precision; /* precision specifier */
  int __length;    /* length modifier */
  int __flags;     /* flags */
};

#define FLAG_SET(F, FLAG) ((F) |= (FLAG))    /* set flag */
#define FLAG_CLEAR(F, FLAG) ((F) &= ~(FLAG)) /* clear flag */

#define FLAG_PADDING_ZERO 0x01 /* zero padding flag */
#define FLAG_LEFT_ALIGN 0x02   /* left align flag */
#define FLAG_PREFIX 0x04       /* prefix flag */

#define FLAG_IS_PADDING_ZERO(F)                                                \
  ((F) & FLAG_PADDING_ZERO) /* check if padding zero flag is set */
#define FLAG_IS_LEFT_ALIGN(F)                                                  \
  ((F) & FLAG_LEFT_ALIGN) /* check if left align flag is set */
#define FLAG_IS_PREFIX(F)                                                      \
  ((F) & FLAG_PREFIX) /* check if prefix flag is set                           \
                       */
#define SPEC_RESET(SPEC)                                                       \
  do {                                                                         \
    memset(SPEC, 0, sizeof(struct __fmt_spec));                                \
    (SPEC)->__precision = -1;                                                  \
    (SPEC)->__length = LEN_NONE;                                               \
  } while (0)

/* Write an unsigned integer to the buffer, without sign handling and NULL
   terminator. Return the number of characters written. */
static size_t __write_num(unsigned char *buff, uintmax_t val, int base,
                          bool upper) {
  unsigned char __buff[INT_BUFFSZ];
  size_t __len = 0;
  do {
    int __digit = val % base;
    unsigned char __cw = __digit < 10 ? '0' + __digit
                         : upper      ? 'A' + __digit - 10
                                      : 'a' + __digit - 10;
    __buff[__len++] = __cw;
    val /= base;
  } while (val);

  /* reverse the buffer in place */
  for (size_t __i = 0, __j = __len - 1; __i < __j; __i++, __j--) {
    unsigned char __tmp = __buff[__i];
    __buff[__i] = __buff[__j];
    __buff[__j] = __tmp;
  }
  /* copy the buffer to the output buffer */
  memcpy(buff, __buff, __len);
  return __len;
}

/* Write a single character to the buffer and update the context */
static void __ctx_outc(struct _OUT_CTX *__ctx, unsigned char __ch) {
  __ctx->__total++;
  if (!BUFF_IS_FULL(__ctx))
    __ctx->__buff[__ctx->__pos++] = __ch;
}

/* Write a string to the buffer and update the context, truncate if the string
   is longer than the buffer */
static void __ctx_outs(struct _OUT_CTX *__ctx, const unsigned char *__str,
                       size_t __len) {
  size_t __n = MIN(__len, BUFF_LEFT(__ctx));
  __ctx->__total += __len;
  if (__n) {
    memcpy(__ctx->__buff + __ctx->__pos, __str, __n);
    __ctx->__pos += __n;
  }
}

/* Write padding to the buffer and update the context */
static void __ctx_outpad(struct _OUT_CTX *__ctx, int __len,
                         unsigned char __padding) {
  while (__len-- > 0) {
    __ctx_outc(__ctx, __padding);
  }
}

/* Emit the prefix, body, fillings (zeros) and padding (spaces or zeros) to the
 * context */
static void __ctx_emit(struct _OUT_CTX *__ctx, struct __fmt_spec *__spec,
                       const unsigned char *__prefix, size_t __prefixlen,
                       const unsigned char *__body, size_t __bodylen,
                       size_t __fillinglen) {
  size_t total = __prefixlen + __fillinglen + __bodylen;
  size_t padlen = (size_t)(MAX(0, (int)(__spec->__width - total)));

  /* left align */
  if (FLAG_IS_LEFT_ALIGN(__spec->__flags)) {
    /* Format: [prefix][fillings][body][padding(spaces)] */
    __ctx_outs(__ctx, __prefix, __prefixlen);
    __ctx_outpad(__ctx, __fillinglen, '0');
    __ctx_outs(__ctx, __body, __bodylen);
    __ctx_outpad(__ctx, padlen, ' ');
  }
  /* right align */
  else {
    if (__spec->__precision >= 0) {
      /* Format: [padding(spaces)][prefix][fillings][body] */
      __ctx_outpad(__ctx, padlen, ' ');
      __ctx_outs(__ctx, __prefix, __prefixlen);
      __ctx_outpad(__ctx, __fillinglen, '0');
      __ctx_outs(__ctx, __body, __bodylen);

    } else {
      if (FLAG_IS_PADDING_ZERO(__spec->__flags)) {
        /* Format: [prefix][padding(zeros)][body] */
        __ctx_outs(__ctx, __prefix, __prefixlen);
        __ctx_outpad(__ctx, padlen, '0');
        __ctx_outs(__ctx, __body, __bodylen);
      } else {
        /* Format: [padding(spaces)][prefix][body] */
        __ctx_outpad(__ctx, padlen, ' ');
        __ctx_outs(__ctx, __prefix, __prefixlen);
        __ctx_outs(__ctx, __body, __bodylen);
      }
    }
  }
}

/* Write a number to the context */
static void ctx_outnum(struct _OUT_CTX *ctx, struct __fmt_spec *spec,
                       uintmax_t val, int base, bool upper,
                       const unsigned char *prefix, size_t prefixlen) {
  unsigned char buff[INT_BUFFSZ];
  size_t len;
  if (!spec->__precision && !val)
    len = 0;
  else
    len = __write_num(buff, val, base, upper);
  size_t fillinglen = (size_t)(MAX(0, (int)(spec->__precision - len)));
  __ctx_emit(ctx, spec, prefix, prefixlen, buff, len, fillinglen);
}

/* Write a string to the context */
static void ctx_outs(struct _OUT_CTX *ctx, struct __fmt_spec *spec,
                     const unsigned char *str, size_t len) {
  if (spec->__precision >= 0) {
    size_t __min_len = MIN((size_t)spec->__precision, len);
    FLAG_CLEAR(spec->__flags, FLAG_PADDING_ZERO);
    __ctx_emit(ctx, spec, NULL, 0, str, __min_len, 0);
  } else
    __ctx_emit(ctx, spec, NULL, 0, str, len, 0);
}

/* Write a single character to the context, just a thin wrapper of __ctx_outc
   for consistency */
static inline __attribute__((always_inline)) void ctx_outc(struct _OUT_CTX *ctx,
                                                           unsigned char ch) {
  __ctx_outc(ctx, ch); /* inline the __ctx_outc function */
}

/* Get the signed argument type based on the length modifier */
static int signed_arg_type(int len) {
  switch (len) {
  case LEN_HH:
    return ARG_CHAR;
  case LEN_H:
    return ARG_SHORT;
  case LEN_L:
    return ARG_LONG;
  case LEN_LL:
    return ARG_LLONG;
  case LEN_Z:
    return ARG_SSIZE_T;
  default:
    return ARG_INT;
  }
}

/* Get the unsigned argument type based on the length modifier */
static int unsigned_arg_type(int len) {
  switch (len) {
  case LEN_HH:
    return ARG_UCHAR;
  case LEN_H:
    return ARG_USHORT;
  case LEN_L:
    return ARG_ULONG;
  case LEN_LL:
    return ARG_ULLONG;
  case LEN_Z:
    return ARG_SIZE_T;
  default:
    return ARG_UINT;
  }
}

/* Pop arguments from the argument list based on promotion rules, the
   implementation is based on the reference implementation of the musl C
   library 1.2.5 */
static void pop_arg(union __arg_pack *__arg, int __type, va_list *__ap) {
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
  case ARG_SIZE_T:
    __arg->__i = va_arg(*__ap, size_t);
    break;
  case ARG_SSIZE_T:
    __arg->__i = va_arg(*__ap, ssize_t);
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
  struct __fmt_spec __spec = {
      .__width = 0,
      .__precision = -1, /* -1 means precision is not set */
      .__flags = 0,
  };
  int __stat = STATE_NORMAL;
  union __arg_pack __arg;
  bool __reach_precision = false;
  va_list __ap;

  /* the copy allows passing va_list* even if va_list is an array */
  va_copy(__ap, __vlist);

  if (!__ctx.__buff || !__bufsz)
    __ctx.__bufsz = 0;
  else
    __ctx.__bufsz = __bufsz - 1;

  while (__format && *__format) {
    switch (__stat) {
    case STATE_NORMAL: {
      if (*__format == '%') {
        SPEC_RESET(&__spec);
        __reach_precision = false;
        __stat = STATE_FORMAT;
      } else
        ctx_outc(&__ctx, *__format);
      break;
    }
    case STATE_FORMAT: {
      switch (*__format) {
      case '%':
        ctx_outc(&__ctx, '%');
        __stat = STATE_NORMAL;
        break;
      /* specifiers */
      case SPEC_C:
        pop_arg(&__arg, ARG_CHAR, &__ap);
        ctx_outs(&__ctx, &__spec, (unsigned char *)&__arg.__i, 1);
        __stat = STATE_NORMAL;
        break;
      case SPEC_S:
        pop_arg(&__arg, ARG_PTR, &__ap);
        if (!__arg.__p)
          ctx_outs(&__ctx, &__spec, (unsigned char *)"(null)", 6);
        else
          ctx_outs(&__ctx, &__spec, (unsigned char *)__arg.__p,
                   strlen((char *)__arg.__p));
        __stat = STATE_NORMAL;
        break;
      case SPEC_I:
      case SPEC_D:
        pop_arg(&__arg, signed_arg_type(__spec.__length), &__ap);
        if ((intmax_t)__arg.__i < 0) {
          ctx_outnum(&__ctx, &__spec, -(uintmax_t)(intmax_t)__arg.__i, 10,
                     false, (unsigned char *)"-", 1);
        } else {
          ctx_outnum(&__ctx, &__spec, __arg.__i, 10, false, NULL, 0);
        }
        __stat = STATE_NORMAL;
        break;
      case SPEC_O:
        pop_arg(&__arg, unsigned_arg_type(__spec.__length), &__ap);
        if (FLAG_IS_PREFIX(__spec.__flags) && __arg.__i != 0) {
          ctx_outnum(&__ctx, &__spec, __arg.__i, 8, false, (unsigned char *)"0",
                     1);
        } else {
          ctx_outnum(&__ctx, &__spec, __arg.__i, 8, false, NULL, 0);
        }
        __stat = STATE_NORMAL;
        break;
      case SPEC_X:
        pop_arg(&__arg, unsigned_arg_type(__spec.__length), &__ap);
        if (FLAG_IS_PREFIX(__spec.__flags) && __arg.__i != 0) {
          ctx_outnum(&__ctx, &__spec, __arg.__i, 16, false,
                     (unsigned char *)"0x", 2);
        } else {
          ctx_outnum(&__ctx, &__spec, __arg.__i, 16, false, NULL, 0);
        }
        __stat = STATE_NORMAL;
        break;
      case SPEC_XX:
        pop_arg(&__arg, unsigned_arg_type(__spec.__length), &__ap);
        if (FLAG_IS_PREFIX(__spec.__flags) && __arg.__i != 0) {
          ctx_outnum(&__ctx, &__spec, __arg.__i, 16, true,
                     (unsigned char *)"0X", 2);
        } else {
          ctx_outnum(&__ctx, &__spec, __arg.__i, 16, true, NULL, 0);
        }
        __stat = STATE_NORMAL;
        break;
      case SPEC_U:
        pop_arg(&__arg, unsigned_arg_type(__spec.__length), &__ap);
        ctx_outnum(&__ctx, &__spec, __arg.__i, 10, false, NULL, 0);
        __stat = STATE_NORMAL;
        break;
      case SPEC_P:
        pop_arg(&__arg, ARG_PTR, &__ap);
        if (__arg.__p) {
          /* for %p specifier the prefix is always 0x */
          ctx_outnum(&__ctx, &__spec, (uintmax_t)(uintptr_t)__arg.__p, 16,
                     false, (unsigned char *)"0x", 2);
        } else {
          ctx_outs(&__ctx, &__spec, (unsigned char *)"(nil)", 5);
        }
        __stat = STATE_NORMAL;
        break;
      /* flags */
      case '-':
        FLAG_SET(__spec.__flags, FLAG_LEFT_ALIGN);
        break;
      case '0':
        FLAG_SET(__spec.__flags, FLAG_PADDING_ZERO);
        break;
      case '#':
        FLAG_SET(__spec.__flags, FLAG_PREFIX);
        break;
      /* length modifiers */
      case 'h': {
        if (*(__format + 1) == 'h') {
          __spec.__length = LEN_HH;
          __format++;
        } else {
          __spec.__length = LEN_H;
        }
        break;
      }
      case 'l': {
        if (*(__format + 1) == 'l') {
          __spec.__length = LEN_LL;
          __format++;
        } else {
          __spec.__length = LEN_L;
        }
        break;
      }
      case 'z': {
        __spec.__length = LEN_Z;
        break;
      }
      /* width or precision */
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9': {
        while (isdigit(*__format)) {
          if (__reach_precision) {
            __spec.__precision = __spec.__precision * 10 + (*__format++ - '0');
          } else {
            __spec.__width = __spec.__width * 10 + (*__format++ - '0');
          }
        }
        __format--;
        break;
      }
      case '.':
        __reach_precision = true;
        __spec.__precision = 0;
        break;
      case '*': {
        pop_arg(&__arg, ARG_INT, &__ap);
        int __wp = (int)(__arg.__i);
        if (__reach_precision) {
          if (__wp >= 0) {
            __spec.__precision = __wp;
          }
          /* If the * yields a negative value in precision, ignore it */
          __reach_precision = false;

        } else {
          if (__wp < 0) {
            /* If * yields a negative value in width, treats it as - flag with a
             width of the absolute value */
            FLAG_SET(__spec.__flags, FLAG_LEFT_ALIGN);
            __spec.__width = -__wp;
          } else {
            __spec.__width = __wp;
          }
        }
        break;
      }
      }
    }
    }
    __format++;
  }

  if (__buffer && __bufsz)
    __ctx.__buff[MIN(__ctx.__pos, __ctx.__bufsz)] = '\0';

  va_end(__ap);
  return __ctx.__total;
}