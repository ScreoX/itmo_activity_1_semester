#include <iostream>

using namespace std;

struct Node {
    int key;
    int height;
    Node *left;
    Node *right;
};

Node *new_Node(int key) {
    Node *new_nodik = new Node;
    new_nodik->key = key;
    new_nodik->left = nullptr;
    new_nodik->right = nullptr;
    new_nodik->height = 1;

    return new_nodik;
}

struct AVL_Tree {

    Node *root = nullptr;

    void insert(int x) {
        root = _insert(x, root);;
    }

    int remove(int x) {
        if (root == nullptr) {
            cout << 0 << '\n';
            return 0;
        }
        root = _remove(root, x);
        return 1;
    }

    void find_balance() {
        int res = _check_balance(root);
        cout << res << '\n';
    }

    void exists(int x) {
        int r = _exists(x, root);
        if (r == 1) {
            cout << 'Y' << '\n';
        } else {
            cout << 'N' << '\n';
        }
    }

private:

    int _height(Node *h) {
        if (h == nullptr) {
            return 0;
        }
        return h->height;
    }

    int _check_balance(Node *n) {
        if (n == nullptr) {
            return 0;
        }
        return _height(n->right) - _height(n->left);
    }

    void _fix_height(Node *n) {
        int height_left = _height(n->left);
        int height_right = _height(n->right);
        if (height_left > height_right) {
            n->height = height_left + 1;
        } else {
            n->height = height_right + 1;
        }
    }


    Node *_rotate_right(Node *r) {
        Node *left_from_r = r->left;
        r->left = left_from_r->right;
        left_from_r->right = r;
        _fix_height(r);
        _fix_height(left_from_r);
        return left_from_r;
    }

    Node *_rotate_left(Node *l) {
        Node *right_from_l = l->right;
        l->right = right_from_l->left;
        right_from_l->left = l;
        _fix_height(l);
        _fix_height(right_from_l);
        return right_from_l;
    }


    Node *_balance(Node *need_to_balance) {

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

    Node *_insert(int x, Node *node) {

        if (node == nullptr) {
            return new_Node(x);
        } else if (x < node->key) {
            node->left = _insert(x, node->left);
        } else if (x > node->key) {
            node->right = _insert(x, node->right);
        }

        return _balance(node);
    }

    Node *_find_max(Node *p) {
        if (p->right == nullptr) {
            return p;
        }
        return _find_max(p->right);
    }

    Node *_remove_max(Node *p) {
        if (p->right == nullptr)
            return p->left;
        p->right = _remove_max(p->right);
        return _balance(p);
    }

    Node *_remove(Node *node, int key) {
        if (node == nullptr) {
            return nullptr;
        }
        if (key < node->key) {
            node->left = _remove(node->left, key);
        }
        else if (key > node->key) {
            node->right = _remove(node->right, key);
        }
        else {
            if (node->left == nullptr && node->right == nullptr) {
                return nullptr;
            } else if (node->left == nullptr) {
                node = node->right;
                return _balance(node);
            } else {
                Node *find_max = _find_max(node->left);
                node->key = find_max->key;
                node->left = _remove_max(find_max);
            }
        }
        return _balance(node);
    }

    int _exists(int x, Node *node) {
        if (node == nullptr) {
            return 0;
        } else if (x == node->key) {
            return 1;
        } else if (x < node->key) {
            return _exists(x, node->left);
        } else {
            return _exists(x, node->right);
        }
    }

};

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    AVL_Tree avlchik_tree;


    char command;
    int num, res;

    for (int i = 0; i < n; i++) {
        cin >> command >> num;
        if (command == 'A') {
            avlchik_tree.insert(num);
            avlchik_tree.find_balance();
        } else if (command == 'D') {
            res = avlchik_tree.remove(num);
            if (res != 0) {
                avlchik_tree.find_balance();
            }
        } else if (command == 'C') {
            avlchik_tree.exists(num);
        }
    }

    return 0;
}