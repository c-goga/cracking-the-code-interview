#include <iostream>
#include<vector>
#include <queue>

using namespace std;

class TreeNode{
    public:
    int d;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int d) {
        this->d = d;
        left = nullptr;
        right = nullptr;
    }


    void addChild(int d) {
        queue<TreeNode*> q;
        q.push(this);

        while (!q.empty()) {
            TreeNode* n = q.front();
            q.pop();

            if (!n->left) {
                n->left = new TreeNode(d);
                return;
            } else {
                q.push(n->left);
            }

            if (!n->right) {
                n->right = new TreeNode(d);
                return;
            } else {
                q.push(n->right);
            }
        }
    }

    TreeNode(vector<int> l) {
        if (l.empty()) return;

        this->d = l[0];
        for (int i = 1; i < l.size(); i++) {
            addChild(l[i]);
        }
    }

    
};

class Subtree {
    private:
    bool search(TreeNode* t1, TreeNode* t2) {
        if (t1 == nullptr && t2 == nullptr) return true; // both null, true they match
        if (t1 == nullptr || t2 == nullptr) return false; // checks if one of the is null, also prevents error on next check

        if (t1->d == t2->d) {
            return search(t1->left, t2->left) && search(t1->right, t2->right); // search left and right subtrees
        } else return false; // return false if no match
    }

    public:
    bool checkSubtree(TreeNode* t1, TreeNode* t2) {
        if (t2 == nullptr) return true; // will assume is true if t2 is null

        queue<TreeNode*> q; // use bfs to search through t1
        q.push(t1);

        while(!q.empty()) {
            TreeNode* n = q.front();
            q.pop();

            // if there is a match, use dfs to check whether it is a subtree or not
            if (n->d == t2->d && search(n->left, t2->left) && search(n->right, t2->right)) return true;
            
            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }

        return false; // return false if no match found
    }
};



int main() {
    TreeNode* t1 = new TreeNode({5, 6, 1, 9, 10, 4, 2, 3});
    /**
     *                  5
     *             6         1
     *          9    10   4     2
     *       3
     */
    TreeNode* t2Valid = new TreeNode({6, 9, 10, 3});
    /**
     *             6        
     *          9    10   
     *       3
     */
    TreeNode* t2Invalid = new TreeNode({4, 9, 10, 3});
    /**
     *             4        
     *          9    10   
     *       3
     */
    Subtree s;
    cout << "True: " << boolalpha << s.checkSubtree(t1, t2Valid) << endl;
    cout << "False: " << boolalpha << s.checkSubtree(t1, t2Invalid) << endl;
    return 0;
}