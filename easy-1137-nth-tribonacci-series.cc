// Approach 1: Dynamic Programming (Tabulation)
class Solution {
public:
    int tribonacci(int n) {
        if (n == 0) return 0;
        if (n == 1 || n == 2) return 1;

        vector<int> dp(n + 1);
        dp[0] = 0;
        dp[1] = dp[2] = 1;

        for (int i = 3; i <= n; ++i) {
            dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
        }

        return dp[n];
    }
};
// Approach 2: Constant Space Optimization
class Solution {
public:
    int tribonacci(int n) {
        if (n == 0) return 0;
        if (n == 1 || n == 2) return 1;

        int a = 0, b = 1, c = 1;
        for (int i = 3; i <= n; ++i) {
            int temp = a + b + c;
            a = b;
            b = c;
            c = temp;
        }

        return c;
    }
};
// Both solutions run in O(n) time, but the second one uses O(1) space, which is optimal given the small constraint (n ≤ 37).
// Approach: Recursion with Memoization (Top-Down DP)
class Solution {
public:
    int tribonacci(int n) {
        vector<int> memo(n + 1, -1);  // Initialize memo with -1 to indicate uncomputed values
        return helper(n, memo);
    }

private:
    int helper(int n, vector<int>& memo) {
        if (n == 0) return 0;
        if (n == 1 || n == 2) return 1;

        if (memo[n] != -1) return memo[n];  // Return cached result

        // Recursively compute and memoize
        memo[n] = helper(n - 1, memo) + helper(n - 2, memo) + helper(n - 3, memo);
        return memo[n];
    }
};
// How it works:
// The helper function computes T(n) recursively.

// Results are memoized to avoid redundant calculations.

// Time complexity is O(n) and space complexity is O(n) due to the memo array and recursion stack.

// Approach: Iterative with Memo (Bottom-Up DP)
class Solution {
public:
    int tribonacci(int n) {
        if (n == 0) return 0;
        if (n == 1 || n == 2) return 1;

        vector<int> memo(n + 1);
        memo[0] = 0;
        memo[1] = memo[2] = 1;

        for (int i = 3; i <= n; ++i) {
            memo[i] = memo[i - 1] + memo[i - 2] + memo[i - 3];
        }

        return memo[n];
    }
};
// C++ Solution: Recursive + Memoization with unordered_map
#include <unordered_map>

class Solution {
public:
    int tribonacci(int n) {
        return helper(n);
    }

private:
    std::unordered_map<int, int> memo;

    int helper(int n) {
        if (n == 0) return 0;
        if (n == 1 || n == 2) return 1;

        if (memo.count(n)) return memo[n];

        memo[n] = helper(n - 1) + helper(n - 2) + helper(n - 3);
        return memo[n];
    }
};
// Why use unordered_map?
// Flexible: You don't need to preallocate space like with vector<int>.

// Useful for large or sparse domains: If n were large or non-contiguous (e.g. memoization with string keys or other complex states), a hash map is better.

// In this problem (0 <= n <= 37), it's not necessary — but good practice in template-style memoization.
