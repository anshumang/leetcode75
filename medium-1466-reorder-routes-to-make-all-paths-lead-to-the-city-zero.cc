🧠 Key Insight:
Think of this as a graph traversal (BFS or DFS).

For each edge, if it's going away from 0, it needs to be reversed.

You can model the graph as bidirectional for traversal, but track the original direction separately.

✅ C++ Code (DFS Approach):

#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int minReorder(int n, vector<vector<int>>& connections) {
        vector<vector<int>> adj(n);
        unordered_set<string> directedEdges;

        // Build undirected graph and record original directions
        for (auto& conn : connections) {
            int from = conn[0], to = conn[1];
            adj[from].push_back(to);
            adj[to].push_back(from);
            directedEdges.insert(to_string(from) + "," + to_string(to));
        }

        int count = 0;

        function<void(int, int)> dfs = [&](int node, int parent) {
            for (int neighbor : adj[node]) {
                if (neighbor == parent) continue;
                if (directedEdges.count(to_string(node) + "," + to_string(neighbor)))
                    count++;  // This edge goes away from 0, needs reversal
                dfs(neighbor, node);
            }
        };

        dfs(0, -1);
        return count;
    }
};
