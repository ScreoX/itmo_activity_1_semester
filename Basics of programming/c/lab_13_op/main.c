#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <windows.h>


/*
 * ftell - кол-во байт, на которое указатель отдален от начала (размер файла)
 * fread - считывает объекты в заданное место (возвращает кол-во считанных объектов)
 * fwrite - возвращает кол-во считанных объектов
 * fseek - устанавливает указатель в файле на нужное место
 * feof - проверяет положение указателя в файле (проверяет, достигнут ли конец файла)
 * strlen - длина строки, оканчивающейся нулевым символом
 * SEEK_END - перемещает указатель в конец файла
 * SEEK_SET - перемещает указатель в начало файла
 */

int File_size(char *file_name_of_the_frame) {
    
    int size_of_the_file;
    FILE *f = fopen(file_name_of_the_frame, "rb");
    
    if (f == NULL) {
        return -1;
    }
    else {
        fseek(f, 0, SEEK_END);
        
        size_of_the_file = ftell(f);

        fclose(f);
    }
    return size_of_the_file;
}

void Show(char *file) {
    char temp[10];
    
    FILE *f = fopen(file, "rb");

    fread(temp, 1, 10, f);

    char *size_of_bites = (char *) malloc(sizeof(char) * File_size(file));

    fread(size_of_bites, 1, File_size(file) - 10, f);

    int i = 0;
    
    while (size_of_bites[i] != 0) {

        char name_of_the_frame[5] = {size_of_bites[i], size_of_bites[i + 1], size_of_bites[i + 2], size_of_bites[i + 3], '\0'};
        printf("%s ", name_of_the_frame);

        i += 4;

        int size = size_of_bites[i] * 256 * 256 * 256 + size_of_bites[i + 1] * 256 * 256 + size_of_bites[i + 2] * 256 + size_of_bites[i + 3];

        i += 6;

        for (int j = 0; j < size; j++, i++) {
            printf("%c", size_of_bites[i]);
        }
        printf("\n");
    }
    fclose(f);
    free(size_of_bites);
}

void Get(char *file, char frames[5]) {

    char *size_of_bites = (char *) malloc(sizeof(char) * (File_size(file) + 1));
    FILE *new_file = fopen(file, "rb");
    fread(size_of_bites, 1, File_size(file), new_file);

    int i = 10, size;
    
    while (size_of_bites[i] != 0) {
        if (size_of_bites[i] == frames[0] && size_of_bites[i + 1] == frames[1] && size_of_bites[i + 2] == frames[2] && size_of_bites[i + 3] == frames[3]) {
            printf("%c", size_of_bites[i]);
            printf("%c", size_of_bites[i + 1]);
            printf("%c", size_of_bites[i + 2]);
            printf("%c ", size_of_bites[i + 3]);

            i += 4;

            size = size_of_bites[i] * 256 * 256 * 256 + size_of_bites[i + 1] * 256 * 256 + size_of_bites[i + 2] * 256 + size_of_bites[i + 3];

            i += 6;
            
            for (int j = 0; j < size; i++, j++) {
                printf("%c", size_of_bites[i]);
            }
            
            break;
        } else {
            i += 4;
            size = size_of_bites[i] * 256 * 256 * 256 + size_of_bites[i + 1] * 256 * 256 + size_of_bites[i + 2] * 256 + size_of_bites[i + 3];
            i += size + 6;
        }
    }
    
    fclose(new_file);
    free(size_of_bites);
}

void commandSet(char *file, char frames[5], char *value) {

    FILE *f = fopen(file, "rb");
    char *size_of_bites = (char *) malloc(sizeof(char) * File_size(file));
    fread(size_of_bites, 1, File_size(file), f);

    for (int i = 0; i < File_size(file) - 4; i++) {
        
        if (size_of_bites[i] == frames[0] && size_of_bites[i + 1] == frames[1] && size_of_bites[i + 2] == frames[2] && size_of_bites[i + 3] == frames[3]) {
            FILE *extra_file = fopen("extra.mp3", "ab");
            fwrite(size_of_bites, 1, i + 10, extra_file);

            i += 7;
            int size = size_of_bites[i];

            fwrite(value, 1, size, extra_file);
            fseek(f, i + size + 3, SEEK_SET);

            char temp[500] = {0};
            int count;

            while (!feof(f)) {
                count = fread(&temp, 1, 500 * sizeof(char), f);
                fwrite(&temp, 1, count * sizeof(char), extra_file);
            }

            fclose(f);
            fclose(extra_file);

            extra_file = fopen("extra.mp3", "rb");
            f = fopen(file, "wb");

            fseek(extra_file, 0, SEEK_SET);

            while (!feof(extra_file)) {
                count = fread(&temp, 1, 500 * sizeof(char), extra_file);
                fwrite(&temp, 1, count * sizeof(char), f);
            }

            fclose(extra_file);
            remove("extra.mp3");
            break;
        }
    }
    free(size_of_bites);
}

int main(int argc, char *argv[]) {

    char frame[5] = {0};
    char *value = (char *) malloc(sizeof(char) * 100);

    for (int i = 0; i < 100; i++) {
        value[i] = 0;
    }

    char *file = (char *) malloc(sizeof(char) * 9);


    // * команды show, set, get

    // * argv содержит все аргументы, которые подаются в консоль
    // * argc содержит число, отвечающее за количество подаваемых аргументов


    int show = 0;
    int get = 0;
    int set = 0;

    for (int i = 0; i < argc; i++) {
        if (argv[i][2] == 'f') {
            // * файл musi.mp3 успешно считывается
            for (int j = 0; j < 8; j++) {
                file[j] = argv[i][j + 11];
            }

            file[8] = '\0';
        }
        if (!strcmp("--show", argv[i])) {
            show = 1;
        }

        if (argv[i][2] == 'g') {
            get = 1;

            file[8] = '\0';

            for (int j = 0; j < 4; j++) {
                frame[j] = argv[i][j + 6];
                if (j == 3) {
                    frame[4] = '\0';
                }
            }
        }
        if (argv[i][2] == 's' && argv[i][3] == 'e') {
            set = 1;
            for (int j = 0; j < 4; j++) {
                frame[j] = argv[i][j + 6];
                if (j == 3) {
                    frame[4] = '\0';
                }
            }
            

            int c;

            for (int j = 0, c = 8; j < strlen(argv[i + 1]); j++, c++) {
                if (argv[i + 1][c] >= 'a' && argv[i + 1][c] <= 'z' || argv[i + 1][c] >= 'A' && argv[i + 1][c] <= 'Z' || argv[i + 1][c] >= '0' && argv[i + 1][c] <= '9' || argv[i][c] == ' ') {
                    value[j] = argv[i + 1][c];
                }
                else {
                    break;
                }
            }
            value[c] = '\0';
        }
    }

//    for (int i = 0; i < 9; i++) {
//        printf("%c ", file[i]);
//    }
    if (show != 0) {
        Show(file);
    }
    if (get != 0) {
        Get(file, frame);
    }
    if (set != 0) {
        commandSet(file, frame, value);
    }

    return 0;
}

//.\lab_13_op.exe --filepath=music --show

//.\lab_13_op.exe --filepath=musi.mp3 --get=TIT2

//D:\c\lab_13_op\cmake-build-debug>\lab_13_op.exe --filepath=music.mp3 --show

//.\lab_13_op.exe --filepath=D:\c\lab_13_op\cmake-build-debug>\music.mp3 --show

//.\lab_13_op.exe --filepath=D:\c\lab_13_op\cmake-build-debug>\music.mp3 --set=COMM --value=Test