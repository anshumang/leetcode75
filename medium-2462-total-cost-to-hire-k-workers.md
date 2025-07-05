Sure! Here's a clear explanation of the LeetCode problem **"Total Cost to Hire K Workers"**.
Nov 05, 2022
---

### 🔗 Problem Link:

[Total Cost to Hire K Workers – LeetCode #2462](https://leetcode.com/problems/total-cost-to-hire-k-workers/description/)

---

### 🧾 Problem Summary:

You are given:

* An integer array `costs` where `costs[i]` is the cost of hiring the `i`-th worker.
* Two integers:
  `k` → the total number of workers you need to hire.
  `candidates` → number of candidates you can consider from **both ends** of the list at any time.

---

### ⚙️ Rules:

You **must** hire exactly `k` workers.
Each time, you can:

* Pick the **lowest-cost** worker from the **first `candidates`** or the **last `candidates`**.
* If there's a tie, pick the one with the **lower index** (from the front).

After hiring one worker:

* They are removed from the list.
* If possible, replace them by extending the window to include the next available person from their side.

---

### 🔄 Example:

**Input:**
`costs = [17,12,10,2,7,2,11,20,8]`, `k = 3`, `candidates = 4`

**Hiring Process:**
You can initially consider:

* First 4: `[17,12,10,2]`
* Last 4: `[2,11,20,8]`

Now repeatedly pick the **lowest cost** from these groups.

Steps:

1. Pick 2 (from front), now front = `[17,12,10]` + back = `[2,11,20,8]`
2. Pick 2 (from back), now back = `[11,20,8]`
3. Pick 8 (from back), done.

**Output:** `2 + 2 + 8 = 12`

---

### ✅ Constraints:

* `1 <= costs.length <= 10^5`
* `1 <= k, candidates <= costs.length`
* `1 <= costs[i] <= 10^5`

---

### 🧠 Intuition:

Use two **min-heaps** for the front and back halves.
Maintain a sliding window of candidates on both sides.
Always pick the cheapest option.

---

### ✅ C++ Code (Using `priority_queue`):

```cpp
class Solution {
public:
    long long totalCost(vector<int>& costs, int k, int candidates) {
        int n = costs.size();
        priority_queue<int, vector<int>, greater<int>> left, right;
        int i = 0, j = n - 1;

        // Initialize both heaps
        while (left.size() < candidates && i <= j) {
            left.push(costs[i++]);
        }
        while (right.size() < candidates && i <= j) {
            right.push(costs[j--]);
        }

        long long total = 0;
        while (k--) {
            if (!left.empty() && (right.empty() || left.top() <= right.top())) {
                total += left.top(); left.pop();
                if (i <= j) left.push(costs[i++]);
            } else {
                total += right.top(); right.pop();
                if (i <= j) right.push(costs[j--]);
            }
        }
        return total;
    }
};
```

---

Let me know if you want the **Python version**, a **visual diagram**, or a **dry-run** of the code!
Great observation — this is a subtle but **very important point** in the problem.

Let’s go back to the example to clarify:

---

### 🔁 Example:

```plaintext
costs = [17, 12, 10, 2, 7, 2, 11, 20, 8]
k = 3
candidates = 4
```

**Step 0 (initial setup):**
You consider:

* First 4 = `[17, 12, 10, 2]` → from left
* Last 4 = `[2, 11, 20, 8]` → from right

Note: 7 (index 4) is **not** in either group initially.

### 💡 Why?

Because:

* The left heap contains **only the first 4**: indices 0 to 3.
* The right heap contains **only the last 4**: indices 5 to 8.

`7` is at **index 4**, and it’s **not** included in either group at the beginning.

---

### ⏳ After hiring:

Let’s break it down step-by-step:

---

#### ✅ Step 1:

Pick **2** from left (`[17,12,10,2]`), remove it.
Add next available from the left: `costs[4] = 7` → now in left heap.

Heaps:

* Left: `[17,12,10,7]`
* Right: `[2,11,20,8]`

---

#### ✅ Step 2:

Pick **2** from right (`[2,11,20,8]`), remove it.
Next from right: already used 2 from index 5, now 4 elements already in the window.

Heaps:

* Left: `[17,12,10,7]`
* Right: `[8,11,20]`

---

#### ✅ Step 3:

Compare top of both heaps:

* Left: `7`
* Right: `8`

👉 Pick **7 from left**, not 8.

So if you saw `8` being picked instead of `7`, it was likely a **misinterpretation or mistake** in a given explanation or test output.

---

### ✅ Conclusion:

**7 *does* get picked** when it enters the heap.
But **initially it’s not available** because it's at index 4, and the candidate range only included the first 4 and last 4 elements.

---

Would you like me to do a full trace of the heap values step-by-step?
