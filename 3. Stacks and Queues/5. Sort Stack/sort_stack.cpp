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

    void print() {
        for (int i = 0; i < stk.size(); i++) {
            cout << stk[i] << " ";
        }
        cout << endl;
    }
};

class Sort {
    public:
    void sortStack(Stack &stk) { 
        int size = stk.size(); // size of stack
        for (int i = 0; i < size; i++) { // gets the max and puts it at the bottom of the stack
            Stack temp;
            int max = stk.pop();

            for (int j = i + 1; j < size; j++) { // since the max is at the bottom after each iteration, we we only need to pop
                                                // however many elements haven't been sorted yet
                int d = stk.pop();
                if (d < max) {
                    temp.push(d);
                } else {
                    temp.push(max);
                    max = d;
                }
            }
            temp.push(max);

            while (!temp.isEmpty()) { // put elements back onto to the stack to restart the process
                stk.push(temp.pop());
            }
        }
    }

    void sortStackT(Stack &stk) {
        Stack stk2;
        while (!stk.isEmpty()) {
            int tmp = stk.pop();
            while (!stk2.isEmpty() && stk2.top() < tmp) {
                stk.push(stk2.pop());
            }
            stk2.push(tmp);
        }
        stk = stk2;
    }
};

int main() {
    Stack s;
    s.push(5);
    s.push(7);
    s.push(10);
    s.push(9);
    s.push(6);
    s.print(); 
    
    Sort sort;
    sort.sortStackT(s);
    s.print(); 
    sort.sortStackT(s);
    s.print(); 
}