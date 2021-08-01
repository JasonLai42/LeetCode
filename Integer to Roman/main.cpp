#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    string intToRoman(int num) {
        string roman_result = "";
        
        // Index to store the roman numeral representation of our integers
        unordered_map<int, string> int_to_roman({   { 1, "I"    },
                                                    { 4, "IV"   },
                                                    { 5, "V"    },
                                                    { 9, "IX"   },
                                                    { 10, "X"   },
                                                    { 40, "XL"  },
                                                    { 50, "L"   },
                                                    { 90, "XC"  },
                                                    { 100, "C"  },
                                                    { 400, "CD" },
                                                    { 500, "D"  },
                                                    { 900, "CM" },
                                                    { 1000, "M" }
                                                });
        
        // We're going to solve this greedily, so we have an array with the possible integers ordered from greatest 
        // to least
        vector<int> largest_to_smallest = { 1000, 
                                            900, 
                                            500, 
                                            400, 
                                            100, 
                                            90, 
                                            50, 
                                            40, 
                                            10, 
                                            9, 
                                            5, 
                                            4,
                                            1 };
        
        // num_index is a counter used to track where we are in largest_to_smallest
        // val is just a copy of the argument num (not really needed, but helps with clarity imo)
        // Our greedy algorithm works as follows: divide val by the number in largest_to_smallest we are currently on
        // If we can "fit" this number into val once or more, then we append the roman numeral for that number to the 
        // end of our string and decrement val by that number
        // If we can't divide val by this number (all we have is remainders), then we increment num_index and try the 
        // next largest number
        int num_index = 0;
        int val = num;
        while(val > 0) {
            if(val / largest_to_smallest[num_index] > 0) {
                val -= largest_to_smallest[num_index];
                roman_result += int_to_roman[largest_to_smallest[num_index]];
            }
            else {
                num_index++;
            }
        }
        
        return roman_result;
    }
};