#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <sys/wait.h>

enum
{
    FORKS_NUM = 3,
    YEAR_START = 1900
};

int
main(void)
{
    int fd[2];
    pipe(fd);
    int i;
    for (i = 0; i < FORKS_NUM && !fork(); ++i)
        ;
    time_t curr;
    struct tm date;
    if (i != FORKS_NUM) {
        close(fd[1]);
        wait(NULL);
        read(fd[0], &curr, sizeof(curr));
        localtime_r(&curr, &date);
        switch (i) {
        case 0:
            printf("Y:%04d\n", date.tm_year + YEAR_START);
            break;
        case 1:
            printf("M:%02d\n", date.tm_mon + 1);
            break;
        case 2:
            printf("D:%02d\n", date.tm_mday);
        }
    } else {
        close(fd[0]);
        curr = time(NULL);
        for (int j = 0; j < FORKS_NUM; ++j) {
            write(fd[1], &curr, sizeof(curr));
        }
        close(fd[1]);
    }
    return 0;
}
