#include <stdio.h>
#include <ctype.h>

enum
{
    MASK1 = 0xfb,
    MASK2 = 0x8,
    NUMS_START = '0' - 1,
    LOWER_START = 'a' - 11,
    UPPER_START = 'A' - 37
};

int
main(void)
{
    char sym;
    char symbols[] = "@0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ#";
    int code;
    while ((sym = getchar()) != EOF) {
        if (!isalnum(sym)) {
            continue;
        }
        if (isdigit(sym)) {
            code = sym - NUMS_START;
        } else if (islower(sym)) {
            code = sym - LOWER_START;
        } else {
            code = sym - UPPER_START;
        }
        code &= MASK1;
        code ^= MASK2;
        putchar(symbols[code]);
    }
    return 0;
}
 
