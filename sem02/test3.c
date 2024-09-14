#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    int a, b;
    scanf("%d%d", &a, &b);
    int size = 0;
    int *p = NULL;
    if (__builtin_mul_overflow(a, b, &size) || __builtin_mul_overflow(size, sizeof(p), &size))
    {
        fprintf(stderr, "Overflow\n");
        _exit(1);
    }
    p = malloc(size);
}
