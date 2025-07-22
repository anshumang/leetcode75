Jul 05, 2025
### Think “rewind the clock”

Removing every edge whose `time ≤ t` is **equivalent** to
*keeping* only the edges with `time > t`.
So a value of `t` is feasible iff **the sub-graph made of edges whose
`time` > `t` has at least `k` connected components**.

If we look at the edges from the **latest to the earliest removal time**

```
time  9  9  8  6  6  4  ...
edge   ────  ─  ──  ──  ─
```

and **add** them back into an initially empty graph, the component count

```
n → n-1 → n-2 → …                (never increases)
```

can only go **down**.
The moment it drops *below* `k` we just crossed the last time-stamp
that still kept us at ≥ `k` components.
That time-stamp is exactly the **minimum** `t` we are looking for.

---

### Algorithm (DSU + one linear scan)

1. **Initial shortcut**
   Build a DSU with *all* edges.
   If the original graph already has ≥ `k` components, the answer is `0`
   (no edge has been removed yet).

2. **Sort edges by `time` descending**.

3. **Walk the timeline from future to past**

   ```
   components ← n
   for every group of edges having the same time T (from large to small):
       comps_before ← components
       for each (u,v, T) in the group:
           if union(u,v): components -= 1
       if comps_before ≥ k  and  components < k:
            return T        # first time we cross the threshold
   ```

4. If the loop ends without returning, `k > n` and the task is impossible:
   return `-1`.

Because every edge is processed once and DSU operations are *amortised*
`α(n)`, the algorithm runs in **O(E log E)** time for the sort and
`O(n)` memory.

---

### Correctness proof

*Lemma 1* – At step 3 the variable `components` always equals the number of
connected components in the graph that contains **exactly** the edges whose
`time` has been processed so far (those with `time` ≥ current `T`).

*Proof.*
Induction over the groups: initially the edge set is empty, so
`components = n` is correct.
Whenever we union `(u,v)` we merge two components, so the invariant
holds after every edge.

*Lemma 2* – Between two consecutive distinct time-stamps
`T_high > T_low` the component count never increases.

*Proof.*
We only **add** edges while scanning; adding edges can never split a component.

*Theorem* – The algorithm returns the minimum `t` such that removing all
edges with `time ≤ t` leaves at least `k` components, or `-1` if no such
`t` exists.

*Proof.*
Let `T*` be the time returned by the algorithm.
Immediately **before** processing the group `T*` we had
`components_before ≥ k` (checked in the `if`).
Immediately **after** we have `components_after < k`.
By Lemma 1 and the construction of the scan,
edges with `time > T*` are present in the first case and absent in the second.

Therefore

* with all edges of `time > T*` present (i.e. after removing those
  with `time ≤ T*`) the graph still has ≥ `k` components – `T*` is *feasible*;
* removing a **smaller** `t < T*` keeps one of the edges in the group
  `T*`, so the number of components remains `< k` – no smaller `t`
  is feasible.

Hence `T*` is the **minimum feasible time**, as required.
If the algorithm never returns, even the empty graph (all edges removed)
has `< k` components, so the answer is correctly `-1`.

---

### Reference implementation

```python
from collections import defaultdict

class DSU:
    def __init__(self, n: int):
        self.p = list(range(n))
        self.sz = [1]*n
        self.comp = n

    def find(self, x: int) -> int:
        while self.p[x] != x:
            self.p[x] = self.p[self.p[x]]
            x = self.p[x]
        return x

    def union(self, a: int, b: int) -> bool:
        ra, rb = self.find(a), self.find(b)
        if ra == rb:
            return False
        if self.sz[ra] < self.sz[rb]:
            ra, rb = rb, ra
        self.p[rb] = ra
        self.sz[ra] += self.sz[rb]
        self.comp -= 1
        return True


def minRemovalTime(n: int, edges: list[list[int]], k: int) -> int:
    if k > n:                       # impossible
        return -1

    # 1. components in the **original** graph
    dsu_all = DSU(n)
    for u, v, _ in edges:
        dsu_all.union(u, v)
    if dsu_all.comp >= k:
        return 0

    # 2. sort edges by time descending
    edges.sort(key=lambda e: -e[2])

    dsu = DSU(n)                    # start with no edges
    i = 0
    while i < len(edges):
        T = edges[i][2]             # current time-stamp
        comps_before = dsu.comp

        while i < len(edges) and edges[i][2] == T:
            dsu.union(edges[i][0], edges[i][1])
            i += 1

        if comps_before >= k and dsu.comp < k:
            return T

    return -1                       # even the full graph has < k comps
```

The code follows the exact steps proven correct above and meets the
`O(E log E)` time / `O(n)` space bounds.

Below is a compact, self-contained C++17 implementation of the **“walk back in time”** algorithm described earlier.

```cpp
#include <bits/stdc++.h>
using namespace std;

/* ---------- Disjoint-Set Union (union–find) ---------- */
struct DSU {
    vector<int> p, sz;
    int comps;                       // current number of connected components
    explicit DSU(int n): p(n), sz(n,1), comps(n) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {                // path-compressed find
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    bool unite(int a, int b) {       // union by size
        a = find(a);  b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
        --comps;
        return true;
    }
};

/* ---------- main routine ---------- */
long long minRemovalTime(int n,
                         vector<array<int,3>>& edges,   // {u, v, time}
                         int k)
{
    if (k > n) return -1;            // impossible

    /* 1.  How many components does the *original* graph have?
           If already ≥ k, we need no removals (t = 0).                */
    DSU dsu_full(n);
    for (auto &e : edges) dsu_full.unite(e[0], e[1]);
    if (dsu_full.comps >= k) return 0;

    /* 2.  Process edges from *latest* to *earliest* removal time. */
    sort(edges.begin(), edges.end(),
         [](const auto& a, const auto& b){ return a[2] > b[2]; }); // descending by time

    DSU dsu(n);                        // start with no edges (max components = n)
    size_t i = 0;
    while (i < edges.size()) {
        int T = edges[i][2];           // current time-stamp
        int comps_before = dsu.comps;

        /* add every edge that disappears exactly at time T */
        while (i < edges.size() && edges[i][2] == T) {
            dsu.unite(edges[i][0], edges[i][1]);
            ++i;
        }

        /* first moment we drop below k components → answer */
        if (comps_before >= k && dsu.comps < k)
            return T;
    }

    /* if we finish the loop, even after removing *all* edges we still
       have < k components ⇒ impossible                           */
    return -1;
}

/* ---------- usage example ---------- */
/*
int main() {
    int n = 5, k = 3;
    vector<array<int,3>> edges = {
        {0,1,4}, {1,2,6}, {3,4,5}, {2,3,2}
    };
    cout << minRemovalTime(n, edges, k) << '\n';
}
*/
```

### How it works — quick recap

1. **Feasibility at t = 0** – If the original graph already splits into ≥ k
   components, return 0.
2. **Sort edges by removal time (descending)** and **add them back** one
   batch at a time while tracking the component count with a DSU.
3. The first time the count crosses from **≥ k** to **< k** is the smallest
   time‐stamp `t` whose removal still leaves at least `k` components.
4. If that never happens, no time `t` makes the graph split into k
   components (return –1).

**Complexities**

|                | Cost                   |
| -------------- | ---------------------- |
| Sorting edges  | `O(E log E)`           |
| DSU operations | `O(E α(n))` (≈ linear) |
| Extra memory   | `O(n)`                 |

`α(n)` is the inverse Ackermann function—effectively a small constant.
