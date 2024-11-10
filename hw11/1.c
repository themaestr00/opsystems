#include <unistd.h>

int
proc(void)
{
    int pid = fork();
    if (!pid) {
        write(1, "1\n", 2);
    }
    return pid;
}

int
main(void)
{
    proc(), proc(), proc();
    return 0;
}
