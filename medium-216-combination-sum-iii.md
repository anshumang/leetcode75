🔗 [Problem Link](https://leetcode.com/problems/combination-sum-iii/description/)

---

### ✅ Problem Summary:

You are given:

* An integer `k` → number of numbers to pick
* An integer `n` → target sum

Return **all possible combinations** of `k` distinct numbers from `1` to `9` such that:

* The numbers add up to `n`
* Each number is used **at most once**
* Each combination must be **unique** and in **ascending order**

---

### 🧠 Example:

```text
Input: k = 3, n = 7
Output: [[1,2,4]]
```

---

### 🧩 Approach: Backtracking

We explore all combinations using **DFS with pruning**:

1. Maintain:

   * `start` — the next number to consider (to avoid duplicates)
   * `path` — the current combination
   * `remaining` — how much sum is left
2. Base case: If `path.size() == k` and `remaining == 0`, it's a valid answer.

---

### 💻 C++ Code:

```cpp
class Solution {
public:
    vector<vector<int>> result;

    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int> path;
        backtrack(1, k, n, path);
        return result;
    }

    void backtrack(int start, int k, int remaining, vector<int>& path) {
        if (path.size() == k) {
            if (remaining == 0)
                result.push_back(path);
            return;
        }

        for (int i = start; i <= 9; ++i) {
            if (i > remaining) break; // pruning
            path.push_back(i);
            backtrack(i + 1, k, remaining - i, path);
            path.pop_back();
        }
    }
};
```

---

### 🧮 Time Complexity:

* **Time:** O(C(9, k)) — we choose `k` numbers from 1–9
* **Space:** O(k) for recursion stack and path

---

### ✅ Notes:

* Numbers from `1` to `9` only → small space of combinations
* No duplicates because we use `i + 1` to move forward
* Pruning (`if i > remaining`) optimizes performance

---
