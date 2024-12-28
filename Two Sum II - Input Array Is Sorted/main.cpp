/* Time Complexity: O(n)
 * Space Complexity: O(1)
 * This is a two pointer approach that works by first initializing a pointer at both ends of the sorted array. Then we 
 * add the values that the two pointers point to and if they add up to target, we're done and we store their indices. 
 * Otherwise, if they don't add up to target, then their sum is either greater than target or less than target. If 
 * they're greater than target, then we decrement the pointer j at the higher end, because effectively we need to 
 * decrease sum of the values at the two pointers to get the sum closer to target, and decrementing j means we will add a 
 * lower value than the previous value that j pointed to thereby decreasing the sum. Alternatively, if the sum is less 
 * than target, then we increment the pointer i at the lower end, because we need to increase the sum of the values at 
 * the two pointers, and incrementing i means we will add a higher value thereby increasing the sum. Eventually we will 
 * encounter a pair of numbers where their sum is target via this approach. The time complexity is O(n) because we 
 * iterate through the array at most once. The space complexity is O(1) because we only use 2 pointers and the return 
 * vector of size 2 in our solution, which are all constant size variables.
 */
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> result;

        int i = 0;
        int j = numbers.size() - 1;
        while(j > i) {
            int sum = numbers[i] + numbers[j];
            if(sum == target) {
                result.push_back(i+1);
                result.push_back(j+1);
                break;
            }
            else if(sum > target) {
                j--;
            }
            else {
                i++;
            }
        }

        return result;
    }
};

/* This is a brute force approach that runs in O(n^2) time, but with O(1) space. Basically, anytime we see a number n 
 * where the difference between it and the target is greater than the number n, then we iterate ahead and see if there's 
 * any subsequent number m that the sum between n and m is target.
 */
// class Solution {
// public:
//     vector<int> twoSum(vector<int>& numbers, int target) {
//         vector<int> result;

//         bool found = false;
//         for(int i = 0; i < numbers.size(); i++) {
//             int difference = target - numbers[i];
//             if(difference >= numbers[i]) {
//                 for(int j = i + 1; j < numbers.size(); j++) {
//                     if(numbers[j] == difference) {
//                         result.push_back(i+1);
//                         result.push_back(j+1);

//                         found = true;
//                         break;
//                     }
//                 }
//             }

//             if(found)
//                 break;
//         }

//         return result;
//     }
// };