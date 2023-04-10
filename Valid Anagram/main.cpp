class Solution {
public:
    bool isAnagram(string s, string t) {
        // Edge case: they can't be anagrams of one another if they're different length strings
        if(s.size() != t.size()) {
            return false;
        }

        // Because we're only dealing with lowercase English letters, we can just use an array 
        // of length 26 to act as a hash table for keeping track of the number of instances 
        // that a character shows up in the string s. We need these counts because we will use 
        // this table to check against the string t to ensure that t has the same number of 
        // each character that s has, in order for them to be anagrams on one another. We first 
        // zero initialize the array since each character has initially 0 count, and we access 
        // each character's count using character arithmetic (see below).
        int alphabetCount[26] = { 0 };

        // Iterate through the string s and record the counts for each character
        for(int i = 0; i < s.size(); i++) {
            // Increment the count for the character s[i]. We subtract 'a' from s[i] to clamp 
            // the integer value of s[i] to the range 0-25, so that we have a valid index to 
            // access our array with.
            alphabetCount[s[i]-'a']++;
        }

        // Iterate through the string t and check that every character of t is found in s the 
        // same number of times
        for(int i = 0; i < t.size(); i++) {
            // If this character has 0 count or less, then t has more of this character than s, 
            // so they are not anagrams (realistically, the count shouldn't be less than 0)
            if(alphabetCount[t[i]-'a'] <= 0) {
                return false;
            }

            // Decrement the count for this character since we've matched one instance of it in 
            // t to one instance of it in s successfully
            alphabetCount[t[i]-'a']--;
        }

        return true;
    }
};

// This solution uses an unordered_map instead of an array to store the counts of characters. 
// Perhaps slightly better for memory since we don't have to store a value for all 26 
// characters, but less readable and elegant, but they're really the same tbh.
// class Solution {
// public:
//     bool isAnagram(string s, string t) {
//         // Edge case: they can't be anagrams of one another if they're different length strings
//         if(s.size() != t.size()) {
//             return false;
//         }

//         // Hash table that stores the number of instances (value) that a character (key) shows 
//         // up in the string s. We need the number of instances, because we need t to have the 
//         // same exact number of certain characters that s has.
//         unordered_map<char, int> alphabetCount;

//         // Iterate through s and populate our hash table
//         for(int i = 0; i < s.size(); i++) {
//             // If this is the first time we've seen this character, we have to give it an entry
//             if(alphabetCount.find(s[i]) == alphabetCount.end()) {
//                 alphabetCount[s[i]] = 0;
//             }

//             // Increment the count for this character
//             alphabetCount[s[i]]++;
//         }

//         // Now iterate through t and check that every character of t is found within s
//         for(int i = 0; i < t.size(); i++) {
//             // If this character isn't found in the hash table or has a 0 count, meaning t has 
//             // more of this character than s has, then t isn't an anagram of s, so return false
//             if(alphabetCount.find(t[i]) == alphabetCount.end() || alphabetCount[t[i]] == 0) {
//                 return false;
//             }

//             // Decrement the count for this character since we've matched one instance of this 
//             // character in t to one in s
//             alphabetCount[t[i]]--;
//         }

//         return true;
//     }
// };