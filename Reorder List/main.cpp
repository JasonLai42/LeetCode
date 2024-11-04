// Time Complexity: O(n), Space Complexity: O(1)
// Basically, we're going to divide the linked list into two smaller singly linked lists:
// the first list is the front half of the OG list in its normal order and the second list is 
// is the back half of the OG list REVERSED. The rationale here is that our result is basically 
// the first of half of the OG list in its normal order interleaved with the back half of the 
// OG list in reverse order.
//
// For example: [1,2,3,4,5] results in [1,5,2,4,3] because it's the front half [1,2,3] in its 
// normal order interleaved with the back half [4,5] in reverse order i.e. [5,4].

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
    void reorderList(ListNode* head) {
        ListNode* current = head;

        // First count the nodes so we know where to bisect the list
        int numNodes = 0;
        while(current != nullptr) {
            numNodes++;
            current = current->next;
        }

        // Edge case - doesn't work if list is of size 1 or empty
        if(numNodes <= 1) {
            return;
        }

        // Now get the front half of the list in it's normal order and separate it from 
        // the rest of the list
        current = head;
        ListNode* prevNode;
        // It's a given that the first node will always be the original head and every other 
        // node after that is the nodes in the original order, so to get the front half, we simply 
        // increment by 2 until we reach >= numNodes.
        for(int i = 0; i < numNodes; i+=2) {
            prevNode = current;
            current = current->next;
        }
        // Separation from the rest of the list
        prevNode->next = nullptr;

        // Get the back half of the list in it's reverse order.
        // We can thankfully pick up where we left off from the front half code above to get 
        // the back half and I use my reverse a linked list code (check the LC problem) to 
        // to the reversing.
        prevNode = current;
        current = current->next;
        prevNode->next = nullptr;
        while(current != nullptr) {
            ListNode* nextNode = current->next;
            current->next = prevNode;
            prevNode = current;
            current = nextNode;
        }

        // Finally, we interleave the front half and reversed back half to get the final 
        // result.
        current = head;
        ListNode* front = head->next;
        ListNode* back = prevNode;
        // I use a state here to switch between adding a front half node and a back half node 
        // on every iteration.
        bool state = true;
        for(int i = 1; i < numNodes; i++) {
            if(state) {
                current->next = back;
                back = back->next;
                state = false;
            }
            else {
                current->next = front;
                front = front->next;
                state = true;
            }

            current = current->next;
        }
    }
};