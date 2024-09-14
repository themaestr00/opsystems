#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum
{
    MAX_LEN = 129
};

int
main(void)
{
    char buf1[MAX_LEN];
    char buf2[MAX_LEN];
    char buf3[MAX_LEN];
    if (!fgets(buf1, MAX_LEN, stdin)) {
        exit(1);
    }
    if (!fgets(buf2, MAX_LEN, stdin)) {
        exit(1);
    }
    if (!fgets(buf3, MAX_LEN, stdin)) {
        exit(1);
    }
    buf1[strlen(buf1) - 1] = '\0';
    buf2[strlen(buf2) - 1] = '\0';
    buf3[strlen(buf3) - 1] = '\0';
    printf("[Host:%s,Login:%s,Password:%s]\n", buf1, buf2, buf3);
    return 0;
}
