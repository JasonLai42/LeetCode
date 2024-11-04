// Time Complexity: O(n), Space Complexity: O(n)
// Keep a log of all the nodes we've visited. In this case, the log is an unordered_set of 
// the node pointers - every pointer is unique hence the set. We simply iterate through the 
// linked list and if we encounter a node we've visited before, then we know there's a cycle 
// so we return true. If we make it through the whole list, there's no cycle, so we return 
// false.

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
    bool hasCycle(ListNode *head) {
        // Log all the nodes we've visited
        unordered_set<ListNode*> visited;

        // Iterate through linked list
        ListNode* current = head;
        while(current != nullptr) {
            // If we've visited this node before, there's a cycle so return true
            if(visited.find(current) != visited.end()) {
                return true;
            }
            // Otherwise, we haven't visited this node, so add it to visited now
            else {
                visited.insert(current);
            }
            // Continue iterating
            current = current->next;
        }

        // If we made it through the whole list, there's no cycle so return false
        return false;
    }
};