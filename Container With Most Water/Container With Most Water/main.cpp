//
//  main.cpp
//  Container With Most Water
//
//  Created by Jason Lai on 11/2/19.
//  Copyright © 2019 Jason Lai. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int area = 0;
        
        // Compression; start from the outside in
        int LHS = 0;
        int RHS = height.size()-1;
        while(LHS != RHS) {
            // Calculate area using the current left and right sides
            int temp_area = min(height[LHS], height[RHS]) * (RHS - LHS);
            area = max(area, temp_area);
            
            // If the left is taller than the right, move to next right vice versa
            if(height[LHS] > height[RHS]) {
                RHS--;
            }
            else {
                LHS++;
            }
        }
        
        return area;
        
        // Could use dynamic programming?
    }
};
