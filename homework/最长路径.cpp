// #include <iostream>
// using namespace std;
// struct TreeNode {
//     int val;
//     TreeNode *left;
//     TreeNode *right;
//     TreeNode() : val(0), left(nullptr), right(nullptr) {}
//     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
// };
//
// class Solution {
// private:
//     int maxSum = 0;
//     void backtrack(TreeNode* node, int &curSum) {
//         if (node == nullptr) return;
//         curSum += node->val;
//         if (curSum > maxSum) {
//             maxSum = curSum;
//         }
//         backtrack(node->left, curSum);
//         backtrack(node->right, curSum);
//         curSum -= node->val;
//     }
//
// public:
//     int maxPathSum2(TreeNode *root) {
//         if (root == nullptr) return 0;
//         maxSum = -1e9;
//         int curSum = 0;
//         backtrack(root, curSum);
//         return maxSum;
//     }
// };
//
// int a() {
//     TreeNode* root = new TreeNode(1);
//     root->left = new TreeNode(2);
//     root->right = new TreeNode(3);
//     root->left->right = new TreeNode(5);
//     root->right->left = new TreeNode(7);
//
//     Solution sol;
//     cout << sol.maxPathSum2(root) << endl;
//     return 0;
// }


#include <iostream>
#include <climits>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int maxPathSum2(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }
        maxSum = INT_MIN;
        int currentSum = 0;
        backtrack(root, currentSum);
        return maxSum;
    }

private:
    int maxSum;

    void backtrack(TreeNode* node, int &currentSum) {
        if (node == nullptr) {
            return;
        }

        currentSum += node->val;

        if (currentSum > maxSum) {
            maxSum = currentSum;
        }

        backtrack(node->left, currentSum);
        backtrack(node->right, currentSum);

        currentSum -= node->val;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(5);
    root->left->left->right = new TreeNode(-1);

    Solution sol;
    cout << "最大路径和为：" << sol.maxPathSum2(root) << endl;

    delete root->left->left;
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}