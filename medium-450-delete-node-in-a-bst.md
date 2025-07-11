The LeetCode problem **[450. Delete Node in a BST](https://leetcode.com/problems/delete-node-in-a-bst/description/)** requires you to **delete a node with a given key** from a Binary Search Tree (BST) and return the new root.
Oct 31, 2016
---

### 🔍 Problem Summary:

Given the root of a BST and an integer `key`, delete the node with that value **while maintaining BST properties**, and return the root of the updated tree.

---

### ✅ BST Properties Recap:

* Left child < Node
* Right child > Node
* All nodes in the left/right subtrees must follow this property recursively

---

### 🧠 Deletion Cases:

There are **3 main cases** to handle when deleting a node:

1. **Node not found** → return `root` unchanged
2. **Node has no children (leaf)** → just remove it
3. **Node has one child** → return the non-null child
4. **Node has two children** → replace node with its **inorder successor** (smallest in right subtree), and delete the successor recursively

---

### ✅ C++ Code:

```cpp
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return nullptr;
        
        if (key < root->val) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->val) {
            root->right = deleteNode(root->right, key);
        } else {
            // Node found
            if (!root->left) return root->right;
            if (!root->right) return root->left;
            
            // Node with two children
            TreeNode* successor = findMin(root->right);
            root->val = successor->val;
            root->right = deleteNode(root->right, successor->val);
        }
        
        return root;
    }
    
private:
    TreeNode* findMin(TreeNode* node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }
};
```

---

### 🧪 Example:

Input:

```text
root = [5,3,6,2,4,null,7], key = 3
```

Output:

```text
[5,4,6,2,null,null,7]
```

Explanation: Node `3` is deleted and replaced by its inorder successor `4`.

---

### ⏱️ Time & Space Complexity:

* **Time Complexity:** O(h), where `h` is the height of the tree
  (O(log n) for balanced BST, O(n) for skewed)
* **Space Complexity:** O(h) for recursion stack

---

Let me know if you'd like:

* Python version
* Iterative version
* Visual explanation of each deletion case
