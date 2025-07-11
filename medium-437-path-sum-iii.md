The LeetCode problem **[437. Path Sum III](https://leetcode.com/problems/path-sum-iii/description/)** requires you to find the number of paths in a binary tree that sum to a given value.
Dec 23, 2016
---

### 🔍 Problem Summary:

* You’re given the **root** of a binary tree and an **integer targetSum**.
* A path is defined as any **sequence of nodes** from **parent to child** (not necessarily root to leaf).
* You must count **how many such paths** sum up to `targetSum`.

---

### ✅ Constraints:

* The path **must go downwards** (from parent to child).
* The path **can start and end at any node**.
* Nodes can have **negative values**.

---

### 🧠 Brute-force Approach:

At each node, start a DFS to calculate all downward paths and check if any add up to `targetSum`.

Time Complexity: `O(n^2)` in the worst case (unbalanced tree), because each node may explore all others beneath it.

---

### ⚡ Optimal Solution: Prefix Sum + Hash Map

Use a **prefix sum hashmap** to track the running sum from root to current node and how many times each prefix sum has occurred.

#### Key Idea:

If the current prefix sum is `currSum`, and you're looking for paths that sum to `targetSum`, then:

```text
Number of valid paths = prefix_sum_count[currSum - targetSum]
```

---

### ✅ C++ Code (Prefix Sum):

```cpp
class Solution {
public:
    int count = 0;
    
    void dfs(TreeNode* node, long currSum, int target, unordered_map<long, int>& prefixSums) {
        if (!node) return;
        
        currSum += node->val;
        
        // Check if there's a prefix sum that leads to target
        if (prefixSums.count(currSum - target)) {
            count += prefixSums[currSum - target];
        }
        
        // Add current sum to prefix map
        prefixSums[currSum]++;
        
        dfs(node->left, currSum, target, prefixSums);
        dfs(node->right, currSum, target, prefixSums);
        
        // Backtrack
        prefixSums[currSum]--;
    }

    int pathSum(TreeNode* root, int targetSum) {
        unordered_map<long, int> prefixSums;
        prefixSums[0] = 1;  // Base case: empty path has sum 0
        dfs(root, 0, targetSum, prefixSums);
        return count;
    }
};
```

---

### 🧪 Example:

Input:

```
root = [10,5,-3,3,2,null,11,3,-2,null,1]
targetSum = 8
```

Output:

```
3
```

Explanation:
The three paths are:

* 5 → 3
* 5 → 2 → 1
* -3 → 11

---

Let me know if you'd like a **Python version**, **step-by-step walkthrough**, or **visual tree explanation**.
