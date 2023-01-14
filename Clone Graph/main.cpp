/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    Node* cloneGraph(Node* node) {
        // Cloned graph we return
        // clone is a copy of node that's passed in as the argument of the function
        Node* clone;
        if(!node) {
            clone = NULL;
            return clone;
        } 
        else {
            clone = new Node(node->val);
        }

        // DFS/BFS? Let's try BFS
        // We need a fringe to add to for a queue of nodes we need to visit
        deque<Node*> fringe;
        fringe.insert(fringe.end(), node->neighbors.begin(), node->neighbors.end());

        // This deque stores the nodes that we have visited in the fringe but have yet to populate 
        // neighbors for
        // The front of this deque is the current node we're populating the neighbors for
        // Initially, this is our first node: clone
        deque<Node*> nodesThatNeedNeighbors;
        nodesThatNeedNeighbors.push_back(clone);
        // This deque stores the size of the neighbors vector for each of the nodes in the above 
        // deque: nodesThatNeedNeighbors in a 1:1 mapping
        // We track these numbers so we know when to stop adding nodes from the fringe to the 
        // currentNodeNeighbors vector in the loop below, because if currentNodeNeighbors is the 
        // same size as frontIsNumNeighborsOfCurrentNode.front(), then we know we have created a 
        // vector that contains all the neighbors of the node nodesThatNeedNeighbors.front()
        deque<int> frontIsNumNeighborsOfCurrentNode;
        frontIsNumNeighborsOfCurrentNode.push_back(node->neighbors.size());

        // Basically, this map tracks if we've visited a node before so we don't create a  
        // redundant copy of the current node we're visiting in the fringe i.e. fringe.front()
        // The key value is the pointer to a node in the original graph and the mapped value is 
        // the pointer the node that is the copy of that node in the original graph
        unordered_map<Node*, Node*> visitedNodes;
        visitedNodes[node] = clone;

        // currentNodeNeighbors is a vector that stores all the neighbors for the current node 
        // we populating for i.e. nodesThatNeedNeighbors.front()
        vector<Node*> currentNodeNeighbors;
        // While we still have nodes to visit in the fringe, we continue to search and copy
        while(!fringe.empty()) {
            // Have we visited this node before?
            unordered_map<Node*, Node*>::const_iterator findNode 
                = visitedNodes.find(fringe.front());
            if(findNode != visitedNodes.end()) {
                // If we've visited this node before, add the existing node copy to the vector
                currentNodeNeighbors.push_back(findNode->second);
            }
            else {
                // If we haven't visited this node before, create a copy, and add it to the vector 
                // and mark it as visited in the unordered_map
                Node* neighborNode = new Node(fringe.front()->val);
                currentNodeNeighbors.push_back(neighborNode);
                visitedNodes[fringe.front()] = neighborNode;

                // Append this new node's neighbors to the end of the fringe, so that we can visit 
                // them later and all also copy them
                fringe.insert(
                    fringe.end(), 
                    fringe.front()->neighbors.begin(), 
                    fringe.front()->neighbors.end());

                // Add this newly copied node to the nodesThatNeedNeighbors and add number of 
                // neighbors it has to frontIsNumNeighborsOfCurrentNode
                nodesThatNeedNeighbors.push_back(neighborNode);
                frontIsNumNeighborsOfCurrentNode.push_back(fringe.front()->neighbors.size());
            }

            // If currentNodeNeighbors is the same size as the number of neighbors this copied 
            // node had in the original graph, then we're done copying its neighbors and we can 
            // set the current node's neighbors member variable
            if(currentNodeNeighbors.size() == frontIsNumNeighborsOfCurrentNode.front()) {
                // Set the member variable
                nodesThatNeedNeighbors.front()->neighbors = currentNodeNeighbors;
                // Clear the vector for the next node we need to copy the neighbors for
                currentNodeNeighbors.clear();
                // The current node is now fully copied, so we can pop its values from the deques
                nodesThatNeedNeighbors.pop_front();
                frontIsNumNeighborsOfCurrentNode.pop_front();
            }

            // We're done processing this node, so pop it
            fringe.pop_front();
        }

        return clone;
    }
};