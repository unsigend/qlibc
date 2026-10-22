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

#ifndef _QLIBC_ELF_H_
#define _QLIBC_ELF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* 16-bit types */
typedef uint16_t Elf32_Half;
typedef uint16_t Elf64_Half;

/* 32-bit types */
typedef uint32_t Elf32_Word;
typedef int32_t Elf32_Sword;
typedef uint32_t Elf64_Word;
typedef int32_t Elf64_Sword;

/* 64-bit types */
typedef uint64_t Elf32_Xword;
typedef int64_t Elf32_Sxword;
typedef uint64_t Elf64_Xword;
typedef int64_t Elf64_Sxword;

/* Address types */
typedef uint32_t Elf32_Addr;
typedef uint64_t Elf64_Addr;

/* File offset types */
typedef uint32_t Elf32_Off;
typedef uint64_t Elf64_Off;

/* Section index types */
typedef uint16_t Elf32_Section;
typedef uint16_t Elf64_Section;

/* Version symbol types */
typedef Elf32_Half Elf32_Versym;
typedef Elf64_Half Elf64_Versym;

#define EI_NIDENT (16) /* Identification bytes */

typedef struct {
    unsigned char e_ident[EI_NIDENT]; /* Magic and other info */
    Elf32_Half e_type;                /* Object file type */
    Elf32_Half e_machine;             /* Architecture */
    Elf32_Word e_version;             /* Object file version */
    Elf32_Addr e_entry;               /* Entry point */
    Elf32_Off e_phoff;                /* Program header offset */
    Elf32_Off e_shoff;                /* Section header offset */
    Elf32_Word e_flags;               /* Processor flags */
    Elf32_Half e_ehsize;              /* ELF header size */
    Elf32_Half e_phentsize;           /* Program header entry size */
    Elf32_Half e_phnum;               /* Program header count */
    Elf32_Half e_shentsize;           /* Section header entry size */
    Elf32_Half e_shnum;               /* Section header count */
    Elf32_Half e_shstrndx;            /* Section name string table */
} Elf32_Ehdr;

typedef struct {
    unsigned char e_ident[EI_NIDENT]; /* Magic and other info */
    Elf64_Half e_type;                /* Object file type */
    Elf64_Half e_machine;             /* Architecture */
    Elf64_Word e_version;             /* Object file version */
    Elf64_Addr e_entry;               /* Entry point */
    Elf64_Off e_phoff;                /* Program header offset */
    Elf64_Off e_shoff;                /* Section header offset */
    Elf64_Word e_flags;               /* Processor flags */
    Elf64_Half e_ehsize;              /* ELF header size */
    Elf64_Half e_phentsize;           /* Program header entry size */
    Elf64_Half e_phnum;               /* Program header count */
    Elf64_Half e_shentsize;           /* Section header entry size */
    Elf64_Half e_shnum;               /* Section header count */
    Elf64_Half e_shstrndx;            /* Section name string table */
} Elf64_Ehdr;

/* e_ident indexes and magic */
#define EI_MAG0 0        /* Magic byte 0 index */
#define EI_MAG1 1        /* Magic byte 1 index */
#define EI_MAG2 2        /* Magic byte 2 index */
#define EI_MAG3 3        /* Magic byte 3 index */
#define ELFMAG0 0x7f     /* Magic byte 0 */
#define ELFMAG1 'E'      /* Magic byte 1 */
#define ELFMAG2 'L'      /* Magic byte 2 */
#define ELFMAG3 'F'      /* Magic byte 3 */
#define ELFMAG "\177ELF" /* Magic string */
#define SELFMAG 4        /* Magic length */

#define EI_CLASS 4     /* File class index */
#define ELFCLASSNONE 0 /* Invalid class */
#define ELFCLASS32 1   /* 32-bit objects */
#define ELFCLASS64 2   /* 64-bit objects */
#define ELFCLASSNUM 3  /* Number of classes */

#define EI_DATA 5     /* Data encoding index */
#define ELFDATANONE 0 /* Invalid encoding */
#define ELFDATA2LSB 1 /* Little endian */
#define ELFDATA2MSB 2 /* Big endian */
#define ELFDATANUM 3  /* Number of encodings */

