// /* qlibc - A light-weight and portable C standard library
//  * Copyright (C) 2025 Qiu Yixiang
//  *
//  * This program is free software: you can redistribute it and/or modify
//  * it under the terms of the GNU General Public License as published by
//  * the Free Software Foundation, either version 3 of the License, or
//  * (at your option) any later version.
//  *
//  * This program is distributed in the hope that it will be useful,
//  * but WITHOUT ANY WARRANTY; without even the implied warranty of
//  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  * GNU General Public License for more details.
//  *
//  * You should have received a copy of the GNU General Public License
//  * along with this program.  If not, see <https://www.gnu.org/licenses/>.
//  */

// #include <ctype.h>
// #include <errno.h>
// #include <stddef.h>

// #define BASE_AUTO 0
// #define BASE_BIN 2
// #define BASE_OCT 8
// #define BASE_DEC 10
// #define BASE_HEX 16
// #define BASE_MAX 36

// long strtol(const char* restrict str, char** restrict str_end, int base){
//     long r = 0;
//     long sign = 1;
//     int i = 0;
//     int any = 0;

//     // check base
//     if (base < BASE_AUTO || base == 1 || base > BASE_MAX){
//         errno = EINVAL;
//         if (str_end != NULL){
//             *str_end = (char *)str;
//         }
//         return 0;
//     }

//     // skip whitespace
//     while (isspace(str[i])) { ++i;}

//     if (str[i] == '-'){
//         sign = -1;
//         ++i;
//     }else if (str[i] == '+'){
//         ++i;
//     }

//     if (base == BASE_AUTO){
//         if (str[i] == '0'){
//             if (str[i + 1] == 'x' || str[i + 1] == 'X'){
//                 base = BASE_HEX;
//                 i += 2;
//             }else{
//                 base = BASE_OCT;
//                 ++i;
//             }
//         }else{
//             base = BASE_DEC;
//         }
//     }else{
//         if (base == BASE_HEX){
//             if (str[i] == '0' && tolower(str[i + 1]) == 'x'){
//                 i += 2;
//             }
//         }else if (base == BASE_OCT){
//             if (str[i] == '0'){
//                 ++i;
//             }
//         }
//     }

//     for (int c; isalnum(str[i]); ++i){
//         if (isdigit(str[i]))
//             c = str[i] - '0';
//         else
//             c = tolower(str[i]) - 'a' + 10;

//         if (c >= base)
//             break;
        
//         any = 1;
//         r = r * base + c;
//     }

//     if (str_end != NULL){
//         if (!any){
//             *str_end = (char *)str;
//         }else{
//             *str_end = (char *)str + i;
//         }
//     }
//     return r * sign;
// }