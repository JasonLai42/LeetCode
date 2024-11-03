class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.size();
        int m = text2.size();
        if(n < 1 || m < 1) {
            return 0;
        }

        vector<vector<int>> log(n + 1, vector<int>(m + 1, 0));

        for(int i = n-1; i >= 0; i--) {
            for(int j = m-1; j >= 0; j--) {
                if(text1[i] == text2[j]) {
                    log[i][j] = 1 + log[i+1][j+1];
                }
                else {
                    log[i][j] = max(log[i+1][j], log[i][j+1]);
                }
            }
        }

        return log[0][0];
    }
};