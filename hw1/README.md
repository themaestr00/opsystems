# Решение контеста №1
В данном разделе решения задач первого контеста, который был проведен на первом занятии практикума на 2 курсе
## Задача №1
Условие задачи: [click](https://disk.yandex.ru/i/nku74hg9fs2MLg)

По рисунку нетрудно определяем функции `y = 1, y = 7, y = x, x = 2, x = 5`. После чего составим неравенства, определяющие фигуру на рисунке:
```c
#include <stdio.h>

int
main(void)
{
    double x, y;
    scanf("%lf%lf", &x, &y);
    if (x >= 2 && x <= 5 && y >= 1 && y <= 7 && y >= x - 2) {
        printf("1");
    } else {
        printf("0");
    }
    return 0;
}
```
Задача с автопроверкой, так что забираем легкие 100 баллов

## Задача №2
Условие задачи: [click](https://disk.yandex.ru/i/suPPVteFm6UT1g) [click](https://disk.yandex.ru/i/Z-pKunCUld4mNQ)

Несмотря на кажущуюся простоту, эта задача может оказаться для вас серьезным испытаниям. Для решения рекомендую использовать массив символов, где индекс элемента будет совпадать с его 6-битной кодировкой, а также библиотеку ```ctype.h```. Важно: можно обойтись и без функции ```feof```, но записывать считанный символ в переменную типа ```int```.
```c
#include <stdio.h>
#include <ctype.h>

enum
{
    MASK1 = 0xfb,
    MASK2 = 0x8,
    NUMS_START = '0' - 1,
    LOWER_START = 'a' - 11,
    UPPER_START = 'A' - 37
};

int
main(void)
{
    char sym;
    char symbols[] = "@0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ#";
    int code;
    while ((sym = getchar()) != EOF) {
        if (!isalnum(sym)) {
            continue;
        }
        if (isdigit(sym)) {
            code = sym - NUMS_START;
        } else if (islower(sym)) {
            code = sym - LOWER_START;
        } else {
            code = sym - UPPER_START;
        }
        code &= MASK1;
        code ^= MASK2;
        putchar(symbols[code]);
    }
    return 0;
}
```
## Задача №3
Условие задачи: [click](https://disk.yandex.ru/i/KK1os86pD2pjsw)

Задача не из простых, нужно научиться находить обратные в поле $Z_n$. Для этого воспользуемся малой теоремой Ферма, о том, что остаток от деления $a^{n-1} \equiv 1 \mod{n}$. Напишем функцию для возведения числа в степень по модулю и заполним массив всевозможных степеней для лучшей эффективновсти кода. Теперь осталось лишь найти $b \equiv c * a^{n-2} \mod{n}$

Совет: не используйте ```malloc()```, лучше создайте массив на стеке с размером, равным максимально возможному числу степеней!
```c
#include <stdio.h>
#include <stdlib.h>

int
pow_mod(int x, int y, int n)
{
    int res = 1;
    while (y) {
        if (y & 1) {
            res *= x;
            res %= n;
        }
        x *= x;
        x %= n;
        y >>= 1;
    }
    return res;
}

int
main(void)
{
    int n;
    scanf("%d", &n);
    int *degs = malloc((n - 1) * sizeof(int));
    for (int a = 1; a < n; a++) {
        degs[a - 1] = pow_mod(a, n - 2, n);
    }
    for (int c = 0; c < n; c++) {
        for (int a = 1; a < n; a++) {
            printf("%d ", c * degs[a - 1] % n);
        }
        printf("\n");
    }
    free(degs);
    return 0;
}
```
