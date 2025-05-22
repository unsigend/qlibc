#include <utest.h>

#include <ctype.h>
#include <stdint.h>

UTEST_TEST_CASE(isalpha){
    for (unsigned char c = 0; c != UINT8_MAX; c++){
        if (c >= 'a' && c <= 'z'){
            EXPECT_TRUE(isalpha(c));
        }else if (c >= 'A' && c <= 'Z'){
            EXPECT_TRUE(isalpha(c));
        }else{
            EXPECT_FALSE(isalpha(c));
        }
    }
}
UTEST_TEST_CASE(isalnum){
    for (unsigned char c = 0; c != UINT8_MAX; c++){
        if (c >= 'a' && c <= 'z'){
            EXPECT_TRUE(isalnum(c));
        }else if (c >= 'A' && c <= 'Z'){
            EXPECT_TRUE(isalnum(c));
        }else if (c >= '0' && c <= '9'){
            EXPECT_TRUE(isalnum(c));
        }else{
            EXPECT_FALSE(isalnum(c));
         }
    }
}
UTEST_TEST_CASE(iscntrl){
    for (unsigned char c = 0; c != UINT8_MAX; c++){
        if (c <= 0x1f || c == 0x7f){
            EXPECT_TRUE(iscntrl(c));
        }else{
            EXPECT_FALSE(iscntrl(c));
        }
    }
}
UTEST_TEST_CASE(isdigit){
    for (unsigned char c = 0; c != UINT8_MAX; c++){
        if (c >= '0' && c <= '9'){
            EXPECT_TRUE(isdigit(c));
        }else{
            EXPECT_FALSE(isdigit(c));
        }
    }
}
UTEST_TEST_CASE(islower){
    for (unsigned char c = 0; c != UINT8_MAX; c++){
        if (c >= 'a' && c <= 'z'){
            EXPECT_TRUE(islower(c));
        }else{
            EXPECT_FALSE(islower(c));
        }
    }
}
UTEST_TEST_CASE(isupper){
    for (unsigned char c = 0; c != UINT8_MAX; c++){
        if (c >= 'A' && c <= 'Z'){
            EXPECT_TRUE(isupper(c));
        }else{
            EXPECT_FALSE(isupper(c));
        }
    }
}
UTEST_TEST_CASE(isxdigit){
    for (unsigned char c = 0; c != UINT8_MAX; c++){
        if (c >= '0' && c <= '9'){
            EXPECT_TRUE(isxdigit(c));
        }else if (c >= 'A' && c <= 'F'){
            EXPECT_TRUE(isxdigit(c));
        }else if (c >= 'a' && c <= 'f'){
            EXPECT_TRUE(isxdigit(c));
        }else{
            EXPECT_FALSE(isxdigit(c));
        }
    }
}
UTEST_TEST_CASE(isgraph){
    for (unsigned char c = 0; c != UINT8_MAX; c++){
        if (c >= 0x21 && c <= 0x7e){
            EXPECT_TRUE(isgraph(c));
        }else{
            EXPECT_FALSE(isgraph(c));
        }
    }
}
UTEST_TEST_CASE(ispunct){
    for (unsigned char c = 0; c != UINT8_MAX; c++){
        if (c >= 0x21 && c <= 0x2f){
            EXPECT_TRUE(ispunct(c));
        }else if (c >= 0x3a && c <= 0x40){
            EXPECT_TRUE(ispunct(c));
        }else if (c >= 0x5b && c <= 0x60){
            EXPECT_TRUE(ispunct(c));
        }else if (c >= 0x7b && c <= 0x7e){
            EXPECT_TRUE(ispunct(c));
        }else{
            EXPECT_FALSE(ispunct(c));
        }
    }
}
UTEST_TEST_CASE(isspace){
    for (unsigned char c = 0; c != UINT8_MAX; c++){
        if (c == 0x20 || (c >= 0x09 && c <= 0x0d)){
            EXPECT_TRUE(isspace(c));
        }else{
            EXPECT_FALSE(isspace(c));
        }
    }
}
UTEST_TEST_CASE(isblank){
    for (unsigned char c = 0; c != UINT8_MAX; c++){
        if (c == 0x20 || c == 0x09){
            EXPECT_TRUE(isblank(c));
        }else{
            EXPECT_FALSE(isblank(c));
        }
    }
}
UTEST_TEST_CASE(isprint){
    for (unsigned char c = 0; c != UINT8_MAX; c++){
        if (c >= 0x20 && c <= 0x7e){
            EXPECT_TRUE(isprint(c));
        }else{
            EXPECT_FALSE(isprint(c));
        }
    }
}
UTEST_TEST_CASE(tolower){
    for (unsigned char c = 0; c != UINT8_MAX; c++){
        if (c >= 'A' && c <= 'Z'){
            EXPECT_EQUAL_INT(tolower(c), (int)c | 32);
        }else{
            EXPECT_EQUAL_INT(tolower(c), (int)c);
        }
    }
}
UTEST_TEST_CASE(toupper){
    for (unsigned char c = 0; c != UINT8_MAX; c++){
        if (c >= 'a' && c <= 'z'){
            EXPECT_EQUAL_INT(toupper(c), (int)c - 32);
        }else{
            EXPECT_EQUAL_INT(toupper(c), (int)c);
        }
    }
}
UTEST_TEST_SUITE(ctype){
    UTEST_RUN_TEST_CASE(isalpha);
    UTEST_RUN_TEST_CASE(isalnum);
    UTEST_RUN_TEST_CASE(iscntrl);
    UTEST_RUN_TEST_CASE(isdigit);
    UTEST_RUN_TEST_CASE(islower);
    UTEST_RUN_TEST_CASE(isupper);
    UTEST_RUN_TEST_CASE(isxdigit);
    UTEST_RUN_TEST_CASE(isgraph);
    UTEST_RUN_TEST_CASE(ispunct);
    UTEST_RUN_TEST_CASE(isspace);
    UTEST_RUN_TEST_CASE(isblank);
    UTEST_RUN_TEST_CASE(isprint);
    UTEST_RUN_TEST_CASE(tolower);
    UTEST_RUN_TEST_CASE(toupper);
}