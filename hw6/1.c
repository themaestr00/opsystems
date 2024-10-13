#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

int
is_suffix(char *str1, char *str2)
{
    if (strlen(str1) <= strlen(str2) && !strcmp(str1, str2 + strlen(str2) - strlen(str1))) {
        return 1;
    }
    return 0;
}

int
main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Wrong arguments!\n");
        exit(1);
    }
    DIR *directory;
    errno = 0;
    if (!(directory = opendir(argv[1]))) {
        fprintf(stderr, "Error in opendir: %s\n", strerror(errno));
        exit(1);
    }
    struct dirent *curr;
    struct stat fileinfo;
    long count = 0;
    char path[PATH_MAX];
    errno = 0;
    while ((curr = readdir(directory))) {
        snprintf(path, PATH_MAX, "%s/%s", argv[1], curr->d_name);
        if (!access(path, F_OK | X_OK) && stat(path, &fileinfo) != -1 && S_ISREG(fileinfo.st_mode) &&
            is_suffix(".exe", curr->d_name)) {
            ++count;
        }
        errno = 0;
    }
    if (errno) {
        fprintf(stderr, "Error in readdir: %s\n", strerror(errno));
        exit(1);
    }
    errno = 0;
    if (closedir(directory) == -1) {
        fprintf(stderr, "Error in closedir: %s\n", strerror(errno));
        exit(1);
    }
    printf("%ld\n", count);
    return 0;
}
