#include "header.h"

int Area(Rectangle rect) {
    int width, height;
    if (rect.x1 != rect.x2) {
        width = (rect.x2 - rect.x1);
    }
    else {
        width = (rect.x2 - rect.x3);
    }
    if (rect.y1 != rect.y2) {
        height = (rect.y2 - rect.y1);
    }
    else {
        height = (rect.y2 - rect.y3);
    }
    if (width * height < 0) {
        return -width * height;
    }
    return width * height;
}

int Perimeter(Rectangle rect) {
    int width, height;
    if (rect.x1 != rect.x2) {
        width = (rect.x2 - rect.x1);
    }
    else {
        width = (rect.x2 - rect.x3);
    }
    if (width < 0) {
        width = -width;
    }

    if (rect.y1 != rect.y2) {
        height = (rect.y2 - rect.y1);
    }
    else {
        height = (rect.y2 - rect.y3);
    }
    if (height < 0) {
        height = -height;
    }

    return 2 * (width + height);
}