#include <iostream>

using namespace std;

void radixSort(char arr[], int k, int n) {
    char output[n][k];
    int count[256] = {0};
    for (int j = 0; j < k; j++) {
        for (int i = 0; i < n; i++) {
            count[arr[i][j]]++;
        }

        for (int i = 1; i <= 255; i++) {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            output[count[arr[i][j] - 1]][k] = arr[i][j];
            count[arr[i][j]]--;
        }

        for (int i = 0; i < n; i++) {
            arr[i][j] = output[i][k];
        }
    }
}

int main() {
    int n,k,t;
    cin >> n >> k >> t;
    char arr[k][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            cin >> arr[j][i];
        }
    }

    radixSort(**arr, n, k);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            cout << arr[j][i];
        }
        cout << '\n';
    }
    cout << endl;

    return 0;
}
//3 3 1
//bbb
//aba
//baa
// =
//aba
//baa
//bbb

//#include <iostream>
//#include <cstring>
//
//using namespace std;
//
//void radixSort(char arr[][100], int k, int n) {
//    char output[n][100];
//    for (int j = k - 1; j >= 0; j--) {
//        int count[256] = {0};
//        for (int i = 0; i < n; i++) {
//            ++count[arr[i][j]];
//        }
//        int temp = count[0];
//        count[0] = 0;
//        for (int i = 1; i <= 255; i++) {
//            int temp2 = count[i];
//            count[i] = temp;
//            temp += temp2;
//        }
//        for (int i = 0; i < n; i++) {
//            int s = arr[i][j];
//            output[count[s]][j] = arr[i][j];
//            ++count[s];
//        }
//    }
//}
//
//int main() {
//    int n, k, t;
//    cin >> n >> k >> t;
//    char arr[100][100];
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < k; j++) {
//            cin >> arr[i][j];
//        }
//    }
//
//    radixSort(arr, k, n);
//
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < k; j++) {
//            cout << arr[i][j];
//        }
//        cout << '\n';
//    }
//
//    return 0;
//}