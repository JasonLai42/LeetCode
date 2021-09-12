#include <string>

using namespace std;

class Solution {
public:
    // Get if there is a carry for this addition
    bool getCarry(char a, char b, bool carry) {
        if((a == '1' && b == '1') || (carry && a == '1') || (carry && b == '1')) {
            return true;
        }
        else {
            return false;
        }
    }
    
    // Get the character we insert into the sum at this point (either 0 or 1) i.e. do the addition
    char addHelper(char a, char b, bool carry) {
        if(a == '1' && b == '1') {
            if(carry) {
                return '1';
            }
            else {
                return '0';
            }
        }
        else if(a == '0' && b == '0') {
            if(carry) {
                return '1';
            }
            else {
                return '0';
            }
        }
        else {
            if(carry) {
                return '0';
            }
            else {
                return '1';
            }
        }
    }
    
    string addBinary(string a, string b) {
        string sum = "";
        
        int aIndex = a.size() - 1;
        int bIndex = b.size() - 1;
        bool carry = false;
        while(aIndex >= 0 || bIndex >= 0) {
            // If we haven't reached the end of either string
            if(aIndex >= 0 && bIndex >= 0) {
                sum = addHelper(a[aIndex], b[bIndex], carry) + sum;
                carry = getCarry(a[aIndex], b[bIndex], carry);
                
                aIndex--;
                bIndex--;
            }   
            // If we reached the end of b
            else if(aIndex >= 0) {
                sum = addHelper(a[aIndex], '0', carry) + sum;
                carry = getCarry(a[aIndex], '0', carry);
                
                aIndex--;
            }
            // If we reached the end of a
            else if(bIndex >= 0) {
                sum = addHelper('0', b[bIndex], carry) + sum;
                carry = getCarry('0', b[bIndex], carry);
                
                bIndex--;
            }
        }
        
        // If after the last values were added there was a character, add one more 1 to the sum
        if(carry) {
            sum = '1' + sum;
        }
        
        return sum;
    }
};