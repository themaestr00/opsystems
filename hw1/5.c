#include <stdio.h>

enum
{
    MAX_LEN = 9,
    MAX_VALUE = 10,
    MIN_VALUE = 0
};

int
find(size_t count, int key, int *data)
{
    for (int i = 0; i < count; i++) {
        if (data[i] == key) {
            return 1;
        }
    }
    return 0;
}

void
print_permutations(int len, int remain)
{
    static int permutation[MAX_LEN];
    if (!remain) {
        for (int i = 0; i < len; i++) {
            printf("%d", permutation[i]);
        }
        printf("\n");
    }
    for (int i = 1; i <= len; i++) {
        if (!find(len, i, permutation)) {
            permutation[len - remain] = i;
            print_permutations(len, remain - 1);
            permutation[len - remain] = 0;
        }
    }
}

int
main(void)
{
    int n;
    if (scanf("%d", &n) != 1 || n <= MIN_VALUE || n >= MAX_VALUE) {
        fprintf(stderr, "error: incorrect input!\n");
        return 1;
    }
    print_permutations(n, n);
    return 0;
}
