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

#ifndef _QLIBC_INTTYPES_H_
#define _QLIBC_INTTYPES_H_

#include <feature.h>
#include <stdint.h>

#if __WORD_SIZE == 8
#define __QLIBC_PRI64 "l"
#define __QLIBC_PRIPTR "l"
#else
#define __QLIBC_PRI64 "ll"
#define __QLIBC_PRIPTR
#endif

#define __QLIBC_PRI8 "hh"
#define __QLIBC_PRI16 "h"
#define __QLIBC_PRI32

#if __INT_LEAST8_WIDTH__ == 64
#define __QLIBC_PRI_LEAST8 __QLIBC_PRI64
#elif __INT_LEAST8_WIDTH__ == 32
#define __QLIBC_PRI_LEAST8 __QLIBC_PRI32
#elif __INT_LEAST8_WIDTH__ == 16
#define __QLIBC_PRI_LEAST8 __QLIBC_PRI16
#else
#define __QLIBC_PRI_LEAST8 __QLIBC_PRI8
#endif

#if __INT_LEAST16_WIDTH__ == 64
#define __QLIBC_PRI_LEAST16 __QLIBC_PRI64
#elif __INT_LEAST16_WIDTH__ == 32
#define __QLIBC_PRI_LEAST16 __QLIBC_PRI32
#else
#define __QLIBC_PRI_LEAST16 __QLIBC_PRI16
#endif

#if __INT_LEAST32_WIDTH__ == 64
#define __QLIBC_PRI_LEAST32 __QLIBC_PRI64
#else
#define __QLIBC_PRI_LEAST32 __QLIBC_PRI32
#endif

#define __QLIBC_PRI_LEAST64 __QLIBC_PRI64

#if __INT_FAST8_WIDTH__ == 64
#define __QLIBC_PRI_FAST8 __QLIBC_PRI64
#elif __INT_FAST8_WIDTH__ == 32
#define __QLIBC_PRI_FAST8 __QLIBC_PRI32
#elif __INT_FAST8_WIDTH__ == 16
#define __QLIBC_PRI_FAST8 __QLIBC_PRI16
#else
#define __QLIBC_PRI_FAST8 __QLIBC_PRI8
#endif

#if __INT_FAST16_WIDTH__ == 64
#define __QLIBC_PRI_FAST16 __QLIBC_PRI64
#elif __INT_FAST16_WIDTH__ == 32
#define __QLIBC_PRI_FAST16 __QLIBC_PRI32
#else
#define __QLIBC_PRI_FAST16 __QLIBC_PRI16
#endif

#if __INT_FAST32_WIDTH__ == 64
#define __QLIBC_PRI_FAST32 __QLIBC_PRI64
#else
#define __QLIBC_PRI_FAST32 __QLIBC_PRI32
#endif

#if __INT_FAST64_WIDTH__ == 64
#define __QLIBC_PRI_FAST64 __QLIBC_PRI64
#else
#define __QLIBC_PRI_FAST64 __QLIBC_PRI64
#endif

#if __INTMAX_WIDTH__ == 64
#define __QLIBC_PRIMAX __QLIBC_PRI64
#else
#define __QLIBC_PRIMAX __QLIBC_PRI32
#endif

#ifdef __INT8_TYPE__
#define PRId8 __QLIBC_PRI8 "d"
#define PRIi8 __QLIBC_PRI8 "i"
#define PRIo8 __QLIBC_PRI8 "o"
#define PRIu8 __QLIBC_PRI8 "u"
#define PRIx8 __QLIBC_PRI8 "x"
#define PRIX8 __QLIBC_PRI8 "X"
#define SCNd8 __QLIBC_PRI8 "d"
#define SCNi8 __QLIBC_PRI8 "i"
#define SCNo8 __QLIBC_PRI8 "o"
#define SCNu8 __QLIBC_PRI8 "u"
#define SCNx8 __QLIBC_PRI8 "x"
#endif

#ifdef __INT16_TYPE__
#define PRId16 __QLIBC_PRI16 "d"
#define PRIi16 __QLIBC_PRI16 "i"
#define PRIo16 __QLIBC_PRI16 "o"
#define PRIu16 __QLIBC_PRI16 "u"
#define PRIx16 __QLIBC_PRI16 "x"
#define PRIX16 __QLIBC_PRI16 "X"
#define SCNd16 __QLIBC_PRI16 "d"
#define SCNi16 __QLIBC_PRI16 "i"
#define SCNo16 __QLIBC_PRI16 "o"
#define SCNu16 __QLIBC_PRI16 "u"
#define SCNx16 __QLIBC_PRI16 "x"
#endif

#ifdef __INT32_TYPE__
#define PRId32 __QLIBC_PRI32 "d"
#define PRIi32 __QLIBC_PRI32 "i"
#define PRIo32 __QLIBC_PRI32 "o"
#define PRIu32 __QLIBC_PRI32 "u"
#define PRIx32 __QLIBC_PRI32 "x"
#define PRIX32 __QLIBC_PRI32 "X"
#define SCNd32 __QLIBC_PRI32 "d"
#define SCNi32 __QLIBC_PRI32 "i"
#define SCNo32 __QLIBC_PRI32 "o"
#define SCNu32 __QLIBC_PRI32 "u"
#define SCNx32 __QLIBC_PRI32 "x"
#endif

