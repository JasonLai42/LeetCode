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

#include <stddef.h>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        // If the linked list is of size 0 or 1, return the head
        if(head == NULL || head->next == NULL) {
            return head;
        }
        
        // Because we didn't hit that edge case above, we know there's at least 2 nodes in the linked list
        // Store the second node in new_head for our return statement
        ListNode* new_head = head->next;
        
        // This value will oscillate between 0 and 1
        // We know that:
        //  - Every even numbered node will point to the node preceding it in the list's original order after swaps
        //  - Every odd numbered node will point to the node 3 positions in front of it in the list's original order 
        //      after swaps
        // So our algorithm will process the list pair by pair, but for each pair we swap, we need both the current pair
        // and preceding pair to join up the linked list, hence the 4 ListNode* variables node_1 through node_4
        // Example: ORIGINAL: 1->2->3->4->5->6
        //       AFTER SWAPS: 2->1->4->3->6->5
        // Basically we have 2 quartets to process in the loop:
        //  - One where the preceding pair is (1, 2) and the current pair is (3, 4)
        //  - Another one where the preceding pair is (3, 4) and the current pair is (5, 6)
        int every_two = 0;
        ListNode* node_1 = head;
        ListNode* node_2 = head->next;
        ListNode* node_3;
        ListNode* node_4;
        ListNode* current_node = head->next->next;
        while(current_node != NULL) {
            switch(every_two) {
                case 0:
                    // Get first node of the current pair
                    node_3 = current_node;
                    current_node = current_node->next;
                    every_two++;
                    break;
                case 1:
                    // Get second node of the current pair
                    node_4 = current_node;
                    current_node = current_node->next;
                    every_two--;
                    
                    // Swap accordingly and set the appropriate pointers
                    // This line and only this line is going to be a redundant computation
                    node_2->next = node_1;
                    node_1->next = node_4;
                    node_4->next = node_3;
                    
                    // Set the current pair to be the new preceding pair
                    node_1 = node_3;
                    node_2 = node_4;
                    break;
            }
        }
        
        // After the above loop finishes, we have one of two cases:
        //  - every_two is equal to 0, so all swaps have been completed, we just need to set the last node's next to NULL
        //  - every_two is equal to 1, so there's a dangling node at the end with no partner to swap places with
        switch(every_two) {
            case 0:
                // Again this is a potentially redundant computation (for the case if there's only 2 nodes in the list)
                node_2->next = node_1;
                // This completes the new list after swaps
                node_1->next = NULL;
                break;
            case 1:
                // Potentially a redundant computation (for the case if there's only 3 nodes in the list)
                node_2->next = node_1;
                // Point node_1 to the dangling node
                node_1->next = node_3;
                // This completes the new list after swaps; dangling node is last node so set next field to NULL
                node_3->next = NULL;
                break;
        }
            
        return new_head;
    }
};