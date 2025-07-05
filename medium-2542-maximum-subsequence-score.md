Sure! Here's a full explanation of the LeetCode problem **"Maximum Subsequence Score"**.
Jan 21, 2023
---

### 🔗 Problem Link:

[LeetCode #2542 – Maximum Subsequence Score](https://leetcode.com/problems/maximum-subsequence-score/description/)

---

### 🧾 Problem Summary:

You are given two integer arrays `nums1` and `nums2`, both of size `n`, and an integer `k`.

You need to:

* Select **k indices** (0-based) from `0` to `n-1`.
* Let’s call the selected indices `i₁, i₂, ..., iₖ`.

Then compute the **score** as:

```
score = (sum of nums1[i₁] + ... + nums1[iₖ]) * min(nums2[i₁], ..., nums2[iₖ])
```

Your task is to choose **k indices** such that this score is **maximized**.

---

### ⚙️ Constraints:

* `1 <= k <= n <= 10^5`
* `1 <= nums1[i], nums2[i] <= 10^5`

---

### 🧠 Intuition:

This is a tricky **greedy + heap** problem.

The score formula is:

```
score = sum(nums1 of chosen k elements) * min(nums2 of those k elements)
```

**Observation**:
If we fix `min(nums2)` to some value `m`, we want the **largest possible sum of k nums1 elements** from those entries where `nums2 >= m`.

So we:

1. **Sort the elements by nums2 descending** — so we always consider using a smaller `min(nums2)` last.
2. For each position, maintain a **heap of the top k nums1 values** so far.
3. At each step, compute the score = sum(nums1 in heap) \* current nums2, and update the max.

---

### ✅ C++ Code:

```cpp
class Solution {
public:
    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size();
        vector<pair<int, int>> pairs(n);
        for (int i = 0; i < n; i++) {
            pairs[i] = {nums2[i], nums1[i]};
        }

        // Sort by nums2 descending
        sort(pairs.rbegin(), pairs.rend());

        priority_queue<int, vector<int>, greater<int>> minHeap;
        long long sum = 0, result = 0;

        for (int i = 0; i < n; i++) {
            int num2 = pairs[i].first;
            int num1 = pairs[i].second;

            sum += num1;
            minHeap.push(num1);

            if (minHeap.size() > k) {
                sum -= minHeap.top();
                minHeap.pop();
            }

            if (minHeap.size() == k) {
                result = max(result, sum * num2);
            }
        }

        return result;
    }
};
```

---

### 🔍 Example:

**Input:**
`nums1 = [1,3,3,2]`, `nums2 = [2,1,3,4]`, `k = 3`

**Pairs (nums2, nums1):**

```
[(2,1), (1,3), (3,3), (4,2)]
=> after sorting by nums2 descending:
[(4,2), (3,3), (2,1), (1,3)]
```

Iterate and keep top 3 nums1 values so far, compute score as `sum(nums1) * min(nums2)` at each valid step.

Best combination gives:

* `nums1 = [2,3,3]` → sum = 8
* `nums2 = [4,3,2]` → min = 2
  → Score = `8 * 2 = 16`

**Answer:** `16`

---

Let me know if you'd like a **step-by-step heap trace**, **Python version**, or to run through a custom input!