#ifdef __INT64_TYPE__
#define PRId64 __QLIBC_PRI64 "d"
#define PRIi64 __QLIBC_PRI64 "i"
#define PRIo64 __QLIBC_PRI64 "o"
#define PRIu64 __QLIBC_PRI64 "u"
#define PRIx64 __QLIBC_PRI64 "x"
#define PRIX64 __QLIBC_PRI64 "X"
#define SCNd64 __QLIBC_PRI64 "d"
#define SCNi64 __QLIBC_PRI64 "i"
#define SCNo64 __QLIBC_PRI64 "o"
#define SCNu64 __QLIBC_PRI64 "u"
#define SCNx64 __QLIBC_PRI64 "x"
#endif

#define PRIdLEAST8 __QLIBC_PRI_LEAST8 "d"
#define PRIiLEAST8 __QLIBC_PRI_LEAST8 "i"
#define PRIoLEAST8 __QLIBC_PRI_LEAST8 "o"
#define PRIuLEAST8 __QLIBC_PRI_LEAST8 "u"
#define PRIxLEAST8 __QLIBC_PRI_LEAST8 "x"
#define PRIXLEAST8 __QLIBC_PRI_LEAST8 "X"
#define SCNdLEAST8 __QLIBC_PRI_LEAST8 "d"
#define SCNiLEAST8 __QLIBC_PRI_LEAST8 "i"
#define SCNoLEAST8 __QLIBC_PRI_LEAST8 "o"
#define SCNuLEAST8 __QLIBC_PRI_LEAST8 "u"
#define SCNxLEAST8 __QLIBC_PRI_LEAST8 "x"

#define PRIdLEAST16 __QLIBC_PRI_LEAST16 "d"
#define PRIiLEAST16 __QLIBC_PRI_LEAST16 "i"
#define PRIoLEAST16 __QLIBC_PRI_LEAST16 "o"
#define PRIuLEAST16 __QLIBC_PRI_LEAST16 "u"
#define PRIxLEAST16 __QLIBC_PRI_LEAST16 "x"
#define PRIXLEAST16 __QLIBC_PRI_LEAST16 "X"
#define SCNdLEAST16 __QLIBC_PRI_LEAST16 "d"
#define SCNiLEAST16 __QLIBC_PRI_LEAST16 "i"
#define SCNoLEAST16 __QLIBC_PRI_LEAST16 "o"
#define SCNuLEAST16 __QLIBC_PRI_LEAST16 "u"
#define SCNxLEAST16 __QLIBC_PRI_LEAST16 "x"

#define PRIdLEAST32 __QLIBC_PRI_LEAST32 "d"
#define PRIiLEAST32 __QLIBC_PRI_LEAST32 "i"
#define PRIoLEAST32 __QLIBC_PRI_LEAST32 "o"
#define PRIuLEAST32 __QLIBC_PRI_LEAST32 "u"
#define PRIxLEAST32 __QLIBC_PRI_LEAST32 "x"
#define PRIXLEAST32 __QLIBC_PRI_LEAST32 "X"
#define SCNdLEAST32 __QLIBC_PRI_LEAST32 "d"
#define SCNiLEAST32 __QLIBC_PRI_LEAST32 "i"
#define SCNoLEAST32 __QLIBC_PRI_LEAST32 "o"
#define SCNuLEAST32 __QLIBC_PRI_LEAST32 "u"
#define SCNxLEAST32 __QLIBC_PRI_LEAST32 "x"

#define PRIdLEAST64 __QLIBC_PRI_LEAST64 "d"
#define PRIiLEAST64 __QLIBC_PRI_LEAST64 "i"
#define PRIoLEAST64 __QLIBC_PRI_LEAST64 "o"
#define PRIuLEAST64 __QLIBC_PRI_LEAST64 "u"
#define PRIxLEAST64 __QLIBC_PRI_LEAST64 "x"
#define PRIXLEAST64 __QLIBC_PRI_LEAST64 "X"
#define SCNdLEAST64 __QLIBC_PRI_LEAST64 "d"
#define SCNiLEAST64 __QLIBC_PRI_LEAST64 "i"
#define SCNoLEAST64 __QLIBC_PRI_LEAST64 "o"
#define SCNuLEAST64 __QLIBC_PRI_LEAST64 "u"
#define SCNxLEAST64 __QLIBC_PRI_LEAST64 "x"

#define PRIdFAST8 __QLIBC_PRI_FAST8 "d"
#define PRIiFAST8 __QLIBC_PRI_FAST8 "i"
#define PRIoFAST8 __QLIBC_PRI_FAST8 "o"
#define PRIuFAST8 __QLIBC_PRI_FAST8 "u"
#define PRIxFAST8 __QLIBC_PRI_FAST8 "x"
#define PRIXFAST8 __QLIBC_PRI_FAST8 "X"
#define SCNdFAST8 __QLIBC_PRI_FAST8 "d"
#define SCNiFAST8 __QLIBC_PRI_FAST8 "i"
#define SCNoFAST8 __QLIBC_PRI_FAST8 "o"
#define SCNuFAST8 __QLIBC_PRI_FAST8 "u"
#define SCNxFAST8 __QLIBC_PRI_FAST8 "x"

