#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    string key;
    int height;
    Node* left;
    Node* right;
};

Node* new_Node(string key) {
    Node* new_nodik = new Node;
    new_nodik->key = key;
    new_nodik->left = nullptr;
    new_nodik->right = nullptr;
    new_nodik->height = 1;

    return new_nodik;
}

struct AVL_Tree {

    Node* root = nullptr;

    void insert(string x, vector <string>& mas) {
        root = _insert(x,  mas, root);
    }

    void insert_for_check(string x, int& count) {
        root = _insert_for_check(x, count , root);
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


    Node* _rotate_right(Node* r) {
        Node* left_from_r = r->left;
        r->left = left_from_r->right;
        left_from_r->right = r;
        _fix_height(r);
        _fix_height(left_from_r);
        return left_from_r;
    }

    Node* _rotate_left(Node* l) {
        Node* right_from_l = l->right;
        l->right = right_from_l->left;
        right_from_l->left = l;
        _fix_height(l);
        _fix_height(right_from_l);
        return right_from_l;
    }


    Node* _balance(Node* need_to_balance) {

        _fix_height(need_to_balance);

        if (_check_balance(need_to_balance) == 2) {
            if (_check_balance(need_to_balance->right) < 0) {
                need_to_balance->right = _rotate_right(need_to_balance->right);
            }
            return _rotate_left(need_to_balance);
        }
        if (_check_balance(need_to_balance) == -2) {
            if (_check_balance(need_to_balance->left) > 0) {
                need_to_balance->left = _rotate_left(need_to_balance->left);
            }
            return _rotate_right(need_to_balance);
        }

        return need_to_balance;
    }


    Node* _insert(string x, vector <string>& mas, Node* node) {

        if (node == nullptr) {
            return new_Node(x);
        }
        else if (x == node->key) {
            mas.push_back(x);
        }
        else if (x < node->key) {
            node->left = _insert(x, mas, node->left);
        }
        else if (x > node->key) {
            node->right = _insert(x, mas, node->right);
        }

        return _balance(node);
    }

    Node* _insert_for_check(string x, int& count, Node* node) {

        if (node == nullptr) {
            return new_Node(x);
        }
        else if (x == node->key) {
            ++count;
        }
        else if (x < node->key) {
            node->left = _insert_for_check(x, count, node->left);
        }
        else if (x > node->key) {
            node->right = _insert_for_check(x, count, node->right);
        }

        return _balance(node);
    }

};

int main() {

    int n; cin >> n;

    AVL_Tree bin_search_tree;

    string str;
    vector <string> mas_of_sames;

    for (int i = 0; i < n; i++) {
        cin >> str;
        bin_search_tree.insert(str, mas_of_sames);
    }

    int sum_result = 0;
    int total_lenght = 0;

    for (int i = 0; i < mas_of_sames.size(); i++) {
        AVL_Tree check;
        bool mark = false;
        for (int j = 0; j < mas_of_sames[i].size(); j++) {
            if (!mark) {
                total_lenght += mas_of_sames[i].size();
                mark = true;
            }
            int count = 0;
            string num = to_string(mas_of_sames[i][j]);
            check.insert_for_check(num, count);
            sum_result += count;
        }
    }

    cout << total_lenght - sum_result;

    return 0;
}