The problem [**Counting Bits**](https://leetcode.com/problems/counting-bits/description/) requires you to count the number of `1`s (set bits) in the binary representation of each number from `0` to `n`.

---

### 🔹 Problem Summary

> Given an integer `n`, return an array `ans` of length `n + 1` such that for each `i (0 <= i <= n)`,
> `ans[i]` is the number of `1`'s in the binary representation of `i`.

---

### 🔹 Constraints

* `0 <= n <= 10^5`

---

### 🔹 Example

**Input:** `n = 5`
**Output:** `[0,1,1,2,1,2]`
**Explanation:**

* `0 = 0b000` → 0
* `1 = 0b001` → 1
* `2 = 0b010` → 1
* `3 = 0b011` → 2
* `4 = 0b100` → 1
* `5 = 0b101` → 2

---

### 🔹 Key Idea (Dynamic Programming)

Use the fact that:

* `i >> 1` is `i / 2` (dropping the last bit),
* So:

  $$
  \text{countBits}[i] = \text{countBits}[i >> 1] + (i \& 1)
  $$

---

### ✅ C++ Solution

```cpp
vector<int> countBits(int n) {
    vector<int> ans(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        ans[i] = ans[i >> 1] + (i & 1);
    }
    return ans;
}
```

---

### 🔍 Why it Works

* `i >> 1` is just `i / 2` (in binary, it shifts right).
* `i & 1` checks whether the least significant bit is 1.

So each value reuses a previously computed result (DP) in **O(1)** time.

---

### 🔸 Time & Space Complexity

* **Time:** O(n)
* **Space:** O(n)

---

Would you like a Python version or explanation of how this compares to using `__builtin_popcount`?
