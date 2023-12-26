#include <stdio.h>
#include <string.h>

void create_arc_file(char *file, int argc, char *argv[]) {
    FILE *arc_file = fopen(file, "wb");
    FILE *new_file;

    int mas_size[128];

    for (int i = 4; i < argc; i++) {
        
        new_file = fopen(argv[i], "rb");

        if (new_file == NULL) {
            continue;
        }
        fseek(new_file, 0, SEEK_END);
        mas_size[i - 4] = ftell(new_file);
        fseek(new_file, 0, SEEK_SET);
        fclose(new_file);
    }
    for (int i = 0; i < argc - 4; i++) {
        fprintf(arc_file, "%s %d\n", argv[i + 4], mas_size[i]);
    }
    fprintf(arc_file, " ");
    for (int i = 4; i < argc; i++) {
        
        new_file = fopen(argv[i], "rb");
        if (new_file == NULL) {
            continue;
        }
        else {
            printf("%s added\n", argv[i]);
        }
        while (getc(new_file) != EOF) {
            putc(getc(new_file), arc_file);
        }
        fclose(new_file);
    }
}

void show_list_with_archive_files(char *file1) {

    FILE *file = fopen(file1, "rb");
    char temp[128];

    for (int i = 0; i < 2; i++) {
        fscanf(file, "%s", temp);
        printf("%s\n", temp);
        fscanf(file, "%s", temp);
        fscanf(file, "%s", temp);
    }
    fclose(file);
}

void extract_file(char *file_needed_to_delete) {
    FILE *file = fopen(file_needed_to_delete, "rb+");
    int start_of_the_file = 0;
    int end_of_the_file;
    int temp;
    while (getc(file) != EOF) {
        temp = getc(file);
        start_of_the_file++;
        if (temp == '\n') {
            break;
        }
    }
    fseek(file, 0, SEEK_SET);
    
    char new_file[128] = {0};
    char empty_array[128] = {0};
    unsigned long long size_of_the_file;

    FILE *output_file;

    for (int i = 0; i < 2; i++) {
        
        fscanf(file, "%s %s %llu", new_file, empty_array, &size_of_the_file);
        output_file = fopen(new_file, "wb");
        
        if (output_file == NULL) {
            break;
        }
        
        end_of_the_file = ftell(file);
        fseek(file, start_of_the_file, SEEK_SET);
        start_of_the_file += size_of_the_file;
        
        while (size_of_the_file > 0) {
            putc(getc(file), output_file);
            size_of_the_file--;
        }
        
        fseek(file, end_of_the_file, SEEK_SET);
        fclose(output_file);
    }
}

int main(int argc, char *argv[]) {
    char *input_file;
    
    int i = 1;
    
    while (i < argc) {

        if (strcmp("--file", argv[i]) == 0) {
            input_file = argv[i + 1];
        }
        else if (strcmp("--create", argv[i]) == 0) {
            create_arc_file(input_file, argc, argv);
            break;
        }
        else if (strcmp("--extract", argv[i]) == 0) {
            extract_file(input_file);
        }
        else if (strcmp("--list", argv[i]) == 0) {
            show_list_with_archive_files(input_file);
        }
        
        i++;
    }
}