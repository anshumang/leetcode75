The LeetCode problem **[452. Minimum Number of Arrows to Burst Balloons](https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/description/)** asks you to find the **minimum number of arrows** required to burst all balloons, where each balloon is represented by a horizontal interval.
Jul 24, 2020
---

### 🔍 Problem Summary:

* Each balloon is represented as an interval `[start, end]`.
* An arrow shot at position `x` will burst all balloons where `start <= x <= end`.
* You need to **minimize** the number of arrows needed to burst **all** balloons.

---

### 🧠 Key Insight:

This is a **Greedy Interval Scheduling** problem — very similar to **Non-overlapping Intervals (LC 435)**.

* Sort all intervals by their **end coordinate**.
* Always shoot the arrow at the **earliest possible end** that still bursts the current balloon.
* Every time a new balloon doesn’t overlap with the previous, you need a new arrow.

---

### ✅ Algorithm:

1. **Sort** balloons by `end`.
2. Initialize `arrows = 1`, and set `last_end` to the end of the first balloon.
3. For each balloon:

   * If the current balloon’s start is **greater than `last_end`**, it can’t be burst with the previous arrow → increment arrow count.
   * Update `last_end` to the end of the current balloon when needed.

---

### ✅ C++ Code:

```cpp
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.empty()) return 0;
        
        // Sort by the end of each balloon
        sort(points.begin(), points.end(), [](auto &a, auto &b) {
            return a[1] < b[1];
        });
        
        int arrows = 1;
        int last_end = points[0][1];
        
        for (const auto& balloon : points) {
            if (balloon[0] > last_end) {
                arrows++;
                last_end = balloon[1];
            }
        }
        
        return arrows;
    }
};
```

---

### 🧪 Example:

Input:

```text
[[10,16],[2,8],[1,6],[7,12]]
```

Sorted:

```text
[[1,6],[2,8],[7,12],[10,16]]
```

* One arrow at 6 bursts \[1,6], \[2,8]
* Another arrow at 12 bursts \[7,12], \[10,16]

Output:

```text
2
```

---

### ⏱️ Time & Space Complexity:

* **Time:** O(n log n) for sorting
* **Space:** O(1) extra space

---

Let me know if you’d like:

* A **Python version**
* **Dry run** with a visual example
* **Variants** like "maximum number of balloons with one arrow"
