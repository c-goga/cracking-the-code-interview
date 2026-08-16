#include <iostream>
using namespace std;

class Stack {
    private:
    int size = 0;
    int limit = 1;
    int* stk = new int[1];

    public:
    int pop() {
        size--;
        return stk[size];
    }

    void push(int d) {
        if (size == limit) {
            int* newStk = new int[limit * 2];
            for (int i = 0; i < size; i++) {
                newStk[i] = stk[i];
            }
            delete[] stk;
            stk = newStk;
            limit *= 2;
        }
        stk[size] = d;
        size++;
    }

    int top() {
        return stk[size - 1];
    }

    bool isEmpty() {
        return size == 0;
    }
};

int main() {
    Stack s;
    s.push(1);
    s.push(2);
    s.push(3);
    cout << s.top() << endl; // 3
    cout << s.pop() << endl; // 3
    cout << s.top() << endl; // 2
    cout << boolalpha << s.isEmpty() << endl; // false
    return 0;
}