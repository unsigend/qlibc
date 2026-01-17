#include <utest.h>
#include <syscall.h>
#include <errno.h>

UTEST_TEST_CASE(syscall){
    long ret;
    
    ret = syscall(SYS_getpid);
    EXPECT_TRUE(ret > 0);
    
    ret = syscall(SYS_getuid);
    EXPECT_TRUE(ret >= 0);
    
    ret = syscall(SYS_getgid);
    EXPECT_TRUE(ret >= 0);
    
    ret = syscall(SYS_getppid);
    EXPECT_TRUE(ret > 0);
    
    errno = 0;
    ret = syscall(99999);
    EXPECT_EQUAL_INT(ret, -1);
    EXPECT_TRUE(errno != 0);
}