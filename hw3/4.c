int
satsum(int v1, int v2)
{
    enum
    {
        MY_INT_MAX = ~0U << -~0U >> -~0U
    };
    enum
    {
        MY_INT_MIN = ~MY_INT_MAX
    };
    printf("%d %d\n", MY_INT_MAX, MY_INT_MIN);
    if (v1 > 0 && v2 > 0 && MY_INT_MAX - v1 <= v2) {
        return MY_INT_MAX;
    } else if (v1 < 0 && v2 < 0 && v1 - MY_INT_MIN <= -v2) {
        return MY_INT_MIN;
    }
    return v1 + v2;
}
