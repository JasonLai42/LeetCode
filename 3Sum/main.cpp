class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        // Make our lives easier, lets use set to remove duplicate triplets - O(log(n)) insertion
        set<vector<int>> uniqueTriplets;

        if(!nums.empty()) {
            vector<vector<int>> dupeTriplets;
            unordered_map<int, int> numSeenBefore;
            for(int i = 0; i < nums.size(); i++) {
                // If we've seen this nums[i] before, we already have all the possible triplets 
                // that could be formed with this number.
                // Consider [1,-1,0,1,2,-1,-4], if nums[i] is equal to the first 1, then we 
                // populate numsSeenBefore with [[1,-1],[1,0],[1,1],[1,2],[1,-4]] as the duplets, 
                // then when we encounter the second 1 as nums[i], we skip it because we already 
                // have [[1,2],[1,-1],[1,-4]] as possible duplets from before so it's redundant.
                if(numSeenBefore.find(nums[i]) != numSeenBefore.end()) {
                    continue;
                }

                unordered_map<int, int> secondNumSeenBefore;
                for(int j = i+1; j < nums.size(); j++) {
                    int negDupletSum = (nums[i] + nums[j]) * -1;
                    // We've seen this num before in the i loop, so skip since we already have all 
                    // its triplets.
                    if(numSeenBefore.find(negDupletSum) != numSeenBefore.end()) {
                        continue;
                    }

                    // Find viable triplets.
                    if(secondNumSeenBefore.find(negDupletSum) != secondNumSeenBefore.end()) {
                        vector<int> triplet = { nums[i], nums[j], negDupletSum };
                        dupeTriplets.push_back(triplet);
                    }
                    else {
                        secondNumSeenBefore[nums[j]] = nums[j];
                    }
                }
                numSeenBefore[nums[i]] = nums[i];
            }
            // Filter out the duplicates.
            for(auto& i : dupeTriplets) {
                sort(i.begin(), i.end());
                uniqueTriplets.insert(i);
            }
        }

        // Our return value
        vector<vector<int>> triplets(uniqueTriplets.begin(), uniqueTriplets.end());
        return triplets;
    }
};