#include <iostream>
using namespace std;

long long merge(int mas_1[], int mas_2[], int start, int midddle, int end) {
    int i = start;
    int j = midddle + 1;
    int s = start;
    long long count = 0;

    while ((i <= midddle) && (j <= end)) {
        if (mas_1[i] <= mas_1[j]) {
            mas_2[s] = mas_1[i];
            ++s;
            ++i;
        }
        else {
            mas_2[s] = mas_1[j];
            ++s;
            ++j;
            count += midddle - i + 1;
        }
    }

    while (i <= midddle) {
        mas_2[s] = mas_1[i];
        ++s;
        ++i;
    }

    while (j <= end) {
        mas_2[s] = mas_1[j];
        ++s;
        ++j;
    }

    for (i = start; i <= end; ++i) {
        mas_1[i] = mas_2[i];
    }

    return count;
}

long long mergeSort(int mas_1[], int mas_2[], int start, int end) {
    long long count = 0;

    if (start < end) {
        int mid = (start + end) / 2;

        count += mergeSort(mas_1, mas_2, start, mid);
        count += mergeSort(mas_1, mas_2, mid + 1, end);

        count += merge(mas_1, mas_2, start, mid, end);
    }

    return count;
}

int main() {
    int n = 0;
    cin >> n;
    int mas_input[n];
    int mas_dop[n];

    for (int i = 0; i < n; i++) {
        cin >> mas_input[i];
    }
    long long count = 0;

    count = mergeSort(mas_input, mas_dop,0, n - 1);

    cout << count;
    return 0;
}