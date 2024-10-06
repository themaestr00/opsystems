#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>

enum
{
    FIRST_BYTE = 0,
    SECOND_BYTE,
    THIRD_BYTE,
    LAST_BYTE
};

struct Node
{
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
};

unsigned int
byte_reverse(unsigned char *bytes)
{
    return (((uint32_t) bytes[LAST_BYTE]) | ((uint32_t) bytes[THIRD_BYTE] << CHAR_BIT) |
            ((uint32_t) bytes[SECOND_BYTE] << CHAR_BIT * 2) | ((uint32_t) bytes[FIRST_BYTE] << CHAR_BIT * 3));
}

void
print_tree(int fd, off_t offset)
{
    unsigned char buf[sizeof(struct Node)];
    if (lseek(fd, offset, SEEK_SET) == -1) {
        fprintf(stderr, "Error in lseek: %s\n", strerror(errno));
        _exit(1);
    }
    for (int i = 0; i < sizeof(struct Node); ++i) {
        if (read(fd, buf + i, sizeof(buf[0])) != sizeof(buf[0])) {
            fprintf(stderr, "Error in read: %s\n", strerror(errno));
            _exit(1);
        }
    }
    uint32_t key = byte_reverse(buf);
    uint32_t left = byte_reverse(buf + sizeof(int32_t));
    uint32_t right = byte_reverse(buf + 2 * sizeof(int32_t));
    if (right) {
        print_tree(fd, right * sizeof(struct Node));
    }
    printf("%d\n", key);
    if (left) {
        print_tree(fd, left * sizeof(struct Node));
    }
}

int
main(int argc, char *argv[])
{
    errno = 0;
    if (argc != 2) {
        fprintf(stderr, "%s: Wrong arguments!\n", argv[0]);
        return 1;
    }
    errno = 0;
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "%s: Incorrect file or pathname: %s\n", argv[0], strerror(errno));
        return 1;
    }
    print_tree(fd, 0);
    errno = 0;
    if (close(fd) == -1) {
        fprintf(stderr, "%s: Error in close: %s\n", argv[0], strerror(errno));
        return 1;
    }
    return 0;
}
