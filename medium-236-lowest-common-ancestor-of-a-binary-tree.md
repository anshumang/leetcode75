🔗 [Problem Link](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/description/)

---

### ✅ Problem Summary:

Given a binary tree and two nodes `p` and `q`, return **the lowest node in the tree** that has **both `p` and `q` as descendants** (a node can be a descendant of itself).

---

### 🧠 Example:

```text
        3
       / \
      5   1
     / \ / \
    6  2 0  8
      / \
     7   4

Input: root = 3, p = 5, q = 1
Output: 3
```

LCA of nodes 5 and 1 is **3**.

---

### 🧩 Approach: DFS (Bottom-Up)

We traverse the tree and:

* If we find either `p` or `q`, return that node up the stack.
* If both left and right subtrees return non-null, the current node is the **LCA**.
* Otherwise, propagate non-null value upward.

---

### 💻 C++ Code:

```cpp
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || root == p || root == q) return root;

        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        if (left && right) return root; // p and q found in both sides
        return left ? left : right;    // one side contains both or one
    }
};
```

---

### ⏱️ Time & Space Complexity:

* **Time:** O(n) — visit each node once
* **Space:** O(h) — recursion stack, where `h` is the tree height

---

### ✅ Notes:

* Handles all binary trees (not just BSTs)
* Works even if `p` is ancestor of `q`, or vice versa

---

Let’s walk through a **step-by-step trace** of the recursive solution for **Lowest Common Ancestor of a Binary Tree**, using this example:

```
        3
       / \
      5   1
     / \ / \
    6  2 0  8
      / \
     7   4
```

We’re given:

* `p = 5`
* `q = 1`

Goal: Find **lowest common ancestor (LCA)** of 5 and 1.

---

### 🔁 C++ Recursive Function Recap:

```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root == p || root == q) return root;

    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);

    if (left && right) return root;
    return left ? left : right;
}
```

---

### 🧠 Step-by-Step Recursive Trace:

Start: `lowestCommonAncestor(root=3, p=5, q=1)`

#### 1️⃣ Root = 3

* Not `p` or `q`, recurse left and right

---

#### 2️⃣ Left Subtree: `lowestCommonAncestor(5, p=5, q=1)`

* `root == p` → return 5

✅ Left subtree returns `5`

---

#### 3️⃣ Right Subtree: `lowestCommonAncestor(1, p=5, q=1)`

* `root == q` → return 1

✅ Right subtree returns `1`

---

#### 🔙 Back to Root = 3:

* Left = 5
* Right = 1
* Both non-null → current node **3** is the **LCA**

**✅ Final Answer: 3**

---

### 🌳 Visual Recap:

```
Recursion stack:

lowestCommonAncestor(3)
├── left = lowestCommonAncestor(5) → returns 5
└── right = lowestCommonAncestor(1) → returns 1
⇒ returns 3
```

---

### 📌 Key Logic Recap:

* If one side returns `p` and the other returns `q` → current node is LCA
* If one side is null → continue searching in non-null side

---

Let me know if you'd like to trace a different pair like (7, 4) or (6, 4), or see how this differs for a **Binary Search Tree (BST)** version.

Great! Let's now trace the recursive **Lowest Common Ancestor** algorithm for nodes **6** and **4** in the same tree:

```
        3
       / \
      5   1
     / \ / \
    6  2 0  8
      / \
     7   4
```

You're finding the LCA of **nodes 6 and 4**.

---

## ✅ Step-by-Step Recursive Trace

We call:

```cpp
lowestCommonAncestor(root = 3, p = 6, q = 4)
```

---

### Step 1: At Node 3

* Node 3 is not 6 or 4
* Recurse left and right

---

### Step 2: Left Subtree → `lowestCommonAncestor(5, 6, 4)`

* Node 5 is not 6 or 4
* Recurse into left and right children

---

### Step 3: Left of 5 → `lowestCommonAncestor(6, 6, 4)`

* Base case: root == p (6) → return 6

✅ Left child of 5 returns `6`

---

### Step 4: Right of 5 → `lowestCommonAncestor(2, 6, 4)`

* Node 2 ≠ 6 or 4
* Recurse into 7 and 4

---

#### Left of 2 → `lowestCommonAncestor(7, 6, 4)`

→ Node 7 ≠ p/q, children are null → return `nullptr`

#### Right of 2 → `lowestCommonAncestor(4, 6, 4)`

→ Base case: root == q (4) → return 4

✅ Right child of 2 returns `4`

So node 2 has:

* Left: `nullptr`
* Right: `4`

→ Return `4` to caller (node 5)

---

### Step 5: Back at Node 5:

* Left = 6
* Right = 4

✅ Both are non-null → current node **5 is the LCA**

Return `5` to node 3

---

### Step 6: Right Subtree of 3 → `lowestCommonAncestor(1, 6, 4)`

* Node 1 ≠ 6 or 4, children don't match → return `nullptr`

---

### Final Step: Back at Root (3):

* Left = 5 (LCA from subtree)
* Right = `nullptr`

→ Return **5** as the final answer

---

## ✅ Final Answer: `5`

---

### 🌳 Summary Tree Trace:

```
lowestCommonAncestor(3)
├── left = lowestCommonAncestor(5)
│   ├── left = 6
│   └── right = lowestCommonAncestor(2)
│       └── right = 4
│   → returns 5 (both children non-null)
└── right = nullptr
⇒ returns 5
```

---

Let me know if you'd like this visualized or applied to another pair like (7, 8).

Here's a **visual representation** of the recursion and tree structure for finding the **Lowest Common Ancestor (LCA) of nodes 6 and 4** in the binary tree.

---

### 🧱 Tree Structure:

```
            3
          /   \
        5       1
      /   \    / \
     6     2  0   8
          / \
         7   4
```

You are finding the **LCA of 6 and 4**.

---

### 🔁 Recursive Calls Flow (DFS Tree Traversal):

We traverse the tree recursively and pass results back up the call stack:

```
LCA(3)
├── LCA(5)
│   ├── LCA(6) → returns 6 ✅
│   └── LCA(2)
│       ├── LCA(7) → nullptr
│       └── LCA(4) → returns 4 ✅
│       → returns 4
│   → left = 6, right = 4 → returns 5 ✅ (LCA)
└── LCA(1)
    ├── LCA(0) → nullptr
    └── LCA(8) → nullptr
    → returns nullptr

Final result from LCA(3): **5**
```

---

### 🧠 Twin Match Visualization:

```text
✔ LCA found at Node 5 because:

- Left Subtree of 5 → found node 6
- Right Subtree of 5 → found node 4

→ So 5 is the **lowest** node where both 6 and 4 are in separate subtrees
```

---

### 🟢 Final Visual Verdict:

```
LCA of 6 and 4 is:
        3
       /
     ✔5
     / \
    6   2
        \
        ✔4
```

✅ The LCA is **node 5**

---

Let me know if you'd like a version with arrows, animations, or tracing values in memory step-by-step!
