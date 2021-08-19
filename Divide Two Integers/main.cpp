#include <stdlib.h>

using namespace std;

int subOvf(int a, int b) 
{ 
    int result = a - b; 
    if(a > 0 && b > 0 && result < 0) 
        return -1; 
    if(a < 0 && b < 0 && result > 0) 
        return -1; 
    return 0; 
} 

class Solution {
public:
    int divide(int dividend, int divisor) {
        long quotient = 1;
        
        bool isNegative = false;
        if((dividend < 0 && divisor >= 0) || (dividend >= 0 && divisor < 0))
            isNegative = true;
        
        long y = abs(dividend);
        long x = abs(divisor);
        
        if(y < x)
            return 0;
        
        for(int i = 0; i < 32; i++) {
            quotient =  quotient << 1;
            x = x << 1;
            
            if(x > y) {
                quotient =  quotient >> 1;
                x = x >> 1;
                y -= x;
                break;
            }
        }
        
        while(y >= abs(divisor)) {
            quotient++;
            y -= abs(divisor);
        }
        
        if(isNegative)
            quotient = -quotient;
        
        return (quotient < INT_MIN || quotient > INT_MAX) ? INT_MAX : quotient;
    }
};