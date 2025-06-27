class Solution {
public:
    // Approach 1: Optimized DP with O(n) space - Most Efficient
    int minFallingPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        if (n == 1) return grid[0][0];
        
        // For each row, we only need to track:
        // 1. The minimum value and its column index
        // 2. The second minimum value (for when we can't use the minimum)
        
        // Initialize with first row
        int firstMin = 0, secondMin = 0;
        int firstMinCol = -1;
        
        for (int col = 0; col < n; col++) {
            if (firstMinCol == -1 || grid[0][col] < firstMin) {
                secondMin = firstMin;
                firstMin = grid[0][col];
                firstMinCol = col;
            } else if (grid[0][col] < secondMin) {
                secondMin = grid[0][col];
            }
        }
        
        // Process remaining rows
        for (int row = 1; row < n; row++) {
            int newFirstMin = INT_MAX, newSecondMin = INT_MAX;
            int newFirstMinCol = -1;
            
            for (int col = 0; col < n; col++) {
                // Choose minimum from previous row (excluding same column)
                int prevMin = (col == firstMinCol) ? secondMin : firstMin;
                int currentSum = grid[row][col] + prevMin;
                
                // Update minimum and second minimum for current row
                if (currentSum < newFirstMin) {
                    newSecondMin = newFirstMin;
                    newFirstMin = currentSum;
                    newFirstMinCol = col;
                } else if (currentSum < newSecondMin) {
                    newSecondMin = currentSum;
                }
            }
            
            firstMin = newFirstMin;
            secondMin = newSecondMin;
            firstMinCol = newFirstMinCol;
        }
        
        return firstMin;
    }
    
    // Approach 2: Standard DP with O(n²) space - More readable
    int minFallingPathSumStandard(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
        
        // Initialize first row
        for (int col = 0; col < n; col++) {
            dp[0][col] = grid[0][col];
        }
        
        // Fill DP table
        for (int row = 1; row < n; row++) {
            for (int col = 0; col < n; col++) {
                // Check all columns from previous row except same column
                for (int prevCol = 0; prevCol < n; prevCol++) {
                    if (prevCol != col) {
                        dp[row][col] = min(dp[row][col], 
                                         dp[row-1][prevCol] + grid[row][col]);
                    }
                }
            }
        }
        
        // Find minimum in last row
        int result = INT_MAX;
        for (int col = 0; col < n; col++) {
            result = min(result, dp[n-1][col]);
        }
        
        return result;
    }
    
    // Approach 3: Space-optimized DP with O(n) space
    int minFallingPathSumSpaceOptimized(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<int> prev(grid[0]); // Previous row DP values
        
        for (int row = 1; row < n; row++) {
            vector<int> curr(n, INT_MAX);
            
            for (int col = 0; col < n; col++) {
                // Check all previous columns except same column
                for (int prevCol = 0; prevCol < n; prevCol++) {
                    if (prevCol != col) {
                        curr[col] = min(curr[col], prev[prevCol] + grid[row][col]);
                    }
                }
            }
            
            prev = curr;
        }
        
        return *min_element(prev.begin(), prev.end());
    }
    
    // Approach 4: Recursive with memoization
    int minFallingPathSumMemo(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> memo(n, vector<int>(n, INT_MAX));
        
        int result = INT_MAX;
        for (int col = 0; col < n; col++) {
            result = min(result, dfs(grid, 0, col, memo));
        }
        
        return result;
    }
    
private:
    int dfs(vector<vector<int>>& grid, int row, int col, vector<vector<int>>& memo) {
        int n = grid.size();
        
        // Base case: reached last row
        if (row == n - 1) {
            return grid[row][col];
        }
        
        // Check memoization
        if (memo[row][col] != INT_MAX) {
            return memo[row][col];
        }
        
        // Try all possible next positions (all columns except same column)
        int minPath = INT_MAX;
        for (int nextCol = 0; nextCol < n; nextCol++) {
            if (nextCol != col) {
                minPath = min(minPath, dfs(grid, row + 1, nextCol, memo));
            }
        }
        
        memo[row][col] = grid[row][col] + minPath;
        return memo[row][col];
    }
};

// Helper class for testing and demonstration
class FallingPathDemo {
public:
    void demonstrateAlgorithm(vector<vector<int>>& grid) {
        int n = grid.size();
        
        cout << "Grid:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << setw(3) << grid[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
        
        // Show DP table construction
        vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
        
        // Initialize first row
        for (int col = 0; col < n; col++) {
            dp[0][col] = grid[0][col];
        }
        
        cout << "DP Table construction:\n";
        cout << "Row 0: ";
        for (int col = 0; col < n; col++) {
            cout << setw(3) << dp[0][col] << " ";
        }
        cout << "\n";
        
        // Fill remaining rows
        for (int row = 1; row < n; row++) {
            for (int col = 0; col < n; col++) {
                for (int prevCol = 0; prevCol < n; prevCol++) {
                    if (prevCol != col) {
                        dp[row][col] = min(dp[row][col], 
                                         dp[row-1][prevCol] + grid[row][col]);
                    }
                }
            }
            
            cout << "Row " << row << ": ";
            for (int col = 0; col < n; col++) {
                cout << setw(3) << dp[row][col] << " ";
            }
            cout << "\n";
        }
        
        int result = *min_element(dp[n-1].begin(), dp[n-1].end());
        cout << "\nMinimum falling path sum: " << result << "\n";
    }
};
