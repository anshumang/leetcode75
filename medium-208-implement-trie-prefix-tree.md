🔗 [Problem Link](https://leetcode.com/problems/implement-trie-prefix-tree/description/)

---

### ✅ Problem Summary:

Implement a Trie with the following methods:

* `insert(word)` → Insert a word into the trie
* `search(word)` → Return `true` if the word exists
* `startsWith(prefix)` → Return `true` if any word starts with the prefix

---

### 🧠 Example:

```cpp
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");   // true
trie.search("app");     // false
trie.startsWith("app"); // true
trie.insert("app");
trie.search("app");     // true
```

---

### 🧩 Trie Node Structure:

Each node should:

* Store pointers to child nodes (typically 26 for lowercase letters a–z)
* Optionally store a flag `is_end` to mark the end of a word

---

### 💻 C++ Implementation:

```cpp
class TrieNode {
public:
    TrieNode* children[26];
    bool is_end;

    TrieNode() {
        is_end = false;
        for (int i = 0; i < 26; ++i)
            children[i] = nullptr;
    }
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int i = c - 'a';
            if (!node->children[i])
                node->children[i] = new TrieNode();
            node = node->children[i];
        }
        node->is_end = true;
    }

    bool search(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int i = c - 'a';
            if (!node->children[i])
                return false;
            node = node->children[i];
        }
        return node->is_end;
    }

    bool startsWith(string prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            int i = c - 'a';
            if (!node->children[i])
                return false;
            node = node->children[i];
        }
        return true;
    }
};
```

---

### ⏱️ Time Complexity:

Let `n` = length of the word or prefix:

* `insert`: O(n)
* `search`: O(n)
* `startsWith`: O(n)

All operations are **very fast**, making Tries ideal for dictionary-style lookups and autocomplete.

---
Here is a **recursive implementation** of a **Trie** in **C++**, covering the three key methods:

* `insert(word)`
* `search(word)`
* `startsWith(prefix)`

---

### 💡 Key Idea:

Each operation (`insert`, `search`, `startsWith`) can be implemented recursively by:

* Moving one character at a time
* Passing the rest of the string into the recursive call
* Marking the end of the word with a flag (`is_end`)

---

### 💻 Recursive C++ Implementation:

```cpp
class TrieNode {
public:
    TrieNode* children[26];
    bool is_end;

    TrieNode() {
        is_end = false;
        fill(begin(children), end(children), nullptr);
    }
};

class Trie {
private:
    TrieNode* root;

    void insertRecursive(TrieNode* node, const string& word, int index) {
        if (index == word.length()) {
            node->is_end = true;
            return;
        }

        int i = word[index] - 'a';
        if (!node->children[i])
            node->children[i] = new TrieNode();

        insertRecursive(node->children[i], word, index + 1);
    }

    bool searchRecursive(TrieNode* node, const string& word, int index, bool fullWord) {
        if (!node) return false;
        if (index == word.length()) return fullWord ? node->is_end : true;

        int i = word[index] - 'a';
        return searchRecursive(node->children[i], word, index + 1, fullWord);
    }

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        insertRecursive(root, word, 0);
    }

    bool search(string word) {
        return searchRecursive(root, word, 0, true);
    }

    bool startsWith(string prefix) {
        return searchRecursive(root, prefix, 0, false);
    }
};
```

---

### 🧪 Example Usage:

```cpp
Trie* trie = new Trie();
trie->insert("apple");
trie->search("apple");   // true
trie->search("app");     // false
trie->startsWith("app"); // true
```

---

### 📌 Notes:

* This version uses index tracking for recursion instead of substring slicing to avoid repeated allocations.
* The same `searchRecursive` handles both `search` and `startsWith` using a `fullWord` flag.
