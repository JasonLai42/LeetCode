#include <vector>

using namespace std;

class Solution {
public:
    int searchHelper(vector<int> nums, int target, int start, int end) {
        // Normal binary search algo with a couple added conditions
        if(end >= start) {
            int mid = start + (end - start) / 2;
            
            if(nums[mid] == target) {
                return mid;
            }
            else if(nums[mid] > target) {
                // If mid - 1 becomes less than start, we know that means this number wasn't found (we would hit the 
                // return -1) in the array, so we have to return the index where we would insert target, which is 
                // actually the index start itself (target would come before nums[start] in order, so we shift right)
                if(mid - 1 < start) {
                    return start;
                }
                return searchHelper(nums, target, start, mid - 1);
            }
            else {
                // If mid + 1 becomes greater than end, we know that means this number wasn't found (we would hit the 
                // return -1) in the array, so we have to return the index where we would insert target, which is 
                // end + 1 (target would come after nums[end] in order)
                if(mid + 1 > end) {
                    return end + 1;
                }
                return searchHelper(nums, target, mid + 1, end);
            }
        }
        
        // This line should never be hit
        return -1;
    }
    
    int searchInsert(vector<int>& nums, int target) {
        return searchHelper(nums, target, 0, nums.size() - 1);
    }
};