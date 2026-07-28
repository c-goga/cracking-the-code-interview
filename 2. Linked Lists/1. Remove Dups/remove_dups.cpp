#include <iostream>
#include <unordered_map>
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
        Node* temp = head;
        if (head == NULL) {
            cout << "List empty" << endl;
            return;
        }

        while (temp != NULL) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

class Dup {
    public:
    void removeDups(Node *head) {
        // temporary buffer solution
        // Time: O(n), Space: O(n)

        // unordered_map<int, bool> mp;
        // Node* temp = head;
        // mp[temp->data] = true;
        // // cout << "d" << endl;
        // while (temp->next != NULL) {
        //     if (!mp[temp->next->data]) {
        //         // cout << "e" << endl;
        //         mp[temp->next->data] = true;
        //         temp = temp->next;
        //     } else {
        //         // cout << "f" << endl;
        //         temp->next = temp->next->next;
        //     }
        // }

        // no temporary buffer solution
        // Time: 0(n^2), Space: O(1)
        
        Node* temp = head;
        while (temp != NULL) {
            Node* temp2 = temp;
            while (temp2->next != NULL) {
                if (temp2->next->data == temp->data) {
                    temp2->next = temp2->next->next;
                } else {
                    temp2 = temp2->next;
                }
            }
            temp = temp->next;
        }
    }
};

int main() {
    Dup d;
    LinkedList l;
    l.insertAtTail(1);
    l.insertAtTail(2);
    l.insertAtTail(1);
    l.insertAtTail(3);
    l.insertAtTail(2);
    d.removeDups(l.head);
    l.print(); // should be 1 2 3

    LinkedList l2;
    l2.insertAtHead(1);
    l2.insertAtHead(1);
    l2.insertAtHead(1);
    l2.insertAtHead(1);
    l2.insertAtHead(1);
    d.removeDups(l2.head);
    l2.print(); // should be 1
    return 0;
}