#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        
        int start_pos;
        int end_pos;
        
        // Start from size of entire string, then decrement by 1 to get decreasing 
        // size substrings
        for(int i = s.size(); i > 0; i--) {
            // Number of possible substrings for the given size we have currently
            int num_pos = s.size() - i;
            start_pos = 0;
            end_pos = i - 1;
            int mid_point = i / 2;
            
            bool pal_found = false;
            while(num_pos >= 0) {
                pal_found = true;
                
                // Process palindrome substring from both sides
                // Different behavior depending on even or odd size substring
                if(i % 2 == 0) {
                    for(int j = start_pos, k = end_pos; (j < mid_point && k >= mid_point); j++, k--) {
                        if(s[j] != s[k]) {
                            pal_found = false;
                            break;
                        }
                    }
                }
                else {
                    for(int j = start_pos, k = end_pos; (j < mid_point && k >= mid_point) ; j++, k--) {
                        if(s[j] != s[k]) {
                            pal_found = false;
                            break;
                        }
                    } 
                }
                
                if(pal_found)
                    break;
                
                num_pos--;
                // Shift the substring to the right
                start_pos++;
                end_pos++;
                mid_point++;
            }
            
            if(pal_found)
                break;
        }
        
        return s.substr(start_pos, (end_pos - start_pos) + 1);
    }
};