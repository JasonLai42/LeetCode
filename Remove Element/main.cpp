#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        // Store indices of instances of val in array
        vector<int> elem_to_remove;
        // When we erase elements from nums as we iterate over it, the size shrinks, so the 
        // indices of the elements will shift left by 1; offset will account for this
        int offset = 0;
        
        // Find the indices of all instances of val
        for(int i = 0; i < nums.size(); i++) {
            if(nums[i] == val) {
                elem_to_remove.push_back(i - offset);
                offset++;
            }
        }
        
        // Remove the elements from the array
        for(int i = 0; i < elem_to_remove.size(); i++) {
            nums.erase(nums.begin() + elem_to_remove[i]);
        }
        
        // Return the length of the new array
        return nums.size();
    }
};