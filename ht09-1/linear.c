#include "linear.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

enum
{
    MUL = 1103515245,
    INC = 12345,
    DECIMAL = 10,
    MOD = 1 << 31
};

RandomSource *
destroy_linear(RandomSource *src)
{
    errno = 0;
    free(src->ops);
    if (errno) {
        fprintf(stderr, "Error in 'linear.c': %s\n", strerror(errno));
        exit(1);
    }
    free(src);
    if (errno) {
        fprintf(stderr, "Error in 'linear.c' %s\n", strerror(errno));
        exit(1);
    }
    return NULL;
}

double
next_linear(RandomSource *src)
{
    src->base = (MUL * src->base + INC) % MOD;
    return (double) src->base / MOD;
}

RandomSource *
random_linear_factory(const char *params)
{
    errno = 0;
    RandomSource *src = calloc(1, sizeof(RandomSource));
    if (!src) {
        fprintf(stderr, "Error in 'linear.c': %s\n", strerror(errno));
        exit(1);
    }
    src->ops = calloc(1, sizeof(RandomSourceOperations));
    if (!(src->ops)) {
        fprintf(stderr, "Error in 'linear.c': %s\n", strerror(errno));
        exit(1);
    }
    src->ops->destroy = destroy_linear;
    src->ops->next = next_linear;
    char *eptr = NULL;
    errno = 0;
    unsigned long long seed = strtoull(params, &eptr, DECIMAL);
    if (errno || *eptr || eptr == params) {
        fprintf(stderr, "Wrong seed!\n");
        exit(1);
    }
    seed %= MOD;
    src->base = seed;
    return src;
}
