// A trivially easy solution is linear (I wrote a linear solution at the bottom), but 
// we should use binary search to optimize.
// Going to assume newInterval is always a valid interval i.e. END > START.
// Here's how it works: consider: intervals = [[1,2],[4,5],[6,7],[8,10],[12,16]],     
// newInterval = [3,15]
// Another way to look at this is intervals is [1,2,4,5,6,7,8,9,10,12,13,14,15,16]
// Then what we can do is perform a binary search on 3 and 15 and find where these two 
// numbers slot into this expanded intervals. Once we find where they are, then all 
// we have to do is figure out if they are contained within an interval. If it's 
// contained in an interval, then that means there's an overlap and we MAY or MAY NOT 
// have to adjust our newInterval's bounds. In the above example, 3 comes after 2 and 
// before 4, so it lies between [1,2] and [4,5] so we don't have to do any comparisons. 
// However, 15 is contained in [12,16], so we have to do a comparison and take 16 as 
// our newInterval's bound now, which means our final newInterval is [3,16]. Note that 
// we don't care about the rest of the overlapping intervals in between our bounds 3 
// and 16 e.g. [6,7] and [8,10]. The reason is because we're only concerned with 
// intervals that contain our bounds 3 and 15, because then we may have to change our
// bounds like we did with 15 and [12,16], so we have to do 2 comparisons AT MOST, and 
// don't need to do any comparisons with the intervals in between. All the overlapping 
// intervals in between 3 and 16 are going to be removed no matter what and get 
// replaced with [3,16], so we're not concerned with them. After we get our final 
// newInterval [3,16], then with the indices we get from our two binary searches, it's 
// trivial to just take all the intervals that fall outside of [3,16] and construct my 
// return vector by just inserting all intervals that come before 3, insert [3,16], 
// then insert all intervals that come after 16. And voila, we're done.

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        // Our return value
        vector<vector<int>> retIntervals;

        // Edge case
        if(intervals.empty()) {
            retIntervals.push_back(newInterval);
            return retIntervals;
        }

        // Starting with our two binary searchs, findIndexForStart finds where the START of 
        // newInterval slots in and findIndexForEnd finds where the END of newInterval slots in.
        // These two functions both return a vector containing two integers. If the integers 
        // equal, then that means either we found a definitive interval in intervals that START/
        // END are contained in or START/END lie are outside of intervals i.e. at the very 
        // start or very end i.e. indices -1 or intervals.size(). If the integers in the vector 
        // do not equal, then that means that START/END lies in between two intervals e.g. 3 is 
        // between [1,2] and [4,5].
        vector<int> startLoc = findIndexForStart(intervals, newInterval[0], 0, intervals.size()-1);
        vector<int> endLoc = findIndexForEnd(intervals, newInterval[1], 0, intervals.size()-1);

        // Since newInterval is subject to change, we store it in a temp vector that we can 
        // make changes to.
        vector<int> actualNewInterval = newInterval;
        // Since we build our return vector by inserting all intervals that come before START,
        // then insert our newInterval, and finally insert all intervals that come after END, 
        // we need to know up to which interval do the intervals we want come before START in 
        // the intervals vector and from which interval do the intervals come after END. These 
        // two interators will store these bounds for us so we know which intervals will end 
        // up being in the final vector.
        vector<vector<int>>::iterator startInsertionBound = intervals.begin();
        vector<vector<int>>::iterator endInsertionBound = intervals.begin();
        // For the edge cases where our newInterval is at the very start or very end of 
        // the final vector, that means we don't have to insert any intervals before/after 
        // new interval, so these flags ensure we don't do so.
        bool atStart = false;
        bool atEnd = false;

        // Comparisons with intervals.size() in if conditions are wonky hence the const 
        // (somehow -1 >= 2 and -1 < 0 at the same time, so maybe something funky going on at 
        // runtime?).
        const int intervalsSize = intervals.size();
        // IMPORTANT NOTE: .insert() for vectors inserts elements in the range [first,last).
        // If the two integers in the vector equal, we START is contained in an interval 
        // or at the very beginning or end of intervals.
        if(startLoc[0] == startLoc[1]) {
            // If START is at the very end...
            if(startLoc[0] >= intervalsSize) {
                // then that means our newIntervals sits at the very end of intervals, so we 
                // don't need to insert any intervals after newInterval.
                atEnd = true;
                // We want to insert the entire intervals vector before newInterval, and here 
                // startLoc[0] should be equal to intervals.size(), so adding that offset to 
                // our startInsertionBound should yield intervals.end() for our final bound.
                startInsertionBound += startLoc[0];
            }
            // If START is at the very beginning of intervals... 
            else if(startLoc[0] < 0) {
                // then we know our newInterval will be at the beginning of intervals, 
                // therefore no intervals will come before it.
                atStart = true;
            }
            // Otherwise, START is contained in an interval... 
            else {
                // so we need to check if START is greater than the start of the interval 
                // it's contained in. If so, then that start will be the new START for our 
                // newInterval.
                if(newInterval[0] > intervals[startLoc[0]][0]) {
                    actualNewInterval[0] = intervals[startLoc[0]][0];
                }
                // Since this interval is an overlap, we don't want to include it, so we insert 
                // all intervals up to but not including startLoc[0].
                startInsertionBound += startLoc[0];
            }
        }
        // Otherwise, the integers in startLoc don't equal, so START sits between two intervals.
        else {
            // Since START is between the two intervals indexed by startLoc[0] and startLoc[1], 
            // that we means we need to include the interval indexed by startLoc[0] in our 
            // final vector, so we insert all intervals up to but not including startLoc[1].
            startInsertionBound += startLoc[1];
        }

        // Ditto above.
        if(endLoc[0] == endLoc[1]) {
            // If the END bound of newInterval is at the very end of intervals... 
            if(endLoc[0] >= intervalsSize) {
                // then we know no intervals will come after newInterval.
                atEnd = true;
            }
            // If the END bound is at the very beginning of intervals... 
            else if(endLoc[0] < 0) {
                // then we know our newInterval will be at the beginning of intervals, 
                // therefore no intervals will come before it.
                atStart = true;
                // endLoc[0] at this point is -1, and we want to insert all the intervals in 
                // the intervals vector after newInterval, so endInsertionBound has to be 
                // intervals.begin(), so we add 1 to -1 to get 0 and therefore no offset.
                endInsertionBound += endLoc[0]+1;
            }
            // Otherwise, END is contained in an interval... 
            else {
                // so we need to check if END is less than the end of the interval it's 
                // contained in. If so, then that end will be the new END for our newInterval.
                if(newInterval[1] < intervals[endLoc[0]][1]) {
                    actualNewInterval[1] = intervals[endLoc[0]][1];
                }
                // Since this interval is an overlap, we don't want to include it, so we insert 
                // all intervals starting from the interval that comes after startLoc[0].
                endInsertionBound += endLoc[0]+1;
            }
        }
        // Otherwise, the integers in endLoc don't equal, so END sits between two intervals.
        else {
            // Since END is between the two intervals indexed by endLoc[0] and endLoc[1], 
            // that we means we need to include the interval indexed by startLoc[1] in our 
            // final vector, so we insert all intervals starting from startLoc[1] inclusive.
            endInsertionBound += endLoc[1];
        }

        // Construct the final vector
        if(!atStart) {
            retIntervals.insert(
                retIntervals.end(),
                intervals.begin(),
                startInsertionBound
            );
        }
        retIntervals.push_back(actualNewInterval);
        if(!atEnd) {
            retIntervals.insert(
                retIntervals.end(),
                endInsertionBound,
                intervals.end()
            );
        }

        return retIntervals;
    }

    vector<int> findIndexForStart(vector<vector<int>>& intervals, int startVal, int l, int r) {
        if(r >= l) {
            int mid = l + ((r - l) / 2);

            // Return if we found an interval that startVal is contained in.
            if(intervals[mid][0] <= startVal && intervals[mid][1] >= startVal) {
                vector<int> index{mid, mid};
                return index;
            }
            // If the END of this interval is less than startVal, look right, because there's 
            // a possibility there's other intervals with numbers that are less than startVal.
            else if(intervals[mid][1] < startVal) {
                return findIndexForStart(intervals, startVal, mid+1, r);
            }
            // Else, look left, because we now know startVal isn't in this interval and the 
            // END for this interval is greater than startVal, so an interval that contains 
            // startVal or startVal's true position can only exist in the left half.
            else {
                return findIndexForStart(intervals, startVal, l, mid-1);
            }
        }

        // l at this point will be greater than r, so we have three scenarios:
        vector<int> index;
        const int intervalsSize = intervals.size();
        // startVal lies at the very end of intervals.
        if(l == intervalsSize) {
            index.insert(index.begin(), 2, l);
        }
        // startVal lies at the very beginning of intervals.
        else if(r == -1) {
            index.insert(index.begin(), 2, r);
        }
        // startVal lies between two intervals.
        else {
            index.push_back(r);
            index.push_back(l);
        }
        return index;
    }

    vector<int> findIndexForEnd(vector<vector<int>>& intervals, int endVal, int l, int r) {
        if(r >= l) {
            int mid = l + ((r - l) / 2);

            // Return if we found an interval that endVal is contained in.
            if(intervals[mid][0] <= endVal && intervals[mid][1] >= endVal) {
                vector<int> index{mid, mid};
                return index;
            }
            // If the START of this interval is greater than endVal, look left, because there's 
            // a possibility there's other intervals with numbers that are greater than endVal.
            else if(intervals[mid][0] > endVal) {
                return findIndexForEnd(intervals, endVal, l, mid-1);
            }
            // Else, look right, because we now know endVal isn't in this interval and the 
            // START for this interval is less than endVal, so an interval that contains 
            // endVal or endVal's true position can only exist in the right half.
            else {
                return findIndexForEnd(intervals, endVal, mid+1, r);
            }
        }

        // l at this point will be greater than r, so we have three scenarios:
        vector<int> index;
        const int intervalsSize = intervals.size();
        // endVal lies at the very end of intervals.
        if(l == intervalsSize) {
            index.insert(index.begin(), 2, l);
        }
        // endVal lies at the very beginning of intervals.
        else if(r == -1) {
            index.insert(index.begin(), 2, r);
        }
        // endVal lies between two intervals.
        else {
            index.push_back(r);
            index.push_back(l);
        }
        return index;
    }
};

