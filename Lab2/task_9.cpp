#include <iostream>

using namespace std;

int partition(int mas[], int left, int right, int pivot_ind) {
    int pivot = mas[pivot_ind];
    int i = left;
    int j = right;
    int l = -1, r = -1;
    while (i <= j) {
        while (mas[i] < pivot) {
            ++i;
        }
        while (mas[j] > pivot) {
            --j;
        }
        if (i >= j) {
            break;
        }
        swap(mas[i], mas[j]);
        if (j == r && i == l) {
            ++i;
            --j;
        }
        l = i, r = j;
    }
    return i;
}

void quickSelect(int mas[], int left, int right, int k) {

    int pivot_ind = left;
    pivot_ind = partition(mas, left, right, pivot_ind);

    if (k == pivot_ind) {
        return;
    } else if (k < pivot_ind) {
        quickSelect(mas, left, pivot_ind - 1, k);
    } else {
        quickSelect(mas, pivot_ind + 1, right, k);
    }
}

int main() {
    int n;
    cin >> n;
    int k;
    cin >> k;
    int A, B, C;
    cin >> A >> B >> C;
    int a1, a2;
    cin >> a1 >> a2;
    int mas[n];
    mas[0] = a1;
    mas[1] = a2;
    for (int i = 2; i < n; ++i) {
        mas[i] = mas[i - 2] * A + mas[i - 1] * B + C;
    }
    quickSelect(mas, 0, n - 1, n - k);

    int ans = 0;
    for (int i = n - k; i < n; i++) {
        ans ^= mas[i];
    }
    cout << ans;
}