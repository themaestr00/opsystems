#include <stdio.h>
#include <limits.h>
#include <string.h>

char *
relativize_path(const char *path1, const char *path2)
{
    if (!path1 || !path2 || strlen(path1) >= PATH_MAX || strlen(path2) >= PATH_MAX) {
        return NULL;
    }
    int prefix = -1;
    for (int i = 0; i < strlen(path1) && i < strlen(path2) && path1[i] == path2[i]; ++i) {
        if (path1[i] == '/') {
            prefix = i;
        }
    }
    static char res[PATH_MAX];
    for (int i = prefix + 1; i < strlen(path1); ++i) {
        if (path1[i] == '/') {
            snprintf(res + strlen(res), sizeof(res) - strlen(res), "../");
        }
    }
    snprintf(res + strlen(res), sizeof(res) - strlen(res), "%s", path2 + prefix + 1);
    if (res[strlen(res) - 1] == '/') {
        res[strlen(res) - 1] = 0;
    }
    return res;
}
