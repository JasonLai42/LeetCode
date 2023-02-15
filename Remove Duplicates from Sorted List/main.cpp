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
    ListNode* deleteDuplicates(ListNode* head) {
        // Edge case: no nodes in the list
        if(head == nullptr) {
            return head;
        }

        // Basically to remove the duplicates, we store the node of the first instance we 
        // see of a specific number, and then we continue to iterate until we see the first 
        // instance of a different number. We then have the stored node's next pointer point 
        // to the first instance of the new number we encountered, thereby cutting out all the 
        // duplicates of the number we stored. We then store the first instance of the new 
        // number we encountered and continue doing the same.
        ListNode* firstInstance = head;
        ListNode* current = head->next;
        while(current != nullptr) {
            if(current->val != firstInstance->val) {
                firstInstance->next = current;
                firstInstance = current;
            }
            current = current->next;
        }
        // If we've reached the end of the list, we have to set the last-number-we-stored's 
        // next pointer to nullptr, since that will be the end of our list and cut out any 
        // duplicates of the last number that may be in the list.
        firstInstance->next = nullptr;

        return head;
    }
};