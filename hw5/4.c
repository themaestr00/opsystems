#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int
compar(const void *arg1, const void *arg2)
{
    char *str1 = *(char **) arg1;
    char *str2 = *(char **) arg2;
    return strcmp(str1, str2);
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

int
is_unique(char **arr, size_t count, size_t start, char *path)
{
    for (int i = start + 1; i < count; ++i) {
        if (is_equal(path, arr[i])) {
            return 0;
        }
    }
    return 1;
}

int
main(int argc, char *argv[])
{
    qsort(argv + 1, argc - 1, sizeof(argv[0]), compar);
    struct stat buf;
    for (int i = 1; i < argc; ++i) {
        if (stat(argv[i], &buf) != -1 && is_unique(argv, argc, i, argv[i])) {
            printf("%s\n", argv[i]);
        }
    }
    return 0;
}
