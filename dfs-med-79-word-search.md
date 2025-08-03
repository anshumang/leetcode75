Nov 22, 2013
Here's a C++ implementation of the **Word Search** problem using **DFS with backtracking**:

### ✅ C++ Code:

```cpp
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dfs(board, word, i, j, 0))
                    return true;
            }
        }

        return false;
    }

private:
    bool dfs(vector<vector<char>>& board, const string& word, int i, int j, int index) {
        if (index == word.length()) return true;
        if (i < 0 || i >= board.size() ||
            j < 0 || j >= board[0].size() ||
            board[i][j] != word[index])
            return false;

        char temp = board[i][j];
        board[i][j] = '#';  // mark as visited

        // Explore all 4 directions
        bool found = dfs(board, word, i + 1, j, index + 1) ||
                     dfs(board, word, i - 1, j, index + 1) ||
                     dfs(board, word, i, j + 1, index + 1) ||
                     dfs(board, word, i, j - 1, index + 1);

        board[i][j] = temp;  // backtrack
        return found;
    }
};
```

### 🔍 Explanation:

* We try starting the search from each cell.
* Use DFS to check all 4 directions from the current cell.
* Use `#` to temporarily mark visited cells (avoiding using the same cell twice).
* Restore the cell value after backtracking.

### 📦 Example Usage:

```cpp
int main() {
    Solution sol;
    vector<vector<char>> board = {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'}
    };
    string word = "ABCCED";

    bool result = sol.exist(board, word);
    // Output: true
}
```

Let me know if you’d like a version with more debugging or visualization of the recursion stack.

Yes — **search pruning** is a key optimization technique to make the DFS faster, especially on larger boards. While the brute-force DFS explores every possible path, **pruning** lets us **cut off paths early** when we know they can't possibly lead to a solution.

---

### ✅ Here are common pruning strategies you can apply:

---

### 1. **Early termination using character count (pre-check)**

Before running DFS at all, **count characters in the board vs. the word**. If any character in the word appears more times than it does in the board — immediately return false.

#### ✨ Example:

```cpp
bool precheck(const vector<vector<char>>& board, const string& word) {
    unordered_map<char, int> boardCount, wordCount;
    for (auto& row : board)
        for (char c : row)
            boardCount[c]++;
    for (char c : word)
        wordCount[c]++;
    for (auto& [ch, count] : wordCount)
        if (boardCount[ch] < count)
            return false;
    return true;
}
```

---

### 2. **Reverse search: start from least frequent letter**

If the first letter of the word appears many times and the last letter is rare, it’s often better to **reverse the word** and start the DFS from rarer letters to reduce branching.

#### ✨ Example:

```cpp
if (count(word.begin(), word.end(), word[0]) > count(word.begin(), word.end(), word.back()))
    reverse(word.begin(), word.end());
```

---

### 3. **Direction order optimization**

If certain directions are more likely to succeed based on board layout (e.g. text is left-to-right), prefer those first. While subtle, this improves average performance.

---

### 4. **Early cutoff on depth**

For custom variations or time-constrained scenarios, you can optionally limit DFS depth or skip DFS from unlikely areas (e.g., if a corner has no matching neighbors).

---

### 🧠 Summary:

Yes, pruning improves performance significantly, especially when:

* The board is large (close to 6x6).
* The word has rare characters.
* Many DFS paths are invalid early.

Let me know if you’d like to add any of these to your current C++ code.

Here's your **enhanced C++ solution** with **reverse search optimization** (prune by starting from the rarer end of the word):

### ✅ Updated C++ Code with Reverse Search Pruning:

