//
//  main.c
//  dz4
//
//  Created by Михаил Прозорский on 12.02.2024.
//

#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

const int size = 5; // по столько символов будет происходить чтение и запись

int main(int argc, char *argv[]) {
    // Проверка количества аргументов
    if (argc != 3) {
        fprintf(stderr, "Вызов должен содержать 2 аргумента\n");
        return 0;
    }

    // Достаем названия файлов из командной строки
    char *file_r = argv[1];
    char *file_w = argv[2];

    int     fd_r, fd_w;
    char    buffer[size];
    ssize_t bytes_r;
    ssize_t bytes_w;

    // Пытаемся получить информацию об исходном файле
    struct stat fileStat;
    if (stat(file_r, &fileStat) == -1) {
        printf("Ошибка с исходным файлом");
        return 0;
    }

    // Пытаемся открыть файл для чтения
    if((fd_r = open(file_r, O_RDONLY)) == -1) {
        printf("Не получается открыть файл для чтения\n");
        exit(-1);
    }

    // Пытаемся открыть файл для записи
    if((fd_w = open(file_w, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
        printf("Не получается открыть файл для записи\n");
        exit(-1);
    }

    // Циклическое чтение и запись
    do {
        bytes_r = read(fd_r, buffer, size);
        if(bytes_r == -1) {
            printf("Не получается прочитать из файла\n");
            exit(-1);
        }

        bytes_w = write(fd_w, buffer, bytes_r);
        if(bytes_w == -1) {
            printf("Не получается записать в файл\n");
            exit(-1);
        }
    } while(bytes_r == size);

    // Пытаемся закрыть файл для чтения
    if(close(fd_r) == -1) {
        printf("Не получается закрыть файл для чтения\n");
    }

    // Пытаемся закрыть файл для записи
    if(close(fd_w) == -1) {
        printf("Не получается закрыть файл для записи\n");
    }

    return 0;
}
