#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        int longest = 0;
        
        // Stack to track the indices of unmatched left parentheses
        // The stack ensures that the order of parentheses we get from the stack is always the most recent 
        // to oldest. This is so we follow the rule of matching most recent left parentheses first.
        stack<int> left_par;
        
        // If we don't have any unmatched parentheses, then the longest valid string so far is from the most recent 
        // right parenthese we encountered to the start index (which is the index where the current longest valid string 
        // started)
        int start_index = -1;
        for(int i = 0; i < s.size(); i++) {
            if(s[i] == '(') {
                left_par.push(i);
            }
            else if(s[i] == ')') {
                // If we encountered a right parenthese and there's no left parentheses to match with it, then we've 
                // reached the limit for the longest valid string up to this point. We assign a new start index and 
                // continue
                if(left_par.empty()) {
                    start_index = i;
                    continue;
                }
                else {
                    // Match the most recent left parenthese (we pop it off the stack)
                    left_par.pop();
                    // If there aren't any unmatched left parentheses, then the length of this valid string is from i to 
                    // the start index
                    if(left_par.empty()) {
                        longest = max(longest, i - start_index);
                    }
                    // If there are unmatched parentheses, then the length of this valid string is from i to the most 
                    // recent unmatched left parenthese
                    else {
                        longest = max(longest, i - left_par.top());
                    }
                }
            }
        }
        
        return longest;
    }
};