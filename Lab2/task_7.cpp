#include <iostream>
using namespace std;

void quick_sort(long long mas[][2], long long left, long long right)
{
    long long i = left;
    long long j = right;
    long long pivot = mas[(i+j)/2][0];

    while (i <= j)
    {
        while (mas[i][0] < pivot)
            i++;
        while (mas[j][0] > pivot)
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
    long long n;
    cin >> n;

    long long mas[n][2];
    for (long long i = 0; i < n; i++) {
        cin >> mas[i][0] >> mas[i][1];
    }


    quick_sort(mas, 0 , n - 1);


    long long day = 0;
    int mark = 0;
    long long summs[n];
    long long summa = 0;
    for (int i = 0; i < n; i++) {
        if (mark == 0) {
            summa = (mas[i][1] - (mas[i][0] + day));
            summs[i] = summa;
            day += mas[i][0];
            mark = 1;
        }
        else {
            summa = (mas[i][1] - (mas[i][0] + day));
            day += mas[i][0];
            summs[i] = summa;
        }
    }
    summa = 0;
    for (int i = 0; i < n; i++) {
        summa += summs[i];
    }

    cout << summa;
    return 0;
}
