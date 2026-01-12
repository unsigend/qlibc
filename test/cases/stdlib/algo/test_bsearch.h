#include <utest.h>
#include <stdlib.h>
#include <stddef.h>

int int_compare(const void *a, const void *b) {
    const int *ia = (const int *)a;
    const int *ib = (const int *)b;
    if (*ia < *ib) return -1;
    if (*ia > *ib) return 1;
    return 0;
}

int char_compare(const void *a, const void *b) {
    const char *ca = (const char *)a;
    const char *cb = (const char *)b;
    if (*ca < *cb) return -1;
    if (*ca > *cb) return 1;
    return 0;
}

int long_compare(const void *a, const void *b) {
    const long *la = (const long *)a;
    const long *lb = (const long *)b;
    if (*la < *lb) return -1;
    if (*la > *lb) return 1;
    return 0;
}

struct person {
    int id;
    char name[20];
    int age;
};

int person_compare_id(const void *a, const void *b) {
    const struct person *pa = (const struct person *)a;
    const struct person *pb = (const struct person *)b;
    if (pa->id < pb->id) return -1;
    if (pa->id > pb->id) return 1;
    return 0;
}

int person_compare_age(const void *a, const void *b) {
    const struct person *pa = (const struct person *)a;
    const struct person *pb = (const struct person *)b;
    if (pa->age < pb->age) return -1;
    if (pa->age > pb->age) return 1;
    return 0;
}

