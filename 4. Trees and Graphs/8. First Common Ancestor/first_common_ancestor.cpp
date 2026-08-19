#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

class TreeNode {
    public:
    int d;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;

    TreeNode(int d) {
        this->d = d;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    void addChild(TreeNode* n) {
        if (n == nullptr) return;
        queue<TreeNode*> q;
        q.push(this);
    
        while (!q.empty()) {
            TreeNode* curr = q.front();
            q.pop();

            if (curr->left == nullptr) {
                curr->left = n;
                curr->left->parent = curr;
                return;
            } else {
                q.push(curr->left);
            }

            if (curr->right == nullptr) {
                curr->right = n;
                curr->right->parent = curr;
                return;
            } else {
                q.push(curr->right);
            }

        }
    }
    
};

class FCA {
    public:
    // O(d) time where d is the depth of the tree, O(n) space where n is the number of nodes
    TreeNode* firstCommonAncestor(TreeNode* n1, TreeNode* n2) {
        // map for O(1) lookups
        unordered_map<TreeNode*, bool> mp;

        // while either node still has a parent
        while (n1->parent != nullptr || n2->parent != nullptr) {
            if (n1->parent != nullptr) {
                if (mp[n1->parent]) return n1->parent;

                mp[n1->parent] = true;
                n1 = n1->parent;
            }

            if (n2->parent != nullptr) {
                if (mp[n2->parent]) return n2->parent;

                mp[n2->parent] = true;
                n2 = n2->parent;
            }
        }

        // this shouldn't happen as there should always be a common ancestor
        return nullptr;
    }
};

int main() {
    TreeNode* root = new TreeNode(7);
    TreeNode* n1 = new TreeNode(1);
    TreeNode* n2 = new TreeNode(3);
    root->addChild(new TreeNode(5));
    root->addChild(new TreeNode(9));
    root->addChild(new TreeNode(4));
    root->addChild(n1);
    root->addChild(new TreeNode(11));
    root->addChild(n2);
    /**
     * tree representation:
     * 
     *           7
     *       5       9
     *    4    1   11   3
     */

    FCA f;
    cout << f.firstCommonAncestor(n1, n2)->d << endl; // 7
    cout << f.firstCommonAncestor(n1, n1->parent->left)->d << endl; // 5
    cout << f.firstCommonAncestor(n1, n1->parent)->d << endl; // 7
    return 0;
}