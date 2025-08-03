Oct 21, 2014
Here's the C++ solution for **inorder traversal of a binary tree**, both:

---

### ✅ 1. **Iterative version using a stack** (as requested for follow-up)

```cpp
#include <vector>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> st;
        TreeNode* current = root;

        while (current != nullptr || !st.empty()) {
            // Reach the leftmost node of the current node
            while (current != nullptr) {
                st.push(current);
                current = current->left;
            }

            // Current is null at this point
            current = st.top();
            st.pop();
            result.push_back(current->val);

            // Visit the right subtree
            current = current->right;
        }

        return result;
    }
};
```

---

### 🧪 Example Usage:

```cpp
#include <iostream>

int main() {
    Solution sol;

    // Tree: [1,null,2,3]
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);

    vector<int> result = sol.inorderTraversal(root);

    for (int val : result)
        cout << val << " ";  // Output: 1 3 2
}
```

---

### 🧠 Explanation (Iterative Inorder):

* Use a **stack** to simulate the recursive call stack.
* Traverse to the **leftmost node**, pushing each node on the stack.
* Pop from the stack, add the node to result, and move to its right subtree.

---

Let me know if you'd also like the **recursive version** or help building the tree from level-order input like `[1,null,2,3]`.

Here’s the **recursive version** of the **inorder traversal** for a binary tree in C++.

---

### ✅ 2. Recursive Inorder Traversal (Simple & Elegant)

```cpp
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        dfs(root, result);
        return result;
    }

private:
    void dfs(TreeNode* node, vector<int>& result) {
        if (!node) return;
        dfs(node->left, result);      // Left
        result.push_back(node->val);  // Root
        dfs(node->right, result);     // Right
    }
};
```

---

### 🧪 Usage Example:

```cpp
#include <iostream>

int main() {
    Solution sol;

    // Tree: [1,null,2,3]
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);

    vector<int> result = sol.inorderTraversal(root);

    for (int val : result)
        cout << val << " ";  // Output: 1 3 2
}
```

---

### 🧠 Summary:

* **Recursive version** is easier to write and read.
* **Iterative version** avoids function call overhead and is needed when recursion depth may be large (not needed here due to constraint `n ≤ 100`).

Let me know if you want:

* A function to build a tree from level-order input (like `[1,null,2,3]`)
* A postorder or preorder version too
* Performance comparison between iterative and recursive versions
