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
        fgets(buf, sizeof(buf), stdin);
        if (!(pid = fork())) {
            for (int j = 0; j < 7 && !(num = strtol(buf + j, NULL, 10)); ++j)
                ;
        } else {
            wait(NULL);
        }
    }
    if (!pid) {
        printf("%d\n", i - 1);
        printf("%d\n", num * num);
    }
    return 0;
}
