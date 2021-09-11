#include <string>

using namespace std;

class Solution {
public:
    
    string countAndSayHelper(string nth, int m, int n) {
        if(m == n) {
            return nth;
        }
        
        string next = "";
        char current = nth[0];
        int count = 0;
        for(int i = 0; i <= nth.size(); i++) {
            if(i == nth.size() || nth[i] != current) {
                next = next + to_string(count) + current;
                
                if(i == nth.size()) {
                    break;
                }
                
                current = nth[i];
                count = 1;
            }
            else {
                count++;
            }
        }
        
        return countAndSayHelper(next, m + 1, n);
    }
    
    string countAndSay(int n) {
        return countAndSayHelper("1", 1, n);
    }
};