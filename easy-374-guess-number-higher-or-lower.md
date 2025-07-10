The problem [**Guess Number Higher or Lower**](https://leetcode.com/problems/guess-number-higher-or-lower/description/) is a classic **binary search** question.
Jul 13, 2016
---

### 🔹 Problem Summary

You are trying to guess a number between `1` and `n`. There's a predefined API function:

```cpp
int guess(int num);
```

* Returns:

  * `-1` if the target number is **lower** than `num`
  * `1` if the target is **higher** than `num`
  * `0` if `num` is the correct guess

Your task is to **implement a function**:

```cpp
int guessNumber(int n);
```

to find the number using as few guesses as possible.

---

### 🔹 Example

**Input:** `n = 10`, `pick = 6`
**Output:** `6`

---

### 🔹 Key Idea: Binary Search

You search between `1` and `n`, narrowing the range using `guess(mid)`.

---

### ✅ C++ Solution

```cpp
int guessNumber(int n) {
    int left = 1, right = n;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int res = guess(mid);

        if (res == 0) return mid;
        else if (res < 0) right = mid - 1;
        else left = mid + 1;
    }

    return -1; // shouldn't reach here
}
```

---

### 🔍 Explanation

* Use binary search to minimize the number of `guess()` calls.
* The key is checking the return value of `guess(mid)`:

  * If `0`, found the number.
  * If `-1`, search the **left half**.
  * If `1`, search the **right half**.

---

### 🔸 Time Complexity

* **Time:** O(log n)
* **Space:** O(1)

---

Let me know if you want a dry run example or a version in Python!
