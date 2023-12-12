#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "header.h"
#include <string.h>
#include "time.h"
//lab 1

void lab1() {
    char str[4];
    float a;
    scanf("%s",str);
    scanf("%f", &a);
    printf("%s\n", str);
    printf("%f", a);
}

//lab 2

void lab2() {
    double z1,z2,a;
    scanf("%lf", &a);
    z1 = ((1-2*pow(sin(a/57.3),2))) / (1+sin((2*a)/57.3));
    z2 = (1 - tan(a/57.3)) / (1 + tan(a/57.3));
    printf("%lf\n", z1);
    printf("%lf", z2);

}

//lab 3

void lab3() {
    int x;
    int y;
    int result = 0;
    scanf("%d", &x);
    printf("%x\n", x);
    printf("%o\n", x);
    int new_x = x << 3;
    printf("%o\n", new_x);
    scanf("%o", &y);
    printf("%o", y & x);
}

//lab 4

void lab4() {
    int num_1;
    int start = 11, end = 12;
    scanf("%d", &num_1);
    int res = 0;
    res = ((num_1 >= start) && (num_1 <= end));
    printf("%d", res);
    int num_2;
    scanf("%o", &num_2);
    int chislo = num_2 >> 11;
    printf("%d", 1 & chislo);
}

//lab 5

void lab5() {
    int mas[7];

    for (int i = 0; i < 7; i++) {
        scanf("%d", &mas[i]);
    }

    for (int i = 0; i < 7; i++) {
        if (i == 6) {
            printf("%d\n", mas[i]);
        }
        else {
            printf("%d ", mas[i]);
        }
    }

    int matrix_a[2][2] = {{1,2},{3,1}};

    int matrix_b[2][2] = {{1,1},{0,2}};

    int matrix_c[2][2] = {{matrix_a[0][0] * matrix_b[0][0] + matrix_a[0][1] * matrix_b[1][0],
                                  matrix_a[0][0] * matrix_b[0][1] + + matrix_a[0][1] * matrix_b[1][1]},
                          {matrix_a[1][0] * matrix_b[0][0] + + matrix_a[1][1] * matrix_b[1][0],
                                  matrix_a[1][0] * matrix_b[0][1] + + matrix_a[1][1] * matrix_b[1][1]}};
    printf("%d %d\n", matrix_c[0][0], matrix_c[1][0]);
    printf("%d %d\n", matrix_c[0][1], matrix_c[1][1]);
}

//lab 6

void lab6() {
    int* mas = (int*)malloc(4 * sizeof(int));
    mas[0] = 'a';
    mas[1] = 'b';
    mas[2] = 'c';
    mas[3] = 'd';

    for (int i = 0; i < 4; i++) {
        printf("%c ", *(mas + i));
    }

    free(mas);
}

//lab 7

struct Square {
    double x, y;
    int storona;
};
int area(struct Square square) {
    return square.storona * square.storona;
}
int perimetr(struct Square square) {
    return square.storona * 4;
}
enum Days {
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
} Days;
struct Keyboard {
    unsigned short NumLock : 1;
    unsigned short CapsLock : 1;
    unsigned short ScrollLock : 1;
};
void lab7() {

    struct Square square;
    printf("Понедельник стоит под номером %d\n", Monday + 1);

    printf("Напишите координаты одной точки\n");
    scanf("%f %f", &square.x, &square.y);
    printf("Введите длину стороны квадрата\n");
    scanf("%d", &square.storona);
    printf("Площадь квадрата: %d\n", area(square));
    printf("Периметр квадрата: %d\n", perimetr(square));
    int* mas = (int*)malloc(7 * sizeof(int));


    int num;
    printf("Введите число в 16-ичной сс: \n");
    scanf("%x", &num);

    union {
        unsigned long num;
        struct Keyboard keyboard;
    } un;
    un.num = num;

    printf("NumLock: %s\n", (un.keyboard.NumLock ? "вкл" : "выкл"));
    printf("CapsLock: %s\n", (un.keyboard.CapsLock ? "вкл" : "выкл"));
    printf("ScrollLock: %s\n", (un.keyboard.ScrollLock ? "вкл" : "выкл"));

}

//lab 8

void lab8 () {
    int n;
    printf("Введите первую и вторую строку\n");
    char* str1 = (char*)malloc(sizeof(char) * 15);
    char* str2 = (char*)malloc(sizeof(char) * 15);
    char* str3 = (char*)malloc(sizeof(char) * (15 + 15 + 1));
    int i = 0, j = 0;

    fgets(str1, 15, stdin);
    fgets(str2, 15, stdin);
    str1[strcspn(str1, "\n")] = '\0';
    str2[strcspn(str2, "\n")] = '\0';


    printf("Введите, число n\n");
    scanf("%d", &n);

    while (str1[i] != '\0') {
        str3[i] = str1[i];
        i++;
    }

    while (j < n) {
        str3[i] = str2[j];
        ++i;
        ++j;
    }

    str3[i] = '\0';
    printf("%s\n", str3);

    for (i = 0; i < n; i++) {
        if (str1[i] > str2[i]) {
            printf("элемент %c больше, чем %c\n", str1[i], str2[i]);
        }
        else if (str1[i] < str2[i]) {
            printf("элемент %c больше, чем %c\n", str2[i], str1[i]);
        }
        else {
            printf("%c и %c равны\n", str1[i], str2[i]);
        }
    }

    char str4[n];

    int f = 0;
    while (f < n) {
        str4[f] = str1[f];
        ++f;
    }
    printf("Первые %d элемента 1 строки: %s\n", n, str4);

    int len_otrezka = strcspn(str1, str2);
    printf("Длина отрезка 1 строки, содержащего символы из множества символов 2 строки: %d\n", len_otrezka);


    char *flag = strtok(str1, str2);
    while (flag != 0) {
        printf("Лексема: %s\n", flag);
        flag = strtok(0, str2);
    }
    free(str1);
    free(str2);
    free(str3);

}
//lab 9

