#include <iostream>
#include <string>
using namespace std;

long long mn = 1e9+1;
long long mx = -1e9-1;

struct Node {
    int data;
    Node* left;
    Node* right;
};
Node* new_Node(int x) {
    Node* new_node = new Node;
    new_node->data = x;
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

    void _exists(int x) {
        int r = exists(x, root);
        if (r == 0) {
            cout << "false" << "\n";
        }
        else {
            cout << "true" << "\n";
         }
    }

    void _next(int x) {
        mn = 1e9+1;
        next(x, root);
        if (mn != 1e9+1) {
            cout << mn << "\n";
        }
        else {
            cout << "none" << "\n";
        }
    }

    void _prev(int x) {
        mx = -1e9-1;
        prev(x, root);
        if (mx != -1e9-1) {
            cout << mx << "\n";
        }
        else {
            cout << "none" << "\n";
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
            node->right = method_delete(x, node->right);
        }
        else if (node->left != nullptr && node->right != nullptr) {
            temp = find_min(node->right);
            node->data = temp->data;
            node->right = method_delete(node->data, node->right);
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


    int exists(int x, Node* node) {
        if (node == nullptr) {
            return 0;
        }
        else if (x == node->data) {
            return 1;
        }
        else if (x < node->data) {
            return exists(x, node->left);
        }
        else {
            return exists(x, node->right);
        }
    }

    void next(int x, Node* node) {
        if (node == nullptr) {
            return;
        }
        else if (node->data > x) {
            if (node->data < mn) {
                mn = node->data;
            }
            next(x, node->left);
        }
        else {
            next(x, node->right);
        }
    }

    void prev(int x, Node* node) {
        if (node == nullptr) {
            return;
        }
        else if (node->data < x) {
            if (node->data > mx) {
                mx = node->data;
            }
            prev(x, node->right);
        }
        else {
            prev(x, node->left);
        }
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

};


int main() {
    string command;
    BST bin_search_tree;
    while (cin >> command) {
        if (command == "end") {
            break;
        }
        else if (command == "insert") {
            int x; cin >> x;
            bin_search_tree._insert(x);
        }
        else if (command == "delete") {
            int x; cin >> x;
            bin_search_tree._delete(x);
        }
        else if (command == "exists") {
            int x; cin >> x;
            bin_search_tree._exists(x);
        }
        else if (command == "next") {
            int x; cin >> x;
            bin_search_tree._next(x);
        }
        else if (command == "prev") {
            int x; cin >> x;
            bin_search_tree._prev(x);
        }
    }

    return 0;
}
