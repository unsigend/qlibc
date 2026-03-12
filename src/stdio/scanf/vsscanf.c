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

#include <ext/scanfcore.h>
#include <stdarg.h>
#include <stdio.h>

struct ctx {
  const char *cur;
};

static int readc(void *ctx)
{
  struct ctx *c = (struct ctx *)ctx;
  if (*c->cur == '\0')
    return EOF;
  return *c->cur++;
}

static int unreadc(int ch, void *ctx)
{
  struct ctx *c = (struct ctx *)ctx;
  if (ch != EOF)
    c->cur--;
  return *c->cur;
}

int vsscanf(const char *restrict buffer, const char *restrict format,
            va_list vlist)
{
  if (!buffer || !format || (*format && *buffer == '\0'))
    return EOF;
  struct ctx c = {.cur = buffer};
  struct reader r = {.readc = readc, .unreadc = unreadc, .ctx = &c};
  return scanf_core(&r, format, vlist);
}