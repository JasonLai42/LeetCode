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

class Solution1 {
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
                curr_max = i - last_dup;
            }
            
            // If the current max is greater than the final max, set the new final max
            final_max = max(final_max, curr_max);
            // Set the index of where this character was last seen
            seen_before[s[i]] = i;
        }
        
        return final_max;
    }
};

class Solution2 {
public:
    int lengthOfLongestSubstring(string s) {
        // Store the index at which this character was last seen in the string i.e. the highest index in s that this char was at
        unordered_map<char, int> last_seen_index;
        
        // The length of the longest substring thus far
        int longest = 0;
        // Store the index in s where the substring we are currently computing starts
        int first = 0;
        
        for(int i = 0; i < s.length(); i++) {
            auto temp = last_seen_index.find(s[i]);
            // If we've seen this char before, "truncate" this char and everything before it in the last substring we were computing
            // and set first as the index of the character after it (the new start of the substring we are currently computing)
            if(temp != last_seen_index.end() && temp->second >= first) {
                first = temp->second + 1;
                temp->second = i;
            }
            // If we haven't seen this char before, hash it and store its index in s
            else {
                last_seen_index[s[i]] = i;
            }
            
            // See if the substring we are currently computing has overtaken the previous longest substring
            if((i - first + 1) > longest) {
                longest = i - first + 1;
            }
        }

        return longest;
    }
};