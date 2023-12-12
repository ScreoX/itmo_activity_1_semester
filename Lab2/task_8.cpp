#include <iostream>
using namespace std;

int insertion(int mas[], int n) {
    while (true) {
        int flag = 0;
        for (int i = 0; i < (n - 1); i++) {
            if (mas[i] - 1 == mas[i + 1]) {
                return 0;
            }
            else if (mas[i] > mas[i + 1]) {
                mas[i] -= 1;
                mas[i + 1] += 1;
                swap(mas[i], mas[i + 1]);
            }
        }

        for (int i = 0; i < (n - 1); i++) {
            if (mas[i] > mas[i + 1]) {
                flag = 1;
                break;
            }
        }

        if (flag != 1) {
            return 1;
        }
    }
}

int main() {
    int n;
    cin >> n;
    int mas[n];

    for (int i = 0; i < n; ++i) {
        cin >> mas[i];
    }

    int flag = insertion(mas,n);

    if (flag == 1) {
        for (int i = 0; i < n; ++i) {
            cout << mas[i] << " ";
        }
    }
    else {
        cout << ":(";
    }

    return 0;
}


