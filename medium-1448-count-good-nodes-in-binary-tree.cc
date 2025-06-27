✅ Strategy: DFS (Depth-First Search)
Track the maximum value encountered from root to the current node.

If the current node is greater than or equal to that max, it's a "good" node.

class Solution {
public:
    int countGoodNodes(TreeNode* root, int maxSoFar = INT_MIN) {
        if (!root) return 0;

        int count = root->val >= maxSoFar ? 1 : 0;
        maxSoFar = std::max(maxSoFar, root->val);

        count += countGoodNodes(root->left, maxSoFar);
        count += countGoodNodes(root->right, maxSoFar);

        return count;
    }
};

🔹 Time & Space Complexity:
Time: O(n), where n is the number of nodes.

Space: O(h), where h is the height of the tree (due to recursion stack).

✅ C++ Code (BFS / Iterative Version):
class Solution {
public:
    int countGoodNodes(TreeNode* root) {
        if (!root) return 0;

        queue<pair<TreeNode*, int>> q;
        q.push({root, root->val});

        int count = 0;

        while (!q.empty()) {
            auto [node, maxSoFar] = q.front();
            q.pop();

            if (node->val >= maxSoFar)
                ++count;

            int newMax = max(maxSoFar, node->val);

            if (node->left)
                q.push({node->left, newMax});
            if (node->right)
                q.push({node->right, newMax});
        }

        return count;
    }
};

🔹 Explanation:
Each queue element holds:

The TreeNode*

The maxSoFar value along the path from the root

For each node:

If node->val >= maxSoFar, it's counted as good

The new max is passed down to its children

🔸 Time & Space Complexity:
Time: O(n) — every node is visited once

Space: O(n) — worst case for queue (in case of a complete tree)
