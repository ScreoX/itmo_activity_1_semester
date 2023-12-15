#include <iostream>
#include <string>
using namespace std;

struct Node {
    int data;
    int count_right;
    Node* left;
    Node* right;
};

Node* new_Node(int x) {

    Node* new_node = new Node;
    new_node->data = x;
    new_node->count_right = 0;
    new_node->left = nullptr;
    new_node->right = nullptr;

    return new_node;
}

struct BST {

    Node* root = nullptr;

    void _insert(int x) {
        root = insert(x, root);
    }

    void _delete(int x) {
        root = method_delete(x, root);
    }

    void _find_k_max(int x) {
        int res = find_k_max(x, root);
        if (res != -12345) {
            cout << res << '\n';
        }
    }

private:

    Node* insert(int x, Node* node) {
        if (node == nullptr) {
            node = new_Node(x);
        }
        else if (x < node->data) {
            node->left = insert(x, node->left);
        }
        else if (x > node->data) {
            node->right = insert(x, node->right);
            ++node->count_right;
        }
        return node;
    }

    Node* method_delete (int x, Node* node) {
        Node* temp;
        if (node == nullptr) {
            return nullptr;
        }
        else if (x < node->data) {
            node->left = method_delete(x, node->left);
        }
        else if (x > node->data) {
            --node->count_right;
            node->right = method_delete(x, node->right);
        }
        else if (node->left != nullptr && node->right != nullptr) {
            temp = find_min(node->right);
            node->data = temp->data;
            node->right = method_delete(node->data, node->right);
            --node->count_right;
        }
        else  {
            temp = node;
            if (node->left == nullptr) {
                node = node->right;
            }
            else if (node->right == nullptr) {
                node = node->left;
            }
            delete temp;
        }
        return node;
    }


    Node* find_min(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        else if (node->left == nullptr)
            return node;
        else
            return find_min(node->left);
    }

    int find_k_max(int x, Node* node) {
        if (node == nullptr) {
            return -12345;
        }
        else if (node->count_right == x) {
            return node->data;
        }
        else if (x < node->count_right + 1) {
            return find_k_max(x, node->right);
        }
        else {
            return find_k_max(x - node->count_right - 1, node->left);
        }
    }


};

int main() {

    int n; cin >> n;

    BST bin_search_tree;

    int command, x;

    for (int i = 0; i < n; i++) {

        cin >> command;

        if (command == 1) {
            cin >> x;
            bin_search_tree._insert(x);
        }
        else if (command == -1) {
            cin >> x;
            bin_search_tree._delete(x);
        }
        else if (command == 0) {
            cin >> x;
            bin_search_tree._find_k_max(x - 1);
        }
    }

    return 0;
}