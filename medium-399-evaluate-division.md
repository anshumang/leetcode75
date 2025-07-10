The problem [**Evaluate Division**](https://leetcode.com/problems/evaluate-division/description/) is a **graph-based** problem that requires simulating a division system using equations.
Dec 03, 2016
---

### 🔹 Problem Summary

You're given:

* A list of **equations** like `a / b = k`
* A list of **queries** like `x / y`

> Return the result of each query using the equations. If the answer does not exist, return `-1.0`.

---

### 🔹 Example

**Input:**

```plaintext
equations = [["a","b"],["b","c"]]
values = [2.0,3.0]
queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
```

**Output:**

```plaintext
[6.0, 0.5, -1.0, 1.0, -1.0]
```

---

### 🔹 Key Idea: Graph + DFS/BFS

* Build a **graph** where:

  * Nodes = variables
  * Edges = division relationships (weights = division values)
  * For `a / b = 2.0`, add:

    * `a → b (2.0)`
    * `b → a (1 / 2.0)`

* Then use **DFS or BFS** to evaluate queries.

---

### ✅ C++ Solution Using DFS

```cpp
class Solution {
public:
    unordered_map<string, vector<pair<string, double>>> graph;

    double dfs(string curr, string target, unordered_set<string>& visited, double value) {
        if (curr == target) return value;
        visited.insert(curr);

        for (auto& [neighbor, weight] : graph[curr]) {
            if (!visited.count(neighbor)) {
                double result = dfs(neighbor, target, visited, value * weight);
                if (result != -1.0) return result;
            }
        }
        return -1.0;
    }

    vector<double> calcEquation(
        vector<vector<string>>& equations,
        vector<double>& values,
        vector<vector<string>>& queries
    ) {
        // Build graph
        for (int i = 0; i < equations.size(); ++i) {
            string a = equations[i][0];
            string b = equations[i][1];
            double val = values[i];

            graph[a].push_back({b, val});
            graph[b].push_back({a, 1.0 / val});
        }

        vector<double> results;
        for (auto& query : queries) {
            string start = query[0], end = query[1];
            if (!graph.count(start) || !graph.count(end)) {
                results.push_back(-1.0);
            } else if (start == end) {
                results.push_back(1.0);
            } else {
                unordered_set<string> visited;
                results.push_back(dfs(start, end, visited, 1.0));
            }
        }

        return results;
    }
};
```

---

### 🔸 Time & Space Complexity

* **Time:** O(N + Q) in average case (N = # of equations, Q = # of queries), assuming each DFS is bounded
* **Space:** O(N) for graph and visited set

---

Would you like a version using Union-Find with weights or an iterative BFS approach?
