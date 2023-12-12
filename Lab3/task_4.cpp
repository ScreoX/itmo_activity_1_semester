#include <iostream>
using namespace std;

class Queue {
private:
    struct Node {
        int data;
        Node *next;
        Node *prev;
    };

    Node *head;
    Node *tail;

public:
    Queue() : head(nullptr), tail(nullptr) {}
    void enqueue(int data) {
        Node *newNode = new Node{data};
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
            tail -> next = nullptr;
        }
    }

    int pop_front() {
        if (isEmpty()) {
            return 0;
        }
        Node *temp = head;
        head = head->next;
        int x = temp -> data;
        delete temp;

        return x;
    }

    int pop_back() {
        if (isEmpty()) {
            return 0;
        }
        Node *temp = tail;
        tail = tail->prev;
        int x = temp -> data;
        delete temp;
        return x;
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
    long n;
    int m;
    cin >> n >> m;
    Queue queue;
    int mx, mn;
    if (n >= m) {
        for (int i = 0; i < m; i++) {
            int x;
            cin >> x;
            queue.enqueue(x);
        }

        for (int i = 0; i < n - m; i++) {
            int x;
            cin >> x;

            int f = queue.pop_back();
            int b = queue.pop_front();

            if (x <= f) {
                if (f >= b)
                    mx = f;
                else
                    mx = b;
            }
            else if (b <= f) {
                if (x >= f)
                    mx = x;
                else
                    mx = f;
            }
            else {
                if (x >= b)
                    mx = x;
                else
                    mx = b;
            }

            if (x >= f) {
                if (f <= b)
                    mn = f;
                else
                    mn = b;
            }
            else if (b >= f) {
                if (x <= f)
                    mn = x;
                else
                    mn = f;
            }
            else {
                if (x <= b)
                    mn = x;
                else
                    mn = b;
            }
            queue.enqueue((x + f + b) - (mx + mn));
            queue.enqueue(mx);
        }
        for (int i = 0; i < m; i++) {
            cout << queue.front() << " ";
            queue.pop_front();
        }
        return 0;
    }
    else {
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            queue.enqueue(x);
        }

        for (int i = 0; i < n; i++) {
            cout << queue.front() << " ";
            queue.pop_front();
        }
        return 0;
    }
}
