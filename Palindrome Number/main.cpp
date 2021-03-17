//
//  main.cpp
//  Palindrome Number
//
//  Created by Jason Lai on 11/2/19.
//  Copyright © 2019 Jason Lai. All rights reserved.
//

#include <iostream>

class Solution {
public:
    bool isPalindrome(int x) {
        // If it's negative, it won't be a palindrome
        if(x < 0)
            return false;
        
        // Uses same logic as reverse integer
        int num = x;
        int rev = 0;
        
        while(num != 0) {
            if(rev < INT_MIN/10 || rev > INT_MAX/10) { return false; }
            
            rev = (rev * 10) + (num % 10);
            num /= 10;
        }
        
        // Check if the reversed integer equals the input
        return rev == x;
        
        // A better way to do this without the issue of overflow?
        // Maybe use mod to separate digits into an STL data structure the compare iterators;
        // one from the beginning, the other from the end
    }
};
