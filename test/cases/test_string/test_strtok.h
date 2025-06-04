#include <string.h>
#include <utest.h>

UTEST_TEST_CASE(strtok) {
    char str1[] = "Hello,World";
    const char *delim1 = ",";
    char *token1 = strtok(str1, delim1);
    EXPECT_EQUAL_STRING(token1, "Hello");
    token1 = strtok(NULL, delim1);
    EXPECT_EQUAL_STRING(token1, "World");
    token1 = strtok(NULL, delim1);
    EXPECT_TRUE(token1 == NULL);

    char str2[] = "Hello,World;Test";
    const char *delim2 = ",;";
    char *token2 = strtok(str2, delim2);
    EXPECT_EQUAL_STRING(token2, "Hello");
    token2 = strtok(NULL, delim2);
    EXPECT_EQUAL_STRING(token2, "World");
    token2 = strtok(NULL, delim2);
    EXPECT_EQUAL_STRING(token2, "Test");
    token2 = strtok(NULL, delim2);
    EXPECT_TRUE(token2 == NULL);

    char str3[] = "Hello,,,World";
    const char *delim3 = ",";
    char *token3 = strtok(str3, delim3);
    EXPECT_EQUAL_STRING(token3, "Hello");
    token3 = strtok(NULL, delim3);
    EXPECT_EQUAL_STRING(token3, "World");
    token3 = strtok(NULL, delim3);
    EXPECT_TRUE(token3 == NULL);

    char str4[] = ",Hello,World";
    const char *delim4 = ",";
    char *token4 = strtok(str4, delim4);
    EXPECT_EQUAL_STRING(token4, "Hello");
    token4 = strtok(NULL, delim4);
    EXPECT_EQUAL_STRING(token4, "World");
    token4 = strtok(NULL, delim4);
    EXPECT_TRUE(token4 == NULL);

    char str5[] = "Hello,World,";
    const char *delim5 = ",";
    char *token5 = strtok(str5, delim5);
    EXPECT_EQUAL_STRING(token5, "Hello");
    token5 = strtok(NULL, delim5);
    EXPECT_EQUAL_STRING(token5, "World");
    token5 = strtok(NULL, delim5);
    EXPECT_TRUE(token5 == NULL);

    char str6[] = "";
    const char *delim6 = ",";
    char *token6 = strtok(str6, delim6);
    EXPECT_TRUE(token6 == NULL);

    char str7[] = ",,,";
    const char *delim7 = ",";
    char *token7 = strtok(str7, delim7);
    EXPECT_TRUE(token7 == NULL);

    char str8[] = "Hello,World;Test:End";
    const char *delim8 = ",;:";
    char *token8 = strtok(str8, delim8);
    EXPECT_EQUAL_STRING(token8, "Hello");
    token8 = strtok(NULL, delim8);
    EXPECT_EQUAL_STRING(token8, "World");
    token8 = strtok(NULL, delim8);
    EXPECT_EQUAL_STRING(token8, "Test");
    token8 = strtok(NULL, delim8);
    EXPECT_EQUAL_STRING(token8, "End");
    token8 = strtok(NULL, delim8);
    EXPECT_TRUE(token8 == NULL);

    char str9[] = "Hello World\tTest";
    const char *delim9 = " \t";
    char *token9 = strtok(str9, delim9);
    EXPECT_EQUAL_STRING(token9, "Hello");
    token9 = strtok(NULL, delim9);
    EXPECT_EQUAL_STRING(token9, "World");
    token9 = strtok(NULL, delim9);
    EXPECT_EQUAL_STRING(token9, "Test");
    token9 = strtok(NULL, delim9);
    EXPECT_TRUE(token9 == NULL);

    char str10[] = "HelloWorld";
    const char *delim10 = ",";
    char *token10 = strtok(str10, delim10);
    EXPECT_EQUAL_STRING(token10, "HelloWorld");
    token10 = strtok(NULL, delim10);
    EXPECT_TRUE(token10 == NULL);

    char str11[] = "Hello, World; Test:End";
    const char *delim11 = ",;: ";
    char *token11 = strtok(str11, delim11);
    EXPECT_EQUAL_STRING(token11, "Hello");
    token11 = strtok(NULL, delim11);
    EXPECT_EQUAL_STRING(token11, "World");
    token11 = strtok(NULL, delim11);
    EXPECT_EQUAL_STRING(token11, "Test");
    token11 = strtok(NULL, delim11);
    EXPECT_EQUAL_STRING(token11, "End");
    token11 = strtok(NULL, delim11);
    EXPECT_TRUE(token11 == NULL);

    char str12[] = "Hello*World#Test@End";
    const char *delim12 = "*#@";
    char *token12 = strtok(str12, delim12);
    EXPECT_EQUAL_STRING(token12, "Hello");
    token12 = strtok(NULL, delim12);
    EXPECT_EQUAL_STRING(token12, "World");
    token12 = strtok(NULL, delim12);
    EXPECT_EQUAL_STRING(token12, "Test");
    token12 = strtok(NULL, delim12);
    EXPECT_EQUAL_STRING(token12, "End");
    token12 = strtok(NULL, delim12);
    EXPECT_TRUE(token12 == NULL);

    char str13[] = "123,456;789:0";
    const char *delim13 = ",;:";
    char *token13 = strtok(str13, delim13);
    EXPECT_EQUAL_STRING(token13, "123");
    token13 = strtok(NULL, delim13);
    EXPECT_EQUAL_STRING(token13, "456");
    token13 = strtok(NULL, delim13);
    EXPECT_EQUAL_STRING(token13, "789");
    token13 = strtok(NULL, delim13);
    EXPECT_EQUAL_STRING(token13, "0");
    token13 = strtok(NULL, delim13);
    EXPECT_TRUE(token13 == NULL);

    char str14[] = "Hello,Hello,World,World";
    const char *delim14 = ",";
    char *token14 = strtok(str14, delim14);
    EXPECT_EQUAL_STRING(token14, "Hello");
    token14 = strtok(NULL, delim14);
    EXPECT_EQUAL_STRING(token14, "Hello");
    token14 = strtok(NULL, delim14);
    EXPECT_EQUAL_STRING(token14, "World");
    token14 = strtok(NULL, delim14);
    EXPECT_EQUAL_STRING(token14, "World");
    token14 = strtok(NULL, delim14);
    EXPECT_TRUE(token14 == NULL);

    char str15[] = "a,b,c,d";
    const char *delim15 = ",";
    char *token15 = strtok(str15, delim15);
    EXPECT_EQUAL_STRING(token15, "a");
    token15 = strtok(NULL, delim15);
    EXPECT_EQUAL_STRING(token15, "b");
    token15 = strtok(NULL, delim15);
    EXPECT_EQUAL_STRING(token15, "c");
    token15 = strtok(NULL, delim15);
    EXPECT_EQUAL_STRING(token15, "d");
    token15 = strtok(NULL, delim15);
    EXPECT_TRUE(token15 == NULL);

    char *token16 = strtok(NULL, ",");
    EXPECT_TRUE(token16 == NULL);

    char str17[] = "Hello\0World,Test";
    const char *delim17 = ",";
    char *token17 = strtok(str17, delim17);
    EXPECT_EQUAL_STRING(token17, "Hello");
    token17 = strtok(NULL, delim17);
    EXPECT_TRUE(token17 == NULL);

    char str18[] = "This is a very long string that contains multiple delimiters "
                   "and should be properly tokenized into smaller pieces for "
                   "testing the function's ability to handle long input strings";
    const char *delim18 = " ,";
    char *token18 = strtok(str18, delim18);
    EXPECT_EQUAL_STRING(token18, "This");
    token18 = strtok(NULL, delim18);
    EXPECT_EQUAL_STRING(token18, "is");
    token18 = strtok(NULL, delim18);
    EXPECT_EQUAL_STRING(token18, "a");
    // Continue tokenization
    while ((token18 = strtok(NULL, delim18)) != NULL) {
        EXPECT_TRUE(token18 != NULL);
    }

    char str20[] = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    const char *delim20 = "!@#$%^&*()";
    char *token20 = strtok(str20, delim20);
    EXPECT_EQUAL_STRING(token20, "\"");
    token20 = strtok(NULL, delim20);
    EXPECT_EQUAL_STRING(token20, "'");
    token20 = strtok(NULL, delim20);
    EXPECT_TRUE(token20 != NULL);
    EXPECT_EQUAL_STRING(token20, "+,-./0123456789:;<=>?");
    token20 = strtok(NULL, delim20);
    EXPECT_EQUAL_STRING(token20, "ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]");
    token20 = strtok(NULL, delim20);
    EXPECT_EQUAL_STRING(token20, "_`abcdefghijklmnopqrstuvwxyz{|}~");
    token20 = strtok(NULL, delim20);
    EXPECT_TRUE(token20 == NULL);

    char str21[] = ",,Hello,,,World,,,Test,,,";
    const char *delim21 = ",";
    char *token21 = strtok(str21, delim21);
    EXPECT_EQUAL_STRING(token21, "Hello");
    token21 = strtok(NULL, delim21);
    EXPECT_EQUAL_STRING(token21, "World");
    token21 = strtok(NULL, delim21);
    EXPECT_EQUAL_STRING(token21, "Test");
    token21 = strtok(NULL, delim21);
    EXPECT_TRUE(token21 == NULL);

    char str22[] = "Hello123,World456,Test789,End000";
    const char *delim22 = ",";
    char *token22 = strtok(str22, delim22);
    EXPECT_EQUAL_STRING(token22, "Hello123");
    token22 = strtok(NULL, delim22);
    EXPECT_EQUAL_STRING(token22, "World456");
    token22 = strtok(NULL, delim22);
    EXPECT_EQUAL_STRING(token22, "Test789");
    token22 = strtok(NULL, delim22);
    EXPECT_EQUAL_STRING(token22, "End000");
    token22 = strtok(NULL, delim22);
    EXPECT_TRUE(token22 == NULL);

    char str23[] = "a,";
    const char *delim23 = ",";
    char *token23 = strtok(str23, delim23);
    EXPECT_EQUAL_STRING(token23, "a");
    token23 = strtok(NULL, delim23);
    EXPECT_TRUE(token23 == NULL);

    char str24[] = "Hello,World;Test:End,Again;More:Final";
    const char *delim24 = ",;:";
    char *token24 = strtok(str24, delim24);
    EXPECT_EQUAL_STRING(token24, "Hello");
    token24 = strtok(NULL, delim24);
    EXPECT_EQUAL_STRING(token24, "World");
    token24 = strtok(NULL, delim24);
    EXPECT_EQUAL_STRING(token24, "Test");
    token24 = strtok(NULL, delim24);
    EXPECT_EQUAL_STRING(token24, "End");
    token24 = strtok(NULL, delim24);
    EXPECT_EQUAL_STRING(token24, "Again");
    token24 = strtok(NULL, delim24);
    EXPECT_EQUAL_STRING(token24, "More");
    token24 = strtok(NULL, delim24);
    EXPECT_EQUAL_STRING(token24, "Final");
    token24 = strtok(NULL, delim24);
    EXPECT_TRUE(token24 == NULL);

    char str25[] = ",Hello,World,";
    const char *delim25 = ",";
    char *token25 = strtok(str25, delim25);
    EXPECT_EQUAL_STRING(token25, "Hello");
    token25 = strtok(NULL, delim25);
    EXPECT_EQUAL_STRING(token25, "World");
    token25 = strtok(NULL, delim25);
    EXPECT_TRUE(token25 == NULL);
}

