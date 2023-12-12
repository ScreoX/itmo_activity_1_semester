#include <iostream>
#include <vector>
using namespace std;

struct Num {
    long long base;
    long long num;
};

class Heap {
public:
    vector <Num> mas;

    void siftUp(long long v) {
        while (v != 0) {
            long long p = (v - 1) / 2;
            if (mas[p].num > mas[v].num) {
                swap(mas[p], mas[v]);
            }
            v = p;
        }
    }
    void siftDown(long long v) {
        while (v < mas.size()) {
            long long l = v * 2 + 1;
            long long r = v * 2 + 2;
            long long i = v;
            if (l < mas.size() && mas[i].num > mas[l].num) {
                i = l;
            }
            if (r < mas.size() && mas[i].num > mas[r].num) {
                i = r;
            }
            if (i == v) {
                break;
            }
            swap(mas[v], mas[i]);
            v = i;
        }
    }
    void insert(long long val1, long long val2) {
        Num val;
        val.base = val1;
        val.num = val2;
        mas.push_back(val);
        siftUp(mas.size() - 1);
    }

    Num extract_min() {
        swap(mas[0], mas[mas.size() - 1]);
        mas.pop_back();
        siftDown(0);
        return mas[mas.size()];
    }

};

void quick_sort(long long *mas, long long left, long long right)
{
    long long i = left;
    long long j = right;
    long long pivot = mas[(i+j)/2+1];

    while (i <= j)
    {
        while (mas[i] < pivot)
            i++;
        while (mas[j] > pivot)
            j--;
        if (i <= j)
        {
            swap(mas[i],mas[j]);
            i++;
            j--;
        }
    }
    if (j > left)
        quick_sort(mas, left, j);
    if (i < right)
        quick_sort(mas, i, right);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    long long n;
    cin >> n;
    Heap heapchik;
    long long *v = new long long[30000000];
    long long cnt = 0;
    long long *a = new long long[30000000];
    for (long long i = 0; i < 6000000; i++)
        a[i] = i;
    for (long long p = 2; p < 6000000; p++)
    {
        if (a[p] != 0)
        {
            v[cnt] = a[p];
            ++cnt;
            if (cnt == n) {
                break;
            }
            for (long long j = p*p; j < 6000000; j += p)
                a[j] = 0;
        }
    }

    long long count = 0;
    long long *result_mas = new long long[30000000];

    for (long long i = 0; i < cnt; i++) {
        heapchik.insert(v[i], v[i]);
    }

    long long base, num;
    long long total_count = 0;
    while (count < n) {
        Num minimal = heapchik.extract_min();
        base = minimal.base;
        num = minimal.num;
        long long new_num = num;
        heapchik.insert(base, num * num);
        result_mas[total_count] = base;
        while (new_num / base != 1) {
            ++total_count;
            new_num = new_num / base;
            result_mas[total_count] = base;
        }
        ++count;
        ++total_count;
    }
    cout << total_count << '\n';
    quick_sort(result_mas, 0, total_count - 1);
    for (long long i = 0; i < total_count; i++) {
        cout << result_mas[i] << " ";
    }


    return 0;
}
