🔗 [Problem Link\*\*](https://leetcode.com/problems/kth-largest-element-in-an-array/description/)

---

### ✅ Problem Summary:

Given an integer array `nums` and an integer `k`, return the **kᵗʰ largest element** in the array.

📌 Note: The kᵗʰ largest is the **kᵗʰ largest in sorted order**, not necessarily the kᵗʰ distinct element.

---

### 🧠 Example:

```text
Input: nums = [3,2,1,5,6,4], k = 2
Output: 5
Explanation: The sorted array is [1,2,3,4,5,6], so the 2nd largest is 5.
```

---

### 🧩 Common Approaches:

#### ✅ 1. **Min-Heap (Priority Queue)** – Time: O(n log k)

* Maintain a **min-heap of size k**
* Push elements one by one
* If heap size > k, pop smallest
* Top of heap is the kth largest

**C++ Code:**

```cpp
int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int num : nums) {
        minHeap.push(num);
        if (minHeap.size() > k)
            minHeap.pop();
    }
    return minHeap.top();
}
```

---

#### ✅ 2. **Sort the Array** – Time: O(n log n)

**C++ Code:**

```cpp
int findKthLargest(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());
    return nums[nums.size() - k];
}
```

---

#### ✅ 3. **Quickselect Algorithm** – Average Time: O(n)

* Similar to QuickSort
* Partition the array to place pivot in sorted position
* Recur on left/right based on `k`

(More complex but faster in average cases)

---

### 🕒 Time & Space Complexity:

| Method      | Time       | Space |
| ----------- | ---------- | ----- |
| Min-Heap    | O(n log k) | O(k)  |
| Sort        | O(n log n) | O(1)  |
| Quickselect | O(n) avg   | O(1)  |

---

Here's a **C++ implementation of Quickselect** to solve **LeetCode 215: Kth Largest Element in an Array**.

---

### 🧠 Key Idea: Quickselect

Quickselect is a selection algorithm related to Quicksort.
Instead of sorting the entire array, it **partitions** the array until the k-th largest is in the correct position.

---

### ✅ C++ Code:

```cpp
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int target = nums.size() - k; // convert kth largest to (n-k)th smallest
        return quickSelect(nums, 0, nums.size() - 1, target);
    }

    int quickSelect(vector<int>& nums, int left, int right, int k) {
        if (left == right) return nums[left];

        int pivotIndex = partition(nums, left, right);

        if (pivotIndex == k) {
            return nums[pivotIndex];
        } else if (pivotIndex < k) {
            return quickSelect(nums, pivotIndex + 1, right, k);
        } else {
            return quickSelect(nums, left, pivotIndex - 1, k);
        }
    }

    int partition(vector<int>& nums, int left, int right) {
        int pivot = nums[right];
        int i = left;
        for (int j = left; j < right; ++j) {
            if (nums[j] <= pivot) {
                swap(nums[i], nums[j]);
                ++i;
            }
        }
        swap(nums[i], nums[right]);
        return i;
    }
};
```

---

### 🔍 Explanation:

* **Target index**: We convert "kth largest" to the `(n - k)`-th **smallest** index (0-based).
* **Partition**: Places pivot in its final sorted position.

  * Elements ≤ pivot go left, > pivot go right.
* **Recursive narrowing**:

  * If pivot is at the target index → done.
  * Else recurse left or right.

---

### ⏱️ Time & Space Complexity:

| Case         | Time Complexity |
| ------------ | --------------- |
| Average Case | O(n)            |
| Worst Case   | O(n²) (rare)    |
| Space        | O(1)            |

> Worst case can be avoided using **randomized pivot selection**.
