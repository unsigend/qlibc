#include "_compare.h"

static void verify_sorted_int_asc(int *arr, size_t len) {
    for (size_t i = 1; i < len; i++) {
        EXPECT_TRUE(arr[i-1] <= arr[i]);
    }
}

static void verify_sorted_int_desc(int *arr, size_t len) {
    for (size_t i = 1; i < len; i++) {
        EXPECT_TRUE(arr[i-1] >= arr[i]);
    }
}

static void verify_sorted_char_asc(char *arr, size_t len) {
    for (size_t i = 1; i < len; i++) {
        EXPECT_TRUE(arr[i-1] <= arr[i]);
    }
}

static void verify_sorted_double_asc(double *arr, size_t len) {
    for (size_t i = 1; i < len; i++) {
        EXPECT_TRUE(arr[i-1] <= arr[i]);
    }
}

static void verify_sorted_string_asc(char **arr, size_t len) {
    for (size_t i = 1; i < len; i++) {
        EXPECT_TRUE(strcmp(arr[i-1], arr[i]) <= 0);
    }
}

UTEST_TEST_CASE(qsort){

NAMESPACE_BEGIN
    int buf[10] = {5, 2, 8, 1, 9, 3, 7, 6, 4, 10};
    qsort(buf, 10, sizeof(int), compare_int_asc);
    verify_sorted_int_asc(buf, 10);
    EXPECT_EQUAL_INT(buf[0], 1);
    EXPECT_EQUAL_INT(buf[9], 10);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[10] = {5, 2, 8, 1, 9, 3, 7, 6, 4, 10};
    qsort(buf, 10, sizeof(int), compare_int_desc);
    verify_sorted_int_desc(buf, 10);
    EXPECT_EQUAL_INT(buf[0], 10);
    EXPECT_EQUAL_INT(buf[9], 1);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[1] = {42};
    qsort(buf, 1, sizeof(int), compare_int_asc);
    EXPECT_EQUAL_INT(buf[0], 42);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[2] = {20, 10};
    qsort(buf, 2, sizeof(int), compare_int_asc);
    EXPECT_EQUAL_INT(buf[0], 10);
    EXPECT_EQUAL_INT(buf[1], 20);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[2] = {10, 20};
    qsort(buf, 2, sizeof(int), compare_int_asc);
    EXPECT_EQUAL_INT(buf[0], 10);
    EXPECT_EQUAL_INT(buf[1], 20);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[3] = {30, 10, 20};
    qsort(buf, 3, sizeof(int), compare_int_asc);
    EXPECT_EQUAL_INT(buf[0], 10);
    EXPECT_EQUAL_INT(buf[1], 20);
    EXPECT_EQUAL_INT(buf[2], 30);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[1] = {1};
    qsort(buf, 0, sizeof(int), compare_int_asc);
    EXPECT_EQUAL_INT(buf[0], 1);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[5] = {5, 5, 5, 5, 5};
    qsort(buf, 5, sizeof(int), compare_int_asc);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQUAL_INT(buf[i], 5);
    }
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[10] = {1, 5, 5, 5, 5, 5, 5, 5, 5, 10};
    qsort(buf, 10, sizeof(int), compare_int_asc);
    verify_sorted_int_asc(buf, 10);
    EXPECT_EQUAL_INT(buf[0], 1);
    EXPECT_EQUAL_INT(buf[9], 10);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[8] = {3, 3, 3, 1, 2, 4, 4, 4};
    qsort(buf, 8, sizeof(int), compare_int_asc);
    verify_sorted_int_asc(buf, 8);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[7] = {-10, 5, -3, 0, 15, -1, 8};
    qsort(buf, 7, sizeof(int), compare_int_asc);
    verify_sorted_int_asc(buf, 7);
    EXPECT_EQUAL_INT(buf[0], -10);
    EXPECT_EQUAL_INT(buf[6], 15);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[5] = {-50, -10, -30, -20, -40};
    qsort(buf, 5, sizeof(int), compare_int_asc);
    verify_sorted_int_asc(buf, 5);
    EXPECT_EQUAL_INT(buf[0], -50);
    EXPECT_EQUAL_INT(buf[4], -10);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[3] = {-2147483647-1, 2147483647, 0};
    qsort(buf, 3, sizeof(int), compare_int_asc);
    EXPECT_EQUAL_INT(buf[0], -2147483647-1);
    EXPECT_EQUAL_INT(buf[1], 0);
    EXPECT_EQUAL_INT(buf[2], 2147483647);
NAMESPACE_END

NAMESPACE_BEGIN
    char buf[5] = {'e', 'a', 'c', 'b', 'd'};
    qsort(buf, 5, sizeof(char), compare_char_asc);
    verify_sorted_char_asc(buf, 5);
    EXPECT_EQUAL_INT(buf[0], 'a');
    EXPECT_EQUAL_INT(buf[4], 'e');
