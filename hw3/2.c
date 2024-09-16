#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int
main(int argc, char *argv[])
{
    int sum_pos = 0, sum_neg = 0;
    long num;
    char *eptr = NULL;
    for (int i = 1; i < argc; ++i) {
        errno = 0;
        num = strtol(argv[i], &eptr, 10);
        if (errno || *eptr || eptr == argv[i] || (int) num != num) {
            fprintf(stderr, "%s: Invalid argument number %d!\n", argv[0], i);
            return 1;
        }
        if (num > 0) {
            if (__builtin_add_overflow(num, sum_pos, &sum_pos)) {
                fprintf(stderr, "%s: Data is too big!\n", argv[0]);
                return 1;
            }
        } else {
            if (__builtin_add_overflow(num, sum_neg, &sum_neg)) {
                fprintf(stderr, "%s: Data is too big!\n", argv[0]);
                return 1;
            }
        }
    }
    printf("%d\n%d\n", sum_pos, sum_neg);
}

