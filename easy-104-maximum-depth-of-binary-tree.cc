/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

class Solution {
public:
    // Approach 1: Recursive DFS (Most elegant)
    int maxDepth(TreeNode* root) {
        if (!root) return 0;
        return 1 + max(maxDepth(root->left), maxDepth(root->right));
    }
    
    // Approach 2: Iterative DFS using stack
    int maxDepthIterativeDFS(TreeNode* root) {
        if (!root) return 0;
        
        stack<pair<TreeNode*, int>> stk;
        stk.push({root, 1});
        int maxDepth = 0;
        
        while (!stk.empty()) {
            auto [node, depth] = stk.top();
            stk.pop();
            
            maxDepth = max(maxDepth, depth);
            
            if (node->right) stk.push({node->right, depth + 1});
            if (node->left) stk.push({node->left, depth + 1});
        }
        
        return maxDepth;
    }
    
    // Approach 3: Iterative BFS using queue (level-order traversal)
    int maxDepthIterativeBFS(TreeNode* root) {
        if (!root) return 0;
        
        queue<TreeNode*> q;
        q.push(root);
        int depth = 0;
        
        while (!q.empty()) {
            int levelSize = q.size();
            depth++;
            
            // Process all nodes at current level
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        
        return depth;
    }
};

// Alternative recursive approach with helper function
class SolutionAlternative {
public:
    int maxDepth(TreeNode* root) {
        int depth = 0;
        dfs(root, 1, depth);
        return depth;
    }
    
private:
    void dfs(TreeNode* node, int currentDepth, int& maxDepth) {
        if (!node) return;
        
        maxDepth = max(maxDepth, currentDepth);
        
        dfs(node->left, currentDepth + 1, maxDepth);
        dfs(node->right, currentDepth + 1, maxDepth);
    }
};

I'll solve the Maximum Depth of Binary Tree problem, which is a fundamental tree traversal problem.
Problem Analysis:

Find the maximum depth (height) of a binary tree
Depth is the number of nodes along the longest path from root to leaf
Can be solved using DFS (recursive or iterative) or BFS

Approaches:

Recursive DFS - Most intuitive and clean
Iterative DFS - Using stack
Iterative BFS - Using queue, level by level

Solution Breakdown:
Approach 1: Recursive DFS (Recommended)

Logic: Depth = 1 + max(left subtree depth, right subtree depth)
Base case: null node has depth 0
Time: O(n), Space: O(h) where h is tree height

Approach 2: Iterative DFS

Uses stack to simulate recursion
Each stack entry stores (node, current_depth)
Track maximum depth encountered
Time: O(n), Space: O(h)

Approach 3: Iterative BFS

Level-order traversal using queue
Process nodes level by level, increment depth counter
Time: O(n), Space: O(w) where w is maximum width

Example walkthrough:
Tree: [3,9,20,null,null,15,7]
       3
      / \
     9   20
        /  \
       15   7

Recursive: maxDepth(3) = 1 + max(maxDepth(9), maxDepth(20))
                       = 1 + max(1, 2) = 3
When to use each approach:

Recursive: Most readable and concise
Iterative DFS: When you want to avoid recursion stack overflow
Iterative BFS: When you need level-by-level processing or want to minimize space for wide trees

The recursive solution is typically preferred for its simplicity and clarity, unless there are specific constraints about stack usage.
