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

#ifndef _QLIBC_ELF_SHDR_H
#define _QLIBC_ELF_SHDR_H

#include <elf/type.h>

/**
 * @brief: ELF section header structures and macros
 * This file is part of the ELF specification.
*/

/* 32-bit ELF section header */
typedef struct {
    Elf32_Word sh_name;               /* Section name (string table index) */
    Elf32_Word sh_type;               /* Section type */
    Elf32_Word sh_flags;              /* Section flags */
    Elf32_Addr sh_addr;               /* Section virtual address */
    Elf32_Off sh_offset;              /* Section file offset */
    Elf32_Word sh_size;               /* Section size in bytes */
    Elf32_Word sh_link;               /* Link to another section */
    Elf32_Word sh_info;               /* Additional section information */
    Elf32_Word sh_addralign;          /* Section alignment */
    Elf32_Word sh_entsize;            /* Entry size if section holds a table */
} Elf32_Shdr;

/* 64-bit ELF section header */
typedef struct {
    Elf64_Word	sh_name;		    /* Section name (string tbl index) */
    Elf64_Word	sh_type;		    /* Section type */
    Elf64_Xword	sh_flags;		    /* Section flags */
    Elf64_Addr	sh_addr;		    /* Section virtual addr at execution */
    Elf64_Off	sh_offset;		    /* Section file offset */
    Elf64_Xword	sh_size;		    /* Section size in bytes */
    Elf64_Word	sh_link;		    /* Link to another section */
    Elf64_Word	sh_info;		    /* Additional section information */
    Elf64_Xword	sh_addralign;		/* Section alignment */
    Elf64_Xword	sh_entsize;		    /* Entry size if section holds table */
} Elf64_Shdr;

/* Macros for sh_type: section types */
#define SHT_NULL	  0		            /* Section header table entry unused */
#define SHT_PROGBITS	  1		        /* Program data */
#define SHT_SYMTAB	  2		            /* Symbol table */
#define SHT_STRTAB	  3		            /* String table */
#define SHT_RELA	  4		            /* Relocation entries with addends */
#define SHT_HASH	  5		            /* Symbol hash table */
#define SHT_DYNAMIC	  6		            /* Dynamic linking information */
#define SHT_NOTE	  7		            /* Notes */
#define SHT_NOBITS	  8		            /* Program space with no data (bss) */
#define SHT_REL		  9		            /* Relocation entries, no addends */
#define SHT_SHLIB	  10		        /* Reserved */
#define SHT_DYNSYM	  11		        /* Dynamic linker symbol table */
#define SHT_INIT_ARRAY	  14		    /* Array of constructors */
#define SHT_FINI_ARRAY	  15		    /* Array of destructors */
#define SHT_PREINIT_ARRAY 16		    /* Array of pre-constructors */
#define SHT_GROUP	  17		        /* Section group */
#define SHT_SYMTAB_SHNDX  18		    /* Extended section indeces */
#define	SHT_NUM		  19		        /* Number of defined types */
#define SHT_LOOS	  0x60000000	    /* Start OS-specific */
#define SHT_GNU_ATTRIBUTES 0x6ffffff5   /* Object attributes */
#define SHT_GNU_HASH	  0x6ffffff6	/* GNU-style hash table */
#define SHT_GNU_LIBLIST	  0x6ffffff7	/* Prelink library list */
#define SHT_CHECKSUM	  0x6ffffff8	/* Checksum for DSO content */
#define SHT_LOSUNW	  0x6ffffffa	    /* Sun-specific low bound */
#define SHT_SUNW_move	  0x6ffffffa
#define SHT_SUNW_COMDAT   0x6ffffffb
#define SHT_SUNW_syminfo  0x6ffffffc
#define SHT_GNU_verdef	  0x6ffffffd	/* Version definition section */
#define SHT_GNU_verneed	  0x6ffffffe	/* Version needs section */
#define SHT_GNU_versym	  0x6fffffff	/* Version symbol table */
#define SHT_HISUNW	  0x6fffffff	    /* Sun-specific high bound */
#define SHT_HIOS	  0x6fffffff	    /* End OS-specific type */
#define SHT_LOPROC	  0x70000000	    /* Start of processor-specific */
#define SHT_HIPROC	  0x7fffffff	    /* End of processor-specific */
#define SHT_LOUSER	  0x80000000	    /* Start of application-specific */
#define SHT_HIUSER	  0x8fffffff	    /* End of application-specific */

/* Macros for sh_flags: section flags */
#define SHF_WRITE	     (1 << 0)	    /* Writable */
#define SHF_ALLOC	     (1 << 1)	    /* Occupies memory during execution */
#define SHF_EXECINSTR	 (1 << 2)	    /* Executable */
#define SHF_MERGE	     (1 << 4)	    /* Might be merged */
#define SHF_STRINGS	     (1 << 5)	    /* Contains nul-terminated strings */
#define SHF_INFO_LINK	 (1 << 6)	    /* `sh_info' contains SHT index */
#define SHF_LINK_ORDER	 (1 << 7)	    /* Preserve order after combining */
#define SHF_OS_NONCONFORMING (1 << 8)	/* Non-standard OS specific handling required */
#define SHF_GROUP	     (1 << 9)	    /* Section is member of a group */
#define SHF_TLS		     (1 << 10)	    /* Section hold thread-local data */
#define SHF_COMPRESSED	     (1 << 11)	/* Section with compressed data */
#define SHF_MASKOS	     0x0ff00000	    /* OS-specific */
#define SHF_MASKPROC	     0xf0000000	/* Processor-specific */
#define SHF_ORDERED	     (1 << 30)	    /* Special ordering requirement(Solaris) */
#define SHF_EXCLUDE	     (1U << 31)	    /* Section is excluded unless referenced or allocated (Solaris) */

#endif