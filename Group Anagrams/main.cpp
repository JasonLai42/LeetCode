#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // The groups of anagrams
        vector<vector<string>> groups;
        
        // Hash table that takes a sorted string (alphabetical) as a key and have an int as a value; the int is the index
        // of groups that pertains to the group of anagrams this string belongs to
        unordered_map<string, int> anagram_to_group;
        for(int i = 0; i < strs.size(); i++) {
            // Sort the string
            string key = strs[i];
            sort(key.begin(), key.end());
            
            // If this anagram group hasn't been made yet, make it
            if(anagram_to_group.find(key) == anagram_to_group.end()) {
                anagram_to_group[key] = groups.size();
                groups.push_back({ strs[i] });
            }
            // Else, this anagram group exists so put it in the appropriate group
            else {
                groups[anagram_to_group[key]].push_back(strs[i]);
            }
        }
        
        return groups;
    }
};