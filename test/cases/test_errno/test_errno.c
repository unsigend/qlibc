#include <utest.h>
#include <errno.h>

UTEST_TEST_CASE(value){
    EXPECT_EQUAL_INT(errno, 0);
    errno = 1;
    EXPECT_EQUAL_INT(errno, 1);
    errno = 0;
    EXPECT_EQUAL_INT(errno, 0);
    errno = -1;
    EXPECT_EQUAL_INT(errno, -1);
    errno = 1234567890;
    EXPECT_EQUAL_INT(errno, 1234567890);
    errno = 0;
}

#if defined(__aarch64__)
UTEST_TEST_CASE(macro){
    EXPECT_EQUAL_INT(EPERM, 1);
    EXPECT_EQUAL_INT(ENOENT, 2);
    EXPECT_EQUAL_INT(ESRCH, 3);
    EXPECT_EQUAL_INT(EINTR, 4);
    EXPECT_EQUAL_INT(EIO, 5);
    EXPECT_EQUAL_INT(ENXIO, 6);
    EXPECT_EQUAL_INT(E2BIG, 7);
    EXPECT_EQUAL_INT(ENOEXEC, 8);
    EXPECT_EQUAL_INT(EBADF, 9);
    EXPECT_EQUAL_INT(ECHILD, 10);
    EXPECT_EQUAL_INT(EDEADLK, 11);
    EXPECT_EQUAL_INT(ENOMEM, 12);
    EXPECT_EQUAL_INT(EACCES, 13);
    EXPECT_EQUAL_INT(EFAULT, 14);
    EXPECT_EQUAL_INT(ENOTBLK, 15);
    EXPECT_EQUAL_INT(EBUSY, 16);
    EXPECT_EQUAL_INT(EEXIST, 17);
    EXPECT_EQUAL_INT(EXDEV, 18);
    EXPECT_EQUAL_INT(ENODEV, 19);
    EXPECT_EQUAL_INT(ENOTDIR, 20);
    EXPECT_EQUAL_INT(EISDIR, 21);
    EXPECT_EQUAL_INT(EINVAL, 22);
    EXPECT_EQUAL_INT(ENFILE, 23);
    EXPECT_EQUAL_INT(EMFILE, 24);
    EXPECT_EQUAL_INT(ENOTTY, 25);
    EXPECT_EQUAL_INT(ETXTBSY, 26);
    EXPECT_EQUAL_INT(EFBIG, 27);
    EXPECT_EQUAL_INT(ENOSPC, 28);
    EXPECT_EQUAL_INT(ESPIPE, 29);
    EXPECT_EQUAL_INT(EROFS, 30);
    EXPECT_EQUAL_INT(EMLINK, 31);
    EXPECT_EQUAL_INT(EPIPE, 32);
    EXPECT_EQUAL_INT(EDOM, 33);
    EXPECT_EQUAL_INT(ERANGE, 34);
    EXPECT_EQUAL_INT(EAGAIN, 35);
    EXPECT_EQUAL_INT(EINPROGRESS, 36);
    EXPECT_EQUAL_INT(EALREADY, 37);
    EXPECT_EQUAL_INT(ENOTSOCK, 38);
    EXPECT_EQUAL_INT(EDESTADDRREQ, 39);
    EXPECT_EQUAL_INT(EMSGSIZE, 40);
    EXPECT_EQUAL_INT(EPROTOTYPE, 41);
    EXPECT_EQUAL_INT(ENOPROTOOPT, 42);
    EXPECT_EQUAL_INT(EPROTONOSUPPORT, 43);
    EXPECT_EQUAL_INT(ESOCKTNOSUPPORT, 44);
    EXPECT_EQUAL_INT(ENOTSUP, 45);
    EXPECT_EQUAL_INT(EPFNOSUPPORT, 46);
    EXPECT_EQUAL_INT(EAFNOSUPPORT, 47);
    EXPECT_EQUAL_INT(EADDRINUSE, 48);
    EXPECT_EQUAL_INT(EADDRNOTAVAIL, 49);
    EXPECT_EQUAL_INT(ENETDOWN, 50);
    EXPECT_EQUAL_INT(ENETUNREACH, 51);
    EXPECT_EQUAL_INT(ENETRESET, 52);
    EXPECT_EQUAL_INT(ECONNABORTED, 53);
    EXPECT_EQUAL_INT(ECONNRESET, 54);
    EXPECT_EQUAL_INT(ENOBUFS, 55);
    EXPECT_EQUAL_INT(EISCONN, 56);
    EXPECT_EQUAL_INT(ENOTCONN, 57);
    EXPECT_EQUAL_INT(ESHUTDOWN, 58);
    EXPECT_EQUAL_INT(ETOOMANYREFS, 59);
    EXPECT_EQUAL_INT(ETIMEDOUT, 60);
    EXPECT_EQUAL_INT(ECONNREFUSED, 61);
    EXPECT_EQUAL_INT(ELOOP, 62);
    EXPECT_EQUAL_INT(ENAMETOOLONG, 63);
    EXPECT_EQUAL_INT(EHOSTDOWN, 64);
    EXPECT_EQUAL_INT(EHOSTUNREACH, 65);
    EXPECT_EQUAL_INT(ENOTEMPTY, 66);
    EXPECT_EQUAL_INT(EPROCLIM, 67);
    EXPECT_EQUAL_INT(EUSERS, 68);
    EXPECT_EQUAL_INT(EDQUOT, 69);
    EXPECT_EQUAL_INT(ESTALE, 70);
    EXPECT_EQUAL_INT(EREMOTE, 71);
    EXPECT_EQUAL_INT(EBADRPC, 72);
    EXPECT_EQUAL_INT(ERPCMISMATCH, 73);
    EXPECT_EQUAL_INT(EPROGUNAVAIL, 74);
    EXPECT_EQUAL_INT(EPROGMISMATCH, 75);
    EXPECT_EQUAL_INT(EPROCUNAVAIL, 76);
    EXPECT_EQUAL_INT(ENOLCK, 77);
    EXPECT_EQUAL_INT(ENOSYS, 78);
    EXPECT_EQUAL_INT(EFTYPE, 79);
    EXPECT_EQUAL_INT(EAUTH, 80);
    EXPECT_EQUAL_INT(ENEEDAUTH, 81);
    EXPECT_EQUAL_INT(EILSEQ, 92);
}
#endif

