The problem [**Reverse Vowels of a String**](https://leetcode.com/problems/reverse-vowels-of-a-string/description/) asks you to reverse only the vowels in a given string.
Apr 23, 2016
---

### 🔹 Problem Summary

> Given a string `s`, reverse **only the vowels** of the string and return the resulting string.

---

### 🔹 Vowels to Consider

* Both lowercase and uppercase: `'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'`

---

### 🔹 Example

**Input:** `"hello"`
**Output:** `"holle"`

**Input:** `"leetcode"`
**Output:** `"leotcede"`

---

### 🔹 Constraints

* `1 <= s.length <= 3 * 10^5`
* `s` consists of **printable ASCII characters**

---

### 🔹 Key Idea: Two Pointers

Use two pointers, one starting from the beginning and the other from the end. Swap the vowels when both pointers point to vowels.

---

### ✅ C++ Solution

```cpp
string reverseVowels(string s) {
    unordered_set<char> vowels = {'a','e','i','o','u','A','E','I','O','U'};
    int left = 0, right = s.length() - 1;

    while (left < right) {
        while (left < right && vowels.find(s[left]) == vowels.end()) left++;
        while (left < right && vowels.find(s[right]) == vowels.end()) right--;

        swap(s[left], s[right]);
        left++;
        right--;
    }

    return s;
}
```

---

### 🔍 How it Works

* Move `left` forward until it finds a vowel.
* Move `right` backward until it finds a vowel.
* Swap them, then continue inward.
* Stop when `left >= right`.

---

### 🔸 Time & Space Complexity

* **Time:** O(n)
* **Space:** O(1) (set is small and constant-sized)

---

Would you like a Python version or test case walkthrough?
