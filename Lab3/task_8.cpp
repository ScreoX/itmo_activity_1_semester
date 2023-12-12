#include <iostream>
using namespace std;

class Stack {
private:
    struct Node {
        long long data;
        Node* next;
    };

    Node* top;

public:
    Stack(): top(nullptr) {
    }

    void push(long long data) {
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

    long long height_counter, n, i;
    long long mx_square = 0;
    Stack square, height;
    cin >> n;
    square.push(0);
    height.push(0);

    for (int i = 1; i <= n + 1; i++) {
        if (i <= n) {
            cin >> height_counter;
        }
        else {
            height_counter = 0;
        }
        long long x = i;
        while (height_counter <= height.top_stack())
        {
            x = square.top_stack();
            long long Height = height.top_stack();
            square.pop();
            height.pop();
            long long square_counter = Height * (i - x);
            if (square_counter> mx_square) {
                mx_square = square_counter;
            }
        }
        if (height_counter > height.top_stack()) {
            square.push(x);
            height.push(height_counter);
        }
    }
    cout << mx_square;
    return 0;
}
//5
//4 1 3 5 2

//9
//5 5 5 1 9 8 7 1 2
