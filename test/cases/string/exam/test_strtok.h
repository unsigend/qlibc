#include <utest.h>
#include <string.h>

UTEST_TEST_CASE(strtok){
    {
        char str[] = "hello world";
        char *result = strtok(str, " ");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "hello") == 0);
        result = strtok(NULL, " ");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "world") == 0);
        result = strtok(NULL, " ");
        EXPECT_NULL(result);
    }
    {
        char str[] = "a,b,c";
        char *result = strtok(str, ",");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "a") == 0);
        result = strtok(NULL, ",");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "b") == 0);
        result = strtok(NULL, ",");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "c") == 0);
        result = strtok(NULL, ",");
        EXPECT_NULL(result);
    }
    {
        char str[] = "test";
        char *result = strtok(str, " ");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "test") == 0);
        result = strtok(NULL, " ");
        EXPECT_NULL(result);
    }
    {
        char str[] = "  hello  world  ";
        char *result = strtok(str, " ");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "hello") == 0);
        result = strtok(NULL, " ");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "world") == 0);
        result = strtok(NULL, " ");
        EXPECT_NULL(result);
    }
    {
        char str[] = "one\ttwo\tthree";
        char *result = strtok(str, "\t");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "one") == 0);
        result = strtok(NULL, "\t");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "two") == 0);
        result = strtok(NULL, "\t");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "three") == 0);
        result = strtok(NULL, "\t");
        EXPECT_NULL(result);
    }
    {
        char str[] = "a:b:c:d";
        char *result = strtok(str, ":");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "a") == 0);
        result = strtok(NULL, ":");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "b") == 0);
        result = strtok(NULL, ":");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "c") == 0);
        result = strtok(NULL, ":");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "d") == 0);
        result = strtok(NULL, ":");
        EXPECT_NULL(result);
    }
    {
        char str[] = "hello";
        char *result = strtok(str, "xyz");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "hello") == 0);
        result = strtok(NULL, "xyz");
        EXPECT_NULL(result);
    }
    {
        char str[] = "";
        char *result = strtok(str, " ");
        EXPECT_NULL(result);
    }
    {
        char str[] = "   ";
        char *result = strtok(str, " ");
        EXPECT_NULL(result);
    }
    {
        char str[] = "a";
        char *result = strtok(str, " ");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "a") == 0);
        result = strtok(NULL, " ");
        EXPECT_NULL(result);
    }
    {
        char str[] = "a b";
        char *result = strtok(str, " ");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "a") == 0);
        result = strtok(NULL, " ");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "b") == 0);
        result = strtok(NULL, " ");
        EXPECT_NULL(result);
    }
    {
        char str[] = "abc";
        char *result = strtok(str, "b");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "a") == 0);
        result = strtok(NULL, "b");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "c") == 0);
        result = strtok(NULL, "b");
        EXPECT_NULL(result);
    }
    {
        char str[] = "path/to/file";
        char *result = strtok(str, "/");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "path") == 0);
        result = strtok(NULL, "/");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "to") == 0);
        result = strtok(NULL, "/");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "file") == 0);
        result = strtok(NULL, "/");
        EXPECT_NULL(result);
    }
    {
        char str[] = "one,two,three,four";
        char *result = strtok(str, ",");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "one") == 0);
        result = strtok(NULL, ",");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "two") == 0);
        result = strtok(NULL, ",");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "three") == 0);
        result = strtok(NULL, ",");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "four") == 0);
        result = strtok(NULL, ",");
        EXPECT_NULL(result);
    }
    {
        char str[] = "word";
        char *result = strtok(str, "word");
        EXPECT_NULL(result);
    }
    {
        char str[] = "word";
        char *result = strtok(str, "or");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "w") == 0);
        result = strtok(NULL, "or");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "d") == 0);
        result = strtok(NULL, "or");
        EXPECT_NULL(result);
    }
    {
        char str[] = "a|b|c";
        char *result = strtok(str, "|");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "a") == 0);
        result = strtok(NULL, "|");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "b") == 0);
        result = strtok(NULL, "|");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "c") == 0);
        result = strtok(NULL, "|");
        EXPECT_NULL(result);
    }
    {
        char str[] = "123-456-789";
        char *result = strtok(str, "-");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "123") == 0);
        result = strtok(NULL, "-");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "456") == 0);
        result = strtok(NULL, "-");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "789") == 0);
        result = strtok(NULL, "-");
        EXPECT_NULL(result);
    }
    {
        char str[] = "hello";
        char *result = strtok(str, "");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "hello") == 0);
        result = strtok(NULL, "");
        EXPECT_NULL(result);
    }
    {
        char str[] = "a b c d e";
        char *result = strtok(str, " ");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "a") == 0);
        result = strtok(NULL, " ");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "b") == 0);
        result = strtok(NULL, " ");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "c") == 0);
        result = strtok(NULL, " ");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "d") == 0);
        result = strtok(NULL, " ");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "e") == 0);
        result = strtok(NULL, " ");
        EXPECT_NULL(result);
    }
    {
        char str[] = "test";
        char *result = strtok(str, "t");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "es") == 0);
        result = strtok(NULL, "t");
        EXPECT_NULL(result);
    }
    {
        char str[] = "test";
        char *result = strtok(str, "e");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "t") == 0);
        result = strtok(NULL, "e");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(strcmp(result, "st") == 0);
        result = strtok(NULL, "e");
        EXPECT_NULL(result);
    }
}
