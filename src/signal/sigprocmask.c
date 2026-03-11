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

#include <errno.h>
#include <signal.h>
#include <sys/syscall.h>

int
sigprocmask(int how, const sigset_t *set, sigset_t *oldset)
{
  if (how != SIG_BLOCK && how != SIG_UNBLOCK && how != SIG_SETMASK)
    {
      errno = EINVAL;
      return -1;
    }

  long ret = __syscall4_raw(SYS_rt_sigprocmask, how, set ? (long)set : 0,
                            oldset ? (long)oldset : 0, (long)sizeof(sigset_t));
  return __syscall_ret(ret);
}