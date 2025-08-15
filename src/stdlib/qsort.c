/* qlibc - A light-weight and portable C standard library
 * Copyright (C) 2025 Qiu Yixiang
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
#include <string.h>

static void _swap(void *a, void *b, size_t size){
    unsigned char *pa = (unsigned char *)a;
    unsigned char *pb = (unsigned char *)b;
    for (size_t i = 0; i < size; i++) {
        unsigned char temp = pa[i];
        pa[i] = pb[i];
        pb[i] = temp;
    }
}

// partition the array into two parts,
// the left part is less than the pivot,
// the right part is greater than the pivot
// return the index of the pivot
static size_t _partition(void *ptr, size_t count, size_t size,
    int (*comp)(const void*, const void*)){
    
    unsigned char *base = (unsigned char *)ptr;
    size_t pivot_idx = count / 2;
    
    // Move pivot to end
    _swap(base + pivot_idx * size, base + (count - 1) * size, size);
    
    unsigned char *pivot = base + (count - 1) * size;
    size_t i = 0;
    
    for (size_t j = 0; j < count - 1; j++) {
        if (comp(base + j * size, pivot) <= 0) {
            if (i != j) {
                _swap(base + i * size, base + j * size, size);
            }
            i++;
        }
    }
    
    // Move pivot to its final position
    _swap(base + i * size, pivot, size);
    return i;
}

void qsort(void *ptr, size_t count, size_t size,
    int (*comp)(const void*, const void*)){

    if (count <= 1)
        return;
    
    size_t pivot_idx = _partition(ptr, count, size, comp);
    
    // Sort left partition
    if (pivot_idx > 0) {
        qsort(ptr, pivot_idx, size, comp);
    }
    
    // Sort right partition
    if (pivot_idx + 1 < count) {
        unsigned char *base = (unsigned char *)ptr;
        qsort(base + (pivot_idx + 1) * size, count - pivot_idx - 1, size, comp);
    }
}