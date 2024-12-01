#include <stdio.h>
#include <unistd.h>
#include <signal.h>

enum
{
    ADD,
    MUL
};

volatile sig_atomic_t op = ADD;

void
handler(int s)
{
    if (s == SIGINT) {
        op = ADD;
    } else {
        op = MUL;
    }
}

int
main(void)
{
    sigaction(SIGINT, &(struct sigaction){.sa_handler = handler, .sa_flags = SA_RESTART}, NULL);
    sigaction(SIGQUIT, &(struct sigaction){.sa_handler = handler, .sa_flags = SA_RESTART}, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    int num, val = 0;
    while (scanf("%d", &num) == 1) {
        if (op == ADD) {
            __builtin_add_overflow(val, num, &val);
        } else {
            __builtin_mul_overflow(val, num, &val);
        }
    }
}
