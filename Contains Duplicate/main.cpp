class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        // Unordered set to store the numbers we've encountered so far in nums
        unordered_set<int> seenBefore;

        // Iterate through nums and check if we've seen nums[i] before
        // If we have, return true
        // Otherwise, add nums[i] to our unordered set and continue until we 
        // either find a duplicate or reach the end of nums
        for(int i = 0; i < nums.size(); i++) {
            if(seenBefore.find(nums[i]) == seenBefore.end()) {
                seenBefore.insert(nums[i]);
            }
            else {
                return true;
            }
        }

        // Return false, meaning all the numbers in nums are distinct
        return false;
    }
};