#define EI_VERSION 6 /* File version index */

#define EI_OSABI 7              /* OS ABI index */
#define ELFOSABI_NONE 0         /* UNIX System V ABI */
#define ELFOSABI_SYSV 0         /* Alias */
#define ELFOSABI_GNU 3          /* GNU extensions */
#define ELFOSABI_LINUX 3        /* Compatibility alias */
#define ELFOSABI_ARM 97         /* ARM */
#define ELFOSABI_STANDALONE 255 /* Standalone / embedded */

#define EI_ABIVERSION 8 /* ABI version index */
#define EI_PAD 9        /* Padding start */

/* e_type */
#define ET_NONE 0        /* No file type */
#define ET_REL 1         /* Relocatable */
#define ET_EXEC 2        /* Executable */
#define ET_DYN 3         /* Shared object */
#define ET_CORE 4        /* Core file */
#define ET_NUM 5         /* Number of defined types */
#define ET_LOOS 0xfe00   /* OS-specific start */
#define ET_HIOS 0xfeff   /* OS-specific end */
#define ET_LOPROC 0xff00 /* Processor-specific start */
#define ET_HIPROC 0xffff /* Processor-specific end */

/* e_machine (supported targets) */
#define EM_NONE 0      /* No machine */
#define EM_386 3       /* Intel 80386 */
#define EM_ARM 40      /* ARM */
#define EM_X86_64 62   /* AMD x86-64 */
#define EM_AARCH64 183 /* ARM AArch64 */

/* e_version */
#define EV_NONE 0    /* Invalid version */
#define EV_CURRENT 1 /* Current version */
#define EV_NUM 2

/* Special section indexes */
#define SHN_UNDEF 0          /* Undefined section */
#define SHN_LORESERVE 0xff00 /* Reserved start */
#define SHN_LOPROC 0xff00    /* Processor-specific start */
#define SHN_HIPROC 0xff1f    /* Processor-specific end */
#define SHN_LOOS 0xff20      /* OS-specific start */
#define SHN_HIOS 0xff3f      /* OS-specific end */
#define SHN_ABS 0xfff1       /* Absolute symbol */
#define SHN_COMMON 0xfff2    /* Common symbol */
#define SHN_XINDEX 0xffff    /* Extra table index */
#define SHN_HIRESERVE 0xffff /* Reserved end */

typedef struct {
    Elf32_Word sh_name;      /* Name (string table index) */
    Elf32_Word sh_type;      /* Type */
    Elf32_Word sh_flags;     /* Flags */
    Elf32_Addr sh_addr;      /* Virtual address */
    Elf32_Off sh_offset;     /* File offset */
    Elf32_Word sh_size;      /* Size in bytes */
    Elf32_Word sh_link;      /* Link to another section */
    Elf32_Word sh_info;      /* Extra information */
    Elf32_Word sh_addralign; /* Alignment */
    Elf32_Word sh_entsize;   /* Table entry size */
} Elf32_Shdr;

typedef struct {
    Elf64_Word sh_name;       /* Name (string table index) */
    Elf64_Word sh_type;       /* Type */
    Elf64_Xword sh_flags;     /* Flags */
    Elf64_Addr sh_addr;       /* Virtual address */
    Elf64_Off sh_offset;      /* File offset */
    Elf64_Xword sh_size;      /* Size in bytes */
    Elf64_Word sh_link;       /* Link to another section */
    Elf64_Word sh_info;       /* Extra information */
    Elf64_Xword sh_addralign; /* Alignment */
    Elf64_Xword sh_entsize;   /* Table entry size */
} Elf64_Shdr;

