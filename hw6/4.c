#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

enum
{
    ARGS_COUNT = 3,
    MAX_DEPTH = 4,
    DECIMAL = 10
};

struct DirVec
{
    char **dirs;
    size_t vec_size;
    size_t vec_count;
};

int
print_paths(const char *path, const char *curr, size_t size, int depth)
{
    if (depth > MAX_DEPTH) {
        return 0;
    }
    DIR *dir = opendir(path);
    if (!dir) {
        return -1;
    }
    struct DirVec v = {.dirs = calloc(PATH_MAX, sizeof(char *)), .vec_size = PATH_MAX, .vec_count = 0};
    if (!v.dirs) {
        return -1;
    }
    struct dirent *dirinfo;
    struct stat fileinfo;
    char fullpath[PATH_MAX];
    int len;
    errno = 0;
    while ((dirinfo = readdir(dir))) {
        if (strcmp(".", dirinfo->d_name) && strcmp("..", dirinfo->d_name)) {
            len = snprintf(fullpath, sizeof(fullpath), "%s/%s", path, dirinfo->d_name);
            if (len + 1 > sizeof(fullpath)) {
                return -1;
            }
            if (lstat(fullpath, &fileinfo) != -1) {
                if (!access(fullpath, R_OK) && S_ISREG(fileinfo.st_mode) && fileinfo.st_size <= size) {
                    if (curr[0]) {
                        printf("%s/%s\n", curr, dirinfo->d_name);
                    } else {
                        printf("%s\n", dirinfo->d_name);
                    }
                } else if (S_ISDIR(fileinfo.st_mode)) {
                    if (v.vec_count == v.vec_size) {
                        v.vec_size <<= 1;
                        v.dirs = realloc(v.dirs, v.vec_size);
                        if (!v.dirs) {
                            return -1;
                        }
                    }
                    if (!(v.dirs[v.vec_count++] = strdup(dirinfo->d_name))) {
                        return -1;
                    }
                }
            }
        }
        errno = 0;
    }
    if (errno) {
        return -1;
    }
    if (closedir(dir) == -1) {
        return -1;
    }
    char ncurr[PATH_MAX];
    for (size_t i = 0; i < v.vec_count; ++i) {
        len = snprintf(fullpath, sizeof(fullpath), "%s/%s", path, v.dirs[i]);
        if (len + 1 > sizeof(fullpath)) {
            return -1;
        }
        if (curr[0]) {
            len = snprintf(ncurr, sizeof(ncurr), "%s/%s", curr, v.dirs[i]);
        } else {
            len = snprintf(ncurr, sizeof(ncurr), "%s", v.dirs[i]);
        }
        if (len + 1 > sizeof(ncurr)) {
            return -1;
        }
        print_paths(fullpath, ncurr, size, depth + 1);
        free(v.dirs[i]);
    }
    free(v.dirs);
    return 0;
}

int
main(int argc, char *argv[])
{
    if (argc != ARGS_COUNT) {
        fprintf(stderr, "Wrong arguments!\n");
        exit(1);
    }
    char *eptr = NULL;
    errno = 0;
    size_t size = strtol(argv[2], &eptr, DECIMAL);
    if (errno || *eptr || eptr == argv[2]) {
        fprintf(stderr, "Wrong argument number 2!\n");
        exit(1);
    }
    print_paths(argv[1], "", size, 1);
    return 0;
}
