The LeetCode problem **[2352. Equal Row and Column Pairs](https://leetcode.com/problems/equal-row-and-column-pairs/description/)** asks you to find how many times a row of a square matrix equals a column (same elements, same order).
Oldest comment Dec05, 2022
---

### 🔍 Problem Summary

You're given an `n x n` integer matrix.
Return the **number of pairs** `(r, c)` such that **row `r` == column `c`**.

---

### ✅ Key Observations

* Each row and column is a vector of `n` integers.
* Compare each row with every column → brute-force is `O(n^3)` (too slow).
* But we can optimize using a **hash map**.

---

### 💡 Efficient Approach: Use Hash Map

1. Store the **frequency of each row** (as a tuple or vector) in a hash map.
2. For each column `c`, build a vector of elements `matrix[r][c]` for all `r`.
3. Check if this column vector exists in the row map — if yes, add the count.

---

### ✅ C++ Code

```cpp
class Solution {
public:
    int equalPairs(vector<vector<int>>& grid) {
        int n = grid.size();
        map<vector<int>, int> rowMap;

        // Count each row
        for (const auto& row : grid) {
            rowMap[row]++;
        }

        int result = 0;

        // For each column, build vector and check in map
        for (int c = 0; c < n; ++c) {
            vector<int> col;
            for (int r = 0; r < n; ++r) {
                col.push_back(grid[r][c]);
            }
            if (rowMap.count(col)) {
                result += rowMap[col];
            }
        }

        return result;
    }
};
```

---

### 🧪 Example

Input:

```
grid = [[3,2,1],
        [1,7,6],
        [2,7,7]]
```

* Row \[1,7,6] == Column \[1,7,6] → 1 match
* So output is `1`

---

### ⏱ Time & Space Complexity

* **Time:** `O(n^2)` — efficient enough for `n ≤ 200`
* **Space:** `O(n^2)` — for storing rows in the map

---

Let me know if you'd like a Python version or a follow-up (e.g. rows equal to reversed columns).
