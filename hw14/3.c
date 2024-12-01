#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/wait.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    int n = strtol(argv[0], NULL, 10);
    char fullpath[PATH_MAX];
    FILE *f;
    pid_t pid = 1;
    for (int i = 1; i < n && i < argc; ++i) {
        f = fopen(argv[i], "r");
        if (f) {
            fgets(fullpath, sizeof(fullpath), f);
            fullpath[strlen(fullpath) - 1] = 0;
            if (!(pid = fork())) {
                execlp(fullpath, fullpath, NULL);
                _exit(1);
            }
        }
    }
    int count = 0, status;
    while (wait(&status) > 0) {
        if (WIFEXITED(status) && !WEXITSTATUS(status)) {
            ++count;
        }
    }
    for (int i = n; i < argc; ++i) {
        f = fopen(argv[i], "r");
        if (f) {
            fgets(fullpath, sizeof(fullpath), f);
            fullpath[strlen(fullpath) - 1] = 0;
            if (!(pid = fork())) {
                execlp(fullpath, fullpath, NULL);
                _exit(1);
            }
            if (wait(&status) > 0 && WIFEXITED(status) && !WEXITSTATUS(status)) {
                ++count;
            }
        }
    }
    printf("%d\n", count);
    return 0;
}
