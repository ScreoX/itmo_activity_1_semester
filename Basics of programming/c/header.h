#ifndef header_c
#define header_c

typedef struct {
    int x1, y1;
    int x2, y2;
    int x3, y3;
    int x4, y4;
} Rectangle;

int Area(Rectangle rect);

int Perimeter(Rectangle rect);

#endif
