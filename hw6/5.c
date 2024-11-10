#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

int
st_is_equal(struct stat *file1, struct stat *file2)
{
    if (!file1 || !file2) {
        return 0;
    }
    if (file1->st_dev == file2->st_dev && file1->st_ino == file2->st_ino) {
        return 1;
    }
    return 0;
}

int
is_equal(char *path1, char *path2)
{
    struct stat file1, file2;
    if (stat(path1, &file1) != -1 && stat(path2, &file2) != -1 && file1.st_dev == file2.st_dev &&
        file1.st_ino == file2.st_ino) {
        return 1;
    }
    return 0;
}

ssize_t
getcwd2(int fd, char *buf, size_t size)
{
    if (size <= 0) {
        return size;
    }
    DIR *start = opendir(".");
    if (!start) {
        return -1;
    }
    int fd_start = dirfd(start);
    if (fd_start == -1) {
        return -1;
    }
    if (fchdir(fd) == -1) {
        return -1;
    }
    char fullpath[PATH_MAX] = {};
    DIR *curr;
    struct dirent *dirinfo;
    struct stat fileinfo1, fileinfo2;
    if (fstat(fd, &fileinfo1) == -1) {
        return -1;
    }
    do {
        curr = opendir("..");
        if (!curr) {
            return -1;
        }
        while ((dirinfo = readdir(curr))) {
            if (strcmp(".", dirinfo->d_name) && strcmp("..", dirinfo->d_name) &&
                lstat(dirinfo->d_name, &fileinfo2) != -1 && st_is_equal(&fileinfo1, &fileinfo2)) {
                snprintf(fullpath, sizeof(fullpath), "%s/%s", )
            }
        }
    } while (!is_equal(dirinfo->d_name, "/"));
    if (fchdir(fd_start) == -1) {
        return -1;
    }
    if (closedir(start) == -1) {
        return -1;
    }
}
