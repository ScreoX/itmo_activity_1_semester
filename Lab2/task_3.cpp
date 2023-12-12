#include <iostream>
using namespace std;

void merge(long long summs[], int start, int midddle, int end) {
    int left = midddle - start + 1;
    int right = end - midddle;

    long long left_summ[left], right_summ[right];

    for (int i = 0; i < left; i++) {
        left_summ[i] = summs[start + i];
    }

    for (int j = 0; j < right; j++) {
        right_summ[j] = summs[midddle + j + 1];
    }
    int i = 0, j = 0, k = start;
    while ((i < left) && (j < right)) {
        if (left_summ[i] <= right_summ[j]) {
            summs[k] = left_summ[i];
            i++;
        }
        else {
            summs[k] = right_summ[j];
            j++;
        }
        k++;
    }

    while (i < left) {
        summs[k] = left_summ[i];
        ++i;
        ++k;
    }

    while (j < right) {
        summs[k] = right_summ[j];
        ++j;
        ++k;
    }
}

void mergeSort(long long summs[], int start, int end) {

    if (start < end) {
        int middle = start + (end - start) / 2;

        mergeSort(summs,  start, middle);
        mergeSort(summs,  middle + 1, end);

        merge(summs , start, middle, end);
    }
}
int main() {
    int size;
    cin >> size;

    long long mas[size];
    long long summa = 0;
    long long spisok[size];


    for (int i = 0; i < size; i++) {
        cin >> mas[i];
    }

    mergeSort(mas, 0, size - 1);

    int i = size - 1;
    int k = 0;
    int count = 0;
    while (i > 0) {
        if (mas[i] == mas[i - 1]) {
            spisok[k] = mas[i];
            i -= 2;
            ++k;
            ++count;
        }
        else if (mas[i] - mas[i - 1] == 1) {
            spisok[k] = mas[i - 1];
            i -= 2;
            ++k;
            ++count;
        }
        else {
            i -= 1;
        }
    }

    for (int l = 0; l < k; l+= 2) {
        if (k % 2 != 0) {
            if (l == k - 1) {
                break;
            }
            else {
                summa += (spisok[l] * spisok[l + 1]);
            }
        }
        else {
            summa += (spisok[l] * spisok[l+1]);
        }
    }
    cout << summa;
    return 0;
}