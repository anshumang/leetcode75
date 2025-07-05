✅ Problem Summary:
You're given:

A 2D maze grid with:

'.' representing open path

'+' representing walls

An entrance position (x, y) (not on the boundary)

👉 Your task: Find the nearest exit from the entrance. An exit is any open cell on the boundary other than the entrance itself.

Return the minimum number of steps to reach an exit, or -1 if no exit is reachable.

🧠 Example:
maze = [
  ['+','+','.','+'],
  ['.','.','.','+'],
  ['+','+','+','.']
]
entrance = [1,2]

Starting at (1,2), shortest path to boundary is:

(1,2) → (1,1) → (1,0) → ✅ Exit in 2 steps

Output: 2

🧩 Approach: BFS (Shortest Path in Unweighted Graph)
Since each move has equal cost (1 step), BFS guarantees the shortest path.

Start from entrance

Use a queue to explore in all 4 directions

Mark visited cells as walls ('+')

Stop when you reach the first boundary cell (excluding entrance)

class Solution {
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        int m = maze.size(), n = maze[0].size();
        queue<pair<int, int>> q;
        q.push({entrance[0], entrance[1]});
        maze[entrance[0]][entrance[1]] = '+';  // mark visited

        int steps = 0;
        vector<pair<int, int>> directions = {{1,0}, {-1,0}, {0,1}, {0,-1}};

        while (!q.empty()) {
            int size = q.size();
            steps++;
            for (int i = 0; i < size; ++i) {
                auto [x, y] = q.front(); q.pop();
                for (auto [dx, dy] : directions) {
                    int nx = x + dx, ny = y + dy;
                    if (nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
                    if (maze[nx][ny] == '.') {
                        // if boundary and not entrance
                        if (nx == 0 || ny == 0 || nx == m-1 || ny == n-1) {
                            return steps;
                        }
                        maze[nx][ny] = '+'; // mark visited
                        q.push({nx, ny});
                    }
                }
            }
        }
        return -1;
    }
};

⏱️ Time & Space Complexity:
Time: O(m × n) — each cell is visited once

Space: O(m × n) — queue in worst case
