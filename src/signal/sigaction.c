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

#include <bits/ksigaction.h>
#include <errno.h>
#include <signal.h>
#include <sys/syscall.h>

#define MAX_SIGNUM 64

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)
{
  if (signum < 1 || signum > MAX_SIGNUM || signum == SIGKILL ||
      signum == SIGSTOP) {
    errno = EINVAL;
    return -1;
  }
  struct k_sigaction k_act;
  struct k_sigaction k_oldact;

  if (act) {
    k_act.handler = act->sa_handler;
    k_act.flags = (unsigned long)act->sa_flags;
    k_act.restorer = act->sa_restorer;
    k_act.mask[0] = (unsigned)(act->sa_mask & 0xFFFFFFFF);
    k_act.mask[1] = (unsigned)(act->sa_mask >> 32);
  }

  long ret =
      __syscall4_raw(SYS_rt_sigaction, signum, act ? (long)&k_act : 0,
                     oldact ? (long)&k_oldact : 0, (long)sizeof(sigset_t));

  if (ret >= 0 && oldact) {
    oldact->sa_handler = k_oldact.handler;
    oldact->sa_flags = k_oldact.flags;
    oldact->sa_restorer = k_oldact.restorer;
    oldact->sa_mask = ((unsigned long long)k_oldact.mask[0] |
                       (unsigned long long)k_oldact.mask[1] << 32);
  }

  return __syscall_ret(ret);
}