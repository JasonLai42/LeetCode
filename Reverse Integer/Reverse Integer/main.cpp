//
//  main.cpp
//  Reverse Integer
//
//  Created by Jason Lai on 11/2/19.
//  Copyright © 2019 Jason Lai. All rights reserved.
//

#include <iostream>

class Solution {
public:
    int reverse(int x) {
        int final_num = 0;
        
        while(x != 0) {
            // Check oveflow
            if(final_num > INT_MAX/10 || final_num < INT_MIN/10) { return 0; }
            
            // Move existing numbers a magnitude over and add new number to ones place
            final_num = (final_num * 10) + (x % 10);
            
            // Truncate previously added number
            x /= 10;
        }
        
        return final_num;
    }
};
