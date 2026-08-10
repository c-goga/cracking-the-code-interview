#include <iostream>
#include <unordered_map>
#include <stack>
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

    void insertAtTail(int d) {
        Node* n = new Node(d);

        if (this->tail == NULL) {
            this->head = n;
            this->tail = n;
            return;
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

class Palindrome {
    // M = my implementation
    // RC = reverse and compare
    // I = iterative
    // R = recursive
    public:
    bool isPalindromeM(Node* head) {
        if (head == NULL || head->next == NULL) { // if length of list is 0 or 1
            return true;
        }

        Node* n = head; // get the length, right now I don't think there is a way to do this without first knowing the length
        int length = 0;
        while (n != NULL) {
            length++;
            n = n->next;
        }

        unordered_map<int, int> m; // use a map to keep count of letters 
        n = head;
        int idx = 0;
        while (n != NULL && idx < length / 2) {
            m[n->data]++;
            idx++;
            n = n->next;
        }

        if (length % 2 == 1) {
            n = n->next;
        }

        while (n != NULL) {
            m[n->data]--;
            if (m[n->data] < 0) { // if it goes to negatives, it means that there is a mismatch of letters so not a palindrome
                return false;
            }
            n = n->next;
        }

        return true;
    }

    bool isPalindromeRC(Node* head) {
        Node* reversed = reverseAndClone(head);
        return isEqual(head, reversed);
    }

    Node* reverseAndClone(Node* head) {
        Node* reverse = NULL; // start with NULL
        while (head != NULL) {
            Node* n = new Node(head->data); // make new node with copied data
            n->next = reverse; // next is the current node reverse is on 
            reverse = n; // reset reverse node to the first node
            head = head->next; // go to the next
        }
        return reverse;
    }

    bool isEqual(Node* n1, Node* n2) {
        while (n1 != NULL && n2 != NULL) {
            if (n1->data != n2->data) {
                return false;
            }
            n1 = n1->next;
            n2 = n2->next;
        }
        return n1 == NULL && n2 == NULL;
    }

    bool isPalindromeI(Node* n) {
        Node* slow = n; // can use a slow and fast pointer to find length since we need to be halfway anyways to use a stack
        Node* fast = n;

        stack<int> stk;
        while (fast != NULL && fast->next != NULL) { // check current and next to ensure we can skip twice
            stk.push(slow->data);
            slow = slow->next;
            fast = fast->next->next;
        }

        if (fast != NULL) { // if fast isn't NULL it means there is an odd length so skip the middle element
            slow = slow->next;
        }

        while (slow != NULL) {
            if (slow->data != stk.top()) {
                return false;
            }
            stk.pop(); // pop doesn't return anything, so have to use top above and pop later
            slow = slow->next;
        }

        return true;
    }

    bool isPalindromeR(Node* n) {
        if (n == NULL || n->next == NULL) {
            return true;
        }

        return isPalindromeRecurse(n, getLength(n), &n);
    }

    int getLength(Node* n) {
        int length = 0;
        while (n != NULL) {
            length++;
            n = n->next;
        }
        return length;
    }

    bool isPalindromeRecurse(Node* head, int length, Node **next) {
        if (head == NULL || length <= 0) { // even length
            return true;
        } else if (length == 1) { // odd length
            *next = (*next)->next;
            return true;
        }
        
        *next = (*next)->next; // will always be one step ahead of the head
        bool res = isPalindromeRecurse(head->next, length - 2, next);

        if (!res) {
            return false;
        }

        if (head->data != (*next)->data) { // next is now on the second half of the list, will compare as head moves backward 
                                            // through the list. it does this through the recursive calls made
            return false;
        }

        *next = (*next)->next; // move next one ahead before returning

        return true;
    }
};

int main() {
    LinkedList l;
    Palindrome p;
    l.insertAtTail(1);
    l.insertAtTail(2);
    l.insertAtTail(1);
    cout << boolalpha << p.isPalindromeR(l.head) << endl; // true
    l.insertAtTail(1);
    cout << boolalpha << p.isPalindromeR(l.head) << endl; // false
    l.insertAtTail(2);
    l.insertAtTail(1);
    cout << boolalpha << p.isPalindromeR(l.head) << endl; // true
    return 0;
}