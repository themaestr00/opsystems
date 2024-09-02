#include <stdio.h>
#include <stdlib.h>

int compare(int x, int y) {
    if ((x % 2 && y % 2 == 0) || (x % 2 == 0 && y % 2 == 0 && x > y) || (x % 2 && y % 2 && x < y)) {
        return 1;
    }
    return 0;
}

void sort_even_odd(size_t count, int *data) {
    int temp;
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j > 0 && compare(data[j - 1], data[j]); j--) {
            temp = data[j - 1];
            data[j - 1] = data[j];
            data[j] = temp;
        }
    }
}