The LeetCode problem **[435. Non-overlapping Intervals](https://leetcode.com/problems/non-overlapping-intervals/description/)** asks you to remove the **minimum number of intervals** from a collection so that the remaining intervals **do not overlap**.
Nov 01, 2016
---

### 🔍 Problem Summary:

You're given a list of intervals represented as `[[start1, end1], [start2, end2], ...]`. Your task is to **remove the fewest number of intervals** so that the rest do **not overlap**.

---

### ✅ Constraints:

* An interval `[a, b)` overlaps with `[c, d)` if `a < d` and `c < b`.
* You need to return the **minimum number of intervals to remove**.

---

### 💡 Intuition:

This is a classic **Greedy Algorithm** problem.

* Sort intervals by **ending time**.
* Keep selecting intervals that **end the earliest** and **do not overlap** with previously selected ones.
* Count how many you can keep — the answer will be total intervals minus those you can keep.

---

### 🧠 Greedy Algorithm Steps:

1. **Sort** the intervals by their end time.
2. Initialize `end = -∞` and `count = 0`.
3. Iterate over intervals:

   * If current interval's `start >= end`, it doesn't overlap → keep it, update `end`, and increment `count`.
4. Answer = `total intervals - count`.

---

### 🧪 Example:

Input:

```text
[[1,2],[2,3],[3,4],[1,3]]
```

* Sorted by end: `[[1,2], [1,3], [2,3], [3,4]]`
* We can keep: \[1,2], \[2,3], \[3,4]
* Removed: \[1,3] → **Output: 1**

---

### ✅ C++ Code (Greedy):

```cpp
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end(), [](auto &a, auto &b) {
        return a[1] < b[1];
    });

    int count = 0;
    int end = INT_MIN;

    for (const auto& interval : intervals) {
        if (interval[0] >= end) {
            end = interval[1];
        } else {
            count++;  // overlap, so remove
        }
    }

    return count;
}
```

---

Let me know if you want a **visual dry run**, a **recursive/DP version**, or explanation in **another language**.
