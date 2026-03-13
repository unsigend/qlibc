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

#include "fmt.h"
#include <ctype.h>
#include <ext/scanfcore.h>
#include <iso646.h>
#include <stdarg.h>
#include <stdbool.h>
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
#define POP(ptr, ap)                                                           \
  do {                                                                         \
    if (!(fsm).suppress)                                                       \
      *(ptr) = va_arg(*ap, void *);                                            \
  } while (0) /* pop a pointer from the argument list */
#define PROCNUM(reader, width, base, sign, length, fail)                       \
  {                                                                            \
    void *p = NULL;                                                            \
    POP(&p, &ap);                                                              \
    if (!innum(reader, width, p, base, sign, length, fail))                    \
      goto done;                                                               \
    if (!(fsm).suppress)                                                       \
      n++;                                                                     \
    FSM_SWITCH(&fsm, STATE_NORMAL);                                            \
    break;                                                                     \
  } /* process a number */

/* Read a string use reader and store it in the destination. Return false
   indicating failure. String behaviour if bhvs is set to 1, character behaviour
   otherwise.*/
static bool instr(struct reader *reader, char *dest, size_t width, int bhvs)
{
  int c = reader->readc(reader->ctx);
  size_t n = 0;
  width = width ? width : SIZE_MAX;

  /* skip leading whitespace if string */
  while (bhvs && isspace(c))
    c = reader->readc(reader->ctx);

  if (c == EOF)
    return false;

  reader->unreadc(c, reader->ctx);

  while (n < width && (c = reader->readc(reader->ctx)) != EOF) {
    if (bhvs && isspace(c)) {
      reader->unreadc(c, reader->ctx);
      break;
    }
    if (dest)
      *dest++ = c;
    n++;
  }

  if (bhvs && dest)
    *dest = '\0';

  return true;
}

static void storenum(void *dest, int length, unsigned long long val)
{
  if (!dest)
    return;
  switch (length) {
  case LEN_H:
    *(short *)dest = (short)val;
    break;
  case LEN_HH:
    *(char *)dest = (char)val;
    break;
  case LEN_L:
    *(long *)dest = (long)val;
    break;
  case LEN_LL:
    *(long long *)dest = (long long)val;
    break;
  case LEN_Z:
    *(size_t *)dest = (size_t)val;
    break;
  case LEN_PTR:
    *(uintptr_t *)dest = (uintptr_t)val;
    break;
  default:
    *(int *)dest = (int)val;
    break;
  }
}

static inline bool isdigitc(int c, int base)
{
  if (isspace(c))
    return false;
  if (base == 16)
    return isxdigit(c);
  if (base == 8)
    return c >= '0' && c <= '7';
  return isdigit(c);
}

/* Read a number from the reader and store it in the destination. Return false
  indicating failure. If it is a EOF failure, set the fail flag to 1.*/
static bool innum(struct reader *reader, size_t width, void *dest, int base,
                  int sign, int length, int *fail)
{
  int c = reader->readc(reader->ctx);
  char *end;
  char buff[INT_BUFFSZ];
  long long ll;
  unsigned long long ull;
  int n = width ? MIN(width, INT_BUFFSZ - 1) : INT_BUFFSZ - 1;
  size_t leftn;

  /* skip leading whitespace */
  while (isspace(c))
    c = reader->readc(reader->ctx);

  if (c == EOF) {
    *fail = 1;
    return false;
  }

  reader->unreadc(c, reader->ctx);

  /* read the number to the buffer */
  int i = 0;
  c = reader->readc(reader->ctx);

  if (c == '-' || c == '+')
    buff[i++] = c;
  else
    reader->unreadc(c, reader->ctx);

  if (!base) {
    c = reader->readc(reader->ctx);
    if (c == '0') {
      c = reader->readc(reader->ctx);
      if (c == 'x' || c == 'X') {
        base = 16;
        buff[i++] = '0';
        buff[i++] = c;
      } else {
        base = 8;
        buff[i++] = '0';
        if (c != EOF)
          reader->unreadc(c, reader->ctx);
      }
    } else {
      base = 10;
      reader->unreadc(c, reader->ctx);
    }
  } else if (base == 16) {
    c = reader->readc(reader->ctx);
    if (c == '0') {
      int cc = reader->readc(reader->ctx);
      if (cc == 'x' || cc == 'X') {
        buff[i++] = '0';
        buff[i++] = cc;
      } else {
        if (cc != EOF)
          reader->unreadc(cc, reader->ctx);
        reader->unreadc(c, reader->ctx);
      }
    } else
      reader->unreadc(c, reader->ctx);
  }

  while (i < n && (c = reader->readc(reader->ctx)) != EOF) {
    if (!isdigitc(c, base)) {
      reader->unreadc(c, reader->ctx);
      break;
    }
    buff[i++] = c;
  }
  buff[i] = '\0';

  /* consume the remaining characters if any. */
  leftn = (width > 0 && (size_t)i < width) ? width - i : 0;
  while (leftn-- && (c = reader->readc(reader->ctx)) != EOF) {
    if (!isdigitc(c, base)) {
      reader->unreadc(c, reader->ctx);
      break;
    }
  }

  if (sign)
    ll = strtoll(buff, &end, base);
  else
    ull = strtoull(buff, &end, base);

  if (end == buff)
    return false;

  storenum(dest, length, sign ? (unsigned long long)ll : ull);

  return true;
}

