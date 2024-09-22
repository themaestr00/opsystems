#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
    // Проверяем, что передан аргумент с именем файла
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

    // Читаем файл побайтово и выводим каждый байт в шестнадцатеричном формате
    unsigned char byte;
    while (fread(&byte, 1, 1, file) == 1) {
        printf("0x%02x ", byte);
    }

    // Закрываем файл
    fclose(file);

    printf("\n");
    return 0;
}
