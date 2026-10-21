#include <stdio.h>
#include <utest.h>

UTEST_CASE(in_c)
{
    char buf[16];
    char ch;
    int n, d;

    n = sscanf("a", "%c", &ch);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT((unsigned char)ch, 'a');

    n = sscanf("A", "%c", &ch);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT((unsigned char)ch, 'A');

    n = sscanf("0", "%c", &ch);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT((unsigned char)ch, '0');

    n = sscanf(" ", "%c", &ch);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT((unsigned char)ch, ' ');

    n = sscanf("\n", "%c", &ch);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT((unsigned char)ch, '\n');

    n = sscanf("\t", "%c", &ch);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT((unsigned char)ch, '\t');

    n = sscanf("", "%c", &ch);
    EXPECT_EQ_INT(n, -1);

    n = sscanf("ab", "%c%c", &ch, buf);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_INT((unsigned char)ch, 'a');
    EXPECT_EQ_INT((unsigned char)buf[0], 'b');

    n = sscanf("abc", "%c%c%c", &ch, buf, buf + 1);
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_INT((unsigned char)ch, 'a');
    EXPECT_EQ_INT((unsigned char)buf[0], 'b');
    EXPECT_EQ_INT((unsigned char)buf[1], 'c');

    n = sscanf("xay", "x%cy", &ch);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT((unsigned char)ch, 'a');

    n = sscanf("a\n", "%c%c", &ch, buf);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_INT((unsigned char)ch, 'a');
    EXPECT_EQ_INT((unsigned char)buf[0], '\n');

    n = sscanf("  x", "%c", &ch);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT((unsigned char)ch, ' ');

    n = sscanf("xy", "%1c", &ch);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT((unsigned char)ch, 'x');

    n = sscanf("xyz", "%2c", buf);
    buf[2] = '\0';
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(buf, "xy");

    n = sscanf("hello", "%3c", buf);
    buf[3] = '\0';
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(buf, "hel");

    n = sscanf("ab", "%5c", buf);
    buf[2] = '\0';
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_STR(buf, "ab");

    n = sscanf("x", "%c", &ch);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT((unsigned char)ch, 'x');

    n = sscanf("\x7f", "%c", &ch);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT((unsigned char)ch, 0x7f);

    n = sscanf("\r", "%c", &ch);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT((unsigned char)ch, '\r');

    n = sscanf("a b", "%c %c", &ch, buf);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_INT((unsigned char)ch, 'a');
    EXPECT_EQ_INT((unsigned char)buf[0], 'b');

    n = sscanf("a\tb", "%c%c", &ch, buf);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_INT((unsigned char)ch, 'a');
    EXPECT_EQ_INT((unsigned char)buf[0], '\t');

    n = sscanf("xy", "%c%c", &ch, buf);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_INT((unsigned char)ch, 'x');
    EXPECT_EQ_INT((unsigned char)buf[0], 'y');

    n = sscanf("x", "x%c", &ch);
    EXPECT_EQ_INT(n, -1);

    n = sscanf("ay", "%cy", &ch);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT((unsigned char)ch, 'a');

    n = sscanf("1 42 x", "%c %d %c", &ch, &d, buf);
    EXPECT_EQ_INT(n, 3);
    EXPECT_EQ_INT((unsigned char)ch, '1');
    EXPECT_EQ_INT(d, 42);
    EXPECT_EQ_INT((unsigned char)buf[0], 'x');

    n = sscanf("1 42", "%c %d", &ch, &d);
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_INT((unsigned char)ch, '1');
    EXPECT_EQ_INT(d, 42);

    n = sscanf("1234", "%2c%2c", buf, buf + 2);
    buf[4] = '\0';
    EXPECT_EQ_INT(n, 2);
    EXPECT_EQ_STR(buf, "1234");

    n = sscanf("ab", "%*c%c", &ch);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT((unsigned char)ch, 'b');

    n = sscanf("xyz", "%*c%*c%c", &ch);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT((unsigned char)ch, 'z');

    n = sscanf("abcd", "%*2c%c", &ch);
    EXPECT_EQ_INT(n, 1);
    EXPECT_EQ_INT((unsigned char)ch, 'c');
}
