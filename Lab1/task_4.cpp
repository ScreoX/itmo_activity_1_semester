#include <iostream>

using namespace std;

int main() {
    int n,m,q,epizod,season;
    cin >> n >> m >> q;
    int count = n * m;
    int mas[n+1][m+1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            mas[i][j] = 0;
        }
    }
    for (int i = 1; i <= q; i++) {
        cin >> epizod >> season;
        if (mas[season][epizod] == 0) {
            --count;
            mas[season][epizod] = 1;
        }
    }
    cout << count << '\n';
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (mas[i][j] == 0)
                cout << j << " " << i << '\n';
        }
    }
    return 0;
}
