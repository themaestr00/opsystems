#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

enum
{
    DECIMAL = 10,
    THOUSANDS = 1000
};

int
check_end(char *str)
{
    return !strcmp(str, "k+") || !strcmp(str, "k-") || !strcmp(str, "+") || !strcmp(str, "-");
}

int
main(int argc, char *argv[])
{
    char *endptr = NULL;
    long num;
    long long sum = 0;
    for (int i = 1; i < argc; ++i) {
        num = strtol(argv[i], &endptr, DECIMAL);
        if (!errno && endptr != argv[i] && check_end(endptr) && (int) num == num) {
            if (endptr[0] == 'k') {
                num *= THOUSANDS;
                if (endptr[1] == '+') {
                    sum += num;
                } else {
                    sum -= num;
                }
            } else if (endptr[0] == '+') {
                sum += num;
            } else {
                sum -= num;
            }
        }
    }
    printf("%lld\n", sum);
}
