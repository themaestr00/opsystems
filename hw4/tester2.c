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

    // Открываем файл для записи в бинарном режиме
    FILE *file = fopen(argv[1], "wb");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    double number;
    // Сообщение пользователю о вводе чисел
    printf("Enter double precision numbers (Ctrl+D to finish):\n");

    // Чтение чисел со стандартного потока ввода и запись их в файл
    while (scanf("%lf", &number) == 1) {
        fwrite(&number, sizeof(double), 1, file);
    }

    // Закрываем файл
    fclose(file);

    printf("Numbers have been written to the file %s\n", argv[1]);

    return 0;
}
