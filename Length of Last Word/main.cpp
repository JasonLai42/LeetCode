#include <string>

using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s) {
        int lastLen = 0;
        
        // Iterate through the string from the back, so we get the last word first
        for(int i = s.size() - 1; i >= 0; i--) {
            // If we hit a space, we've finished with the last word
            if(s[i] == ' ') {
                // Check lastLen is greater than 0 before breaking to handle case where there are spaces at the end
                if(lastLen > 0) {
                    break;
                }
            }
            // If we haven't hit a space, we're still counting the last word, so increment lastLen
            else {
                lastLen++;
            }
        }
        
        return lastLen;
    }
};