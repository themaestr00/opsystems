#include <string.h>

int
parse_rwx_permissions(const char *str)
{
    if (!str) {
        return -1;
    }
    int result = 0;
    char template[] = "rwxrwxrwx";
    for (int i = 0; i < strlen(template); ++i) {
        if (str[i] == template[i]) {
            result ^= 1;
        } else if (str[i] != '-') {
            return -1;
        }
        result <<= 1;
    }
    return result;
}
