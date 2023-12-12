#include <iostream>
#include <vector>
using namespace std;

struct Mas_of_two {
    long long salary;
    long long working_time;
};

class Heap {
public:
    vector <Mas_of_two> mas;

    void siftUp_for_salary(long long v) {
        while (v != 0) {
            long long p = (v - 1) / 2;
            if (mas[p].salary > mas[v].salary) {
                swap(mas[p], mas[v]);
            }
            v = p;
        }
    }

    void siftUp_for_time(long long v) {
        while (v != 0) {
            long long p = (v - 1) / 2;
            if (mas[p].working_time > mas[v].working_time) {
                swap(mas[p], mas[v]);
            }
            else if (mas[p].working_time == mas[v].working_time) {
                if (mas[p].salary > mas[v].salary) {
                    swap(mas[p], mas[v]);
                }
            }
            v = p;
        }
    }

    void siftDown_for_time(long long v) {
        while (v < mas.size()) {
            long long l = v * 2 + 1;
            long long r = v * 2 + 2;
            long long i = v;
            if (l < mas.size() && mas[i].working_time > mas[l].working_time) {
                i = l;
            }
            if (r < mas.size() && mas[i].working_time > mas[r].working_time) {
                i = r;
            }
            if (i == v) {
                break;
            }
            swap(mas[v], mas[i]);
            v = i;
        }
    }

    void siftDown_for_salary(long long v) {
        while (v < mas.size()) {
            long long l = v * 2 + 1;
            long long r = v * 2 + 2;
            long long i = v;
            if (l < mas.size() && mas[i].salary > mas[l].salary) {
                i = l;
            }
            if (r < mas.size() && mas[i].salary > mas[r].salary) {
                i = r;
            }
            if (i == v) {
                break;
            }
            swap(mas[v], mas[i]);
            v = i;
        }
    }

    void insert_for_busy(Mas_of_two val) {
        mas.push_back(val);
        siftUp_for_time(mas.size() - 1);
    }
    void insert_for_free(Mas_of_two val) {
        mas.push_back(val);
        siftUp_for_salary(mas.size() - 1);
    }

    Mas_of_two extract_min_for_salary() {
        swap(mas[0], mas[mas.size() - 1]);
        mas.pop_back();
        siftDown_for_salary(0);
        return mas[mas.size()];
    }
    Mas_of_two extract_min_for_time() {
        swap(mas[0], mas[mas.size() - 1]);
        mas.pop_back();
        siftDown_for_time(0);
        return mas[mas.size()];
    }

    bool empty() {
        return mas.empty();
    }
};


int main() {
    long long n,m;
    long long total_salary = 0;
    cin >> n >> m;
    Heap heapchik_for_free, heapchik_for_busy;
    Mas_of_two mas[n];

    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        mas[i].salary = x;
        mas[i].working_time = 0;
        heapchik_for_free.insert_for_free(mas[i]);
    }

    for (int i = 0; i < m; i++) {
        long long time_start, time_work;
        cin >> time_start >> time_work;
        if (!heapchik_for_busy.empty()) {
            while (heapchik_for_busy.mas[0].working_time <= time_start && !heapchik_for_busy.empty()) {
                Mas_of_two min_for_busy = heapchik_for_busy.extract_min_for_time();
                heapchik_for_free.insert_for_free(min_for_busy);
            }
        }
        if (!heapchik_for_free.empty()) {
            Mas_of_two min = heapchik_for_free.extract_min_for_salary();
            total_salary += min.salary * time_work;
            min.working_time = time_start + time_work;
            heapchik_for_busy.insert_for_busy(min);
        }
    }
    cout << total_salary;

    return 0;
}