NAMESPACE_END

NAMESPACE_BEGIN
    char buf[5] = {'a', 'e', 'c', 'd', 'b'};
    qsort(buf, 5, sizeof(char), compare_char_desc);
    EXPECT_EQUAL_INT(buf[0], 'e');
    EXPECT_EQUAL_INT(buf[4], 'a');
NAMESPACE_END

NAMESPACE_BEGIN
    char buf[8] = {'Z', 'a', '5', 'A', 'm', '9', '0', 'z'};
    qsort(buf, 8, sizeof(char), compare_char_asc);
    verify_sorted_char_asc(buf, 8);
NAMESPACE_END

NAMESPACE_BEGIN
    char buf[6] = {'!', '#', '%', '&', '*', '+'};
    qsort(buf, 6, sizeof(char), compare_char_asc);
    verify_sorted_char_asc(buf, 6);
NAMESPACE_END

NAMESPACE_BEGIN
    char buf[4] = {' ', '\t', '\n', '\r'};
    qsort(buf, 4, sizeof(char), compare_char_asc);
    verify_sorted_char_asc(buf, 4);
NAMESPACE_END

NAMESPACE_BEGIN
    double buf[6] = {3.3, 1.1, 5.5, 2.2, 6.6, 4.4};
    qsort(buf, 6, sizeof(double), compare_double_asc);
    verify_sorted_double_asc(buf, 6);
    EXPECT_EQUAL_DOUBLE(buf[0], 1.1);
    EXPECT_EQUAL_DOUBLE(buf[5], 6.6);
NAMESPACE_END

NAMESPACE_BEGIN
    double buf[6] = {1.1, 6.6, 3.3, 4.4, 2.2, 5.5};
    qsort(buf, 6, sizeof(double), compare_double_desc);
    EXPECT_EQUAL_DOUBLE(buf[0], 6.6);
    EXPECT_EQUAL_DOUBLE(buf[5], 1.1);
NAMESPACE_END

NAMESPACE_BEGIN
    double buf[5] = {1.0003, 1.0001, 1.0005, 1.0002, 1.0004};
    qsort(buf, 5, sizeof(double), compare_double_asc);
    verify_sorted_double_asc(buf, 5);
    EXPECT_EQUAL_DOUBLE(buf[0], 1.0001);
    EXPECT_EQUAL_DOUBLE(buf[4], 1.0005);
NAMESPACE_END

NAMESPACE_BEGIN
    double buf[6] = {-5.5, 2.2, -1.1, 4.4, 0.0, -3.3};
    qsort(buf, 6, sizeof(double), compare_double_asc);
    verify_sorted_double_asc(buf, 6);
    EXPECT_EQUAL_DOUBLE(buf[0], -5.5);
    EXPECT_EQUAL_DOUBLE(buf[5], 4.4);
NAMESPACE_END

NAMESPACE_BEGIN
    char *buf[5] = {"cherry", "apple", "elderberry", "banana", "date"};
    qsort(buf, 5, sizeof(char*), compare_string_asc);
    verify_sorted_string_asc(buf, 5);
    EXPECT_EQUAL_STRING(buf[0], "apple");
    EXPECT_EQUAL_STRING(buf[4], "elderberry");
NAMESPACE_END

NAMESPACE_BEGIN
    char *buf[5] = {"apple", "elderberry", "cherry", "date", "banana"};
    qsort(buf, 5, sizeof(char*), compare_string_desc);
    EXPECT_EQUAL_STRING(buf[0], "elderberry");
    EXPECT_EQUAL_STRING(buf[4], "apple");
NAMESPACE_END

NAMESPACE_BEGIN
    char *buf[6] = {"zebra", "Apple", "banana", "apple", "Cherry", "Banana"};
    qsort(buf, 6, sizeof(char*), compare_string_asc);
    verify_sorted_string_asc(buf, 6);
NAMESPACE_END

NAMESPACE_BEGIN
    char *buf[4] = {"abc", "", "ab", "a"};
    qsort(buf, 4, sizeof(char*), compare_string_asc);
    verify_sorted_string_asc(buf, 4);
    EXPECT_EQUAL_STRING(buf[0], "");
    EXPECT_EQUAL_STRING(buf[3], "abc");
NAMESPACE_END

NAMESPACE_BEGIN
    char *buf[5] = {"e", "a", "d", "b", "c"};
    qsort(buf, 5, sizeof(char*), compare_string_asc);
    verify_sorted_string_asc(buf, 5);
NAMESPACE_END

NAMESPACE_BEGIN
    test_struct_t buf[4] = {
        {30, "Charlie"},
        {10, "Alice"},
        {40, "David"},
        {20, "Bob"}
    };
    qsort(buf, 4, sizeof(test_struct_t), compare_struct_by_id_asc);
    EXPECT_EQUAL_INT(buf[0].id, 10);
    EXPECT_EQUAL_STRING(buf[0].name, "Alice");
    EXPECT_EQUAL_INT(buf[3].id, 40);
    EXPECT_EQUAL_STRING(buf[3].name, "David");
