Here’s a straight-forward way to process the string—just keep a mutable buffer and apply each rule exactly as stated.

---

### Algorithm

```
result ← empty list   // we’ll treat it as a dynamic array of chars

for ch in s:
    if 'a' ≤ ch ≤ 'z':      # rule 1
        append ch to result
    elif ch == '*':         # rule 2
        if result: pop last char
    elif ch == '#':         # rule 3
        result.extend(result)   # duplicate in-place
    else:                   # ch == '%', rule 4
        result.reverse()
return string(result)
```

### Correctness proof (sketch)

We proceed by induction over the characters of `s`.

*Base*: Before reading any symbol, `result` is the empty string—exactly what the specification requires.

*Inductive step*:
Assume `result` is correct after processing the first `i−1` symbols.

* If the `i`-th symbol is a letter, we append it—matching rule 1.
* If it is `'*'`, we remove the last character when present—matching rule 2.
* If it is `'#'`, we concatenate `result` with itself—matching rule 3.
* If it is `'%'`, we reverse `result`—matching rule 4.
  In every case the new `result` equals what the statement prescribes, completing the induction. Therefore the algorithm is correct.

### Complexity analysis

* `|s| ≤ 20`, so even the worst-case duplication is tiny.
* Each operation is *amortised* $1$ on a Python list, giving **O(|s|)** time and ≤ 40 characters space in the worst possible expansion—utterly negligible.

### Reference implementations

#### Python 3

```python
class Solution:
    def processString(self, s: str) -> str:
        res = []
        for ch in s:
            if ch.isalpha():           # lowercase letter
                res.append(ch)
            elif ch == '*':
                if res:
                    res.pop()
            elif ch == '#':
                res.extend(res)        # duplicate
            else:  # ch == '%'
                res.reverse()          # reverse in place
        return ''.join(res)
```

#### C++ 17

```cpp
class Solution {
public:
    string processString(string s) {
        string res;
        for (char ch : s) {
            if (islower(ch)) {
                res.push_back(ch);
            } else if (ch == '*') {
                if (!res.empty()) res.pop_back();
            } else if (ch == '#') {
                res += res;            // duplicate
            } else { // '%'
                reverse(res.begin(), res.end());
            }
        }
        return res;
    }
};
```

Both versions implement the algorithm exactly as described and run in constant time for the given constraints.
Jul 12, 2025
