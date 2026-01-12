#include <utest.h>

#include "func/test_isalnum.h"
#include "func/test_isalpha.h"
#include "func/test_isblank.h"
#include "func/test_iscntrl.h"
#include "func/test_isdigit.h"
#include "func/test_isgraph.h"
#include "func/test_islower.h"
#include "func/test_isprint.h"
#include "func/test_ispunct.h"
#include "func/test_isspace.h"
#include "func/test_isupper.h"
#include "func/test_isxdigit.h"
#include "func/test_tolower.h"
#include "func/test_toupper.h"

UTEST_TEST_SUITE(ctype){
    UTEST_RUN_TEST_CASE(isalnum);
    UTEST_RUN_TEST_CASE(isalpha);
    UTEST_RUN_TEST_CASE(isblank);
    UTEST_RUN_TEST_CASE(iscntrl);
    UTEST_RUN_TEST_CASE(isdigit);
    UTEST_RUN_TEST_CASE(isgraph);
    UTEST_RUN_TEST_CASE(islower);
    UTEST_RUN_TEST_CASE(isprint);
    UTEST_RUN_TEST_CASE(ispunct);
    UTEST_RUN_TEST_CASE(isspace);
    UTEST_RUN_TEST_CASE(isupper);
    UTEST_RUN_TEST_CASE(isxdigit);
    UTEST_RUN_TEST_CASE(tolower);
    UTEST_RUN_TEST_CASE(toupper);
}