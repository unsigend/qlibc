#include <utest.h>
#include <string.h>

UTEST_TEST_CASE(strpbrk){
    {
        char str[] = "hello";
        char *result = strpbrk(str, "h");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'h');
    }
    {
        char str[] = "hello";
        char *result = strpbrk(str, "e");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'e');
    }
    {
        char str[] = "hello";
        char *result = strpbrk(str, "l");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'l');
    }
    {
        char str[] = "hello";
        char *result = strpbrk(str, "o");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'o');
    }
    {
        char str[] = "hello";
        char *result = strpbrk(str, "xyz");
        EXPECT_NULL(result);
    }
    {
        char str[] = "hello";
        char *result = strpbrk(str, "ABC");
        EXPECT_NULL(result);
    }
    {
        char str[] = "";
        char *result = strpbrk(str, "abc");
        EXPECT_NULL(result);
    }
    {
        char str[] = "hello";
        char *result = strpbrk(str, "");
        EXPECT_NULL(result);
    }
    {
        char str[] = "";
        char *result = strpbrk(str, "");
        EXPECT_NULL(result);
    }
    {
        char str[] = "a";
        char *result = strpbrk(str, "a");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'a');
    }
    {
        char str[] = "a";
        char *result = strpbrk(str, "b");
        EXPECT_NULL(result);
    }
    {
        char str[] = "abc";
        char *result = strpbrk(str, "a");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "abc";
        char *result = strpbrk(str, "b");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'b');
    }
    {
        char str[] = "abc";
        char *result = strpbrk(str, "c");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'c');
    }
    {
        char str[] = "abc";
        char *result = strpbrk(str, "ab");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'a');
    }
    {
        char str[] = "abc";
        char *result = strpbrk(str, "bc");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'b');
    }
    {
        char str[] = "abc";
        char *result = strpbrk(str, "ac");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'a');
    }
    {
        char str[] = "hello";
        char *result = strpbrk(str, "helo");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'h');
    }
    {
        char str[] = "hello";
        char *result = strpbrk(str, "h");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "hello";
        char *result = strpbrk(str, "e");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'e');
    }
    {
        char str[] = "hello";
        char *result = strpbrk(str, "l");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'l');
    }
    {
        char str[] = "hello";
        char *result = strpbrk(str, "o");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'o');
    }
    {
        char str[] = "hello";
        char *result = strpbrk(str, "xyz");
        EXPECT_NULL(result);
    }
    {
        char str[] = "12345";
        char *result = strpbrk(str, "12345");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == '1');
    }
    {
        char str[] = "12345";
        char *result = strpbrk(str, "1");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "12345";
        char *result = strpbrk(str, "5");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == '5');
    }
    {
        char str[] = "12345";
        char *result = strpbrk(str, "54321");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == '1');
    }
    {
        char str[] = "abc123";
        char *result = strpbrk(str, "123");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == '1');
    }
    {
        char str[] = "abc123";
        char *result = strpbrk(str, "abc");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'a');
    }
    {
        char str[] = "123abc";
        char *result = strpbrk(str, "abc");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'a');
    }
    {
        char str[] = "123abc";
        char *result = strpbrk(str, "123");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == '1');
    }
    {
        char str[] = "aaa";
        char *result = strpbrk(str, "a");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "aaa";
        char *result = strpbrk(str, "b");
        EXPECT_NULL(result);
    }
    {
        char str[] = "aabbcc";
        char *result = strpbrk(str, "a");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "aabbcc";
        char *result = strpbrk(str, "b");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'b');
    }
    {
        char str[] = "aabbcc";
        char *result = strpbrk(str, "c");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'c');
    }
    {
        char str[] = "aabbcc";
        char *result = strpbrk(str, "d");
        EXPECT_NULL(result);
    }
    {
        char str[] = "   hello";
        char *result = strpbrk(str, "h");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'h');
    }
    {
        char str[] = "   hello";
        char *result = strpbrk(str, " ");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == ' ');
    }
    {
        char str[] = "   hello";
        char *result = strpbrk(str, "helo");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'h');
    }
    {
        char str[] = "\t\n\vhello";
        char *result = strpbrk(str, "h");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'h');
    }
    {
        char str[] = "\t\n\vhello";
        char *result = strpbrk(str, "\t\n\v");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == '\t');
    }
    {
        char str[] = "test";
        char *result = strpbrk(str, "test");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 't');
    }
    {
        char str[] = "test";
        char *result = strpbrk(str, "t");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "test";
        char *result = strpbrk(str, "e");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'e');
    }
    {
        char str[] = "test";
        char *result = strpbrk(str, "s");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 's');
    }
    {
        char str[] = "test";
        char *result = strpbrk(str, "x");
        EXPECT_NULL(result);
    }
    {
        char str[] = "prefixsuffix";
        char *result = strpbrk(str, "s");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 's');
    }
    {
        char str[] = "prefixsuffix";
        char *result = strpbrk(str, "pre");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'p');
    }
    {
        char str[] = "prefixsuffix";
        char *result = strpbrk(str, "fix");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'f');
    }
    {
        char str[] = "ABC";
        char *result = strpbrk(str, "ABC");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'A');
    }
    {
        char str[] = "ABC";
        char *result = strpbrk(str, "A");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "ABC";
        char *result = strpbrk(str, "B");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'B');
    }
    {
        char str[] = "ABC";
        char *result = strpbrk(str, "C");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'C');
    }
    {
        char str[] = "ABC";
        char *result = strpbrk(str, "AB");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'A');
    }
    {
        char str[] = "ABC";
        char *result = strpbrk(str, "AC");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'A');
    }
    {
        char str[] = "ABC";
        char *result = strpbrk(str, "BC");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'B');
    }
    {
        char str[] = "0123456789";
        char *result = strpbrk(str, "0123456789");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == '0');
    }
    {
        char str[] = "0123456789";
        char *result = strpbrk(str, "0");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "0123456789";
        char *result = strpbrk(str, "5");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == '5');
    }
    {
        char str[] = "0123456789";
        char *result = strpbrk(str, "9");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == '9');
    }
    {
        char str[] = "0123456789";
        char *result = strpbrk(str, "a");
        EXPECT_NULL(result);
    }
    {
        char str[] = "abcdefghijklmnopqrstuvwxyz";
        char *result = strpbrk(str, "a");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "abcdefghijklmnopqrstuvwxyz";
        char *result = strpbrk(str, "z");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'z');
    }
    {
        char str[] = "abcdefghijklmnopqrstuvwxyz";
        char *result = strpbrk(str, "m");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'm');
    }
    {
        char str[] = "abcdefghijklmnopqrstuvwxyz";
        char *result = strpbrk(str, "0123456789");
        EXPECT_NULL(result);
    }
    {
        char str[] = "a";
        char *result = strpbrk(str, "a");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "a";
        char *result = strpbrk(str, "b");
        EXPECT_NULL(result);
    }
    {
        char str[] = "a";
        char *result = strpbrk(str, "ab");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "ab";
        char *result = strpbrk(str, "a");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "ab";
        char *result = strpbrk(str, "b");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'b');
    }
    {
        char str[] = "ab";
        char *result = strpbrk(str, "ab");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'a');
    }
    {
        char str[] = "ab";
        char *result = strpbrk(str, "c");
        EXPECT_NULL(result);
    }
    {
        char str[] = "xyz";
        char *result = strpbrk(str, "xyz");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'x');
    }
    {
        char str[] = "xyz";
        char *result = strpbrk(str, "x");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "xyz";
        char *result = strpbrk(str, "y");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'y');
    }
    {
        char str[] = "xyz";
        char *result = strpbrk(str, "z");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'z');
    }
    {
        char str[] = "xyz";
        char *result = strpbrk(str, "xy");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'x');
    }
    {
        char str[] = "xyz";
        char *result = strpbrk(str, "xz");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'x');
    }
    {
        char str[] = "xyz";
        char *result = strpbrk(str, "yz");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'y');
    }
    {
        char str[] = "xyz";
        char *result = strpbrk(str, "w");
        EXPECT_NULL(result);
    }
    {
        char str[] = "lllll";
        char *result = strpbrk(str, "l");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "lllll";
        char *result = strpbrk(str, "m");
        EXPECT_NULL(result);
    }
    {
        char str[] = "lllll";
        char *result = strpbrk(str, "lm");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'l');
    }
    {
        char str[] = "abcabc";
        char *result = strpbrk(str, "a");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "abcabc";
        char *result = strpbrk(str, "b");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'b');
    }
    {
        char str[] = "abcabc";
        char *result = strpbrk(str, "c");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'c');
    }
    {
        char str[] = "abcabc";
        char *result = strpbrk(str, "d");
        EXPECT_NULL(result);
    }
    {
        char str[] = "111222333";
        char *result = strpbrk(str, "1");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "111222333";
        char *result = strpbrk(str, "2");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == '2');
    }
    {
        char str[] = "111222333";
        char *result = strpbrk(str, "3");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == '3');
    }
    {
        char str[] = "111222333";
        char *result = strpbrk(str, "4");
        EXPECT_NULL(result);
    }
    {
        char str[] = "ABCDEF";
        char *result = strpbrk(str, "A");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "ABCDEF";
        char *result = strpbrk(str, "F");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'F');
    }
    {
        char str[] = "ABCDEF";
        char *result = strpbrk(str, "G");
        EXPECT_NULL(result);
    }
    {
        char str[] = "ABCDEF";
        char *result = strpbrk(str, "ABC");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'A');
    }
    {
        char str[] = "ABCDEF";
        char *result = strpbrk(str, "DEF");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'D');
    }
    {
        char str[] = "   \t\n  ";
        char *result = strpbrk(str, "a");
        EXPECT_NULL(result);
    }
    {
        char str[] = "   \t\n  ";
        char *result = strpbrk(str, " ");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == ' ');
    }
    {
        char str[] = "   \t\n  ";
        char *result = strpbrk(str, "\t");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == '\t');
    }
    {
        char str[] = "   \t\n  ";
        char *result = strpbrk(str, "\n");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == '\n');
    }
    {
        char str[] = "ababab";
        char *result = strpbrk(str, "a");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "ababab";
        char *result = strpbrk(str, "b");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'b');
    }
    {
        char str[] = "ababab";
        char *result = strpbrk(str, "c");
        EXPECT_NULL(result);
    }
    {
        char str[] = "xyzxyz";
        char *result = strpbrk(str, "x");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "xyzxyz";
        char *result = strpbrk(str, "y");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'y');
    }
    {
        char str[] = "xyzxyz";
        char *result = strpbrk(str, "z");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'z');
    }
    {
        char str[] = "xyzxyz";
        char *result = strpbrk(str, "w");
        EXPECT_NULL(result);
    }
    {
        char str[] = "abcdef";
        char *result = strpbrk(str, "abcdef");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'a');
    }
    {
        char str[] = "abcdef";
        char *result = strpbrk(str, "fedcba");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'a');
    }
    {
        char str[] = "abcdef";
        char *result = strpbrk(str, "abc");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'a');
    }
    {
        char str[] = "abcdef";
        char *result = strpbrk(str, "def");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'd');
    }
    {
        char str[] = "abcdef";
        char *result = strpbrk(str, "a");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "abcdef";
        char *result = strpbrk(str, "f");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'f');
    }
    {
        char str[] = "aabbccdd";
        char *result = strpbrk(str, "abcd");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'a');
    }
    {
        char str[] = "aabbccdd";
        char *result = strpbrk(str, "ab");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'a');
    }
    {
        char str[] = "aabbccdd";
        char *result = strpbrk(str, "cd");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'c');
    }
    {
        char str[] = "aabbccdd";
        char *result = strpbrk(str, "a");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "aabbccdd";
        char *result = strpbrk(str, "b");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'b');
    }
    {
        char str[] = "1234567890";
        char *result = strpbrk(str, "0123456789");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == '1');
    }
    {
        char str[] = "1234567890";
        char *result = strpbrk(str, "12345");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == '1');
    }
    {
        char str[] = "1234567890";
        char *result = strpbrk(str, "67890");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == '6');
    }
    {
        char str[] = "1234567890";
        char *result = strpbrk(str, "1");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "1234567890";
        char *result = strpbrk(str, "0");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == '0');
    }
    {
        char str[] = "ABCabc";
        char *result = strpbrk(str, "ABC");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'A');
    }
    {
        char str[] = "ABCabc";
        char *result = strpbrk(str, "abc");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'a');
    }
    {
        char str[] = "ABCabc";
        char *result = strpbrk(str, "ABCabc");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'A');
    }
    {
        char str[] = "ABCabc";
        char *result = strpbrk(str, "AaBbCc");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'A');
    }
    {
        char str[] = "   ";
        char *result = strpbrk(str, " ");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "   ";
        char *result = strpbrk(str, " \t");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "   ";
        char *result = strpbrk(str, "a");
        EXPECT_NULL(result);
    }
    {
        char str[] = "\t\t\t";
        char *result = strpbrk(str, "\t");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "\t\t\t";
        char *result = strpbrk(str, "\t\n");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "\t\t\t";
        char *result = strpbrk(str, " ");
        EXPECT_NULL(result);
    }
    {
        char str[] = "test123";
        char *result = strpbrk(str, "test");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 't');
    }
    {
        char str[] = "test123";
        char *result = strpbrk(str, "123");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == '1');
    }
    {
        char str[] = "test123";
        char *result = strpbrk(str, "test123");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 't');
    }
    {
        char str[] = "123test";
        char *result = strpbrk(str, "123");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == '1');
    }
    {
        char str[] = "123test";
        char *result = strpbrk(str, "test");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 't');
    }
    {
        char str[] = "123test";
        char *result = strpbrk(str, "123test");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == '1');
    }
    {
        char str[] = "hello,world";
        char *result = strpbrk(str, ",");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == ',');
    }
    {
        char str[] = "hello,world";
        char *result = strpbrk(str, ",.");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == ',');
    }
    {
        char str[] = "path/to/file";
        char *result = strpbrk(str, "/");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == '/');
    }
    {
        char str[] = "path/to/file";
        char *result = strpbrk(str, "/\\");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == '/');
    }
    {
        char str[] = "a1b2c3";
        char *result = strpbrk(str, "abc");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'a');
    }
    {
        char str[] = "a1b2c3";
        char *result = strpbrk(str, "123");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == '1');
    }
    {
        char str[] = "a1b2c3";
        char *result = strpbrk(str, "a1b2c3");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'a');
    }
    {
        char str[] = "1a2b3c";
        char *result = strpbrk(str, "123");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == '1');
    }
    {
        char str[] = "1a2b3c";
        char *result = strpbrk(str, "abc");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'a');
    }
    {
        char str[] = "1a2b3c";
        char *result = strpbrk(str, "1a2b3c");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == '1');
    }
    {
        char str[] = "!!!";
        char *result = strpbrk(str, "!");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "!!!";
        char *result = strpbrk(str, "!@");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "!!!";
        char *result = strpbrk(str, "@");
        EXPECT_NULL(result);
    }
    {
        char str[] = "mississippi";
        char *result = strpbrk(str, "mis");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'm');
    }
    {
        char str[] = "mississippi";
        char *result = strpbrk(str, "m");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
    }
    {
        char str[] = "mississippi";
        char *result = strpbrk(str, "i");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'i');
    }
    {
        char str[] = "mississippi";
        char *result = strpbrk(str, "s");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 's');
    }
    {
        char str[] = "mississippi";
        char *result = strpbrk(str, "p");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'p');
    }
    {
        char str[] = "programming";
        char *result = strpbrk(str, "prog");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'p');
    }
    {
        char str[] = "programming";
        char *result = strpbrk(str, "gram");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'r');
    }
    {
        char str[] = "programming";
        char *result = strpbrk(str, "programming");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'p');
    }
    {
        char str[] = "programming";
        char *result = strpbrk(str, "pro");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(result == str);
        EXPECT_TRUE(*result == 'p');
    }
    {
        char str[] = "programming";
        char *result = strpbrk(str, "ing");
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*result == 'g');
    }
}
