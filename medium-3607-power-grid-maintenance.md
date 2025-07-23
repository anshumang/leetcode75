Jul 05, 2025
### Intuition

The physical **grid-topology never changes** – taking a station offline does **not** remove its cables.
Hence every station belongs permanently to **one static connected component** (its *power grid*).

For every grid we only have to keep track of
*the set of stations that are still operational*
so that we can

* delete a station when a type-2 query turns it **offline**, and
* return the **smallest id that is still inside that set** when a type-1
  query is asked for any station of the same grid.

---

### Data structures

| purpose                                                       | structure                                                                      | operations                             |
| ------------------------------------------------------------- | ------------------------------------------------------------------------------ | -------------------------------------- |
| Find the grid‐id of a station                                 | **Disjoint Set Union** (union-find) built **once** from the `connections` list | `find(x)` in *α(c)*                    |
| Maintain the currently online stations of every grid in order | one `std::set<int>` per grid (ordered balanced BST)                            | `erase(x)` / `begin()` in *log (size)* |
| Remember whether a station is still online                    | `vector<char> online(c+1, 1)`                                                  | O(1)                                   |

Total memory: one parent array `c`, one `online` array `c`,
and each station stored exactly once inside exactly one `set`.

---

### Algorithm

```
1. Build DSU and unite all (u, v) from connections.
2. For every station i = 1..c
       sets[ find(i) ].insert(i)        # populate online-id sets
3. For every query in order:
       if type == 1 (maintenance on x):
            if online[x]                      → answer = x
            else
                 root = find(x)
                 if sets[root] is empty       → answer = -1
                 else                         → answer = *sets[root].begin()
       else  type == 2 (take x offline):
            if online[x] == 1:                # first time only
                 online[x] = 0
                 sets[ find(x) ].erase(x)
```

*Each query costs* **O( log c )** for the set operation
(plus *α(c)* for the DSU `find`, negligible).

With `|queries| ≤ 2·10⁵` and `c ≤ 10⁵` this easily fits in time.

---

### Proof of correctness

We prove by induction over the processed queries.

*Invariant I* –
For every grid `g`, `sets[g]` contains **exactly** the ids of the stations
that are *still online* in that grid, always kept in ascending order.

*Base*: after step 2 all stations are online and have been inserted
into the set of their grid, so *Invariant I* holds.

*Maintenance query* `[1, x]`

* If `online[x] = 1` we return `x`, which is the smallest operational id
  in its grid.
  (Because `x` itself is operational, any smaller id would have also been
  online and already returned by `begin()`; contradiction.)
* Otherwise `online[x] = 0`. By *Invariant I* the set of its grid contains
  **all and only** the still-online ids, so `*begin()` is precisely the
  smallest operational id, or the set is empty meaning none exist.
  The answer is therefore correct.

*Offline query* `[2, x]`

* If `online[x]` is already `0` nothing changes, *Invariant I* still holds.
* Otherwise we set `online[x] = 0` and erase `x` from its grid’s set,
  restoring *Invariant I*.

Thus by induction *Invariant I* is preserved forever and every answer
returned by a type-1 query is exactly what the statement asks for, proving
the algorithm correct.

---

### Complexity

| phase                 | time                    | memory   |            |          |
| --------------------- | ----------------------- | -------- | ---------- | -------- |
| Build DSU + fill sets | **O(n α(c) + c log c)** | **O(c)** |            |          |
| Each query            | **O(log c)**            | —        |            |          |
| All queries           | \*\*O(                  | queries  | log c)\*\* | **O(c)** |

`α(c)` is the inverse Ackermann function (≤ 5 for all practical sizes).

---

### C++ 17 implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

/* ---------- DSU ---------- */
struct DSU {
    vector<int> p, sz;
    DSU(int n): p(n+1), sz(n+1,1) { iota(p.begin(), p.end(), 0); }
    int find(int x){ return p[x]==x ? x : p[x]=find(p[x]); }
    void unite(int a,int b){
        a=find(a); b=find(b);
        if(a==b) return;
        if(sz[a]<sz[b]) swap(a,b);
        p[b]=a; sz[a]+=sz[b];
    }
};

vector<int> solve(int c,
                  const vector<array<int,2>>& connections,
                  const vector<array<int,2>>& queries)
{
    DSU dsu(c);
    for(auto e: connections) dsu.unite(e[0], e[1]);

    /* one ordered set per grid (index by DSU root) */
    vector< set<int> > grid(c+1);
    for(int i=1;i<=c;++i) grid[dsu.find(i)].insert(i);

    vector<char> online(c+1, 1);           // 1 = operational
    vector<int> answers;  answers.reserve(queries.size());

    for(auto q: queries){
        int type = q[0], x = q[1];
        if(type==1){                       // maintenance query
            if(online[x]) {                // station itself online
                answers.push_back(x);
            }else{
                int root = dsu.find(x);
                if(grid[root].empty())     // nobody left online
                    answers.push_back(-1);
                else
                    answers.push_back(*grid[root].begin());
            }
        }else{                             // take x offline
            if(online[x]){
                online[x]=0;
                grid[dsu.find(x)].erase(x);
            }
        }
    }
    return answers;
}

/* ---------- example ---------- */
/*
int main(){
    int c=5;
    vector<array<int,2>> con={{1,2},{2,3},{3,4},{4,5}};
    vector<array<int,2>> q={{1,3},{2,1},{1,1},{2,2},{1,2}};
    auto ans = solve(c, con, q);
    for(int v: ans) cout<<v<<" ";  // 3 2 3
}
*/
```

The program follows exactly the algorithm proven correct above and
meets the required `O((c+|queries|) log c)` performance bounds.
