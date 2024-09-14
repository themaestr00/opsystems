#include <stdio.h>

int
main()
{
    printf("Size of int: %d\n", sizeof(int));
    printf("Size of int16: %d\n", sizeof(__int16_t));
    printf("Size of int32: %d\n", sizeof(__int32_t));
    printf("Size of long: %ld\n", sizeof(long));
}
