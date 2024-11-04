// Time Complexity: O(n/2), Space Complexity: O(1)
// 2 pointer solution: basically to get a valid palindrome, we have to match characters on the 
// left and right of the string until we get to the center, so we do exactly that.

class Solution {
public:
    bool isPalindrome(string s) {
        // Get our left and right pointers
        int i = 0;
        int j = s.size()-1;

        // We keep going until we reach the center of string which is when i is no longer < j
        while(i < j) {
            // Check if left pointer is a valid alphanumeric character to check
            if(isalnum(s[i])) {
                // Check if right pointer is a valid alphanumeric character to check
                if(isalnum(s[j])) {
                    // If both pointers are alphanumeric, check that they are matching characters
                    if(tolower(s[i]) != tolower(s[j])) {
                        // If they don't match, we don't have a palindrome, so return false
                        return false;
                    }
                    // Move onto the next set of characters to match
                    i++;
                    j--;
                }
                else {
                    // Keep searching for a valid character on right pointer
                    j--;
                }
            }
            else {
                // Keep searching for a valid character on left pointer
                i++;
            }
        }

        // If we reach the end, we have a valid palindrome so return true
        return true;
    }
};