The problem [**Is Subsequence**](https://leetcode.com/problems/is-subsequence/description/) asks whether a given string `s` is a **subsequence** of another string `t`.
Dec 28, 2016
---

### 🔹 Problem Summary

> Given two strings `s` and `t`, return `true` **if** `s` is a subsequence of `t`, or `false` otherwise.

A **subsequence** of a string is a new string formed by deleting some (or no) characters **without changing the relative order** of the remaining characters.

---

### 🔹 Examples

**Input:**
`s = "abc"`, `t = "ahbgdc"`
**Output:** `true`
Explanation: `'a'`, `'b'`, `'c'` appear in order in `t`.

**Input:**
`s = "axc"`, `t = "ahbgdc"`
**Output:** `false`

---

### 🔹 Constraints

* `0 <= s.length <= 100`
* `0 <= t.length <= 10^4`
* Both `s` and `t` consist only of lowercase English letters.

---

### 🔹 Key Idea: Two Pointers

Traverse both strings. Use one pointer for `s`, and move it forward only when there's a matching character in `t`.

---

### ✅ C++ Solution

```cpp
bool isSubsequence(string s, string t) {
    int i = 0, j = 0;
    while (i < s.length() && j < t.length()) {
        if (s[i] == t[j]) i++;
        j++;
    }
    return i == s.length();
}
```

---

### 🔍 Explanation

* Start from the beginning of both `s` and `t`.
* Every time you find `s[i] == t[j]`, move `i` forward.
* Always move `j` forward.
* If you can move `i` all the way to `s.length()`, then `s` is a subsequence.

---

### 🔸 Time & Space Complexity

* **Time:** O(n), where `n = t.length()`
* **Space:** O(1)

---

Would you like a dynamic programming solution or approach for multiple `s` strings with a single `t`?
