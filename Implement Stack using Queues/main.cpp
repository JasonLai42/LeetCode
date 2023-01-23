// ONE QUEUE SOLUTION
class MyStack {
public:
    queue<int> myQueue;

    MyStack() {}
    
    void push(int x) {
        myQueue.push(x);
        return;
    }
    
    int pop() {
        unsigned counter = 1;
        const unsigned queueSize = myQueue.size();
        while(counter != queueSize) {
            myQueue.push(myQueue.front());
            myQueue.pop();
            counter++;
        }
        int topStackNum = myQueue.front();
        myQueue.pop();

        return topStackNum;
    }
    
    int top() {
        return myQueue.back();
    }
    
    bool empty() {
        return myQueue.empty();
    }
};

// TWO QUEUE SOLUTION
// class MyStack {
// public:
//     queue<int> primary;
//     queue<int> secondary;

//     MyStack() {}
    
//     void push(int x) {
//         primary.push(x);
//         return;
//     }
    
//     int pop() {
//         int topStackNum = primary.back();
//         while(!primary.empty()) {
//             if(primary.size() > 1) {
//                 secondary.push(primary.front());
//             }
//             primary.pop();
//         }
//         while(!secondary.empty()) {
//             primary.push(secondary.front());
//             secondary.pop();
//         }

//         return topStackNum;
//     }
    
//     int top() {
//         return primary.back();
//     }
    
//     bool empty() {
//         return primary.empty();
//     }
// };

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */