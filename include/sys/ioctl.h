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

#ifndef _QLIBC_SYS_IOCTL_H_
#define _QLIBC_SYS_IOCTL_H_

#include <feature.h>

#define TCGETS 0x5401  /* get termios */
#define TCSETS 0x5402  /* set termios */
#define TCSETSW 0x5403 /* set termios after drain */
#define TCSETSF 0x5404 /* set termios after flush */
#define TCGETA 0x5405  /* get termio */
#define TCSETA 0x5406  /* set termio */
#define TCSETAW 0x5407 /* set termio after drain */
#define TCSETAF 0x5408 /* set termio after flush */
#define TCSBRK 0x5409  /* send break */
#define TCXONC 0x540A  /* flow control */
#define TCFLSH 0x540B  /* flush queues */

#define TIOCEXCL 0x540C     /* exclusive mode */
#define TIOCNXCL 0x540D     /* drop exclusive mode */
#define TIOCSCTTY 0x540E    /* set controlling tty */
#define TIOCGPGRP 0x540F    /* get foreground pgrp */
#define TIOCSPGRP 0x5410    /* set foreground pgrp */
#define TIOCOUTQ 0x5411     /* output queue size */
#define TIOCSTI 0x5412      /* simulate input */
#define TIOCGWINSZ 0x5413   /* get window size */
#define TIOCSWINSZ 0x5414   /* set window size */
#define TIOCMGET 0x5415     /* get modem bits */
#define TIOCMBIS 0x5416     /* set modem bits */
#define TIOCMBIC 0x5417     /* clear modem bits */
#define TIOCMSET 0x5418     /* set all modem bits */
#define TIOCGSOFTCAR 0x5419 /* get soft carrier */
#define TIOCSSOFTCAR 0x541A /* set soft carrier */
#define FIONREAD 0x541B     /* bytes readable */
#define TIOCINQ FIONREAD
#define TIOCLINUX 0x541C      /* linux-specific tty */
#define TIOCCONS 0x541D       /* redirect console */
#define TIOCGSERIAL 0x541E    /* get serial config */
#define TIOCSSERIAL 0x541F    /* set serial config */
#define TIOCPKT 0x5420        /* packet mode */
#define FIONBIO 0x5421        /* non-blocking I/O */
#define TIOCNOTTY 0x5422      /* detach controlling tty */
#define TIOCSETD 0x5423       /* set line discipline */
#define TIOCGETD 0x5424       /* get line discipline */
#define TCSBRKP 0x5425        /* posix break */
#define TIOCTTYGSTRUCT 0x5426 /* get tty structure */
#define TIOCSBRK 0x5427       /* set break */
#define TIOCCBRK 0x5428       /* clear break */
#define TIOCGSID 0x5429       /* get session id */
#define TIOCGPTN 0x80045430   /* get pty number */
#define TIOCSPTLCK 0x40045431 /* lock/unlock pty */
#define TCGETX 0x5432         /* get termiox */
#define TCSETX 0x5433         /* set termiox */
#define TCSETXF 0x5434        /* set termiox after flush */
#define TCSETXW 0x5435        /* set termiox after drain */

#define FIONCLEX 0x5450        /* clear close-on-exec */
#define FIOCLEX 0x5451         /* set close-on-exec */
#define FIOASYNC 0x5452        /* async I/O */
#define TIOCSERCONFIG 0x5453   /* autoconfigure serial */
#define TIOCSERGWILD 0x5454    /* get wildcard */
#define TIOCSERSWILD 0x5455    /* set wildcard */
#define TIOCGLCKTRMIOS 0x5456  /* get locked termios */
#define TIOCSLCKTRMIOS 0x5457  /* set locked termios */
#define TIOCSERGSTRUCT 0x5458  /* get serial structure */
#define TIOCSERGETLSR 0x5459   /* get line status */
#define TIOCSERGETMULTI 0x545A /* get multiport */
#define TIOCSERSETMULTI 0x545B /* set multiport */
#define TIOCMIWAIT 0x545C      /* wait for modem input */
#define TIOCGICOUNT 0x545D     /* get interrupt counts */
#define TIOCGHAYESESP 0x545E   /* get hayes esp */
#define TIOCSHAYESESP 0x545F   /* set hayes esp */
#define FIOQSIZE 0x5460        /* file/queue size */

#define TIOCPKT_DATA 0
#define TIOCPKT_FLUSHREAD 1
#define TIOCPKT_FLUSHWRITE 2
#define TIOCPKT_STOP 4
#define TIOCPKT_START 8
#define TIOCPKT_NOSTOP 16
#define TIOCPKT_DOSTOP 32
#define TIOCPKT_IOCTL 64

#define TIOCSER_TEMT 0x01 /* transmitter empty */

#ifdef __cplusplus
extern "C" {
#endif

extern int ioctl(int fildes, unsigned long request, ...);

#ifdef __cplusplus
}
#endif

#endif /* _QLIBC_SYS_IOCTL_H_ */
