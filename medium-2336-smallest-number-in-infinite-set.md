The LeetCode problem **[Smallest Number in Infinite Set](https://leetcode.com/problems/smallest-number-in-infinite-set/)** is a **design problem** where you implement a class that behaves like an infinite set of positive integers — and supports two operations efficiently.

---

## 🧾 Problem Summary

You're to implement a class with the following:

### Operations:

* `popSmallest()`:
  Removes and returns the **smallest** number in the set.

* `addBack(num)`:
  Adds `num` back into the set *if* it was previously removed.

---

## ⚙️ Key Behavior:

* Initially, the set contains **all positive integers**: {1, 2, 3, 4, 5, ...}
* `popSmallest()` removes and returns the smallest number.
* `addBack(num)` restores a previously removed number **only once**.

---

## ✅ Constraints

* `1 <= num <= 1000`
* Up to `1000` operations

This makes it feasible to track things using a priority queue and a set.

---

## 💡 Core Idea

We **simulate** the infinite set using:

* An integer `current` that tracks the next smallest number not yet popped
* A **min-heap** (`priority_queue` or `set`) to hold any numbers that were "added back"
* A **set** to prevent duplicates in the heap

---

## 🧠 C++ Code

```cpp
#include <set>
#include <queue>

class SmallestInfiniteSet {
private:
    int current;
    set<int> addedBack;
public:
    SmallestInfiniteSet() {
        current = 1;
    }

    int popSmallest() {
        if (!addedBack.empty()) {
            int smallest = *addedBack.begin();
            addedBack.erase(addedBack.begin());
            return smallest;
        }
        return current++;
    }

    void addBack(int num) {
        if (num < current) {
            addedBack.insert(num); // set prevents duplicates
        }
    }
};
```

---

## 🔍 How it Works

* `current`: tracks the smallest number not yet used from the infinite range
* `addedBack`: stores numbers < `current` that were popped and then added back

  * It's a `set`, so it's always sorted and unique
* `popSmallest()`:

  * If `addedBack` has any values, use its smallest
  * Else return `current` and increment it
* `addBack(num)`:

  * Only add back if `num` has been popped (i.e. `< current`)
  * The `set` prevents adding duplicates

---

## 🧪 Example

```cpp
SmallestInfiniteSet s;
s.popSmallest();   // 1
s.popSmallest();   // 2
s.addBack(1);
s.popSmallest();   // 1 (added back)
s.popSmallest();   // 3
```

---

Let me know if you want a Python version or dry-run visual explanation!
