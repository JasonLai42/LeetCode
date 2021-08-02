#include <string>

using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        int index = -1;
        if(needle.size() == 0) {
            return 0;
        }
        if(needle.size() > haystack.size()) {
            return index;
        }
        
        for(int i = 0; i < haystack.size() - needle.size() + 1; i++) {
            if(haystack[i] == needle[0]) {
                string str = haystack.substr(i, needle.size());
                
                if(str == needle) {
                    index = i;
                    break;
                }
            }
        }
        
        return index;
    }
};