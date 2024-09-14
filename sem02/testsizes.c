#include <stdio.h>
#include <sys/types.h>

int
main(void)
{
    printf("Size of int: %ld\n", sizeof(int));
    printf("Size of long: %ld\n", sizeof(long));
    printf("Size of int16: %ld\n", sizeof(u_int16_t));
}
