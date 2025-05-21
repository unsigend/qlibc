#include <ctype.h>

int iscntrl(int c){
    return (unsigned)c <= 0x1f || c == 0x7f;
}