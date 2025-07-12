The LeetCode problem [**Can Place Flowers**](https://leetcode.com/problems/can-place-flowers/description/) is a **greedy array placement** problem.
Jun 04, 2017
---

### 🔹 Problem Summary

You’re given a binary array `flowerbed`, where:

* `1` means a flower is planted.
* `0` means the spot is empty.

You can **only plant a flower in an empty spot** (`0`) **if both its adjacent spots are also empty or out-of-bounds**.

Given an integer `n`, return `true` if you can place `n` new flowers without violating the no-adjacent-flowers rule.

---

### 🔸 Example

**Input:**

```text
flowerbed = [1, 0, 0, 0, 1], n = 1
```

**Output:** `true`
**Explanation:** You can plant 1 flower at index 2.

---

### 🔹 Intuition

Walk through the array. If you find a `0` where:

* `flowerbed[i] == 0`
* `i == 0 || flowerbed[i - 1] == 0`
* `i == n - 1 || flowerbed[i + 1] == 0`

Then you can plant a flower at `i`, and set `flowerbed[i] = 1`.

---

### 🔸 Greedy Solution (Python)

```python
class Solution:
    def canPlaceFlowers(self, flowerbed: List[int], n: int) -> bool:
        for i in range(len(flowerbed)):
            if flowerbed[i] == 0:
                empty_left = (i == 0) or (flowerbed[i - 1] == 0)
                empty_right = (i == len(flowerbed) - 1) or (flowerbed[i + 1] == 0)
                
                if empty_left and empty_right:
                    flowerbed[i] = 1
                    n -= 1
                    
        return n <= 0
```

---

### 🔹 Time and Space Complexity

* **Time:** O(n)
* **Space:** O(1) – modifies the input list in-place

---

Would you like this solution in **C++**, **Java**, or an explanation of **edge cases** and why the greedy approach is sufficient?
Here's the **C++ implementation** of the solution to [**Can Place Flowers**](https://leetcode.com/problems/can-place-flowers/description/) using a **greedy** approach:

---

### ✅ C++ Code

```cpp
class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        int size = flowerbed.size();
        
        for (int i = 0; i < size; ++i) {
            if (flowerbed[i] == 0) {
                bool emptyLeft = (i == 0) || (flowerbed[i - 1] == 0);
                bool emptyRight = (i == size - 1) || (flowerbed[i + 1] == 0);
                
                if (emptyLeft && emptyRight) {
                    flowerbed[i] = 1;  // Plant a flower
                    --n;
                }
            }
        }

        return n <= 0;
    }
};
```

---

### 🧠 Key Points

* **Edge checks** are safely handled using `i == 0` or `i == size - 1` conditions.
* We **modify the input** flowerbed in-place for simplicity and O(1) space.
* Stop as soon as we’ve planted all required flowers (`n <= 0`).

---

Let me know if you'd like:

* A **version without modifying the input**,
* A **loop that exits early** when `n == 0`,
* Or a **step-by-step trace** with an example.
