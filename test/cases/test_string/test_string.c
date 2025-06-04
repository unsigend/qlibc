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
#include "test_strpbrk.h"
#include "test_strstr.h"
#include "test_strtok.h"

#include "test_strcpy.h"
#include "test_strncpy.h"
#include "test_strcat.h"
#include "test_strncat.h"
#include "test_strxfrm.h"

UTEST_TEST_SUITE(string){
    // character array examination
    UTEST_RUN_TEST_CASE(memchr);
    UTEST_RUN_TEST_CASE(memcmp);
    UTEST_RUN_TEST_CASE(memset);
    UTEST_RUN_TEST_CASE(memcpy);
    UTEST_RUN_TEST_CASE(memmove);

    // string examination
    UTEST_RUN_TEST_CASE(strlen);
    UTEST_RUN_TEST_CASE(strcmp);
    UTEST_RUN_TEST_CASE(strncmp);
    UTEST_RUN_TEST_CASE(strcoll);
    UTEST_RUN_TEST_CASE(strchr);
    UTEST_RUN_TEST_CASE(strrchr);
    UTEST_RUN_TEST_CASE(strspn);
    UTEST_RUN_TEST_CASE(strcspn);
    UTEST_RUN_TEST_CASE(strpbrk);
    UTEST_RUN_TEST_CASE(strstr);
    UTEST_RUN_TEST_CASE(strtok);
    
    // string manipulation
    UTEST_RUN_TEST_CASE(strcpy);
    UTEST_RUN_TEST_CASE(strncpy);
    UTEST_RUN_TEST_CASE(strcat);
    UTEST_RUN_TEST_CASE(strncat);
    UTEST_RUN_TEST_CASE(strxfrm);
}