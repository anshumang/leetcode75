### Intuition

Think of choosing a **threshold `T`** and **keeping only the edges whose weight ≤ `T`**.

* Every connected component that survives then has cost ≤ `T` by definition of cost (the largest edge inside) ([DEV Community][1]).
* If that graph already has ≤ `k` components we are done—additional edge removals can only **increase** the number of components and **reduce** their costs.

So the answer is simply the **smallest edge weight `T` for which the sub-graph made of edges ≤ `T` breaks into at most `k` components**.  This is a classic “grow the graph in ascending weight order” situation—exactly what Kruskal’s algorithm does.

---

### One-pass Kruskal / DSU algorithm

| step | action                                                                                                                              |
| ---- | ----------------------------------------------------------------------------------------------------------------------------------- |
| 1    | Sort `edges` by weight ascending.                                                                                                   |
| 2    | Start with `components = n` single-node components in a **Disjoint-Set Union** (union-find).                                        |
| 3    | Scan the sorted edges; for each edge `(u,v,w)`<br>  *if `u` and `v` belong to different sets* → `union(u,v)` and `components –= 1`. |
| 4    | As soon as `components ≤ k`, the current edge’s weight `w` is the minimum feasible `T`; **return `w`**.                             |
| 5    | Special case: if `k == n` we may delete every edge, so the answer is `0`.                                                           |

Because we touch each edge once after sorting, the cost is

* **Time** `O(E log E)` (sorting) + `O(E α(n))` (almost linear DSU), well within `10^5` edges.
* **Memory** `O(n)`.

The same result can also be found with a binary-search wrapper around “count components with edges ≤ T”, but the single linear scan is shorter and a bit faster.  Either way rests on the same observation about the threshold `T` ([DEV Community][1]).

---

### Proof of correctness

Let `T*` be the value returned by the algorithm and let `G_T` be the sub-graph containing exactly the edges of weight ≤ `T`.

1. **Feasibility.**
   When the algorithm stops we have processed all edges ≤ `T*`, and the DSU reports `components ≤ k`, so `G_{T*}` exhibits a partition with at most `k` components whose individual costs are ≤ `T*`. Therefore `T*` is attainable.

2. **Minimality.**
   For any `T < T*`, the algorithm never reached `components ≤ k` while processing edges ≤ `T`. Thus `G_T` has **more than `k` components**; no sequence of additional edge deletions can merge components, so no partition with ≤ `k` components exists at that smaller threshold. Hence no value `< T*` is feasible.

Because `T*` is feasible and every smaller `T` is not, `T*` is the minimum possible maximum component cost—exactly what the problem asks.

---

### C++ 17 implementation

```cpp
class Solution {
public:
    int minCost(int n, vector<vector<int>>& edges, int k) {
        if (k >= n) return 0;              // every vertex can stand alone

        sort(edges.begin(), edges.end(),
             [](const auto& a, const auto& b){ return a[2] < b[2]; });

        DSU dsu(n);
        int components = n;

        for (const auto& e : edges) {
            if (dsu.merge(e[0], e[1])) {   // a useful edge
                if (--components <= k)     // first time we reach ≤ k parts
                    return e[2];           // that edge’s weight is the answer
            }
        }
        return 0;                          // k == 1 and graph is connected
    }

private:
    struct DSU {
        vector<int> parent, rank;
        DSU(int n): parent(n), rank(n,0) { iota(parent.begin(), parent.end(), 0); }
        int find(int x){ return parent[x]==x ? x : parent[x]=find(parent[x]); }
        bool merge(int a, int b){
            a = find(a);  b = find(b);
            if (a == b) return false;
            if (rank[a] < rank[b]) swap(a,b);
            parent[b] = a;
            if (rank[a] == rank[b]) ++rank[a];
            return true;
        }
    };
};
```

The code mirrors the steps above and runs in well under a second for the full constraints.

[1]: https://dev.to/rohithv07/leetcode-3613-minimize-maximum-component-cost-45ah "Leetcode 3613. Minimize Maximum Component Cost - DEV Community"
can this go into an infinite recursion without a base case?
No—so long as the disjoint-set (DSU) structure is kept valid, that `find` can’t loop forever.

```cpp
int find(int x) {
    return parent[x] == x ? x          // base case: x is the root
                          : parent[x] = find(parent[x]);  // recurse up
}
```

### Why it always terminates

1. **Base case is explicit.**
   The ternary operator stops recursion when it reaches a node whose `parent` points to itself (`parent[x] == x`). Every set *must* have at least one such root node, because of the way we initialise the DSU:

   ```cpp
   for (int i = 0; i < n; ++i) parent[i] = i;   // each vertex is its own root
   ```

2. **Union never creates cycles.**
   `merge(a, b)` is only called on the *roots* of two **different** trees. It sets one root’s parent to the other:

   ```cpp
   parent[rootB] = rootA;
   ```

   This links two trees into a larger tree; no edge ever points back downward, so a cycle cannot arise. Without a cycle, every chain of parents is strictly shorter than the number of vertices, guaranteeing a finite recursion depth.

3. **Path compression only shortens chains.**
   The assignment `parent[x] = find(parent[x])` flattens the path from `x` to its root. It never lengthens a chain or changes a root’s parent, so it can’t introduce a loop either.

### Practical caveats

* **Corrupted parent array.**
  If something outside `find`/`merge` writes to `parent` incorrectly—e.g. `parent[x] = y` while `y` is *already* under `x`—then a cycle could appear and the recursion would indeed become infinite (until the stack overflows). But that’s a bug in the surrounding code, not in `find` itself.

* **Deep trees vs. stack depth.**
  In theory a very skew-shaped tree could have height `n`, so recursion depth could reach ≈10⁵ for the largest inputs. That will terminate, but on some systems it might blow the program stack. If you’re worried, rewrite `find` iteratively:

  ```cpp
  int find(int x) {
      int root = x;
      while (parent[root] != root) root = parent[root];   // climb to root
      while (parent[x] != x) {                            // path-compress
          int nxt = parent[x];
          parent[x] = root;
          x = nxt;
      }
      return root;
  }
  ```

In normal, correctly-implemented DSU code the recursive `find` is safe and always finishes.
Jul 12, 2025
