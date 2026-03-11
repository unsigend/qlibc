#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include <signal.h>
#include <string.h>
#include <utest.h>

UTEST_TEST_CASE(types)
{
  EXPECT_EQUAL_UINT(sizeof(sig_atomic_t), sizeof(int));
#if defined(_QLIBC_SOURCE) || defined(__QLIBC__)
  EXPECT_EQUAL_UINT(sizeof(sighandler_t), sizeof(void *));
#elif defined(__GNUC__)
  EXPECT_EQUAL_UINT(sizeof(__sighandler_t), sizeof(void *));
#endif
}

UTEST_TEST_CASE(macros)
{
  EXPECT_EQUAL_INT(SIG_DFL, 0);
  EXPECT_EQUAL_INT(SIG_IGN, 1);
  EXPECT_EQUAL_INT(SIG_ERR, -1);

  EXPECT_EQUAL_INT(SIGHUP, 1);
  EXPECT_EQUAL_INT(SIGINT, 2);
  EXPECT_EQUAL_INT(SIGQUIT, 3);
  EXPECT_EQUAL_INT(SIGILL, 4);
  EXPECT_EQUAL_INT(SIGTRAP, 5);
  EXPECT_EQUAL_INT(SIGABRT, 6);
  EXPECT_EQUAL_INT(SIGBUS, 7);
  EXPECT_EQUAL_INT(SIGFPE, 8);
  EXPECT_EQUAL_INT(SIGKILL, 9);
  EXPECT_EQUAL_INT(SIGUSR1, 10);
  EXPECT_EQUAL_INT(SIGSEGV, 11);
  EXPECT_EQUAL_INT(SIGUSR2, 12);
  EXPECT_EQUAL_INT(SIGPIPE, 13);
  EXPECT_EQUAL_INT(SIGALRM, 14);
  EXPECT_EQUAL_INT(SIGTERM, 15);
  EXPECT_EQUAL_INT(SIGSTKFLT, 16);
  EXPECT_EQUAL_INT(SIGCHLD, 17);
  EXPECT_EQUAL_INT(SIGCONT, 18);
  EXPECT_EQUAL_INT(SIGSTOP, 19);
  EXPECT_EQUAL_INT(SIGTSTP, 20);
  EXPECT_EQUAL_INT(SIGTTIN, 21);
  EXPECT_EQUAL_INT(SIGTTOU, 22);
  EXPECT_EQUAL_INT(SIGURG, 23);
  EXPECT_EQUAL_INT(SIGXCPU, 24);
  EXPECT_EQUAL_INT(SIGXFSZ, 25);
  EXPECT_EQUAL_INT(SIGVTALRM, 26);
  EXPECT_EQUAL_INT(SIGPROF, 27);
  EXPECT_EQUAL_INT(SIGWINCH, 28);
  EXPECT_EQUAL_INT(SIGIO, 29);
  EXPECT_EQUAL_INT(SIGPWR, 30);
  EXPECT_EQUAL_INT(SIGSYS, 31);

  EXPECT_EQUAL_INT(SIG_BLOCK, 0);
  EXPECT_EQUAL_INT(SIG_UNBLOCK, 1);
  EXPECT_EQUAL_INT(SIG_SETMASK, 2);

  EXPECT_EQUAL_INT(SA_NOCLDSTOP, 1);
  EXPECT_EQUAL_INT(SA_NOCLDWAIT, 2);
  EXPECT_EQUAL_INT(SA_NODEFER, 0x40000000);
  EXPECT_EQUAL_INT(SA_RESETHAND, 0x80000000);
  EXPECT_EQUAL_INT(SA_RESTART, 0x10000000);
  EXPECT_EQUAL_INT(SA_SIGINFO, 4);
}

UTEST_TEST_CASE(sigemptyset)
{
  sigset_t set;
  EXPECT_EQUAL_INT(sigemptyset(&set), 0);
  EXPECT_TRUE(sigisemptyset(&set));
  EXPECT_FALSE(sigismember(&set, SIGINT));
  EXPECT_FALSE(sigismember(&set, 1));
}

