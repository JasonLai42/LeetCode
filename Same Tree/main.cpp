/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        // Base case for recursion, if either p or q are nullptr aka leaf nodes
        if(p == nullptr || q == nullptr) {
            // If p or q are nullptr from the above statement, then that means if one of 
            // them is not a nullptr, then they aren't equal, so the trees are not the same
            if(p != nullptr || q != nullptr) {
                return false;
            }
            // Otherwise, both p and q are nullptr so return true
            else {
                return true;
            }
        }

        // If p and q have the same value, we need to keep traversing the trees until we reach 
        // the end (via DFS) or find a discrepancy
        if(p->val == q->val) {
            // We use a ternary statement because we know that both the left and right 
            // subtrees must return true in order for the trees to be the same, so if we 
            // explore the left subtree first and find a discrepancy, we can short circuit 
            // and return false without even having to explore the right subtree
            // Otherwise, if the left subtree is the same between the two trees, then we 
            // continue with exploring and comparing the right subtrees as well
            return isSameTree(p->left, q->left) ? isSameTree(p->right, q->right) : false;
        }
        // If the values aren't the same, we have found a discrepancy and return false
        else {
            return false;
        }
    }
};