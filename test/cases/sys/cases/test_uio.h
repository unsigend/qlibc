#include <fcntl.h>
#include <sys/uio.h>
#include <unistd.h>
#include <utest.h>

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