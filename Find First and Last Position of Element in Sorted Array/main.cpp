#include <vector>

using namespace std;

class Solution {
public:
    int searchRangeStart(vector<int> nums, int target, int start, int end) {
        if(end >= start) {
            int mid = start + (end - start) / 2;

            if(nums[mid] == target) {
                if(mid == 0) {
                    return mid;
                }
                else if(mid > 0 && nums[mid - 1] != target) {
                    return mid;
                }
                else {
                    return searchRangeStart(nums, target, start, mid - 1);
                }
            }
            else if(nums[mid] > target) {
                return searchRangeStart(nums, target, start, mid - 1);
            }
            else {
                return searchRangeStart(nums, target, mid + 1, end);
            }
        }
        
        return -1;
    }
    
    int searchRangeEnd(vector<int> nums, int target, int start, int end) {
        if(end >= start) {
            int mid = start + (end - start) / 2;

            if(nums[mid] == target) {
                if(mid == nums.size() - 1) {
                    return mid;
                }
                else if(mid < nums.size() - 1 && nums[mid + 1] != target) {
                    return mid;
                }
                else {
                    return searchRangeEnd(nums, target, mid + 1, end);
                }
            }
            else if(nums[mid] > target) {
                return searchRangeEnd(nums, target, start, mid - 1);
            }
            else {
                return searchRangeEnd(nums, target, mid + 1, end);
            }
        }
        
        return -1;
    }
    
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> indices;
        
        indices.push_back(searchRangeStart(nums, target, 0, nums.size() - 1));
        indices.push_back(searchRangeEnd(nums, target, 0, nums.size() - 1));
        
        return indices;
    }
};