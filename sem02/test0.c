#include <stdlib.h>

int a()
{
    return 1;
}

int b()
{
    return 2;
}

int c(int, int)
{

    return a() + b();
}

int d(int a, int b)
{
    return a + b;
}

int main()
{
    int *ptr = malloc(10);
    int q = d(a(), b());
}
