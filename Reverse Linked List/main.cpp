/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        // Easiest algorithm is to just reverse the next pointers in the other direction. 
        // So each node is going to point to the node that was behind it in the original list.
        
        // Our return, which will eventually be the last node in the linked list. Since we're
        // reversing the linked list, the last node will be the newHead.
        ListNode* newHead;

        // Edge case
        if(head == nullptr) {
            return head;
        }

        // prevNode stores the previous node we were visiting because we need to point the 
        // current node's next pointer to it.
        ListNode* prevNode = head;
        // current stores the current node we are visiting.
        ListNode* current = head->next;
        // Initially, prevNode is head, and since head is going to end up being our tail, we 
        // need to set its next pointer as nullptr
        prevNode->next = nullptr;
        // Iterate through the list.
        while(current != nullptr) {
            // We temporarily store the next node that comes after the current node, that way 
            // we can continue iterating through the list and don't lose track of the rest of 
            // the list.
            ListNode* nextNode = current->next;
            // Set the current node's next pointer to the node behind it to reverse.
            current->next = prevNode;
            // Set up the next iteration: the prevNode will be the current node and the current 
            // node will be the nextNode.
            prevNode = current;
            current = nextNode;
        }

        // current should be nullptr at this point, meaning prevNode must be the last node in 
        // the list i.e. the tail, which is going to be our newHead in the reversed list, so 
        // set it as such.
        newHead = prevNode;

        return newHead;
    }
};