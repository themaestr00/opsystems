#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <limits.h>

int
main(int argc, char *argv[])
{
    errno = 0;
    if (argc != 2) {
        fprintf(stderr, "%s: Wrong arguments!\n", argv[0]);
        return 1;
    }
    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        fprintf(stderr, "%s: Incorrect file or pathname: %s\n", argv[0], strerror(errno));
        return 1;
    }
    long long min = LLONG_MAX, num = 0, pos = 0;
    int ret = 0;
    int flag_empty = 0;
    while ((ret = read(fd, &num, sizeof(num))) == sizeof(num)) {
        if (!flag_empty) {
            flag_empty++;
        }
        if (num < min) {
            pos = lseek(fd, 0, SEEK_CUR) - sizeof(num);
            min = num;
        }
    }
    if (!flag_empty) {
        close(fd);
        return 0;
    }
    if (min == LLONG_MIN) {
        close(fd);
        return 0;
    }
    if (ret == -1) {
        fprintf(stderr, "%s: Error in reading: %s\n", argv[0], strerror(errno));
        return 1;
    }
    if (lseek(fd, pos, SEEK_SET) == -1) {
        fprintf(stderr, "%s: Error in lseek: %s\n", argv[0], strerror(errno));
        return 1;
    }
    unsigned long long neg = 0;
    neg = ~(unsigned long long) min + 1;
    if (write(fd, &neg, sizeof(neg)) == -1) {
        fprintf(stderr, "%s: Error in writing: %s\n", argv[0], strerror(errno));
        return 1;
    }
    close(fd);
    return 0;
}
