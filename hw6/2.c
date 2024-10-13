void
normalize_path(char *buf)
{
    long r_idx = 0, w_idx = 0;
    while (buf[r_idx]) {
        while (buf[r_idx] && buf[r_idx] != '.') {
            buf[w_idx++] = buf[r_idx++];
        }
        if (buf[r_idx] && buf[r_idx - 1] == '/') {
            if (!buf[r_idx + 1] || buf[r_idx + 1] == '/') {
                if (!buf[r_idx + 1]) {
                    ++r_idx;
                } else {
                    r_idx += 2;
                }
            } else if (buf[r_idx + 1] == '.' && (!buf[r_idx + 2] || buf[r_idx + 2] == '/')) {
                if (w_idx > 1) {
                    --w_idx;
                }
                while (w_idx > 0 && buf[w_idx - 1] != '/') {
                    --w_idx;
                }
                if (!buf[r_idx + 2]) {
                    r_idx += 2;
                } else {
                    r_idx += 3;
                }
            } else {
                buf[w_idx++] = buf[r_idx++];
            }
        } else if (buf[r_idx]) {
            buf[w_idx++] = buf[r_idx++];
        }
    }
    if (w_idx > 0) {
        if (w_idx > 1 && buf[w_idx - 1] == '/') {
            buf[w_idx - 1] = 0;
        } else {
            buf[w_idx] = 0;
        }
    }
}
