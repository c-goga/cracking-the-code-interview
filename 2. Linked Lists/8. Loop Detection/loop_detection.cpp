#include <iostream>
#include <unordered_map>
using namespace std;

class Node {
    public:
    int data;
    Node* next;

    Node() {
        this->data = 0;
        this->next = NULL;
    }

    Node(int d) {
        this->data = d;
        this->next = NULL;
    }
};

class LinkedList {
    public:
    Node* head;
    Node* tail;

    LinkedList() {
        this->head = NULL;
        this->tail = NULL;
    }

    void insertTail(int d) {
        Node* n = new Node(d);

        if (this->tail == NULL) {
            this->head = n;
            this->tail = n;
            return;
        }

        this->tail->next = n;
        this->tail = n;
    }

    void insertTailNode(Node* n) {
        if (this->tail == NULL) {
            this->head = n;
            this->tail = n;
            return;
        }

        this->tail->next = n;
        this->tail = n;
    }
};

class Loop {
    public:
    Node* detectLoop(Node* head) {
        Node* slow = head;
        Node* fast = head;

        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                return findLoopStart(head, fast);
            }
        }

        return NULL;
        // unordered_map<Node*, bool> mp;
        // while(head != NULL) {
        //     if (mp[head]) {
        //         return head;
        //     }

        //     mp[head] = true;
        //     head = head->next;
        // }
        // return NULL;
    }

    Node* findLoopStart(Node* n1, Node* n2) {
        while (n1 != n2) {
            n1 = n1->next;
            n2 = n2->next;
        };
        return n1;
    }
};

int main() {
    LinkedList l;
    l.insertTail(1);
    l.insertTail(2);
    Node* n = new Node(3);
    l.insertTailNode(n);
    l.insertTail(4);
    l.insertTail(5); // 1 2 3 4 5

    Loop lp;
    cout << (lp.detectLoop(l.head) == NULL ? "NULL" : "FAIL: NOT NULL") << endl; // NULL
    l.insertTailNode(n); // 1 2 3 4 5 3 ...
    cout << lp.detectLoop(l.head)->data << endl; // 3
    
    return 0;
}