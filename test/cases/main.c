/**
 * @brief: Main test entry for qlibc
 * Dispatch the test cases based on the command line arguments
 */

#include <utest.h>
#define MATCH(ARG, CASE)    (strcmp(ARG, CASE) == 0)

extern UTEST_TEST_SUITE(assert);
extern UTEST_TEST_SUITE(string);

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;
    
    UTEST_BEGIN();
    UTEST_CLEAR_FLAG(UTEST_FLAG_STYLE_FULL);


    // Run test suites here
    if (argc <= 1){
        UTEST_RUN_TEST_SUITE(assert);
    }else{
        if (MATCH(argv[1], "assert")){
            UTEST_RUN_TEST_SUITE(assert);
        }else if (MATCH(argv[1], "string")){
            
        }else { }
    }
    

    UTEST_END();

    return 0;
}