#define _GNU_SOURCE

#include <fcntl.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <utest.h>

UTEST_TEST_CASE(types) {
  EXPECT_EQUAL_UINT(sizeof(off_t), sizeof(long));
  EXPECT_EQUAL_UINT(sizeof(ssize_t), sizeof(long));
  EXPECT_EQUAL_UINT(sizeof(time_t), sizeof(long));
  EXPECT_EQUAL_UINT(sizeof(ino_t), sizeof(unsigned long));
  EXPECT_EQUAL_UINT(sizeof(dev_t), sizeof(unsigned long long));
  EXPECT_EQUAL_UINT(sizeof(blkcnt_t), sizeof(long));
  EXPECT_EQUAL_UINT(sizeof(blksize_t), sizeof(long));
  EXPECT_EQUAL_UINT(sizeof(mode_t), sizeof(unsigned int));
  EXPECT_EQUAL_UINT(sizeof(pid_t), sizeof(unsigned int));
  EXPECT_EQUAL_UINT(sizeof(uid_t), sizeof(unsigned int));
  EXPECT_EQUAL_UINT(sizeof(gid_t), sizeof(unsigned int));
}

UTEST_TEST_CASE(readv) {
  int fd = open(__FILE__, O_RDONLY);
  EXPECT_TRUE(fd >= 0);

  char buf1[10];
  char buf2[10];
  struct iovec iov[2] = {{buf1, sizeof(buf1)}, {buf2, sizeof(buf2)}};

  ssize_t ret = readv(fd, iov, 2);
  EXPECT_TRUE(ret > 0);

  int close_ret = close(fd);
  EXPECT_EQUAL_INT(close_ret, 0);
}

UTEST_TEST_SUITE(sys) {
  /* types */
  UTEST_RUN_TEST_CASE(types);

  /* functions */
  UTEST_RUN_TEST_CASE(readv);
}
