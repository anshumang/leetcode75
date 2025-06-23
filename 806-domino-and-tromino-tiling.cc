You have two types of tiles: a 2 x 1 domino shape and a tromino shape. You may rotate these shapes.
Given an integer n, return the number of ways to tile an 2 x n board. Since the answer may be very large, return it modulo 109 + 7.

In a tiling, every square must be covered by a tile. Two tilings are different if and only if there are two 4-directionally adjacent cells on the board such that exactly one of the
tilings has both squares occupied by a tile.

Example 1:
Input: n = 3
Output: 5

Example 2:
Input: n = 1
Output: 1

Constraints:
1 <= n <= 1000

The key to solving this problem with dynamic programming is to identify the states of the board as we build it from left to right. A simple dp[i] representing the number of ways
to tile a 2xi board isn't enough, because a tromino can leave the board in an incomplete state.

Let's consider the state of the rightmost column(s). When we tile a 2xi board, it can end in one of three states:

Fully Tiled: The 2xi rectangle is perfectly covered.
Partially Tiled (Top protruding): The 2x(i-1) rectangle is tiled, and the top cell of column i is also covered, leaving the bottom cell of column i empty.
Partially Tiled (Bottom protruding): The 2x(i-1) rectangle is tiled, and the bottom cell of column i is also covered, leaving the top cell of column i empty.

Let's define our DP functions based on this:

f(i): The number of ways to fully tile a 2xi board.
p(i): The number of ways to tile a 2xi board with one cell protruding (partially tiled). By symmetry, the number of ways for the top to protrude is the same as for the bottom, so we can combine them.
Deriving the Recurrence Relations
Now, let's figure out how to calculate f(n) and p(n) based on previous values.

1. Ways to form a f(n) (fully tiled 2xn board):
You can get a fully tiled 2xn board in four ways:

From a fully tiled f(n-1): Add one vertical domino.
From a fully tiled f(n-2): Add two horizontal dominoes.
From a partially tiled p(n-1) with top protruding: Add a tromino to fill the gap.
From a partially tiled p(n-1) with bottom protruding: Add a tromino to fill the gap.
This gives us our first recurrence relation:
f(n)=f(n−1)+f(n−2)+2⋅p(n−1)

2. Ways to form a p(n) (partially tiled 2xn board):
You can get a partially tiled 2xn board in two ways:

From a fully tiled f(n-1): Add a tromino.
From a partially tiled p(n-1): Add a horizontal domino.
This gives us our second recurrence relation:
p(n)=f(n−1)+p(n−1)

f(n)=2⋅f(n−1)+f(n−3)

This is our final, simplified recurrence relation! We only need to keep track of the number of ways to fully tile the board.

The Algorithm
Define the modulo 10^9 + 7.
Create a DP array, let's call it dp, of size n+1. dp[i] will store the value of f(i).
Set the base cases:
dp[0] = 1 (The number of ways to tile a 2x0 board is 1: do nothing). This is a useful base for the recurrence.
dp[1] = 1 (One vertical domino).
dp[2] = 2 (Two vertical dominoes or two horizontal dominoes).
Iterate from i = 3 to n.
In each iteration, calculate dp[i] = (2 * dp[i-1] + dp[i-3]) % MOD.
Return dp[n].
C++ Solution

#include <vector>

class Solution {
public:
    int numTilings(int n) {
        // The modulo value
        int MOD = 1e9 + 7;

        // Base cases for small n where the recurrence doesn't apply cleanly
        if (n <= 2) {
            return n;
        }

        // dp[i] will store the number of ways to fully tile a 2xi board.
        // We use a vector of long long to prevent overflow during intermediate calculations.
        std::vector<long long> dp(n + 1);

        // Base cases for the recurrence relation
        dp[0] = 1; // A 2x0 board can be tiled in one way (by doing nothing)
        dp[1] = 1; // One vertical domino
        dp[2] = 2; // Two vertical or two horizontal dominoes

        // Apply the recurrence f(n) = 2*f(n-1) + f(n-3)
        for (int i = 3; i <= n; ++i) {
            dp[i] = (2 * dp[i - 1] + dp[i - 3]) % MOD;
        }

        return dp[n];
    }
};
