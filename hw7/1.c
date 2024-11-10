#include <stdio.h>
#include <ctype.h>

enum
{
    WEIGHT = 3
};

void
shift_to_space(void)
{
    int c;
    while ((c = getchar()) != EOF && !isspace(c))
        ;
}

int
getnum(long long *buf)
{
    int c;
    *buf = 0;
    while ((c = getchar()) != EOF && isspace(c))
        ;
    if (c == EOF) {
        return 0;
    }
    while (c != EOF && !isspace(c)) {
        if (c == '0') {
            if (__builtin_mul_overflow(*buf, WEIGHT, buf)) {
                shift_to_space();
                return -1;
            }
        }
        if (c == '1') {
            if (*buf < 0) {
                if (__builtin_mul_overflow(*buf + 1, WEIGHT, buf) || __builtin_sub_overflow(*buf, 2, buf)) {
                    shift_to_space();
                    return -1;
                }
            } else {
                if (__builtin_mul_overflow(*buf, WEIGHT, buf) || __builtin_add_overflow(*buf, 1, buf)) {
                    shift_to_space();
                    return -1;
                }
            }
        } else if (c == 'a') {
            if (*buf > 0) {
                if (__builtin_mul_overflow(*buf - 1, WEIGHT, buf) || __builtin_add_overflow(*buf, 2, buf)) {
                    shift_to_space();
                    return -1;
                }
            } else {
                if (__builtin_mul_overflow(*buf, WEIGHT, buf) || __builtin_sub_overflow(*buf, 1, buf)) {
                    shift_to_space();
                    return -1;
                }
            }
        }
        c = getchar();
    }
    return 1;
}

int
main(void)
{
    long long num = 0;
    int ret;
    while ((ret = getnum(&num))) {
        if (ret == -1) {
            printf("18446744073709551616\n");
        } else {
            printf("%lld\n", num);
        }
    }
}

