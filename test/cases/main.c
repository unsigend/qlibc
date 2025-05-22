/**
 * @brief: Main test entry for qlibc
 * Dispatch the test cases based on the command line arguments
 */

#include <utest.h>
#define MATCH(ARG, CASE)    (strcmp(ARG, CASE) == 0)

extern UTEST_TEST_SUITE(assert);
extern UTEST_TEST_SUITE(string);
extern UTEST_TEST_SUITE(ctype);
extern UTEST_TEST_SUITE(limits);

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    UTEST_BEGIN();
    UTEST_CLEAR_FLAG(UTEST_FLAG_STYLE_FULL);


    // Run test suites here
    if (argc <= 1){
        UTEST_RUN_TEST_SUITE(assert);
        UTEST_RUN_TEST_SUITE(ctype);
        UTEST_RUN_TEST_SUITE(limits);
    }else{
        if (MATCH(argv[1], "assert")){
            UTEST_RUN_TEST_SUITE(assert);
        }else if (MATCH(argv[1], "ctype")){
            UTEST_RUN_TEST_SUITE(ctype);
        }else if (MATCH(argv[1], "limits")){
            UTEST_RUN_TEST_SUITE(limits);
        }else { }
    }
    
    UTEST_END();

    return 0;
}