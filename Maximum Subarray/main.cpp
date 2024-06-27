/* Approach: Subarrays in this problem have to be composed of elements atomic to each other, 
 * that is, they have to be adjacent or consecutively next to each other. So our approach is 
 * going to leverage some dynamic programming type memoization. We're going to create a DP 
 * array that mirrors the nums array. As we iterate over nums, for each element at index i 
 * (nums[i]), we're going to store the largest possible sum of all subarrays that END with 
 * that element nums[i] in the DP array. To do this, we're going to take advantage of the one 
 * simple fact: every subarray that ends in nums[i], EXCEPT THE ONE THAT IS JUST nums[i] ON 
 * ITS OWN, has to include the element directly preceding nums[i], which is nums[i-1]. And 
 * since according to our approach, we have one rule: to store the largest possible sum of all 
 * subarrays that end in nums[i] for any given i, this also applies to i-1! So, since our DP 
 * array stores the largest sum for subarrays ending in nums[i-1], to find the largest 
 * possible sum for all subarrays ending in nums[i], we simply take the maximum between 
 * nums[i] (this is the sum of the subarray that has nums[i] by itself) and nums[i] + the DP 
 * value for nums[i-1], because the DP value for nums[i-1] is largest sum for all subarrays 
 * ending in nums[i-1], and adding nums[i] to this value will obviously be the largest sum for 
 * all subarrays ending nums[i] (except the subarray we're maximuming against). As we iterate 
 * over nums and populate our DP array, we simply track the largest sum we've seen so far, 
 * then return it.
 */

 /* Time Complexity: O(n)
  * Space Complexity: O(n)
  * The time complexity is linear because we simply iterate over nums once. The space 
  * complexity is linear because we keep a DP array the same size as nums.
  */

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        // Problem says nums will never be empty, but better safe than sorry.
        if(nums.empty()) {
            return 0;
        }

        // Our return value, which we set to the first element in nums because initially, 
        // the largest sum we have is simply the sum of the subarray with just the first 
        // element by itself. This also handles the edge case where nums only has one element, 
        // which means we would just return nums[0] since that's the only possible sum.
        int largestSum = nums[0];

        // Declare our DP array and store our initial largest sum which is simply the first 
        // element as we explained above.
        vector<int> numsDp;
        numsDp.push_back(nums[0]);
        // Iterate over nums and begin storing largest sums for subarrays ending in nums[i].
        for(int i = 1; i < nums.size(); i++) {
            // Store the largest possible sum for all subarrays ending in nums[i]. Read the 
            // approach section at top of file to understand why this works.
            int currSubSum = numsDp[i-1] + nums[i];
            numsDp.push_back(max(currSubSum, nums[i]));

            // Compare our global largest sum to the current largest sum we calculated for 
            // subarrays ending in nums[i].
            largestSum = max(largestSum, numsDp[i]);
        }

        return largestSum;
    }
};