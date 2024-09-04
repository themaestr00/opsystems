#include <stdio.h>

int
main(void)
{
    char symbols[] = "@0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ#";
    char sym;
    int code;
    while ((sym = getchar()) != EOF) {
        for (int i = 1; i < 63; i++) {
            if (sym == symbols[i]) {
                code = i & 0xFB;
                code ^= 0x8;
                putchar(symbols[code]);
                break;
            }
        }
    }
    return 0;
}
