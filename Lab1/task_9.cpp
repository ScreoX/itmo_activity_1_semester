#include <iostream>
using namespace std;
int main() {
    unsigned long long x,y;
    cin >> x >> y;
    unsigned long long mas[250000] = {0};
    int count = 0;
    long long f = 1;
    long long i = 0;
    for (int a = 3; a < 62; a++) {
        for (int b = 1; b < a - 1; b++) {
            for (int c = 1; c < a-b; c++, i++) {
                mas[i] = (((f << b) - 1) << (a-b)) + ((f << c) - 1);
            }
        }
    }
    for (int j = 0; j < (250000 - 1); j++) {
        if ((mas[j] >= x) && (mas[j] <= y))
            ++count;
    }
    cout << count;
    return 0;
}