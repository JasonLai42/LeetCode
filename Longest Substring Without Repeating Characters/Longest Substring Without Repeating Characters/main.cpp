//
//  main.cpp
//  Longest Substring Without Repeating Characters
//
//  Created by Jason Lai on 10/23/19.
//  Copyright © 2019 Jason Lai. All rights reserved.
//

#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int final_max = 0;
        
        int curr_max = 0;
        int last_dup = 0;
        unordered_map<char, int> seen_before;
        for(int i = 0; i < s.length(); i++) {
            // If this character hasn't been seen before, increment current max
            if(seen_before.find(s[i]) == seen_before.end()) {
                curr_max++;
            }
            else {
                // Set last_dup to latest "last seen" instance of most recently found duplicate
                if(last_dup < seen_before[s[i]]) {
                    last_dup = seen_before[s[i]];
                }
                // Restart the current max count from the most recent duplicate
                curr_max = (i+1) - last_dup;
            }
            
            // If the current max is greater than the final max, set the new final max
            final_max = max(final_max, curr_max);
            // Set the index of where this character was last seen
            seen_before[s[i]] = i + 1;
        }
        
        return final_max;
    }
};
