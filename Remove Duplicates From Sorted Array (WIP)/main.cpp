#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.empty()) {
            return 0;
        }
        
        int curr_num = nums[0];
        bool first_elem = true;
        
        // Store the indices of elements to remove from nums
        vector<int> elem_to_remove;
        // Each index we add to elem_to_remove will cause the nums array to shrink by 1 when we 
        // erase, so we need the indices to be substracted by the number of elements deleted 
        // before it to get the right index to delete
        int offset = 0;
        
        for(int i = 1; i < nums.size(); i++) {
            if(nums[i] == curr_num) {
                elem_to_remove.push_back(i - offset);
                offset++;
            }
            else {
                curr_num = nums[i];
            }
        }
        
        // The given solution doesn't remove duplicates????
        // But mine does sooooo
        for(int i = 0; i < elem_to_remove.size(); i++) {
            nums.erase(nums.begin() + elem_to_remove[i]);
        }
        
        return nums.size();
    }
};