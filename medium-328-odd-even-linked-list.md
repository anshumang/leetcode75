The problem [**Odd Even Linked List**](https://leetcode.com/problems/odd-even-linked-list/description/) asks you to rearrange a singly linked list such that all nodes at odd indices come before those at even indices, **while maintaining their relative order**.
Jan 24, 2016
---

### 🔹 Problem Summary

Given the `head` of a singly linked list, group all the nodes with **odd indices** together followed by the nodes with **even indices**, and return the reordered list.

> Note: The node positions (1-based indexing) determine whether a node is odd or even—not the values in the list.

---

### 🔹 Example

**Input:**
`head = [1,2,3,4,5]`
**Output:**
`[1,3,5,2,4]`

---

### 🔹 Constraints

* The number of nodes is in the range `[0, 10^4]`.
* `-10^6 <= Node.val <= 10^6`

---

### 🔹 Key Idea

You maintain two separate chains:

* One for **odd-indexed** nodes (1st, 3rd, 5th…),
* One for **even-indexed** nodes (2nd, 4th, 6th…),

Then connect the end of the odd list to the head of the even list.

---

### ✅ C++ Solution

```cpp
ListNode* oddEvenList(ListNode* head) {
    if (!head || !head->next) return head;

    ListNode* odd = head;
    ListNode* even = head->next;
    ListNode* evenHead = even;

    while (even && even->next) {
        odd->next = even->next;
        odd = odd->next;

        even->next = odd->next;
        even = even->next;
    }

    odd->next = evenHead;
    return head;
}
```

---

### 🔍 Dry Run on Input `[1,2,3,4,5]`

* `odd = 1`, `even = 2`, `evenHead = 2`
* Loop 1:

  * `odd->next = 3`, `odd = 3`
  * `even->next = 4`, `even = 4`
* Loop 2:

  * `odd->next = 5`, `odd = 5`
  * `even->next = NULL`, `even = NULL`
* Final: `odd->next = evenHead (2)`

Final list: `1 -> 3 -> 5 -> 2 -> 4`

---

Would you like a step-by-step visualization or a recursive version as well?
