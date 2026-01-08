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

#ifndef _QLIBC_ELF_SYMTAB_H
#define _QLIBC_ELF_SYMTAB_H

#include <elf/type.h>

/**
 * @brief: ELF symbol table structures and macros
 * This file is part of the ELF specification.
*/

/* 32-bit ELF symbol table */
typedef struct {
    Elf32_Word st_name;               /* Symbol name (string table index) */
    Elf32_Addr st_value;              /* Symbol value */
    Elf32_Word st_size;               /* Symbol size */
    unsigned char st_info;            /* Symbol type and binding information */
    unsigned char st_other;           /* Symbol visibility and other information */
    Elf32_Section st_shndx;           /* Section index of the symbol */
} Elf32_Sym;

/* 64-bit ELF symbol table */
typedef struct{
    Elf64_Word	st_name;		      /* Symbol name (string table index) */
    unsigned char st_info;		      /* Symbol type and binding information*/
    unsigned char st_other;		      /* Symbol visibility and other information */
    Elf64_Section st_shndx;		      /* Section index of the symbol */
    Elf64_Addr	st_value;		      /* Symbol value */
    Elf64_Xword	st_size;		      /* Symbol size */
} Elf64_Sym;

/* Macros for st_info: symbol type and binding information */
#define ELF32_ST_BIND(val)		    (((unsigned char) (val)) >> 4)
#define ELF32_ST_TYPE(val)		    ((val) & 0xf)
#define ELF32_ST_INFO(bind, type)	(((bind) << 4) + ((type) & 0xf))

#define ELF64_ST_BIND(val)		    ELF32_ST_BIND (val)
#define ELF64_ST_TYPE(val)		    ELF32_ST_TYPE (val)
#define ELF64_ST_INFO(bind, type)	ELF32_ST_INFO ((bind), (type))

/* Symbol type (low 4 bits) */
#define STB_LOCAL	0		/* Local symbol */
#define STB_GLOBAL	1		/* Global symbol */
#define STB_WEAK	2		/* Weak symbol */
#define	STB_NUM		3		/* Number of defined types */
#define STB_LOOS	10		/* Start of OS-specific */
#define STB_GNU_UNIQUE	10	/* Unique symbol */
#define STB_HIOS	12		/* End of OS-specific */
#define STB_LOPROC	13		/* Start of processor-specific */
#define STB_HIPROC	15		/* End of processor-specific */

/* Symbol binding (high 28 bits) */
#define STT_NOTYPE	0		/* Symbol type is unspecified */
#define STT_OBJECT	1		/* Symbol is a data object */
#define STT_FUNC	2		/* Symbol is a code object */
#define STT_SECTION	3		/* Symbol associated with a section */
#define STT_FILE	4		/* Symbol's name is file name */
#define STT_COMMON	5		/* Symbol is a common data object */
#define STT_TLS		6		/* Symbol is thread-local data object*/
#define	STT_NUM		7		/* Number of defined types */
#define STT_LOOS	10		/* Start of OS-specific */
#define STT_GNU_IFUNC	10	/* Symbol is indirect code object */
#define STT_HIOS	12		/* End of OS-specific */
#define STT_LOPROC	13		/* Start of processor-specific */
#define STT_HIPROC	15		/* End of processor-specific */

/* Macros for sh_shndx: section index */
#define SHN_UNDEF	0		        /* Undefined section */
#define SHN_LORESERVE	0xff00		/* Start of reserved indices */
#define SHN_LOPROC	0xff00		    /* Start of processor-specific */
#define SHN_BEFORE	0xff00		    /* Order section before all others(Solaris) */
#define SHN_AFTER	0xff01		    /* Order section after all others(Solaris) */
#define SHN_HIPROC	0xff1f		    /* End of processor-specific */
#define SHN_LOOS	0xff20		    /* Start of OS-specific */
#define SHN_HIOS	0xff3f		    /* End of OS-specific */
#define SHN_ABS		0xfff1		    /* Associated symbol is absolute */
#define SHN_COMMON	0xfff2		    /* Associated symbol is common */
#define SHN_XINDEX	0xffff		    /* Index is in extra table */
#define SHN_HIRESERVE	0xffff		/* End of reserved indices */

#endif