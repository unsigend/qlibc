#ifndef TEST_COMMON_H
#define TEST_COMMON_H

// this file provides some common functions for comparing values
// used for testing bsearch and qsort

#include <stdlib.h>
#include <utest.h>
#include <string.h>

#define NAMESPACE_BEGIN {
#define NAMESPACE_END }

static int compare_int_asc(const void *a, const void *b){
    int x = *(int*)a;
    int y = *(int*)b;
    return (x > y) - (x < y);
}

static int compare_int_desc(const void *a, const void *b){
    int x = *(int*)a;
    int y = *(int*)b;
    return (y > x) - (y < x);
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

#endif // TEST_COMMON_H
