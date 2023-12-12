#include <iostream>
using namespace std;

int main() {
    int n;
    int mark = 0;
    long int summa_r = 0;
    long int summa_l = 0;
    long int summa_total = 0;
    cin >> n;
    long int mas[n+1];
    mas[0] = 0;
    for (long int i = 1; i <= n; i++) {
        cin >> mas[i];
        summa_total += mas[i];
    }

    for (long int j = 1; j <(n+1) ; j++) {
        summa_l += mas[j-1];
        summa_r = summa_total - summa_l - mas[j];
        if (summa_r == summa_l) {
            cout << j-1;
            mark = 1;
            break;
        }
    }
    if (mark != 1)
        cout << "-1";
    return 0;
}

