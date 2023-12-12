#include <iostream>
#include <vector>

using namespace std;

vector <int> from_string_to_vector(string str) {

    vector <int> vector_of_str;

    for (int i = str.size(); i > 0; i -= 9) {
        if (i < 9) {
            vector_of_str.push_back(stoi(str.substr(0, i)));
        } else {
            vector_of_str.push_back(stoi(str.substr(i - 9, 9)));
        }
    }
    return vector_of_str;
}

int main() {
    int n;
    cin >> n;
    string first_num;
    cin >> first_num;
    int a = 1000000000;

    vector <int> vector_of_first_num = from_string_to_vector(first_num);

    for (int chisla = 1; chisla < n; chisla++) {

        string others_nums;
        cin >> others_nums;
        vector <int> vector_of_others_num = from_string_to_vector(others_nums);
        int des = 0;
        if (vector_of_first_num.size() > vector_of_others_num.size()) {
            for (int i = 0; i < vector_of_first_num.size() || des; i++) {
                if (i == first_num.size()) {
                    vector_of_first_num.push_back(0);
                }

                if (i < vector_of_others_num.size()) {
                    vector_of_first_num[i] += (des + vector_of_others_num[i]);
                } else {
                    vector_of_first_num[i] += des;
                }

                if (vector_of_first_num[i] >= a) {
                    des = 1;
                }
                if (des == 1) {
                    vector_of_first_num[i] -= a;
                }
            }
        }
        else {
            for (int i = 0; i < vector_of_others_num.size() || des; i++) {
                if (i == first_num.size()) {
                    vector_of_first_num.push_back(0);
                }

                if (i < vector_of_others_num.size()) {
                    vector_of_first_num[i] += (des + vector_of_others_num[i]);
                } else {
                    vector_of_first_num[i] += des;
                }

                if (vector_of_first_num[i] >= a) {
                    des = 1;
                }
                if (des == 1) {
                    vector_of_first_num[i] -= a;
                }
            }
        }
    }

    if (!vector_of_first_num.empty()) {
        cout << vector_of_first_num.back();
    }
    else {
        cout << 0;
        return 0;
    }
    for (int i = (vector_of_first_num.size() - 2); i >= 0; i--) {
        cout << vector_of_first_num[i];
    }
    return 0;
}
