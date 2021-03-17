//
//  main.cpp
//  Two Sum
//
//  Created by Jason Lai on 10/23/19.
//  Copyright © 2019 Jason Lai. All rights reserved.
//

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> seen_before;
        vector<int> sum;
        
        for(int i = 0; i < nums.size(); i++) {
            // If first element, put it in hash table
            if(seen_before.empty()) {
                seen_before[nums[i]] = i;
            }
            // Else, see if pairing element is in hash table
            else {
                std::unordered_map<int, int>::const_iterator temp = seen_before.find(target-nums[i]);
                // If element exists, store it in vector and break
                if(temp != seen_before.end()) {
                    sum.push_back(temp->second);
                    sum.push_back(i);
                    break;
                }
                // Else store element in hash table
                else {
                    seen_before[nums[i]] = i;
                }
            }
        }
        
        return sum;
    }
};
