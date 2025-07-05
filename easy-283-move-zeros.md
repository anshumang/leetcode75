Sure! Here's a full explanation of the LeetCode problem **"Move Zeroes"**.
Jan 28, 2017
---

### 🔗 Problem Link:

[LeetCode #283 – Move Zeroes](https://leetcode.com/problems/move-zeroes/description/)

---

### 🧾 Problem Summary:

You are given an integer array `nums`.
Your task is to **move all the 0's to the end** of the array **while maintaining the relative order of the non-zero elements**.

You must do this **in-place** (i.e., no extra array), and with minimal operations.

---

### 🔄 Example:

**Input:**
`nums = [0,1,0,3,12]`

**Output:**
`[1,3,12,0,0]`

---

### ✅ Constraints:

* `1 <= nums.length <= 10^4`
* `-2³¹ <= nums[i] <= 2³¹ - 1`

---

### 🧠 Intuition:

Use the **two-pointer technique**:

* One pointer tracks the current position to **place a non-zero number**.
* The other pointer scans through the array.

---

### ✅ C++ Code:

```cpp
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int insertPos = 0;

        // First pass: move non-zeroes to the front
        for (int num : nums) {
            if (num != 0) {
                nums[insertPos++] = num;
            }
        }

        // Second pass: fill the rest with zeroes
        while (insertPos < nums.size()) {
            nums[insertPos++] = 0;
        }
    }
};
```

---

### ✅ Python Version (for reference):

```python
def moveZeroes(nums):
    insert_pos = 0

    for num in nums:
        if num != 0:
            nums[insert_pos] = num
            insert_pos += 1

    for i in range(insert_pos, len(nums)):
        nums[i] = 0
```

---

### 🧠 Time & Space Complexity:

* **Time:** O(n) – one pass to move non-zeroes, one pass to fill zeroes
* **Space:** O(1) – in-place

---

Let me know if you'd like to see a **dry-run**, **variant question**, or an **interview follow-up**!
