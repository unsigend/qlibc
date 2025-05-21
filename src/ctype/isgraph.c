#include <ctype.h>

int isgraph(int c){
    return (unsigned)c <= 0x7e && (unsigned)c >= 0x21;
}