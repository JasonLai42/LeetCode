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
    TreeNode* invertTree(TreeNode* root) {
        // Call to auxiliary function that'll do the inversion
        doInversion(root);        

        // Return the original root; it'll still be the root of the new tree after the inversion
        return root;
    }

    // Recursive function to do the inversion, which is basically traversing the tree as DFS, 
    // and inverting the tree from the bottom to the top
    void doInversion(TreeNode* node) {
        // Our base case: if this node is nullptr, that means the node of the previous 
        // recursive call was either a leaf node or only has one child and this child is null, 
        // therefore this branch no longer has any inversions we can do, so return
        if(node == nullptr) {
            return;
        }

        // Swap the children of this node, then continue to invert this subtree
        swapChildren(node);

        // Traverse the left and invert all nodes in the left subtree, then move on to the right
        doInversion(node->left);
        doInversion(node->right);
    }

    // Auxiliary function that does the swapping of children - cleaner code!
    void swapChildren(TreeNode* node) {
        TreeNode* temp = node->left;
        node->left = node->right;
        node->right = temp;
    }
};