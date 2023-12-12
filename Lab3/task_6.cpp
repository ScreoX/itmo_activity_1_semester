#include <iostream>
using namespace std;

int proverka(int mas[], int rastoyanie, int n, int k) {
    int count_boyar = 1;
    int first_boyar = mas[0];
    for (int i = 1; i < n; i++) {
        if (mas[i] - first_boyar >= rastoyanie) {
            ++count_boyar;
            first_boyar = mas[i];
        }
    }
    if (count_boyar >= k) {
        return 1;
    } else {
        return 0;
    }
}

int bin_search(int mas[], int n, int k) {
    int left = 0;
    int right = mas[n - 1] - mas[0] + 1;
    while (right >= left + 2) {
        int middle = (left + right) / 2;
        if (proverka(mas, middle, n, k) == 1) {
            left = middle;
        } else {
            right = middle;
        }
    }
    return left;
}

int main() {
    int n, k;
    cin >> n >> k;
    int mas[n];
    for (int i = 0; i < n; i++) {
        cin >> mas[i];
    }
    cout << bin_search(mas, n, k);
    return 0;
}