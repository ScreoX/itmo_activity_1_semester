#include <iostream>
using namespace std;
int main() {
    long long n;
    cin >> n;
    long long mas[n];
    int count = 0;
    for (int i = 0; i < n; i++) {
        cin >> mas[i];
    }
    long long summa_pred = mas[n-1];
    for (int i = 0; i < n; i++) {
        if ((summa_pred & mas[i]) == 0) {
            summa_pred += mas[i];
        }
        else {
            summa_pred = mas[i];
        }
    }
    for (int i = 0; i < n; i++) {
        if ((summa_pred & mas[i]) == 0) {
            summa_pred += mas[i];
        }
        else {
            summa_pred = mas[i];
            ++count;
        }
    }
    if (count > 0)
        cout << count;
    else
        cout << 1;
    return 0;
}
