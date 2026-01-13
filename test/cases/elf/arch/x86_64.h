#include <elf.h>
#include <utest.h>

UTEST_TEST_CASE(elf_test) {
    EXPECT_EQUAL_UINT(sizeof(Elf64_Half), 2);
    EXPECT_EQUAL_UINT(sizeof(Elf64_Word), 4);
    EXPECT_EQUAL_UINT(sizeof(Elf64_Sword), 4);
    EXPECT_EQUAL_UINT(sizeof(Elf64_Xword), 8);
    EXPECT_EQUAL_UINT(sizeof(Elf64_Sxword), 8);
    EXPECT_EQUAL_UINT(sizeof(Elf64_Addr), 8);
    EXPECT_EQUAL_UINT(sizeof(Elf64_Off), 8);
    EXPECT_EQUAL_UINT(sizeof(Elf64_Section), 2);
    EXPECT_EQUAL_UINT(sizeof(Elf64_Versym), 2);
    EXPECT_EQUAL_UINT(sizeof(Elf64_Ehdr), 64);
    EXPECT_EQUAL_UINT(sizeof(Elf64_Shdr), 64);
    EXPECT_EQUAL_UINT(sizeof(Elf64_Sym), 24);
    EXPECT_EQUAL_UINT(sizeof(Elf64_Rel), 16);
}
