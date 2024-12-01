#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int
main(int argc, char *argv[])
{
    int file, fd[2];
    pipe(fd);
    if (!fork()) {
        dup2(fd[1], STDOUT_FILENO);
        file = open(argv[4], O_RDONLY | O_CLOEXEC);
        dup2(file, STDIN_FILENO);
        close(fd[1]);
        execlp("/bin/sh", "sh", "-c", argv[1], NULL);
        _exit(1);
    } else {
        int status;
        wait(&status);
        if (WIFEXITED(status) && !WEXITSTATUS(status)) {
            if (!fork()) {
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]);
                close(fd[1]);
                execlp("/bin/sh", "sh", "-c", argv[2], NULL);
                _exit(1);
            } else {
                wait(NULL);
            }
        }
        if (!fork()) {
            dup2(fd[0], STDIN_FILENO);
            file = open(argv[5], O_WRONLY | O_APPEND | O_CREAT | O_CLOEXEC, 0600);
            dup2(file, STDOUT_FILENO);
            close(fd[0]);
            close(fd[1]);
            execlp("/bin/sh", "sh", "-c", argv[3], NULL);
            _exit(1);
        } else {
            close(fd[0]);
            close(fd[1]);
            wait(NULL);
        }
    }
    return 0;
}
