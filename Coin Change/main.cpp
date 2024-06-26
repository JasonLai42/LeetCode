/* Approach: While I came up with my own approach (commented out below) that comes close to 
 * this one in performance, I didn't like it because it wasn't elegant and this one is a 
 * posted solution that I found to be cleaner. My approach focused on using a current value we 
 * previously calculated to calculate other "future" values, whereas this approach uses past 
 * values we calculated to calculate the current value (both use memoized data, but the 
 * approach is kind of the opposite of each other). Anyways, in this solution we're going to 
 * keep a DP array numbered from 0 to amount, where amount is the sum we want to reach with 
 * the coins. Each index of this array is basically a sub-amount that is less than amount, and 
 * for each sub-amount from 0 to amount, we're going to store the minimum number of coins it 
 * takes to sum to this sub-amount in our DP array at the index represented by sub-amount. 
 * Intuitively for each denomination in our coins array, the sub-amount that equals that 
 * denomination will have a minimum number of coins equal to 1 because it only takes 1 coin to 
 * make up that sub-amount. Those are our "starting" past values that we calculate and use to 
 * calculate the minimum number of coins for the next sub-amounts.
 *
 * In practice, we calculate the minimum number of coins for each sub-amount by iterating 
 * through the coins array and subtracting each coin denomination from the sub-amount. This 
 * difference is possibly a previous sub-amount (so long as it isn't <0) that we calculated 
 * the minimum number of coins for and memoized, so leveraging this, we can then simply add 1 
 * additional coin to this previous minimum and we would have the minimum number of coins for 
 * this current sub-amount USING THIS COIN. I make the distinction that this is a minimum 
 * specific for THIS COIN, because as we calculate other previous sub-amounts for each 
 * denomination by also subtracting them from the current sub-amount, those coins may have 
 * different minimums stored in their previous sub-amount cells. So we would need to find 
 * which denomination gives us the absolute minimum number of coins need to sum to this 
 * current sub-amount.
 */

 /* Time Complexity: O(nk) where n is amount and k is the number of coin denominations
  * Space Complexity: O(n)
  * The time complexity is O(nk) because in the worst case, we have to calculate the 
  * difference for every coin denomination for every sub-amount in our DP array. This means 
  * for every cell in our DP array we have to iterate through the coins array. We have some 
  * safeguards to short circuit the nested loop if a denomination is so big that the current 
  * sub-amount can't possibly use this denomination, but other than that, we're still running 
  * O(nk). The space complexity is O(n) because we have to use a DP array the size of amount 
  * (plus 1) to memoize the minimum number of coins for each sub-amount.
  */

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // Edge cases.
        if(amount <= 0) {
            return 0;
        }

        // Our DP array; we initialize everything to INT_MAX so we can take the minimum 
        // against these stored values as we iterate through this array.
        vector<int> coinDpArray(amount+1, INT_MAX);
        // We have the DP array one size larger than amount and set the first element 0 to 0 
        // because it takes 0 coins to make up the sub-amount 0. Then as we reach the 
        // sub-amounts that are equal to our denominations in the coins array, we can use 
        // this 0 value as a memoized past minimum number of coins added together with 1 
        // to be the minimum number of coins to sum to those sub-amounts. This is to ensure 
        // that our algorithm is seamless and doesn't need any funky preprocessing for 
        // populating the sub-amounts that are equal to denominations.
        coinDpArray[0] = 0;

        // Sort coins smallest to largest for short circuiting purposes.
        sort(coins.begin(), coins.end());

        // Iterate through the DP array and begin populating minimum numbers of coins for 
        // each sub-amount.
        for(int currAmt = 1; currAmt <= amount; currAmt++) {
            // Iterate through the coins array and find the minimum numbers of coins for 
            // the current sub-amount using each coin and then store the smallest one.
            for(int j = 0; j < coins.size(); j++) {
                // Get the previous sub-amount that is equal to the current sub-amount minus 
                // the current coin coins[j].
                int prevAmt = currAmt - coins[j];
                // If this previous sub-amount is found to be less than 0, it means the 
                // current sub-amount can't use the current coins[j] (it's too big). So we 
                // break because we sorted the coins array smallest to largest, so if the 
                // current coin is too big, then the rest are also too big so no need to 
                // check them.
                if(prevAmt < 0)
                    break;

                // If the previous sub-amount is equal to INT_MAX, then that means that the 
                // previous sub-amount wasn't able to be summed to using the coins we have, 
                // so that means the current sub-amount can't be summed to either.
                if(coinDpArray[prevAmt] != INT_MAX)
                    // Otherwise, we take minimum of the previous sub-amount's minimum plus 1 
                    // and the current stored value for the current sub-amount (which could 
                    // either be INT_MAX or another coin denomination's minimum number of 
                    // coins)
                    coinDpArray[currAmt] = min(coinDpArray[currAmt], coinDpArray[prevAmt]+1);
            }
        }

        // If the minimum number of coins stored at amount is INT_MAX, then there wasn't a 
        // way to sum to this amount with the coins we have, so return -1. Otherwise, return 
        // the stored value. Notice that this doesn't handle the edge case where the 
        // minimum number of coins is equal to INT_MAX such as in the case where amount is 
        // INT_MAX and the only coin we have is penny (1). My original solution does handle 
        // this case however.
        return coinDpArray[amount] != INT_MAX ? coinDpArray[amount] : -1;
    }
};

/* Below is my original solution that works but is not elegant and sort of inefficient.
 * The heart of the dp solution is there, but I have too much extra computation happening
 * like unnecessary if conditions, operations, and checking coins that won't work.
 */

// class Solution {
// public:
//     int coinChange(vector<int>& coins, int amount) {
//         if(amount <= 0 || coins.empty()) {
//             return 0;
//         }
//         vector<int> coinDpArray(amount, -1);
//         vector<int> prunedCoins;

//         for(int i = 0; i < coins.size(); i++) {
//             if(coins[i] == amount) {
//                 return 1;
//             }
//             else if(coins[i] > amount) {
//                 continue;
//             }

//             coinDpArray[amount - coins[i]] = 1;
//             prunedCoins.push_back(coins[i]);
//         }

//         for(int i = amount-1; i >= 0; i--) {
//             if(coinDpArray[i] != -1) {
//                 for(int j = 0; j < prunedCoins.size(); j++) {
//                     int nextDiff = i - prunedCoins[j];
//                     if(nextDiff >= 0) {
//                         if(coinDpArray[nextDiff] > coinDpArray[i] + 1 
//                             || coinDpArray[nextDiff] == -1) {
//                             coinDpArray[nextDiff] = coinDpArray[i] + 1;
//                         }
//                     }
//                 }
//             }
//         }

//         return coinDpArray[0];
//     }
// };