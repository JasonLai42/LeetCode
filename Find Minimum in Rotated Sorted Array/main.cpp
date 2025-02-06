/* Time Complexity: O(logn)
 * Space Complexity: O(1)
 */
class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0;
        int r = nums.size() - 1;

        // Perform recursive binary search
        return binarySearchHelper(nums, l, r);
    }

    int binarySearchHelper(vector<int>& nums, int l, int r) {
        // Calculate the midpoint
        int mid = l + ((r - l) / 2);

        // If we've reach either end of the array, it means this array hasn't rotated (if mid is 0) or it's only been 
        // rotated once (mid is nums.size()-1) meaning our minimum element is either at the right end or left end 
        // of the array - well sort of
        // Because of funky math with calculating the mid point we might be next to the minimum element but not exactly 
        // on it as in the case of [5, 1, 2, 3, 4] - mid eventually reaches 0, but the element at index 0 is 5 which is 
        // not our minimum so we have to do some hacky fix so that we get the minimum
        if(mid == 0 || mid == nums.size()-1) {
            // This is the hacky fix to ensure we get the minimum element. If we're at either end of the array, check if 
            // its adjacent element is less than it
            if(nums.size() > 1) {
                if(mid == 0) {
                    return min(nums[0], nums[1]);
                }
                if(mid == nums.size()-1) {
                    return min(nums[nums.size()-1], nums[nums.size()-2]);
                }
            }
            // Array only has one element so that is automatically our minimum element
            else {
                return nums[mid];
            }
        }

        // If this element is sandwiched between element greater than it, then it's our minimum element
        if(nums[mid-1] > nums[mid] && nums[mid+1] > nums[mid]) {
            return nums[mid];
        }
        // Otherwise if the last element in the array is less than this element, then the array has been rotated and 
        // the minimum element is in the upper half
        else if(nums[mid] > nums[nums.size()-1]) {
            return binarySearchHelper(nums, mid+1, r);
        }
        // If the last element in the array is not less than this element, then the minimum element lives in the lower 
        // half
        else {
            return binarySearchHelper(nums, l, mid-1);
        }
    }
};