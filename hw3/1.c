STYPE
bit_reverse(STYPE value)
{
    UTYPE ones = -1, u_value = value, count, u_result;
    STYPE result;
    for (count = 0; ones; ones >>= 1) {
        ++count;
    }
    for (STYPE i = 0; i < count; ++i) {
        u_result <<= 1;
        u_result ^= u_value & 1;
        u_value >>= 1;
    }
    result = u_result;
    return result;
}