UTEST_TEST_CASE(bsearch){
    {
        int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int key = 5;
        void *result = bsearch(&key, arr, 10, sizeof(int), int_compare);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(int *)result == 5);
    }

    {
        int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int key = 1;
        void *result = bsearch(&key, arr, 10, sizeof(int), int_compare);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(int *)result == 1);
    }

    {
        int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int key = 10;
        void *result = bsearch(&key, arr, 10, sizeof(int), int_compare);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(int *)result == 10);
    }

    {
        int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int key = 0;
        void *result = bsearch(&key, arr, 10, sizeof(int), int_compare);
        EXPECT_NULL(result);
    }

    {
        int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int key = 11;
        void *result = bsearch(&key, arr, 10, sizeof(int), int_compare);
        EXPECT_NULL(result);
    }

    {
        int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int key = 7;
        void *result = bsearch(&key, arr, 10, sizeof(int), int_compare);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(int *)result == 7);
    }

    {
        int arr[] = {5};
        int key = 5;
        void *result = bsearch(&key, arr, 1, sizeof(int), int_compare);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(int *)result == 5);
    }

    {
        int arr[] = {5};
        int key = 3;
        void *result = bsearch(&key, arr, 1, sizeof(int), int_compare);
        EXPECT_NULL(result);
    }

    {
        int arr[] = {1, 3, 5, 7, 9};
        int key = 5;
        void *result = bsearch(&key, arr, 5, sizeof(int), int_compare);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(int *)result == 5);
    }

    {
        int arr[] = {1, 3, 5, 7, 9};
        int key = 4;
        void *result = bsearch(&key, arr, 5, sizeof(int), int_compare);
        EXPECT_NULL(result);
    }

    {
        int arr[] = {-10, -5, 0, 5, 10};
        int key = 0;
        void *result = bsearch(&key, arr, 5, sizeof(int), int_compare);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(int *)result == 0);
    }

    {
        int arr[] = {-10, -5, 0, 5, 10};
        int key = -10;
        void *result = bsearch(&key, arr, 5, sizeof(int), int_compare);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(int *)result == -10);
    }

    {
        int arr[] = {-10, -5, 0, 5, 10};
        int key = 10;
        void *result = bsearch(&key, arr, 5, sizeof(int), int_compare);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(int *)result == 10);
    }

    {
        int arr[] = {2, 2, 2, 2, 2};
        int key = 2;
        void *result = bsearch(&key, arr, 5, sizeof(int), int_compare);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(int *)result == 2);
    }

    {
        int arr[] = {1, 2, 2, 2, 5};
        int key = 2;
        void *result = bsearch(&key, arr, 5, sizeof(int), int_compare);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(int *)result == 2);
    }

    {
        char arr[] = {'a', 'b', 'c', 'd', 'e'};
        char key = 'c';
        void *result = bsearch(&key, arr, 5, sizeof(char), char_compare);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(char *)result == 'c');
    }

    {
        char arr[] = {'a', 'b', 'c', 'd', 'e'};
        char key = 'a';
        void *result = bsearch(&key, arr, 5, sizeof(char), char_compare);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(char *)result == 'a');
    }

    {
        char arr[] = {'a', 'b', 'c', 'd', 'e'};
        char key = 'e';
        void *result = bsearch(&key, arr, 5, sizeof(char), char_compare);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(char *)result == 'e');
    }

    {
        char arr[] = {'a', 'b', 'c', 'd', 'e'};
        char key = 'z';
        void *result = bsearch(&key, arr, 5, sizeof(char), char_compare);
        EXPECT_NULL(result);
    }

    {
        long arr[] = {100L, 200L, 300L, 400L, 500L};
        long key = 300L;
        void *result = bsearch(&key, arr, 5, sizeof(long), long_compare);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(long *)result == 300L);
    }

    {
        long arr[] = {100L, 200L, 300L, 400L, 500L};
        long key = 150L;
        void *result = bsearch(&key, arr, 5, sizeof(long), long_compare);
        EXPECT_NULL(result);
    }

    {
        struct person people[] = {
            {1, "Alice", 25},
            {2, "Bob", 30},
            {3, "Charlie", 35},
            {4, "David", 40},
            {5, "Eve", 45}
        };
        struct person key = {3, "", 0};
        void *result = bsearch(&key, people, 5, sizeof(struct person), person_compare_id);
        EXPECT_NOT_NULL(result);
        struct person *found = (struct person *)result;
        EXPECT_TRUE(found->id == 3);
    }

    {
        struct person people[] = {
            {1, "Alice", 25},
            {2, "Bob", 30},
            {3, "Charlie", 35},
            {4, "David", 40},
            {5, "Eve", 45}
        };
        struct person key = {6, "", 0};
        void *result = bsearch(&key, people, 5, sizeof(struct person), person_compare_id);
        EXPECT_NULL(result);
    }

    {
        struct person sorted[] = {
            {1, "Charlie", 35},
            {2, "Eve", 45},
            {3, "Bob", 30},
            {4, "David", 40},
            {5, "Alice", 25}
        };
        struct person key = {3, "", 0};
        void *result = bsearch(&key, sorted, 5, sizeof(struct person), person_compare_id);
        EXPECT_NOT_NULL(result);
        struct person *found = (struct person *)result;
        EXPECT_TRUE(found->id == 3);
    }

    {
        struct person people[] = {
            {1, "Alice", 25},
            {2, "Bob", 30},
            {3, "Charlie", 35},
            {4, "David", 40},
            {5, "Eve", 45}
        };
        struct person key = {0, "", 35};
        void *result = bsearch(&key, people, 5, sizeof(struct person), person_compare_age);
        EXPECT_NOT_NULL(result);
        struct person *found = (struct person *)result;
        EXPECT_TRUE(found->age == 35);
    }

    {
        struct person people[] = {
            {1, "Alice", 25},
            {2, "Bob", 30},
            {3, "Charlie", 35},
            {4, "David", 40},
            {5, "Eve", 45}
        };
        struct person key = {0, "", 20};
        void *result = bsearch(&key, people, 5, sizeof(struct person), person_compare_age);
        EXPECT_NULL(result);
    }

    {
        int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
        int key = 50;
        void *result = bsearch(&key, arr, 10, sizeof(int), int_compare);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(int *)result == 50);
    }

    {
        int arr[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
        int key = 55;
        void *result = bsearch(&key, arr, 10, sizeof(int), int_compare);
        EXPECT_NULL(result);
    }

    {
        int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
        int key = 8;
        void *result = bsearch(&key, arr, 15, sizeof(int), int_compare);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(int *)result == 8);
    }

    {
        int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
        int key = 16;
        void *result = bsearch(&key, arr, 15, sizeof(int), int_compare);
        EXPECT_NULL(result);
    }

    {
        int arr[] = {100, 200, 300, 400, 500};
        int key = 250;
        void *result = bsearch(&key, arr, 5, sizeof(int), int_compare);
        EXPECT_NULL(result);
    }

    {
        int arr[] = {100, 200, 300, 400, 500};
        int key = 300;
        void *result = bsearch(&key, arr, 5, sizeof(int), int_compare);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(int *)result == 300);
    }

    {
        int arr[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
        int key = 11;
        void *result = bsearch(&key, arr, 10, sizeof(int), int_compare);
        EXPECT_NOT_NULL(result);
        EXPECT_TRUE(*(int *)result == 11);
    }

    {
        int arr[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
        int key = 12;
        void *result = bsearch(&key, arr, 10, sizeof(int), int_compare);
        EXPECT_NULL(result);
    }
}
