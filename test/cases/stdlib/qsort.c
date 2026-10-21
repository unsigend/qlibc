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

static int cmp_int_desc(const void *a, const void *b)
{
    return cmp_int(b, a);
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

static int sorted_int(const int *a, size_t n)
{
    size_t i;

    for (i = 1; i < n; i++) {
        if (a[i - 1] > a[i])
            return 0;
    }
    return 1;
}

UTEST_CASE(qsort)
{
    int key;

    {
        int arr[] = {1};
        qsort(arr, 1, sizeof(int), cmp_int);
        EXPECT_EQ_INT(arr[0], 1);
        qsort(arr, 0, sizeof(int), cmp_int);
        EXPECT_EQ_INT(arr[0], 1);
    }

    {
        int arr[] = {2, 1};
        qsort(arr, 2, sizeof(int), cmp_int);
        EXPECT_EQ_INT(arr[0], 1);
        EXPECT_EQ_INT(arr[1], 2);
    }

    {
        int arr[] = {3, 1, 2};
        qsort(arr, 3, sizeof(int), cmp_int);
        EXPECT_EQ_INT(arr[0], 1);
        EXPECT_EQ_INT(arr[1], 2);
        EXPECT_EQ_INT(arr[2], 3);
    }

    {
        int arr[] = {1, 2, 3, 4, 5};
        qsort(arr, 5, sizeof(int), cmp_int);
        EXPECT_TRUE(sorted_int(arr, 5));
        EXPECT_EQ_INT(arr[0], 1);
        EXPECT_EQ_INT(arr[4], 5);
    }

    {
        int arr[] = {5, 4, 3, 2, 1};
        qsort(arr, 5, sizeof(int), cmp_int);
        EXPECT_EQ_INT(arr[0], 1);
        EXPECT_EQ_INT(arr[1], 2);
        EXPECT_EQ_INT(arr[2], 3);
        EXPECT_EQ_INT(arr[3], 4);
        EXPECT_EQ_INT(arr[4], 5);
    }

    {
        int arr[] = {4, 1, 5, 2, 3};
        qsort(arr, 5, sizeof(int), cmp_int);
        EXPECT_TRUE(sorted_int(arr, 5));
        EXPECT_EQ_INT(arr[0], 1);
        EXPECT_EQ_INT(arr[4], 5);
    }

    {
        int arr[] = {2, 2, 2, 2};
        qsort(arr, 4, sizeof(int), cmp_int);
        EXPECT_EQ_INT(arr[0], 2);
        EXPECT_EQ_INT(arr[1], 2);
        EXPECT_EQ_INT(arr[2], 2);
        EXPECT_EQ_INT(arr[3], 2);
    }

    {
        int arr[] = {3, 1, 2, 1, 3};
        qsort(arr, 5, sizeof(int), cmp_int);
        EXPECT_TRUE(sorted_int(arr, 5));
        EXPECT_EQ_INT(arr[0], 1);
        EXPECT_EQ_INT(arr[1], 1);
        EXPECT_EQ_INT(arr[2], 2);
        EXPECT_EQ_INT(arr[3], 3);
        EXPECT_EQ_INT(arr[4], 3);
    }

    {
        int arr[] = {-5, 2, -1, 0, 4, -3};
        qsort(arr, 6, sizeof(int), cmp_int);
        EXPECT_TRUE(sorted_int(arr, 6));
        EXPECT_EQ_INT(arr[0], -5);
        EXPECT_EQ_INT(arr[1], -3);
        EXPECT_EQ_INT(arr[2], -1);
        EXPECT_EQ_INT(arr[3], 0);
        EXPECT_EQ_INT(arr[4], 2);
        EXPECT_EQ_INT(arr[5], 4);
    }

    {
        int arr[] = {1, 4, 2, 5, 3};
        qsort(arr, 5, sizeof(int), cmp_int_desc);
        EXPECT_EQ_INT(arr[0], 5);
        EXPECT_EQ_INT(arr[1], 4);
        EXPECT_EQ_INT(arr[2], 3);
        EXPECT_EQ_INT(arr[3], 2);
        EXPECT_EQ_INT(arr[4], 1);
    }

    {
        char arr[] = {'d', 'a', 'c', 'b'};
        qsort(arr, 4, sizeof(char), cmp_char);
        EXPECT_EQ_CHAR(arr[0], 'a');
        EXPECT_EQ_CHAR(arr[1], 'b');
        EXPECT_EQ_CHAR(arr[2], 'c');
        EXPECT_EQ_CHAR(arr[3], 'd');
    }

    {
        long arr[] = {400L, 100L, 300L, 200L};
        qsort(arr, 4, sizeof(long), cmp_long);
        EXPECT_EQ_INT(arr[0], 100L);
        EXPECT_EQ_INT(arr[1], 200L);
        EXPECT_EQ_INT(arr[2], 300L);
        EXPECT_EQ_INT(arr[3], 400L);
    }

    {
        struct rec people[] = {
            {3, 35}, {1, 25}, {5, 45}, {2, 30}, {4, 40},
        };
        qsort(people, 5, sizeof(people[0]), cmp_id);
        EXPECT_EQ_INT(people[0].id, 1);
        EXPECT_EQ_INT(people[1].id, 2);
        EXPECT_EQ_INT(people[2].id, 3);
        EXPECT_EQ_INT(people[3].id, 4);
        EXPECT_EQ_INT(people[4].id, 5);
        EXPECT_EQ_INT(people[0].age, 25);
        EXPECT_EQ_INT(people[2].age, 35);
    }

    {
        int arr[] = {9, 4, 7, 1, 6, 2, 8, 3, 5};
        qsort(arr, 9, sizeof(int), cmp_int);
        EXPECT_TRUE(sorted_int(arr, 9));
        key = 1;
        EXPECT_EQ_PTR(bsearch(&key, arr, 9, sizeof(int), cmp_int), arr);
        key = 9;
        EXPECT_EQ_PTR(bsearch(&key, arr, 9, sizeof(int), cmp_int), arr + 8);
        key = 6;
        EXPECT_EQ_PTR(bsearch(&key, arr, 9, sizeof(int), cmp_int), arr + 5);
        key = 0;
        EXPECT_NULL(bsearch(&key, arr, 9, sizeof(int), cmp_int));
    }
}
