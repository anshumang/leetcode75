The LeetCode problem **[443. String Compression](https://leetcode.com/problems/string-compression/description/)** asks you to **compress a character array in-place** and return the new length of the compressed array.
Oct 29, 2017
---

### 🔍 Problem Summary:

You're given a character array `chars`. You need to compress it **in-place** using the following rules:

* Repeated characters are replaced with the character followed by the count (if the count > 1).
* The array is modified in-place and you return the **new length** after compression.

---

### 🧪 Example:

Input:

```
["a","a","b","b","c","c","c"]
```

Output:

```
Return 6, and the array is modified to ["a","2","b","2","c","3"]
```

---

### ✅ Constraints:

* 1 <= `chars.length` <= 2000
* `chars[i]` is a lowercase English letter
* You **must modify the input array in-place** with O(1) extra space

---

### 🧠 Approach:

Use **two pointers**:

* `read` pointer to scan through `chars`
* `write` pointer to overwrite `chars` with the compressed result

Steps:

1. Initialize `read = 0` and `write = 0`.
2. While `read < chars.length`:

   * Count how many times `chars[read]` repeats.
   * Write the character at `write`, then increment `write`.
   * If count > 1, convert the count to characters and write each digit.

---

### ✅ Python Code:

```python
def compress(chars):
    write = 0
    read = 0
    
    while read < len(chars):
        char = chars[read]
        count = 0
        
        while read < len(chars) and chars[read] == char:
            read += 1
            count += 1
        
        chars[write] = char
        write += 1
        
        if count > 1:
            for digit in str(count):
                chars[write] = digit
                write += 1
    
    return write
```

---

### ⏱️ Time and Space Complexity:

* **Time:** O(n), where n is the length of `chars`
* **Space:** O(1), since the compression is done in-place

---

Let me know if you’d like a **dry run**, **C++ version**, or explanation of **edge cases** (like all unique characters).
Here's the **C++ version** of the solution for **[443. String Compression](https://leetcode.com/problems/string-compression/)** using the **two-pointer approach**:

---

### ✅ C++ Code:

```cpp
class Solution {
public:
    int compress(vector<char>& chars) {
        int write = 0;
        int read = 0;
        int n = chars.size();
        
        while (read < n) {
            char currentChar = chars[read];
            int count = 0;
            
            // Count occurrences of the current character
            while (read < n && chars[read] == currentChar) {
                read++;
                count++;
            }
            
            // Write the character
            chars[write++] = currentChar;
            
            // If count > 1, write the digits
            if (count > 1) {
                string countStr = to_string(count);
                for (char c : countStr) {
                    chars[write++] = c;
                }
            }
        }
        
        return write;
    }
};
```

---

### 🧪 Example:

Input:

```cpp
chars = ['a', 'a', 'b', 'b', 'c', 'c', 'c']
```

Output:

```cpp
6 // modified chars = ['a', '2', 'b', '2', 'c', '3']
```

---

### 🔧 Time & Space Complexity:

* **Time Complexity:** O(n)
* **Space Complexity:** O(1) – in-place compression

---

Let me know if you want a **dry run**, **edge case explanation**, or the **reverse: decompression** logic.
