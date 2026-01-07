#include <utest.h>
#include <elf.h>

UTEST_TEST_CASE(type){
    EXPECT_EQUAL_UINT(sizeof(Elf32_Addr), sizeof(uint32_t));
    EXPECT_EQUAL_UINT(sizeof(Elf32_Half), sizeof(uint16_t));
    EXPECT_EQUAL_UINT(sizeof(Elf32_Off), sizeof(uint32_t));
    EXPECT_EQUAL_UINT(sizeof(Elf32_Sword), sizeof(int32_t));
    EXPECT_EQUAL_UINT(sizeof(Elf32_Word), sizeof(uint32_t));
    EXPECT_EQUAL_UINT(sizeof(Elf64_Addr), sizeof(uint64_t));
    EXPECT_EQUAL_UINT(sizeof(Elf64_Half), sizeof(uint16_t));
    EXPECT_EQUAL_UINT(sizeof(Elf64_Off), sizeof(uint64_t));
    EXPECT_EQUAL_UINT(sizeof(Elf64_Sword), sizeof(int32_t));
    EXPECT_EQUAL_UINT(sizeof(Elf64_Word), sizeof(uint32_t));
}

UTEST_TEST_SUITE(elf){
    UTEST_RUN_TEST_CASE(type);
}