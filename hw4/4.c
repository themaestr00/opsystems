#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

struct Node
{
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
};

void
print_tree(int fd, struct Node el)
{
    struct Node next = {};
    if (el.right_idx) {
        if (lseek(fd, el.right_idx * sizeof(el), SEEK_SET) == -1) {
            fprintf(stderr, "Error in lseek (print_tree)\n");
            _exit(1);
        }
        if (read(fd, &next, sizeof(next)) == -1) {
            fprintf(stderr, "Error in read (print_tree)\n");
            _exit(1);
        }
        print_tree(fd, next);
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
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "%s: Incorrect file or pathname: %s\n", argv[0], strerror(errno));
        return 1;
    }
    close(fd);
}
