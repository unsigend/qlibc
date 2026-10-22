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

#ifndef _QLIBC_SYS_MOUNT_H_
#define _QLIBC_SYS_MOUNT_H_

#include <feature.h>

#define MS_RDONLY 1      /* read only */
#define MS_NOSUID 2      /* ignore suid/sgid */
#define MS_NODEV 4       /* no device files */
#define MS_NOEXEC 8      /* no execute */
#define MS_REMOUNT 32    /* alter flags of a mount */
#define MS_BIND 4096     /* bind mount */
#define MS_REC 16384     /* recursive */
#define MS_SILENT 32768  /* no up-mount messages */

#define MNT_FORCE 1      /* force unmount */
#define MNT_DETACH 2     /* lazy unmount */
#define UMOUNT_NOFOLLOW 8 /* do not follow symlink */

#ifdef __cplusplus
extern "C" {
#endif

extern int mount(const char *source, const char *target, const char *fstype,
                 unsigned long flags, const void *data);
extern int umount(const char *target);
extern int umount2(const char *target, int flags);

#ifdef __cplusplus
}
#endif

#endif /* _QLIBC_SYS_MOUNT_H_ */
