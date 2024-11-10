#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
    long long res = 0;
    int count = 0;
    for (int i = 1; i < argc - 1; ++i) {
        if (strtol(argv[i], NULL, 10) == 1) {
            for (int j = 0; j < strtol(argv[i + 1], NULL, 10); ++j) {
                res |= 1 << (count + j);
            }
            count += strtol(argv[i + 1], NULL, 10);
        } else if (strtol(argv[i], NULL, 10) == 0) {
            count += strtol(argv[i + 1], NULL, 10);
        }
    }
    printf("%lld\n", res);
    return 0;
}
