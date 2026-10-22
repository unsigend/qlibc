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

.text
.globl _start
#ifdef __ELF__
.type _start, @function
#endif

_start:
    mov x29, xzr                /* fp */
    mov x30, xzr                /* lr */
    ldr x0, [sp]                /* argc */
    add x1, sp, #8              /* argv */
    add x2, x1, x0, lsl #3
    add x2, x2, #8              /* envp = argv + (argc + 1) * 8 */
    mov x9, sp
    and x9, x9, #0xfffffffffffffff0
    mov sp, x9
    bl __qlibc_start_main

    hlt #0

#ifdef __ELF__
.section .note.GNU-stack,"",@progbits
#endif
