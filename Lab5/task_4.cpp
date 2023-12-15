#include <iostream>
#include <string>
using namespace std;


struct Node {
    int data;
    int level;
    Node* left;
    Node* right;
};

Node* new_Node(int x) {

    Node* new_node = new Node;
    new_node->data = x;
    new_node->level = 1;
    new_node->left = nullptr;
    new_node->right = nullptr;

    return new_node;
}

struct BST {

    Node* root = nullptr;

    void _insert(int x) {
        int lvl = 1;
        root = insert(x, lvl, root);

    }

    void _print() {
        Node* node = root;
        printik(node);
    }

private:

    Node* insert(int x, int lvl, Node* node) {
        if (node == nullptr) {
            node = new_Node(x);
            node->level = lvl;
        }
        else if (x < node->data) {
            node->left = insert(x, lvl + 1, node->left);
        }
        else if (x > node->data) {
            node->right = insert(x, lvl + 1, node->right);
        }
        return node;
    }

    int count = 1;

    Node* printik(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        if (node->level == count) {
            cout << node->data << " ";
            ++count;
        }
        printik(node->right);
        printik(node->left);
        return nullptr;
    }

};


int main() {
    int n; cin >> n;

    BST bin_search_tree;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        bin_search_tree._insert(x);
    }

    bin_search_tree._print();
    return 0;
}