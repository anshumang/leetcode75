The problem [**Decode String**](https://leetcode.com/problems/decode-string/description/) is a **stack-based** parsing problem that involves decoding strings with nested encoded patterns.
Sep 15, 2016
---

### 🔹 Problem Summary

> Given an encoded string, return its decoded version.
> The encoding rule is: **`k[encoded_string]`**, where the `encoded_string` inside the square brackets is repeated exactly `k` times.

---

### 🔹 Examples

**Input:** `"3[a]2[bc]"`
**Output:** `"aaabcbc"`

**Input:** `"3[a2[c]]"`
**Output:** `"accaccacc"`

**Input:** `"2[abc]3[cd]ef"`
**Output:** `"abcabccdcdcdef"`

---

### 🔹 Constraints

* `1 <= s.length <= 30^5`
* `s` consists of digits, letters, and square brackets `[]`
* `s` is **guaranteed to be valid**
* `All numbers are positive integers ≤ 300`

---

### 🔹 Key Idea: Stack for Nested Structure

You process characters from left to right using a **stack**:

* Push numbers (for repetition counts).
* Push current strings (accumulated letters).
* On `]`, pop and build the decoded section.

---

### ✅ C++ Solution

```cpp
string decodeString(string s) {
    stack<int> countStack;
    stack<string> strStack;
    string curr = "";
    int k = 0;

    for (char c : s) {
        if (isdigit(c)) {
            k = k * 10 + (c - '0');
        } else if (c == '[') {
            countStack.push(k);
            strStack.push(curr);
            k = 0;
            curr = "";
        } else if (c == ']') {
            int repeat = countStack.top(); countStack.pop();
            string prev = strStack.top(); strStack.pop();
            while (repeat--) prev += curr;
            curr = prev;
        } else {
            curr += c;
        }
    }

    return curr;
}
```

---

### 🔍 Dry Run on `"3[a2[c]]"`

1. Parse `3[` → push 3, `curr = ""`
2. Parse `a` → `curr = "a"`
3. Parse `2[` → push 2, `curr = ""`
4. Parse `c` → `curr = "c"`
5. Parse `]` → pop 2 and `"a"`, become `"acc"`
6. Parse `]` → pop 3 and `""`, become `"accaccacc"`

---

### 🔸 Time & Space Complexity

* **Time:** O(n)
* **Space:** O(n) (for stacks)

---

Would you like a recursive solution or Python version as well?