/* sh_type */
#define SHT_NULL 0                 /* Inactive */
#define SHT_PROGBITS 1             /* Program data */
#define SHT_SYMTAB 2               /* Symbol table */
#define SHT_STRTAB 3               /* String table */
#define SHT_RELA 4                 /* Relocations with addends */
#define SHT_HASH 5                 /* Symbol hash table */
#define SHT_DYNAMIC 6              /* Dynamic linking info */
#define SHT_NOTE 7                 /* Notes */
#define SHT_NOBITS 8               /* BSS */
#define SHT_REL 9                  /* Relocations */
#define SHT_SHLIB 10               /* Reserved */
#define SHT_DYNSYM 11              /* Dynamic symbol table */
#define SHT_INIT_ARRAY 14          /* Constructors */
#define SHT_FINI_ARRAY 15          /* Destructors */
#define SHT_PREINIT_ARRAY 16       /* Pre-constructors */
#define SHT_GROUP 17               /* Section group */
#define SHT_SYMTAB_SHNDX 18        /* Extended section indexes */
#define SHT_RELR 19                /* Relative relocations */
#define SHT_NUM 20                 /* Number of defined types */
#define SHT_LOOS 0x60000000        /* OS-specific start */
#define SHT_GNU_HASH 0x6ffffff6    /* GNU hash table */
#define SHT_GNU_verdef 0x6ffffffd  /* Version definitions */
#define SHT_GNU_verneed 0x6ffffffe /* Version needs */
#define SHT_GNU_versym 0x6fffffff  /* Version symbol table */
#define SHT_HIOS 0x6fffffff        /* OS-specific end */
#define SHT_LOPROC 0x70000000      /* Processor-specific start */
#define SHT_HIPROC 0x7fffffff      /* Processor-specific end */
#define SHT_LOUSER 0x80000000      /* Application-specific start */
#define SHT_HIUSER 0x8fffffff      /* Application-specific end */

/* sh_flags */
#define SHF_WRITE (1 << 0)       /* Writable */
#define SHF_ALLOC (1 << 1)       /* Occupies memory */
#define SHF_EXECINSTR (1 << 2)   /* Executable */
#define SHF_MERGE (1 << 4)       /* May be merged */
#define SHF_STRINGS (1 << 5)     /* NUL-terminated strings */
#define SHF_INFO_LINK (1 << 6)   /* sh_info is a section index */
#define SHF_LINK_ORDER (1 << 7)  /* Preserve link order */
#define SHF_GROUP (1 << 9)       /* Group member */
#define SHF_TLS (1 << 10)        /* Thread-local data */
#define SHF_COMPRESSED (1 << 11) /* Compressed */
#define SHF_MASKOS 0x0ff00000    /* OS-specific mask */
#define SHF_MASKPROC 0xf0000000  /* Processor-specific mask */
#define SHF_GNU_RETAIN (1 << 21) /* Do not GC */

typedef struct {
    Elf32_Word st_name;     /* Name (string table index) */
    Elf32_Addr st_value;    /* Value */
    Elf32_Word st_size;     /* Size */
    unsigned char st_info;  /* Binding and type */
    unsigned char st_other; /* Visibility */
    Elf32_Section st_shndx; /* Section index */
} Elf32_Sym;

typedef struct {
    Elf64_Word st_name;     /* Name (string table index) */
    unsigned char st_info;  /* Binding and type */
    unsigned char st_other; /* Visibility */
    Elf64_Section st_shndx; /* Section index */
    Elf64_Addr st_value;    /* Value */
    Elf64_Xword st_size;    /* Size */
} Elf64_Sym;

/* st_info */
#define ELF32_ST_BIND(val) (((unsigned char)(val)) >> 4)           /* Binding */
#define ELF32_ST_TYPE(val) ((val) & 0xf)                           /* Type */
#define ELF32_ST_INFO(bind, type) (((bind) << 4) + ((type) & 0xf)) /* Pack */
#define ELF64_ST_BIND(val) ELF32_ST_BIND(val)
#define ELF64_ST_TYPE(val) ELF32_ST_TYPE(val)
#define ELF64_ST_INFO(bind, type) ELF32_ST_INFO((bind), (type))

#define STB_LOCAL 0       /* Local symbol */
#define STB_GLOBAL 1      /* Global symbol */
#define STB_WEAK 2        /* Weak symbol */
#define STB_NUM 3         /* Number of defined types */
#define STB_LOOS 10       /* OS-specific start */
#define STB_GNU_UNIQUE 10 /* Unique symbol */
#define STB_HIOS 12       /* OS-specific end */
#define STB_LOPROC 13     /* Processor-specific start */
#define STB_HIPROC 15     /* Processor-specific end */

