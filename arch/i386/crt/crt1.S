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

.section .text
.global _start
.type _start, @function

/* Based on System V ABI clear, the _start function should clear the frame 
   pointer and set up the arguments for the main function */
_start:
    xorl %ebp, %ebp 
    popl %edi           /* argc */
    movl %esp, %esi    /* argv */
    leal 4(%esi, %edi, 4), %edx /* envp = argv + (argc + 1) * 4 */
    andl $-16, %esp             /* Align the stack pointer to 16 bytes */

    pushl %edx
    pushl %esi
    pushl %edi
    
    call __qlibc_start_main

    hlt

/* Mark the stack as non-executable */
.section .note.GNU-stack,"",@progbits