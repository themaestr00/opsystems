#include <unistd.h>
#include <sys/wait.h>

int
cmd(char *command)
{
    pid_t pid;
    int status = 0;
    if ((pid = fork()) == -1) {
        return 0;
    } else if (!pid) {
        execlp("/bin/sh", "sh", "-c", command, NULL);
        return 0;
    } else {
        wait(&status);
    }
    if (WIFEXITED(status) && !WEXITSTATUS(status)) {
        return 1;
    }
    return 0;
}

int
main(int argc, char *argv[])
{
    if ((cmd(argv[1]) || cmd(argv[2])) && cmd(argv[3])) {
        return 0;
    }
    return 1;
}
