#include <stddef.h>

struct s1
{
    char f1;
    long long f2;
    char f3;
};

struct s2
{
    char f1;
    char f3;
    long long f2;
};

size_t
compactify(void *ptr, size_t size)
{
    if (size <= 0 || !ptr) {
        return 0;
    }
    struct s1 *ptr_in = (struct s1 *) ptr;
    struct s2 *ptr_out = (struct s2 *) ptr;
    size_t len = size / sizeof(struct s1);
    size_t size2 = 0;
    for (size_t i = 0; i < len; ++i) {
        ptr_out[i].f1 = ptr_in[i].f1;
        ptr_out[i].f2 = ptr_in[i].f2;
        ptr_out[i].f3 = ptr_in[i].f3;
        size2 += sizeof(struct s2);
    }
    return size2;
}
