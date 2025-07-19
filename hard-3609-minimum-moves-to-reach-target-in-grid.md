### Key observation – work **backwards**

Each forward move

```
(x , y) ──► (x+m , y)   or   (x , y+m)        where m = max(x , y)
```

*strictly enlarges* the larger coordinate, and never decreases either of them.
So from the target `(tx, ty)` we can only move **to smaller points**.
Going backward is therefore a finite search that always marches toward the start.

---

### What did the previous state look like?

Assume without loss of generality `X ≥ Y` (the other case is symmetric).

| backward rule                                                         | when it applies                                  | why                                                                                                       |
| --------------------------------------------------------------------- | ------------------------------------------------ | --------------------------------------------------------------------------------------------------------- |
| **halve the larger coordinate**<br>`(X , Y) → (X/2 , Y)`              | `X` is **even** **and** `X ≥ 2 Y`                | Forward step was “double the max”: `(X/2,Y) → (2·X/2= X , Y)`                                             |
| **subtract the smaller**<br>`(X , Y) → (X-Y , Y)`                     | `Y < X < 2 Y`                                    | Forward step was “add the max to the smaller”: `(X-Y , Y) → ((X-Y)+Y = X , Y)`                            |
| **equal coordinates**<br>`(c , c) → (0 , c)` *or* `(c , c) → (c , 0)` | always, unless we have already reached the start | The only way to make both coordinates equal is to add `c` to the *zero* coordinate in the previous state. |

The table shows *all* possible predecessors, and each rule
**reduces at least one coordinate**, so the reverse search always finishes.

Because every state has **≤ 2 predecessors**, the search tree is tiny
(depth is at most ≈ 60 for coordinates up to 10⁹),
so a plain breadth-first search finds the **minimum** number of moves.

---

### Algorithm

```text
0. If (sx,sy) == (tx,ty)                     → return 0
1. queue ← {(tx, ty, 0)}                     # (x, y, distance)
2. visited ← { (tx, ty) }

3. while queue not empty:
       (x, y, d) ← pop queue
       if (x, y) == (sx, sy)                 → return d        # hit start
       if x < sx or y < sy                   → continue        # outside box

       for each predecessor (px, py) given by the rules above:
           if (px, py) not in visited:
               push (px, py, d+1)
               visited ← visited ∪ {(px, py)}

4. If the loop ends, start is unreachable      → return –1
```

---

### Correctness proof

We prove that the algorithm outputs the minimum number of moves.

*Soundness* – Every edge we traverse backwards is the exact inverse of a legal
forward move (table above), so any path we build corresponds to a valid
forward sequence from `(sx, sy)` to `(tx, ty)`.

*Completeness* – Every legal forward move fits one of the three patterns,
hence every legal state has been given **all** of its predecessors.
Therefore the reverse graph explored by BFS contains **every** valid route
from the start to the target.

*Optimality* – Breadth-first search visits states in non-decreasing distance
from `(tx, ty)`.
The first time it reaches `(sx, sy)` it has followed the **shortest**
back-to-front path, which is the same length as the shortest
front-to-back path we are asked for.

---

### Complexity analysis

*Each iteration* visits one grid point and enqueues at most 2 predecessors,
and the depth of the tree is `O(log max(tx,ty))` (every step at least halves
or subtracts a *non-zero* number).

```
Time   :  O(log max(tx,ty))      ≤ ~60 for 10^9
Memory :  O(log max(tx,ty))      (visited set + queue)
```

Both are easily inside the limits.

---

### Reference implementation

#### Python 3

```python
from collections import deque

def minMoves(sx: int, sy: int, tx: int, ty: int) -> int:
    if (sx, sy) == (tx, ty):
        return 0

    def predecessors(x: int, y: int):
        if x > y:                                           # X ≥ Y
            if x % 2 == 0 and x // 2 >= y:                  # halve
                yield (x // 2, y)
            if x < 2 * y:                                   # subtract
                yield (x - y, y)
        elif y > x:                                         # Y ≥ X
            if y % 2 == 0 and y // 2 >= x:
                yield (x, y // 2)
            if y < 2 * x:
                yield (x, y - x)
        else:                                               # x == y
            yield (0, y)
            yield (x, 0)

    q   = deque([(tx, ty, 0)])      # BFS from the target
    seen = {(tx, ty)}

    while q:
        x, y, d = q.popleft()
        if (x, y) == (sx, sy):
            return d
        if x < sx or y < sy:        # outside the rectangle that can still reach start
            continue
        for px, py in predecessors(x, y):
            if (px, py) not in seen:
                seen.add((px, py))
                q.append((px, py, d + 1))
    return -1
```

#### C++17

```cpp
class Solution {
    using ll = long long;
    struct State { ll x, y, d; };
    struct Hash {
        size_t operator()(const pair<ll,ll>& p) const {
            return (p.first << 32) ^ p.second;
        }
    };
public:
    int minMoves(long long sx, long long sy,
                 long long tx, long long ty) {

        if (sx == tx && sy == ty) return 0;

        auto push = [&](ll x,ll y,ll d, queue<State>& q,
                        unordered_set<pair<ll,ll>,Hash>& seen) {
            if (x < sx || y < sy) return;
            if (seen.emplace(x,y).second) q.push({x,y,d});
        };

        queue<State> q;
        unordered_set<pair<ll,ll>,Hash> seen;
        q.push({tx,ty,0});
        seen.emplace(tx,ty);

        while (!q.empty()) {
            auto [x,y,d] = q.front(); q.pop();
            if (x == sx && y == sy) return (int)d;

            if (x > y) {
                if (!(x & 1) && x/2 >= y) push(x/2,y,d+1,q,seen);
                if (x < 2*y)              push(x-y,y,d+1,q,seen);
            } else if (y > x) {
                if (!(y & 1) && y/2 >= x) push(x,y/2,d+1,q,seen);
                if (y < 2*x)              push(x,y-x,d+1,q,seen);
            } else {                      // x == y
                push(0,y,d+1,q,seen);
                push(x,0,d+1,q,seen);
            }
        }
        return -1;                        // unreachable
    }
};
```

Both versions implement the backward-BFS exactly as described,
returning the minimum number of moves or `-1` when the target cannot be reached.

Jul 05, 2025
