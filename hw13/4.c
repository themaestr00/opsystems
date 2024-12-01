#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

void
kill_all()
{
    kill(0, SIGKILL);
    while (wait(NULL) > 0)
        ;
    _exit(1);
}

int
main(int argc, char *argv[])
{
    pid_t pid;
    int in[2] = {}, out[2] = {};
    for (int j = 1; j < argc; ++j) {
        in[0] = out[0];
        in[1] = out[1];
        if (j != argc - 1) {
            if (pipe(out) < 0) {
                kill_all();
            }
        }
        if (!(pid = fork())) {
            if (j != 1) {
                dup2(in[0], STDIN_FILENO);
                if (close(in[0]) < 0 || close(in[1]) < 0) {
                    _exit(1);
                }
            }
            if (j != argc - 1) {
                dup2(out[1], STDOUT_FILENO);
                if (close(out[0]) < 0 || close(out[1]) < 0) {
                    _exit(1);
                }
            }
            execlp("/bin/sh", "sh", "-c", argv[j], NULL);
            _exit(1);
        } else if (pid < 0) {
            kill_all();
        } else if (j != 1 && (close(in[0]) < 0 || close(in[1]) < 0)) {
            kill_all();
        }
    }
    while (wait(NULL) > 0)
        ;
    return 0;
}
