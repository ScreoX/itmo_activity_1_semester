#include <iostream>
using namespace std;

class List {
public:
    List() {
        head = nullptr;
        tail = nullptr;
    }
    
    struct Node {
        int data;
        int link;
        Node *next;
    };
    
    Node *head;
    Node *tail;

    void add(int data, int link) {
        Node* newNode = new Node(data, link);
        if (isEmpty()) {
            head = tail = newNode;
            return;
        }
        tail->next = newNode;
        tail = newNode;
    }

    bool proverka_have_cycle() {
        Node* temp = head;
        int last_el = tail -> link;
        while (temp != nullptr) {
            if (last_el == temp -> data) {
                tail -> next = temp;
                return true;
            }
            temp = temp -> next;
        }
        return false;
    }

    int main_func() {
        if (!proverka_have_cycle()) {
            return -1;
        }
        else {
            Node *turt = head->next;
            Node *rab = head->next->next;
            while (rab != turt) {
                turt = turt->next;
                rab = rab->next->next;
            }
            int start_of_cycle = 0;
            turt = head;
            while (rab != turt) {
                ++start_of_cycle;
                turt = turt->next;
                rab = rab->next;
            }
            int length_of_cycle = 1;
            rab = rab->next;
            while (rab != turt) {
                ++length_of_cycle;
                rab = rab->next;
            }
            return length_of_cycle;
        }
    }
    bool isEmpty() { return head == nullptr; }
};

int main() {
    List listochek;

    int n,x; cin >> n;
    int mas[n + 1];
    for (int i = 0; i <= n; i++) {
        mas[i] = 0;
    }

    int cnt = 1;
    while (cin >> x) {
        mas[cnt++] = x;
    }

    int i = 1;
    int temp;
    while (mas[i] != 0){
        listochek.add(i,mas[i]);
        temp = mas[i];
        mas[i] = 0;
        i = temp;
    }

    cout << listochek.main_func();
    return 0;
}