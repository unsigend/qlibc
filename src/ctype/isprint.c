#include <ctype.h>

int isprint(int c){
    return (unsigned)c <= 0x7e && (unsigned)c >= 0x20;
}