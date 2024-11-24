#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(void)
{
    int fd[2];
    pipe(fd);
    int i;
    for (i = 0; i < 2 && !fork(); ++i)
        ;
    int num;
    long sum = 0;
    switch (i) {
    case 0:
        close(fd[0]);
        while (scanf("%d", &num) != EOF) {
            write(fd[1], &num, sizeof(num));
        }
        close(fd[1]);
        wait(NULL);
        break;
    case 1:
        close(fd[0]);
        close(fd[1]);
        wait(NULL);
        break;
    case 2:
        close(fd[1]);
        while (read(fd[0], &num, sizeof(num))) {
            sum += num;
        }
        close(fd[0]);
        printf("%ld\n", sum);
    }
    return 0;
}
