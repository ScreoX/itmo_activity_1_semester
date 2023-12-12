#include <iostream>
#include <string>
using namespace std;

struct Node {
    string key;
    int height;
    int count;
    int index;
    Node* left;
    Node* right;
};

Node* new_Node(string key, int ind) {
    Node* new_nodik = new Node;
    new_nodik->key = key;
    new_nodik->count = 1;
    new_nodik->index = ind;
    new_nodik->left = nullptr;
    new_nodik->right = nullptr;
    new_nodik->height = 1;

    return new_nodik;
}

struct AVL_Tree {

    Node* root = nullptr;

    void insert(string x, int ind) {
        root = _insert(x, ind, root);
    }

    int exists(string x) {
        int r = _exists(x, root);
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

    int _height(Node* h) {
        if (h == nullptr) {
            return 0;
        }
        return h->height;
    }

    int _check_balance(Node* n) {
        if (n == nullptr) {
            return 0;
        }
        return _height(n->right) - _height(n->left);
    }

    void _fix_height(Node* n) {
        int height_left = _height(n->left);
        int height_right = _height(n->right);
        if (height_left > height_right) {
            n->height = height_left + 1;
        } else {
            n->height = height_right + 1;
        }
    }

    // Rotations

    Node* _rotate_right(Node* r) { //правый поворот вокруг узла r
        Node* left_from_r = r->left;
        r->left = left_from_r->right;
        left_from_r->right = r;
        _fix_height(r);
        _fix_height(left_from_r);
        return left_from_r;
    }

    Node* _rotate_left(Node* l) { //левый поворот вокруг узла l
        Node* right_from_l = l->right;
        l->right = right_from_l->left;
        right_from_l->left = l;
        _fix_height(l);
        _fix_height(right_from_l);
        return right_from_l;
    }

    // Balance

    Node* _balance(Node* need_to_balance) { // балансируем узел need_to_balance

        _fix_height(need_to_balance);

        if (_check_balance(need_to_balance) == 2) { // если баланс нарушен (перевешивает правый узел)
            if (_check_balance(need_to_balance->right) < 0) { // если баланс правого узла для need_to_balance меньше нуля, то делаем правый поворот
                need_to_balance->right = _rotate_right(need_to_balance->right);
            }
            return _rotate_left(need_to_balance);
        }
        if (_check_balance(need_to_balance) == -2) { // если баланс нарушен (перевешивает левый узел)
            if (_check_balance(need_to_balance->left) > 0) {
                need_to_balance->left = _rotate_left(need_to_balance->left);
            }
            return _rotate_right(need_to_balance);
        }

        return need_to_balance;
    }

    // Insert element
    Node* _insert(string x, int ind, Node* node) { // изначально node является корнем

        if (node == nullptr) {
            return new_Node(x, ind);
        }
        if (x == node->key) {
            ++node->count;
        }
        else if (x < node->key) {
            node->left = _insert(x, ind, node->left);
        }
        else if (x > node->key) {
            node->right = _insert(x, ind, node->right);
        }

        return _balance(node);
    }

    int _exists(string x, Node* node) {
        if (node == nullptr) {
            return 0;
        }
        else if (x == node->key) {
            if (node->count >= 2) {
                return 1;
            }
            else {
                if (node->index == 1) {
                    return 11;
                }
                else if (node->index == 2) {
                    return 22;
                }
            }
        }
        else if (x < node->key) {
            return _exists(x, node->left);
        }
        else {
            return _exists(x, node->right);
        }
    }


};

int main() {

    int n; cin >> n;

    AVL_Tree bin_search_tree;

    string title;
    int sum_1 = n * 3, sum_2 = n * 3, sum_3 = n * 3;

    for (int i = 0; i < n; i++) {
        cin >> title;
        bin_search_tree.insert(title, 1);
    }
    for (int i = 0; i < n; i++) {
        cin >> title;
        bin_search_tree.insert(title, 2);
        int res = bin_search_tree.exists(title);

        if (res == 1) {
            sum_1 -= 2;
            sum_2 -= 2;
        }
    }

    for (int i = 0; i < n; i++) {
        cin >> title;
        int res = bin_search_tree.exists(title);

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