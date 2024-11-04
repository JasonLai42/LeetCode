// I'm so smart omg
// Time Complexity: O(nlogn), Space Complexity: O(n)
// The gist of this solution is simple. First we sort all the intervals by their starting 
// value in ascending order. We then define a vector to hold our return values, which are all 
// the merged intervals. We then push the first interval of our newly sorted interval vector 
// onto this return vector. We're going to take advantage of one simple idea: because we sorted 
// the intervals by their starting values, if an interval overlaps with another interval, then 
// its starting value should be contained within the interval at the BACK of the return vector. 
// Basically, we're going to continuously extend the interval at the BACK of the return vector 
// until no more intervals overlap with it.
//
// For example: [[1,3], [2,6], [4,7], [8,10], [15,18]]
// The return vector by iteration:
// 1: [[1,3]] we push the first interval to initialize
// 2: [[1,6]] because 2 is between 1 and 3, we know it overlaps, so extend the interval to [1,6]
// 3: [[1,7]] because 4 is between 1 and 6, we know this interval overlaps to extend it to 7
// 4: [[1,7], [8,10]] 8 is not between 1 and 7, so we just push this interval onto the vector 
// 5: [[1,7], [8,10], [15,18]] 15 is not between 8 and 10 so more of the same

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> ret;

        // Sort the intervals vector by the starting values using a custom comparator
        sort(intervals.begin(), intervals.end(),
            [](const vector<int>& a, const vector<int>& b) {
                return a[0] < b[0];
            });

        // Push the first interval (smallest starting value) onto the return vector to initialize
        ret.push_back(intervals[0]);
        for(int i = 1; i < intervals.size(); i++) {
            int start = intervals[i][0];
            int end = intervals[i][1];
            // If the current interval we're looking at has a starting value between the values of 
            // the interval at the BACK of the return vector, we know it overlaps with the interval 
            // at the BACK, so we extend the end value if needed
            if(start >= ret.back()[0] && start <= ret.back()[1]) {
                // Extend the end value if needed (an interval could be completely contained 
                // within another interval so no extension would be needed, therefore take 
                // whichever is greater)
                ret.back()[1] = max(ret.back()[1], end);
            }
            // If this interval doesn't overlap, simply push it onto the return vector
            // This is the new interval we're going to extend
            else {
                ret.push_back(intervals[i]);
            }
        }

        return ret;
    }
};