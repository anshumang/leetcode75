The LeetCode problem [**Dota2 Senate**](https://leetcode.com/problems/dota2-senate/description/) is a **simulation and greedy queue** problem.
May 28, 2025
---

### 🔹 Problem Summary

Given a string `senate` composed of characters `'R'` (Radiant) and `'D'` (Dire), simulate a turn-based ban system:

* Each senator can **ban one opposing senator**.
* The process continues in rounds.
* A banned senator cannot ban or vote.
* The **order** of senators remains cyclic.

Return **which party will win**: `"Radiant"` or `"Dire"`.

---

### 🔸 Example

**Input:**

```
"RDD"
```

**Output:**

```
"Dire"
```

---

### 🔹 Intuition

Use **two queues** to track indices of `'R'` and `'D'`. At each round:

* The senator with the smaller index gets to ban the other.
* They go to the back of the queue with `index + n` (simulate next round).

---

### ✅ C++ Code Using Queues

```cpp
class Solution {
public:
    string predictPartyVictory(string senate) {
        int n = senate.length();
        queue<int> radiant, dire;

        for (int i = 0; i < n; ++i) {
            if (senate[i] == 'R') radiant.push(i);
            else dire.push(i);
        }

        while (!radiant.empty() && !dire.empty()) {
            int r = radiant.front(); radiant.pop();
            int d = dire.front(); dire.pop();

            if (r < d) 
                radiant.push(r + n);  // Radiant bans Dire
            else 
                dire.push(d + n);     // Dire bans Radiant
        }

        return radiant.empty() ? "Dire" : "Radiant";
    }
};
```

---

### 🔹 Time and Space Complexity

* **Time:** O(n), each senator acts once per round
* **Space:** O(n) for queues

---

Would you like a **step-by-step trace**, a **greedy without queues version**, or code in **Python** or **Java**?
