class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // Our return value.
        int maxProfit = 0;

        // Edge cases: if there's 0 elements, no data to work on, if there's 1 element we can 
        // only buy but not sell, so no profit.
        if(prices.size() < 2) {
            return maxProfit;
        }

        // Basic algorithm: we iterate through the prices per day and for each day, we calculate 
        // the maximum amount of profit we could possibly make by selling on that day at that day's 
        // price. In order to do this, we need the minimum buying price that we've seen prior to 
        // that day, hence the minBuyPrice variable. We set minBuyPrice to prices[0] initially, 
        // because on the first day we can only buy (can't sell), so it follows that we should 
        // compare any potential buying prices after the first day should be compared to day 1's 
        // price.
        int minBuyPrice = prices[0];
        for(int i = 1; i < prices.size(); i++) {
            // Calculate the maximum possible profit for day i.
            int profit = prices[i] - minBuyPrice;
            // Compare day i's maximum possible profit with the maximum profit we've seen so far.
            if(profit > maxProfit) {
                maxProfit = profit;
            }
            // Get a new smallest buying price if day i's price is less than minBuyPrice. We have 
            // else here because, if profit was greater than maxProfit in the if condition above, 
            // then that means price[i] was greater than minBuyPrice. So if profit isn't greater 
            // than maxProfit, then prices[i] was either less than or equal to minBuyPrice, but 
            // we disregard the equal to case.
            else if(prices[i] < minBuyPrice) {
                minBuyPrice = prices[i];
            }
        }

        return maxProfit;
    }
};