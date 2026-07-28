#include <iostream>
using namespace std;

class Node {
    public:
    int data;
    Node *next;

    Node() {
        data = 0;
        next = NULL;
    }

    Node(int d) {
        this->data = d;
        this->next = NULL;
    }
};

class LinkedList {
    public:
    Node *head;
    Node *tail;

    LinkedList() {
        head = NULL;
        tail = NULL;
    }

    void insertAtHead(int d) {
        Node *newNode = new Node(d);

        if (head == NULL) {
            head = newNode;
            tail = newNode;
            return;
        }

        newNode->next = this->head;
        this->head = newNode;
    }

    void insertAtTail(int d) {
        Node *newNode = new Node(d);

        if (tail == NULL) {
            head = newNode;
            tail = newNode;
            return;
        }

        this->tail->next = newNode;
        this->tail = newNode;
    }

    void print() {
        Node *temp = head;
        while (temp != NULL) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

class Kth {
    public:
    void removeKthToLast(Node*& head, int k) {
        if (head == NULL) {
            return;
        }

        // int length = 0;
        // Node *temp = head;
        // while (temp != NULL) {
        //     length++;
        //     temp = temp->next;
        // }

        // if (k <= length) {
        //     temp = head;
        //     if (length - k > 0) {
        //         for (int i = 0; i < length - k - 1; i++) {
        //             temp = temp->next;
        //         }
        //         temp->next = temp->next->next;
        //     } else {
        //         head = head->next;
        //     }
        // }

        Node *p1 = head;
        Node *p2 = p1;
        bool end = false;
        for (int i = 0; i < k; i++) {
            if (p2 != NULL) {
                p2 = p2->next;
            } else {
                end = true;
            }
        }
    
        if (!end) {

            if (p2 == NULL) {
                head = head->next;
            } else {
                // cout << "data: " << p1->data << p2->data << endl;
                while (p2->next != NULL) {
                    p2 = p2->next;
                    p1 = p1->next;
                }
                // cout << "data: " << p1->data << endl;
                p1->next = p1->next->next;
            }
        }
    }
};

int main() {
    Kth k;
    LinkedList l;
    l.insertAtTail(1);
    l.insertAtTail(2);
    l.insertAtTail(3);
    l.insertAtTail(4);
    k.removeKthToLast(l.head, 2);
    l.print(); // should be 1 2 4
    k.removeKthToLast(l.head, 1);
    l.print(); // should be 1 2;
    k.removeKthToLast(l.head, 2);
    l.print(); // should be 2
    k.removeKthToLast(l.head, 5);
    l.print(); // should be 2 since k > length
    k.removeKthToLast(l.head, 1);
    l.print(); // should be nothing
    return 0;
}