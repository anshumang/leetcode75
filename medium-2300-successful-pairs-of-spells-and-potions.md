Here's the **C++ version** of the optimal solution to **"Successful Pairs of Spells and Potions"** using **binary search**:

---

### ✅ C++ Code (Using `std::lower_bound`)

```cpp
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        sort(potions.begin(), potions.end());
        int m = potions.size();
        vector<int> result;

        for (int spell : spells) {
            // Minimum potion needed so that spell * potion >= success
            long long minPotion = (success + spell - 1) / spell; // ceil(success / spell)

            // Find first potion >= minPotion using lower_bound
            auto it = lower_bound(potions.begin(), potions.end(), minPotion);
            int count = potions.end() - it;
            result.push_back(count);
        }

        return result;
    }
};
```

---

### 🔍 Explanation:

* `sort(potions.begin(), potions.end())`: allows binary search.
* `(success + spell - 1) / spell` is a neat way to do integer ceiling.
* `lower_bound()` returns the first position where potion ≥ `minPotion`.
* Subtracting gives how many potions satisfy the condition.

---

### 🧠 Time Complexity:

* Sorting: `O(m log m)`
* For each spell: `O(log m)` → total `O(n log m)`

---

Let me know if you want:

* A dry-run example
* The same logic with custom binary search
* Comparison with brute force for learning purposes
