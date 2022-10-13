/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void deleteNode(ListNode* node) {
        // I guess there's no constraint on modifying the node values for this problem, so we'll
        // go with that. (I honestly looked at the solutions; tunnel-visioned on having to 
        // not modify the list values because I just did Reverse Nodes in k-Group)

        // Very simple.
        // We want prevNode here to store the node before currentNode, because when we reach the 
        // last node, we want to make this prevNode point to nullptr, effectively deleting 1 node.
        ListNode* prevNode;
        // The current node we're looking at.
        ListNode* currentNode = node;
        // We keep going until we hit the last node in the list. When this loop terminates, 
        // currentNode will equal the last node in the list.
        while(currentNode->next != nullptr) {
            // Make the current node's value the next nodes value. We're shifting all the values 
            // to the left by 1, effectively overwriting or "deleting" the value of our node of 
            // interest.
            currentNode->val = currentNode->next->val;
            prevNode = currentNode;
            currentNode = currentNode->next;
        }
        // Delete the last node.
        prevNode->next = nullptr;
    }
};