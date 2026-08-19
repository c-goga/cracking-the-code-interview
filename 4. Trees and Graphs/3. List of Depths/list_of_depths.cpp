#include <iostream>
#include <queue>
using namespace std;

class TreeNode {
    public:
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int d) {
        data = d;
        left = nullptr;
        right = nullptr;
    }

    void addChild(TreeNode* n) {
        if (n->data == data) return;

        queue<TreeNode*> q;
        q.push(this);

        while (!q.empty()) {
            TreeNode* curr = q.front();
            q.pop();

            if(!curr->left) {
                curr->left = n;
                return;
            } else {
                q.push(curr->left);
            }

            if (!curr->right) {
                curr->right = n;
                return;
            } else {
                q.push(curr->right);
            }
        }
    }
};

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

    void print() {
        Node* n = head;
        while (n != NULL) {
            cout << n->data << " -> ";
            n = n->next;
        }
        cout << endl;
    }
};

class Depth {
    public:
    vector<LinkedList> listOfDepths(TreeNode* root) {
        vector<LinkedList> depths;
        queue<TreeNode*> q;
        q.push(root);
        int size = 1;

        while (!q.empty()) {
            LinkedList l;
            while (size > 0) {
                TreeNode* n = q.front();
                q.pop();
                l.insertTail(n->data);
                if (n->left) q.push(n->left);
                if (n->right) q.push(n->right);
                size--;
            }
            depths.push_back(l);
            size = q.size();
        }
        return depths;
    }
};

int main() {
    TreeNode* root = new TreeNode(5);
    root->addChild(new TreeNode(6));
    root->addChild(new TreeNode(3));
    root->addChild(new TreeNode(9));
    root->addChild(new TreeNode(1));
    root->addChild(new TreeNode(2));
    Depth d;
    vector<LinkedList> l = d.listOfDepths(root);
    for (LinkedList list : l) {
        list.print();
    }
    /**
     * 5 ->
     * 6 -> 3 ->
     * 9 -> 1 -> 2 ->
     */
    return 0;
}