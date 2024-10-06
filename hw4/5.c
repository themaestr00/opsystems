#include <limits.h>
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
    ARGS_COUNT = 4,
    DECIMAL = 10,
    RIGHTS = 0666
};

int
main(int argc, char *argv[])
{
    if (argc != ARGS_COUNT) {
        fprintf(stderr, "%s: Wrong arguments!\n", argv[0]);
        return 1;
    }
    char *eptr = NULL;
    errno = 0;
    int64_t mod = strtoll(argv[3], &eptr, DECIMAL);
    if (errno || *eptr || eptr == argv[3] || (int32_t) mod != mod) {
        fprintf(stderr, "%s: Incorrect format of MOD!\n", argv[0]);
        return 1;
    }
    if (mod <= 0) {
        fprintf(stderr, "%s: MOD should be positive!\n", argv[0]);
        return 1;
    }
    errno = 0;
    int fd_in = open(argv[1], O_RDONLY);
    if (fd_in == -1) {
        fprintf(stderr, "%s: Incorrect file or pathname: %s\n", argv[0], strerror(errno));
        return 1;
    }
    errno = 0;
    int fd_out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, RIGHTS);
    if (fd_out == -1) {
        fprintf(stderr, "%s: Incorrect file or pathname: %s\n", argv[0], strerror(errno));
        return 1;
    }
    uint64_t sum = 0, i = 1;
    uint8_t byte = 0;
    int32_t out_num = 0;
    int ret = 0;
    errno = 0;
    while ((ret = read(fd_in, &byte, sizeof(byte))) == sizeof(byte)) {
        for (int j = 0; j < CHAR_BIT; ++j) {
            sum = (sum + (i % mod) * (i % mod) % mod) % mod;
            out_num = sum;
            if (byte & 1) {
                errno = 0;
                if (write(fd_out, &out_num, sizeof(out_num)) == -1) {
                    fprintf(stderr, "%s: Error in write: %s\n", argv[0], strerror(errno));
                    return 1;
                }
            }
            byte >>= 1;
            if (__builtin_add_overflow(i, 1, &i)) {
                fprintf(stderr, "%s: Data is too big\n", argv[0]);
                return 1;
            }
        }
        errno = 0;
    }
    if (ret == -1) {
        fprintf(stderr, "%s: Error in read: %s\n", argv[0], strerror(errno));
        return 1;
    }
    errno = 0;
    if (close(fd_in) == -1) {
        fprintf(stderr, "%s: Error in close fd_in: %s\n", argv[0], strerror(errno));
        return 1;
    }
    errno = 0;
    if (close(fd_out) == -1) {
        fprintf(stderr, "%s: Error in close fd_out: %s\n", argv[0], strerror(errno));
        return 1;
    }
    return 0;
}