void lab9() {
    char Propisnie[26];
    char Strochnie[26];
    char digits[10];

    int count_propisnie = 0;
    int count_strochie = 0;
    int count_digits = 0;

    for (int i = 0; i < 26; i++) {
        Propisnie[i] = 'A' + i;
    }

    for (int i = 0; i < 26; i++) {
        Strochnie[i] = 'a' + i;
    }

    for (int i = 0; i < 10; i++) {
        digits[i] = '0' + i;
    }

    char* str = (char*)malloc(sizeof(char) * 50);

    fgets(str, 50, stdin);

    int len = 0;
    while (str[len] != '\0') {
        ++len;
    }

    for (int ind = 0; ind < len; ++ind) {
        for (int j = 0; j < 26; ++j) {
            if (str[ind] == Propisnie[j]) {
                ++count_propisnie;
            }
            if (str[ind] == Strochnie[j]) {
                ++count_strochie;
            }
            if (j < 10) {
                if (str[ind] == digits[j]) {
                    ++count_digits;
                }
            }
        }
    }

    printf("Прописные - %d\n", count_propisnie);
    printf("Строчные - %d\n", count_strochie);
    printf("Цифры - %d\n", count_digits);

    int minutes;
    int abon_fee;
    int extra_fee_of_every_minute;

    scanf("%d %d %d", &minutes, &abon_fee, &extra_fee_of_every_minute);

    int sum;

    if (minutes > 499) {
        minutes -= 499;
        sum = abon_fee + (minutes * extra_fee_of_every_minute);
    }
    else {
        sum = abon_fee;
    }

    printf("%d", sum);
}

//lab 10

int greatest_div(int first, int second) {
    while (second != 0)
    {
        int temp = second;
        second = first % second;
        first= temp;
    }
    return first;
}

int least_div(int a, int b) {
    return (a * b) / greatest_div(a, b);
}

void calculate_dist(int n, float** points, float** distances) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0, k = 0; j < n; ++j) {
            if (i != j) {
                float x1 = points[i][0];
                float y1 = points[i][1];
                float x2 = points[j][0];
                float y2 = points[j][1];
                float distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
                distances[i][k] = distance;
                ++k;
            }
        }
    }
}

void lab10() {
    int first;
    int second;

    scanf_s("%d %d", &first, &second);

    printf("Наименьшее общее кратное - %d\n", least_div(first, second));
    printf("Наибольший общий делитель - %d", greatest_div(first, second));

    printf("\n");


    int n = 0;
    scanf("%d", &n);

    float** mas_points = (float**)malloc(n * sizeof(float*));
    for (int i = 0; i < n; i++) {
        mas_points[i] = (float*)malloc(2 * sizeof(float));
    }

    for (int i = 0; i < n; i++) {
        printf("Координаты точки %d: \n", i + 1);
        float x, y;
        scanf("%f %f", &x, &y);
        mas_points[i][0] = x;
        mas_points[i][1] = y;
    }

    float** distances = (float**)malloc(n * sizeof(float*));
    for (int i = 0; i < n; i++) {
        distances[i] = (float*)malloc((n - 1) * sizeof(float));
    }

    calculate_dist(n, mas_points, distances);

    printf("Расстояния:\n");
    for (int i = 0; i < n; i++) {
        printf("До точки %d: ", i + 1);
        for (int j = 0; j < n - 1; j++) {
            printf("%f ", distances[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        free(mas_points[i]);
        free(distances[i]);
    }
    free(mas_points);
    free(distances);

}
// lab 11
void lab11() {

    Rectangle r;

    printf("%s", "Введите координаты 1 точки:");
    scanf_s("%d %d", &r.x1, &r.y1);
    printf("%s", "Введите координаты 2 точки:");
    scanf_s("%d %d", &r.x2, &r.y2);
    printf("%s", "Введите координаты 3 точки:");
    scanf_s("%d %d", &r.x3, &r.y3);
    printf("%s", "Введите координаты 4 точки:");
    scanf_s("%d %d", &r.x4, &r.y4);

    int area = Area(r);
    int perimeter = Perimeter(r);

    printf("Периметр: %d\n", perimeter);
    printf("Площадь: %d", area);

}
// lab 12
void lab12() {
    FILE* f;
    f = fopen("D:/c/c/for_lab_12.txt", "w");

    time_t current_data;
    struct tm* date;
    char mas_of_dates[11];

    time(&current_data);
    date = localtime(&current_data);

    for (int i = 0; i < 10; i++) {
        ++date->tm_mday;
        mktime(date);
        strftime(mas_of_dates, 11, "%d.%m.%Y", date);
        fprintf(f, "%s\n", mas_of_dates);
    }

    fclose(f);
}
int main( )
{
    lab12();
    return 0;
}

