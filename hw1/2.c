#include <stdio.h>

int main(void) {
    char symbols[] = "@0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ#";
    char sym;
    int code;
    while ((sym = getchar()) != EOF) {
        for (int i = 0; i < 64; i++) {
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