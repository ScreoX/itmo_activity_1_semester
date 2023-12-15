#include <iostream>
#include <string>
using namespace std;

struct Node {
    string data;
    int count;
    int index;
    Node* left;
    Node* right;
};

Node* new_Node(string x, int ind) {
    Node* new_node = new Node;
    new_node->data = x;
    new_node->count = 1;
    new_node->index = ind;
    new_node->left = nullptr;
    new_node->right = nullptr;

    return new_node;
}

struct BST {
    Node* root = nullptr;

    void _insert(string x, int ind) {
        root = insert(x, ind,root);
    }

    int _exists(string x) {
        int r = exists(x, root);
        if (r != 0) {
            if (r == 1) {
                return 1;
            } else if (r == 11) {
                return 11;
            } else if (r == 22) {
                return 22;
            }
        }
        return 54;
    }

private:

    Node* insert(string x, int ind, Node* node) {
        if (node == nullptr) {
            node = new_Node(x, ind);
        }
        else if (x == node->data) {
            node->count += 1;
        }
        else if (x < node->data) {
            node->left = insert(x, ind, node->left);
        }
        else if (x > node->data) {
            node->right = insert(x, ind, node->right);
        }
        return node;
    }

    int exists(string x, Node* node) {
        if (node == nullptr) {
            return 0;
        }
        else if (x == node->data) {
            if (node->count == 2) {
                return 1;
            }
            else {
                if (node->index == 1) {
                    return 11;
                }
                else {
                    return 22;
                }
            }
        }
        else if (x < node->data) {
            return exists(x, node->left);
        }
        else {
            return exists(x, node->right);
        }
    }

};

int main() {

    int n; cin >> n;

    BST bin_search_tree;

    string title;
    int sum_1 = n * 3, sum_2 = n * 3, sum_3 = n * 3;
    for (int i = 0; i < n; i++) {
        cin >> title;
        bin_search_tree._insert(title, 1);
    }

    for (int i = 0; i < n; i++) {
        cin >> title;
        bin_search_tree._insert(title, 2);
        int res = bin_search_tree._exists(title);

        if (res == 1) {
            sum_1 -= 2;
            sum_2 -= 2;
        }
    }

    for (int i = 0; i < n; i++) {
        cin >> title;
        int res = bin_search_tree._exists(title);

        if (res == 1) {
            sum_1 -= 1;
            sum_2 -= 1;
            sum_3 -= 3;
        }
        else if (res == 11) {
            sum_1 -= 2;
            sum_3 -= 2;
        }
        else if (res == 22) {
            sum_2 -= 2;
            sum_3 -= 2;
        }
    }

    cout << sum_1 << " " << sum_2 << " " << sum_3;

    return 0;
}
