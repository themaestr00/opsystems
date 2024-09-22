#include <limits.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

enum
{
    MASK_FIRST = 0x00fff000,
    MASK_LAST = ~MASK_FIRST,
    BYTE_MASK = 0xff,
    MASK_MOVE = 4
};

uint32_t
byte_reverse(uint32_t value)
{
    uint32_t result = 0, bytes_count = sizeof(value);
    for (int32_t i = CHAR_BIT; value; i += CHAR_BIT) {
        result ^= (value & BYTE_MASK) << (bytes_count * CHAR_BIT - i);
        value >>= CHAR_BIT;
    }
    return result;
}

int
main(int argc, char *argv[])
{
    errno = 0;
    if (argc != 2) {
        fprintf(stderr, "%s: Wrong arguments!\n", argv[0]);
        return 1;
    }
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
    if (fd == -1) {
        fprintf(stderr, "%s: Incorrect file or pathname: %s\n", argv[0], strerror(errno));
        return 1;
    }
    uint32_t num = 0;
    while (scanf("%d", &num) == 1) {
        num = ((num & MASK_FIRST) << MASK_MOVE) | (num & MASK_LAST);
        num = byte_reverse(num);
        if (write(fd, &num, sizeof(num)) == -1) {
            fprintf(stderr, "%s: Write error: %s\n", argv[0], strerror(errno));
            return 1;
        }
    }
    close(fd);
}
