/* qlibc - A light-weight and portable C standard library
 * Copyright (C) 2025-2027 Yixiang Qiu
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

#ifndef _QLIBC_SYS_REBOOT_H_
#define _QLIBC_SYS_REBOOT_H_

#include <feature.h>

#define RB_AUTOBOOT 0x01234567    /* restart */
#define RB_HALT_SYSTEM 0xcdef0123 /* halt */
#define RB_ENABLE_CAD 0x89abcdef  /* enable Ctrl-Alt-Del */
#define RB_DISABLE_CAD 0          /* disable Ctrl-Alt-Del */
#define RB_POWER_OFF 0x4321fedc   /* power off */

#ifdef __cplusplus
extern "C" {
#endif

extern int reboot(int howto);

#ifdef __cplusplus
}
#endif

#endif /* _QLIBC_SYS_REBOOT_H_ */
