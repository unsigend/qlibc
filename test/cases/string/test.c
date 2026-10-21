#include <utest.h>

extern UTEST_CASE(memchr);
extern UTEST_CASE(memcmp);
extern UTEST_CASE(memcpy);
extern UTEST_CASE(memmove);
extern UTEST_CASE(memset);
extern UTEST_CASE(strcat);
extern UTEST_CASE(strchr);
extern UTEST_CASE(strcmp);
extern UTEST_CASE(strcpy);
extern UTEST_CASE(strcspn);
extern UTEST_CASE(strdup);
extern UTEST_CASE(strlen);
extern UTEST_CASE(strncat);
extern UTEST_CASE(strncmp);
extern UTEST_CASE(strncpy);
extern UTEST_CASE(strpbrk);
extern UTEST_CASE(strrchr);
extern UTEST_CASE(strspn);
extern UTEST_CASE(strstr);
extern UTEST_CASE(strtok);

UTEST_SUITE(string)
{
    UTEST_RUNCASE(memchr);
    UTEST_RUNCASE(memcmp);
    UTEST_RUNCASE(memcpy);
    UTEST_RUNCASE(memmove);
    UTEST_RUNCASE(memset);
    UTEST_RUNCASE(strcat);
    UTEST_RUNCASE(strchr);
    UTEST_RUNCASE(strcmp);
    UTEST_RUNCASE(strcpy);
    UTEST_RUNCASE(strcspn);
    UTEST_RUNCASE(strdup);
    UTEST_RUNCASE(strlen);
    UTEST_RUNCASE(strncat);
    UTEST_RUNCASE(strncmp);
    UTEST_RUNCASE(strncpy);
    UTEST_RUNCASE(strpbrk);
    UTEST_RUNCASE(strrchr);
    UTEST_RUNCASE(strspn);
    UTEST_RUNCASE(strstr);
    UTEST_RUNCASE(strtok);
}
