//
//  main.cpp
//  ZigZag Conversion
//
//  Created by Jason Lai on 11/2/19.
//  Copyright © 2019 Jason Lai. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        // Base case for simple output
        if(numRows == 1) {
            return s;
        }
        
        string zig_zag = "";
        
        // Holds the sequence for each row
        string rows[numRows];
        int rows_populated = false;
        
        // Keeps track of what row to write to
        int count = 0;
        int max_row = numRows - 1;
        int incr = true;
        
        for(int i = 0; i < s.length(); i++) {
            // Bounce the count if we hit max or min row
            if(count == max_row) {
                incr = false;
                rows_populated = true;
            }
            else if(count == 0) {
                incr = true;
            }
            
            // Add characters according to row
            if(!rows_populated) {
                rows[count] = "";
                rows[count] += s[i];
            }
            else {
                rows[count] += s[i];
            }
            
            // Increment or decrement the count depending on place in zig zag
            if(incr)
                count++;
            else
                count--;
        }
        
        // Append the rows for output
        for(int i = 0; i < numRows; i++) {
            zig_zag += rows[i];
        }
        
        return zig_zag;
    }
};
