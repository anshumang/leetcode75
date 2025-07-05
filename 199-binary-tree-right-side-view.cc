✅ Problem Summary:
Given the root of a binary tree, return the right side view of the tree, i.e., a list of the last node at each level (the node that would be visible from the right side).

🧩 Approach 1: BFS (Level Order Traversal)
Use a queue to perform level-order traversal. At each level, add the last node's value to the result.

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        if (!root) return result;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; ++i) {
                TreeNode* node = q.front();
                q.pop();
                // If it's the last node in the current level
                if (i == levelSize - 1) {
                    result.push_back(node->val);
                }
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        return result;
    }
};

⏱️ Time & Space Complexity:
Time: O(n) — every node is visited once

Space: O(n) — queue stores nodes level by level

🧩 Approach 2: DFS (Right-first Preorder)
Explore the right subtree first, and record the first node at each depth.

class Solution {
public:
    void dfs(TreeNode* node, int depth, vector<int>& res) {
        if (!node) return;
        if (depth == res.size()) {
            res.push_back(node->val); // first time reaching this depth
        }
        dfs(node->right, depth + 1, res);
        dfs(node->left, depth + 1, res);
    }

    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        dfs(root, 0, res);
        return res;
    }
};

Here’s a detailed DFS (right‑first) walk‑through for the tree:
       1
      / \
     2   3
      \    \
       5    4
We’ll trace the recursive calls, tracking:

🔹 node – current node

🔹 depth – current depth

🔹 res – result vector (tracks rightmost values)

Initial call:
dfs(node=1, depth=0, res=[])

1. Visit root (1):
depth = 0, res.size() = 0

Since equal, append 1 → res = [1]
Call:
dfs(node=3, depth=1, res=[1])

2. Visit 3:
depth = 1, res.size() = 1

Append 3 → res = [1, 3]
Call:
dfs(node=4, depth=2, res=[1,3])

3. Visit 4:
depth = 2, res.size() = 2

Append 4 → res = [1, 3, 4]

No children → backtrack

Returns to node 3, now explore left child (null) → returns

Back to node 1, proceed to left subtree:
Call:
dfs(node=2, depth=1, res=[1,3,4])

4. Visit 2:
depth = 1, res.size() = 3

depth < res.size() → we’ve already seen depth 1 (node 3), so skip appending

No left child; recurse right (5)
Call:
dfs(node=5, depth=2, res=[1,3,4])

5. Visit 5:
depth = 2, res.size() = 3

Already visited depth 2 (node 4), so skip

No children → backtrack → all done

📌 Summary of call stack:
| Call        | Action                  | res      |
| ----------- | ----------------------- | -------- |
| dfs(1,0)    | append 1                | \[1]     |
| └─ dfs(3,1) | append 3                | \[1,3]   |
| └─ dfs(4,2) | append 4                | \[1,3,4] |
| dfs(null,3) | return                  | \[1,3,4] |
| dfs(null,2) | return                  | \[1,3,4] |
| dfs(2,1)    | depth seen, skip append | \[1,3,4] |
| └─ dfs(5,2) | depth seen, skip append | \[1,3,4] |
| All done    | Final res = `[1,3,4]`   |          |
