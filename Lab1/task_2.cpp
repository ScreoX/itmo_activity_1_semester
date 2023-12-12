#include <iostream>
using namespace std;
int main() {
    int n;
    long int k;
    cin >> n >> k;
    int new_mas[n];
    int mas[n];
    for (int i = 0; i < n; i++) {
        cin >> mas[i];
    }
    if (k > 0) {
        for (int j = 0; j < n; j++) {
            new_mas[(j + k) % n] = mas[j];
        }
    }
    if (k < 0) {
        for (int j  = 0; j < n; j++) {
            new_mas[j] = mas[(j-k)%n];
        }
    }
    for (int l = 0; l < n; l++) {
        cout << new_mas[l] << " ";
    }

    return 0;
}
