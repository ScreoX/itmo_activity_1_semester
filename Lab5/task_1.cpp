//#include <iostream>
//using namespace std;
//
//
//
//struct Node {
//    int key;
//    int height;
//    Node* left;
//    Node* right;
//
//    Node(int key) {
//        key = key;
//        left = nullptr;
//        right = nullptr;
//        height = 1;
//    }
//
//    int is_height(Node* h) {
//        if (h == nullptr) {
//            return 0;
//        }
//        return h->height;
//    }
//
//    int check_balance(Node* n) {
//        if (n == nullptr) {
//            return 0;
//        }
//        return is_height(n->right) - is_height(n->left);
//    }
//
//    void fix_height(Node* n) {
//        if (n->left != nullptr && n->right != nullptr) {
//            int height_left = is_height(n->left);
//            int height_right = is_height(n->right);
//            if (height_left > height_right) {
//                n->height = height_left + 1;
//            } else if (height_left < height_right) {
//                n->height = height_right + 1;
//            }
//        }
//    }
//
//};
//void preorder(Node* root) {
//    if (root == nullptr) {
//        return;
//    }
//    cout << root->key << " ";
//    preorder(root->left);
//    preorder(root->right);
//}
//
//int main() {
//    int n; cin >> n;
//    int mas[n];
//    Node* root = nullptr;
//    for (int i = 0; i < n; i++) {
//        int x; cin >> x;
//        mas[i] = x;
//    }
//
//
//    return 0;
//}

#include <iostream>
using namespace std;

struct Node_Tree {

    int key;
    Node_Tree* left;
    Node_Tree* right;

};

Node_Tree* new_Node(int key)
{
    Node_Tree* node = new Node_Tree;
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;

    return node;
}

Node_Tree* sort_for_mas(int mas[], int start, int end)
{
    if (start > end)
        return nullptr;

    int mid = (start + end) / 2;
    Node_Tree* root = new_Node(mas[mid]);

    root->left = sort_for_mas(mas, start, mid - 1);
    root->right = sort_for_mas(mas, mid + 1, end);

    return root;
}

void preorder(Node_Tree* root) {
    if (root == nullptr) {
        return;
    }
    cout << root->key << " ";
    preorder(root->left);
    preorder(root->right);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin >> n;
    int mas[n];

    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        mas[i] = x;
    }

    Node_Tree* root = sort_for_mas(mas, 0, n - 1);

    preorder(root);

    return 0;
}