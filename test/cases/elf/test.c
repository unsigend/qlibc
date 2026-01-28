#include <elf.h>
#include <utest.h>

UTEST_TEST_CASE(elf) {
  /* 64-bits types */
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

  /* 32-bits types */
  EXPECT_EQUAL_UINT(sizeof(Elf32_Half), 2);
  EXPECT_EQUAL_UINT(sizeof(Elf32_Word), 4);
  EXPECT_EQUAL_UINT(sizeof(Elf32_Sword), 4);
  EXPECT_EQUAL_UINT(sizeof(Elf32_Xword), 8);
  EXPECT_EQUAL_UINT(sizeof(Elf32_Sxword), 8);
  EXPECT_EQUAL_UINT(sizeof(Elf32_Addr), 4);
  EXPECT_EQUAL_UINT(sizeof(Elf32_Off), 4);
  EXPECT_EQUAL_UINT(sizeof(Elf32_Section), 2);
  EXPECT_EQUAL_UINT(sizeof(Elf32_Versym), 2);
  EXPECT_EQUAL_UINT(sizeof(Elf32_Ehdr), 52);
  EXPECT_EQUAL_UINT(sizeof(Elf32_Shdr), 40);
  EXPECT_EQUAL_UINT(sizeof(Elf32_Sym), 16);
  EXPECT_EQUAL_UINT(sizeof(Elf32_Rel), 8);
}

UTEST_TEST_SUITE(elf) { UTEST_RUN_TEST_CASE(elf); }
