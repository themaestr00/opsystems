#include <stdio.h>
#include <stdlib.h>

int compare(const void  *ptr1, const void *ptr2) {
    int num1 = *(int*)ptr1;
    int num2 = *(int*)ptr2;
    if (num1 == num2) {
        return 0;
    }
    if ((num1 % 2 && num2 % 2 == 0) || (num1 % 2 == 0 && num2 % 2 == 0 && num1 > num2) || (num1 % 2 && num2 % 2 && num1 < num2)) {
        return 1;
    }
    return -1;
}

void sort_even_odd(size_t count, int *data) {
    qsort(data, count, sizeof(int), compare);
}

int main(void) {
    int mas[] = {};
    sort_even_odd(0, mas);
    for (int i = 0; i < 0; i++) {
        printf("%d ", mas[i]);
    }
    return 0;
}