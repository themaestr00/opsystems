#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(void)
{
    int num, new_num, is_father = 1;
    pid_t pid = 1;
    while (scanf("%d", &new_num) != EOF && !(pid = fork())) {
        num = new_num;
        is_father = 0;
    }
    if (pid == -1) {
        if (is_father) {
            printf("-1\n");
            return 0;
        } else {
            _exit(1);
        }
    }
    int status;
    if (pid) {
        wait(&status);
    }
    if (WIFEXITED(status) && WEXITSTATUS(status)) {
        if (is_father) {
            printf("-1\n");
        } else {
            _exit(1);
        }
    } else if (!is_father) {
        printf("%d\n", num);
    }
    return 0;
}
