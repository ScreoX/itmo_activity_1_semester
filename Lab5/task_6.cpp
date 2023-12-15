#include <iostream>
#include <string>
using namespace std;

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
bool flag_for_inorder = true, flag_for_postorder = true;

struct BST {
    Node* root = nullptr;

    Node* create_bst_from_preorder_traversal(int mas[], int size) {
        int i = 0;
        root = new_Node(mas[0]);
        root = _create_bst_from_preorder_traversal(mas, size, INT_MIN, INT_MAX, i);
        return root;
    }

private:

    Node* _create_bst_from_preorder_traversal(int mas[], int n, int low_border, int high_border, int& index) {

        if (index >= n || mas[index] >= high_border || mas[index] < low_border) {
            return nullptr;
        }

        Node* new_nodik = new_Node(mas[index++]);

        new_nodik->left = _create_bst_from_preorder_traversal(mas, n, low_border, new_nodik->data, index);
        new_nodik->right = _create_bst_from_preorder_traversal(mas, n, new_nodik->data, high_border, index);

        return new_nodik;
    }

};

int index_for_post = 0;

void postorder(Node* node, int mas[])
{
    if (node == nullptr)
        return;
    postorder(node->left, mas);
    postorder(node->right, mas);
    if (mas[index_for_post++] != node->data) {
        flag_for_postorder = false;
    }
}

int index_for_in = 0;

void inorder(Node* node, int mas[])
{
    if (node == nullptr)
        return;

    inorder(node->left, mas);

    if (mas[index_for_in++] != node->data) {
        flag_for_inorder = false;
    }

    inorder(node->right, mas);
}

int main() {

    int n; cin >> n;
    int mas_for_pre[n];
    int mas_for_in[n];
    int mas_for_post[n];
    BST bin_search_tree;

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        mas_for_pre[i] = x;
    }

    bin_search_tree.create_bst_from_preorder_traversal(mas_for_pre, n);


    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        mas_for_in[i] = x;
    }

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        mas_for_post[i] = x;
    }
    
    postorder(bin_search_tree.root, mas_for_post);

    if (!flag_for_postorder) {
        cout << "NO";
        return 0;
    }

    inorder(bin_search_tree.root, mas_for_in);

    if (!flag_for_inorder) {
        cout << "NO";
        return 0;
    }

    cout << "YES";

    return 0;
}