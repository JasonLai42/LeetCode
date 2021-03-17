//
//  main.cpp
//  Roman to Integer
//
//  Created by Jason Lai on 11/2/19.
//  Copyright © 2019 Jason Lai. All rights reserved.
//

#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int romanToInt(string s) {
        
        // Index the roman numeral mappings
        unordered_map<char, int> roman_to_int;
        roman_to_int['I'] = 1;
        roman_to_int['V'] = 5;
        roman_to_int['X'] = 10;
        roman_to_int['L'] = 50;
        roman_to_int['C'] = 100;
        roman_to_int['D'] = 500;
        roman_to_int['M'] = 1000;
        
        int final_num = 0;
        int last = 0;
        for(int i = 0; i < s.length(); i++) {
            // If the current numeral is greater than the last, add difference to sum
            if(roman_to_int[s[i]] > last) {
                final_num += (roman_to_int[s[i]] - (2*last));
            }
            else {
                final_num += roman_to_int[s[i]];
            }
            last = roman_to_int[s[i]];
        }
        
        return final_num;
    }
};