#define STT_NOTYPE 0     /* Unspecified */
#define STT_OBJECT 1     /* Data object */
#define STT_FUNC 2       /* Function */
#define STT_SECTION 3    /* Section */
#define STT_FILE 4       /* Source file name */
#define STT_COMMON 5     /* Common data */
#define STT_TLS 6        /* Thread-local data */
#define STT_NUM 7        /* Number of defined types */
#define STT_LOOS 10      /* OS-specific start */
#define STT_GNU_IFUNC 10 /* Indirect function */
#define STT_HIOS 12      /* OS-specific end */
#define STT_LOPROC 13    /* Processor-specific start */
#define STT_HIPROC 15    /* Processor-specific end */

#define STN_UNDEF 0 /* End of a hash chain */

#define ELF32_ST_VISIBILITY(o) ((o) & 0x03) /* Visibility */
#define ELF64_ST_VISIBILITY(o) ELF32_ST_VISIBILITY(o)

#define STV_DEFAULT 0   /* Default visibility */
#define STV_INTERNAL 1  /* Processor-specific hidden */
#define STV_HIDDEN 2    /* Hidden */
#define STV_PROTECTED 3 /* Protected */

typedef struct {
    Elf32_Addr r_offset; /* Relocation address */
    Elf32_Word r_info;   /* Symbol index and type */
} Elf32_Rel;

typedef struct {
    Elf64_Addr r_offset; /* Relocation address */
    Elf64_Xword r_info;  /* Symbol index and type */
} Elf64_Rel;

typedef struct {
    Elf32_Addr r_offset;  /* Relocation address */
    Elf32_Word r_info;    /* Symbol index and type */
    Elf32_Sword r_addend; /* Addend */
} Elf32_Rela;

typedef struct {
    Elf64_Addr r_offset;   /* Relocation address */
    Elf64_Xword r_info;    /* Symbol index and type */
    Elf64_Sxword r_addend; /* Addend */
} Elf64_Rela;

typedef Elf32_Word Elf32_Relr;
typedef Elf64_Xword Elf64_Relr;

#define ELF32_R_SYM(val) ((val) >> 8)    /* Symbol index */
#define ELF32_R_TYPE(val) ((val) & 0xff) /* Reloc type */
#define ELF32_R_INFO(sym, type) (((sym) << 8) + ((type) & 0xff)) /* Pack */
#define ELF64_R_SYM(i) ((i) >> 32)         /* Symbol index */
#define ELF64_R_TYPE(i) ((i) & 0xffffffff) /* Reloc type */
#define ELF64_R_INFO(sym, type) ((((Elf64_Xword)(sym)) << 32) + (type))

typedef struct {
    Elf32_Word p_type;   /* Segment type */
    Elf32_Off p_offset;  /* File offset */
    Elf32_Addr p_vaddr;  /* Virtual address */
    Elf32_Addr p_paddr;  /* Physical address */
    Elf32_Word p_filesz; /* File size */
    Elf32_Word p_memsz;  /* Memory size */
    Elf32_Word p_flags;  /* Flags */
    Elf32_Word p_align;  /* Alignment */
} Elf32_Phdr;

typedef struct {
    Elf64_Word p_type;    /* Segment type */
    Elf64_Word p_flags;   /* Flags */
    Elf64_Off p_offset;   /* File offset */
    Elf64_Addr p_vaddr;   /* Virtual address */
    Elf64_Addr p_paddr;   /* Physical address */
    Elf64_Xword p_filesz; /* File size */
    Elf64_Xword p_memsz;  /* Memory size */
    Elf64_Xword p_align;  /* Alignment */
} Elf64_Phdr;

/* p_type */
#define PT_NULL 0                  /* Unused */
#define PT_LOAD 1                  /* Loadable segment */
#define PT_DYNAMIC 2               /* Dynamic linking info */
#define PT_INTERP 3                /* Interpreter */
#define PT_NOTE 4                  /* Auxiliary information */
#define PT_SHLIB 5                 /* Reserved */
#define PT_PHDR 6                  /* Program header table */
#define PT_TLS 7                   /* Thread-local storage */
#define PT_NUM 8                   /* Number of defined types */
#define PT_LOOS 0x60000000         /* OS-specific start */
#define PT_GNU_EH_FRAME 0x6474e550 /* GNU .eh_frame_hdr */
#define PT_GNU_STACK 0x6474e551    /* GNU stack flags */
#define PT_GNU_RELRO 0x6474e552    /* GNU read-only after reloc */
#define PT_GNU_PROPERTY 0x6474e553 /* GNU property */
#define PT_HIOS 0x6fffffff         /* OS-specific end */
#define PT_LOPROC 0x70000000       /* Processor-specific start */
#define PT_HIPROC 0x7fffffff       /* Processor-specific end */

#define PN_XNUM 0xffff /* Extended program header count */

/* p_flags */
#define PF_X (1 << 0)          /* Execute */
#define PF_W (1 << 1)          /* Write */
#define PF_R (1 << 2)          /* Read */
#define PF_MASKOS 0x0ff00000   /* OS-specific mask */
#define PF_MASKPROC 0xf0000000 /* Processor-specific mask */

typedef struct {
    Elf32_Word n_namesz; /* Name length */
    Elf32_Word n_descsz; /* Descriptor length */
    Elf32_Word n_type;   /* Note type */
} Elf32_Nhdr;

typedef struct {
    Elf64_Word n_namesz; /* Name length */
    Elf64_Word n_descsz; /* Descriptor length */
    Elf64_Word n_type;   /* Note type */
} Elf64_Nhdr;

#define NT_PRSTATUS 1            /* Process status */
#define NT_PRFPREG 2             /* Floating-point registers */
#define NT_FPREGSET 2            /* Alias */
#define NT_PRPSINFO 3            /* Process info */
#define NT_AUXV 6                /* Auxiliary vector */
#define NT_SIGINFO 0x53494749    /* Signal info */
#define NT_FILE 0x46494c45       /* Mapped files */
#define NT_386_TLS 0x200         /* i386 TLS */
#define NT_X86_XSTATE 0x202      /* x86 XSAVE state */
#define NT_ARM_VFP 0x400         /* ARM VFP/NEON */
#define NT_ARM_TLS 0x401         /* ARM TLS */
#define NT_GNU_ABI_TAG 1         /* GNU ABI tag */
#define NT_GNU_HWCAP 2           /* GNU hwcap */
#define NT_GNU_BUILD_ID 3        /* GNU build id */
#define NT_GNU_PROPERTY_TYPE_0 5 /* GNU property */

typedef struct {
    Elf32_Sword d_tag;
    union {
        Elf32_Word d_val;
        Elf32_Addr d_ptr;
    } d_un;
} Elf32_Dyn;

typedef struct {
    Elf64_Sxword d_tag;
    union {
        Elf64_Xword d_val;
        Elf64_Addr d_ptr;
    } d_un;
} Elf64_Dyn;

