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

#ifndef _QLIBC_ENV_H_
#define _QLIBC_ENV_H_

#include <stddef.h>

/* This variable will be set by the CRT. */
extern char **environ;

/* The __heap_environ is used to store the environment variables in heap. Always
   sync with environ. */
extern char **__heap_environ;

/* These Internal helper functions are used to manipulate the environment
   variables array. */

/* Expand the environment variables from envp to a new array in heap. Return
   NULL and set errno to ENOMEM if allocation fails. */
extern char **env_expand(char **oldenvp, char *newstr);

/* Remove the environment variable at the given index from the environment
   variables array. And copy the remaining environment variables to the new
   array. Return NULL and set errno to ENOMEM if allocation fails. */
extern char **env_remove(char **oldenvp, size_t index, int *inplace);

#endif