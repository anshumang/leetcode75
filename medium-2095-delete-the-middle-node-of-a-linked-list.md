🔗 [Problem Link](https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/description/)

---

### ✅ Problem Summary:

Given the `head` of a singly linked list, **delete the middle node**, and return the head of the modified list.

* If the list has `n` nodes, the **middle is the ⌊n/2⌋-th node (0-based index)**.
* If the list has only one node, return `nullptr`.

---

### 🧠 Example:

```
Input: head = [1,3,4,7,1,2,6]
Output: [1,3,4,1,2,6]  // (middle node 7 is removed)
```

---

### 🧩 Approach: Slow & Fast Pointers

1. Use two pointers:

   * `slow` moves 1 step at a time
   * `fast` moves 2 steps at a time
2. Track the node **before `slow`** using a `prev` pointer
3. When `fast` reaches the end:

   * `slow` is at the middle
   * Remove `slow` using `prev->next = slow->next`

---

### 💻 C++ Code:

```cpp
class Solution {
public:
    ListNode* deleteMiddle(ListNode* head) {
        if (!head || !head->next) return nullptr;

        ListNode* slow = head;
        ListNode* fast = head;
        ListNode* prev = nullptr;

        while (fast && fast->next) {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        // delete the middle node
        prev->next = slow->next;
        delete slow;

        return head;
    }
};
```

---

### ⏱️ Time & Space Complexity:

* **Time:** O(n) — single pass through the list
* **Space:** O(1) — no extra data structures

---

### ✅ Notes:

* Handles edge case of 1-node list: returns `nullptr`
* Efficient in both time and memory

---

A **recursive approach** to deleting the middle node of a singly linked list is possible, but it's more complex than the iterative method. The key idea is to use recursion to:

* Traverse the list and **count the index** during the call stack **unwinding**
* When the index matches the **middle**, **skip** that node

---

### ✅ Strategy:

1. First, compute the **length** of the list.
2. Use a recursive function to traverse from the head.
3. When the current index is equal to `length / 2`, **skip the current node** by returning `curr->next`.
4. Otherwise, rebuild the list as recursion unwinds.

---

### 💻 C++ Code (Recursive):

```cpp
class Solution {
public:
    int getLength(ListNode* node) {
        int len = 0;
        while (node) {
            len++;
            node = node->next;
        }
        return len;
    }

    ListNode* deleteMiddleHelper(ListNode* node, int index, int middle) {
        if (!node) return nullptr;

        if (index == middle) {
            // skip this node (delete it)
            ListNode* temp = node->next;
            delete node;
            return temp;
        }

        node->next = deleteMiddleHelper(node->next, index + 1, middle);
        return node;
    }

    ListNode* deleteMiddle(ListNode* head) {
        if (!head || !head->next) return nullptr;

        int len = getLength(head);
        int mid = len / 2;

        return deleteMiddleHelper(head, 0, mid);
    }
};
```

---

### 🧠 Example Walkthrough:

For input `[1,2,3,4,5]`:

* Length = 5 → middle index = `2`
* Recursion hits node with value `3` at index 2 and skips it
* Final list becomes: `[1,2,4,5]`

---

### ⏱️ Time & Space Complexity:

* **Time:** O(n) for both length computation and traversal
* **Space:** O(n) recursive stack

---

### 📝 Notes:

* The recursive version is elegant but not space-optimal (due to call stack)
