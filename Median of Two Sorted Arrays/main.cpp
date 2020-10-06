#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        
        // Two sorted arrays of size m and n
        // Supposed to run in O(log(m + n)), but this doesn't
        int total_num = nums1.size() + nums2.size();
        double median;
        
        // Odd number of elements
        if(total_num % 2 > 0) {
            int i = 0;
            while(i < (total_num / 2) + 1) {
                if(nums1.empty()) {
                    median = nums2.back();
                    nums2.pop_back();
                }
                else if(nums2.empty()) {
                    median = nums1.back();
                    nums1.pop_back();
                }
                else {
                    if(nums1.back() > nums2.back()) {
                        median = nums1.back();
                        nums1.pop_back();
                    }
                    else  {
                        median = nums2.back();
                        nums2.pop_back();
                    }
                }
                
                i++;
            }
        } 
        // Even number of elements
        else {
            double term1 = 0;
            double term2 = 0;
            
            int i = 0;
            while(i < (total_num / 2) + 1) {
                if(nums1.empty()) {
                    term1 = term2;
                    term2 = nums2.back();
                    nums2.pop_back();
                }
                else if(nums2.empty()) {
                    term1 = term2;
                    term2 = nums1.back();
                    nums1.pop_back();
                }
                else {
                    if(nums1.back() > nums2.back()) {
                        term1 = term2;
                        term2 = nums1.back();
                        nums1.pop_back();
                    }
                    else  {
                        term1 = term2;
                        term2 = nums2.back();
                        nums2.pop_back();
                    }
                }
                
                i++;
            }
            
            median = (term1 + term2) / 2.0;
        }
        
        return median;
    }
};