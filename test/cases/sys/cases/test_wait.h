#include <sys/wait.h>
#include <unistd.h>
#include <utest.h>

UTEST_TEST_CASE(wait_macros) {
  EXPECT_EQUAL_UINT(WNOHANG, 1);
  EXPECT_EQUAL_UINT(WUNTRACED, 2);
  EXPECT_EQUAL_UINT(WCONTINUED, 8);
}
