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
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        // Use divide & conquer
        // We're going to take advantage of a property of binary search trees, which is that 
        // every subtree of a binary search tree is also a binary search tree. So, we're 
        // going to use a modified binary search algorithm to halve portions of the array into 
        // smaller and smaller pieces, and turn the pieces into binary search trees, and on 
        // return we put the pieces together to create larger and larger subtrees until the 
        // entire tree is made.
        return divideAndConquer(nums, 0, nums.size()-1);
    }

    TreeNode* divideAndConquer(vector<int>& nums, int l, int r) {
        TreeNode* root = new TreeNode;

        // We have two base cases here
        // If our left and right pointers have crossed each other, we know there's no node 
        // here to add to our binary search tree, so return a nullptr
        if(r < l) {
            root = nullptr;
            return root;
        }
        // If the left and right pointers are equal to one another, we know there's exactly 
        // one node in this piece of array we've broken down, so we make a single-node subtree 
        // and return it
        if(l == r) {
            root->val = nums[l];
            // Note that left and right for root here are default nullptr so we don't have to set them
            return root;
        }
        
        // Calculate the midpoint like any other binary search algorithm
        int mid = l + (r - l) / 2;

        // Set the value of this node
        root->val = nums[mid];
        // Set this node's left and right pointers to the left and right subtrees we're 
        // going to get from the returns of the recursive calls
        root->left = divideAndConquer(nums, l, mid-1);
        root->right = divideAndConquer(nums, mid+1, r);
        // Return this node, so that it can either be set as the root of a subtree for another 
        // node or this is the root of the entire tree
        return root;
    }
};