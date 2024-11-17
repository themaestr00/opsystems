#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
    int fd;
    int status = 0;
    if (!fork()) {
        fd = open(argv[2], O_RDONLY | O_CLOEXEC);
        if (fd == -1 || dup2(fd, STDIN_FILENO) == -1) {
            _exit(42);
        }
        fd = open(argv[3], O_RDWR | O_CREAT | O_APPEND | O_CLOEXEC, 0660);
        if (fd == -1 || dup2(fd, STDOUT_FILENO) == -1) {
            _exit(42);
        }
        fd = open(argv[4], O_RDWR | O_CREAT | O_TRUNC | O_CLOEXEC, 0660);
        if (fd == -1 || dup2(fd, STDERR_FILENO) == -1) {
            _exit(42);
        }
        execlp(argv[1], argv[1], NULL);
        _exit(42);
    } else {
        wait(&status);
    }
    printf("%d\n", status);
    return 0;
}
