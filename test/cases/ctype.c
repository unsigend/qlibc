#include <ctype.h>
#include <stdio.h>
#include <utest.h>

#define F_CNTRL (1u << 0)
#define F_PRINT (1u << 1)
#define F_SPACE (1u << 2)
#define F_BLANK (1u << 3)
#define F_GRAPH (1u << 4)
#define F_PUNCT (1u << 5)
#define F_ALNUM (1u << 6)
#define F_ALPHA (1u << 7)
#define F_UPPER (1u << 8)
#define F_LOWER (1u << 9)
#define F_DIGIT (1u << 10)
#define F_XDIGIT (1u << 11)

static unsigned ascii_flags(int c)
{
    unsigned f = 0;
    int digit = c >= '0' && c <= '9';
    int upper = c >= 'A' && c <= 'Z';
    int lower = c >= 'a' && c <= 'z';
    int alpha = upper || lower;
    int xdigit = digit || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');

    if ((c >= 0 && c <= 0x1f) || c == 0x7f)
        f |= F_CNTRL;
    if (c >= 0x20 && c <= 0x7e)
        f |= F_PRINT;
    if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' ||
        c == ' ')
        f |= F_SPACE;
    if (c == '\t' || c == ' ')
        f |= F_BLANK;
    if (c >= 0x21 && c <= 0x7e)
        f |= F_GRAPH;
    if (digit)
        f |= F_DIGIT;
    if (xdigit)
        f |= F_XDIGIT;
    if (upper)
        f |= F_UPPER;
    if (lower)
        f |= F_LOWER;
    if (alpha)
        f |= F_ALPHA;
    if (alpha || digit)
        f |= F_ALNUM;
    if ((f & F_GRAPH) && !(f & F_ALNUM))
        f |= F_PUNCT;
    return f;
}

#define CHECK_ASCII(fn, bit)                                                   \
    do {                                                                       \
        int c;                                                                 \
        EXPECT_FALSE(fn(EOF));                                                 \
        for (c = 0; c < 128; c++)                                              \
            EXPECT_EQ_INT(!!(fn)(c), !!(ascii_flags(c) & (bit)));              \
    } while (0)

UTEST_CASE(isalnum) { CHECK_ASCII(isalnum, F_ALNUM); }
UTEST_CASE(isalpha) { CHECK_ASCII(isalpha, F_ALPHA); }
UTEST_CASE(isblank) { CHECK_ASCII(isblank, F_BLANK); }
UTEST_CASE(iscntrl) { CHECK_ASCII(iscntrl, F_CNTRL); }
UTEST_CASE(isdigit) { CHECK_ASCII(isdigit, F_DIGIT); }
UTEST_CASE(isgraph) { CHECK_ASCII(isgraph, F_GRAPH); }
UTEST_CASE(islower) { CHECK_ASCII(islower, F_LOWER); }
UTEST_CASE(isprint) { CHECK_ASCII(isprint, F_PRINT); }
UTEST_CASE(ispunct) { CHECK_ASCII(ispunct, F_PUNCT); }
UTEST_CASE(isspace) { CHECK_ASCII(isspace, F_SPACE); }
UTEST_CASE(isupper) { CHECK_ASCII(isupper, F_UPPER); }
UTEST_CASE(isxdigit) { CHECK_ASCII(isxdigit, F_XDIGIT); }

UTEST_CASE(tolower)
{
    int c;

    EXPECT_EQ_INT(tolower(EOF), EOF);
    for (c = 0; c < 128; c++) {
        int expect = (c >= 'A' && c <= 'Z') ? c - 'A' + 'a' : c;
        EXPECT_EQ_INT(tolower(c), expect);
    }
}

UTEST_CASE(toupper)
{
    int c;

    EXPECT_EQ_INT(toupper(EOF), EOF);
    for (c = 0; c < 128; c++) {
        int expect = (c >= 'a' && c <= 'z') ? c - 'a' + 'A' : c;
        EXPECT_EQ_INT(toupper(c), expect);
    }
}

UTEST_SUITE(ctype)
{
    UTEST_RUNCASE(isalnum);
    UTEST_RUNCASE(isalpha);
    UTEST_RUNCASE(isblank);
    UTEST_RUNCASE(iscntrl);
    UTEST_RUNCASE(isdigit);
    UTEST_RUNCASE(isgraph);
    UTEST_RUNCASE(islower);
    UTEST_RUNCASE(isprint);
    UTEST_RUNCASE(ispunct);
    UTEST_RUNCASE(isspace);
    UTEST_RUNCASE(isupper);
    UTEST_RUNCASE(isxdigit);
    UTEST_RUNCASE(tolower);
    UTEST_RUNCASE(toupper);
}
