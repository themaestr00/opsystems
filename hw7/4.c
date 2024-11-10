#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

void
errchk(int stmnt, const char *errmsg)
{
    if (stmnt) {
        if (errno) {
            fprintf(stderr, "%s: %s\n", errmsg, strerror(errno));
        } else {
            fprintf(stderr, "%s\n", errmsg);
        }
        exit(1);
    }
}

int
main(int argc, char *argv[])
{
    errchk(argc != 2, "Wrong arguments!");
    errno = 0;
    int fd = open(argv[1], O_RDWR);
    errchk(fd == -1, "Error in open");
    struct stat fileinfo;
    errchk(fstat(fd, &fileinfo) == -1, "Error in fstat");
    int x, byte_num;
    unsigned char byte;
    while (scanf("%d", &x) == 1) {
        if (x > 0 && (byte_num = (x - 1) / CHAR_BIT) < fileinfo.st_size) {
            errchk(lseek(fd, byte_num, SEEK_SET) == -1, "Error in lssek");
            errchk(read(fd, &byte, sizeof(byte)) == -1, "Error in read");
            byte |= 1 << (x - 1) % CHAR_BIT;
            errchk(lseek(fd, -sizeof(byte), SEEK_CUR) == -1, "Error in lseek");
            errchk(write(fd, &byte, sizeof(byte)) == -1, "Error in write");
        } else if (x < 0 && (byte_num = -(x + 1) / CHAR_BIT) < fileinfo.st_size) {
            errchk(lseek(fd, byte_num, SEEK_SET) == -1, "Error in lseek");
            errchk(read(fd, &byte, sizeof(byte)) == -1, "Error in read");
            byte &= (unsigned) -1 ^ (1 << (-(x + 1) % CHAR_BIT));
            errchk(lseek(fd, -sizeof(byte), SEEK_CUR) == -1, "Error in lseek");
            errchk(write(fd, &byte, sizeof(byte)) == -1, "Error in write");
        }
    }
    errchk(errno, "Error in scanf");
    errchk(close(fd) == -1, "Erorr in close");
    return 0;
}
