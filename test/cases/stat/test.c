#include <fcntl.h>
#include <stddef.h>
#include <sys/stat.h>
#include <sys/types.h>
#ifdef __GNUC__
#include <time.h>
#endif
#include <unistd.h>
#include <utest.h>

UTEST_TEST_CASE(type) {
#if defined(__x86_64__)
  EXPECT_EQUAL_UINT(offsetof(struct stat, st_dev), 0);
  EXPECT_EQUAL_UINT(offsetof(struct stat, st_ino), 8);
  EXPECT_EQUAL_UINT(offsetof(struct stat, st_nlink), 16);
  EXPECT_EQUAL_UINT(offsetof(struct stat, st_mode), 24);
  EXPECT_EQUAL_UINT(offsetof(struct stat, st_uid), 24 + sizeof(mode_t));
  EXPECT_EQUAL_UINT(offsetof(struct stat, st_gid),
                    24 + sizeof(mode_t) + sizeof(uid_t));
  EXPECT_EQUAL_UINT(offsetof(struct stat, st_rdev), 40);
  EXPECT_EQUAL_UINT(offsetof(struct stat, st_size), 40 + sizeof(dev_t));
  EXPECT_EQUAL_UINT(offsetof(struct stat, st_blksize), 56);
  EXPECT_EQUAL_UINT(offsetof(struct stat, st_blocks), 64);
  EXPECT_EQUAL_UINT(offsetof(struct stat, st_atime), 72);
  EXPECT_EQUAL_UINT(offsetof(struct stat, st_mtime),
                    72 + sizeof(struct timespec));
  EXPECT_EQUAL_UINT(offsetof(struct stat, st_ctime),
                    72 + sizeof(struct timespec) * 2);
  EXPECT_EQUAL_UINT(sizeof(struct stat), 144);
#endif
#if defined(__i386__)
  EXPECT_EQUAL_UINT(offsetof(struct stat, st_dev), 0);
  EXPECT_EQUAL_UINT(offsetof(struct stat, st_ino), 12);
  EXPECT_EQUAL_UINT(offsetof(struct stat, st_mode), 16);
  EXPECT_EQUAL_UINT(offsetof(struct stat, st_nlink), 20);
  EXPECT_EQUAL_UINT(offsetof(struct stat, st_uid), 24);
  EXPECT_EQUAL_UINT(offsetof(struct stat, st_gid), 28);
  EXPECT_EQUAL_UINT(offsetof(struct stat, st_rdev), 32);
  EXPECT_EQUAL_UINT(offsetof(struct stat, st_size), 44);
  EXPECT_EQUAL_UINT(offsetof(struct stat, st_blksize), 48);
  EXPECT_EQUAL_UINT(offsetof(struct stat, st_blocks), 52);
  EXPECT_EQUAL_UINT(offsetof(struct stat, st_atime), 56);
  EXPECT_EQUAL_UINT(offsetof(struct stat, st_mtime), 64);
  EXPECT_EQUAL_UINT(offsetof(struct stat, st_ctime), 72);
  EXPECT_EQUAL_UINT(sizeof(struct stat), 88);
#endif
}

UTEST_TEST_CASE(stat) {
  struct stat st;
  int ret = stat(__FILE__, &st);
  EXPECT_EQUAL_INT(ret, 0);
  EXPECT_TRUE(st.st_dev > 0);
  EXPECT_TRUE(st.st_ino > 0);
  EXPECT_TRUE(st.st_nlink > 0);
  EXPECT_TRUE(S_ISREG(st.st_mode));
  EXPECT_TRUE(st.st_size > 0);
  EXPECT_TRUE(st.st_blksize > 0);
  EXPECT_TRUE(st.st_blocks > 0);
  EXPECT_TRUE(st.st_atime >= 0);
  EXPECT_TRUE(st.st_mtime >= 0);
  EXPECT_TRUE(st.st_ctime >= 0);

  int fd = open(__FILE__, O_RDONLY);
  EXPECT_TRUE(fd >= 0);
  off_t size = lseek(fd, 0, SEEK_END);
  EXPECT_TRUE(size > 0);
  EXPECT_EQUAL_INT(st.st_size, size);
  EXPECT_EQUAL_INT(close(fd), 0);
}

UTEST_TEST_CASE(fstat) {
  int fd = open(__FILE__, O_RDONLY);
  EXPECT_TRUE(fd >= 0);

  struct stat st;
  int ret = fstat(fd, &st);
  EXPECT_EQUAL_INT(ret, 0);
  EXPECT_TRUE(st.st_dev > 0);
  EXPECT_TRUE(st.st_ino > 0);
  EXPECT_TRUE(st.st_nlink > 0);
  EXPECT_TRUE(S_ISREG(st.st_mode));
  EXPECT_TRUE(st.st_size > 0);
  EXPECT_TRUE(st.st_blksize > 0);
  EXPECT_TRUE(st.st_blocks > 0);

  off_t size = lseek(fd, 0, SEEK_END);
  EXPECT_TRUE(size > 0);
  EXPECT_EQUAL_INT(st.st_size, size);

  EXPECT_EQUAL_INT(close(fd), 0);
}

UTEST_TEST_SUITE(stat) {
  UTEST_RUN_TEST_CASE(type);
  UTEST_RUN_TEST_CASE(stat);
  UTEST_RUN_TEST_CASE(fstat);
}