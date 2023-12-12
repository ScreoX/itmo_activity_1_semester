#include <iostream>
using namespace std;

class Stack {
private:
    struct Node {
        int data;
        Node* next;

        Node(int data) : data(data), next(nullptr) {}
    };

    Node* top;

public:
    Stack(): top(nullptr) {
    }

    void push(int data) {
        Node* newNode = new Node(data);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (isEmpty()) {
            return;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    int top_stack() {
        if (isEmpty()) {
            return -1;
        }
        return top->data;
    }
    bool isEmpty() { return top == nullptr; }
};
int main() {
    int n;
    std::cin >> n;
    Stack extra, mas1, last;
    char a;
    int num;
    int count = 0;
    for (int i = 0; i < n; i++) {
        cin >> a;
        if (a == '+') {
            cin >> num;
            mas1.push(num);
        }
        else {
            extra.push(mas1.top_stack());
            mas1.pop();
            ++count;
        }
    }
    for (int i = 0; i < count; i++) {
        last.push(extra.top_stack());
        extra.pop();
    }
    for (int i = 0; i < count; i++) {
        cout << last.top_stack() << '\n';
        last.pop();
    }
    return 0;
}

