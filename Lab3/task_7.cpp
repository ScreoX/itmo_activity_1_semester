#include <iostream>
using namespace std;

class Stack {
private:
    struct Node {
        int data;
        Node* next;
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
    int n; cin >> n;
    int mas[n], result[n];
    int cnt = 0;

    for (int i = 0; i < n; i++) {
        cin >> mas[i];
    }
    Stack s;
//    for (int i = 0; i < n; i++) {
//        s.push(mas[i]);
//    }
//    for (int i = 0; i < n; i++) {
//        cout << s.top_stack() << " ";
//        s.pop();
//    }

    for (int i = 0; i < n; i++) {
        while (!s.isEmpty()) {

            if (s.top_stack() < mas[i])
            {
                cout << s.top_stack() << ' ';
                break;
            }
            else {
                s.pop();
            }
        }

        if (s.isEmpty()) {
             result[i] = -1;
        }

        s.push(mas[i]);
    }

    return 0;
}
//4
//3 4 5 6

//8
//13 14 15 11 9 12 16 14