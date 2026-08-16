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

class SetOfStacks {
    private:
    int threshold;
    vector<Stack> set;

    public:
    SetOfStacks(int threshold) {
        this->threshold = threshold;
        set.push_back(Stack());
    }

    void push(int d) {
        if (set[set.size() - 1].size() == threshold) {
            set.push_back(Stack());
        }
        set[set.size() - 1].push(d);
    }

    int pop() {
        int d = set[set.size() - 1].pop();
        if (set[set.size() - 1].isEmpty()) {
            set.pop_back();
        }
        return d;
    }

    int top() {
        return set[set.size() - 1].top();
    }

    bool isEmpty() {
        return set[0].isEmpty();
    }

    int popAt(int stk) {
        if (stk >= set.size()) {
            throw;
        }

        int d = set[stk].pop();
        if (set[stk].isEmpty()) {
            set.erase(set.begin() + stk);
        }
        return d;
    }

    int numOfStks() {
        return set.size();
    }
};

int main() {
    SetOfStacks s(2);
    s.push(1);
    s.push(2);
    cout << s.numOfStks() << endl; // 1
    s.push(3);
    cout << s.numOfStks() << endl; // 2
    cout << s.pop() << endl; // 3
    cout << s.numOfStks() << endl << endl; // 1

    s.push(4);
    s.push(5);
    s.push(6);
    cout << s.popAt(1) << endl; // 5 // test correctly pops right stack
    cout << s.numOfStks() << endl; // 3
    cout << s.popAt(1) << endl; // 4
    cout << s.numOfStks() << endl; // 2, test correctly removes middle stack

    return 0;
}