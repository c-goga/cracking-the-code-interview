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

class Sum {
    public:
    LinkedList sumListsReverse(Node* h1, Node* h2) {
        LinkedList l;
        int overflow = 0;
        while (h1 != NULL || h2 != NULL) {
            if (h1 != NULL && h2 != NULL) {
                int sum = h1->data + h2->data;
                if (sum >= 10) {
                    l.insertAtTail(sum - 10 + overflow);
                    overflow = 1;
                } else {
                    l.insertAtTail(sum + overflow);
                    overflow = 0;
                }
                h1 = h1->next;
                h2 = h2->next;
            } else if (h1 != NULL) {
                l.insertAtTail(h1->data + overflow);
                overflow = 0;
                h1 = h1->next;
            } else {
                l.insertAtTail(h2->data + overflow);
                overflow = 0;
                h2 = h2->next;
            }
        }

        if (overflow == 1) {
            l.insertAtTail(1);
        }

        return l;
    }

    LinkedList sumListsForward(Node* h1, Node* h2) {
        LinkedList l;
        if (h1 == NULL) {
            while (h2 != NULL) {
                l.insertAtTail(h2->data);
                h2 = h2->next;
            }
            return l;
        }

        if (h2 == NULL) {
            while (h1 != NULL) {
                l.insertAtTail(h1->data);
                h1 = h1->next;
            }
            return l;
        }

        int length1 = 0;
        int length2 = 0;
        Node* n = h1;
        while(n != NULL) {
            length1++;
            n = n->next;
        }
        n = h2;
        while(n != NULL) {
            length2++;
            n = n->next;
        }

        while (h1->next != NULL || h2->next != NULL) {
            if (h1 != NULL && h2 != NULL) {
                if (length1 > length2) {
                    int d = h1->data; // list 1 is bigger so its add digits to list first
                    h1 = h1->next;
                    length1--;
                    if (length1 == length2) {
                        int carry = 0;
                        if (h1->data + h2->data >= 10) {
                            carry = 1;
                        }
                        l.insertAtTail(d + carry);
                    }
                } else if (length1 < length2) { 
                    int d = h2->data; // list 2 is bigger so its add digits to list first
                    h2 = h2->next;
                    length2--;
                    if (length1 == length2) {
                        int carry = 0;
                        if (h1->data + h2->data >= 10) {
                            carry = 1;
                        }
                        l.insertAtTail(d + carry);
                    }
                } else { // once lengths are equal we can go back to our originial implementation
                    int sum = h1->data + h2->data;

                    int carry = 0;
                    if (h1->next->data + h2->next->data >= 10) {
                        carry = 1;
                    }

                    l.insertAtTail((sum % 10) + carry);
                    h1 = h1->next;
                    h2 = h2->next;
                }
            } else if (h1->next != NULL) { // should only be used if list 2 is empty
                l.insertAtTail(h1->data);
                h1 = h1->next;
            } else { // should only be used if list 1 is empty
                l.insertAtTail(h2->data);
                h2 = h2->next;
            }
        }
        if (length1 == length2) {
            l.insertAtTail((h1->data + h2->data) % 10);
        }

        return l;
    }
};

int main() {
    LinkedList l1;
    LinkedList l2;
    Sum s;

    l1.insertAtTail(7); l1.insertAtTail(1); l1.insertAtTail(6);
    l2.insertAtTail(5); l2.insertAtTail(9); l2.insertAtTail(2);
    LinkedList res = s.sumListsReverse(l1.head, l2.head);
    res.print(); // 2 1 9

    LinkedList l3;
    LinkedList l4;
    l3.insertAtTail(6); l3.insertAtTail(1); l3.insertAtTail(7);
    l4.insertAtTail(2); l4.insertAtTail(9); l4.insertAtTail(5);
    res = s.sumListsForward(l3.head, l4.head);
    res.print(); // 9 2 1

    l2.insertAtTail(1);
    res = s.sumListsReverse(l1.head, l2.head);
    res.print(); // 2 1 9 1

    l4.insertAtTail(1);
    res = s.sumListsForward(l3.head, l4.head);
    res.print(); // 3 5 6 8

    LinkedList l5; // empty list check

    res = s.sumListsReverse(l1.head, l5.head);
    res.print(); // 7 1 6
    res = s.sumListsForward(l4.head, l5.head);
    res.print(); // 2 9 5 1

    return 0;
}