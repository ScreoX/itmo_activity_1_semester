#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int mas[n];
    for (int i = 0; i < n; ++i) {
        cin >> mas[i];
    }
    for (int i = 1; i < n; ++i) {
        int key = mas[i];
        int j = i - 1;

        while (j >= 0 && mas[j] > key) {
            mas[j + 1] = mas[j];
            j--;
        }
        mas[j + 1] = key;
    }
    for (int i = 0; i < n; ++i) {
        cout << mas[i] << " ";
    }
    return 0;
}