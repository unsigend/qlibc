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


#undef assert

#ifdef __cplusplus
extern "C" {
#endif

extern void _assert_fail(const char* msg, const char* file, int line);

#ifdef __cplusplus
}
#endif

/**
 * @brief Assert a condition is true.
 * 
 * NDEBUG if set true do nothing. 
 * Otherwise, if expr is false, print a message and abort.
 */

#ifdef NDEBUG
#define assert(expr) ((void)0)
#else
#define assert(expr) (void)((expr) || ())
#endif 
