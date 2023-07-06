class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        // Edge case
        if(nums.empty()) {
            return;
        }

        // The assignment is to move all zeroes to the right, but we can also think of this 
        // as moving all non-zero integers to the left
        // i in this case looks for non-zero integers as we iterate through nums, while 
        // zeroIndex holds the index of the number we need to replace with the next non-zero 
        // integer we encounter as we shift all the integers to the left
        int zeroIndex = 0;
        for(int i = 0; i < nums.size(); i++) {
            // If we encounter a non-zero integer, shift it to the left at zeroIndex
            // Otherwise, do nothing, as this means we encountered a 0, and we don't want 
            // any zeroes on the left as we group non-zero integers on the left
            if(nums[i] != 0) {
                nums[zeroIndex] = nums[i];
                zeroIndex++;
            }
        }

        // After we finish iterating through the loop above, all we have to do now is change 
        // all elements in nums from zeroIndex to the end to 0, since we know that by this 
        // point, zeroIndex stores the index of the element right after the last non-zero 
        // integer in nums after we shifted them all over to the left (we know this because 
        // zeroIndex only gets incremented when we encounter a non-zero integer, so by the 
        // end of the for loop, it should equal the number of non-zero integers in nums)
        while(zeroIndex < nums.size()) {
            nums[zeroIndex] = 0;
            zeroIndex++;
        }

        return;
    }
};