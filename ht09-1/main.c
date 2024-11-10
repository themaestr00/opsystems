#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <stdlib.h>

enum
{
    ARGS_COUNT = 4
};

int
main(int argc, char *argv[])
{
    if (argc != ARGS_COUNT) {
        fprintf(stderr, "Wrong arguments!\n");
        exit(1);
    }
}