/* d_tag */
#define DT_NULL 0                /* End of dynamic array */
#define DT_NEEDED 1              /* Needed library name */
#define DT_PLTRELSZ 2            /* PLT reloc size */
#define DT_PLTGOT 3              /* PLT/GOT address */
#define DT_HASH 4                /* Symbol hash table */
#define DT_STRTAB 5              /* String table */
#define DT_SYMTAB 6              /* Symbol table */
#define DT_RELA 7                /* RELA relocs */
#define DT_RELASZ 8              /* RELA size */
#define DT_RELAENT 9             /* RELA entry size */
#define DT_STRSZ 10              /* String table size */
#define DT_SYMENT 11             /* Symbol entry size */
#define DT_INIT 12               /* Init function */
#define DT_FINI 13               /* Fini function */
#define DT_SONAME 14             /* Shared object name */
#define DT_RPATH 15              /* Library search path */
#define DT_SYMBOLIC 16           /* Start symbol search here */
#define DT_REL 17                /* REL relocs */
#define DT_RELSZ 18              /* REL size */
#define DT_RELENT 19             /* REL entry size */
#define DT_PLTREL 20             /* PLT reloc type */
#define DT_DEBUG 21              /* Debugger info */
#define DT_TEXTREL 22            /* Relocs to read-only text */
#define DT_JMPREL 23             /* PLT relocs */
#define DT_BIND_NOW 24           /* Process all relocs first */
#define DT_INIT_ARRAY 25         /* Init array */
#define DT_FINI_ARRAY 26         /* Fini array */
#define DT_INIT_ARRAYSZ 27       /* Init array size */
#define DT_FINI_ARRAYSZ 28       /* Fini array size */
#define DT_RUNPATH 29            /* Library search path */
#define DT_FLAGS 30              /* Flags */
#define DT_ENCODING 32           /* Encoded range start */
#define DT_PREINIT_ARRAY 32      /* Preinit array */
#define DT_PREINIT_ARRAYSZ 33    /* Preinit array size */
#define DT_SYMTAB_SHNDX 34       /* Symtab section indexes */
#define DT_RELRSZ 35             /* RELR size */
#define DT_RELR 36               /* RELR relocs */
#define DT_RELRENT 37            /* RELR entry size */
#define DT_NUM 38                /* Number of defined tags */
#define DT_LOOS 0x6000000d       /* OS-specific start */
#define DT_HIOS 0x6ffff000       /* OS-specific end */
#define DT_LOPROC 0x70000000     /* Processor-specific start */
#define DT_HIPROC 0x7fffffff     /* Processor-specific end */
#define DT_GNU_HASH 0x6ffffef5   /* GNU hash table */
#define DT_VERSYM 0x6ffffff0     /* Version symbol table */
#define DT_RELACOUNT 0x6ffffff9  /* RELA relative count */
#define DT_RELCOUNT 0x6ffffffa   /* REL relative count */
#define DT_FLAGS_1 0x6ffffffb    /* State flags */
#define DT_VERDEF 0x6ffffffc     /* Version definitions */
#define DT_VERDEFNUM 0x6ffffffd  /* Version definition count */
#define DT_VERNEED 0x6ffffffe    /* Version needs */
#define DT_VERNEEDNUM 0x6fffffff /* Version need count */

#define DF_ORIGIN 0x00000001     /* $ORIGIN used */
#define DF_SYMBOLIC 0x00000002   /* Symbolic linking */
#define DF_TEXTREL 0x00000004    /* Text relocations */
#define DF_BIND_NOW 0x00000008   /* Bind now */
#define DF_STATIC_TLS 0x00000010 /* Static TLS model */

typedef struct {
    uint32_t a_type; /* Entry type */
    union {
        uint32_t a_val; /* Integer value */
    } a_un;
} Elf32_auxv_t;

typedef struct {
    uint64_t a_type; /* Entry type */
    union {
        uint64_t a_val; /* Integer value */
    } a_un;
} Elf64_auxv_t;

#define AT_NULL 0           /* End of vector */
#define AT_IGNORE 1         /* Ignore entry */
#define AT_EXECFD 2         /* Program file descriptor */
#define AT_PHDR 3           /* Program headers address */
#define AT_PHENT 4          /* Program header entry size */
#define AT_PHNUM 5          /* Program header count */
#define AT_PAGESZ 6         /* System page size */
#define AT_BASE 7           /* Interpreter base */
#define AT_FLAGS 8          /* Flags */
#define AT_ENTRY 9          /* Entry point */
#define AT_NOTELF 10        /* Program is not ELF */
#define AT_UID 11           /* Real uid */
#define AT_EUID 12          /* Effective uid */
#define AT_GID 13           /* Real gid */
#define AT_EGID 14          /* Effective gid */
#define AT_PLATFORM 15      /* Platform string */
#define AT_HWCAP 16         /* Arch hw capabilities */
#define AT_CLKTCK 17        /* times() frequency */
#define AT_SECURE 23        /* Secure mode */
#define AT_BASE_PLATFORM 24 /* Real platform string */
#define AT_RANDOM 25        /* 16 random bytes */
#define AT_HWCAP2 26        /* More hw capabilities */
#define AT_EXECFN 31        /* Program pathname */
#define AT_SYSINFO 32       /* vDSO syscall page */
#define AT_SYSINFO_EHDR 33  /* vDSO ELF header */
#define AT_MINSIGSTKSZ 51   /* Minimum signal stack */

#ifdef __cplusplus
}
#endif

#endif /* _QLIBC_ELF_H_ */
