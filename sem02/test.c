#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
    int a, b;
    scanf("%d%d", &a, &b);
    int res = 0;
    if (__builtin_mul_overflow(a, b, &res)) {
        fprintf(stderr, "Overflow!\n");
        exit(1);
    }
}

