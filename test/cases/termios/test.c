#include <termios.h>
#include <utest.h>

UTEST_TEST_CASE(type) {
  EXPECT_TRUE(sizeof(speed_t) == sizeof(unsigned int));
  EXPECT_TRUE(sizeof(cc_t) == sizeof(char));
  EXPECT_TRUE(sizeof(tcflag_t) == sizeof(unsigned int));

  EXPECT_EQUAL_INT(NCCS, 32);

  EXPECT_EQUAL_UINT(sizeof(struct termios), 60);

  EXPECT_EQUAL_UINT(offsetof(struct termios, c_iflag), 0);
  EXPECT_EQUAL_UINT(offsetof(struct termios, c_oflag), 4);
  EXPECT_EQUAL_UINT(offsetof(struct termios, c_cflag), 8);
  EXPECT_EQUAL_UINT(offsetof(struct termios, c_lflag), 12);
  EXPECT_EQUAL_UINT(offsetof(struct termios, c_line), 16);
  EXPECT_EQUAL_UINT(offsetof(struct termios, c_cc), 17);
  EXPECT_EQUAL_UINT(offsetof(struct termios, c_ispeed), 52);
  EXPECT_EQUAL_UINT(offsetof(struct termios, c_ospeed), 56);
}

UTEST_TEST_SUITE(termios) { UTEST_RUN_TEST_CASE(type); }