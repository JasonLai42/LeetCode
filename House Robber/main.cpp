// Time Complexity: O(n), Space Complexity: O(n)
// The approach here is that we create a dpArray and we store the maximum possible amount 
// we can rob for each house on the street if we were to rob that house. The trick is we can't 
// include the house directly preceding the current house because of the adjacency rule, but 
// every house before that one is fair game. To include every house before the current house, 
// we add the max of the house at i-2 (2 lots before the current house) and the house at i-3 (3 
// lots before the current house).
// For example: 
// [2,7,9,3,1] results in 2 + 9 + 1 = 12
// [7,2,3,9,1] results in 7 + 9 = 16
// So we need to account for the houses at i-2 and i-3.

class Solution {
public:
    int rob(vector<int>& nums) {
        // Edge case
        if(nums.size() == 1) {
            return nums[0];
        }
        // Initialize our dpArray
        vector<int> dpArray(nums.size()+2);
        // To make our jobs easier, getting i-2 and i-3, we're going to add 2 additional 
        // elements to our dpArray at the beginning to represent dummy houses with no money.
        dpArray[0] = 0;
        dpArray[1] = 0;
        // We'll start counting houses with the first house (we're guaranteed there's at least 
        // 2 houses because of the edge case check)
        dpArray[2] = nums[0];


        // Start adding up max possible amounts
        for(int i = 3; i < nums.size()+2; i++) {
            dpArray[i] = nums[i-2] + max(dpArray[i-3], dpArray[i-2]);
        }

        // The last two elements represent two possible maximum amounts, so take one or the other
        return max(dpArray[nums.size()], dpArray[nums.size()+1]);
    }
};