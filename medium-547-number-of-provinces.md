The LeetCode problem [**Number of Provinces**](https://leetcode.com/problems/number-of-provinces/description/) is a **graph connectivity** problem. Here's a breakdown of the task and how to solve it.
Apr 03, 2017
---

### 🔹 Problem Summary

You are given an `n x n` matrix `isConnected` where:

* `isConnected[i][j] = 1` means city `i` is connected to city `j`.
* `isConnected[i][j] = 0` means there is no connection.

A **province** is a group of directly or indirectly connected cities. Your goal is to return **the total number of provinces**.

---

### 🔸 Example

**Input:**

```
isConnected = [
  [1, 1, 0],
  [1, 1, 0],
  [0, 0, 1]
]
```

**Output:** `2`

There are two provinces: `{0,1}` and `{2}`.

---

### 🔹 Intuition

The matrix represents an **undirected graph**, where:

* Each city is a node.
* An edge exists if `isConnected[i][j] = 1`.

We need to count the number of **connected components** in this graph.

---

### 🔸 DFS Approach (C++)

```cpp
class Solution {
public:
    void dfs(int node, vector<vector<int>>& isConnected, vector<bool>& visited) {
        visited[node] = true;
        for (int j = 0; j < isConnected.size(); ++j) {
            if (isConnected[node][j] == 1 && !visited[j]) {
                dfs(j, isConnected, visited);
            }
        }
    }

    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<bool> visited(n, false);
        int provinces = 0;

        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                dfs(i, isConnected, visited);
                provinces++;
            }
        }

        return provinces;
    }
};
```

---

### 🔹 Alternate Approaches

* **BFS** instead of DFS
* **Union-Find (Disjoint Set Union)** for improved performance in sparse graphs

Would you like the **Union-Find solution**, a **step-by-step trace**, or help converting to **Python** or **Java**?
