/* Approach: Basically, what we want is, for each element at index i in our result array, we 
 * want the product of all numbers at the indices <i and >i (i.e. to the left and right of i) 
 * in the input nums array. So our approach is going to be two-fold: we first traverse the 
 * nums array front-to-back to handle the product of all nums <i for each i, then we traverse 
 * the nums array in reverse back-to-front to handle the product of all nums >i for each i. 
 * That is, on our first pass through the nums array, as we increment i, we're going store a 
 * running product that multiplies all the nums[i] we've encountered so far together. And at 
 * each i, we're going to store this running product into our result array at that index i 
 * (result[i]) BEFORE we multiply the running product by the current nums[i]. This means that 
 * we will ignore nums[i] as we calculate the product at each i and by the time we finish our 
 * first pass, every result[i] will have stored the product of all nums that come before that 
 * i (i.e. the nums at all indices <i), so all we're missing from the products in the result 
 * array are all the nums that come after i (i.e. the nums at all indices >i). To find the 
 * product of all nums at indices >i for each i, we're gonna do that same thing but traverse 
 * the nums array in reverse in order to instead keep a running product of all nums at indices 
 * >i, and for the running product we calculate at each i, we're going to again IGNORE the 
 * current nums[i] until AFTER we store the current running product in the result array - we 
 * do this by multiplying that running product of all nums[>i] with the product of nums[<i] we 
 * currently have stored at result[i] in the result array. By the time we finish our second 
 * pass, every result[i] with have the correct product of all nums at indices <i and >i.
 */

/* Time Complexity: O(n)
 * Space Complexity: O(1)
 * The time complexity is linear here because we simply traverse the nums array twice: once 
 * normally and once in reverse. So we meet the requirement of maintaining an O(n) time 
 * complexity while also not using the division operator. We also meet the extra requirement 
 * of using O(1) extra space complexity, since we only use a single int variable 
 * (runningProduct) outside of the sunk cost space we use for the vector we store our result 
 * in.
 */

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> result;

        // Our running product variable
        int runningProduct = 1;
        // First pass: traverse nums front-to-back and track a running product of all nums at 
        // indices <i for each i
        for(int i = 0; i < nums.size(); i++) {
            // Store the running product into our result array at i - running product at this 
            // point holds the product of all nums at indices <i
            result.push_back(runningProduct);
            // Multiply the running product by nums[i] to store in the next result[i] in the 
            // next iteration of the loop
            runningProduct *= nums[i];
        }

        // Reset running product
        runningProduct = 1;
        // Second pass: traverse nums back-to-front, but this time running product is going to 
        // store the product of all nums at indices >i for each i
        for(int i = nums.size() - 1; i >= 0; i--) {
            // Multiply result[i] by the current running product so that we have nums[<i] * 
            // nums[>i] - which is the answer we want for this i!
            result[i] *= runningProduct;
            // Again, multiply the running product by nums[i] to "store" in the next result[i]
            runningProduct *= nums[i];
        }

        return result;
    }
};