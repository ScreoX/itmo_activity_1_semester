#include <iostream>
using namespace std;

int main() {
    int size;

    cin >> size;

    int mas[size];

    for (int i = 0; i < size; i++) {
        mas[i] = i + 1;
    }
    for (int i = 2; i < size; i++) {
        swap(mas[i], mas[i / 2]);
    }
    for (int i = 0; i < size; i++) {
        cout << mas[i] << ' ';
    }
    return 0;
}