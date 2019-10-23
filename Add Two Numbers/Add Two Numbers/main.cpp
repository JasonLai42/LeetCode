//
//  main.cpp
//  Add Two Numbers
//
//  Created by Jason Lai on 10/23/19.
//  Copyright © 2019 Jason Lai. All rights reserved.
//

#include <iostream>

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* l1Node = l1;
        ListNode* l2Node = l2;
        
        // Find the first value to be stored and any carry
        int sum = l1Node->val + l2Node->val;
        int stored_value = sum % 10;
        int carry = sum / 10;
        
        // Initialize the head of the final sum
        ListNode* l3 = new ListNode(stored_value);
        ListNode* firstNode = l3;
        
        // Find the rest of the values to be stored
        ListNode* temp;
        l1Node = l1Node->next;
        l2Node = l2Node->next;
        while(l1Node != NULL || l2Node != NULL) {
            sum = 0;
            
            if(l1Node != NULL) {
                sum += l1Node->val;
                l1Node = l1Node->next;
            }
            
            if(l2Node != NULL) {
                sum += l2Node->val;
                l2Node = l2Node->next;
            }
            
            sum += carry;
            stored_value = sum % 10;
            carry = sum / 10;
            
            temp = new ListNode(stored_value);
            l3->next = temp;
            l3 = temp;
        }
        
        // If the final sum resulted in a carry, store it
        if(carry > 0) {
            temp = new ListNode(carry);
            l3->next = temp;
            l3 = temp;
        }
        l3->next = NULL;
        
        return firstNode;
    }
};
