#include <iostream>
using namespace std;

void merge(long long summs[], int nomera[], int start, int midddle, int end) {
    int left = midddle - start + 1;
    int right = end - midddle;

    long long left_summ[left], right_summ[right];
    int left_films[left], right_films[right];

    for (int i = 0; i < left; i++) {
        left_summ[i] = summs[start + i];
        left_films[i] = nomera[start + i];
    }

    for (int j = 0; j < right; j++) {
        right_summ[j] = summs[midddle + j + 1];
        right_films[j] = nomera[midddle + j + 1];
    }
    int i = 0, j = 0, k = start;
    while ((i < left) && (j < right)) {
        if (left_summ[i] >= right_summ[j]) {
            summs[k] = left_summ[i];
            nomera[k] = left_films[i];
            i++;
        }
        else {
            summs[k] = right_summ[j];
            nomera[k] = right_films[j];
            j++;
        }
        k++;
    }

    while (i < left) {
        summs[k] = left_summ[i];
        nomera[k] = left_films[i];
        ++i;
        ++k;
    }

    while (j < right) {
        summs[k] = right_summ[j];
        nomera[k] = right_films[j];
        ++j;
        ++k;
    }
}

void mergeSort(long long summs[], int nomera[], int start, int end) {

    if (start < end) {
        int middle = start + (end - start) / 2;

        mergeSort(summs, nomera, start, middle);
        mergeSort(summs, nomera, middle + 1, end);

        merge(summs , nomera, start, middle, end);
    }
}
int main() {
    int n,m,k;

    cin >> n >> m >> k;

    long long mas_kritikov[n];
    int mas_nums[m];

    for (int i = 0; i < n; i++) {
        cin >> mas_kritikov[i];
    }

    long long summ[m];

    for (int i = 0; i < m; i ++) {
        mas_nums[i] = i + 1;
    }
    for (int i = 0; i < m; i++) {
        summ[i] = 0;
        for (int j = 0; j < n; j++) {
            int films = 0;
            cin >> films;
            summ[i] += mas_kritikov[j] * films;
            summ[i] %= 1000000007;
        }
    }

    mergeSort(summ, mas_nums, 0 , m - 1);

    for (int i = 0; i < k;i++) {
        cout << mas_nums[i] << " ";
    }
    return 0;
}
