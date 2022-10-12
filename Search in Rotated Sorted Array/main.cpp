class Solution {
public:
    int search(vector<int>& nums, int target) {
        if(nums.size() > 0) {
            // Some terminology here: "displaced array" means like if we have a rotated 
            // array [4,5,6,7,0,1,2], then [4,5,6,7] is the displaced array.
            // Checks whether target is in the displaced subarray or not.
            bool isInDisplaced = target > nums[nums.size()-1];
            return binarySearchInRotatedArray(nums, target, isInDisplaced, 0, nums.size()-1);
        }
        else {
            return -1;
        }
    }

    int binarySearchInRotatedArray(
        vector<int>&nums, 
        int target, 
        int isInDisplaced, 
        int l, 
        int r
        ) {
        if(r >= l) {
            int mid = l + ((r - l) / 2);
            // Checks whether nums[mid] is in displaced subarray or not.
            bool midIsInDisplaced = nums[mid] > nums[nums.size()-1];

            if(nums[mid] == target) {
                return mid;
            }
            else if(nums[mid] < target) {
                // If num[mid] is greater than the num at the end of array, we're in the 
                // displaced subarray, so we search the right, because target > nums[mid].
                // We don't have to worry about cases like 22222222312 or 31222222222 where we 
                // can't tell if we're in the displaced subarray or not because all values are 
                // distinct.
                if(midIsInDisplaced) {
                    return binarySearchInRotatedArray(
                        nums, target, isInDisplaced, mid+1, r);
                }
                // If num[mid] is less than the num at the end of the array, we're not in the 
                // displaced subarray, and since target > nums[mid], target could be left or 
                // right.
                else {
                    // If target is in the displaced subarray we look left
                    if(isInDisplaced) {
                        return binarySearchInRotatedArray(
                            nums, target, isInDisplaced, l, mid-1);
                    }
                    // Otherwise, look right
                    else {
                        return binarySearchInRotatedArray(
                            nums, target, isInDisplaced, mid+1, r);
                    }
                }
            }
            else {
                // Same deal as above, except now that target < nums[mid], if we're in the 
                // displaced subarray, then target could be left or right.
                if(midIsInDisplaced) {
                    // If target is in the displaced subarray we look left
                    if(isInDisplaced) {
                        return binarySearchInRotatedArray(
                            nums, target, isInDisplaced, l, mid-1);
                    }
                    // Otherwise, look right
                    else {
                        return binarySearchInRotatedArray(
                            nums, target, isInDisplaced, mid+1, r);
                    }
                }
                // Since we're not in the displaced subarray, the value has to be left, 
                // because there are only values greater than nums[mid] to the right.
                else {
                    return binarySearchInRotatedArray(
                        nums, target, isInDisplaced, l, mid-1);
                }
            }
        }

        // Didn't find it.
        return -1;
    }

    /*int search(vector<int>& nums, int target) {
        if(nums.size() > 0) {
            int endOfDisplaced = findEndOfDisplacedArrayBinarySearch(nums, 0, nums.size()-1);
            // We enter this block if nums.size() == 1, because we want to avoid the 
            // endOfDisplaced+1 in the else block, because for arrays with only 1 element 
            // we get incorrect -1 output.
            if(target > nums[nums.size()-1]) {
                return binarySearch(nums, target, 0, endOfDisplaced);
            }
            else {
                return binarySearch(nums, target, endOfDisplaced+1, nums.size()-1);
            }
        }
        else {
            return -1;
        }
    }

    int findEndOfDisplacedArrayBinarySearch(vector<int>& nums, int l, int r) {
        if(r > l) {
            int mid = l + ((r - l) / 2);
            // Checks whether nums[mid] is in displaced subarray or not.
            bool midIsInDisplaced = nums[mid] > nums[nums.size()-1];

            if(nums[mid] > nums[mid+1]) {
                return mid;
            }
            
            // If nums[mid] is in the displaced array, we look right.
            if(midIsInDisplaced) {
                return findEndOfDisplacedArrayBinarySearch(nums, mid+1, r);
            }
            // If nums[mid] isn't in the displaced array, we look left.
            else {
                return findEndOfDisplacedArrayBinarySearch(nums, l, mid-1);
            }
        }

        // This is when there's only one element in the array.
        return 0;
    }

    int binarySearch(vector<int>& nums, int target, int l, int r) {
        if(r >= l) {
            int mid = l + ((r - l) / 2);

            if(nums[mid] == target) {
                return mid;
            }
            // If nums[mid] is less than target, look right.
            else if(nums[mid] < target) {
                return binarySearch(nums, target, mid+1, r);
            }
            // If nums[mid] is greater than target, look left;
            else {
                return binarySearch(nums, target, l, mid-1);
            }
        }

        // We didn't find target.
        return -1;
    }*/
};