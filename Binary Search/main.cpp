class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0;
        int r = nums.size() - 1;

        // Perform recursive binary search
        return binarySearch(nums, target, l, r);
    }

    int binarySearch(vector<int>& nums, int target, int l, int r) {
        // Base case, if left is greater than right, then we've exhausted the entire array and have not found target
        if(l > r) {
            return -1;
        }

        // Calculate the midpoint
        int mid = l + ((r - l) / 2);

        // Target found
        if(nums[mid] == target) {
            return mid;
        }
        // Target not found; current num is less than target so search the upper half
        else if(nums[mid] < target) {
            // Remember that we have to add 1 or subtract 1 from mid to shrink search area always
            return binarySearch(nums, target, mid+1, r);
        }
        // Target not found; current num is greater than target so search the lower half
        else {
            return binarySearch(nums, target, l, mid-1);
        }
    }
};