class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        queue<pair<int, int>> q;
        int fresh = 0;
        
        // Find all initially rotten oranges and count fresh ones
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 2) {
                    q.push({i, j});
                } else if (grid[i][j] == 1) {
                    fresh++;
                }
            }
        }
        
        // If no fresh oranges, return 0
        if (fresh == 0) return 0;
        
        // Directions for 4-way movement (up, down, left, right)
        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        int time = 0;
        
        // BFS to spread the rot
        while (!q.empty()) {
            int size = q.size();
            bool rotted = false;
            
            // Process all oranges that are rotten at current time
            for (int i = 0; i < size; i++) {
                auto [row, col] = q.front();
                q.pop();
                
                // Check all 4 adjacent cells
                for (int d = 0; d < 4; d++) {
                    int newRow = row + dirs[d][0];
                    int newCol = col + dirs[d][1];
                    
                    // Check bounds and if cell contains fresh orange
                    if (newRow >= 0 && newRow < m && 
                        newCol >= 0 && newCol < n && 
                        grid[newRow][newCol] == 1) {
                        
                        // Rot the fresh orange
                        grid[newRow][newCol] = 2;
                        q.push({newRow, newCol});
                        fresh--;
                        rotted = true;
                    }
                }
            }
            
            // If we rotted any oranges this round, increment time
            if (rotted) time++;
        }
        
        // Return time if all oranges are rotten, otherwise -1
        return fresh == 0 ? time : -1;
    }
};

I'll solve the Rotting Oranges problem step by step.
This is a classic BFS (Breadth-First Search) problem where we need to simulate the rotting process spreading from initially rotten oranges to fresh ones.
Problem Analysis:

Grid contains: 0 (empty), 1 (fresh orange), 2 (rotten orange)
Each minute, rotten oranges spread to adjacent fresh oranges (4-directionally)
Return minimum time for all oranges to rot, or -1 if impossible

Approach:

Find all initially rotten oranges and count fresh oranges
Use BFS starting from all rotten oranges simultaneously
Track time elapsed and fresh oranges remaining
Return time when no fresh oranges left, or -1 if some remain
Key Points:

Multi-source BFS: We start BFS from all initially rotten oranges simultaneously, which correctly simulates the parallel spreading process.
Time tracking: We increment time only when at least one fresh orange rots in the current round.
Fresh orange counter: We track remaining fresh oranges to determine if all can be reached.
Structured bindings: Using auto [row, col] = q.front() for cleaner code (C++17 feature).

Time Complexity: O(m × n) - each cell is visited at most once
Space Complexity: O(m × n) - for the queue in worst case
Example walkthrough:
Initial: [[2,1,1],[1,1,0],[0,1,1]]
Minute 0: Start with rotten orange at (0,0)
Minute 1: (0,1) and (1,0) rot
Minute 2: (0,2) and (1,1) rot  
Minute 3: (1,2) and (2,1) rot
Minute 4: (2,2) rots
Result: 4 minutes
The solution handles edge cases like grids with no fresh oranges (return 0) and unreachable fresh oranges (return -1).
