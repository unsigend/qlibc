#include <errno.h>
#include <fcntl.h>
#ifdef __GNUC__
#include <sys/types.h>
#endif
#include <syscall.h>
#include <unistd.h>
#include <utest.h>

UTEST_TEST_CASE(macro) {
  EXPECT_EQUAL_INT(STDIN_FILENO, 0);
  EXPECT_EQUAL_INT(STDOUT_FILENO, 1);
  EXPECT_EQUAL_INT(STDERR_FILENO, 2);

  EXPECT_EQUAL_INT(SEEK_SET, 0);
  EXPECT_EQUAL_INT(SEEK_CUR, 1);
  EXPECT_EQUAL_INT(SEEK_END, 2);
}

UTEST_TEST_CASE(types) {
  EXPECT_EQUAL_UINT(sizeof(off_t), sizeof(long));
  EXPECT_EQUAL_UINT(sizeof(ssize_t), sizeof(long));
}

UTEST_TEST_CASE(syscall) {
  long ret;

  ret = syscall(SYS_getpid);
  EXPECT_TRUE(ret > 0);

  ret = syscall(SYS_getuid);
  EXPECT_TRUE(ret >= 0);

  ret = syscall(SYS_getgid);
  EXPECT_TRUE(ret >= 0);

  ret = syscall(SYS_getppid);
  EXPECT_TRUE(ret > 0);

#if !defined(__aarch64__)
  errno = 0;
  ret = syscall(99999);
  EXPECT_EQUAL_INT(ret, -1);
  EXPECT_TRUE(errno != 0);
#endif
}

UTEST_TEST_CASE(close) {
  int fd = open(__FILE__, O_RDONLY);
  EXPECT_TRUE(fd != -1);
  EXPECT_EQUAL_INT(close(fd), 0);
}

UTEST_TEST_CASE(lseek) {
  int fd = open(__FILE__, O_RDONLY);
  EXPECT_TRUE(fd >= 0);

  off_t pos = lseek(fd, 0, SEEK_SET);
  EXPECT_TRUE(pos >= 0);

  pos = lseek(fd, 10, SEEK_SET);
  EXPECT_EQUAL_INT(pos, 10);

  pos = lseek(fd, 5, SEEK_CUR);
  EXPECT_EQUAL_INT(pos, 15);

  pos = lseek(fd, 0, SEEK_END);
  EXPECT_TRUE(pos > 0);

  pos = lseek(fd, -10, SEEK_CUR);
  EXPECT_TRUE(pos >= 0);

  EXPECT_EQUAL_INT(close(fd), 0);
}

UTEST_TEST_CASE(read) {
  int fd = open(__FILE__, O_RDONLY);
  EXPECT_TRUE(fd >= 0);

  char buf[64];
  ssize_t n = read(fd, buf, sizeof(buf));
  EXPECT_TRUE(n > 0);
  EXPECT_TRUE(n <= (ssize_t)sizeof(buf));

  n = read(fd, buf, 10);
  EXPECT_TRUE(n >= 0);
  EXPECT_TRUE(n <= 10);

  EXPECT_EQUAL_INT(close(fd), 0);
}

UTEST_TEST_CASE(write) {
  int fd = open("/dev/null", O_WRONLY);
  EXPECT_TRUE(fd >= 0);

  const char *data = "test";
  ssize_t n = write(fd, data, 4);
  EXPECT_EQUAL_INT(n, 4);

  n = write(fd, data, 0);
  EXPECT_EQUAL_INT(n, 0);

  EXPECT_EQUAL_INT(close(fd), 0);
}

UTEST_TEST_SUITE(unistd) {
  // general macros and types
  UTEST_RUN_TEST_CASE(types);
  UTEST_RUN_TEST_CASE(macro);

  // unistd functions
  UTEST_RUN_TEST_CASE(syscall);
  UTEST_RUN_TEST_CASE(close);
  UTEST_RUN_TEST_CASE(lseek);
  UTEST_RUN_TEST_CASE(read);
  UTEST_RUN_TEST_CASE(write);
}