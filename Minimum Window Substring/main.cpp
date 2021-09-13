#include <string>
#include <unordered_map>
#include <deque>

using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        // Keeps track of how many of each character shows up in string t
        unordered_map<char, int> charToNum;
        // Does the same thing as charToNum, but we decrement the values to check if we have a complete window
        unordered_map<char, int> charToNumDecrement;
        // Keeps track of how many of each character in t is in the current window
        unordered_map<char, int> charToWindowNum;
        // How many characters of t we need in the window before we have a complete window
        int charLeft = t.size();
        
        // Initialize charToNum and charToNumDecrement
        for(int i = 0; i < t.size(); i++) {
            charToNum[t[i]]++;
            charToNumDecrement[t[i]]++;
        }
        
        // Starting and ending indices of the minimum window substring
        int start = 0;
        int end = 0;
        
        // Sliding window; keeps track of characters and their indices
        deque<char> characters;
        deque<int> indices;
        
        // Flow control to see if we have a complete window yet
        bool completeFound = false;
        for(int i = 0; i < s.size(); i++) {
            if(charToNum.find(s[i]) != charToNum.end()) {
                // Push this character (that shows up in t) into the window
                characters.push_back(s[i]);
                indices.push_back(i);
                charToWindowNum[s[i]]++;

                // Trim the start of the window to remove any redundant characters
                if(characters.front() == s[i]) {
                    while(true) {
                        if(charToWindowNum[characters.front()] > charToNum[characters.front()]) {
                            charToWindowNum[characters.front()]--;
                            characters.pop_front();
                            indices.pop_front();
                        }
                        else {
                            break;
                        }
                    }

                    // Every time we trim the window, we check if have a smaller minimum window substring
                    if((indices.back() + 1 - indices.front()) <= (end - start) && completeFound) {
                        start = indices.front();
                        end = indices.back() + 1;
                    }
                }
                
                // Check if we have a complete window
                if(charToNumDecrement[s[i]] > 0 && !completeFound) {
                    charToNumDecrement[s[i]]--;
                    charLeft--;

                    if(charLeft == 0) {
                        completeFound = true;
                        start = indices.front();
                        end = indices.back() + 1;
                    }
                }
            }
        }
        
        // Return the substring with the start, end indices
        return s.substr(start, end - start);
    }
};