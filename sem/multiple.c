#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int
main(void)
{
    char buf1[1000], buf2[1000];
    scanf("%s%s", buf1, buf2);
    if (!fork()) {
        execlp("python3", "python3", "script.py", buf1, buf2, NULL);
    }
    wait(NULL);
    return 0;
}
