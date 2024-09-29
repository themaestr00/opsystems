#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

enum
{
    OCTAL = 8,
    RIGHTS_LEN = 10,
    MASK_MAX = 511
};

int
main(int argc, char *argv[])
{
    int64_t mask = 0;
    char template[] = "rwxrwxrwx";
    char rights[RIGHTS_LEN] = "";
    char *eptr = NULL;
    for (int i = 1; i < argc; ++i) {
        mask = strtol(argv[i], &eptr, OCTAL);
        if (errno || *eptr || eptr == argv[i] || mask > MASK_MAX) {
            fprintf(stderr, "%s: Incorrect argument number %d\n", argv[0], i);
            return 1;
        }
        for (int i = RIGHTS_LEN - 2; i >= 0; --i) {
            if (mask & 1) {
                rights[i] = template[i];
            } else {
                rights[i] = '-';
            }
            mask >>= 1;
        }
        printf("%s\n", rights);
    }
    return 0;
}
