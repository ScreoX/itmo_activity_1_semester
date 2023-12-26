#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *fileName;
char *Output = "";

typedef struct {
    unsigned char Size;
    unsigned char Width;
    unsigned char Height;
    unsigned char Planes;
    unsigned char Count_of_bits;
    unsigned char Compression;
    unsigned char SizeImage;
    unsigned char cnt_x_per_meter;
    unsigned char cnt_y_per_meter;
    unsigned char used_colour;
    unsigned char the_most_important_colour;
} Ingo_about_file;

typedef struct {
    char Type[2];
    unsigned char Size;
    unsigned char Reserved1;
    unsigned char Reserved2;
    unsigned char OffBits;
} File_Map;

typedef struct {
    unsigned char rgb_blue;
    unsigned char rgb_green;
    unsigned char rgb_red;
    unsigned char rgbReserved;
} RGB;

int isAlive(RGB pixel) {
    if (pixel.rgb_blue == 0 && pixel.rgb_green == 0 && pixel.rgb_red == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

File_Map read_file_map(FILE *file) {

    File_Map header;

    int four = 4, two = 2;

    fread(&header.Type, 1, two, file);
    fread(&header.Size, four, 1, file);
    fread(&header.Reserved1, two, 1, file);
    fread(&header.Reserved2, two, 1, file);
    fread(&header.OffBits, four, 1, file);

    return header;
}

Ingo_about_file read_file_header(FILE *file) {
    Ingo_about_file Info_about_header;

    int four = 4, two = 2;

    fread(&Info_about_header.Size, four, 1, file);
    fread(&Info_about_header.Width, four, 1, file);
    fread(&Info_about_header.Height, four, 1, file);
    fread(&Info_about_header.Planes, two, 1, file);
    fread(&Info_about_header.Count_of_bits, two, 1, file);
    fread(&Info_about_header.Compression, four, 1, file);
    fread(&Info_about_header.SizeImage, four, 1, file);
    fread(&Info_about_header.cnt_x_per_meter, four, 1, file);
    fread(&Info_about_header.cnt_y_per_meter, four, 1, file);
    fread(&Info_about_header.used_colour, four, 1, file);
    fread(&Info_about_header.the_most_important_colour, four, 1, file);

    return Info_about_header;
}

RGB **fieldRGB(FILE *file, Ingo_about_file Info_about_header) {
    RGB **field = (RGB **) malloc(Info_about_header.Height * sizeof(RGB *));

    for (int i = 0; i < Info_about_header.Height; ++i)
        field[i] = (RGB *) malloc(Info_about_header.Width * sizeof(RGB));

    for (int i = Info_about_header.Height - 1; i >= 0; i--) {
        for (int j = 0; j < Info_about_header.Width; j++) {
            field[i][j].rgb_blue = getc(file);
            field[i][j].rgb_green = getc(file);
            field[i][j].rgb_red = getc(file);
        }

        if (Info_about_header.Width % 4 != 0) {
            getc(file);
        }
    }

    return field;
}

void makeBmp(FILE *file, File_Map header, Ingo_about_file Info_about_header, RGB **mas_of_pixels) {

    int four = 4, two = 2;

    fwrite(&header.Type, 1, 2, file);
    fwrite(&header.Size, four, 1, file);
    fwrite(&header.Reserved1, two, 1, file);
    fwrite(&header.Reserved2, two, 1, file);
    fwrite(&header.OffBits, four, 1, file);
    fwrite(&Info_about_header.Size, four, 1, file);
    fwrite(&Info_about_header.Width, four, 1, file);
    fwrite(&Info_about_header.Height, four, 1, file);
    fwrite(&Info_about_header.Planes, two, 1, file);
    fwrite(&Info_about_header.Count_of_bits, two, 1, file);
    fwrite(&Info_about_header.Compression, two, 1, file);
    fwrite(&Info_about_header.SizeImage, two, 1, file);
    fwrite(&Info_about_header.cnt_x_per_meter, two, 1, file);
    fwrite(&Info_about_header.cnt_y_per_meter, two, 1, file);
    fwrite(&Info_about_header.used_colour, two, 1, file);
    fwrite(&Info_about_header.the_most_important_colour, two, 1, file);

    for (int i = Info_about_header.Height - 1; i >= 0; i--) {

        for (int j = 0; j < Info_about_header.Width; j++) {
            putc(mas_of_pixels[i][j].rgb_blue, file);
            putc(mas_of_pixels[i][j].rgb_green, file);
            putc(mas_of_pixels[i][j].rgb_red, file);
        }

        if (Info_about_header.Width % 4 != 0) {
            putc(0, file);
        }
    }
}

RGB **field_to_rgb(int **old_pic, Ingo_about_file Info_about_header) {
    RGB **field = (RGB **) malloc(Info_about_header.Height * sizeof(RGB *));

    for (int i = 0; i < Info_about_header.Height; ++i) {
        field[i] = (RGB *) malloc(Info_about_header.Width * sizeof(RGB));
    }

    for (int i = Info_about_header.Height - 1; i >= 0; i--) {
        for (int j = 0; j < Info_about_header.Width; j++) {
            if (old_pic[i][j] == 1) {
                field[i][j].rgb_blue = 0;
                field[i][j].rgb_green = 0;
                field[i][j].rgb_red = 0;
            }
            else {
                field[i][j].rgb_blue = 255;
                field[i][j].rgb_green = 255;
                field[i][j].rgb_red = 255;
            }
        }
    }

    return field;

}

int main(int argc, char *argv[]) {

    int max_iter = 100;
    int dump_freq = 1;

    for (int i = 1; i < argc; i++) {

//        printf("%d %s\n", i, argv[i]);
        if (!strcmp(argv[i], "--input")) {
            fileName = argv[i + 1];
        }

        if (!strcmp(argv[i], "--output")) {
            Output = argv[i + 1];
        }

        if (!strcmp(argv[i], "--max_iter")) {
            sscanf(argv[i + 1], "%d", &max_iter);
        }

        if (!strcmp(argv[i], "--dump_freq")) {
            sscanf(argv[i + 1], "%d", &dump_freq);
        }
        
        ++i;
        
    }

    FILE *file = fopen(fileName, "r");

    if (file == NULL) {
        return 0;
    }

    File_Map header = read_file_map(file);

    Ingo_about_file Info_about_header = read_file_header(file);

    RGB **rgb_colour = fieldRGB(file, Info_about_header);

    int **old_picture = (int **) malloc(Info_about_header.Height * sizeof(int *));

    for (int i = 0; i < Info_about_header.Height; ++i) {
        old_picture[i] = (int *) malloc(Info_about_header.Width * sizeof(int));
    }

    for (int i = 0; i < Info_about_header.Height; i++) {
        for (int j = 0; j < Info_about_header.Width; j++) {
            
            if (isAlive(rgb_colour[i][j]) == 1) {
                old_picture[i][j] = 1;
            }
            else {
                old_picture[i][j] = 0;
            }
        }
    }

    int **new_picture = (int **) malloc(Info_about_header.Height * sizeof(int *));

    for (int i = 0; i < Info_about_header.Height; ++i) {
        new_picture[i] = (int *) malloc(Info_about_header.Width * sizeof(int));
    }

    for (int i = 0; i < Info_about_header.Height; i++) {
        for (int j = 0; j < Info_about_header.Width; j++) {

            if (isAlive(rgb_colour[i][j]) == 1) {
                new_picture[i][j] = 1;
            }
            else {
                new_picture[i][j] = 0;
            }
        }
    }

    fclose(file);

    char str[50];
    char path[100];

    int up, left, down, right;
    int count_of_deathes;

    for (int iter = 0; iter < max_iter; iter++) {
        for (int i = 0; i < Info_about_header.Height; i++) {

            up = i - 1;
            down = i + 1;

            if (i == 0) {
                up = Info_about_header.Height - 1;
            }

            if (i == Info_about_header.Height - 1) {
                down = 0;
            }

            for (int j = 0; j < Info_about_header.Width; j++) {

                left = j - 1;
                right = j + 1;

                if (j == 0) {
                    left = Info_about_header.Width - 1;
                }

                if (j == Info_about_header.Width - 1) {
                    right = 0;
                }

                count_of_deathes = old_picture[up][left] + old_picture[up][j] + old_picture[up][right] + old_picture[i][left] + old_picture[i][right] + old_picture[down][left] + old_picture[down][j] + old_picture[down][right];

                if (old_picture[i][j] == 1) {
                    if (count_of_deathes < 2 || count_of_deathes > 3) {
                        new_picture[i][j] = 0;
                    }
                    else {
                        new_picture[i][j] = 1;
                    }
                }
                else {
                    if (count_of_deathes == 3) {
                        new_picture[i][j] = 1;
                    }
                    else {
                        new_picture[i][j] = 0;
                    }
                }
            }
        }

        for (int i = 0; i < Info_about_header.Height; i++) {
            for (int j = 0; j < Info_about_header.Width; j++) {
                old_picture[i][j] = new_picture[i][j];
            }
        }

        if (iter % dump_freq == 0) {

            memset(str, 0, 50);
            memset(path, 0, 100);
            sprintf(str, "%.bmp", iter);
            strcpy(path, Output);
            strcat(path, str);

            file = fopen(path, "w");

            makeBmp(file, header, Info_about_header, field_to_rgb(old_picture, Info_about_header));

            fclose(file);
        }
    }
}

//.\finalgame.exe --input birds.bmp --output output --max_iter 50 --dump_freq 2