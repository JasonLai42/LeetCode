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
    ListNode* reverseKGroup(ListNode* head, int k) {
        // Edge case.
        if(head == nullptr) {
            return head;
        }

        /* HONESTLY, THIS COULD PROBABLY BE WRITTEN MORE ELEGANTLY. CLEAN IT UP. */

        // Reverse the first k elements of the list.
        kSubList currentK = reverseK(head, k);
        // Because there isn't k elements to reverse at the end of the list, we re-reverse the 
        // last k sublist to undo the reversal.
        if(currentK.count < k) {
            kSubList undoReverseK = reverseK(currentK.firstOfThisK, k);
            return undoReverseK.firstOfThisK;
        }
        // Get our return value - the new head of the list after the reversal(s).
        ListNode* newHead = currentK.firstOfThisK;
        // Get the last node in this k sublist so we can have it point to the first node of the 
        // next k sublist.
        ListNode* lastOfThisK = currentK.lastOfThisK;
        while(currentK.firstOfNextK != nullptr) {
            // Reverse the current k sublist.
            currentK = reverseK(currentK.firstOfNextK, k);
            // Because there isn't k elements to reverse at the end of the list, we re-reverse the 
            // last k sublist to undo the reversal.
            if(currentK.count < k) {
                kSubList undoReversek = reverseK(currentK.firstOfThisK, k);
                lastOfThisK->next = undoReversek.firstOfThisK;
                break;
            }
            else {
                // Have the last node in the previous k sublist point to the first node in the 
                // current reversed k sublist.
                lastOfThisK->next = currentK.firstOfThisK;
                lastOfThisK = currentK.lastOfThisK;
            }
        }

        return newHead;
    }

    // Make our lives easier by tracking these items
    struct kSubList {
        ListNode* firstOfThisK;
        ListNode* lastOfThisK;
        ListNode* firstOfNextK;
        int count;
    };

    // Reverses k nodes in the linked list and returns a ptr to the first of the reversed k nodes
    // and the first of the next k nodes.
    kSubList reverseK(ListNode* head, int k) {
        // Our return value.
        kSubList currentKSubList;

        // A counter to track if we've reversed k elements yet.
        int counter = 0;
        // The current node we're looking at.
        ListNode* currentNode = head; 
        // This stores the last currentNode we were looking at. This prevNode is what the 
        // currentNode right now will point to (because we reverse them).
        ListNode* prevNode;
        // Just holds next currentNode we'll look at, so we don't lose track of the rest of the 
        // list while we swap around the pointers.
        ListNode* oldNextNode;
        // We keep going till we reverse k nodes, or we hit the end of the linked list.
        while(counter < k && currentNode != nullptr) {
            if(counter == 0) {
                // If the counter is equal to 0, that means we're looking at the first node in 
                // the current k sublist. This node will end up being the last node in this 
                // sublist, so no work needs to be done.
                // For [4,3,2,1,5,6,7,8], we set this equal to 1.
                currentKSubList.lastOfThisK = currentNode;
                prevNode = currentNode;
                currentNode = currentNode->next;
            }
            else {
                // Store the next node pointed to by the current node, so we don't lose track 
                // of the rest of the list.
                oldNextNode = currentNode->next;
                // Current node's next ptr has to point to the previous node for the reversal.
                currentNode->next = prevNode;
                // The currentNode will be the prevNode in the next iteration, so update that now.
                prevNode = currentNode;
                // We iterate to the next node in the list.
                currentNode = oldNextNode;
            }
            counter++;
        }
        // This will either point to nullptr or the first node of the next k elements that have 
        // yet to be reversed. In the while loop back in our reverseKGroup() function, we correct 
        // which node this should actually point to, but we do this here to avoid a LeetCode 
        // heap-use-after-free error. In other words, for [4,3,2,1,5,6,7,8], we set 1's next 
        // pointer to 5, but we'll fix that in the while loop by making it point to 8 eventually.
        currentKSubList.lastOfThisK->next = currentNode;
        // For [4,3,2,1,5,6,7,8], we set this equal to 4.
        currentKSubList.firstOfThisK = prevNode;
        // For [4,3,2,1,5,6,7,8], we set this equal to 5.
        currentKSubList.firstOfNextK = currentNode;
        // We want to check this counter in reverseKGroup() to see if we actually reversed k 
        // elements, if not, we want to undo the reversal. (This is wasted work and ideally we 
        // would want to somehow check if there's k elements to reverse at the end of the list 
        // before we reverse or somehow swap the nodes without actually mutating the list)
        currentKSubList.count = counter;

        return currentKSubList;
    }
};