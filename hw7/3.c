#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <limits.h>

struct FileData
{
    char *name;
    dev_t dev;
    ino_t ino;
};

enum
{
    ARGS_COUNT = 3
};

int
is_unique(char *filename, struct stat *fileinfo, struct FileData *dirdata, size_t count)
{
    for (size_t i = 0; i < count; ++i) {
        if (fileinfo->st_dev == dirdata[i].dev && fileinfo->st_ino == dirdata[i].ino &&
            !strcmp(filename, dirdata[i].name)) {
            return 0;
        }
    }
    return 1;
}

int
main(int argc, char *argv[])
{
    if (argc != ARGS_COUNT) {
        fprintf(stderr, "Wrong arguments!\n");
        exit(1);
    }
    errno = 0;
    DIR *dir1 = opendir(argv[1]);
    if (!dir1) {
        fprintf(stderr, "Error in opendir: %s\n", strerror(errno));
        exit(1);
    }
    errno = 0;
    DIR *dir2 = opendir(argv[2]);
    if (!dir2) {
        fprintf(stderr, "Error in opendir: %s\n", strerror(errno));
        exit(1);
    }
    struct dirent *dirinfo;
    struct stat fileinfo;
    errno = 0;
    size_t size = PATH_MAX, count = 0;
    struct FileData *dirdata = calloc(size, sizeof(*dirdata));
    if (!dirdata) {
        fprintf(stderr, "Error in calloc: %s\n", strerror(errno));
        exit(1);
    }
    char fullpath[PATH_MAX];
    errno = 0;
    while ((dirinfo = readdir(dir2))) {
        snprintf(fullpath, sizeof(fullpath), "%s/%s", argv[2], dirinfo->d_name);
        if (stat(fullpath, &fileinfo) != -1 && (S_ISREG(fileinfo.st_mode) || S_ISLNK(fileinfo.st_mode))) {
            if (count == size) {
                size <<= 1;
                errno = 0;
                dirdata = realloc(dirdata, size);
                if (!dirdata) {
                    fprintf(stderr, "Error in realloc: %s\n", strerror(errno));
                    exit(1);
                }
            }
            dirdata[count].dev = fileinfo.st_dev;
            dirdata[count].ino = fileinfo.st_ino;
            errno = 0;
            if (!(dirdata[count++].name = strdup(dirinfo->d_name))) {
                fprintf(stderr, "Error in strdup: %s\n", strerror(errno));
                exit(1);
            }
        }
        errno = 0;
    }
    if (errno) {
        fprintf(stderr, "Error in readdir: %s\n", strerror(errno));
        exit(1);
    }
    if (closedir(dir2) == -1) {
        fprintf(stderr, "Error in closedir: %s\n", strerror(errno));
        exit(1);
    }
    unsigned long long size_sum = 0;
    errno = 0;
    while ((dirinfo = readdir(dir1))) {
        snprintf(fullpath, sizeof(fullpath), "%s/%s", argv[1], dirinfo->d_name);
        if (lstat(fullpath, &fileinfo) != -1 && S_ISREG(fileinfo.st_mode)) {
            if (!access(fullpath, W_OK) && !is_unique(dirinfo->d_name, &fileinfo, dirdata, count)) {
                size_sum += fileinfo.st_size;
            }
        }
        errno = 0;
    }
    if (errno) {
        fprintf(stderr, "Error in readdir: %s\n", strerror(errno));
        exit(1);
    }
    if (closedir(dir1) == -1) {
        fprintf(stderr, "Error in closedir: %s\n", strerror(errno));
        exit(1);
    }
    printf("%lld\n", size_sum);
    return 0;
}
