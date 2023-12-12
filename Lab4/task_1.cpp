#include <iostream>
using namespace std;
int main() {
    int n; cin >> n;
    int mas[n];
    for (int i = 1; i <= n; i++) {
        cin >> mas[i];
    }
    bool flag = true;
    for (int i = 1; i <= n/2; i++) {
        if ((2*i + 1 <= n) && mas[i] > mas[2*i + 1]) {
            flag = false;
            break;
        }
        else if ((2*i<= n) && (mas[i] > mas[2*i])) {
            flag = false;
            break;
        }
    }
    if (flag) {
        cout << "YES";
    }
    else {
        cout << "NO";
    }
    return 0;
}