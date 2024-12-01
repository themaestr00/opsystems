#include <stdio.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t count = 0;

void
handler(int s)
{
    if (count == 5) {
        _exit(0);
    }
    printf("%d\n", count);
    fflush(stdout);
    ++count;
}

int
main(void)
{
    sigaction(SIGHUP, &(struct sigaction){.sa_handler = handler, .sa_flags = SA_RESTART}, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    while (1) {
        pause();
    }
    return 0;
}
