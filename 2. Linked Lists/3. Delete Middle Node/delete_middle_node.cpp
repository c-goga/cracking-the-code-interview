#include <iostream>
using namespace std;

class Node {
    public:
    int data;
    Node *next;

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
    Node *head;
    Node *tail;

    LinkedList() {
        this->head = NULL;
        this->tail = NULL;
    }

    void insertAtHead(int d) {
        Node *newNode = new Node(d);
        if (head == NULL) {
            this->head = newNode;
            this->tail = newNode;
            return;
        }

        newNode->next = this->head;
        this->head = newNode;
    }

    void insertAtTail(int d) {
        Node *newNode = new Node(d);
        if (tail == NULL) {
            this->head = newNode;
            this->tail = newNode;
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
    
    Node* getNode(int d) {
        Node *temp = head;
        while (temp != NULL && temp->data != d) {
            temp = temp->next;
        }
        return temp;
    }
};

class DeleteMiddle {
    public:
    void deleteMiddleNode(Node *n) {
        if (n == NULL || n->next == NULL) { return; }

        n->data = n->next->data;
        n->next = n->next->next;
    }
};

int main() {
    LinkedList l;
    l.insertAtTail(1);
    l.insertAtTail(2);
    l.insertAtTail(3);
    l.insertAtTail(4);
    l.insertAtTail(5);
    l.insertAtTail(6);
    l.print(); // 1 2 3 4 5 6
    DeleteMiddle d;
    d.deleteMiddleNode(l.getNode(3));
    l.print(); // 1 2 4 5 6
    d.deleteMiddleNode(l.getNode(5));
    l.print(); // 1 2 4 6
    d.deleteMiddleNode(l.getNode(2));
    l.print(); // 1 4 6
    d.deleteMiddleNode(l.getNode(4));
    l.print(); // 1 6
    d.deleteMiddleNode(l.getNode(6));
    l.print(); // 1 6
    return 0;
}