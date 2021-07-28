#include <string>
#include <deque>

using namespace std;

// Iterative process:
// 1. First we moved the for loop that parses a number from a string from the recursive deserialize_helper into deserialize
        // Instead of keeping the numbers in the string, we parse the strings into numbers and push them into a deque
        // We replace the numbers in the strings with the letter 'n'
// 2. Instead of shrinking the string in deserialize_helper using data.substr(2), we instead keep track of an index counter

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
public:
    
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(root == NULL) {
            return "?";
        }

        return std::to_string(root->val) + "|" + serialize(root->left) + "|" + serialize(root->right);
    }

    std::pair<TreeNode*, int> deserialize_helper(string data, int index, deque<int>& values) {
        TreeNode* root = NULL;

        if(index >= data.size()) {
            return std::make_pair(root, index = data.size());
        }

        if(data[index] == '?') {
            if(data.size() > 2) {
                return std::make_pair(root, index += 2);
            }
            else {
                return std::make_pair(root, index = data.size());
            }
        }

        root = new TreeNode(values.front());
        values.pop_front();

        pair<TreeNode*, int> left_subtree = deserialize_helper(data, index += 2, values);
        root->left = left_subtree.first;

        pair<TreeNode*, int> right_subtree = deserialize_helper(data, left_subtree.second, values);
        root->right = right_subtree.first;

        return std::make_pair(root, right_subtree.second);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        deque<int> tree_values;

        string parsed_data = "";
        string val = "";
        bool is_number = true;
        for(int i = 0; i < data.size(); i++) {
            if(data[i] == '|') {
                if(is_number) {
                    tree_values.push_back(stoi(val));
                    parsed_data += 'n';   
                    val = "";
                }
                parsed_data += data[i];
            }
            else if(data[i] == '?') {
                is_number = false;
                parsed_data += data[i];
            }
            else {
                is_number = true;
                val += data[i];
            }
        }

        pair<TreeNode*, int> tree = deserialize_helper(parsed_data, 0, tree_values);

        return tree.first;
    }
    
    
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));