// class Solution {
// public:
//     vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
//         vector<vector<int>> retIntervals;

//         if(intervals.empty()) {
//             retIntervals.push_back(newInterval);
//             return retIntervals;
//         }

//         bool startPosFound = false;
//         bool endPosFound = false;
//         vector<int> actualNewInterval = newInterval;
//         int i;
//         for(i = 0; i < intervals.size(); i++) {
//             if(!startPosFound && !endPosFound) {
//                 if(newInterval[0] >= intervals[i][0] && newInterval[0] <= intervals[i][1]) {
//                     actualNewInterval[0] = intervals[i][0];
//                     startPosFound = true;
//                     i--;
//                 }
//                 else if(newInterval[0] < intervals[i][0]) {
//                     startPosFound = true;
//                     i--;
//                 }
//                 else {
//                     retIntervals.push_back(intervals[i]);
//                 }
//             }
//             else if(startPosFound && !endPosFound) {
//                 if(newInterval[1] >= intervals[i][0] && newInterval[1] <= intervals[i][1]) {
//                     actualNewInterval[1] = intervals[i][1];
//                     retIntervals.push_back(actualNewInterval);
//                     endPosFound = true;
//                 }
//                 else if(newInterval[1] < intervals[i][0]) {
//                     retIntervals.push_back(actualNewInterval);
//                     retIntervals.push_back(intervals[i]);
//                     endPosFound = true;
//                 }
//             }
//             else {
//                 retIntervals.push_back(intervals[i]);
//             }
//         }

//         if(!startPosFound || !endPosFound) {
//             retIntervals.push_back(actualNewInterval);
//         }

//         return retIntervals;
//     }
// };