// class Solution {
// public:
//     int trap(vector<int>& height) {
//         int totalRainwater = 0;

//         const unsigned heightSize = height.size();
//         int peakStart = 0;
//         int peakStartIndex = 0;

//         int peakEnd = 0;
//         int peakEndIndex = 0;
//         int currentPuddle = 0;
//         bool peakFound = false;
//         if(heightSize >= 3) {
//             for(int i = 1; i < heightSize; i++) {
//                 int j = i-1;
//                 if(!peakFound && height[j] > height[i]) {
//                     peakStart = height[j];
//                     peakStartIndex = j;
//                     peakFound = true;
//                     continue;
//                 }
//                 else if(peakFound && height[j] < height[i]) {
//                     peakEnd = height[i];
//                     peakEndIndex = i;
//                     if(peakEnd >= peakStart) {

//                         peakStart = 0;
//                         peakStartIndex = 0;
//                         peakEnd = 0;
//                         peakEndIndex = 0;
//                         peakFound = false;
//                     }
//                 }

//                 if(peakFound) {
//                     currentPuddle += peakStart - height[i];
//                 }
//             }
//         }
//         if(peakFound) {
//             if(peakEnd > 0) {
//                 int rainwaterToRemove 
//                     = (peakStart - peakEnd) * ((peakEndIndex - peakStartIndex) - 1);
//                 totalRainwater -= rainwaterToRemove;
//             }
//         }

//         return totalRainwater;
//     }
// };

// class Solution {
// public:
//     int trap(vector<int>& height) {
//         int totalRainwater = 0;

//         const unsigned heightSize = height.size();
//         if(heightSize >= 3) {
//             for(int i = 1; i < heightSize; i++) {
//                 int startPeak = i-1;
//                 if(height[startPeak] > height[i]) {
//                     int landMass = 0;
//                     for(int endPeak = i; endPeak < heightSize; endPeak++) {
//                         if(height[endPeak] >= height[startPeak]) {
//                             int waterMass = (height[startPeak] * ((endPeak - startPeak) - 1)) - landMass;
//                             totalRainwater += waterMass;
//                             i = endPeak;
//                             break;
//                         }
//                         else {
//                             landMass += height[endPeak];
//                         }
//                     }
//                 }
//             }
//         }

//         return totalRainwater;
//     }
// };

// Dumb Solution - Times Out
// class Solution {
// public:
//     int trap(vector<int>& height) {
//         vector<int> waterDp(1, 0);
//         vector<int> landDp;
//         vector<int> mostRecentHeights;

//         const unsigned heightSize = height.size();
//         if(heightSize > 2) {
//             landDp.push_back(height[0]);

//             bool avoidDoubleCount = false;
//             for(int i = 1; i < heightSize; i++) {
//                 int j = i-1;
//                 // Monotonically decreasing
//                 if(height[j] > height[i]) {
//                     for(int k = 0; k < height[j]; k++) {
//                         if(k >= mostRecentHeights.size()) {
//                             mostRecentHeights.push_back(j);
//                             continue;
//                         }
//                         mostRecentHeights[k] = j;
//                     }
//                     waterDp.push_back(waterDp[j]);
//                     avoidDoubleCount = false;
//                 }
//                 // Monotonically increasing
//                 else if(height[j] < height[i] && !mostRecentHeights.empty() && !avoidDoubleCount) {
//                     int peakIndex;
//                     int peakHeight;
//                     if(height[i] < mostRecentHeights.size()) {
//                         peakIndex = mostRecentHeights[height[i]-1];
//                         peakHeight = height[i];
//                     }
//                     else {
//                         peakIndex = mostRecentHeights.back();
//                         peakHeight = mostRecentHeights.size();
//                         avoidDoubleCount = true;
//                     }
//                     int landMass = landDp[j] - landDp[peakIndex];
//                     int waterMass = (peakHeight * ((i - peakIndex) - 1)) - landMass;
//                     waterDp.push_back(waterDp[peakIndex] + waterMass);
//                 }
//                 else {
//                     waterDp.push_back(waterDp[j]);
//                 }
//                 landDp.push_back(landDp[j]+height[i]);
//             }
//         }

//         return waterDp[heightSize-1];
//     }
// };

// I cheated and peeked the solution. I was so tunnel-visioned on doing this in one pass, I 
// did not even consider doing this in two passes, and it makes so much sense that way.
class Solution {
public:
    int trap(vector<int>& height) {
        // Our return value
        int totalRainwater = 0;

        // A condition to catch edge cases. The island can only hold water if there's at least 
        // three spaces; one bar on each end that's taller than the middle position.
        if(height.size() < 3) {
            return totalRainwater;
        }

        // Two arrays - tallestFromTheLeft tracks the tallest bar we've encountered thus far 
        // when walking the island left to right i.e. position 0 to height.size()-1. 
        // tallestFromTheRight tracks the tallest bar we've encountered thus far when walking 
        // the island right to left i.e. position height.size()-1 to 0. These arrays will be 
        // monotonically increasing in their respective directions i.e. left to right and 
        // right to left.
        int tallestFromTheLeft[height.size()];
        int tallestFromTheRight[height.size()];

        // We need to store the height of the first bar for the two arrays, so we can compare 
        // when we populate the array.
        tallestFromTheLeft[0] = height[0];
        tallestFromTheRight[height.size()-1] = height[height.size()-1];

        // Populate the arrays.
        for(int i = 1; i < height.size(); i++) {
            tallestFromTheLeft[i] = max(tallestFromTheLeft[i-1], height[i]);
        }
        for(int i = height.size()-2; i >= 0; i--) {
            tallestFromTheRight[i] = max(tallestFromTheRight[i+1], height[i]);
        }

        // Now at each position i , calculate how much water is stored there. To do so, we 
        // check if the position i is between two maxima. We know that this position i is 
        // either sandwiched between the two tallest bars encountered thus far from the right 
        // and left based on tallestFromTheLeft[i] and tallestFromTheRight[i] or i is itself 
        // a maximum. The only water that can be stored at i can be calculated by taking the 
        // difference between the height of the shorter bar between tallestFromTheLeft[i] and 
        // tallestFromTheRight[i] and the height of bar at position i. If this difference is 
        // greater than 0, then that means there is water stored here, so we add it to our 
        // totalRainwater.
        for(int i = 0; i < height.size(); i++) {
            int water = min(tallestFromTheLeft[i], tallestFromTheRight[i]) - height[i];
            if(water > 0) {
                totalRainwater += water;
            }
        }

        return totalRainwater;
    }
};