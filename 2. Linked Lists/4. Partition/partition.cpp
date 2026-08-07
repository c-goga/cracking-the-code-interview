#include <iostream>
using namespace std;

class Node {
    public:
    int data;
    Node* next;

    Node() {
        this->data = 0;
        this->next = NULL;
    }

    Node (int d) {
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

    void insertAtTail(int d) {
        Node* n = new Node(d);

        if (this->tail == NULL) {
            this->head = n;
            this->tail = n;
        }

        this->tail->next = n;
        this->tail = n;
    }

    void print() {
        Node* n = head;
        while (n != NULL) {
            cout << n->data << " ";
            n = n->next;
        }
        cout << endl;
    }
};

class Partition {
    public:
    
    void partition(Node*& head, int d) {
        Node *first = new Node(); // sentinel node at start of list
        Node* n = head; // node to iterate through list

        if (n->data < d) { // get pointer where we need it, either on the first node before element >= d or before head
            while (n->next != NULL && n->next->data < d) {
                n = n->next;
            }
            first = n;
        } else {
            first->next = head;
        }

        while (n->next != NULL) {
            if (n->next->data < d) { 
                Node* temp = n->next;
                n->next = n->next->next; // remove element < d from original spot
                Node* temp2 = first->next;
                if (first->next == head) { // add element into next of pointer
                    first->next = temp;
                    temp->next = temp2;
                    first = first->next;
                    head = first; // if first is before head, we need to set head equal to the new element (this is why it is passed by reference)
                } else {
                    first->next = temp;
                    temp->next = temp2;
                    first = first->next;
                }
            } else {
                n = n->next;
            }
        }
    }
};

int main() {
    LinkedList l;
    Partition p;
    l.insertAtTail(3);
    l.insertAtTail(5);
    l.insertAtTail(8);
    l.insertAtTail(5);
    l.insertAtTail(10);
    l.insertAtTail(2);
    l.insertAtTail(1);
    l.print(); // 3 5 8 5 10 2 1

    p.partition(l.head, 5);
    l.print(); // 3 2 1 5 8 5 10

    p.partition(l.head, 3);
    l.print(); // 2 1 3 5 8 5 10
    return 0;
}