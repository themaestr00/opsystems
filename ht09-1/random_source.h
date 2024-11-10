#ifndef __RANDOM_SOURCE_H__
#define __RANDOM_SOURCE_H__

typedef struct RandomSource RandomSource;
typedef struct RandomSourceOperations RandomSourceOperations;
RandomSource *destroy(RandomSource *src);
double next(RandomSource *src);

typedef struct RandomSource
{
    RandomSourceOperations *ops;
    unsigned long long base;
} RandomSource;

typedef struct RandomSourceOperations
{
    RandomSource *(*destroy)(RandomSource *src);
    double (*next)(RandomSource *src);
} RandomSourceOperations;

#endif
