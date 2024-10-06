#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

enum
{
    YEAR_MIN = 1910,
    YEAR_MAX = 2037,
    YEAR_MONTHS = 12,
    YEAR_START = 1900,
    WEEK_DAYS = 7,
    THURSDAY = 4,
    MOD = 3
};

int
main(void)
{
    int year;
    if (scanf("%d", &year) != 1 || year < YEAR_MIN || year > YEAR_MAX) {
        fprintf(stderr, "Wrong input!\n");
        exit(1);
    }
    struct tm timeinfo = {.tm_year = year - YEAR_START};
    for (int i = 1; i <= YEAR_MONTHS; ++i) {
        timeinfo.tm_mon = i - 1;
        timeinfo.tm_mday = 1;
        timeinfo.tm_isdst = -1;
        errno = 0;
        if (mktime(&timeinfo) == -1 && errno) {
            fprintf(stderr, "Error in mktime: %s\n", strerror(errno));
            exit(1);
        }
        timeinfo.tm_mday += (THURSDAY - timeinfo.tm_wday + WEEK_DAYS) % WEEK_DAYS + WEEK_DAYS;
        if (timeinfo.tm_mday % MOD) {
            printf("%d %d\n", i, timeinfo.tm_mday);
        }
        timeinfo.tm_mday += 2 * WEEK_DAYS;
        if (timeinfo.tm_mday % MOD) {
            printf("%d %d\n", i, timeinfo.tm_mday);
        }
    }
    return 0;
}
