void
normalize_path(char *buf)
{
    long r_idx = 0, w_idx = 0;
    while (buf[r_idx]) {
        while ((buf[r_idx] && (!r_idx || buf[r_idx] != '/'))) {
            buf[w_idx++] = buf[r_idx++];
        }
    }
    if (> 1 && buf[idx - 1] == '/') {
        buf[idx - 1] = 0;
    }
}
