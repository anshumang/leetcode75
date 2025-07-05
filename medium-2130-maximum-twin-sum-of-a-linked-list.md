🔗 [Problem Link](https://leetcode.com/problems/maximum-twin-sum-of-a-linked-list/description/)

---

### ✅ Problem Summary:

Given a **linked list of even length**, a **twin** of node at index `i` is the node at index `n - 1 - i`.

You are to find the **maximum sum of a pair of twin nodes**.

---

### 🧠 Example:

```text
Input: head = [5,4,2,1]
Output: 6
Explanation: Twin pairs are:
- (5,1) → 5+1 = 6
- (4,2) → 4+2 = 6
Max = 6
```

---

### 🧩 Approach: Reverse Second Half + Compare

To achieve O(n) time and O(1) space, use the **two-pointer technique**:

1. Use slow and fast pointers to find the **middle** of the list.
2. **Reverse the second half** of the list.
3. Traverse both halves together, compute each twin sum, and track the max.
4. (Optional) Restore the list if needed.

---

### 💻 C++ Code:

```cpp
class Solution {
public:
    int pairSum(ListNode* head) {
        // Step 1: Find middle
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // Step 2: Reverse second half
        ListNode* prev = nullptr;
        while (slow) {
            ListNode* next = slow->next;
            slow->next = prev;
            prev = slow;
            slow = next;
        }

        // Step 3: Compare twin pairs
        int max_sum = 0;
        ListNode* first = head;
        ListNode* second = prev;  // reversed second half
        while (second) {
            max_sum = max(max_sum, first->val + second->val);
            first = first->next;
            second = second->next;
        }

        return max_sum;
    }
};
```

---

### ⏱️ Time & Space Complexity:

* **Time:** O(n)
* **Space:** O(1)

---

### ✅ Notes:

* Reversing the second half is key to constant space.
* Fast/slow pointers ensure we split the list in O(n).

---

Creating a **recursive version** for the **“Maximum Twin Sum of a Linked List”** is possible by leveraging the **call stack** to reach the end of the list, then calculating the twin sums while **unwinding** the recursion.

---

### ✅ Strategy:

1. Use a **left pointer** that moves forward during the recursive unwinding phase.
2. Use recursion to traverse to the **end** of the list (right pointer).
3. As the recursion unwinds:

   * Add `left->val + right->val`
   * Update max twin sum
   * Move `left` forward
4. Stop when `left` meets or passes `right`.

---

### 💻 C++ Code (Recursive):

```cpp
class Solution {
public:
    ListNode* left;
    int max_sum = 0;

    void dfs(ListNode* right) {
        if (!right) return;

        dfs(right->next);

        // calculate twin sum only until left crosses right
        if (left) {
            max_sum = max(max_sum, left->val + right->val);
            left = left->next;

            // stop when we meet the middle
            if (left == right || left->next == right) {
                left = nullptr;
            }
        }
    }

    int pairSum(ListNode* head) {
        left = head;
        dfs(head);
        return max_sum;
    }
};
```

---

### 🔍 How It Works:

* The `dfs(right)` goes to the end of the list (rightmost node).
* During the unwinding phase, `left` moves forward from the head, while `right` is moving back from the tail.
* When `left` and `right` meet or cross, stop further processing.

---

### ⏱️ Time & Space Complexity:

* **Time:** O(n)
* **Space:** O(n) due to recursive call stack

---

### ✅ When to Use This:

* When you're okay with O(n) space (e.g. small inputs)
