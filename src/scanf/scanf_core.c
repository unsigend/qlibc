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

#include <ctype.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

/* Features supported:
   Specifiers: %c, %s, %d, %i, %u, %o, %x, %X, %p
   Suppression: *
   Width:      fixed %Nd
   Length:     l (long), ll (long long), z (size_t), h (short), hh (char)
   Format sequence is ordered: %[*][width][length][specifier]
*/

struct ctx {
  const char *cursor; /* current cursor position in the input string */
  int n;              /* number of successfully scanned items */
};

struct fsm_t {
  int state;    /* current state of the parser */
  size_t width; /* width of the field */
  int length;   /* length modifier */
  int suppress; /* suppress flag */
};

#define INT_BUFFSZ 64 /* buffer size for integer conversion */

#define FSM_SWITCH(fsm, newstate)                                              \
  do {                                                                         \
    memset(fsm, 0, sizeof(struct fsm_t));                                      \
    (fsm)->state = (newstate);                                                 \
  } while (0) /* switch to new state */
#define FSM_RESET(fsm)                                                         \
  FSM_SWITCH(fsm, STATE_NORMAL) /* reset the finite state machine */

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define POP(ptr, ap)                                                           \
  do {                                                                         \
    if (!(fsm).suppress)                                                       \
      pop_ptr((ptr), (ap));                                                    \
  } while (0) /* pop a pointer from the argument list */

/* State machine for the parser */
enum {
  STATE_NORMAL, /* Normal state, copy characters from input to buffer */
  STATE_FORMAT, /* Format state, parse the format string */
};

/* Length modifiers */
enum {
  LEN_NONE = 0,
  LEN_H,
  LEN_HH,
  LEN_L,
  LEN_LL,
  LEN_Z,
  LEN_PTR,
};

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

static void pop_ptr(void **ptr, va_list *ap) { *ptr = va_arg(*ap, void *); }

/* Read a string from the buffer and store it in the destination, return the
   number of characters consumed. Return -1 if failed. String behaviour if bhvs
   is set to 1, character behaviour otherwise.*/
static int instr(const char *str, char *dest, size_t width, struct fsm_t *fsm,
                 int bhvs) {
  const char *p = str;
  size_t total = 0;
  size_t n = 0;
  width = width ? width : SIZE_MAX;

  while (bhvs && isspace(*p)) /* skip whitespace if string */
  {
    p++;
    total++;
  }

  if (*p == '\0')
    return -1;

  while (n < width && *p) {
    if (bhvs && isspace(*p))
      break;
    if (!fsm->suppress)
      *dest++ = *p;
    p++;
    n++;
  }

  if (bhvs && !fsm->suppress)
    *dest = '\0';

  return (int)(total + n);
}

/* Read a number from the buffer and store it in the destination, return the
  number of characters read. Return -1 if failed (match failed or EOF failed).
  If it is a EOF failure, set the fail flag to 1.*/
static int innum(const char *restrict str, struct fsm_t *fsm, void *dest,
                 int base, int sign, int length, int *fail) {
  const char *p = str;
  char *end;
  char buff[INT_BUFFSZ];
  long long ll;
  unsigned long long ull;

  if (fsm->width > 0) {
    size_t n = MIN(fsm->width, INT_BUFFSZ - 1);
    strncpy(buff, p, n);
    buff[n] = '\0';
    p = buff;
  }
  if (sign)
    ll = strtoll(p, &end, base);
  else
    ull = strtoull(p, &end, base);

  if (end == p) {
    const char *skip = str;
    while (isspace(*skip))
      skip++;
    if (*skip == '\0')
      *fail = 1;
    return -1;
  }

  if (!fsm->suppress) {
    switch (length) {
    case LEN_H:
      if (sign)
        *(short *)dest = (short)ll;
      else
        *(unsigned short *)dest = (unsigned short)ull;
      break;
    case LEN_HH:
      if (sign)
        *(char *)dest = (char)ll;
      else
        *(unsigned char *)dest = (unsigned char)ull;
      break;
    case LEN_L:
      if (sign)
        *(long *)dest = (long)ll;
      else
        *(unsigned long *)dest = (unsigned long)ull;
      break;
    case LEN_LL:
      if (sign)
        *(long long *)dest = ll;
      else
        *(unsigned long long *)dest = ull;
      break;
    case LEN_Z:
      if (sign)
        *(ssize_t *)dest = (ssize_t)ll;
      else
        *(size_t *)dest = (size_t)ull;
      break;
    case LEN_PTR:
      *(uintptr_t *)dest = (uintptr_t)ull;
      break;
    default:
      if (sign)
        *(int *)dest = (int)ll;
      else
        *(unsigned int *)dest = (unsigned int)ull;
      break;
    }
  }
  return (int)(end - p);
}

/* Internal core implementation of formatted input. With parser and
   formatter support. */
