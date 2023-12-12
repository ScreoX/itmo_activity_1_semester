#include <iostream>
#include <string>

using namespace std;



void counting_sort(long long damages[], string names[], long long n) {
    long long max_el = 0;
    for (long long i = 0; i < n; i++) {
        if (max_el < damages[i]) {
            max_el = damages[i];
        }
    }
    long long *count = new long long[max_el + 1];
    for (long long i = 0; i <= max_el; i++) {
        count[i] = 0;
    }
    long long *output_damages = new long long [n];
    string *output_names = new string [max_el];

    for (int i = 0; i < n; i++) {
        count[damages[i]]++;
    }

    for (int i = 1; i <= max_el; i++) {
        count[i] += count[i - 1];
    }

    for (long long i = n - 1; i >= 0; i--) {
        output_damages[count[damages[i]] - 1] = damages[i];
        output_names[count[damages[i]] - 1] = names[i];
        --count[damages[i]];
    }

    for (int i = 0; i < n; i++) {
        damages[i] = output_damages[i];
        names[i] = output_names[i];
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

int main() {
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);
    long long n, q;
    cin >> n;
    long long damages[n];
    string names[n];
    for (long long i = 0; i < n; i++) {
        cin >> damages[i];
    }

    for (long long i = 0; i < n; i++) {
        cin >> names[i];
    }

    counting_sort(damages, names,  n);


    long long pref_summa[n + 1];
    pref_summa[0] = 0;
    for (long long i = 1; i <= n; i++) {
        pref_summa[i] = pref_summa[i - 1] + damages[i - 1];
    }

    for (long long i = 0; i < n; i++) {
        if (i != n - 1) {
            cout << damages[i] << " ";
        }
        else {
            cout << damages[i];
        }
    }

    cout << '\n';

    for (long long i = 0; i < n; i++) {
        if (i != n - 1) {
            cout << names[i] << " ";
        }
        else {
            cout << names[i];
        }
    }

    cout << '\n';

    cin >> q;
    for (long long i = 0; i < q; i++) {
        string action; cin >> action;
        long long left, right;
        long long left_section, right_section;
        if (action == "Count") {
            cin >> left >> right;
            left_section = left_binary_search(damages, n, left);
            right_section = right_binary_search(damages, n, right);
            cout << right_section - left_section;
            cout << '\n';
        }
        if (action == "Sum") {
            cin >> left >> right;
            left_section = left_binary_search(damages, n, left);
            right_section = right_binary_search(damages, n, right);
            if (left_section != 0) {
                cout << pref_summa[right_section] - pref_summa[left_section];
            }
            else {
                cout << pref_summa[right_section];
            }
            cout << '\n';
        }
        if (action == "Xor"){
            cin >> left >> right;
            left_section = left_binary_search(damages, n, left);
            right_section = right_binary_search(damages, n, right);
            long long local_xor = 0;
            for (long long j = left_section; j < right_section; j++) {
                local_xor ^= damages[j];
            }
            cout << local_xor;
            cout << '\n';
        }
    }
    for (int i = 0; i <= n; i++) {
        cout << pref_summa[i] << " ";
    }

    return 0;
}

