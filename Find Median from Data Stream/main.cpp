/* Time Complexity: O((3/2)nlogk) where k = n/2
 * Space Complexity: O(n)
 * The time complexity is O((3/2)nlogk) because for each of the n integers, we have to add 
 * them to the heap, which is a logn operation, but because the integers are divided evenly 
 * between two heaps, that means the operation becomes logk, where k = n/2, because each heap 
 * is half the size of n. We have the 3/2 there because, in the worst case, we might need to 
 * rebalance the heaps every other integer after the first one is added. Imagine the scenario 
 * where the second integer is put in the left heap with the first, so the sizes are 2:0, and 
 * we need to rebalance. After we rebalance, the sizes are now 1:1, so the third integer can 
 * be added to either heap and we'll have 2:1 or 1:2, so we're good. But then suppose the 
 * fourth integer gets added to the same heap as the third, making the sizes 3:1 or 1:3, 
 * which means we need to rebalance again. This pattern of rebalancing after every other 
 * integer could keep repeating, which means in the worst case, half the total number of 
 * integers n would need a rebalance, so we have O((n/2)logk). Add this to the O(nlogk) that 
 * we have from adding all the integers to a heap and we get the final complexity of 
 * O((3/2)nlogk).
 * The space complexity is just O(n) since we only store the n integers.
 */

class MedianFinder {
public:
    /* Since we want to keep track of the median, we want to keep track of the one or two 
     * middle values of the sorted list of numbers. We can use a min heap and max heap to 
     * make this easy. If we divide the list of sorted numbers down the middle and have 
     * the "left side" stored as a max heap and have the "right side" stored as a min heap,
     * then the top of both heaps will effectively be the middle values of the list. This is 
     * because the left side max heap has its top value as the largest value of the left side 
     * and the right side min heap has its top value as the smallest value of the right side, 
     * which are essentially the "middle values" of the sorted list. If the elements of both 
     * heaps were to be joined at these two specific values, we would generate the original 
     * sorted list. Therefore, we have all the info we need to calculate the median.
     */
    priority_queue<int> leftSide;
    priority_queue<int, vector<int>, greater<int>> rightSide;

    MedianFinder() {
        
    }
    
    void addNum(int num) {
        /* When the heaps are initially empty, we don't have any values to compare the very 
         * first num we're adding to, so we just default to sticking it in the left heap.
         */
        if(!leftSide.empty()) {
            /* Here, we simply put the integer in the right heap if it is larger than the 
             * largest number in the left heap, or put the integer in the left heap if it 
             * is less than or equal to the largest number in the left heap.
             * The reason for adding numbers in this fashion has no rationale other than that 
             * we MAY be able to save on a rebalancing operation if we somehow add the new 
             * integer to whichever heap is small (or they're the same size), thus keeping 
             * the heaps balanced. Beyond that, since we have no way of knowing what numbers 
             * are going to be added in the problem's range, we unfortunately have no 
             * surefire way of keep the heaps balanced as we go, so adding integers in this 
             * manner is just purely guesswork.
             */
            if(num > leftSide.top()) {
                rightSide.push(num);
            }
            else {
                leftSide.push(num);
            }
        }
        else {
            leftSide.push(num);
        }
        /* In order to maintain that the top() values of both heaps are always the "middle 
         * values" we have to ensure that both heaps are within +1 size of each other (same 
         * size if even total, +1 size on either heap if odd total). This means we have to 
         * check if the heaps need rebalancing after each num that gets added.
         */
        rebalanceHeaps();

        return;
    }

    void rebalanceHeaps() {
        int leftSize = leftSide.size();
        int rightSize = rightSide.size();
        /* Here, we basically check if one of the heaps has two more elements than the other 
         * which means the total number of integers is no longer divided evenly amongst the 
         * two heaps, so we have to rebalance them. That entails just taking the top() value 
         * from the heap that has one-too-many integers and giving it to the other heap.
         */
        if(abs(leftSize - rightSize) > 1) {
            if(leftSize > rightSize) {
                rightSide.push(leftSide.top());
                leftSide.pop();
            }
            else {
                leftSide.push(rightSide.top());
                rightSide.pop();
            }
        }
    }
    
    double findMedian() {
        double median;

        int leftSize = leftSide.size();
        int rightSize = rightSide.size();
        /* If the left and right heaps are of the same size, we know the number of integers 
         * we have total is even, so calculate the median using the two top() values.
         */
        if(leftSize == rightSize) {
            median = ((double)leftSide.top() + (double)rightSide.top()) / 2.0;
        }
        /* If the left and right heaps are of different sizes, we know the number of integers 
         * we have total is odd, which means that one of the "middle values" in either the 
         * left heap or the right heap is the true median, so take whichever heap is larger, 
         * and the top() value of that heap should be the median.
         */
        else {
            if(leftSize > rightSize){
                median = (double)leftSide.top();
            }
            else {
                median = (double)rightSide.top();
            }
        }

        return median;
    }
};

// struct Node {
//     Node *prev;
//     Node *next;
//     int val;
//     Node(int x) : val(x), prev(nullptr), next(nullptr) {}
// };

// class MedianFinder {
// public:
//     Node *numsTail;
//     int listSize;
//     Node *medianNode;
//     double median;

//     MedianFinder() {
//         numsTail = nullptr;
//         listSize = 0;
//     }
    
//     void addNum(int num) {
//         Node *numNode = new Node(num);

//         if(listSize > 0) {
//             bool isRightSideOfMedian = true;

//             if(num > numsTail->val) {
//                 numNode->prev = numsTail;
//                 numsTail->next = numNode;
//                 numsTail = numNode;
//             }
//             else {
//                 Node *current = numsTail;
//                 while(current != nullptr) {
//                     if(current == medianNode) {
//                         isRightSideOfMedian = false;
//                     }

//                     if(num <= current->val) {
//                         if(current->prev != nullptr) {
//                             current->prev->next = numNode;
//                         }

//                         numNode->prev = current->prev;
//                         numNode->next = current;

//                         current->prev = numNode;
//                     }

//                     current = current->prev;
//                 }
//             }
//             listSize++;

//             if(isRightSideOfMedian) {
//                 if(listSize % 2 == 0) {
//                     median = ((double)medianNode->val + (double)medianNode->next->val) / 2.0;
//                 }
//                 else {
//                     medianNode = medianNode->next;
//                     median = medianNode->val;
//                 }
//             }
//             else {
//                 if(listSize % 2 == 0) {
//                     medianNode = medianNode->prev;
//                     median = ((double)medianNode->val + (double)medianNode->next->val) / 2.0;
//                 }
//                 else {
//                     median = medianNode->val;
//                 }
//             }
//         }
//         else {
//             numsTail = numNode;
//             listSize++;

//             medianNode = numNode;
//             median = (double)num;
//         }
//     }
    
//     double findMedian() {
//         return median;
//     }
// };

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */