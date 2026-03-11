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
#include <stdlib.h>
#include <string.h>

char **__heap_environ = NULL;

char **
env_expand(char **oldenvp, char *newstr)
{
  size_t envcount = 0;
  for (; oldenvp && oldenvp[envcount]; envcount++)
    ;
  char **newenviron = (char **)malloc(sizeof(char *) * (envcount + 2));
  if (!newenviron)
    {
      errno = ENOMEM;
      return NULL;
    }
  if (envcount) memcpy(newenviron, oldenvp, sizeof(char *) * envcount);
  newenviron[envcount] = newstr;
  newenviron[envcount + 1] = NULL;
  return newenviron;
}

/* Based on the semantic of the unsetenv(), the envp will always be not NULL.
 */
char **
env_remove(char **oldenvp, size_t index, int *inplace)
{
  size_t envcount = 0;
  for (; oldenvp[envcount]; envcount++)
    ;
  if (index >= envcount) return NULL;

  /* If the removed index is the last one, optimize the operation to inplace
     remove. */
  if (index == envcount - 1)
    {
      oldenvp[index] = NULL;
      *inplace = 1;
      return oldenvp;
    }

  /* If the removed index is not the last one, copy the remaining environment
     variables to the new array. */
  char **newenviron = (char **)malloc(sizeof(char *) * (envcount));
  if (!newenviron)
    {
      errno = ENOMEM;
      return NULL;
    }
  memcpy(newenviron, oldenvp, sizeof(char *) * index);
  memcpy(newenviron + index, oldenvp + index + 1,
         sizeof(char *) * (envcount - index));
  newenviron[envcount - 1] = NULL;
  *inplace = 0;
  return newenviron;
}