UTEST_TEST_CASE(sigfillset)
{
  sigset_t set;
  EXPECT_EQUAL_INT(sigfillset(&set), 0);
  EXPECT_FALSE(sigisemptyset(&set));
  EXPECT_EQUAL_INT(sigismember(&set, SIGINT), 1);
  EXPECT_TRUE(sigismember(&set, SIGTERM));
  EXPECT_TRUE(sigismember(&set, 1));
}

UTEST_TEST_CASE(sigaddset)
{
  sigset_t set;
  sigemptyset(&set);
  EXPECT_EQUAL_INT(sigaddset(&set, SIGINT), 0);
  EXPECT_TRUE(sigismember(&set, SIGINT));
  EXPECT_FALSE(sigismember(&set, SIGTERM));
  EXPECT_EQUAL_INT(sigaddset(&set, SIGTERM), 0);
  EXPECT_TRUE(sigismember(&set, SIGTERM));
}

UTEST_TEST_CASE(sigdelset)
{
  sigset_t set;
  sigfillset(&set);
  EXPECT_EQUAL_INT(sigdelset(&set, SIGINT), 0);
  EXPECT_FALSE(sigismember(&set, SIGINT));
  EXPECT_TRUE(sigismember(&set, SIGTERM));
  EXPECT_EQUAL_INT(sigdelset(&set, SIGTERM), 0);
  EXPECT_FALSE(sigismember(&set, SIGTERM));
}

UTEST_TEST_CASE(sigismember)
{
  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, SIGUSR1);
  EXPECT_TRUE(sigismember(&set, SIGUSR1));
  EXPECT_FALSE(sigismember(&set, SIGUSR2));
  EXPECT_FALSE(sigismember(&set, 1));
  EXPECT_EQUAL_INT(sigismember(NULL, SIGINT), -1);
}

UTEST_TEST_CASE(sigandset)
{
  sigset_t left, right, dest;
  sigemptyset(&left);
  sigemptyset(&right);
  sigaddset(&left, SIGINT);
  sigaddset(&left, SIGTERM);
  sigaddset(&right, SIGINT);
  EXPECT_EQUAL_INT(sigandset(&dest, &left, &right), 0);
  EXPECT_TRUE(sigismember(&dest, SIGINT));
  EXPECT_FALSE(sigismember(&dest, SIGTERM));
}

UTEST_TEST_CASE(sigorset)
{
  sigset_t left, right, dest;
  sigemptyset(&left);
  sigemptyset(&right);
  sigaddset(&left, SIGINT);
  sigaddset(&right, SIGTERM);
  EXPECT_EQUAL_INT(sigorset(&dest, &left, &right), 0);
  EXPECT_TRUE(sigismember(&dest, SIGINT));
  EXPECT_TRUE(sigismember(&dest, SIGTERM));
}

UTEST_TEST_CASE(sigisemptyset)
{
  sigset_t set;
  sigemptyset(&set);
  EXPECT_TRUE(sigisemptyset(&set));
  sigaddset(&set, SIGINT);
  EXPECT_FALSE(sigisemptyset(&set));
  EXPECT_EQUAL_INT(sigisemptyset(NULL), -1);
}

UTEST_TEST_CASE(sigpending)
{
  sigset_t set;
  EXPECT_EQUAL_INT(sigpending(&set), 0);
  EXPECT_EQUAL_INT(sigpending(NULL), -1);
}

