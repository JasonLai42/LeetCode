// class Solution {
// public:
//     vector<vector<int>> threeSum(vector<int>& nums) {
//         // Make our lives easier, lets use set to remove duplicate triplets - O(log(n)) insertion
//         set<vector<int>> uniqueTriplets;

//         if(!nums.empty()) {
//             vector<vector<int>> dupeTriplets;
//             unordered_map<int, int> numSeenBefore;
//             for(int i = 0; i < nums.size(); i++) {
//                 // If we've seen this nums[i] before, we already have all the possible triplets 
//                 // that could be formed with this number.
//                 // Consider [1,-1,0,1,2,-1,-4], if nums[i] is equal to the first 1, then we 
//                 // populate numsSeenBefore with [[1,-1],[1,0],[1,1],[1,2],[1,-4]] as the duplets, 
//                 // then when we encounter the second 1 as nums[i], we skip it because we already 
//                 // have [[1,2],[1,-1],[1,-4]] as possible duplets from before so it's redundant.
//                 if(numSeenBefore.find(nums[i]) != numSeenBefore.end()) {
//                     continue;
//                 }

//                 unordered_map<int, int> secondNumSeenBefore;
//                 for(int j = i+1; j < nums.size(); j++) {
//                     int negDupletSum = (nums[i] + nums[j]) * -1;
//                     // We've seen this num before in the i loop, so skip since we already have all 
//                     // its triplets.
//                     if(numSeenBefore.find(negDupletSum) != numSeenBefore.end()) {
//                         continue;
//                     }

//                     // Find viable triplets.
//                     if(secondNumSeenBefore.find(negDupletSum) != secondNumSeenBefore.end()) {
//                         vector<int> triplet = { nums[i], nums[j], negDupletSum };
//                         dupeTriplets.push_back(triplet);
//                     }
//                     else {
//                         secondNumSeenBefore[nums[j]] = nums[j];
//                     }
//                 }
//                 numSeenBefore[nums[i]] = nums[i];
//             }
//             // Filter out the duplicates.
//             for(auto& i : dupeTriplets) {
//                 sort(i.begin(), i.end());
//                 uniqueTriplets.insert(i);
//             }
//         }

//         // Our return value
//         vector<vector<int>> triplets(uniqueTriplets.begin(), uniqueTriplets.end());
//         return triplets;
//     }
// };

// Peeked the solution for a hint to use two pointers
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        // Our return value
        vector<vector<int>> triplets;

        // Edge case; we know we need at least 3 numbers to form a triplet
        if(nums.size() < 3) {
            return triplets;
        }

        // We'll initially insert our triplets into a set as to filter out any duplicates
        set<vector<int>> tripletSet;

        // Sort the nums array to simulate a number line
        sort(nums.begin(), nums.end());
        // Basically, we're going to traverse the number line from left to right, and for each 
        // number nums[i], we're going to gather all the valid triplets that use that number 
        // nums[i]
        for(int i = 0; i < nums.size(); i++) {
            // For each i, we initialize two pointers: one that is the number directly after i 
            // and the other that is the very rightmost number. Since we gather all the valid 
            // triplets using the number at i, we don't have to look back at any numbers that 
            // came before the current i in the number line, hence why j = i + 1. With how 
            // these pointers are set up, we also ensure that i != j, i != k, and j != k.
            int j = i + 1;
            int k = nums.size() - 1;

            // We're going to loop until we find all valid triplets for this i
            while(j < k) {
                // Get the sum of this triplet
                int sum = nums[i] + nums[j] + nums[k];

                // If the sum is 0, we found a valid triplet, so add it to our set
                if(sum == 0) {
                    vector<int> triplet{nums[i], nums[j], nums[k]};
                    tripletSet.insert(triplet);
                    // There might be other valid triplets that use nums[i], so move our 
                    // pointers and continue looking
                    j++;
                    k--;
                }
                // If the sum is less than 0, we know our sum needs to be greater, so we 
                // increment j, since based on the number line nums[j+1] > nums[j]
                else if(sum < 0) {
                    j++;
                }
                // If the sum is greater than 0, we know our sum needs to be less, so we 
                // decrement k, since based on the number line nums[k-1] < nums[k]
                else {
                    k--;
                }
            }
        }

        // Convert the set into the vector for our return
        triplets.assign(tripletSet.begin(), tripletSet.end());

        return triplets;
    }
};