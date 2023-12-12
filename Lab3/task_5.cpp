
#include <iostream>
#include <string>
using namespace std;

struct Saves {
    char letter;
    int num;
};
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
        Node* newNode = new Node{data};
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
            return 1;
        }
        return top->data;
    }
    bool isEmpty() { return top == nullptr; }
};

bool is_num(char a) {
    int x = a;
    if (x >= 48 && x <= 57) {
        return true;
    }

    else {
        return false;
    }
}
bool is_bukva(char a) {
    int x = a;
    if (x >= 65 && x <= 90) {
        return true;
    }

    else {
        return false;
    }
}


int main() {
    string str;
    Stack stack;
    int counter = 0;
    cin >> str;
    Saves save[size(str)];
    int len = size(str);

    int mas_alphabet[26] = {0};

    for (int i = len - 1; i >= 0; i--) {
        int temp_s = 0;
        int num = 1;
        int pow = 1;

        while (is_num(str[i])) {
            temp_s += (str[i] - '0') * pow;
            pow *= 10;
            --i;
        }
        if (temp_s == 0) {
            temp_s = 1;
        }
        num = temp_s;
        if (str[i] == ')') {
            stack.push(num * stack.top_stack());
        }

        if (str[i] == '(') {
            stack.pop();
        }
        else if (is_bukva(str[i])) {
            save[counter].letter = str[i];
            save[counter].num = stack.top_stack() * num;
            ++counter;
        }
    }

    for (int i = 0; i < counter; i++)
        mas_alphabet[save[i].letter - 'A'] += save[i].num;

    for (int i = 0; i < 26; i++) {
        if (mas_alphabet[i] != 0)
            cout << static_cast<char>(i + 'A');
        if (mas_alphabet[i] > 1)
            cout << mas_alphabet[i];
    }
    return 0;
}
//H41ZO2
//H4O2Z
//H4ZO2
//H4O2Z