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

extern int main(int argc, char *argv[], char *envp[]);
extern void exit(int status);
extern int atexit(void (*func)(void));

/* from linker */
extern void (*__init_array_start[])(void);
extern void (*__init_array_end[])(void);
extern void (*__fini_array_start[])(void);
extern void (*__fini_array_end[])(void);

char **environ;
char **__environ;

static void __do_global_ctors(void)
{
  for (void (**f)() = __init_array_start; f < __init_array_end; f++) {
    (*f)();
  }
}

static void __do_global_dtors(void)
{
  for (void (**f)() = __fini_array_start; f < __fini_array_end; f++) {
    (*f)();
  }
}

void __qlibc_start_main(int argc, char *argv[], char *envp[])
{
  environ = __environ = envp;
  __do_global_ctors();

  /* Register the global destructors to be called at exit */
  atexit(__do_global_dtors);
  exit(main(argc, argv, envp));
}