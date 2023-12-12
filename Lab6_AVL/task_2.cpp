#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int key;
    int height;
    Node* left;
    Node* right;
};

struct Info_About_Node {
    int index_node;
    int index_left_child;
    int index_right_child;
};

Node* new_Node(int key) {
    Node* new_nodik = new Node;
    new_nodik->key = key;
    new_nodik->left = nullptr;
    new_nodik->right = nullptr;
    new_nodik->height = 1;

    return new_nodik;
}

struct Queue {
private:
    struct Node_que {
        Node* data;
        Node_que* next;

        Node_que(Node* data) : data(data), next(nullptr) {}
    };

    Node_que* head;
    Node_que* tail;

public:
    Queue(): head(nullptr), tail(nullptr) {}

    void enqueue(Node* data) {
        Node_que* newNode = new Node_que(data);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void dequeue() {
        if (isEmpty()) {
            return;
        }
        Node_que* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) {
            tail = nullptr;
        }
    }

    Node* front() {
        if (isEmpty()) {
            return nullptr;
        }
        return head->data;
    }

    bool isEmpty() { return head == nullptr; }
};

struct AVL_Tree {

    Node* root = nullptr;

    void left_rotation() {
        root = _balance(root);
    }

    void insert_for_mas(vector <Info_About_Node>& mas) {
        int count = 0;
        root = _insert_for_mas(mas, count);
    }

    void print(int n) {
        _print(n);
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

    Node* _insert_for_new_element(int x, Node* node) {

        if (node == nullptr) {
            return new_Node(x);
        }
        else if (x < node->key) {
            node->left = _insert_for_new_element(x, node->left);
        }
        else if (x > node->key) {
            node->right = _insert_for_new_element(x, node->right);
        }

        _fix_height(node);

        return _balance(node);
    }

    Node* _insert_for_mas(vector <Info_About_Node>& mas, int top) {

        if (top < 0 || mas.empty())
            return nullptr;

        Node* temp = new_Node(mas[top].index_node);

        temp->left = _insert_for_mas(mas, mas[top].index_left_child);
        temp->right = _insert_for_mas(mas, mas[top].index_right_child);
        temp->height = max(_height(temp->left), _height(temp->right)) + 1;

        return temp;
    }

    void _print(int size) {
        Queue q;
        q.enqueue(root);
        int len = 1;
        int left, right;
        cout << size << '\n';

        while (!q.isEmpty()) {
            Node* mini_tree = q.front();
            q.dequeue();
            left = 0, right = 0;

            if (mini_tree->right != nullptr) {
                q.enqueue(mini_tree->right);
                right = ++len;
            }

            if (mini_tree->left != nullptr) {
                q.enqueue(mini_tree->left);
                left = ++len;
            }

            cout << mini_tree->key << " " << left << " " << right << '\n';
        }
    }

};

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; cin >> n;

    AVL_Tree avlchik_tree;

    vector <Info_About_Node> mas_info(n);

    int x, y, z;

    for (int i = 0; i < n; i++) {
        cin >> x >> y >> z;
        mas_info[i].index_node = x;
        mas_info[i].index_left_child = y - 1;
        mas_info[i].index_right_child = z - 1;
    }

    avlchik_tree.insert_for_mas(mas_info);

    avlchik_tree.left_rotation();

    avlchik_tree.print(n);

    return 0;
}