int scanf_core(const char *restrict buff, const char *restrict fmt,
               va_list vlist) {
  struct ctx ctx = {.cursor = buff, .n = 0};
  struct fsm_t fsm;
  int fail = 0;

  if (!buff || !fmt || (*fmt && *buff == '\0'))
    return EOF;

  FSM_RESET(&fsm);
  va_list ap;

  /* the copy allows passing va_list* even if va_list is an array */
  va_copy(ap, vlist);

  while (*fmt) {
    switch (fsm.state) {
    case STATE_NORMAL: {
      switch (*fmt) {
      case '%': {
        FSM_SWITCH(&fsm, STATE_FORMAT);
        break;
      }
      default: {
        /* skip whitespace */
        if (isspace(*fmt)) {
          while (isspace(*ctx.cursor))
            ctx.cursor++;
        }
        /* literal match */
        else {
          if (*ctx.cursor != *fmt)
            goto done;
          ctx.cursor++;
        }
        break;
      }
      }
      break;
    }
    case STATE_FORMAT: {
      switch (*fmt) {
      case '%': {
        if (*ctx.cursor != '%')
          goto done;
        ctx.cursor++;
        FSM_SWITCH(&fsm, STATE_NORMAL);
        break;
      }
      case '*': {
        fsm.suppress = 1;
        break;
      }
      /* width */
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9': {
        while (isdigit(*fmt)) {
          fsm.width = fsm.width * 10 + (*fmt++ - '0');
        }
        fmt--;
        break;
      }
      /* length modifiers */
      case 'h': {
        if (*(fmt + 1) == 'h') {
          fsm.length = LEN_HH;
          fmt++;
        } else {
          fsm.length = LEN_H;
        }
        break;
      }
      case 'l': {
        if (*(fmt + 1) == 'l') {
          fsm.length = LEN_LL;
          fmt++;
        } else {
          fsm.length = LEN_L;
        }
        break;
      }
      case 'z': {
        fsm.length = LEN_Z;
        break;
      }
      /* specifiers */
      case SPEC_C: {
        char *c = NULL;
        POP((void **)&c, &ap);
        int n = instr(ctx.cursor, c, fsm.width ? fsm.width : 1, &fsm, 0);
        if (n == -1) {
          fail = 1;
          goto done;
        }
        ctx.cursor += n;
        if (!fsm.suppress)
          ctx.n++;
        FSM_SWITCH(&fsm, STATE_NORMAL);
        break;
      }
      case SPEC_S: {
        char *s = NULL;
        POP((void **)&s, &ap);
        int n = instr(ctx.cursor, s, fsm.width, &fsm, 1);
        if (n == -1) {
          fail = 1;
          goto done;
        }
        ctx.cursor += n;
        if (!fsm.suppress)
          ctx.n++;
        FSM_SWITCH(&fsm, STATE_NORMAL);
        break;
      }
      case SPEC_I: {
        void *p = NULL;
        POP(&p, &ap);
        int n = innum(ctx.cursor, &fsm, p, 0, 1, fsm.length, &fail);
        if (n == -1)
          goto done;
        ctx.cursor += n;
        if (!fsm.suppress)
          ctx.n++;
        FSM_SWITCH(&fsm, STATE_NORMAL);
        break;
      }
      case SPEC_D: {
        void *p = NULL;
        POP(&p, &ap);
        int n = innum(ctx.cursor, &fsm, p, 10, 1, fsm.length, &fail);
        if (n == -1)
          goto done;
        ctx.cursor += n;
        if (!fsm.suppress)
          ctx.n++;
        FSM_SWITCH(&fsm, STATE_NORMAL);
        break;
      }
      case SPEC_O: {
        void *p = NULL;
        POP(&p, &ap);
        int n = innum(ctx.cursor, &fsm, p, 8, 0, fsm.length, &fail);
        if (n == -1)
          goto done;
        ctx.cursor += n;
        if (!fsm.suppress)
          ctx.n++;
        FSM_SWITCH(&fsm, STATE_NORMAL);
        break;
      }
      case SPEC_X:
      case SPEC_XX: {
        void *p = NULL;
        POP(&p, &ap);
        int n = innum(ctx.cursor, &fsm, p, 16, 0, fsm.length, &fail);
        if (n == -1)
          goto done;
        ctx.cursor += n;
        if (!fsm.suppress)
          ctx.n++;
        FSM_SWITCH(&fsm, STATE_NORMAL);
        break;
      }
      case SPEC_U: {
        void *p = NULL;
        POP(&p, &ap);
        int n = innum(ctx.cursor, &fsm, p, 10, 0, fsm.length, &fail);
        if (n == -1)
          goto done;
        ctx.cursor += n;
        if (!fsm.suppress)
          ctx.n++;
        FSM_SWITCH(&fsm, STATE_NORMAL);
        break;
      }
      case SPEC_P: {
        void *p = NULL;
        POP(&p, &ap);
        /* for %p specifier the length modifier is always LEN_PTR */
        int n = innum(ctx.cursor, &fsm, p, 16, 0, LEN_PTR, &fail);
        if (n == -1) {
          if (strncmp(ctx.cursor, "(nil)", 5) == 0) {
            if (!fsm.suppress)
              *(void **)p = NULL;
            n = 5;
          } else
            goto done;
        }
        ctx.cursor += n;
        if (!fsm.suppress)
          ctx.n++;
        FSM_SWITCH(&fsm, STATE_NORMAL);
        break;
      }
      }
      break;
    }
    }
    fmt++;
  }

done:
  va_end(ap);
  return (fail && ctx.n == 0) ? EOF : ctx.n;
}