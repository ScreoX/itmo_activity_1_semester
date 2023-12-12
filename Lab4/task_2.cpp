#include <iostream>
#include <vector>
using namespace std;

class Heap {
public:
    vector <int> mas;
public:

    void siftUp(int v) {
        while (v != 0) {
            int p = (v - 1) / 2;
            if (mas[p] > mas[v]) {
                swap(mas[p], mas[v]);
            }
            v = p;
        }
    }
    void siftDown(int v) {
        while (v < mas.size()) {
            int l = v * 2 + 1;
            int r = v * 2 + 2;
            int i = v;
            if (l < mas.size() && mas[i] > mas[l]) {
                i = l;
            }
            if (r < mas.size() && mas[i] > mas[r]) {
                i = r;
            }
            if (i == v) {
                break;
            }
            swap(mas[v], mas[i]);
            v = i;
        }
    }
    void add(int val) {
        mas.push_back(val);
        siftUp(mas.size() - 1);
    }

    int extract_min() {
        if (mas.empty()) {
            return '*';
        }
        else {
            swap(mas[0], mas[mas.size() - 1]);
            mas.pop_back();
            siftDown(0);
            return mas[mas.size()];
        }
    }

    void decrease_key(int x, int y) {
        Heap newBin;
        bool flag = true;
        for (int ma : mas) {
            if (ma == x) {
                if (flag) {
                    newBin.add(y);
                    flag = false;
                }
                else {
                    newBin.add(x);
                }
            } else {
                newBin.add(ma);
            }
        }

        this->mas = newBin.mas;
    }

};

Heap merge(Heap first_mas, Heap second_mas) {
    Heap newBin;
    for (int ma : first_mas.mas) {
        newBin.add(ma);
    }
    for (int ma : second_mas.mas) {
        newBin.add(ma);
    }

    return newBin;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector <Heap> vectorchik(1000000);
    string command;
    int count = 0;
    while (cin >> command) {
        if (command == "create") {
            Heap new_mas;
            vectorchik[count] = new_mas;
            ++count;
        } else if (command == "insert") {
            int k = 0, x = 0;
            cin >> k >> x;
            vectorchik[k].add(x);
        } else if (command == "extract-min") {
            int k = 0;
            cin >> k;
            int ans = vectorchik[k].extract_min();
            if (ans == 42) {
                cout << '*' << '\n';
            }
            else {
                cout << ans << "\n";
            }
        } else if (command == "merge") {
            int k = 0, m = 0;
            cin >> k >> m;;
            vectorchik[count] = (merge(vectorchik[k], vectorchik[m]));
            ++count;
        } else if (command == "decrease-key") {
            int k = 0, x = 0, y = 0;
            cin >> k >> x >> y;
            vectorchik[k].decrease_key(x, y);
        }
    }
    return 0;
}