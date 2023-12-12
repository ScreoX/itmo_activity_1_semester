#include <iostream>
using namespace std;

int main() {

    int t, n;
    char a,b;
    int ball, krai_l, krai_r;
    cin >> t;
    int mas[t][1000];
    int mas_n[t];
    for (int i = 0; i < t; i++) {
        cin >> n;
        mas_n[i] = n;
        krai_l = 15;
        krai_r = 30;
        int mark = 0;
        for (int j = 0; j < n; j++) {
            cin >> a >> b >> ball;
            if (mark == 1)
                mas[i][j] = -1;
            else {
                if (a == '>') {
                    if (ball <= krai_r) {
                        if (krai_l < ball) {
                            krai_l = ball;
                            mas[i][j] = krai_l;
                        } else {
                            mas[i][j] = krai_l;
                        }
                    } else {
                        mas[i][j] = -1;
                        mark = 1;
                    }
                } else if (a == '<') {
                    if (ball >= krai_l) {
                        if (ball < krai_r) {
                            krai_r = ball;
                            mas[i][j] = krai_l;
                        } else
                            mas[i][j] = krai_l;
                    } else {
                        mas[i][j] = -1;
                        mark = 1;
                    }
                }
            }
        }
    }
    for (int k = 0; k < t; k++) {
        for (int l = 0; l < mas_n[k]; l++) {
            cout << mas[k][l] << '\n';
        }
    }
    return 0;
}