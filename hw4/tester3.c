#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
    // Проверяем, что передано правильное количество аргументов
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Открываем файл для чтения в бинарном режиме
    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    double number;
    // Чтение чисел из файла и вывод их в консоль
    while (fread(&number, sizeof(double), 1, file) == 1) {
        printf("%lf\n", number);
    }

    // Закрываем файл
    fclose(file);

    return 0;
}
