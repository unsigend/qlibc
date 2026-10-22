/* qlibc - A light-weight and portable C standard library
 * Copyright (C) 2025-2027 Yixiang Qiu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define GET(base, index, sz) ((void *)((char *)(base) + (index) * (sz)))

static void swap(void *lhs, void *rhs, size_t sz)
{
    unsigned char *a = lhs;
    unsigned char *b = rhs;
    unsigned long word;
    unsigned char byte;
    size_t i = 0;

    if (a == b)
        return;

    for (; i + sizeof(word) <= sz; i += sizeof(word)) {
        memcpy(&word, a + i, sizeof(word));
        memcpy(a + i, b + i, sizeof(word));
        memcpy(b + i, &word, sizeof(word));
    }
    for (; i < sz; i++) {
        memcpy(&byte, a + i, 1);
        memcpy(a + i, b + i, 1);
        memcpy(b + i, &byte, 1);
    }
}

void qsort(void *ptr, size_t n, size_t size,
           int (*cmp)(const void *, const void *))
{
    size_t min, mid, max;
    size_t pivot;

    if (!ptr || !size || !cmp)
        return;
    if (n <= 1)
        return;

    /* Median of three pivot selection: MIN[[min, mid], max], MAX[mid, max]*/
    min = 0, mid = n / 2, max = n - 1;
    if (cmp(GET(ptr, min, size), GET(ptr, mid, size)) > 0)
        swap(GET(ptr, min, size), GET(ptr, mid, size), size);
    if (cmp(GET(ptr, min, size), GET(ptr, max, size)) > 0)
        swap(GET(ptr, min, size), GET(ptr, max, size), size);
    if (cmp(GET(ptr, mid, size), GET(ptr, max, size)) > 0)
        swap(GET(ptr, mid, size), GET(ptr, max, size), size);

    if (n <= 3)
        return;

    pivot = max - 1;
    swap(GET(ptr, mid, size), GET(ptr, pivot, size), size);

    size_t l = 1, r = n - 3;
    while (l < r) {
        while (l < r && cmp(GET(ptr, l, size), GET(ptr, pivot, size)) < 0)
            l++;
        while (l < r && cmp(GET(ptr, r, size), GET(ptr, pivot, size)) > 0)
            r--;
        if (l < r) {
            swap(GET(ptr, l, size), GET(ptr, r, size), size);
            l++, r--;
        }
    }
    size_t pos = l;
    if (cmp(GET(ptr, pos, size), GET(ptr, pivot, size)) <= 0)
        pos++;
    swap(GET(ptr, pos, size), GET(ptr, pivot, size), size);

    qsort(ptr, pos, size, cmp);
    qsort(GET(ptr, pos + 1, size), n - pos - 1, size, cmp);
}