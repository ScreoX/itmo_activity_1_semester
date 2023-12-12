#include <iostream>
using namespace std;

void merge(long long summs[], long long start, long long midddle, long long end) {
    long long left = midddle - start + 1;
    long long right = end - midddle;

    long long left_summ[left], right_summ[right];

    for (int i = 0; i < left; i++) {
        left_summ[i] = summs[start + i];
    }

    for (int j = 0; j < right; j++) {
        right_summ[j] = summs[midddle + j + 1];
    }
    long long i = 0, j = 0, k = start;
    while ((i < left) && (j < right)) {
        if (left_summ[i] <= right_summ[j]) {
            summs[k] = left_summ[i];
            i++;
        }
        else {
            summs[k] = right_summ[j];
            j++;
        }
        k++;
    }

    while (i < left) {
        summs[k] = left_summ[i];
        ++i;
        ++k;
    }

    while (j < right) {
        summs[k] = right_summ[j];
        ++j;
        ++k;
    }
}

void mergeSort(long long summs[], long long start, long long end) {

    if (start < end) {
        long long middle = (start + end) / 2;

        mergeSort(summs,  start, middle);
        mergeSort(summs,  middle + 1, end);

        merge(summs , start, middle, end);
    }
}
long long left_binary_search(long long a[], long long n, long long x) {
    long long l = 0, r = n - 1, res = 0;

    while (l <= r) {
        long long mid = l + (r - l) / 2;
        if (a[mid] >= x) {
            r = mid - 1;
            res = mid;
        } else {
            l = mid + 1;
            res = l;
        }
    }
    return res;
}
long long right_binary_search(long long a[], long long n, long long x) {
    long long l = 0, r = n - 1, res = 0;

    while (l <= r) {
        long long mid = l + (r - l) / 2;
        if (a[mid] <= x) {
            l = mid + 1;
            res = mid;
        } else {
            r = mid - 1;
            res = r;
        }
    }
    return res + 1;
}
long long bin_search_of_bin_serches(long long mas_women[], long long mas_men[], long long n, long long k, long long left_section, long long right_section) {
    long long less, more;
    while (left_section <= right_section) {
        long long mid = (right_section + left_section) / 2;
        less = 0, more = 0;
        int i = 0;
        while (i < n) {
            less += left_binary_search(mas_women, n, mid - mas_men[i]); //кол-во сумм равных меньше мидовой суммы
            more += right_binary_search(mas_women, n, mid - mas_men[i]) - left_binary_search(mas_women, n, mid - mas_men[i]); //кол-во сумм равных мидовой, влючая ее
            ++i;
        }
        long long lower = less, higher = less + more - 1;
        if (higher < lower) {
            if (k < lower) {
                right_section = mid;
            }
            if (k > higher) {
                left_section = mid;
            }
        }
        else if (lower <= k && higher >= k) {
            return mid;
        }
        else if (lower > k) {
            right_section = mid - 1;
        }
        else if (higher < k) {
            left_section = mid + 1;
        }
    }
    return 0;
}
int main() {
    ios::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    long long n, k;
    cin >> n >> k;
    long long mas_men[n], mas_women[n];

    for (int i = 0; i < n; i++) {
        cin >> mas_women[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> mas_men[i];
    }
    mergeSort(mas_men, 0, n - 1);
    mergeSort(mas_women, 0, n - 1);
    long long res_mas[n * n];
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res_mas[count++] = mas_men[i] + mas_women[j];
        }
    }
    mergeSort(res_mas, 0,  25 - 1);
    for (int i = 0; i < n*n; ++i) {
        cout << res_mas[i] << " ";
    }
    long long min_sum = mas_men[0] + mas_women[0];
    long long max_sum = mas_men[n - 1] + mas_women[n - 1];

    cout << bin_search_of_bin_serches(mas_women, mas_men, n, k - 1, min_sum, max_sum);
    return 0;
}
