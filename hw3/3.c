#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>

enum
{
    ROUND_TO = 10000,
    PERCENT = 100
};

int
main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "%s: Not enough arguments!\n", argv[0]);
        return 1;
    }
    double course, coeff = 0;
    char *eptr;
    for (int i = 1; i < argc; ++i) {
        errno = 0;
        if (i == 1) {
            course = strtod(argv[i], &eptr);
        } else {
            coeff = strtod(argv[i], &eptr);
        }
        if (errno || *eptr || eptr == argv[i]) {
            fprintf(stderr, "%s: Invalid argument number %d\n", argv[0], i);
            return 1;
        }
        coeff = 1 + coeff / PERCENT;
        course *= coeff;
        course = round(course * ROUND_TO) / ROUND_TO;
    }
    printf("%.4lf\n", course);
}
