class Solution {
public:
    int climbStairs(int n) {
        // Follows Fibonacci basically. It's all about finding the maximum number of 2-steps you 
        // can take in n steps, then expanding these 2-steps into two 1-steps one at a time.
        // n = 1: (1 way)
        // 1
        // n = 2: (2 ways)
        // 2
        // 1 1
        // n = 3: (3 ways)
        // 2 1
        // 1 2
        // 1 1 1
        // n = 4: (5 ways)
        // 2 2
        // 2 1 1
        // 1 2 1
        // 1 1 2
        // 1 1 1 1
        // n = 5: (8 ways)
        // 2 2 1
        // 2 1 2
        // 1 2 2
        // 2 1 1 1
        // 1 2 1 1
        // 1 1 2 1
        // 1 1 1 2
        // 1 1 1 1 1

        // Fibonacci really starts at n = 2 (after n = 0 and n = 1)
        int fibN = n + 1;
        // Store the fibonacci sequence value at each i until we reach n.
        int stepArray[fibN];
        // The two starting values for fibonacci at n = 0 and n = 1 are both 1.
        stepArray[0] = 1;
        // n is guaranteed to be >= 1
        stepArray[1] = 1;
        // If n > 1, then we can start calculating fibonacci i.e. F_n = F_n-1 + F_n-2.
        if(n > 1) {
            for(int i = 2; i < fibN; i++) {
                stepArray[i] = stepArray[i - 1] + stepArray[i - 2];
            }
        }

        // Last value in the array is the number of ways we can make n steps.
        return stepArray[n];
    }
};