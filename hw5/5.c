#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

enum
{
    READ_SHIFT = 3
};

size_t
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
                    r_idx += READ_SHIFT;
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
            buf[--w_idx] = 0;
        } else {
            buf[w_idx] = 0;
        }
    }
    return w_idx;
}

char *
relativize_path(const char *path1, const char *path2)
{
    if (!path1 || !path2) {
        return NULL;
    }
    size_t len1 = strlen(path1), len2 = strlen(path2);
    char *npath1 = calloc(len1 + 1, sizeof(char));
    if (!npath1) {
        return NULL;
    }
    char *npath2 = calloc(len2 + 1, sizeof(char));
    if (!npath2) {
        return NULL;
    }
    memcpy(npath1, path1, len1 + 1);
    memcpy(npath2, path2, len2 + 1);
    len1 = normalize_path(npath1);
    len2 = normalize_path(npath2);
    size_t prefix = 0;
    for (size_t i = 0; i < len1 && i < len2 && npath1[i] == npath2[i]; ++i) {
        if (npath1[i] == '/') {
            prefix = i;
        } else if (i == len2 - 1 && npath1[i + 1] == '/') {
            prefix = i + 1;
        }
    }
    size_t size = 1, len = 0;
    for (size_t i = prefix + 1; i < len1; ++i) {
        if (npath1[i] == '/') {
            size += sizeof("../") - 1;
        }
    }
    if (prefix == len2) {
        --prefix;
    }
    free(npath1);
    char *res;
    if (size + len2 - prefix - 1 == 1) {
        res = calloc(2, sizeof(char));
    } else {
        res = calloc(size + len2 - prefix - 1, sizeof(char));
    }
    if (!res) {
        return NULL;
    }
    for (size_t i = 0; i < (size - 1) / (sizeof("../") - 1); ++i) {
        sprintf(res + len, "../");
        len += sizeof("../") - 1;
    }
    size += len2 - prefix - 1;
    sprintf(res + len, "%s", npath2 + prefix + 1);
    free(npath2);
    if (!res[0]) {
        res[0] = '.';
    } else if (res[size - 2] == '/') {
        res[size - 2] = 0;
    }
    return res;
}
