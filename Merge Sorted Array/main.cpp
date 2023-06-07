class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        // An in-place solution (no need for a lot of additional memory)

        // Our algorithm works like this: we're going to populate nums1 with the merged 
        // solution starting FROM THE BACK (good idea to consider whether going forwards 
        // or backwards for these problems is better when doing an coding challenge). By 
        // iterating from the back, we're taking advantage of the fact that by going 
        // backwards we are replacing the 0's in nums1 first, so we don't accidentally 
        // overwite any values that we need for comparison later down the line; this is what 
        // allows us do this in-place.
        int size = m + n;
        // Here, i tracks which number we're currently comparing from nums1, j tracks which 
        // number we're currently comparing from nums2, and k tracks which index in nums1 
        // we're currently populating for our solution.
        for(int i = m-1, j = n-1, k = size - 1; k >= 0;) {
            // If j is less than 0, we know the rest of the solution will be populated by 
            // only the remaining numbers in nums1
            // Or, if j is not less than 0, we have to do comparison, so check that i is still 
            // a valid index and do the comparison
            if(j < 0 || (i >= 0 && nums1[i] >= nums2[j])) {
                nums1[k] = nums1[i];
                k--;
                i--;
            }
            // If i is less than 0, we know the rest of the solution will be populated by 
            // only the remaining numbers in nums2
            // Or, if i is not less than 0, we have to do comparison, so check that j is still 
            // a valid index and do the comparison
            else if(i < 0 || (j >= 0 && nums2[j] >= nums1[i])) {
                nums1[k] = nums2[j];
                k--;
                j--;
            }
        }

        return;
    }
};