#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int kth_largest = 0;
        
        // Create a Max Heap; O(N) when initialized with a vector through Floyd's Algorithm
        priority_queue<int, vector<int>, less<int>> pq(nums.begin(), nums.end());
        
        // Pop elements till we get to the kth element; that's the kth largest element
        int n = 0;
        while(n != k) {
            n++;
            if(n == k)
                kth_largest = pq.top();
            pq.pop();
        }
        
        return kth_largest;
    }
};