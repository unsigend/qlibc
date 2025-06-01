#include <utest.h>
#include <string.h>

UTEST_TEST_CASE(strlen) {
    const char str1[] = "Hello World";
    EXPECT_EQUAL_INT(strlen(str1), 11);

    const char str2[] = "";
    EXPECT_EQUAL_INT(strlen(str2), 0);

    const char str3[] = "\0";
    EXPECT_EQUAL_INT(strlen(str3), 0);

    const char str4[] = "Hello\0World";
    EXPECT_EQUAL_INT(strlen(str4), 5);

    const char str5[] = "Hello\n\t\r\v\fWorld";
    EXPECT_EQUAL_INT(strlen(str5), sizeof(str5) - 1);

    const char str7[] = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    EXPECT_EQUAL_INT(strlen(str7), 94);

    const char str8[] = "aaaaaaaaaaaaaaaaaaaa";
    EXPECT_EQUAL_INT(strlen(str8), 20);

    const char str9[] = "    ";
    EXPECT_EQUAL_INT(strlen(str9), 4);

    const char str10[] = "\t\t\t\t";
    EXPECT_EQUAL_INT(strlen(str10), 4);

    const char str11[] = "\n\n\n\n";
    EXPECT_EQUAL_INT(strlen(str11), 4);

    const char str12[] = " \t\n\r\v\f";
    EXPECT_EQUAL_INT(strlen(str12), 6);

    const char str13[] = "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F";
    EXPECT_EQUAL_INT(strlen(str13), 15);

    const char str14[] = "\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8A\x8B\x8C\x8D\x8E\x8F";
    EXPECT_EQUAL_INT(strlen(str14), 16);

    const char str15[] = "\xFF\xFF\xFF\xFF\xFF";
    EXPECT_EQUAL_INT(strlen(str15), 5);

    const char str16[] = "\x00\x00\x00\x00\x00";
    EXPECT_EQUAL_INT(strlen(str16), 0);

    const char str17[] = "\xAA\x55\xAA\x55\xAA\x55";
    EXPECT_EQUAL_INT(strlen(str17), 6);

    const char str18[] = "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
                         "\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F"
                         "\x20\x21\x22\x23\x24\x25\x26\x27\x28\x29\x2A\x2B\x2C\x2D\x2E\x2F"
                         "\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x3A\x3B\x3C\x3D\x3E\x3F"
                         "\x40\x41\x42\x43\x44\x45\x46\x47\x48\x49\x4A\x4B\x4C\x4D\x4E\x4F"
                         "\x50\x51\x52\x53\x54\x55\x56\x57\x58\x59\x5A\x5B\x5C\x5D\x5E\x5F"
                         "\x60\x61\x62\x63\x64\x65\x66\x67\x68\x69\x6A\x6B\x6C\x6D\x6E\x6F"
                         "\x70\x71\x72\x73\x74\x75\x76\x77\x78\x79\x7A\x7B\x7C\x7D\x7E\x7F"
                         "\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8A\x8B\x8C\x8D\x8E\x8F"
                         "\x90\x91\x92\x93\x94\x95\x96\x97\x98\x99\x9A\x9B\x9C\x9D\x9E\x9F"
                         "\xA0\xA1\xA2\xA3\xA4\xA5\xA6\xA7\xA8\xA9\xAA\xAB\xAC\xAD\xAE\xAF"
                         "\xB0\xB1\xB2\xB3\xB4\xB5\xB6\xB7\xB8\xB9\xBA\xBB\xBC\xBD\xBE\xBF"
                         "\xC0\xC1\xC2\xC3\xC4\xC5\xC6\xC7\xC8\xC9\xCA\xCB\xCC\xCD\xCE\xCF"
                         "\xD0\xD1\xD2\xD3\xD4\xD5\xD6\xD7\xD8\xD9\xDA\xDB\xDC\xDD\xDE\xDF"
                         "\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF"
                         "\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF7\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF";
    EXPECT_EQUAL_INT(strlen(str18), 0);

    const char str20[1024] = "a";
    memset((void*)str20, 'a', 1023);
    ((char*)str20)[1023] = '\0';
    EXPECT_EQUAL_INT(strlen(str20), 1023);

    const char str21[5] = {'\0'};
    EXPECT_EQUAL_INT(strlen(str21), 0);

    const char str22[5] = {'a', 'b', '\0', 'c', 'd'};
    EXPECT_EQUAL_INT(strlen(str22), 2);

    const char str23[] = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    EXPECT_EQUAL_INT(strlen(str23), 95);

    const char str24[] = "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
                         "\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F";
    EXPECT_EQUAL_INT(strlen(str24), 0); 

    const char str25[] = "Hello\x07World\x0A";
    EXPECT_EQUAL_INT(strlen(str25), 12);
}