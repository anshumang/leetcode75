The LeetCode problem [**Unique Paths**](https://leetcode.com/problems/unique-paths/description/) is a **dynamic programming** and **combinatorics** problem.
Sep 27, 2015
---

### 🔹 Problem Summary

You are given two integers `m` and `n`, representing a grid of size `m x n`. A robot starts at the **top-left corner** and can only move:

* **Right** or
* **Down**

Your task is to return the total number of **unique paths** from the top-left to the bottom-right corner.

---

### 🔸 Example

**Input:**

```
m = 3, n = 7
```

**Output:**

```
28
```

---

### 🔹 Solution Approaches

#### ✅ 1. Dynamic Programming (Tabulation)

We build a `dp[m][n]` table where `dp[i][j]` means number of unique paths to reach cell `(i, j)`.

**C++ Code:**

```cpp
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 1));

        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }

        return dp[m - 1][n - 1];
    }
};
```

* **Time:** O(m × n)
* **Space:** O(m × n), can be optimized to O(n)

---

#### ✅ 2. Combinatorics (Optimal)

The robot must make `(m-1)` down moves and `(n-1)` right moves — a total of `(m+n-2)` moves, choosing `(m-1)` (or `(n-1)`) of them to be down.

So, the number of paths is:

```
C(m + n - 2, m - 1) = (m+n-2)! / ((m-1)! * (n-1)!)
```

**C++ Code:**

```cpp
class Solution {
public:
    int uniquePaths(int m, int n) {
        long long res = 1;
        int total = m + n - 2;
        int r = min(m - 1, n - 1);

        for (int i = 1; i <= r; ++i) {
            res = res * (total - r + i) / i;
        }

        return (int)res;
    }
};
```

* **Time:** O(min(m, n))
* **Space:** O(1)

---

Would you like:

* The **space-optimized DP version**?
* An explanation of the **combinatorics derivation**?
* Or the **Python or Java version**?
Here’s the **space-optimized dynamic programming** solution for [**Unique Paths**](https://leetcode.com/problems/unique-paths/) in **C++**:

---

### ✅ Space-Optimized DP (1D Array)

Since each cell only depends on the **left** and **top** values, we can reduce space to a **single row** of size `n`.

---

### 🔸 C++ Code

```cpp
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> dp(n, 1);  // Initialize first row as all 1s

        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[j] += dp[j - 1];  // dp[j] = dp[j] (top) + dp[j-1] (left)
            }
        }

        return dp[n - 1];
    }
};
```

---

### 🧠 Explanation

* We initialize `dp` with all 1s because the first row has only one path to any cell (move right only).
* For each subsequent row:

  * We update `dp[j] = dp[j] + dp[j - 1]`
  * `dp[j]` holds the number of paths to that cell in the current row.

---

### 🔹 Time and Space Complexity

* **Time:** O(m × n)
* **Space:** O(n)

---

Let me know if you'd like a **step-by-step walkthrough** of how `dp` updates for a sample input like `m = 3, n = 7`.
