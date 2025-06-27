//✅ Strategy:
//Use DFS (Depth-First Search) to explore every node and track:

//The direction of the last move (left or right),

//The current ZigZag length.

//At each node:

//If last move was left → try right next,

//If last move was right → try left next.

class Solution {
public:
    int maxZigZag = 0;

    void dfs(TreeNode* node, bool isLeft, int length) {
        if (!node) return;
        maxZigZag = max(maxZigZag, length);

        if (isLeft) {
            dfs(node->left, false, 1);         // restart if same direction
            dfs(node->right, true, length + 1); // alternate direction
        } else {
            dfs(node->right, true, 1);
            dfs(node->left, false, length + 1);
        }
    }

    int longestZigZag(TreeNode* root) {
        if (!root) return 0;
        dfs(root->left, false, 1);  // move left first
        dfs(root->right, true, 1);  // move right first
        return maxZigZag;
    }
};

//🔹 Time & Space Complexity:
//Time: O(n) — visits each node once.

//Space: O(h) — for recursion stack, where h = height of the tree.

//✅ Key Idea (Bottom-Up DP):
//At each node, compute two values:

//leftZigZag: longest ZigZag path starting by going left from this node.

//rightZigZag: longest ZigZag path starting by going right from this node.

//Each node returns these values to its parent, which uses them to build longer paths.
class Solution {
public:
    int maxZigZag = 0;

    // Returns {leftZigZag, rightZigZag}
    pair<int, int> dfs(TreeNode* node) {
        if (!node) return {-1, -1}; // use -1 so when we add 1, it starts at 0

        auto [leftLeft, leftRight] = dfs(node->left);
        auto [rightLeft, rightRight] = dfs(node->right);

        int leftZigZag = 1 + leftRight;   // coming from left child, so switch to right
        int rightZigZag = 1 + rightLeft;  // coming from right child, so switch to left

        maxZigZag = max({maxZigZag, leftZigZag, rightZigZag});

        return {leftZigZag, rightZigZag};
    }

    int longestZigZag(TreeNode* root) {
        dfs(root);
        return maxZigZag;
    }
};
//🔍 Why Use -1 Base Case?
//If we return 0 for nullptr, then at the leaf node we get 1 + 0 = 1, which incorrectly implies an edge exists.

//Using -1, the first valid edge becomes 0 when added.

//🔹 Time & Space Complexity:
//Time: O(n) — each node visited once.

//Space: O(h) — recursion stack, h = height of tree.
