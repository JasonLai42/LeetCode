#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    
    // Pass result vector in by reference, current keeps track of the string we're building, left/right_pars counts the number
    // those respective pars we've used so far, and n is the number of pairs and therefore left/right_pars we should have
    void get_combinations(vector<string>& combs, string current, int left_pars, int right_pars, int n) {
        // If we have n left_pars and n right_pars, we've formed a valid string with n pairs, so add it to the vector and return
        if(left_pars == n && right_pars == n) {
            combs.push_back(current);
            return;
        }
        
        // If we still have less than n left_pars, we can put a left_par here, so try it
        if(left_pars < n) {
            get_combinations(combs, current + "(", left_pars + 1, right_pars, n);    
        }
        // If we still have less than n right_pars, we might be able to put a right_par here
        // Only if these is less right_pars than left_pars; if there is a less or equal amount of left_pars to right_pars, we 
        // can't put a right_par here because it would be unmatched, so don't try it
        if(right_pars < n && right_pars < left_pars) {
            get_combinations(combs, current + ")", left_pars, right_pars + 1, n);
        }
    }
    
    vector<string> generateParenthesis(int n) {
        vector<string> combinations;
        
        // We know the string has to start with a left_par
        get_combinations(combinations, "(", 1, 0, n);
        
        return combinations;
    }
};