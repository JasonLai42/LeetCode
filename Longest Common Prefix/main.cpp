#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        
        // If empty, return empty string
        if(strs.empty()) {
            return "";
        }
        
        // If only one string, longest prefix is that entire string
        if(strs.size() == 1) {
            return strs.back();
        }
        
        // Initialize to empty string (if no common prefix, return empty string)
        string prefix = "";
        
        bool found_mismatch = false;
        
        // i tracks what index of each string we are now checking for matching character in prefix
        int i = 0;
        while(!found_mismatch) {
            // Iterate through all strings in vector except the last string, because we compare the prefix of last 
            // string to all other strings
            for(vector<string>::const_iterator it = strs.begin(); it != strs.end() - 1; it++) {
                if(i < it->size()) {
                    // Found mismatch between two strings at index i
                    if(strs.back()[i] != (*it)[i]) {
                        found_mismatch = true;
                        break;
                    }
                }
                // We've reached the end of one of the strings, so the entire said string is the longest common prefix
                // Can no longer compare any characters of other strings to this string, so we break
                else {
                    found_mismatch = true;
                    break;
                }
            }
            
            if(found_mismatch)
                break;
            
            // If character of last string is common to all strings at index i, we add it to prefix
            prefix += strs.back()[i];
            i++;
        }
        
        return prefix;
    }
};