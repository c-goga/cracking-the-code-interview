#include <iostream>
#include <unordered_map>
#include <cmath>
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

    void insertToTail(int d) {
        Node* n = new Node(d);

        if (this->tail == NULL) {
            this->head = n;
            this->tail = n;
            return;
        }

        this->tail->next = n;
        this->tail = n;
    }

    void insertToTailNode(Node *n) {
        this->tail->next = n;
        this->tail = n;
    }
};

class Intersection {
    public:
    // my implementation
    Node* isIntersection(Node* n1, Node* n2) {
        unordered_map<Node*, bool> m;

        while (n1 != NULL) {
            m[n1] = true;
            n1 = n1->next;
        }

        while (n2 != NULL) {
            if (m[n2]) {
                return n2;
            }
            n2 = n2->next;
        }

        return NULL;
    }

    // textbook based on approach information and looking at some of the coe
    class Result { // need to make a separate class to get both the tail and length in one cycle
        public:
        int length;
        Node* tail;

        Result() {
            this->length = 0;
            this->tail = NULL;
        }
    };

    Node* isIntersectionT(Node* n1, Node* n2) {
        Result* r1 = getTailAndLength(n1);
        Result* r2 = getTailAndLength(n2);

        if (r1->tail != r2->tail) {
            return NULL;
        }

        Node* shorter = r1->length < r2->length ? n1 : n2;
        Node* longer = r1->length >= r2->length ? n1 : n2;

        int count = abs(r1->length - r2->length);
        while (count > 0) {
            longer = longer->next;
            count--;
        }

        while (shorter != longer) {
            shorter = shorter->next;
            longer = longer->next;
        }

        return shorter;
    }

    Result* getTailAndLength(Node* n) {
        if (n == NULL) {
            return new Result();
        }

        Result* r = new Result();
        r->length++;
        while (n->next != NULL) {
            r->length++;
            n = n->next;
        }
        r->tail = n;
        return r;
    }
};

int main() {
    LinkedList l1;
    LinkedList l2;
    l1.insertToTail(1);
    l1.insertToTail(2); // 1 2 
    l2.insertToTail(3);
    l2.insertToTail(4); // 3 4 
    Intersection i;
    cout << (i.isIntersectionT(l1.head, l2.head) == NULL ? "NULL" : "FAILURE: NOT NULL") << endl; // NULL

    Node* n = new Node(5);
    l1.insertToTailNode(n); // 1 2 5 
    l2.insertToTailNode(n); // 3 4 5, remember it is by reference, not by value 
    cout << i.isIntersectionT(l1.head, l2.head)->data << endl; // 5
    return 0;
}