#include <stdio.h>
#include <stdlib.h>

int
pow_mod(int x, int y, int n)
{
    int res = 1;
    while (y) {
        if (y & 1) {
            res *= x;
            res %= n;
        }
        x *= x;
        x %= n;
        y >>= 1;
    }
    return res;
}

int
main(void)
{
    int n;
    scanf("%d", &n);
    int *degs = malloc((n - 1) * sizeof(int));
    for (int a = 1; a < n; a++) {
        degs[a - 1] = pow_mod(a, n - 2, n);
    }
    for (int c = 0; c < n; c++) {
        for (int a = 1; a < n; a++) {
            printf("%d ", c * degs[a - 1] % n);
        }
        printf("\n");
    }
    free(degs);
    return 0;
}
 
