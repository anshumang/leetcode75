You are given the root of a binary search tree (BST) and an integer val.

Find the node in the BST that the node's value equals val and return the subtree rooted with that node. If such a node does not exist, return null.

Example 1:
Input: root = [4,2,7,1,3], val = 2
Output: [2,1,3]
Example 2:
Input: root = [4,2,7,1,3], val = 5
Output: []
 

Constraints:

The number of nodes in the tree is in the range [1, 5000].
1 <= Node.val <= 107
root is a binary search tree.
1 <= val <= 107

#include <cstddef> // Required for NULL or nullptr
#include <iostream>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        // Base case: if the root is null or the value is found
        if (root == nullptr || root->val == val) {
            return root;
        }

        // If the value is less than the current node's value, search in the left subtree
        if (val < root->val) {
            return searchBST(root->left, val);
        }
        // If the value is greater than the current node's value, search in the right subtree
        else {
            return searchBST(root->right, val);
        }
    }
};

To provide the C++ code for searching in a Binary Search Tree, I need to define the TreeNode structure first. Then, I can implement the searchBST function.

Here's the C++ code:

C++

#include <cstddef> // Required for NULL or nullptr
#include <iostream>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        // Base case: if the root is null or the value is found
        if (root == nullptr || root->val == val) {
            return root;
        }

        // If the value is less than the current node's value, search in the left subtree
        if (val < root->val) {
            return searchBST(root->left, val);
        }
        // If the value is greater than the current node's value, search in the right subtree
        else {
            return searchBST(root->right, val);
        }
    }
};

// --- Helper function to build a BST for testing ---
// This is a simple insertion for building a BST, not necessarily balanced.
TreeNode* insertIntoBST(TreeNode* root, int val) {
    if (root == nullptr) {
        return new TreeNode(val);
    }
    if (val < root->val) {
        root->left = insertIntoBST(root->left, val);
    } else {
        root->right = insertIntoBST(root->right, val);
    }
    return root;
}

// --- Helper function to print a BST (in-order traversal for verification) ---
void printInOrder(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    printInOrder(root->left);
    std::cout << root->val << " ";
    printInOrder(root->right);
}

// --- Helper function to print a BST as a level-order traversal (for visual matching with LeetCode's array representation) ---
// This is a simplified version and doesn't handle null nodes perfectly for strict array representation.
// For truly matching LeetCode's array format, a queue-based level-order traversal is needed
// that also queues nulls and stops when all subsequent nodes are nulls.
// This is just to give a better sense of the tree structure.
#include <queue>
void printLevelOrder(TreeNode* root) {
    if (root == nullptr) {
        std::cout << "[]" << std::endl;
        return;
    }

    std::queue<TreeNode*> q;
    q.push(root);

    std::cout << "[";
    bool first = true;

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();

        if (!first) {
            std::cout << ",";
        }
        first = false;

        if (current) {
            std::cout << current->val;
            q.push(current->left);
            q.push(current->right);
        } else {
            std::cout << "null";
        }
    }
    std::cout << "]" << std::endl;
}

// --- Main function for testing ---
int main() {
    Solution sol;

    // Example 1: root = [4,2,7,1,3], val = 2
    TreeNode* root1 = nullptr;
    root1 = insertIntoBST(root1, 4);
    root1 = insertIntoBST(root1, 2);
    root1 = insertIntoBST(root1, 7);
    root1 = insertIntoBST(root1, 1);
    root1 = insertIntoBST(root1, 3);

    std::cout << "Tree 1 (In-order): ";
    printInOrder(root1);
    std::cout << std::endl;

    std::cout << "Tree 1 (Level-order - simplified): ";
    printLevelOrder(root1);

    TreeNode* result1 = sol.searchBST(root1, 2);
    std::cout << "Search for 2: ";
    if (result1) {
        std::cout << "Found subtree (root val): " << result1->val << std::endl;
        std::cout << "Subtree (In-order): ";
        printInOrder(result1);
        std::cout << std::endl;
    } else {
        std::cout << "Not found (nullptr)" << std::endl;
    }

    std::cout << "------------------------------------" << std::endl;

    // Example 2: root = [4,2,7,1,3], val = 5
    TreeNode* root2 = nullptr;
    root2 = insertIntoBST(root2, 4);
    root2 = insertIntoBST(root2, 2);
    root2 = insertIntoBST(root2, 7);
    root2 = insertIntoBST(root2, 1);
    root2 = insertIntoBST(root2, 3);

    std::cout << "Tree 2 (In-order): ";
    printInOrder(root2);
    std::cout << std::endl;
    std::cout << "Tree 2 (Level-order - simplified): ";
    printLevelOrder(root2);


    TreeNode* result2 = sol.searchBST(root2, 5);
    std::cout << "Search for 5: ";
    if (result2) {
        std::cout << "Found subtree (root val): " << result2->val << std::endl;
    } else {
        std::cout << "Not found (nullptr)" << std::endl;
    }

    // Remember to free memory in a real application
    // (not done here for brevity in a simple example)
    return 0;
}
Explanation:

TreeNode Structure:

This defines the structure of a node in the binary tree. Each node has:
val: An integer representing the node's value.
left: A pointer to the left child node.
right: A pointer to the right child node.
Constructors are provided for easy initialization.
Solution Class and searchBST Method:

The searchBST function takes two arguments:
root: A pointer to the current node being examined in the BST. Initially, it's the root of the entire tree.
val: The integer value we are searching for.
Base Cases:
if (root == nullptr || root->val == val):
If root is nullptr (we've reached the end of a branch without finding val), return nullptr.
If root->val is equal to val (we found the node), return root (which is the pointer to the found node, serving as the root of the desired subtree).
Recursive Steps (Leveraging BST Property):
if (val < root->val): If the val we are looking for is smaller than the current node's value, it must be in the left subtree (if it exists). So, recursively call searchBST on
  root->left.
else { return searchBST(root->right, val); }: If the val we are looking for is greater than the current node's value, it must be in the right subtree. So, recursively call
  searchBST on root->right.
How it works (BST property):

The core idea is to leverage the property of a Binary Search Tree:

All values in the left subtree of a node are less than the node's value.
All values in the right subtree of a node are greater than the node's value.
This allows us to efficiently prune the search space by deciding whether to go left or right at each node, rather than having to check every node (like in a general binary tree).
This leads to a time complexity of O(h) where 'h' is the height of the tree (O(log N) in a balanced BST, O(N) in a skewed BST).
