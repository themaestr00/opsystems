#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int
main(void)
{
    char buf[9];
    pid_t pid = 1;
    int num, i;
    for (i = 1; i <= 3 && pid; ++i) {
        if (!(pid = fork())) {
            fgets(buf, sizeof(buf), stdin);
            sscanf(buf, "%d", &num);
            printf("num - %d\n", num);
        }
    }
    if (pid) {
        while (wait(NULL) != -1)
            ;
    } else {
        printf("%d\n", i - 1);
        printf("%d\n", num * num);
    }
    return 0;
}
