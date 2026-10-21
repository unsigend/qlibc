#include <stdlib.h>
#include <utest.h>

static int cmp_int(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y)
        return -1;
    if (x > y)
        return 1;
    return 0;
}

static int cmp_char(const void *a, const void *b)
{
    char x = *(const char *)a;
    char y = *(const char *)b;

    if (x < y)
        return -1;
    if (x > y)
        return 1;
    return 0;
}

static int cmp_long(const void *a, const void *b)
{
    long x = *(const long *)a;
    long y = *(const long *)b;

    if (x < y)
        return -1;
    if (x > y)
        return 1;
    return 0;
}

struct rec {
    int id;
    int age;
};

static int cmp_id(const void *a, const void *b)
{
    int x = ((const struct rec *)a)->id;
    int y = ((const struct rec *)b)->id;

    if (x < y)
        return -1;
    if (x > y)
        return 1;
    return 0;
}

static int cmp_age(const void *a, const void *b)
{
    int x = ((const struct rec *)a)->age;
    int y = ((const struct rec *)b)->age;

    if (x < y)
        return -1;
    if (x > y)
        return 1;
    return 0;
}

UTEST_CASE(bsearch)
{
    int *p;
    char *cp;
    long *lp;
    struct rec *rp;
    int key;
    char ckey;
    long lkey;
    struct rec rkey;

    {
        int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        key = 5;
        p = bsearch(&key, arr, 10, sizeof(int), cmp_int);
        EXPECT_EQ_PTR(p, arr + 4);
        EXPECT_EQ_INT(*p, 5);

        key = 1;
        p = bsearch(&key, arr, 10, sizeof(int), cmp_int);
        EXPECT_EQ_PTR(p, arr);

        key = 10;
        p = bsearch(&key, arr, 10, sizeof(int), cmp_int);
        EXPECT_EQ_PTR(p, arr + 9);

        key = 7;
        p = bsearch(&key, arr, 10, sizeof(int), cmp_int);
        EXPECT_EQ_PTR(p, arr + 6);

        key = 0;
        EXPECT_NULL(bsearch(&key, arr, 10, sizeof(int), cmp_int));
        key = 11;
        EXPECT_NULL(bsearch(&key, arr, 10, sizeof(int), cmp_int));
    }

    {
        int arr[] = {5};

        key = 5;
        p = bsearch(&key, arr, 1, sizeof(int), cmp_int);
        EXPECT_EQ_PTR(p, arr);

        key = 3;
        EXPECT_NULL(bsearch(&key, arr, 1, sizeof(int), cmp_int));
        key = 5;
        EXPECT_NULL(bsearch(&key, arr, 0, sizeof(int), cmp_int));
    }

    {
        int arr[] = {1, 3, 5, 7, 9};

        key = 5;
        p = bsearch(&key, arr, 5, sizeof(int), cmp_int);
        EXPECT_EQ_PTR(p, arr + 2);

        key = 4;
        EXPECT_NULL(bsearch(&key, arr, 5, sizeof(int), cmp_int));
        key = 1;
        EXPECT_EQ_PTR(bsearch(&key, arr, 5, sizeof(int), cmp_int), arr);
        key = 9;
        EXPECT_EQ_PTR(bsearch(&key, arr, 5, sizeof(int), cmp_int), arr + 4);
    }

    {
        int arr[] = {-10, -5, 0, 5, 10};

        key = 0;
        EXPECT_EQ_PTR(bsearch(&key, arr, 5, sizeof(int), cmp_int), arr + 2);
        key = -10;
        EXPECT_EQ_PTR(bsearch(&key, arr, 5, sizeof(int), cmp_int), arr);
        key = 10;
        EXPECT_EQ_PTR(bsearch(&key, arr, 5, sizeof(int), cmp_int), arr + 4);
        key = -7;
        EXPECT_NULL(bsearch(&key, arr, 5, sizeof(int), cmp_int));
    }

    {
        int arr[] = {2, 2, 2, 2, 2};

        key = 2;
        p = bsearch(&key, arr, 5, sizeof(int), cmp_int);
        EXPECT_NOTNULL(p);
        EXPECT_EQ_INT(*p, 2);
        EXPECT_TRUE(p >= arr && p < arr + 5);
    }

    {
        int arr[] = {1, 2, 2, 2, 5};

        key = 2;
        p = bsearch(&key, arr, 5, sizeof(int), cmp_int);
        EXPECT_NOTNULL(p);
        EXPECT_EQ_INT(*p, 2);
        EXPECT_TRUE(p >= arr + 1 && p <= arr + 3);
    }

    {
        char arr[] = {'a', 'b', 'c', 'd', 'e'};

        ckey = 'c';
        cp = bsearch(&ckey, arr, 5, sizeof(char), cmp_char);
        EXPECT_EQ_PTR(cp, arr + 2);
        ckey = 'a';
        EXPECT_EQ_PTR(bsearch(&ckey, arr, 5, sizeof(char), cmp_char), arr);
        ckey = 'e';
        EXPECT_EQ_PTR(bsearch(&ckey, arr, 5, sizeof(char), cmp_char), arr + 4);
        ckey = 'z';
        EXPECT_NULL(bsearch(&ckey, arr, 5, sizeof(char), cmp_char));
    }

    {
        long arr[] = {100L, 200L, 300L, 400L, 500L};

        lkey = 300L;
        lp = bsearch(&lkey, arr, 5, sizeof(long), cmp_long);
        EXPECT_EQ_PTR(lp, arr + 2);
        lkey = 150L;
        EXPECT_NULL(bsearch(&lkey, arr, 5, sizeof(long), cmp_long));
    }

    {
        struct rec people[] = {
            {1, 25}, {2, 30}, {3, 35}, {4, 40}, {5, 45},
        };

        rkey.id = 3;
        rkey.age = 0;
        rp = bsearch(&rkey, people, 5, sizeof(people[0]), cmp_id);
        EXPECT_EQ_PTR(rp, people + 2);
        EXPECT_EQ_INT(rp->id, 3);

        rkey.id = 6;
        EXPECT_NULL(bsearch(&rkey, people, 5, sizeof(people[0]), cmp_id));

        rkey.id = 0;
        rkey.age = 35;
        rp = bsearch(&rkey, people, 5, sizeof(people[0]), cmp_age);
        EXPECT_EQ_PTR(rp, people + 2);
        EXPECT_EQ_INT(rp->age, 35);

        rkey.age = 20;
        EXPECT_NULL(bsearch(&rkey, people, 5, sizeof(people[0]), cmp_age));
    }

    {
        int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

        key = 50;
        EXPECT_EQ_PTR(bsearch(&key, arr, 10, sizeof(int), cmp_int), arr + 4);
        key = 55;
        EXPECT_NULL(bsearch(&key, arr, 10, sizeof(int), cmp_int));
    }

    {
        int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

        key = 8;
        EXPECT_EQ_PTR(bsearch(&key, arr, 15, sizeof(int), cmp_int), arr + 7);
        key = 16;
        EXPECT_NULL(bsearch(&key, arr, 15, sizeof(int), cmp_int));
    }

    {
        int arr[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};

        key = 11;
        EXPECT_EQ_PTR(bsearch(&key, arr, 10, sizeof(int), cmp_int), arr + 5);
        key = 12;
        EXPECT_NULL(bsearch(&key, arr, 10, sizeof(int), cmp_int));
    }
}
