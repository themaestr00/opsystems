#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

enum
{
    MAX_SIZE = 32,
    DECIMAL = 10
};

struct Elem
{
    struct Elem *next;
    char *str;
};

struct Elem *
dup_elem(struct Elem *head)
{
    if (!head) {
        return head;
    }
    long long num = 0;
    struct Elem *p = head;
    char *eptr = NULL;
    errno = 0;
    num = strtoll(p->str, &eptr, DECIMAL);
    if (!(errno || *eptr || eptr == p->str || num >= INT32_MAX || num < INT32_MIN)) {
        p = calloc(1, sizeof(*p));
        if (!p) {
            fprintf(stderr, "In function 'dup_elem': %s\n", strerror(errno));
            _exit(1);
        }
        p->next = head;
        p->str = calloc(MAX_SIZE, sizeof(char));
        if (!p->str) {
            fprintf(stderr, "In function 'dup_elem': %s\n", strerror(errno));
            _exit(1);
        }
        snprintf(p->str, MAX_SIZE, "%lld", num + 1);
        head = p;
        p = p->next;
    }
    struct Elem *new = p;
    while (p->next) {
        errno = 0;
        num = strtoll(p->next->str, &eptr, DECIMAL);
        if (!(errno || *eptr || eptr == p->next->str || num >= INT32_MAX || num < INT32_MIN)) {
            new = calloc(1, sizeof(*new));
            if (!new) {
                fprintf(stderr, "In function 'dup_elem': %s\n", strerror(errno));
                _exit(1);
            }
            new->next = p->next;
            p->next = new;
            p = new;
            new->str = calloc(MAX_SIZE, sizeof(char));
            if (!new->str) {
                fprintf(stderr, "In function 'dup_elem': %s\n", strerror(errno));
                _exit(1);
            }
            snprintf(new->str, MAX_SIZE, "%lld", num + 1);
        }
        p = p->next;
    }
    return head;
}
