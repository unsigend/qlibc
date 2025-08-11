#include <stdlib.h>
#include <utest.h>
#include <string.h>

#define NAMESPACE_BEGIN {
#define NAMESPACE_END }
static int compare_int_asc(const void *a, const void *b){
    return *(int*)a - *(int*)b;
}

static int compare_int_desc(const void *a, const void *b){
    return *(int*)b - *(int*)a;
}

static int compare_char_asc(const void *a, const void *b){
    return *(char*)a - *(char*)b;
}

static int compare_char_desc(const void *a, const void *b){
    return *(char*)b - *(char*)a;
}

static int compare_double_asc(const void *a, const void *b){
    double diff = *(double*)a - *(double*)b;
    return (diff > 0) - (diff < 0);
}

static int compare_double_desc(const void *a, const void *b){
    double diff = *(double*)b - *(double*)a;
    return (diff > 0) - (diff < 0);
}

static int compare_string_asc(const void *a, const void *b){
    return strcmp(*(char**)a, *(char**)b);
}

static int compare_string_desc(const void *a, const void *b){
    return strcmp(*(char**)b, *(char**)a);
}

typedef struct {
    int id;
    char name[20];
} test_struct_t;

static int compare_struct_by_id_asc(const void *a, const void *b){
    return ((test_struct_t*)a)->id - ((test_struct_t*)b)->id;
}

static int compare_struct_by_name_asc(const void *a, const void *b){
    return strcmp(((test_struct_t*)a)->name, ((test_struct_t*)b)->name);
}