#if defined(__x86_64__) || defined(__i386__)
UTEST_TEST_CASE(macro){
    EXPECT_EQUAL_INT(EPERM, 1);
    EXPECT_EQUAL_INT(ENOENT, 2);
    EXPECT_EQUAL_INT(ESRCH, 3);
    EXPECT_EQUAL_INT(EINTR, 4);
    EXPECT_EQUAL_INT(EIO, 5);
    EXPECT_EQUAL_INT(ENXIO, 6);
    EXPECT_EQUAL_INT(E2BIG, 7);
    EXPECT_EQUAL_INT(ENOEXEC, 8);
    EXPECT_EQUAL_INT(EBADF, 9);
    EXPECT_EQUAL_INT(ECHILD, 10);
    EXPECT_EQUAL_INT(EAGAIN, 11);
    EXPECT_EQUAL_INT(ENOMEM, 12);
    EXPECT_EQUAL_INT(EACCES, 13);
    EXPECT_EQUAL_INT(EFAULT, 14);
    EXPECT_EQUAL_INT(ENOTBLK, 15);
    EXPECT_EQUAL_INT(EBUSY, 16);
    EXPECT_EQUAL_INT(EEXIST, 17);
    EXPECT_EQUAL_INT(EXDEV, 18);
    EXPECT_EQUAL_INT(ENODEV, 19);
    EXPECT_EQUAL_INT(ENOTDIR, 20);
    EXPECT_EQUAL_INT(EISDIR, 21);
    EXPECT_EQUAL_INT(EINVAL, 22);
    EXPECT_EQUAL_INT(ENFILE, 23);
    EXPECT_EQUAL_INT(EMFILE, 24);
    EXPECT_EQUAL_INT(ENOTTY, 25);
    EXPECT_EQUAL_INT(ETXTBSY, 26);
    EXPECT_EQUAL_INT(EFBIG, 27);
    EXPECT_EQUAL_INT(ENOSPC, 28);
    EXPECT_EQUAL_INT(ESPIPE, 29);
    EXPECT_EQUAL_INT(EROFS, 30);
    EXPECT_EQUAL_INT(EMLINK, 31);
    EXPECT_EQUAL_INT(EPIPE, 32);
    EXPECT_EQUAL_INT(EDOM, 33);
    EXPECT_EQUAL_INT(ERANGE, 34);
    EXPECT_EQUAL_INT(EDEADLK, 35);
    EXPECT_EQUAL_INT(ENAMETOOLONG, 36);
    EXPECT_EQUAL_INT(ENOLCK, 37);
    EXPECT_EQUAL_INT(ENOSYS, 38);
    EXPECT_EQUAL_INT(ENOTEMPTY, 39);
    EXPECT_EQUAL_INT(ELOOP, 40);
    EXPECT_EQUAL_INT(EWOULDBLOCK, EAGAIN);
    EXPECT_EQUAL_INT(ENOMSG, 42);
    EXPECT_EQUAL_INT(EIDRM, 43);
    EXPECT_EQUAL_INT(ECHRNG, 44);
    EXPECT_EQUAL_INT(EL2NSYNC, 45);
    EXPECT_EQUAL_INT(EL3HLT, 46);
    EXPECT_EQUAL_INT(EL3RST, 47);
    EXPECT_EQUAL_INT(ELNRNG, 48);
    EXPECT_EQUAL_INT(EUNATCH, 49);
    EXPECT_EQUAL_INT(ENOCSI, 50);
    EXPECT_EQUAL_INT(EL2HLT, 51);
    EXPECT_EQUAL_INT(EBADE, 52);
    EXPECT_EQUAL_INT(EBADR, 53);
    EXPECT_EQUAL_INT(EXFULL, 54);
    EXPECT_EQUAL_INT(ENOANO, 55);
    EXPECT_EQUAL_INT(EBADRQC, 56);
    EXPECT_EQUAL_INT(EBADSLT, 57);
    EXPECT_EQUAL_INT(EILSEQ, 84);
}
#endif

#undef errno
UTEST_TEST_SUITE(errno){
    UTEST_RUN_TEST_CASE(value);
    UTEST_RUN_TEST_CASE(macro);
}