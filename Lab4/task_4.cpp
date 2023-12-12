#include <iostream>
#include <vector>

using namespace std;

struct City {
    long long code;
    long long val;
};

class Heap {
public:
    vector<City> mas;

    void siftUp(long long v) {
        while (v != 0) {
            long long p = (v - 1) / 2;
            if (mas[p].val == mas[v].val) {
                if (mas[v].code > mas[p].code) {
                    swap(mas[p], mas[v]);
                }
            }
            if (mas[p].val < mas[v].val) {
                swap(mas[p], mas[v]);
            }
            v = p;
        }
    }


    void siftDown(int v) {
        while (2 * v + 1 < mas.size()) {
            int l = 2 * v + 1;
            int r = 2 * v + 2;
            int i = l;
            if ((r < mas.size()) && (mas[r].val > mas[l].val)) {
                i = r;
            }
            if ((r < mas.size()) && (mas[r].val == mas[l].val)) {
                if (mas[l].code > mas[r].code) {
                    i = l;
                }
                else {
                    i = r;
                }
            }

            if (mas[v].val == mas[i].val) {
                if (mas[i].code < mas[v].code) {
                    swap(mas[i], mas[v]);
                }
            }
            if (mas[i].val < mas[v].val) {
                break;
            }
            swap(mas[i], mas[v]);
            v = i;
        }
    }

    void insert(City val) {
        mas.push_back(val);
        siftUp(mas.size() - 1);
    }

    void delete_max_el() {
        swap(mas[0], mas[mas.size() - 1]);
        mas.pop_back();
        siftDown(0);
    }


    bool empty() {
        return mas.empty();
    }

    void find_element(long long val) {
        for (int i = 0; i < mas.size(); i++) {
            if (mas[i].code == val) {
                swap(mas[i], mas[mas.size() - 1]);
                mas.pop_back();
                siftDown(i);
                siftUp(i);
                return;
            }
        }
    }
};

int main() {
    long long n;
    cin >> n;
    City mas_money[n];
    City mas_rating[n];
    Heap heapchik_rating, heapchik_money;
    vector<long long> result_cities;
    for (long long i = 0; i < n; i++) {
        long long x, y, z;
        cin >> x >> y >> z;

        mas_money[i].code = x;
        mas_rating[i].code = x;

        mas_rating[i].val = y;
        mas_money[i].val = z;

        heapchik_rating.insert(mas_rating[i]);
        heapchik_money.insert(mas_money[i]);
    }

    long long calls;
    cin >> calls;
    string mas_calls[calls];
    vector<long long> result_calls;
    long long count_calls = 0;
    for (int i = 0; i < calls; i++) {
        string call;
        cin >> call;
        mas_calls[i] = call;
    }
    while (!heapchik_rating.empty()) {
        if (heapchik_rating.mas[0].code == heapchik_money.mas[0].code) {
            result_cities.push_back(heapchik_rating.mas[0].code);
            heapchik_money.delete_max_el();
        } else if (count_calls < calls) {
            result_calls.push_back(heapchik_rating.mas[0].code);
            if (mas_calls[count_calls] == "YES") {
                result_cities.push_back(heapchik_rating.mas[0].code);
                ++count_calls;

            } else if (mas_calls[count_calls] == "NO") {
                ++count_calls;
            }
            heapchik_money.find_element(heapchik_rating.mas[0].code);
        }
        heapchik_rating.delete_max_el();
        heapchik_money.siftDown(0);
    }

    if (!(result_calls.empty())) {
        for (int i = 0; i < result_calls.size(); i++) {
            cout << result_calls[i] << " ";
        }
        cout << '\n';
    }

    for (int i = 0; i < result_cities.size(); i++) {
        cout << result_cities[i] << " ";
    }
    return 0;
}

//3
//1 2 2
//2 3 3
//3 2 2
//4
//NO
//NO
//NO
//NO
//
//2
//1 4 9
//2 4 8
//1
//NO
//
//2
//1 2 2
//2 2 2
//2
//NO
//NO
//
//3
//1 1 1
//2 1 1
//3 1 1
//3
//NO
//NO
//NO
//
//2
//2 9 1
//3 2 1
//1
//NO
//
//
//2
//1 2 1
//2 2 7
//0
//
//3
//1 5 5
//2 7 7
//3 7 7
//0
//
//3
//1 5 5
//2 5 5
//3 5 5
//0