#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    char *tmp;
    char fullpath[PATH_MAX];
    pid_t pid = getpid();
    if ((tmp = getenv("XDG_RUNTIME_DIR"))) {
        sprintf(fullpath, "%s/%dscr.py", tmp, pid);
    } else if ((tmp = getenv("TMPDIR"))) {
        sprintf(fullpath, "%s/%dscr.py", tmp, pid);
    } else {
        sprintf(fullpath, "/tmp/%dscr.py", pid);
    }
    int fd = open(fullpath, O_WRONLY | O_CREAT | O_TRUNC, 0700);
    if (fd == -1) {
        fprintf(stderr, "Error in open: %s\n", strerror(errno));
        return 1;
    }
    FILE *script = fdopen(fd, "w");
    if (!script) {
        fprintf(stderr, "Error in fdopen: %s\n", strerror(errno));
        return 1;
    }
    fprintf(script, "#! /usr/bin/python3\n"
                    "import os\n"
                    "print(1");
    for (int i = 1; i < argc; ++i) {
        fprintf(script, "*%s", argv[i]);
    }
    fprintf(script, ")\n");
    fprintf(script, "os.remove('%s')\n", fullpath);
    fflush(script);
    fclose(script);
    execv(fullpath, argv);
    fprintf(stderr, "Error in execv: %s\n", strerror(errno));
    return 1;
}
