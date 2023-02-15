class Solution {
public:
    int uniquePaths(int m, int n) {
        // Dynamic programming array: basically at each square, we store the total number of 
        // different paths we can take to reach that square; the idea is, we can get the number 
        // of paths it takes to reach a square by getting the number of paths it takes to reach 
        // the squares that are above and to the left of it i.e. the only squares that the 
        // current square is reachable from
        vector<vector<int>> pathsDp(m, vector<int>(n));

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                // If the square we're looking at is along the top edge or left edge, we 
                // know it's only reachable by one possible path: going purely down or purely 
                // right
                if(i == 0 || j == 0) {
                    pathsDp[i][j] = 1;
                    continue;
                }

                // Get the number of different paths the square i,j is reachable by, by taking 
                // the sum of the paths from the two squares preceding it above and to the left
                pathsDp[i][j] = pathsDp[i-1][j] + pathsDp[i][j-1];
            }
        }

        // The final total is stored in the destination square in the bottom right corner
        return pathsDp[m-1][n-1];
    }
};

// Simplest and most intuitive solution, but bad time complexity (exponential in size of grid 
// in longest dimension)
// class Solution {
// public:
//     int uniquePaths(int m, int n) {
//         // Call recursive function to get number of paths
//         int numPaths = getPaths(m, n, 0, 0);

//         return numPaths;
//     }

//     int getPaths(int m, int n, int x, int y) {
//         // Once we reach the end, we know this is a possible path, so return 1 to add to total
//         // number of paths
//         if(x == m-1 || y == n-1) {
//             return 1;
//         }

//         // Recursive calls to go in either possible direction: down or right
//         return getPaths(m, n, x, y+1) + getPaths(m, n, x+1, y);
//     }
// };