/* Time Complexity: O(n)
 * Space Complexity: O(n)
 * Peeked solution. Simple, but not super intuitive imo. Basically we push each temp (or rather their index) onto a stack 
 * and at the start of each iteration, we compare the current temperature to the ones in the stack and if the top element 
 * of the stack is less than the current temperature then we pop. We keep popping elements that are less than the current 
 * temperature until either we find a temp in the stack that is greater than the current temperature or the stack is 
 * empty. If we find a temp that is greater, we use the index of that temp to calculate the distance in days from the 
 * current temperature. The time complexity of this solution is O(n) because the outer loop visits every temp once and 
 * the inner loop visits every temp once as well so we have O(n+n) which is O(n). The space complexity is O(n) because we 
 * use a stack.
 */
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> result(temperatures.size(), 0);

        stack<int> tempIndices;
        for(int i = temperatures.size()-1; i >= 0; i--) {
            while(!tempIndices.empty() && temperatures[tempIndices.top()] <= temperatures[i])
                tempIndices.pop();

            if(!tempIndices.empty())
                result[i] = tempIndices.top()-i;

            tempIndices.push(i);
        }

        return result;
    }
};

// Brute force solution
// class Solution {
// public:
//     vector<int> dailyTemperatures(vector<int>& temperatures) {
//         vector<int> result(temperatures.size(), 0);

//         for(int i = 0; i < temperatures.size(); i++) {
//             int dayCounter = 0;
//             for(int j = i + 1; j < temperatures.size(); j++) {
//                 dayCounter++;
//                 if(temperatures[j] > temperatures[i]) {
//                     result[i] = dayCounter;
//                     break;
//                 }
//             }
//         }

//         return result;
//     }
// };