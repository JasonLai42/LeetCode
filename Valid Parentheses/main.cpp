#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        // For every unmatched parenthese so far, we want to push its closing parenthese
        // onto the stack to maintain the order
        stack<char> paren_order;
        
        for(int i = 0; i < s.length(); i++) {
            switch(s[i]) {
                case '(': 
                    paren_order.push(')');
                    break;
                case '{':
                    paren_order.push('}');
                    break;
                case '[':
                    paren_order.push(']');
                    break;
                default:
                    // If we encounter anything other than an open parenthese, check it with 
                    // the expected closing parenthese on the stack
                    // If stack empty(), we have an unmatched closing paren (short circuit)
                    // Otherwise, check if we have a mismatch
                    if(paren_order.empty() || s[i] != paren_order.top()) {
                        return false;
                    }
                    else
                        paren_order.pop();
                        break;
            }
        }
        
        if(!paren_order.empty())
            return false;
        
        return true;
    }
};