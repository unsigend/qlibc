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

.section .text
.global _start
.type _start, @function

_start:
    xorq %rbp, %rbp
    popq %rdi                   /* argc */
    movq %rsp, %rsi             /* argv */
    leaq 8(%rsi, %rdi, 8), %rdx /* envp = argv + (argc + 1) * 8 */
    andq $-16, %rsp
    call __qlibc_start_main

    hlt

.section .note.GNU-stack,"",@progbits
