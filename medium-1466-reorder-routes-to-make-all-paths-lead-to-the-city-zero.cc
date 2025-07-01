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
✅ C++ Code (Less Memory):
#include <vector>
using namespace std;

class Solution {
public:
    int minReorder(int n, vector<vector<int>>& connections) {
        vector<vector<int>> adj(n);       // Undirected adjacency list
        vector<vector<int>> directed(n);  // Original directed edges

        for (auto& conn : connections) {
            int from = conn[0], to = conn[1];
            adj[from].push_back(to);
            adj[to].push_back(from);
            directed[from].push_back(to);  // Only store original direction
        }

        vector<bool> visited(n, false);
        int count = 0;

        // DFS
        function<void(int)> dfs = [&](int node) {
            visited[node] = true;
            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    // If the original edge goes from node -> neighbor, it needs reversal
                    for (int to : directed[node]) {
                        if (to == neighbor) {
                            count++;
                            break;
                        }
                    }
                    dfs(neighbor);
                }
            }
        };

        dfs(0);
        return count;
    }
};
✅ C++ Code (BFS, Low Memory):
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int minReorder(int n, vector<vector<int>>& connections) {
        vector<vector<int>> adj(n);       // Undirected graph
        vector<vector<int>> directed(n);  // Tracks original direction: from -> to

        // Build graphs
        for (auto& conn : connections) {
            int from = conn[0], to = conn[1];
            adj[from].push_back(to);
            adj[to].push_back(from);
            directed[from].push_back(to);  // Store only one-way (from → to)
        }

        vector<bool> visited(n, false);
        queue<int> q;
        int count = 0;

        q.push(0);
        visited[0] = true;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    // Check if the edge is originally from node → neighbor
                    for (int to : directed[node]) {
                        if (to == neighbor) {
                            count++;
                            break;
                        }
                    }
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        return count;
    }
};
