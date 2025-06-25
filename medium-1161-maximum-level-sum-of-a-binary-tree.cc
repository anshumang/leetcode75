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
    // Approach 1: BFS Level-order Traversal (Most intuitive)
    int maxLevelSum(TreeNode* root) {
        if (!root) return 1;
        
        queue<TreeNode*> q;
        q.push(root);
        
        int level = 1;
        int maxSum = root->val;
        int maxLevel = 1;
        
        while (!q.empty()) {
            int levelSize = q.size();
            int currentSum = 0;
            
            // Process all nodes at current level
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                currentSum += node->val;
                
                // Add children to queue for next level
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            
            // Update max sum and level if current sum is greater
            if (currentSum > maxSum) {
                maxSum = currentSum;
                maxLevel = level;
            }
            
            level++;
        }
        
        return maxLevel;
    }
    
    // Approach 2: DFS with level tracking
    int maxLevelSumDFS(TreeNode* root) {
        if (!root) return 1;
        
        vector<long long> levelSums;
        dfs(root, 0, levelSums);
        
        // Find level with maximum sum
        long long maxSum = levelSums[0];
        int maxLevel = 1;
        
        for (int i = 1; i < levelSums.size(); i++) {
            if (levelSums[i] > maxSum) {
                maxSum = levelSums[i];
                maxLevel = i + 1; // Convert 0-indexed to 1-indexed
            }
        }
        
        return maxLevel;
    }
    
private:
    void dfs(TreeNode* node, int level, vector<long long>& levelSums) {
        if (!node) return;
        
        // Expand vector if needed
        if (level >= levelSums.size()) {
            levelSums.resize(level + 1, 0);
        }
        
        // Add current node's value to its level sum
        levelSums[level] += node->val;
        
        // Recursively process children
        dfs(node->left, level + 1, levelSums);
        dfs(node->right, level + 1, levelSums);
    }
    
public:
    // Approach 3: BFS with detailed tracking
    int maxLevelSumDetailed(TreeNode* root) {
        if (!root) return 1;
        
        queue<TreeNode*> q;
        q.push(root);
        
        int currentLevel = 1;
        long long maxSum = LLONG_MIN;
        int resultLevel = 1;
        
        while (!q.empty()) {
            int nodesInLevel = q.size();
            long long levelSum = 0;
            
            // Process all nodes in current level
            for (int i = 0; i < nodesInLevel; i++) {
                TreeNode* current = q.front();
                q.pop();
                
                levelSum += current->val;
                
                // Add children for next level
                if (current->left) {
                    q.push(current->left);
                }
                if (current->right) {
                    q.push(current->right);
                }
            }
            
            // Check if current level has maximum sum
            if (levelSum > maxSum) {
                maxSum = levelSum;
                resultLevel = currentLevel;
            }
            
            currentLevel++;
        }
        
        return resultLevel;
    }
};
