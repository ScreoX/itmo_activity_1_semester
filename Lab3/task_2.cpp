#include <iostream>
using namespace std;

class Queue {
private:
    struct Node {
        int data;
        Node* next;

        Node(int data) : data(data), next(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    Queue(): head(nullptr), tail(nullptr) {
    }

    void enqueue(int data) {
        Node* newNode = new Node(data);
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
        Node* temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr) {
            tail = nullptr;
        }
    }

    int front() {
        if (isEmpty()) {
            return -1;
        }
        return head->data;
    }

    bool isEmpty() { return head == nullptr; }
};
int main() {
    int n;
    std::cin >> n;
    Queue extra, mas1, last;
    char a;
    int num;
    int count = 0;
    for (int i = 0; i < n; i++) {
        cin >> a;
        if (a == '+') {
            cin >> num;
            mas1.enqueue(num);
        }
        else {
            extra.enqueue(mas1.front());
            mas1.dequeue();
            ++count;
        }
    }
    for (int i = 0; i < count; i++) {
        cout << extra.front() << '\n';
        extra.dequeue();
    }
    return 0;
}