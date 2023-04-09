class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        // Edge case
        if(matrix.size() == 0) {
            return;
        }

        // Hash tables to check which rows and columns we need to zero out; we use sets to 
        // avoid any duplicate rows/columns to cut down on memory usage (keeps it O(m+n))
        unordered_set<int> zeroRows;
        unordered_set<int> zeroCols;

        // First pass: we iterate through the matrix and record any rows and columns that 
        // need to be zeroed out when we encounter a 0 at matrix[row][col]
        for(int row = 0; row < matrix.size(); row++) {
            for(int col = 0; col < matrix[0].size(); col++) {
                if(matrix[row][col] == 0) {
                    if(zeroRows.find(row) == zeroRows.end()) {
                        zeroRows.insert(row);
                    }
                    if(zeroCols.find(col) == zeroCols.end()) {
                        zeroCols.insert(col);
                    }
                }
            }
        }

        // Second pass: we iterate through and use out hash tables to zero out the appropriate 
        // rows and columns
        for(int row = 0; row < matrix.size(); row++) {
            for(int col = 0; col < matrix[0].size(); col++) {
                // If this [row] or [col] is found in our hash tables, then we need to zero 
                // out this element
                if(zeroRows.find(row) != zeroRows.end() || 
                    zeroCols.find(col) != zeroCols.end()) {
                    matrix[row][col] = 0;
                }
            }
        }

        return;
    }
};

// I peeked this solution to see what a memory improvements could be made. I felt this was 
// worth writing down, since I had not considered using the first row and column of the 
// matrix as our "hash table" to check if I need to zero out a row/column or not.
// class Solution {
// public:
//     void setZeroes(vector<vector<int>>& matrix) {
//         // Edge case
//         if(matrix.size() == 0) {
//             return;
//         }

//         // We're going to use the first row and column of the matrix to record whether we 
//         // need to zero out a row/column or not, so we need these flags to know whether the 
//         // first row and column need to be zeroed out as well, because there's going to be 
//         // a lot of modifications made to the first row and column so it will be hard to tell 
//         // if there was a 0 initially in the first row or column.
//         bool zeroFirstRow = false, zeroFirstCol = false;

//         for(int row = 0; row < matrix.size(); row++) {
//             for(int col = 0; col < matrix[0].size(); col++) {
//                 // Check if we've encountered a 0
//                 if(matrix[row][col] == 0) {
//                     // If we found a 0 in the first row, then we need to zero out the first 
//                     // row later
//                     if(row == 0) {
//                         zeroFirstRow = true;
//                     }
//                     // If we found a 0 in the first column, then we need to zero out the first 
//                     // column later
//                     if(col == 0) {
//                         zeroFirstCol = true;
//                     }

//                     // Because we've encountered a 0 at this i,j (row,col), we know that this 
//                     // row and column need to be zeroed out, so record that in the respective 
//                     // positions in the first row and column
//                     matrix[row][0] = 0;
//                     matrix[0][col] = 0;
//                 }
//             }
//         }

//         // Now using the first row and column as a guide, we will zero out any necessary rows 
//         // and columns. Note that we start from row = 1 and col = 1.
//         for(int row = 1; row < matrix.size(); row++) {
//             for(int col = 1; col < matrix[0].size(); col++) {
//                 // Check the value in the first row/column; if it's a zero, then zero out this 
//                 // element
//                 if(matrix[row][0] == 0 || matrix[0][col] == 0) {
//                     matrix[row][col] = 0;
//                 }
//             }
//         }

//         // If we need to zero out either the first row or column, then do so
//         if(zeroFirstRow) {
//             for(int col = 0; col < matrix[0].size(); col++) {
//                 matrix[0][col] = 0;
//             }
//         }
//         if(zeroFirstCol) {
//             for(int row = 0; row < matrix.size(); row++) {
//                 matrix[row][0] = 0;
//             }
//         }

//         return;
//     }
// };