/* Time Complexity: O(n)
 * Space Complexity: O(1)
 * Peeked the solution. Basically what we're gonna do here is keep track of the frequency of each character in s1 
 * in a vector and also keep track of the frequency of each character in our sliding window in another vector. If 
 * they're valid permutations of one another then the frequency counts of both vectors will be equal. Time complexity 
 * here is O(n) because although we have to iterate through the vectors to check equality, that is always an O(26) 
 * operation so we have O(26n) which is just O(n). Space complexity is O(52) which is just O(1).
 */

 class Solution {
    public:
        bool checkInclusion(string s1, string s2) {
            if(s2.length() < s1.length()) {
                return false;
            }
    
            vector<int> s1Counts(26, 0);
            for(int i = 0; i < s1.length(); i++) {
                s1Counts[s1[i] - 'a']++;
            }
    
            vector<int> windowCounts(26, 0);
            int i = 0, j = 0;
            while(j < s2.length()) {
                windowCounts[s2[j] - 'a']++;
    
                // Check if the current window's character frequency counts are equal to those of s1
                if(j - i + 1 == s1.length()) {
                    if(checkVectorsAreEqual(s1Counts, windowCounts)) {
                        return true;
                    }
                }
    
                // If our window hasn't expanded to the size of s1 yet, only increment j to increase the size of the window
                if(j - i + 1 < s1.length()) {
                    j++;
                }
                // Otherwise, our window is the size of s1, so we can slide it over 1 character to check the next permutation
                else {
                    windowCounts[s2[i] - 'a']--;
                    i++;
                    j++;
                }
            }
    
            return false;
        }
        
        bool checkVectorsAreEqual(vector<int>& a, vector<int>& b) {
            for(int i = 0; i < 26; i++) {
                if(a[i] != b[i]) {
                    return false;
                }
            }
    
            return true;
        }
    };