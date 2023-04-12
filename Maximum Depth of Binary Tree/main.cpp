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
    int maxDepth(TreeNode* root) {
        // So very simply, we're just gonna do a DFS and count the length of each branch until 
        // we've traversed the whole tree, then return the longest path which is the max depth.

        // Call to our auxiliary function
        return getMaxDepth(root);
    }

    int getMaxDepth(TreeNode* node) {
        // Our base case for recursion: if node is nullptr, this is the end of this branch, 
        // and since this isn't a valid node, we don't count it as part of the depth, so we 
        // return 0
        if(node == nullptr) {
            return 0;
        }

        // We're going to perform DFS, so we explore both the left and right subtrees, but for 
        // our return, we're only concerned with whichever subtree has the largest depth, hence 
        // why we perform a max() on the return of both the left and right subtree calls to 
        // getMaxDepth(). We add 1 to whatever the size of the largest depth subtree is, 
        // because we have to count the current node we are on as part of the depth for the 
        // overall tree.
        return max(getMaxDepth(node->left), getMaxDepth(node->right)) + 1;
    }
};