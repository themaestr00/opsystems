#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum
{
    MASK_1 = 1 << 3,
    MASK_2 = 1 << 2,
    MAX_DECODED_ELEM = 63,
    NUM_ENCODE = 2 + '9' - '0',
    LOWCASE_ENCODE = NUM_ENCODE + 'z' - 'a' + 1
};

int
main(void)
{
    int cur_sym = 0;
    while ((cur_sym = getchar()) != EOF) {
        if (!(('0' <= cur_sym && cur_sym <= '9') || isalpha(cur_sym))) {
            continue;
        }
        if ('A' <= cur_sym && cur_sym <= 'Z') {
            cur_sym = LOWCASE_ENCODE + cur_sym - 'A';
        } else if ('a' <= cur_sym && cur_sym <= 'z') {
            cur_sym = NUM_ENCODE + cur_sym - 'a';
        } else if ('0' <= cur_sym && cur_sym <= '9') {
            cur_sym = cur_sym - '0' + 1;
        }
        cur_sym ^= MASK_1;
        cur_sym &= ~MASK_2;
        if (1 <= cur_sym && cur_sym < NUM_ENCODE) {
            cur_sym = '0' + cur_sym - 1;
        } else if (NUM_ENCODE <= cur_sym && cur_sym < LOWCASE_ENCODE) {
            cur_sym = 'a' + cur_sym - NUM_ENCODE;
        } else if (LOWCASE_ENCODE <= cur_sym && cur_sym < MAX_DECODED_ELEM) {
            cur_sym = 'A' + cur_sym - LOWCASE_ENCODE;
        } else if (cur_sym == 0) {
            cur_sym = '@';
        } else {
            cur_sym = '#';
        }
        putchar(cur_sym);
    }
    return 0;
}
