#include <vector>
#include <iostream>
using namespace std;

class Stack {
    private:
    vector<int> stk;

    public:
    void push(int d) {
        stk.push_back(d);
    }

    int pop() {
        if (isEmpty()) {
            throw;
        }

        int d = stk[stk.size() - 1];
        stk.pop_back();
        return d;
    }

    int top() {
        // throw for now but should throw a specific exception if empty
        return isEmpty() ? throw : stk[stk.size() - 1];
    }

    bool isEmpty() {
        return stk.size() == 0;
    }

    int size() {
        return stk.size();
    }
};

class MyQueue {
    // my implementation needlessly switches too many times and puts more logic into the stackSwitch function.
    private:
    Stack s1; // if elements in here then it goes oldest -> youngest
    Stack s2; // if elements in here then it goes youngest -> oldest

    // only need to use this when the elements aren't in the right stack when adding and removing
    void stackSwitch() {
        if (s1.isEmpty()) {
            while (!s2.isEmpty()) {
                s1.push(s2.pop());
            }
        } else {
            while (!s1.isEmpty()) {
                s2.push(s1.pop());
            }
        }
    }

    public:
    void add(int d) {
        if (!s2.isEmpty()) {
            stackSwitch();
        }
        s1.push(d);
    }

    int remove() {
        if (s2.isEmpty()) {
            stackSwitch();
        }
        return s2.pop();
    }
};

class MyQueueT {
    // implementation with textbook tips

    // this works better since it only needs to possibly give elements to the old stack on remove and peek
    private:
    Stack oldStk;
    Stack newStk;

    void stackSwitch() {
        if (oldStk.isEmpty()) {
            while (!newStk.isEmpty()) {
                oldStk.push(newStk.pop());
            }
        }
    }

    public:

    void add(int d) {
        newStk.push(d);
    }

    int remove() {
        stackSwitch();
        return oldStk.pop();
    }

    int size() {
        return newStk.size() + oldStk.size();
    }

    int peek() {
        stackSwitch();
        return oldStk.top();
    }
};

int main() {
    MyQueueT q;
    q.add(1);
    q.add(2);
    q.add(3);
    cout << q.remove() << endl; // 1
    q.add(4);
    cout << q.remove() << endl; // 2
    return 0;
}