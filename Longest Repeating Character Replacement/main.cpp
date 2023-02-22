class Solution {
public:
    int characterReplacement(string s, int k) {
        // Cheated and peeked the admin solution - couldn't think of a better solution than my 
        // O(mn) jank sliding window. Admin solution is elegant, but takes a bit to wrap your 
        // head around.
        // Here's how it works: we create a sliding window and keep track of the frequencies 
        // of each different character in the window (using the 
        // frequencyofLetterInCurrentWindow hashtable below) and foremost keeping track of 
        // the highest frequency for a character we've seen in the current window (using the 
        // highestFrequencyInCurrentWindow variable below). We hold the start of the window in 
        // place while we expand the window by incrementing the end of the window until the 
        // window can no longer accommodate any characters that aren't the character with the 
        // highest frequency in the window i.e. if the number of characters that aren't the 
        // character with the highest frequency in the window exceeds k, then we've exceeded 
        // the amount of characters we can replace to continue the repeating string. When the 
        // window can no longer accommodate any additional characters per the reasoning above, 
        // we shrink the window by incrementing the start, until we once again have a valid 
        // window (count of characters that aren't the highest frequency character is less 
        // than k). We continue this sliding window until we reach the end of the string, and 
        // as we iterate, we compare the size of the current window against our return value: 
        // longest; by the end of the loop, longest will have stored the length of the longest 
        // possible repeating character string with k replaced characters.

        // Our return value.
        int longest = 0;

        // A hashtable to keep track of the frequencies of each character in the current 
        // window.
        unordered_map<char, int> frequencyOfLetterInCurrentWindow;
        // An int to keep track of the highest frequency of a character in the current window.
        int highestFrequencyInCurrentWindow = 0;

        // Start index of our window - marks the beginning of our window and is also the 
        // index of the first character in the window.
        int start = 0;
        // End index of our window - we iterate on it to expand the window and it is also the 
        // index of the last character in the window.
        for(int end = 0; end < s.size(); end++) {
            // If we haven't seen this character before, add an entry for its frequency in the 
            // hashtable.
            if(frequencyOfLetterInCurrentWindow.find(s[end]) 
                == frequencyOfLetterInCurrentWindow.end()) {
                frequencyOfLetterInCurrentWindow[s[end]] = 1;
            }
            // Otherwise, we have seen this character, so increment its frequency for the 
            // current window.
            else {
                frequencyOfLetterInCurrentWindow[s[end]] += 1;
            }

            // If the frequency of this character is greater than the current highest 
            // frequency of a character in the window, then set the new highest frequency to 
            // be this one.
            if(frequencyOfLetterInCurrentWindow[s[end]] > highestFrequencyInCurrentWindow) {
                highestFrequencyInCurrentWindow = frequencyOfLetterInCurrentWindow[s[end]];
            } 

            // Calculate the size of the window.
            int windowLength = end - start + 1;
            // Get the number of characters in the window that aren't character with the 
            // highest frequency in the window.
            int numLettersInWindowThatArentMaxFreqLetter 
                = windowLength - highestFrequencyInCurrentWindow;
            // If the number of characters in the window that aren't the character with the 
            // highest frequency doesn't exceed k, then see if this window size is larger than 
            // our current longest possible repeating character string stored in longest; if 
            // so, then set longest to this new length.
            if(numLettersInWindowThatArentMaxFreqLetter <= k) {
                if(windowLength > longest) {
                    longest = windowLength;
                }
            }
            // Otherwise, the number of characters in the window that aren't the character 
            // with the highest frequency does exceed k, so that means this window is invalid, 
            // since it's impossible to have a repeating character string the size of this 
            // window, as even the character with the highest frequency would need >k 
            // replacements to be a repeating character string the size of this window.
            else {
                // Therefore, we have to shrink the window, so we first decrement the 
                // frequency of the character we're going to push out of the window i.e. the 
                // character at the start index.
                frequencyOfLetterInCurrentWindow[s[start]]--;
                // Then increment start to move the window forward and push out the character 
                // at the start index, thereby shrinking the window by one character.
                start++;
            }
        }

        return longest;
    }
};

// class Solution {
// public:
//     int characterReplacement(string s, int k) {
//         int longest = 0;

//         unordered_map<char, int> longestForLetterAtLastSeen;
//         unordered_map<char, int> usesLeftForLetter;
//         unordered_map<char, int> indexOfLetterAtLastSeen;
//         unordered_map<char, int> lengthOfRunOfLetterAtLastSeen;
//         unordered_map<char, deque<int>> gapDeck;
//         unordered_map<char, deque<int>> runDeck;

//         for(int i = 0; i < s.size(); i++) {
//             if(longestForLetterAtLastSeen.find(s[i]) != longestForLetterAtLastSeen.end()) {
//                 int distance = i - indexOfLetterAtLastSeen[s[i]] - 1;

//                 if(usesLeftForLetter[s[i]] >= distance) {
//                     longestForLetterAtLastSeen[s[i]] += 1;
//                     usesLeftForLetter[s[i]] -= distance;
//                 }
//                 else {
//                     while(!gapDeck[s[i]].empty()) {
//                         usesLeftForLetter[s[i]] += gapDeck[s[i]].front();
//                         longestForLetterAtLastSeen[s[i]] -= runDeck[s[i]].front();
//                         gapDeck[s[i]].pop_front();
//                         runDeck[s[i]].pop_front();
//                         if(usesLeftForLetter[s[i]] >= distance) {
//                             break;
//                         }
//                     }

//                     if(usesLeftForLetter[s[i]] >= distance) {
//                         longestForLetterAtLastSeen[s[i]] += 1;
//                         usesLeftForLetter[s[i]] -= distance;
//                     }
//                     else {
//                         longestForLetterAtLastSeen[s[i]] = k + 1;
//                     }
//                 }

//                 if(distance == 0) {
//                     lengthOfRunOfLetterAtLastSeen[s[i]] += 1;
//                 }
//                 else if(distance <= k) {
//                     runDeck[s[i]].push_back(lengthOfRunOfLetterAtLastSeen[s[i]]);
//                     gapDeck[s[i]].push_back(distance);
//                     lengthOfRunOfLetterAtLastSeen[s[i]] = 1;
//                 }
//             }
//             else {
//                 longestForLetterAtLastSeen[s[i]] = k + 1;
//                 usesLeftForLetter[s[i]] = k;
//                 lengthOfRunOfLetterAtLastSeen[s[i]] = 1;
//                 runDeck[s[i]] = {};
//                 gapDeck[s[i]] = {};
//             }

//             indexOfLetterAtLastSeen[s[i]] = i;

//             if(longestForLetterAtLastSeen[s[i]] > longest) {
//                 longest = longestForLetterAtLastSeen[s[i]];
//             }
//         }

//         if(longest >= s.size()) {
//             return s.size();
//         }

//         return longest;
//     }
// };

// class Solution {
// public:
//     int characterReplacement(string s, int k) {
//         int longest = 0;

//         unordered_map<char, int> longestForLetter;

//         for(int i = 0; i < s.size(); i++) {
//             int length = k;
//             int counter = k;
//             for(int j = i; j < s.size(); j++) {
//                 if(s[j] == s[i]) {
//                     length++;
//                 }
//                 else if(counter > 0) {
//                     counter--;
//                 }
//                 else {
//                     break;
//                 }
//             }

//             if(length > longest) {
//                 longest = length;
//             }
//         }

//         if(longest >= s.size()) {
//             return s.size();
//         }

//         return longest;
//     }
// };