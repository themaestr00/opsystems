#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

enum
{
    ARGS_COUNT = 3,
    DECIMAL = 10
};

int
main(int argc, char *argv[])
{
    errno = 0;
    if (argc != ARGS_COUNT) {
        fprintf(stderr, "%s: Wrong arguments!\n", argv[0]);
        return 1;
    }
    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        fprintf(stderr, "%s: Incorrect file or pathname: %s\n", argv[0], strerror(errno));
        return 1;
    }
    int64_t count = 0;
    char *eptr = NULL;
    count = strtoll(argv[2], &eptr, DECIMAL);
    if (errno || *eptr || eptr == argv[2]) {
        fprintf(stderr, "%s: Incorrect argument number 2!\n", argv[0]);
        return 1;
    }
    if (count > 1) {
        double res = 0, cur = 0, prev = 0;
        int ret;
        while (count > 0 && (ret = read(fd, &cur, sizeof(double))) == sizeof(double)) {
            res = cur - prev;
            if (lseek(fd, -sizeof(double), SEEK_CUR) == -1) {
                fprintf(stderr, "%s: Error in lseek: %s\n", argv[0], strerror(errno));
                return 1;
            }
            if (write(fd, &res, sizeof(double)) == -1) {
                fprintf(stderr, "%s: Error in writing: %s\n", argv[0], strerror(errno));
                return 1;
            }
            prev = res;
            --count;
        }
        if (ret == -1) {
            fprintf(stderr, "%s: Error in reading: %s\n", argv[0], strerror(errno));
            return 1;
        }
    }
    close(fd);
}
