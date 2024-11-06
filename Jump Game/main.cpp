// Time Complexity: O(n), Space Complexity: O(1)
// Peeked a solution - simple greedy algorithm. Basically we want to take as many "multijump" 
// spaces as we can and absorb any spaces from the start of the multijump to the end if they're 
// not larger than the multijump. Just read the code and you'll understand.

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int jumps = 0;

        for(int i = 0; i < nums.size(); i++) {
            if(jumps < 0) {
                return false;
            }
            else if(nums[i] > jumps) {
                jumps = nums[i];
            }
            jumps--;
        }

        return true;
    }
};