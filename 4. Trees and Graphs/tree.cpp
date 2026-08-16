#include <iostream>
using namespace std;

class TreeNode {
    public:
    int d;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int d) {
        this->d = d;
        left = nullptr;
        right = nullptr;
    }

    void addChild(TreeNode* n) {
        if (left == nullptr && n->d < d) {
            left = n;
        } else if (right == nullptr && n-> d > d) {
            right = n;
        } else if (d == n->d) {
            return;
        } else if (left != nullptr && n->d < d) {
            left->addChild(n);
        } else if (right != nullptr && n->d > d) {
            right->addChild(n);
        }
    }
};


class TraverseBinary {
    public:

    void inOrder(TreeNode* n) {
        if (n != nullptr) {
            inOrder(n->left);
            cout << n->d << " ";
            inOrder(n->right);
        }
    }

    void preOrder(TreeNode* n) {
        if (n != nullptr) {
            cout << n->d << " ";
            preOrder(n->left);
            preOrder(n->right);
        }
    }

    void postOrder(TreeNode* n) {
        if (n != nullptr) {
            postOrder(n->left);
            postOrder(n->right);
            cout << n->d << " ";
        }
    }
};

int main() {
    TreeNode* root = new TreeNode(10);
    root->addChild(new TreeNode(5));
    root->addChild(new TreeNode(1));
    root->addChild(new TreeNode(16));
    root->addChild(new TreeNode(11)); 
    /**
     *          10
     *      5       16
     *  1        11
     */
    TraverseBinary b;
    b.inOrder(root); // 1 5 10 11 16
    cout << endl;
    b.preOrder(root); // 10 5 1 16 11
    cout << endl;
    b.postOrder(root); // 1 5 11 16 10
    cout << endl;
    return 0;
}