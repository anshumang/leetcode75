We run a preorder depth-first search (DFS) on the root of a binary tree.

At each node in this traversal, we output D dashes (where D is the depth of this node), then we output the value of this node.  If the depth of a node is D, the depth of its immediate child is D + 1.  The depth
of the root node is 0.

If a node has only one child, that child is guaranteed to be the left child.

Given the output traversal of this traversal, recover the tree and return its root.

Example 1:
Input: traversal = "1-2--3--4-5--6--7"
Output: [1,2,5,3,4,6,7]

Example 2:
Input: traversal = "1-2--3---4-5--6---7"
Output: [1,2,5,3,null,6,null,4,null,7]

Example 3:
Input: traversal = "1-401--349---90--88"
Output: [1,401,null,349,88,90]

Constraints:

The number of nodes in the original tree is in the range [1, 1000].
1 <= Node.val <= 109

Accepted
157,320/188.8K
Acceptance Rate
83.3%

Topics
String
Tree
Depth-First Search
Binary Tree

Hint 1
Do an iterative depth first search, parsing dashes from the string to inform you how to link the nodes together.

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cctype>
#include <utility>

// Definition for a binary tree node, as commonly used in LeetCode.
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
    /**
     * @brief Recovers a binary tree from a string representation of its preorder traversal.
     *
     * The method works in two main steps:
     * 1. Parsing: The input string is parsed into a vector of pairs, where each
     * pair contains the depth and value of a node.
     * 2. Reconstruction: An iterative approach using a stack is employed to build
     * the tree. The stack maintains the current path from the root. For each new
     * node, we pop from the stack until we find its correct parent, which will
     * be the node at the top of the stack.
     *
     * @param traversal The string representation of the preorder traversal.
     * @return The root node of the recovered binary tree.
     */
    TreeNode* recoverFromPreorder(std::string traversal) {
        // Step 1: Parse the traversal string into a list of {depth, value} pairs.
        std::vector<std::pair<int, int>> nodes;
        for (int i = 0; i < traversal.length(); ) {
            int depth = 0;
            // Count the number of dashes to determine the depth.
            while (i < traversal.length() && traversal[i] == '-') {
                depth++;
                i++;
            }

            int value = 0;
            // Parse the digits to get the node's value.
            while (i < traversal.length() && isdigit(traversal[i])) {
                value = value * 10 + (traversal[i] - '0');
                i++;
            }
            nodes.push_back({depth, value});
        }

        if (nodes.empty()) {
            return nullptr;
        }

        // Step 2: Reconstruct the tree using a stack.
        // The stack will hold the nodes in the current path from the root.
        std::stack<TreeNode*> s;

        // The first node is always the root.
        TreeNode* root = new TreeNode(nodes[0].second);
        s.push(root);

        // Iterate through the rest of the nodes to build the tree.
        for (size_t i = 1; i < nodes.size(); ++i) {
            auto [depth, value] = nodes[i];
            
            // Pop from the stack until we find the parent of the current node.
            // The parent's depth will be `depth - 1`.
            // The stack's size represents the depth of the node at its top.
            while (s.size() > depth) {
                s.pop();
            }

            TreeNode* newNode = new TreeNode(value);
            
            // The node at the top of the stack is the parent.
            TreeNode* parent = s.top();

            // The problem guarantees that if a node has one child, it's the left one.
            // Since we process in preorder, we always try to fill the left child first.
            if (!parent->left) {
                parent->left = newNode;
            } else {
                parent->right = newNode;
            }
            
            // Push the new node onto the stack as it's now part of the current path.
            s.push(newNode);
        }

        return root;
    }
};

// Helper function to print the tree (for verification, not part of the solution)
void printInOrder(TreeNode* node) {
    if (!node) return;
    printInOrder(node->left);
    std::cout << node->val << " ";
    printInOrder(node->right);
}


// --- Example Usage ---
int main() {
    Solution sol;

    // Example 1:
    std::string traversal1 = "1-2--3--4-5--6--7";
    TreeNode* root1 = sol.recoverFromPreorder(traversal1);
    std::cout << "In-order traversal for example 1: ";
    printInOrder(root1); // Expected output would correspond to [1,2,5,3,4,6,7]
    std::cout << std::endl;

    // Example 2:
    std::string traversal2 = "1-2--3---4-5--6---7";
    TreeNode* root2 = sol.recoverFromPreorder(traversal2);
    std::cout << "In-order traversal for example 2: ";
    printInOrder(root2); // Expected output would correspond to [1,2,5,3,null,6,null,4,null,7]
    std::cout << std::endl;

    // Example 3:
    std::string traversal3 = "1-401--349---90--88";
    TreeNode* root3 = sol.recoverFromPreorder(traversal3);
    std::cout << "In-order traversal for example 3: ";
    printInOrder(root3); // Expected output would correspond to [1,401,null,349,88,90]
    std::cout << std::endl;

    return 0;
}
