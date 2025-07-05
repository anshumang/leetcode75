The LeetCode problem ["Product of Array Except Self"](https://leetcode.com/problems/product-of-array-except-self/) asks you to compute an output array such that each element at index `i` is equal to the product of all the elements of the input array except `nums[i]`, **without using division**, and in **O(n)** time.

---

### 🔧 Constraints

* You **cannot** use division.
* You must achieve **O(n)** time complexity.
* Space complexity must be **O(1)** (excluding the output array).

---

### ✅ Example

#### Input:

```
nums = [1, 2, 3, 4]
```

#### Output:

```
[24, 12, 8, 6]
```

#### Explanation:

* Output\[0] = 2 × 3 × 4 = 24
* Output\[1] = 1 × 3 × 4 = 12
* Output\[2] = 1 × 2 × 4 = 8
* Output\[3] = 1 × 2 × 3 = 6

---

### 💡 Key Insight

Use two passes:

1. Left pass: store product of elements to the **left** of each index.
2. Right pass: multiply product of elements to the **right** of each index.

---

### 🧪 C++ Code

```cpp
vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> output(n, 1);

    // First pass: calculate left products
    int left = 1;
    for (int i = 0; i < n; i++) {
        output[i] = left;
        left *= nums[i];
    }

    // Second pass: multiply with right products
    int right = 1;
    for (int i = n - 1; i >= 0; i--) {
        output[i] *= right;
        right *= nums[i];
    }

    return output;
}
```

---

### 🧠 Dry Run on `[1, 2, 3, 4]`

**First pass (left products):**

* output = \[1, 1, 2, 6]

**Second pass (right products):**

* output = \[24, 12, 8, 6]

---

Would you like a version with step-by-step state visualization or in another language (e.g., Python)?
