The problem [**Increasing Triplet Subsequence**](https://leetcode.com/problems/increasing-triplet-subsequence/description/) asks you to **determine whether an increasing subsequence of length 3** exists in a given array.

Jun 03, 2016
---

### 🔹 Problem Summary

> Given an integer array `nums`, return `true` if there exists a triple of indices `(i, j, k)` such that:
>
> * `0 <= i < j < k < nums.length`, and
> * `nums[i] < nums[j] < nums[k]`
>
> If no such indices exist, return `false`.

---

### 🔹 Constraints

* `1 <= nums.length <= 10^5`
* `-2^31 <= nums[i] <= 2^31 - 1`

---

### 🔹 Example

**Input:** `nums = [1, 2, 3, 4, 5]`
**Output:** `true`
Explanation: The triplet `(1, 2, 3)` satisfies the condition.

**Input:** `nums = [5, 4, 3, 2, 1]`
**Output:** `false`
Explanation: No increasing triplet exists.

---

### 🔹 Key Idea

We want to find three increasing numbers using only **O(n)** time and **O(1)** space.
Use two variables `first` and `second` to track the smallest and second smallest numbers seen so far.

---

### ✅ C++ Solution (Greedy)

```cpp
bool increasingTriplet(vector<int>& nums) {
    int first = INT_MAX, second = INT_MAX;

    for (int n : nums) {
        if (n <= first) {
            first = n;
        } else if (n <= second) {
            second = n;
        } else {
            return true; // Found a number greater than both first and second
        }
    }

    return false;
}
```

---

### 🔍 Explanation

* `first` keeps track of the smallest value seen.
* `second` keeps track of the next bigger value.
* If we ever find a number greater than `second`, we return `true`.

---

### 🔄 Dry Run on `[2, 1, 5, 0, 4, 6]`

* `first = 2`
* `1` → update `first = 1`
* `5` → update `second = 5`
* `0` → update `first = 0`
* `4` → update `second = 4`
* `6` → `6 > second → return true`

---

Would you like a diagram or Python version too?
