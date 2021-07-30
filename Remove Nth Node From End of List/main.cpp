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

#include <unordered_map>

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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // Store the pointer for a node with the index that it shows up in the list as the key
        unordered_map<int, ListNode*> index_to_node;
        
        // We use a counter to get the key/index for where a node occurs in the list
        int count = 0;
        ListNode* curr_node = head;
        while(curr_node != NULL) {
            count++;
            
            // Store the node according to its index
            index_to_node[count] = curr_node;
            
            curr_node = curr_node->next;
        }
        // After this loop finishes, count should equal the size of the linked list
        // We can use the size of the linked list and subtract (n - 1) from it, get the nth element from the back

        // If the nth element from the back is the head, then we delete the head, i.e. just return the next node
        // This works for the case if the linked list only has one node and we're supposed to delete the head because we return
        // head->next which should be NULL in this case
        if(index_to_node[count - (n - 1)] == head) {
            return head->next;
        }
        // Else, delete the nth element from the back
        else {
            // We take the next pointer of node that comes before the one we have to delete i.e. count - n and set it to the 
            // node that comes after the one we have to delete i.e. count - (n - 2)
            // Then return the head as normal
            index_to_node[count - n]->next = index_to_node[count - (n - 2)];
            return head;
        }
    }
};