UTEST_TEST_CASE(bsearch){
NAMESPACE_BEGIN
    int buf[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int key = 5;
    int *ptr = (int *)bsearch(&key, buf, 10, sizeof(int), compare_int_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 5);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int key = 1;
    int *ptr = (int *)bsearch(&key, buf, 10, sizeof(int), compare_int_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 1);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int key = 10;
    int *ptr = (int *)bsearch(&key, buf, 10, sizeof(int), compare_int_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 10);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int key = 6;
    int *ptr = (int *)bsearch(&key, buf, 10, sizeof(int), compare_int_desc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 6);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int key = 0;
    int *ptr = (int *)bsearch(&key, buf, 10, sizeof(int), compare_int_asc);
    EXPECT_NULL(ptr);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int key = 11;
    int *ptr = (int *)bsearch(&key, buf, 10, sizeof(int), compare_int_asc);
    EXPECT_NULL(ptr);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[1] = {42};
    int key = 42;
    int *ptr = (int *)bsearch(&key, buf, 1, sizeof(int), compare_int_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 42);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[1] = {42};
    int key = 41;
    int *ptr = (int *)bsearch(&key, buf, 1, sizeof(int), compare_int_asc);
    EXPECT_NULL(ptr);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[1] = {1};
    int key = 1;
    int *ptr = (int *)bsearch(&key, buf, 0, sizeof(int), compare_int_asc);
    EXPECT_NULL(ptr);
NAMESPACE_END

NAMESPACE_BEGIN
    char buf[5] = {'a', 'c', 'e', 'g', 'i'};
    char key = 'e';
    char *ptr = (char *)bsearch(&key, buf, 5, sizeof(char), compare_char_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 'e');
NAMESPACE_END

NAMESPACE_BEGIN
    char buf[5] = {'z', 'x', 'v', 't', 'r'};
    char key = 'v';
    char *ptr = (char *)bsearch(&key, buf, 5, sizeof(char), compare_char_desc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 'v');
NAMESPACE_END

NAMESPACE_BEGIN
    double buf[6] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6};
    double key = 3.3;
    double *ptr = (double *)bsearch(&key, buf, 6, sizeof(double), compare_double_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_DOUBLE(*ptr, 3.3);
NAMESPACE_END

NAMESPACE_BEGIN
    char *buf[5] = {"apple", "banana", "cherry", "date", "elderberry"};
    char *key = "cherry";
    char **ptr = (char **)bsearch(&key, buf, 5, sizeof(char*), compare_string_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_STRING(*ptr, "cherry");
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[10] = {1, 2, 3, 3, 3, 5, 6, 7, 8, 9};
    int key = 3;
    int *ptr = (int *)bsearch(&key, buf, 10, sizeof(int), compare_int_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 3);
NAMESPACE_END

NAMESPACE_BEGIN
    int large_buf[100];
    for (int i = 0; i < 100; i++) {
        large_buf[i] = i * 2;  // Even numbers 0, 2, 4, ..., 198
    }
    int key = 88;  // Should be at index 44
    int *ptr = (int *)bsearch(&key, large_buf, 100, sizeof(int), compare_int_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 88);
NAMESPACE_END

NAMESPACE_BEGIN
    int large_buf[100];
    for (int i = 0; i < 100; i++) {
        large_buf[i] = i * 2;  // Even numbers only
    }
    int key = 87;  // Odd number, should not be found
    int *ptr = (int *)bsearch(&key, large_buf, 100, sizeof(int), compare_int_asc);
    EXPECT_NULL(ptr);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[7] = {-10, -5, -1, 0, 3, 8, 15};
    int key = -1;
    int *ptr = (int *)bsearch(&key, buf, 7, sizeof(int), compare_int_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, -1);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[5] = {7, 7, 7, 7, 7};
    int key = 7;
    int *ptr = (int *)bsearch(&key, buf, 5, sizeof(int), compare_int_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 7);
NAMESPACE_END

NAMESPACE_BEGIN
    test_struct_t buf[4] = {
        {10, "Alice"},
        {20, "Bob"}, 
        {30, "Charlie"},
        {40, "David"}
    };
    test_struct_t key = {20, ""};
    test_struct_t *ptr = (test_struct_t *)bsearch(&key, buf, 4, sizeof(test_struct_t), compare_struct_by_id_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(ptr->id, 20);
    EXPECT_EQUAL_STRING(ptr->name, "Bob");
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[2] = {10, 20};
    int key = 10;
    int *ptr = (int *)bsearch(&key, buf, 2, sizeof(int), compare_int_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 10);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[2] = {10, 20};
    int key = 20;
    int *ptr = (int *)bsearch(&key, buf, 2, sizeof(int), compare_int_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 20);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[2] = {10, 20};
    int key = 5;
    int *ptr = (int *)bsearch(&key, buf, 2, sizeof(int), compare_int_asc);
    EXPECT_NULL(ptr);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[2] = {10, 20};
    int key = 25;
    int *ptr = (int *)bsearch(&key, buf, 2, sizeof(int), compare_int_asc);
    EXPECT_NULL(ptr);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[2] = {10, 20};
    int key = 15;
    int *ptr = (int *)bsearch(&key, buf, 2, sizeof(int), compare_int_asc);
    EXPECT_NULL(ptr);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[3] = {5, 10, 15};
    int key = 5;
    int *ptr = (int *)bsearch(&key, buf, 3, sizeof(int), compare_int_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 5);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[3] = {5, 10, 15};
    int key = 10;
    int *ptr = (int *)bsearch(&key, buf, 3, sizeof(int), compare_int_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 10);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[3] = {5, 10, 15};
    int key = 15;
    int *ptr = (int *)bsearch(&key, buf, 3, sizeof(int), compare_int_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 15);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[8] = {1, 1, 1, 4, 5, 6, 7, 8};
    int key = 1;
    int *ptr = (int *)bsearch(&key, buf, 8, sizeof(int), compare_int_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 1);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[8] = {1, 2, 3, 4, 5, 9, 9, 9};
    int key = 9;
    int *ptr = (int *)bsearch(&key, buf, 8, sizeof(int), compare_int_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 9);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[10] = {1, 2, 5, 5, 5, 5, 5, 8, 9, 10};
    int key = 5;
    int *ptr = (int *)bsearch(&key, buf, 10, sizeof(int), compare_int_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 5);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[3] = {-2147483647-1, 0, 2147483647};  // INT_MIN, 0, INT_MAX
    int key = -2147483647-1;  // INT_MIN
    int *ptr = (int *)bsearch(&key, buf, 3, sizeof(int), compare_int_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, -2147483647-1);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[7] = {-100, -50, -1, 0, 1, 50, 100};
    int key = 0;
    int *ptr = (int *)bsearch(&key, buf, 7, sizeof(int), compare_int_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 0);
NAMESPACE_END

NAMESPACE_BEGIN
    double buf[5] = {1.0001, 1.0002, 1.0003, 1.0004, 1.0005};
    double key = 1.0003;
    double *ptr = (double *)bsearch(&key, buf, 5, sizeof(double), compare_double_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_DOUBLE(*ptr, 1.0003);
NAMESPACE_END

NAMESPACE_BEGIN
    double buf[6] = {-5.5, -3.3, -1.1, 0.0, 2.2, 4.4};
    double key = -3.3;
    double *ptr = (double *)bsearch(&key, buf, 6, sizeof(double), compare_double_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_DOUBLE(*ptr, -3.3);
NAMESPACE_END

NAMESPACE_BEGIN
    double buf[5] = {9.9, 7.7, 5.5, 3.3, 1.1};
    double key = 5.5;
    double *ptr = (double *)bsearch(&key, buf, 5, sizeof(double), compare_double_desc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_DOUBLE(*ptr, 5.5);
NAMESPACE_END

NAMESPACE_BEGIN
    char buf[8] = {'0', '5', '9', 'A', 'M', 'Z', 'a', 'z'};
    char key = 'M';
    char *ptr = (char *)bsearch(&key, buf, 8, sizeof(char), compare_char_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 'M');
NAMESPACE_END

NAMESPACE_BEGIN
    char buf[7] = {'!', '#', '%', '&', '*', '+', '='};
    char key = '&';
    char *ptr = (char *)bsearch(&key, buf, 7, sizeof(char), compare_char_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, '&');
NAMESPACE_END

NAMESPACE_BEGIN
    char buf[4] = {'\t', '\n', '\r', ' '};  // Tab, newline, carriage return, space
    char key = '\n';
    char *ptr = (char *)bsearch(&key, buf, 4, sizeof(char), compare_char_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, '\n');
NAMESPACE_END

NAMESPACE_BEGIN
    char *buf[6] = {"Apple", "Banana", "apple", "banana", "cherry", "zebra"};
    char *key = "apple";
    char **ptr = (char **)bsearch(&key, buf, 6, sizeof(char*), compare_string_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_STRING(*ptr, "apple");
NAMESPACE_END

NAMESPACE_BEGIN
    char *buf[5] = {"zebra", "cherry", "banana", "apple", "Apple"};
    char *key = "banana";
    char **ptr = (char **)bsearch(&key, buf, 5, sizeof(char*), compare_string_desc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_STRING(*ptr, "banana");
NAMESPACE_END

NAMESPACE_BEGIN
    char *buf[4] = {"", "a", "ab", "abc"};
    char *key = "";
    char **ptr = (char **)bsearch(&key, buf, 4, sizeof(char*), compare_string_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_STRING(*ptr, "");
NAMESPACE_END

NAMESPACE_BEGIN
    char *buf[5] = {"a", "b", "c", "d", "e"};
    char *key = "c";
    char **ptr = (char **)bsearch(&key, buf, 5, sizeof(char*), compare_string_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_STRING(*ptr, "c");
NAMESPACE_END

NAMESPACE_BEGIN
    test_struct_t buf[5] = {
        {40, "Alice"},
        {10, "Bob"}, 
        {30, "Charlie"},
        {20, "David"},
        {50, "Eve"}
    };
    test_struct_t key = {0, "David"};
    test_struct_t *ptr = (test_struct_t *)bsearch(&key, buf, 5, sizeof(test_struct_t), compare_struct_by_name_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(ptr->id, 20);
    EXPECT_EQUAL_STRING(ptr->name, "David");
NAMESPACE_END

NAMESPACE_BEGIN
    test_struct_t buf[4] = {
        {10, "Alice"},
        {20, "Bob"}, 
        {30, "Charlie"},
        {40, "David"}
    };
    test_struct_t key = {25, ""};
    test_struct_t *ptr = (test_struct_t *)bsearch(&key, buf, 4, sizeof(test_struct_t), compare_struct_by_id_asc);
    EXPECT_NULL(ptr);
NAMESPACE_END

NAMESPACE_BEGIN
    test_struct_t buf[4] = {
        {10, "Alice"},
        {20, "Bob"}, 
        {30, "Charlie"},
        {40, "David"}
    };
    test_struct_t key = {0, "Eve"};
    test_struct_t *ptr = (test_struct_t *)bsearch(&key, buf, 4, sizeof(test_struct_t), compare_struct_by_name_asc);
    EXPECT_NULL(ptr);
NAMESPACE_END

NAMESPACE_BEGIN
    int large_buf[1000];
    for (int i = 0; i < 1000; i++) {
        large_buf[i] = i * 3;
    }
    int key = 1497;
    int *ptr = (int *)bsearch(&key, large_buf, 1000, sizeof(int), compare_int_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 1497);
NAMESPACE_END

NAMESPACE_BEGIN
    int large_buf[500];
    for (int i = 0; i < 500; i++) {
        large_buf[i] = i * 5 + 100;
    }
    int key = 100;
    int *ptr = (int *)bsearch(&key, large_buf, 500, sizeof(int), compare_int_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 100);
NAMESPACE_END

NAMESPACE_BEGIN
    int large_buf[500];
    for (int i = 0; i < 500; i++) {
        large_buf[i] = i * 5 + 100;
    }
    int key = 2595;
    int *ptr = (int *)bsearch(&key, large_buf, 500, sizeof(int), compare_int_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 2595);
NAMESPACE_END

NAMESPACE_BEGIN
    int desc_buf[20];
    for (int i = 0; i < 20; i++) {
        desc_buf[i] = 100 - i * 5; 
    }
    int key = 45;
    int *ptr = (int *)bsearch(&key, desc_buf, 20, sizeof(int), compare_int_desc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 45);
NAMESPACE_END

NAMESPACE_BEGIN
    char desc_buf[10] = {'z', 'x', 'v', 't', 'r', 'p', 'n', 'l', 'j', 'h'};
    char key = 'p';
    char *ptr = (char *)bsearch(&key, desc_buf, 10, sizeof(char), compare_char_desc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 'p');
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[4] = {10, 20, 30, 40};
    int key = 30;
    int *ptr = (int *)bsearch(&key, buf, 4, sizeof(int), compare_int_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 30);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[8] = {5, 10, 15, 20, 25, 30, 35, 40};
    int key = 25;
    int *ptr = (int *)bsearch(&key, buf, 8, sizeof(int), compare_int_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 25);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[16];
    for (int i = 0; i < 16; i++) {
        buf[i] = (i + 1) * 7;
    }
    int key = 77;
    int *ptr = (int *)bsearch(&key, buf, 16, sizeof(int), compare_int_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 77);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[7] = {11, 22, 33, 44, 55, 66, 77};
    int key = 44;
    int *ptr = (int *)bsearch(&key, buf, 7, sizeof(int), compare_int_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 44);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[9] = {1, 3, 5, 7, 9, 11, 13, 15, 17};
    int key = 9;
    int *ptr = (int *)bsearch(&key, buf, 9, sizeof(int), compare_int_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 9);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[5] = {1000000, 2000000, 2147483647, 2147483647, 2147483647};
    int key = 2147483647;
    int *ptr = (int *)bsearch(&key, buf, 5, sizeof(int), compare_int_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 2147483647);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[5] = {-2147483647-1, -2147483647-1, -1000000, -500000, -1};
    int key = -2147483647-1;
    int *ptr = (int *)bsearch(&key, buf, 5, sizeof(int), compare_int_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, -2147483647-1);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int key = 6;
    int *ptr = (int *)bsearch(&key, buf, 10, sizeof(int), compare_int_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 6);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[10] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    int key = 14;
    int *ptr = (int *)bsearch(&key, buf, 10, sizeof(int), compare_int_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 14);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[10] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55};
    int key = 13;
    int *ptr = (int *)bsearch(&key, buf, 10, sizeof(int), compare_int_asc);
    EXPECT_NOT_NULL(ptr);
    EXPECT_EQUAL_INT(*ptr, 13);
NAMESPACE_END
}