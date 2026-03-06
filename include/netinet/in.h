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

#ifndef _NETINET_IN_H_
#define _NETINET_IN_H_ 1

#include <stdint.h>

typedef uint16_t in_port_t;
typedef uint32_t in_addr_t;

/* IPv4 address */
struct in_addr {
  in_addr_t s_addr;
};

/* IPv6 address */
struct in6_addr {
  union {
    uint8_t __s6_addr[16];
    uint16_t __s6_addr16[8];
    uint32_t __s6_addr32[4];
  } __in6_union;
};
#define s6_addr __in6_union.__s6_addr
#define s6_addr16 __in6_union.__s6_addr16
#define s6_addr32 __in6_union.__s6_addr32

#endif