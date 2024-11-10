#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(void)
{
    int n, i;
    scanf("%d", &n);
    pid_t pid = 0;
    for (i = 0; i < n && !pid; ++i) {
        if (i == n - 1) {
            printf("%d\n", i + 1);
            fflush(stdout);
        } else {
            printf("%d ", i + 1);
            fflush(stdout);
            pid = fork();
        }
    }
    if (i != n) {
        wait(NULL);
    }
    return 0;
}
