/* Time Complexity: O(1) for each function
 * Space Complexity: O(n)
 * The solution couples each val pushed onto the stack with the minimum value in the stack seen thus far. This is useful 
 * because when we pop the minimum value, all the values under it in the stack will have the next minimum value.
 */
class MinStack {
public:
    stack<pair<int, int>> minstack;
    
    MinStack() {

    }
    
    void push(int val) {
        if(minstack.empty()) {
            minstack.push({val, val});
        }
        else {
            minstack.push({val, min(val, minstack.top().second)});
        }
    }
    
    void pop() {
        minstack.pop();
    }
    
    int top() {
        return minstack.top().first;
    }
    
    int getMin() {
        return minstack.top().second;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */