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
#ifndef _QLIBC_I386_SYSDEP_ERRNO_H_
#define _QLIBC_I386_SYSDEP_ERRNO_H_

#define	EPERM		 1	/* Operation not permitted */
#define	ENOENT		 2	/* No such file or directory */
#define	ESRCH		 3	/* No such process */
#define	EINTR		 4	/* Interrupted system call */
#define	EIO		     5	/* I/O error */
#define	ENXIO		 6	/* No such device or address */
#define	E2BIG		 7	/* Argument list too long */
#define	ENOEXEC		 8	/* Exec format error */
#define	EBADF		 9	/* Bad file number */
#define	ECHILD		 10	/* No child processes */
#define	EAGAIN		 11	/* Try again */
#define	ENOMEM		 12	/* Out of memory */
#define	EACCES		 13	/* Permission denied */
#define	EFAULT		 14	/* Bad address */
#define	ENOTBLK		 15	/* Block device required */
#define	EBUSY		 16	/* Device or resource busy */
#define	EEXIST		 17	/* File exists */
#define	EXDEV		 18	/* Cross-device link */
#define	ENODEV		 19	/* No such device */
#define	ENOTDIR		 20	/* Not a directory */
#define	EISDIR		 21	/* Is a directory */
#define	EINVAL		 22	/* Invalid argument */
#define	ENFILE		 23	/* File table overflow */
#define	EMFILE		 24	/* Too many open files */
#define	ENOTTY		 25	/* Not a typewriter */
#define	ETXTBSY		 26	/* Text file busy */
#define	EFBIG		 27	/* File too large */
#define	ENOSPC		 28	/* No space left on device */
#define	ESPIPE		 29	/* Illegal seek */
#define	EROFS		 30	/* Read-only file system */
#define	EMLINK		 31	/* Too many links */
#define	EPIPE		 32	/* Broken pipe */
#define	EDOM		 33	/* Math argument out of domain of func */
#define	ERANGE		 34	/* Math result not representable */
#define	EDEADLK		 35	/* Resource deadlock would occur */
#define	ENAMETOOLONG 36	/* File name too long */
#define	ENOLCK		 37	/* No record locks available */
#define	ENOSYS		 38	/* Function not implemented */
#define	ENOTEMPTY	 39	/* Directory not empty */
#define	ELOOP		 40	/* Too many symbolic links encountered */
#define	EWOULDBLOCK	EAGAIN	/* Operation would block */
#define	ENOMSG		 42	/* No message of desired type */
#define	EIDRM		 43	/* Identifier removed */
#define	ECHRNG		 44	/* Channel number out of range */
#define	EL2NSYNC	 45	/* Level 2 not synchronized */
#define	EL3HLT		 46	/* Level 3 halted */
#define	EL3RST		 47	/* Level 3 reset */
#define	ELNRNG		 48	/* Link number out of range */
#define	EUNATCH		 49	/* Protocol driver not attached */
#define	ENOCSI		 50	/* No CSI structure available */
#define	EL2HLT		 51	/* Level 2 halted */
#define	EBADE		 52	/* Invalid exchange */
#define	EBADR		 53	/* Invalid request descriptor */
#define	EXFULL		 54	/* Exchange full */
#define	ENOANO		 55	/* No anode */
#define	EBADRQC		 56	/* Invalid request code */
#define	EBADSLT		 57	/* Invalid slot */
#define EILSEQ       84  /* Illegal byte sequence */


#endif /* _QLIBC_I386_SYSDEP_ERRNO_H_ */