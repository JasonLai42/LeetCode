#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int> k_nums;
        // Our result vector will contain k elements, so reserve an area of memory of size k
        k_nums.reserve(k);
        
        // First count the number of instances of each unique num
        unordered_map<int, int> num_to_count;
        // Get the count of the num(s) with the most instances
        int highest_count = INT_MIN;
        for(int i = 0; i < nums.size(); i++) {
            num_to_count[nums[i]] += 1;
            highest_count = max(highest_count, num_to_count[nums[i]]);
        }
        
        // Now iterate through num_to_count, and group the nums with the same counts
        unordered_map<int, vector<int>> count_to_nums;
        for(auto it : num_to_count) {
            count_to_nums[it.second].push_back(it.first);
        }
        
        // Starting from the highest count, insert the group of nums for this count if it exists in count_to_nums
        // We then decrement highest_count to get the group of the next most common nums
        while(k_nums.size() != k && highest_count > 0) {
            if(count_to_nums.find(highest_count) != count_to_nums.end()) { 
                // Since the solution is unique, we know that we can insert the entire vector for a given count, because 
                // If the remaining number of nums we need to reach k is less than the group size for this count, we 
                // would have to choose which nums are inserted, resulting in multiple solutions
                k_nums.insert(k_nums.end(), 
                              count_to_nums[highest_count].begin(), 
                              count_to_nums[highest_count].end());
            }
            highest_count--;
        }
        
        return k_nums;
    }
};