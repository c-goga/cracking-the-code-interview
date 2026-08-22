#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;


class TreeNode {
    private:
    int search(TreeNode* n, int sum, int target) {
        if (n == nullptr) return 0;

        sum += n->data;
        if (sum == target) return search(n->left, sum, target) + search(n->right, sum, target) + 1;
        else return search(n->left, sum, target) + search(n->right, sum, target);
    }

    int searchT(TreeNode* n, int sum, int target, unordered_map<int, int> &pathCount) {
        if (n == nullptr) return 0;

        int paths = 0;
        sum += n->data;
        pathCount[sum] += 1;
        if (sum == target) paths++;
        if (pathCount[sum - target]) paths += searchT(n->left, sum, target, pathCount) + searchT(n->right, sum, target, pathCount) + pathCount[sum - target];
        else paths += searchT(n->left, sum, target, pathCount) + searchT(n->right, sum, target, pathCount);
        pathCount[sum] -= 1;
        return paths;
    }

    public:
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int d) {
        data = d;
        left = nullptr;
        right = nullptr;
    }

    void insertLeft(int d) {
        delete left;
        left = new TreeNode(d);
    }

    void insertRight(int d) {
        delete right;
        right = new TreeNode(d);
    }

    // O(nlog(n))
    int pathWithSums(int target) {
        queue<TreeNode*> q;
        q.push(this);
        int paths = 0;

        while (!q.empty()) {
            TreeNode* n = q.front();
            q.pop();

            paths += search(n, 0, target);
            if (n->left != nullptr) q.push(n->left);
            if (n->right != nullptr) q.push(n->right);
        }

        return paths;
    }

    // implementation based on textbook info (more optimized) O(n)
    int pathWithSumsT(int target) {
        unordered_map<int, int> pathCount;
        return searchT(this, 0, target, pathCount);
    }
};

int main() {
    TreeNode* root = new TreeNode(7);
    root->insertLeft(-1);
    root->left->insertRight(3);
    root->insertRight(4);
    root->right->insertRight(-5);
    cout << "6 (2 paths): " << root->pathWithSumsT(6) << endl;
    cout << "-1 (2 paths): " << root->pathWithSumsT(-1) << endl;
    cout << "2 (1 path): " << root->pathWithSumsT(2) << endl;
    return 0;
}