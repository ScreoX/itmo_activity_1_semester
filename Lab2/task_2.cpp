#include <iostream>
using namespace std;

void quick_sort(int mas[], int left, int right)
{
    int i = left;
    int j = right;
    int pivot = mas[(i+j)/2+1];

    while (i <= j)
    {
        while (mas[i] < pivot)
            i++;
        while (mas[j] > pivot)
            j--;
        if (i <= j)
        {
            swap(mas[i],mas[j]);
            i++;
            j--;
        }
    }
    if (j > left)
        quick_sort(mas, left, j);
    if (i < right)
        quick_sort(mas, i, right);
}

int main() {
    int size;

    cin >> size;

    int mas[size];

    for (int i = 0; i < size; i++) {
        cin >> mas[i];
    }

    quick_sort(mas, 0, size - 1);

    for (int i = 0; i < size; i++) {
        cout << mas[i] << ' ';
    }
    return 0;
}

