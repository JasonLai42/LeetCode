#include <vector>
#include <queue>

using namespace std;

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

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // Check edge case
        if(lists.size() == 0) {
            return NULL;
        }
        
        // Create a min heap for log(k) sorts
        priority_queue<int, vector<int>, greater<int>> q1;
        
        ListNode* head = new ListNode;
        ListNode* current = head;
        
        bool allProcessed = false;
        while(!allProcessed) {
            allProcessed = true;
            // Take next value from each list and put onto min heap
            for(int i = 0; i < lists.size(); i++) {
                if(lists[i] != NULL) {
                    allProcessed = false;
                    
                    q1.push(lists[i]->val);
                    lists[i] = lists[i]->next;
                }
            }
            
            // After new elements are put on the heap, take the least one and put into new merged list
            if(!q1.empty()) {
                current->next = new ListNode(q1.top());
                q1.pop();
                current = current->next;
            }
        }
        
        // Take leftover values in heap and put into merged list
        while(!q1.empty()) {
            current->next = new ListNode(q1.top());
            q1.pop();
            current = current->next;
        }
        
        // Runtime will be nlogk, where n is total number of elements and k is some number less than n (most likely 
        // n - number_of_lists)
        
        // head->next will be NULL if input is [[]], so this edge case is handled
        return head->next;
    }
};