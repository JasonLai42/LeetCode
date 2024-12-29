/* Time Complexity: O(log(m * n)) i.e. O(logm + logn)
 * Space Complexity: O(1)
 * Basically we want to perform two binary searches. One in the m (row) dimension, then one in the n (column) dimension. 
 * Since the integers in the matrix are sorted, we can guarantee that all of the integers at the start of each row are 
 * also sorted e.g. for matrix [[1,3,5,7],[10,11,16,20],[23,30,34,60]], the starting integers 1, 10, 23 are sorted in 
 * in ascending order so we can perform binary search on these values! This means the first binary search we perform will 
 * prioritize finding which row the target lives in and in order to do that we check the starting integer of the current 
 * row i we're looking at and the starting integer of the next row i+1 because target must be >= starting integer of row 
 * i and < starting integer of row i+1 in order to validly live in row i. Alternatively, if i is the last row in the 
 * matrix and the target is >= starting integer of i, then target could also live in this row. Once we find which row 
 * target lives in, we return this value and use it for the next binary search, which is find where exactly target is in 
 * the row if it exists. This is just a normal binary search. Because we perform a binary search in the m dimension and n 
 * dimension respectively, the time complexity is O(logm + logn) which is the same as O(log(m * n)) which meets our 
 * requirement. Space complexity is O(1) since we only use constant variables.
 */
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        // Get matrix dimension sizes
        int m = matrix.size();
        int n = matrix[0].size();

        // Perform first binary search to find which row target lives in
        int ml = 0;
        int mr = m - 1;
        int row = mBinarySearch(matrix, m, target, ml, mr);
        // We couldn't find a plausible row that target lives in (in other words, all of the starting integers of each 
        // row are greater than target)
        if(row == -1)
            return false;

        // Once we have which row target lives in, we find the exact location of target if it exists in the row
        int nl = 0;
        int nr = n - 1;
        return nBinarySearch(matrix, row, target, nl, nr);
    }

    int mBinarySearch(vector<vector<int>>& matrix, int m, int target, int l, int r) {
        if(l > r) {
            return -1;
        }

        int mid = l + ((r - l) / 2);

        // Check starting integer of the current row to see if its <= target
        if(matrix[mid][0] <= target) {
            // Check the next row to see if the starting integer is > target or if current row is the last row in the 
            // matrix
            if(mid == m-1 || (mid < m-1 && matrix[mid+1][0] > target)) {
                return mid;
            }
            // If the next row's starting integer is also <= target, we will search the upper half of the rows
            else {
                return mBinarySearch(matrix, m, target, mid+1, r);
            }
        }
        // Otherwise, the starting integer of the current row is greater than target so we search the lower half of the 
        // rows
        else {
            return mBinarySearch(matrix, m, target, l, mid-1);
        }
    }

    // Once we have the row that target lives in, we perform a normal binary search as follows
    bool nBinarySearch(vector<vector<int>>& matrix, int row, int target, int l, int r) {
        if(l > r) {
            return false;
        }

        int mid = l + ((r - l) / 2);

        if(matrix[row][mid] == target) {
            return true;
        }
        else if(matrix[row][mid] < target) {
            return nBinarySearch(matrix, row, target, mid+1, r);
        }
        else {
            return nBinarySearch(matrix, row, target, l, mid-1);
        }
    }
};