#include <iostream>
#include <string>
#include <vector>
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


struct BST {
    Node* root = nullptr;

    void _insert(int x) {
        root = insert(x, root);
    }

    void _delete(int x) {
        root = method_delete(x, root);
    }

    void _merge(Node* node) {
        root = merge_x_inorder(root, node);
    }

    void _delete_tree(){
        root = nullptr;
    }

    bool _is_empty() {
        if (root == nullptr) {
            return true;
        }
        else {
            return false;
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
        else if (x >= node->data) {
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

    Node* merge_x_inorder(Node* main_root, Node* needed_to_free_node) {

        if (needed_to_free_node == nullptr) {
            return nullptr;
        }

        merge_x_inorder(main_root, needed_to_free_node->left);
        main_root = insert(needed_to_free_node->data, main_root);
        merge_x_inorder(main_root, needed_to_free_node->right);

        return main_root;
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

void output_vector(vector <int> v) {
    for (int i = 0; i < v.size(); i++) {
        if (i == v.size() - 1) {
            cout << v[i] << "\n";
        } else {
            cout << v[i] << " ";
        }
    }
}

Node* in_order(Node* node, vector <int>& nums) {
    if (node == nullptr)
        return nullptr;

    in_order(node->left, nums);

    nums.push_back(node->data);

    in_order(node->right, nums);

    return nullptr;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    BST wallets[2];
    int n; cin >> n;
    string command;
    int account = 0, id = 0;

    for (int i = 0; i < n; i++) {
        cin >> command;
        if (command == "buy") {
            cin >> account >> id;
            wallets[account - 1]._insert(id);
        }
        else if (command == "sell") {
            cin >> account >> id;
            if (!wallets[account - 1]._is_empty()) {
                wallets[account - 1]._delete(id);
            }
        }
        else if (command == "merge") {
            if (!wallets[1]._is_empty()) {
                wallets[0]._merge(wallets[1].root);
                vector <int> output_nums;
                in_order(wallets[0].root, output_nums);
                wallets[1]._delete_tree();
                output_vector(output_nums);
            } else {
                if (!wallets[0]._is_empty()) {
                    vector <int> output_nums;
                    in_order(wallets[0].root, output_nums);
                    output_vector(output_nums);
                }
            }
        }
    }

    return 0;
}


//4
//buy 1 2
//buy 1 5
//buy 2 3
//merge

//6
//buy 1 2
//sell 2 3
//buy 1 2
//buy 1 5
//buy 2 3
//merge

//9
//buy 1 2
//sell 2 2
//buy 1 2
//sell 1 2
//buy 1 5
//buy 2 3
//sell 2 3
//sell 1 9
//merge

//10
//buy 1 1
//merge
//buy 1 2
//buy 1 4
//sell 1 4
//buy 2 9
//merge
//sell 2 9
//buy 2 1
//merge