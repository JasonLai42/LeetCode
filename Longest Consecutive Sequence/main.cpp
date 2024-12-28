/* Time Complexity: Supposedly O(n)
 * Space Complexity: O(n)
 * Posted solution suggests this is linear time complexity - basically we store all the numbers in an unordered set and 
 * when we come across a number that is the start of a run of consecutive numbers i.e. the number - 1 is not present in 
 * the set, then we iterate through the set, looking for all numbers that come after it consecutively, thereby 
 * constructing a run of consecutive numbers. We then store the length of longest run we've seen thus far. This is linear 
 * because we only iterate through the set if we encounter the start of a run, so we look at each number in the set 
 * exactly once, which would be O(n). This means we loop 3 times total in this algorithm so O(3n) becomes ~O(n). Space is 
 * O(n) because we use an unordered_set.
 */
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int result = 0;
        if(nums.size() == 0) {
            return result;
        }
        
        unordered_set<int> set_of_nums;
        for(auto num : nums) {
            set_of_nums.insert(num);
        }
        for(auto num : nums) {
            if(set_of_nums.find(num-1) == set_of_nums.end()) {
                int currentNum = num;
                int currentRun = 1;
                while(set_of_nums.find(currentNum+1) != set_of_nums.end()) {
                    currentRun++;
                    currentNum++;
                }
                result = max(result, currentRun);
            }
        }

        return result;
    }
};

/* Time Complexity: O(nlogn)
 * Space Complexity: O(1)
 * Even though this works, this is doesn't pass because it doesn't run in O(n) time since we sort. The approach is just 
 * we sort, then count the length of runs of consecutive numbers and store the length of the longest run we've seen as we 
 * go.
 */
// class Solution {
// public:
//     int longestConsecutive(vector<int>& nums) {
//         int result = 0;
//         if(nums.size() == 0) {
//             return result;
//         }

//         sort(nums.begin(), nums.end());

//         int current = 1;
//         for(int i = 1; i < nums.size(); i++) {
//             if(nums[i] != nums[i-1]) {
//                 if(nums[i] == nums[i-1] + 1) {
//                     current++;
//                 }
//                 else {
//                     result = max(result, current);
//                     current = 1;
//                 }
//             }
//         }

//         return max(result, current);
//     }
// };