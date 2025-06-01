#include <utest.h>

#include "test_memchr.h"
#include "test_memcmp.h"
#include "test_memset.h"
#include "test_memcpy.h"
#include "test_memmove.h"

#include "test_strlen.h"
#include "test_strcmp.h"
#include "test_strncmp.h"
#include "test_strcoll.h"
#include "test_strchr.h"
#include "test_strrchr.h"
#include "test_strspn.h"
#include "test_strcspn.h"

UTEST_TEST_SUITE(string){
    UTEST_RUN_TEST_CASE(memchr);
    UTEST_RUN_TEST_CASE(memcmp);
    UTEST_RUN_TEST_CASE(memset);
    UTEST_RUN_TEST_CASE(memcpy);
    UTEST_RUN_TEST_CASE(memmove);

    UTEST_RUN_TEST_CASE(strlen);
    UTEST_RUN_TEST_CASE(strcmp);
    UTEST_RUN_TEST_CASE(strncmp);
    UTEST_RUN_TEST_CASE(strcoll);
    UTEST_RUN_TEST_CASE(strchr);
    UTEST_RUN_TEST_CASE(strrchr);
    UTEST_RUN_TEST_CASE(strspn);
    UTEST_RUN_TEST_CASE(strcspn);
}