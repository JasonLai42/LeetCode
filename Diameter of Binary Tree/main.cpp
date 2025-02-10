/* Time Complexity: O(n)
 * Space Complexity : O(1)
 * In principle, the same algorithm as Balanced Binary Tree (which I peeked the solution for), except instead of getting 
 * the height difference at every "root" node we get the diameter (add instead of subtract basically). We visit every 
 * node once so the time complexity is O(n) and the space complexity is O(1) because we only store a diameter.
 */

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
        int diameterOfBinaryTree(TreeNode* root) {
            int diameter = 0;
            getHeight(root, diameter);
    
            return diameter;
        }
    
        int getHeight(TreeNode*root, int& diameter) {
            if(root == nullptr) {
                return 0;
            }
    
            int leftHeight = getHeight(root->left, diameter);
            int rightHeight = getHeight(root->right, diameter);
    
            diameter = max(diameter, leftHeight + rightHeight);
    
            return max(leftHeight, rightHeight) + 1;
        }
    };