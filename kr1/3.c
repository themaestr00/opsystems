#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>

int
main(int argc, char *argv[])
{
    int chk_flg = 1;
    char fullpath[PATH_MAX] = {};
    char tmp[PATH_MAX] = {};
    struct stat fileinfo;
    FILE *fin;
    DIR *dir;
    struct dirent *dirinfo;
    long long sum_size = 0;
    memcpy(fullpath, argv[1], strlen(argv[1]) + 1);
    while (chk_flg) {
        if (lstat(fullpath, &fileinfo) != -1) {
            if (S_ISREG(fileinfo.st_mode) && !access(fullpath, R_OK) && fileinfo.st_mode & (1 << 9)) {
                fin = fopen(fullpath, "r");
                fgets(fullpath, sizeof(fullpath), fin);
                fclose(fin);
            } else if (S_ISDIR(fileinfo.st_mode)) {
                dir = opendir(fullpath);
                memcpy(tmp, fullpath, sizeof(fullpath));
                while ((dirinfo = readdir(dir))) {
                    if (snprintf(fullpath, sizeof(fullpath), "%s/%s", tmp, dirinfo->d_name) + 1 > sizeof(fullpath)) {
                        break;
                    }
                    if (stat(fullpath, &fileinfo) != -1 && S_ISREG(fileinfo.st_mode) && !access(fullpath, X_OK)) {
                        sum_size += fileinfo.st_size;
                    }
                }
                closedir(dir);
                printf("%lld\n", sum_size);
                chk_flg = 0;
            } else {
                printf("%ld\n", fileinfo.st_size);
                chk_flg = 0;
            }
        } else {
            chk_flg = 0;
        }
    }
    return 0;
}
