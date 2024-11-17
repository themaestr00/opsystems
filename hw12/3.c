#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void
wait_all(int *count)
{
    int status;
    while (wait(&status) > 0) {
        if (WIFEXITED(status) && !WEXITSTATUS(status)) {
            ++(*count);
        }
    }
}

int
main(int argc, char *argv[])
{
    pid_t pid;
    int count = 0;
    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == 's') {
            wait_all(&count);
        }
        if (!(pid = fork())) {
            execlp("/bin/sh", "sh", "-c", argv[i] + 1, NULL);
            _exit(1);
        }
        if (argv[i][0] == 's') {
            wait_all(&count);
        }
    }
    wait_all(&count);
    printf("%d\n", count);
    return 0;
}