/* Internal core implementation of formatted input. With parser and
   formatter support. */
int scanf_core(struct reader *reader, const char *restrict fmt, va_list vlist)
{
  struct fsm_t fsm;
  int fail = 0;
  int n = 0;

  FSM_RESET(&fsm);
  va_list ap;

  /* the copy allows passing va_list* even if va_list is an array */
  va_copy(ap, vlist);

  while (*fmt) {
    switch (fsm.state) {
    case STATE_NORMAL:
      switch (*fmt) {
      case '%':
        FSM_SWITCH(&fsm, STATE_FORMAT);
        break;
      default:
        /* skip whitespace */
        if (isspace(*fmt)) {
          int c = reader->readc(reader->ctx);
          while (isspace(c))
            c = reader->readc(reader->ctx);
          if (c != EOF)
            reader->unreadc(c, reader->ctx);
        }
        /* literal match */
        else {
          int c = reader->readc(reader->ctx);
          if (c != *fmt) {
            reader->unreadc(c, reader->ctx);
            goto done;
          }
        }
        break;
      }
      break;
    case STATE_FORMAT:
      switch (*fmt) {
      case '%': {
        int c = reader->readc(reader->ctx);
        if (c != '%') {
          if (c != EOF)
            reader->unreadc(c, reader->ctx);
          goto done;
        }
        FSM_SWITCH(&fsm, STATE_NORMAL);
        break;
      }
      case '*':
        fsm.suppress = 1;
        break;
      /* width */
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        while (isdigit(*fmt)) {
          fsm.width = fsm.width * 10 + (*fmt++ - '0');
        }
        fmt--;
        break;
      /* length modifiers */
      case 'h':
        if (*(fmt + 1) == 'h') {
          fsm.length = LEN_HH;
          fmt++;
        } else
          fsm.length = LEN_H;
        break;
      case 'l':
        if (*(fmt + 1) == 'l') {
          fsm.length = LEN_LL;
          fmt++;
        } else
          fsm.length = LEN_L;
        break;
      case 'z':
        fsm.length = LEN_Z;
        break;
      /* specifiers */
      case SPEC_C: {
        char *c = NULL;
        POP((void **)&c, &ap);
        if (!instr(reader, c, fsm.width ? fsm.width : 1, 0)) {
          fail = 1;
          goto done;
        }
        if (!fsm.suppress)
          n++;
        FSM_SWITCH(&fsm, STATE_NORMAL);
        break;
      }
      case SPEC_S: {
        char *s = NULL;
        POP((void **)&s, &ap);
        if (!instr(reader, s, fsm.width, 1)) {
          fail = 1;
          goto done;
        }
        if (!fsm.suppress)
          n++;
        FSM_SWITCH(&fsm, STATE_NORMAL);
        break;
      }
      case SPEC_I:
        PROCNUM(reader, fsm.width, 0, 1, fsm.length, &fail);
      case SPEC_D:
        PROCNUM(reader, fsm.width, 10, 1, fsm.length, &fail);
      case SPEC_O:
        PROCNUM(reader, fsm.width, 8, 0, fsm.length, &fail);
      case SPEC_X:
      case SPEC_XX:
        PROCNUM(reader, fsm.width, 16, 0, fsm.length, &fail);
      case SPEC_U:
        PROCNUM(reader, fsm.width, 10, 0, fsm.length, &fail);
      case SPEC_P: {
        void *p = NULL;
        POP(&p, &ap);
        /* for %p specifier the length modifier is always LEN_PTR */
        if (!innum(reader, fsm.width, p, 16, 0, LEN_PTR, &fail)) {
          const char *nil = "(nil)";
          for (size_t i = 0; i < 5; i++) {
            if (reader->readc(reader->ctx) != nil[i])
              goto done;
          }
          if (!fsm.suppress)
            *(void **)p = NULL;
        }
        if (!fsm.suppress)
          n++;
        FSM_SWITCH(&fsm, STATE_NORMAL);
        break;
      }
      }
      break;
    }
    fmt++;
  }

done:
  va_end(ap);
  return (fail && n == 0) ? EOF : n;
}