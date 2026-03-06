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

#include "exit_funcs.h"
#include <stdio.h>
#include <unistd.h>

int __atexit_lock = 0;

#if __USE_ISO_C11
#include <stdnoreturn.h>
noreturn void exit(int status) {
#else
void exit(int status) {
#endif
  if (!__exit_func_count)
    goto done;
  LOCK();
  for (size_t i = __exit_func_count; i > 0;) {
    __exit_funcs[--i]();
  }
  UNLOCK();
done:
  /* Flush all stdio streams. */
  fflush(NULL);
  _exit(status);
}