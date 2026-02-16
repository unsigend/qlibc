#define _GNU_SOURCE

// cases
#include "cases/mman.h"
#include "cases/stat.h"
#include "cases/uio.h"

UTEST_TEST_CASE(types) {
  EXPECT_EQUAL_UINT(sizeof(off_t), sizeof(long));
  EXPECT_EQUAL_UINT(sizeof(ssize_t), sizeof(long));
  EXPECT_EQUAL_UINT(sizeof(time_t), sizeof(long));
  EXPECT_EQUAL_UINT(sizeof(ino_t), sizeof(unsigned long));
  EXPECT_EQUAL_UINT(sizeof(dev_t), sizeof(unsigned long long));
  EXPECT_EQUAL_UINT(sizeof(blkcnt_t), sizeof(long));
  EXPECT_EQUAL_UINT(sizeof(blksize_t), sizeof(long));
  EXPECT_EQUAL_UINT(sizeof(nlink_t), sizeof(unsigned long));
  EXPECT_EQUAL_UINT(sizeof(mode_t), sizeof(unsigned int));
  EXPECT_EQUAL_UINT(sizeof(pid_t), sizeof(unsigned int));
  EXPECT_EQUAL_UINT(sizeof(uid_t), sizeof(unsigned int));
  EXPECT_EQUAL_UINT(sizeof(gid_t), sizeof(unsigned int));

#if defined(_QLIBC_SOURCE) || defined(_QLIBC)
  EXPECT_EQUAL_UINT(sizeof(off64_t), 8);
  EXPECT_EQUAL_UINT(sizeof(time64_t), 8);
  EXPECT_EQUAL_UINT(sizeof(ino64_t), 8);
  EXPECT_EQUAL_UINT(sizeof(nlink64_t), 8);
  EXPECT_EQUAL_UINT(sizeof(dev64_t), 8);
  EXPECT_EQUAL_UINT(sizeof(blkcnt64_t), 8);
  EXPECT_EQUAL_UINT(sizeof(blksize64_t), 8);
#endif
}

UTEST_TEST_SUITE(sys) {
  /* types */
  UTEST_RUN_TEST_CASE(types);

  /* uio */
  UTEST_RUN_TEST_CASE(readv);

  /* stat */
  UTEST_RUN_TEST_CASE(stat_types);
  UTEST_RUN_TEST_CASE(stat);
  UTEST_RUN_TEST_CASE(fstat);

  /* mman */
  UTEST_RUN_TEST_CASE(mman);
  UTEST_RUN_TEST_CASE(mmap);
}
