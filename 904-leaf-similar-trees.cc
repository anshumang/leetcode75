Consider all the leaves of a binary tree, from left to right order, the values of those leaves form a leaf value sequence.
Two binary trees are considered leaf-similar if their leaf value sequence is the same.
Return true if and only if the two given trees with head nodes root1 and root2 are leaf-similar.
Example 1:
Input: root1 = [3,5,1,6,2,9,8,null,null,7,4], root2 = [3,5,1,6,7,4,2,null,null,null,null,null,null,9,8]
Output: true
Example 2:
Input: root1 = [1,2,3], root2 = [1,3,2]
Output: false
Constraints:
The number of nodes in each tree will be in the range [1, 200].
Both of the given trees will have values in the range [0, 200].

This problem asks us to compare the sequence of leaf nodes from two different binary trees. The core idea is to traverse each tree, collect its leaves in the correct left-to-right
  order, and then compare the two resulting sequences.

Approach
Extract Leaf Sequence: We need a way to traverse a tree and collect the values of its leaf nodes in a left-to-right order. A Depth-First Search (DFS) traversal, such as a pre-order
  traversal, is perfect for this. As we traverse the tree, we check if a node is a leaf (i.e., it has no left and no right child). If it is, we add its value to a list. Since DFS
  explores the entire left subtree before the right subtree, this naturally collects the leaves from left to right.

Create Sequences for Both Trees: We will perform this leaf-extraction process for both root1 and root2, creating two separate lists of leaf values (leaves1 and leaves2).

Compare Sequences: Once we have both leaf value sequences, we can simply compare them. If the lists are identical (same size and same values in the same order), the trees are 
leaf-similar, and we return true. Otherwise, we return false.

#include <vector>

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
    /**
     * @brief Determines if two binary trees are leaf-similar.
     * @param root1 The root of the first binary tree.
     * @param root2 The root of the second binary tree.
     * @return True if the trees are leaf-similar, false otherwise.
     */
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        // Step 1: Get the leaf value sequence for the first tree.
        std::vector<int> leaves1;
        getLeaves(root1, leaves1);
        
        // Step 2: Get the leaf value sequence for the second tree.
        std::vector<int> leaves2;
        getLeaves(root2, leaves2);
        
        // Step 3: Compare the two sequences.
        // The == operator for std::vector checks for size and element-wise equality.
        return leaves1 == leaves2;
    }

private:
    /**
     * @brief A helper function to perform a DFS traversal and collect leaf values.
     * @param node The current node in the traversal.
     * @param leaves A reference to the vector where leaf values are stored.
     */
    void getLeaves(TreeNode* node, std::vector<int>& leaves) {
        // Base case: if the node is null, there's nothing to do.
        if (node == nullptr) {
            return;
        }
        
        // Check if the current node is a leaf.
        if (node->left == nullptr && node->right == nullptr) {
            leaves.push_back(node->val);
        }
        
        // Recursively traverse the left and right subtrees.
        getLeaves(node->left, leaves);
        getLeaves(node->right, leaves);
    }
};

Explanation of the Code
leafSimilar(root1, root2):

This is the main function.
It initializes two std::vector<int> containers, leaves1 and leaves2, to hold the leaf values for each tree.
It calls the getLeaves helper function for root1 to populate leaves1.
It calls getLeaves again for root2 to populate leaves2.
Finally, it returns the result of leaves1 == leaves2. This is a convenient feature of C++ vectors, which automatically compares their sizes and all their elements in order.
getLeaves(node, leaves):

This is a private helper function that implements the core DFS logic.
The base case for the recursion is when node is nullptr.
It checks if a node is a leaf by seeing if both node->left and node->right are nullptr. If they are, the node's value is added to the leaves vector.
It then makes recursive calls on the left and right children, ensuring that the entire tree is visited. This pre-order traversal guarantees that leaves are found and stored in a
left-to-right fashion.

Complexity Analysis
Time Complexity: O(N₁ + N₂), where N₁ and N₂ are the number of nodes in the first and second trees, respectively. We must visit every node in both trees to find all the leaves.
Space Complexity: O(L₁ + L₂) in the worst case, where L₁ and L₂ are the number of leaves in each tree. This space is used to store the leaf sequences. Additionally, there is
space used by the recursion stack, which is O(H₁ + H₂), where H₁ and H₂ are the heights of the trees.
