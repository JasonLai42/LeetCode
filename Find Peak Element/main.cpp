// Question asked by Hive and Nordstrom

#include <vector>

using namespace std;

class Solution {
public:
    
    int find_peak_helper(int left, int right, vector<int> nums) {
        // Modified Binary Search
        if(right > left) {
            // Calculate the midpoint using the left and right bounds
            int mid = left + (right - left) / 2;

            // For the case of nums.size() == 2 e.g. [2, 1] or [1, 2] in which case our initial mid will be 0 (we should never be at
            // the edge of the array in this if block)
            // If mid is 0, we can access mid - 1 because of seg fault
            if(mid == 0) {
                // If the right element is less return this number
                if(nums[mid + 1] < nums[mid])
                    return mid;
                // Else the other number is definitely the peak
                else 
                    return find_peak_helper(mid + 1, right, nums);
            }
            // Standard check for left and right neighbors
            else if(nums[mid - 1] < nums[mid] && nums[mid + 1] < nums[mid])
                return mid;
            // If left is greater, guaranteed peak on left side
            else if(nums[mid - 1] > nums[mid])
                return find_peak_helper(left, mid - 1, nums);
            // If right is greater, guaranteed peak on right side
            else
                return find_peak_helper(mid + 1, right, nums);
        }
        
        // Since we increment/decrement left/right by 1, we reach this return statement if left == right, which is the edge of 
        // the array and guaranteed to be a peak (according to my algo)
        return left;
    }
    
    int findPeakElement(vector<int>& nums) {
        return find_peak_helper(0, nums.size() - 1, nums);
    }
};