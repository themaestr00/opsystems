#include <stdio.h>
#include <ctype.h>
#include <string.h>

int
main(void)
{
    char str[101] = {};
    size_t len;
    int k = 13;
    while (fgets(str, 101, stdin)) {
        len = strlen(str);
        if (str[len - 1] == '\n') {
            str[len - 1] = 0;
            --len;
        }
        for (size_t i = 0; i < len; ++i) {
            if (islower(str[i])) {
                str[i] = 'a' + (str[i] + k - 'a') % 26;
            }
        }
        k = (k - 1 + 26) % 26;
        printf("%s\n", str);
    }
    return 0;
}
