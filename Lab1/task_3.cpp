#include <iostream>
using namespace std;
int main() {
    int nuts, sweets;
    cin >> nuts >> sweets;
    while (sweets != 0 && nuts != 0) {
        if (sweets > nuts)
            sweets = sweets % nuts;
        else
            nuts = nuts % sweets;
    }
    cout << nuts + sweets;
    return 0;
}