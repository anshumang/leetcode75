Jul 05, 2025
### Approach

1. **Filter valid coupons**

   For each index `i ∈ [0,n)` the coupon is valid iff

   * `!code[i].empty()` **and** `code[i]` matches the pattern <br>
     `^[A-Za-z0-9_]+$`  (alphanumerics or underscores only);
   * `businessLine[i]` is one of the four allowed categories;
   * `isActive[i] == true`.

2. **Sort**

   * Primary key – the business line in the fixed order
     `electronics  <  grocery  <  pharmacy  <  restaurant`.
   * Secondary key – `code` in normal lexicographical order.

Because `n ≤ 100`, straight-forward filtering and an `std::sort` with a
custom comparator are more than fast enough ( *O(n log n)* time,
*O(n)* extra memory).

---

### C++17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

/* helper: true iff s is non-empty and contains only A–Z a–z 0–9 _ */
bool isValidCode(const string& s) {
    if (s.empty()) return false;
    return all_of(s.begin(), s.end(), [](char c) {
        return isalnum(static_cast<unsigned char>(c)) || c == '_';
    });
}

/* maps a business line to an order index 0-3, or 4 (=invalid) */
int blIndex(const string& bl) {
    if (bl == "electronics") return 0;
    if (bl == "grocery")     return 1;
    if (bl == "pharmacy")    return 2;
    if (bl == "restaurant")  return 3;
    return 4;                                   // invalid
}

vector<string> validCoupons(vector<string> code,
                            vector<string> businessLine,
                            vector<bool>   isActive)
{
    const int n = code.size();
    struct Item { int blIdx; string code; };    // keep both keys
    vector<Item> keep;
    
    for (int i = 0; i < n; ++i) {
        int idx = blIndex(businessLine[i]);
        if (idx < 4 && isActive[i] && isValidCode(code[i]))
            keep.push_back({idx, code[i]});
    }
    sort(keep.begin(), keep.end(),
         [](const Item& a, const Item& b){
             return (a.blIdx != b.blIdx) ? a.blIdx < b.blIdx
                                         : a.code   < b.code;
         });
    vector<string> ans;
    ans.reserve(keep.size());
    for (auto& it : keep) ans.push_back(it.code);
    return ans;
}

/* ------------------ example driver ------------------
int main(){
    vector<string> code = {"SAVE20","","PHARMA5","SAVE@20"};
    vector<string> bl   = {"restaurant","grocery","pharmacy","restaurant"};
    vector<bool>   act  = {true,true,true,true};
    auto out = validCoupons(code, bl, act);     // ["PHARMA5", "SAVE20"]
    for (auto& s: out) cout << s << ' ';
    cout << '\n';
}
----------------------------------------------------- */
```

**Explanation of key points**

* `isValidCode` is written without `<regex>` to stay fast and lightweight.
* `blIndex` converts each business-line string to an integer rank; any
  unrecognised string gets rank 4 and is treated as invalid.
* The `Item` array is sorted with a lambda comparator that first compares
  the ranks, then the codes.

The function returns the list of valid coupon codes in exactly the order
required by the problem statement.
