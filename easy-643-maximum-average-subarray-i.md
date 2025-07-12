The LeetCode problem [**Maximum Average Subarray I**](https://leetcode.com/problems/maximum-average-subarray-i/description/) is a **sliding window** problem focused on optimizing subarray calculations.
Jan 11, 2021
---

### 🔹 Problem Summary

Given an array `nums` of length `n` and an integer `k`, return the **maximum average** of any contiguous subarray of length `k`.

---

### 🔸 Example

**Input:**

```
nums = [1,12,-5,-6,50,3], k = 4
```

**Output:**

```
12.75
```

**Explanation:**
Subarray `[12,-5,-6,50]` has a sum of `51`, so average = `51 / 4 = 12.75`.

---

### 🔹 Intuition

To find the max average of subarrays of size `k`, use a **sliding window**:

* Start by summing the first `k` elements.
* Then slide the window one element at a time, adding the new one and subtracting the old one.

---

### 🔸 C++ Code (Sliding Window)

```cpp
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        double maxSum = 0, currSum = 0;

        for (int i = 0; i < k; ++i)
            currSum += nums[i];

        maxSum = currSum;

        for (int i = k; i < nums.size(); ++i) {
            currSum += nums[i] - nums[i - k];
            maxSum = max(maxSum, currSum);
        }

        return maxSum / k;
    }
};
```

---

### 🔹 Time and Space Complexity

* **Time:** O(n) – one pass through the array
* **Space:** O(1) – constant extra space

---

Would you like:

* A version that handles **precision issues** explicitly?
* Or to extend this to **maximum average of variable-length subarrays** (like in the follow-up problem)?
