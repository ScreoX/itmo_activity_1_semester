#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    long long data;
    Node *left;
    Node *right;
    Node *parent;
};


Node *new_Node(long long x) {
    Node *new_node = new Node;
    new_node->data = x;
    new_node->left = nullptr;
    new_node->right = nullptr;
    new_node->parent = nullptr;

    return new_node;
}

struct BST {
    Node* root = nullptr;

    void _insert(long long x, vector<char>& v) {
        root = insert(x, root, v);
    }

    void _method_for_u() {
        now = now->parent;
    }

private:

    Node* prev = nullptr;
    Node* now = nullptr;

    Node* insert(long long x, Node *node, vector<char> mas) {
        if (mas.empty()) {
            node = new_Node(x);
            node->parent = prev;
            now = node;
        } else {
            if (mas.front() == 'l') {
                mas.erase(mas.begin());
                prev = now;
                now->left = new_Node(x);
                now->left->parent = prev;
                now = now->left;
            } else if (mas.front() == 'r') {
                mas.erase(mas.begin());
                prev = now;
                now->right = new_Node(x);
                now->right->parent = prev;
                now = now->right;
            }
        }

        return node;
    }


};

long long find_max_sum(Node* node, long long& mx, long long& mn, long long& res) {

    if (node == nullptr) {
        return 0;
    }

    long long left_min = 1e9 + 1, right_min = 1e9 + 1, right_max = -1e9 - 1, left_max = -1e9 - 1;

    long long left = find_max_sum(node->left, left_max, left_min, res);
    long long right = find_max_sum(node->right, right_max, right_min, res);

    long long sum = left + right + node->data;

    if ((left_max < (node->data)) && (right_min > (node->data))) {

        if (sum > res) {
            res = sum;
        }

        if (node->data > right_max) {
            mx = node->data;
        } else {
            mx = right_max;
        }

        if (node->data < left_min) {
            mn = node->data;
        } else {
            mn = left_min;
        }

    } else {
        mx = 1e9 + 1;
        mn = -1e9 - 1;
    }

    return sum;
}


int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    BST bin_search_tree;
    long long mx = -1e9 - 1;
    long long mn = 1e9 + 1;
    long long res = 0;

    vector<char> mas_of_chars;

    string stroka;

    while (cin >> stroka) {
        if (stroka[0] == 'e') {
            break;
        }
        else if (stroka.size() > 1 || isdigit(stroka[0])) {
            bin_search_tree._insert(stoi(stroka), mas_of_chars);
        }
        else {
            if (stroka[0] == 'u') {
                bin_search_tree._method_for_u();
            }
            if (!mas_of_chars.empty()) {
                mas_of_chars.pop_back();
            }
            mas_of_chars.push_back(stroka[0]);
        }
    }

    find_max_sum(bin_search_tree.root, mx, mn, res);

    cout << res;

    return 0;
}

//1 l 4 l 2 u r 4 u u r 3 l 2 u r 5 l 4 u r 6 u u u u
//20

//4 l 3 l 1 u r 2 u u u
//2

//-4 l -2 u r -5 u u
//0

//1
//l
//2
//r
//3

//1
//r
//5
//u
//l
//3

//4 l -2 u r 2 u u

//-1 r 5 u l 2 r -2 u l -5 e

//-1 r -5 l -9 u r -10 e