UTEST_TEST_CASE(strsignal)
{
  EXPECT_EQUAL_STRING(strsignal(0), "Unknown signal 0");
  EXPECT_EQUAL_STRING(strsignal(SIGHUP), "Hangup");
  EXPECT_EQUAL_STRING(strsignal(SIGINT), "Interrupt");
  EXPECT_EQUAL_STRING(strsignal(SIGQUIT), "Quit");
  EXPECT_EQUAL_STRING(strsignal(SIGILL), "Illegal instruction");
  EXPECT_EQUAL_STRING(strsignal(SIGTRAP), "Trace/breakpoint trap");
  EXPECT_EQUAL_STRING(strsignal(SIGABRT), "Aborted");
  EXPECT_EQUAL_STRING(strsignal(SIGBUS), "Bus error");
  EXPECT_EQUAL_STRING(strsignal(SIGFPE), "Floating point exception");
  EXPECT_EQUAL_STRING(strsignal(SIGKILL), "Killed");
  EXPECT_EQUAL_STRING(strsignal(SIGUSR1), "User defined signal 1");
  EXPECT_EQUAL_STRING(strsignal(SIGSEGV), "Segmentation fault");
  EXPECT_EQUAL_STRING(strsignal(SIGUSR2), "User defined signal 2");
  EXPECT_EQUAL_STRING(strsignal(SIGPIPE), "Broken pipe");
  EXPECT_EQUAL_STRING(strsignal(SIGALRM), "Alarm clock");
  EXPECT_EQUAL_STRING(strsignal(SIGTERM), "Terminated");
  EXPECT_EQUAL_STRING(strsignal(SIGSTKFLT), "Stack fault");
  EXPECT_EQUAL_STRING(strsignal(SIGCHLD), "Child exited");
  EXPECT_EQUAL_STRING(strsignal(SIGCONT), "Continued");
  EXPECT_EQUAL_STRING(strsignal(SIGSTOP), "Stopped (signal)");
  EXPECT_EQUAL_STRING(strsignal(SIGTSTP), "Stopped");
  EXPECT_EQUAL_STRING(strsignal(SIGTTIN), "Stopped (tty input)");
  EXPECT_EQUAL_STRING(strsignal(SIGTTOU), "Stopped (tty output)");
  EXPECT_EQUAL_STRING(strsignal(SIGURG), "Urgent I/O condition");
  EXPECT_EQUAL_STRING(strsignal(SIGXCPU), "CPU time limit exceeded");
  EXPECT_EQUAL_STRING(strsignal(SIGXFSZ), "File size limit exceeded");
  EXPECT_EQUAL_STRING(strsignal(SIGVTALRM), "Virtual timer expired");
  EXPECT_EQUAL_STRING(strsignal(SIGPROF), "Profiling timer expired");
  EXPECT_EQUAL_STRING(strsignal(SIGWINCH), "Window changed");
  EXPECT_EQUAL_STRING(strsignal(SIGIO), "I/O possible");
  EXPECT_EQUAL_STRING(strsignal(SIGPWR), "Power failure");
  EXPECT_EQUAL_STRING(strsignal(SIGSYS), "Bad system call");
  EXPECT_EQUAL_STRING(strsignal(32), "Unknown signal 32");
  EXPECT_EQUAL_STRING(strsignal(-1), "Unknown signal -1");
  EXPECT_EQUAL_STRING(strsignal(100), "Unknown signal 100");
  EXPECT_EQUAL_STRING(strsignal(999999999), "Unknown signal 999999999");
}

UTEST_TEST_SUITE(signal)
{
  UTEST_RUN_TEST_CASE(types);
  UTEST_RUN_TEST_CASE(macros);
  UTEST_RUN_TEST_CASE(sigemptyset);
  UTEST_RUN_TEST_CASE(sigfillset);
  UTEST_RUN_TEST_CASE(sigaddset);
  UTEST_RUN_TEST_CASE(sigdelset);
  UTEST_RUN_TEST_CASE(sigismember);
  UTEST_RUN_TEST_CASE(sigandset);
  UTEST_RUN_TEST_CASE(sigorset);
  UTEST_RUN_TEST_CASE(sigisemptyset);
  UTEST_RUN_TEST_CASE(sigpending);
  UTEST_RUN_TEST_CASE(strsignal);
}