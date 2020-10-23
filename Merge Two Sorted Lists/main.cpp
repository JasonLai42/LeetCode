#include <iostream>

/**
 * Definition for singly-linked list.
 */
 struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        // Check edge case
        if(l1 == nullptr) {
            // If l2 is nullptr as well, this still works; we just return nullptr
            return l2;
        }
        else if(l2 == nullptr) {
            return l1;
        }
        
        // merged_headd to hold head of final list, current to hold last added node to final 
        // list
        ListNode* merged_head;
        ListNode* current;
        
        // First set up the head of the new merged, sorted list
        if(l1->val > l2->val) {
            merged_head = l2;
            current = merged_head;
            l2 = l2->next;
        }
        else {
            merged_head = l1;
            current = merged_head;
            l1 = l1->next;
        }
        
        for(;;) {
            if(l1 == nullptr) {
                // If l2 is also nullptr, still works
                current->next = l2;
                break;
            }
            else if(l2 == nullptr) {
                current->next = l1;
                break;
            }
            
            // Take the min value of the two lists as the next node from the current node
            // Shift current pointer to newly added node and l1 or l2 pointer for whichever 
            // list added a value
            if(l1->val > l2->val) {
                current->next = l2;
                l2 = l2->next;
                current = current->next;
            }
            else {
                current->next = l1;
                l1 = l1->next;
                current = current->next;
            }
        }
        
        return merged_head;
    }
};