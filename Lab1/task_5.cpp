#include <iostream>
using namespace std;

int main() {
    long int n;
    int count = 0;
    cin >> n;
    char stroka[n];
    for (int i = 0; i < n; i++) {
        cin >> stroka[i];
    }
    if (n % 2 != 0) {
        for (int i = 0, j = n - 1; i < j ; i++, --j) {
            if (stroka[i] != stroka[j]) {
                ++count;
                if (stroka[i] == stroka[j - 1])
                    --j;
                else if (stroka[j] == stroka[i + 1])
                    ++i;
                else if (stroka[i] != stroka[j - 1] || stroka[j] != stroka[i + 1]) {
                    ++count;
                    break;
                }
            }
        }
    }
    if (n % 2 == 0) {
        for (int i = 0, j = n - 1; i < j ; i++, j--) {
            if (stroka[i] != stroka[j]) {
                ++count;
                if (j - i == 1)
                    break;
                else {
                    if (stroka[i] == stroka[j - 1])
                        --j;
                    else if (stroka[j] == stroka[i + 1])
                        ++i;
                    else if (stroka[i] != stroka[j - 1] || stroka[j] != stroka[i + 1]) {
                        ++count;
                        break;
                    }
                }
            }
        }
    }
    if (count < 2)
        cout << "YES";
    else
        cout << "NO";
    return 0;
}