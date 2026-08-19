#include <iostream>
#include <queue>
#include <limits>

using namespace std;

class TreeNodeBST {
    private:
    void inOrder(TreeNodeBST* n) {
        if (n != nullptr) {
            inOrder(n->left);
            cout << n->data << " ";
            inOrder(n->right);
        }
    }

    public:
    int data;
    TreeNodeBST* left;
    TreeNodeBST* right;

    TreeNodeBST(int d) {
        data = d;
        left = nullptr;
        right = nullptr;
    }

    void addChild(TreeNodeBST* n) {
        if (n->data == data) return;

        if (n->data < data) {
            if (!left) left = n;
            else left->addChild(n);
        } else {
            if (!right) right = n;
            else right->addChild(n);
        }
    }

    void print() {
        inOrder(this);
        cout << endl;
    }
};

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

class Validate {
    private:
    bool search(auto* root, int min, int max) {
        if (root == nullptr) return true;

        if (root->data >= max || root->data < min) {
            return false;
        }

        return search(root->left, min, root->data) && search(root->right, root->data, max);;
    }

    public:
    bool validateBST(auto* root) {
        if (root == nullptr) return true;

        return search(root->left, INT_MIN, root->data) && search(root->right, root->data, INT_MAX);
    }
};

int main() {
    TreeNode* t = new TreeNode(5);
    t->addChild(new TreeNode(7));
    t->addChild(new TreeNode(9));
    t->addChild(new TreeNode(1));

    TreeNodeBST* b = new TreeNodeBST(5);
    b->addChild(new TreeNodeBST(3));
    b->addChild(new TreeNodeBST(4));
    b->addChild(new TreeNodeBST(6));

    Validate v;
    cout << boolalpha << v.validateBST(t) << endl; // false
    cout << boolalpha << v.validateBST(b) << endl; // true
    return 0;
}