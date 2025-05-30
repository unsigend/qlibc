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
extern UTEST_TEST_SUITE(stdalign);
extern UTEST_TEST_SUITE(stdbool);
extern UTEST_TEST_SUITE(stddef);
extern UTEST_TEST_SUITE(stdint);

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
        UTEST_RUN_TEST_SUITE(stdalign);
        UTEST_RUN_TEST_SUITE(stdbool);
        UTEST_RUN_TEST_SUITE(stddef);
        UTEST_RUN_TEST_SUITE(stdint);
    }else{
        if (MATCH(argv[1], "assert")){
            UTEST_RUN_TEST_SUITE(assert);
        }else if (MATCH(argv[1], "ctype")){
            UTEST_RUN_TEST_SUITE(ctype);
        }else if (MATCH(argv[1], "limits")){
            UTEST_RUN_TEST_SUITE(limits);
        }else if (MATCH(argv[1], "stdalign")){
            UTEST_RUN_TEST_SUITE(stdalign);
        }else if (MATCH(argv[1], "stdbool")){
            UTEST_RUN_TEST_SUITE(stdbool);
        }else if (MATCH(argv[1], "stddef")){
            UTEST_RUN_TEST_SUITE(stddef);
        }else if (MATCH(argv[1], "stdint")){
            UTEST_RUN_TEST_SUITE(stdint);
        }
    }
    
    UTEST_END();

    return 0;
}