NAMESPACE_END

NAMESPACE_BEGIN
    test_struct_t buf[4] = {
        {30, "Charlie"},
        {10, "Alice"},
        {40, "David"},
        {20, "Bob"}
    };
    qsort(buf, 4, sizeof(test_struct_t), compare_struct_by_name_asc);
    EXPECT_EQUAL_STRING(buf[0].name, "Alice");
    EXPECT_EQUAL_INT(buf[0].id, 10);
    EXPECT_EQUAL_STRING(buf[3].name, "David");
    EXPECT_EQUAL_INT(buf[3].id, 40);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[100];
    for (int i = 0; i < 100; i++) {
        buf[i] = 99 - i;
    }
    qsort(buf, 100, sizeof(int), compare_int_asc);
    verify_sorted_int_asc(buf, 100);
    EXPECT_EQUAL_INT(buf[0], 0);
    EXPECT_EQUAL_INT(buf[99], 99);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[500];
    for (int i = 0; i < 500; i++) {
        buf[i] = (i * 37) % 500;
    }
    qsort(buf, 500, sizeof(int), compare_int_asc);
    verify_sorted_int_asc(buf, 500);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[1000];
    for (int i = 0; i < 1000; i++) {
        buf[i] = 1000 - i - 1;
    }
    qsort(buf, 1000, sizeof(int), compare_int_asc);
    verify_sorted_int_asc(buf, 1000);
    EXPECT_EQUAL_INT(buf[0], 0);
    EXPECT_EQUAL_INT(buf[999], 999);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[4] = {40, 10, 30, 20};
    qsort(buf, 4, sizeof(int), compare_int_asc);
    verify_sorted_int_asc(buf, 4);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[8] = {80, 10, 60, 20, 70, 30, 50, 40};
    qsort(buf, 8, sizeof(int), compare_int_asc);
    verify_sorted_int_asc(buf, 8);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[16];
    for (int i = 0; i < 16; i++) {
        buf[i] = (16 - i) * 7;
    }
    qsort(buf, 16, sizeof(int), compare_int_asc);
    verify_sorted_int_asc(buf, 16);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[7] = {77, 11, 55, 33, 66, 22, 44};
    qsort(buf, 7, sizeof(int), compare_int_asc);
    verify_sorted_int_asc(buf, 7);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[9] = {17, 1, 13, 5, 9, 3, 15, 7, 11};
    qsort(buf, 9, sizeof(int), compare_int_asc);
    verify_sorted_int_asc(buf, 9);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[5] = {2147483647, 1000000, 2147483647, 2000000, 2147483647};
    qsort(buf, 5, sizeof(int), compare_int_asc);
    verify_sorted_int_asc(buf, 5);
    EXPECT_EQUAL_INT(buf[0], 1000000);
    EXPECT_EQUAL_INT(buf[4], 2147483647);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[5] = {-1, -500000, -2147483647-1, -1000000, -2147483647-1};
    qsort(buf, 5, sizeof(int), compare_int_asc);
    verify_sorted_int_asc(buf, 5);
    EXPECT_EQUAL_INT(buf[0], -2147483647-1);
    EXPECT_EQUAL_INT(buf[4], -1);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[10] = {6, 3, 8, 1, 9, 4, 7, 2, 10, 5};
    qsort(buf, 10, sizeof(int), compare_int_asc);
    verify_sorted_int_asc(buf, 10);
    for (int i = 0; i < 10; i++) {
        EXPECT_EQUAL_INT(buf[i], i + 1);
    }
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[10] = {18, 4, 14, 8, 16, 2, 12, 6, 20, 10};
    qsort(buf, 10, sizeof(int), compare_int_asc);
    verify_sorted_int_asc(buf, 10);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[10] = {55, 21, 34, 3, 13, 1, 8, 2, 5, 1};
    qsort(buf, 10, sizeof(int), compare_int_asc);
    verify_sorted_int_asc(buf, 10);
NAMESPACE_END

NAMESPACE_BEGIN
    int buf[20];
    for (int i = 0; i < 20; i++) {
        buf[i] = 100 - i * 5;
    }
    qsort(buf, 20, sizeof(int), compare_int_desc);
    verify_sorted_int_desc(buf, 20);
NAMESPACE_END

NAMESPACE_BEGIN
    char buf[10] = {'j', 'a', 'h', 'c', 'f', 'b', 'i', 'd', 'g', 'e'};
    qsort(buf, 10, sizeof(char), compare_char_desc);
    EXPECT_EQUAL_INT(buf[0], 'j');
    EXPECT_EQUAL_INT(buf[9], 'a');
NAMESPACE_END

}
