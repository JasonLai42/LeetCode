#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> all_combinations;
        // Edge case if digits has no numbers
        if(digits.length() == 0) {
            return all_combinations;
        }
        
        fanDigit(digits, "", all_combinations);
        
        return all_combinations;
    }

    // Use recursion
    void fanDigit(string digits, string current, vector<string>& all_strs) {
        // If we went through every digit, the current string has reach max length and is a 
        // unique combination we add to the vector
        if(digits.length() == 0) {
            all_strs.push_back(current);
            return;
        }
        
        // For each char for a given num on keypad, add to a new instance of the current string
        for(int i = 0; i < keypad[digits[0]].length(); i++) {
            string curr = current + keypad[digits[0]][i];
            // Recursive call to pass built string so far and fan next num on keypad in digits
            fanDigit(digits.substr(1), curr, all_strs);
        }
        
        return;
    }
    
    // A "dictionary" for the keypad
    unordered_map<char, string> keypad = {
            {'2', "abc"},
            {'3', "def"},
            {'4', "ghi"},
            {'5', "jkl"},
            {'6', "mno"},
            {'7', "pqrs"},
            {'8', "tuv"},
            {'9', "wxyz"}
    };
};