#define PRIdFAST16 __QLIBC_PRI_FAST16 "d"
#define PRIiFAST16 __QLIBC_PRI_FAST16 "i"
#define PRIoFAST16 __QLIBC_PRI_FAST16 "o"
#define PRIuFAST16 __QLIBC_PRI_FAST16 "u"
#define PRIxFAST16 __QLIBC_PRI_FAST16 "x"
#define PRIXFAST16 __QLIBC_PRI_FAST16 "X"
#define SCNdFAST16 __QLIBC_PRI_FAST16 "d"
#define SCNiFAST16 __QLIBC_PRI_FAST16 "i"
#define SCNoFAST16 __QLIBC_PRI_FAST16 "o"
#define SCNuFAST16 __QLIBC_PRI_FAST16 "u"
#define SCNxFAST16 __QLIBC_PRI_FAST16 "x"

#define PRIdFAST32 __QLIBC_PRI_FAST32 "d"
#define PRIiFAST32 __QLIBC_PRI_FAST32 "i"
#define PRIoFAST32 __QLIBC_PRI_FAST32 "o"
#define PRIuFAST32 __QLIBC_PRI_FAST32 "u"
#define PRIxFAST32 __QLIBC_PRI_FAST32 "x"
#define PRIXFAST32 __QLIBC_PRI_FAST32 "X"
#define SCNdFAST32 __QLIBC_PRI_FAST32 "d"
#define SCNiFAST32 __QLIBC_PRI_FAST32 "i"
#define SCNoFAST32 __QLIBC_PRI_FAST32 "o"
#define SCNuFAST32 __QLIBC_PRI_FAST32 "u"
#define SCNxFAST32 __QLIBC_PRI_FAST32 "x"

#define PRIdFAST64 __QLIBC_PRI_FAST64 "d"
#define PRIiFAST64 __QLIBC_PRI_FAST64 "i"
#define PRIoFAST64 __QLIBC_PRI_FAST64 "o"
#define PRIuFAST64 __QLIBC_PRI_FAST64 "u"
#define PRIxFAST64 __QLIBC_PRI_FAST64 "x"
#define PRIXFAST64 __QLIBC_PRI_FAST64 "X"
#define SCNdFAST64 __QLIBC_PRI_FAST64 "d"
#define SCNiFAST64 __QLIBC_PRI_FAST64 "i"
#define SCNoFAST64 __QLIBC_PRI_FAST64 "o"
#define SCNuFAST64 __QLIBC_PRI_FAST64 "u"
#define SCNxFAST64 __QLIBC_PRI_FAST64 "x"

#define PRIdMAX __QLIBC_PRIMAX "d"
#define PRIiMAX __QLIBC_PRIMAX "i"
#define PRIoMAX __QLIBC_PRIMAX "o"
#define PRIuMAX __QLIBC_PRIMAX "u"
#define PRIxMAX __QLIBC_PRIMAX "x"
#define PRIXMAX __QLIBC_PRIMAX "X"
#define SCNdMAX __QLIBC_PRIMAX "d"
#define SCNiMAX __QLIBC_PRIMAX "i"
#define SCNoMAX __QLIBC_PRIMAX "o"
#define SCNuMAX __QLIBC_PRIMAX "u"
#define SCNxMAX __QLIBC_PRIMAX "x"

#ifdef __INTPTR_TYPE__
#define PRIdPTR __QLIBC_PRIPTR "d"
#define PRIiPTR __QLIBC_PRIPTR "i"
#define PRIoPTR __QLIBC_PRIPTR "o"
#define PRIuPTR __QLIBC_PRIPTR "u"
#define PRIxPTR __QLIBC_PRIPTR "x"
#define PRIXPTR __QLIBC_PRIPTR "X"
#define SCNdPTR __QLIBC_PRIPTR "d"
#define SCNiPTR __QLIBC_PRIPTR "i"
#define SCNoPTR __QLIBC_PRIPTR "o"
#define SCNuPTR __QLIBC_PRIPTR "u"
#define SCNxPTR __QLIBC_PRIPTR "x"
#endif

typedef struct {
    intmax_t quot;
    intmax_t rem;
} imaxdiv_t;

#ifdef __cplusplus
extern "C" {
#endif

extern intmax_t imaxabs(intmax_t n);
extern imaxdiv_t imaxdiv(intmax_t x, intmax_t y);
extern intmax_t strtoimax(const char *__restrict str, char **__restrict str_end,
                          int base);
extern uintmax_t strtoumax(const char *__restrict str,
                           char **__restrict str_end, int base);

#ifdef __cplusplus
}
#endif

#endif /* _QLIBC_INTTYPES_H_ */
