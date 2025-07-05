🔗 [Problem Link](https://leetcode.com/problems/reverse-linked-list/description/)

---

### ✅ Problem Summary:

Given the `head` of a **singly linked list**, reverse the list and return the new head.

---

### 🧠 Example:

```
Input:  1 → 2 → 3 → 4 → 5 → NULL  
Output: 5 → 4 → 3 → 2 → 1 → NULL
```

---

### 🧩 Approach: **Iterative Method**

We reverse the pointers one by one while traversing the list.

#### 🔄 Idea:

* Maintain `prev` and `curr` pointers
* At each step:

  * Save `next` node
  * Point `curr->next` to `prev`
  * Move `prev` and `curr` forward

---

### 💻 C++ Code (Iterative):

```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;

        while (curr) {
            ListNode* next_node = curr->next; // save next
            curr->next = prev;                // reverse pointer
            prev = curr;                      // move prev
            curr = next_node;                 // move curr
        }

        return prev; // new head
    }
};
```

---

### 🔁 Approach: **Recursive Version**

```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode* new_head = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return new_head;
    }
};
```

---

### ⏱️ Time & Space Complexity:

* **Time:** O(n) — every node is visited once
* **Space:**

  * Iterative: O(1)
  * Recursive: O(n) stack frames (can cause stack overflow on long lists)

---

---

## 🧠 Recursive Stack Trace:

We'll track the state of:

* `head`
* `new_head`
* Recursive calls

---

### 🔽 First Call: `reverseList(1)`

* `head = 1`, `head->next = 2`
* Recurse with `reverseList(2)`

---

### 🔽 Second Call: `reverseList(2)`

* `head = 2`, `head->next = 3`
* Recurse with `reverseList(3)`

---

### 🔽 Third Call: `reverseList(3)`

* `head = 3`, `head->next = NULL`
* Base case: return `head = 3`
* So `new_head = 3` for the second call

---

### 🔁 Back to Second Call (`head = 2`)

* `new_head = 3`
* Now do:

  ```cpp
  head->next->next = head;  // 3->next = 2
  head->next = nullptr;     // 2->next = nullptr
  ```
* Now `3 → 2 → NULL`
* Return `new_head = 3` to first call

---

### 🔁 Back to First Call (`head = 1`)

* `new_head = 3`
* Now do:

  ```cpp
  head->next->next = head;  // 2->next = 1
  head->next = nullptr;     // 1->next = nullptr
  ```
* Now `3 → 2 → 1 → NULL`
* Return `new_head = 3`

---

## ✅ Final Output:

```
3 → 2 → 1 → NULL
```

---

### 📌 Summary of Stack Unwind:

| Call (head) | What happens        | Resulting list so far |
| ----------- | ------------------- | --------------------- |
| 3           | base case, return 3 | 3                     |
| 2           | 3 → 2, break 2 → 3  | 3 → 2                 |
| 1           | 2 → 1, break 1 → 2  | 3 → 2 → 1             |

---
