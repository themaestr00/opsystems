#include <stdio.h>
#include <time.h>

enum
{
    MINS = 60,
    HOURS = 60 * MINS,
    DAYS = 24 * HOURS,
    WEEK_DAYS = 7,
    WEEKS_COUNT = 3,
    PERIOD = 29 * DAYS + 12 * HOURS + 44 * MINS,
    YEAR_START = 1900,
    DAY_START = 256,
    FM_YEAR = 2021,
    FM_MON = 4,
    FM_MDAY = 26,
    FM_HOUR = 11,
    FM_MIN = 14
};

int
main(void)
{
    int year;
    scanf("%d", &year);
    struct tm date = {.tm_year = year - YEAR_START, .tm_mday = DAY_START + 1, .tm_isdst = -1};
    struct tm fmoon = {.tm_year = FM_YEAR - YEAR_START,
                       .tm_mon = FM_MON,
                       .tm_mday = FM_MDAY,
                       .tm_hour = FM_HOUR,
                       .tm_min = FM_MIN,
                       .tm_isdst = -1};
    time_t curr = timegm(&date);
    time_t fm = timegm(&fmoon);
    while ((curr - fm) % PERIOD) {
        curr += MINS;
    }
    curr += DAYS;
    gmtime_r(&curr, &date);
    date.tm_mday += WEEK_DAYS * WEEKS_COUNT + (WEEK_DAYS + 1 - date.tm_wday) % WEEK_DAYS;
    curr = timegm(&date);
    printf("%d-%02d-%02d\n", date.tm_year + YEAR_START, date.tm_mon + 1, date.tm_mday);
    return 0;
}