```cpp
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if (board.empty() || board[0].empty()) return false;

        // Reverse search optimization: start with rarer character
        if (charFrequency(board, word.front()) > charFrequency(board, word.back())) {
            reverse(word.begin(), word.end());
        }

        int m = board.size(), n = board[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dfs(board, word, i, j, 0))
                    return true;
            }
        }
        return false;
    }

private:
    // Helper to count how often a character appears on the board
    int charFrequency(const vector<vector<char>>& board, char target) {
        int count = 0;
        for (const auto& row : board)
            for (char c : row)
                if (c == target) ++count;
        return count;
    }

    bool dfs(vector<vector<char>>& board, const string& word, int i, int j, int index) {
        if (index == word.length()) return true;
        if (i < 0 || i >= board.size() || 
            j < 0 || j >= board[0].size() || 
            board[i][j] != word[index])
            return false;

        char temp = board[i][j];
        board[i][j] = '#'; // mark as visited

        bool found = dfs(board, word, i + 1, j, index + 1) ||
                     dfs(board, word, i - 1, j, index + 1) ||
                     dfs(board, word, i, j + 1, index + 1) ||
                     dfs(board, word, i, j - 1, index + 1);

        board[i][j] = temp; // backtrack
        return found;
    }
};
```

---

### 🔍 Optimization Summary:

* ✅ **`charFrequency`**: Counts how often a letter appears on the board.
* ✅ **`reverse(word.begin(), word.end())`**: Applied when the last letter is rarer — so we start DFS from a less common entry point to reduce search space.

---

Let me know if you also want to add **character frequency pre-check** or performance benchmarking!
Here's the **fully optimized C++ solution** including:

1. ✅ **Character frequency pre-check** (early exit if board lacks enough of any letter in the word)
2. ✅ **Reverse search pruning** (start from rarer end of the word)
3. ✅ **DFS with visited-cell marking and backtracking**

---

### ✅ Final C++ Code with All Optimizations:

```cpp
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if (board.empty() || board[0].empty()) return false;

        // Step 1: Frequency pre-check
        if (!hasEnoughLetters(board, word)) return false;

        // Step 2: Reverse search pruning based on rarer end
        if (charFrequency(board, word.front()) > charFrequency(board, word.back())) {
            reverse(word.begin(), word.end());
        }

        int m = board.size(), n = board[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dfs(board, word, i, j, 0))
                    return true;
            }
        }
        return false;
    }

private:
    bool hasEnoughLetters(const vector<vector<char>>& board, const string& word) {
        unordered_map<char, int> boardCount, wordCount;
        for (const auto& row : board)
            for (char c : row)
                boardCount[c]++;
        for (char c : word)
            wordCount[c]++;
        for (const auto& [ch, count] : wordCount) {
            if (boardCount[ch] < count) return false;
        }
        return true;
    }

    int charFrequency(const vector<vector<char>>& board, char target) {
        int count = 0;
        for (const auto& row : board)
            for (char c : row)
                if (c == target) ++count;
        return count;
    }

    bool dfs(vector<vector<char>>& board, const string& word, int i, int j, int index) {
        if (index == word.length()) return true;
        if (i < 0 || i >= board.size() || 
            j < 0 || j >= board[0].size() || 
            board[i][j] != word[index])
            return false;

        char temp = board[i][j];
        board[i][j] = '#';  // mark as visited

        bool found = dfs(board, word, i + 1, j, index + 1) ||
                     dfs(board, word, i - 1, j, index + 1) ||
                     dfs(board, word, i, j + 1, index + 1) ||
                     dfs(board, word, i, j - 1, index + 1);

        board[i][j] = temp;  // backtrack
        return found;
    }
};
```

---

### 🧪 Sample Test

```cpp
int main() {
    Solution sol;
    vector<vector<char>> board = {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'}
    };

    cout << boolalpha << sol.exist(board, "ABCCED") << endl;  // true
    cout << boolalpha << sol.exist(board, "SEE") << endl;     // true
    cout << boolalpha << sol.exist(board, "ABCB") << endl;    // false
    cout << boolalpha << sol.exist(board, "SFFF") << endl;    // false (fails pre-check)
}
```

---

Let me know if you'd like to also count recursive calls or add a timeout limiter for large boards!
