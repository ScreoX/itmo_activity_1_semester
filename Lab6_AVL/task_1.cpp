#include <iostream>
using namespace std;

struct Info_About_Node {
    int index_node;
    int index_left_child;
    int index_right_child;
};

int main() {

    int n;
    cin >> n;

    Info_About_Node mas_info[n];

    int result_mas[n];

    int x, y, z, left_child, right_child;

    for (int i = 0; i < n; i++) {
        cin >> x >> y >> z;
        mas_info[i].index_left_child = y;
        mas_info[i].index_right_child = z;
    }

    for (int i = 0; i < n; i++) {
        result_mas[i] = 0;
    }

    for (int i = n; i > 0; i--) {

        left_child = mas_info[i - 1].index_left_child;
        right_child = mas_info[i - 1].index_right_child;

        if (result_mas[left_child] > result_mas[right_child]) {
            result_mas[i] = 1 + result_mas[left_child];
        } else {
            result_mas[i] = 1 + result_mas[right_child];
        }
    }

    for (int i = 0; i < n; i++) {
        cout << result_mas[mas_info[i].index_right_child] - result_mas[mas_info[i].index_left_child] << "\n";
    }

    return 0;
}