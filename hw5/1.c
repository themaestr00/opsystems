#include <stdio.h>
#include <sys/stat.h>
#include <stdint.h>

enum
{
    KIB = 1 << 10
};

int
main(int argc, char *argv[])
{
    unsigned long long count = 0;
    struct stat buf = {};
    for (int i = 1; i < argc; ++i) {
        if (lstat(argv[i], &buf) != -1 && buf.st_size % KIB == 0 && S_ISREG(buf.st_mode) && !S_ISLNK(buf.st_mode) &&
            buf.st_nlink == 1) {
            count += buf.st_size;
        }
    }
    printf("%llu\n", count);
    return 0;
}
