#include <vector>
#include <iostream>
using namespace std;

class Stack {
    private:
    vector<int> stk;
    vector<int> minStk;
    int size = 0;

    public:
    void push(int d) {
        stk.push_back(d);
        if (minStk.size() == 0) {
            minStk.push_back(d);
        } else {
            if (d <= minStk[minStk.size() - 1]) {
                minStk.push_back(d);
            }
        }
        size++;
    }

    int pop() {
        if (isEmpty()) {
            throw;
        }

        int d = stk[stk.size() - 1];
        stk.pop_back();
        if (d == minStk[minStk.size() - 1]) {
            minStk.pop_back();
        }
        size--;
        return d;
    }

    int top() {
        // throw for now but should throw a specific exception if empty
        return isEmpty() ? throw : stk[stk.size() - 1];
    }

    int min() {
        return isEmpty() ? throw : minStk[minStk.size() - 1];
    }

    bool isEmpty() {
        return size == 0;
    }
};

int main() {
    Stack s;
    s.push(1);
    s.push(2);
    cout << s.min() << endl; // 1
    s.push(0);
    cout << s.min() << endl; // 0
    cout << s.pop() << endl; // 0
    cout << s.min() << endl; // 1
}