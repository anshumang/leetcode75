#Approach 1: Dynamic Programming (Tabulation)
#✅ Time Complexity:
#O(m × n) where m and n are the lengths of text1 and text2

#✅ Space Complexity:
#O(m × n) (can be optimized to O(min(m, n)) with 1D DP)

int longestCommonSubsequence(string text1, string text2) {
    int m = text1.length(), n = text2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for(int i = 1; i <= m; ++i){
        for(int j = 1; j <= n; ++j){
            if(text1[i - 1] == text2[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    return dp[m][n];
}
// Memoized Recursive (Top-Down) Approach
int dp[1001][1001];

int lcs(string& a, string& b, int i, int j){
    if(i == a.size() || j == b.size()) return 0;
    if(dp[i][j] != -1) return dp[i][j];

    if(a[i] == b[j])
        return dp[i][j] = 1 + lcs(a, b, i + 1, j + 1);
    else
        return dp[i][j] = max(lcs(a, b, i + 1, j), lcs(a, b, i, j + 1));
}

int longestCommonSubsequence(string text1, string text2) {
    memset(dp, -1, sizeof(dp));
    return lcs(text1, text2, 0, 0);
}
// Here's a space-optimized dynamic programming solution for the Longest Common Subsequence problem. Instead of using a full 2D table (O(m × n) space), we use two 1D arrays, reducing space complexity to
// O(min(m, n)).
int longestCommonSubsequence(string text1, string text2) {
    // Ensure text1 is the shorter string to use less space
    if (text1.length() > text2.length()) 
        swap(text1, text2);

    int m = text1.length(), n = text2.length();
    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    for (int j = 1; j <= n; ++j) {
        for (int i = 1; i <= m; ++i) {
            if (text2[j - 1] == text1[i - 1])
                curr[i] = 1 + prev[i - 1];
            else
                curr[i] = max(prev[i], curr[i - 1]);
        }
        prev = curr;
    }

    return prev[m];
}
//Explanation:
//We only store two rows at a time: prev (previous row) and curr (current row).

//After each row of processing, curr becomes prev for the next iteration.

//text1 is made the shorter string to minimize memory usage.

// can optimize even further by using just one array instead of two. This is possible because you process the DP table from right to left, which ensures you don’t overwrite values that you still need.
int longestCommonSubsequence(string text1, string text2) {
    if (text1.length() > text2.length()) 
        swap(text1, text2); // text1 is the shorter string

    int m = text1.length(), n = text2.length();
    vector<int> dp(m + 1, 0);

    for (int j = 1; j <= n; ++j) {
        int prev = 0;  // This holds dp[i - 1] from the previous iteration
        for (int i = 1; i <= m; ++i) {
            int temp = dp[i]; // Save current dp[i] before overwriting
            if (text2[j - 1] == text1[i - 1])
                dp[i] = 1 + prev;
            else
                dp[i] = max(dp[i], dp[i - 1]);
            prev = temp;
        }
    }

    return dp[m];
}
//How It Works:
//dp[i] represents the current row (or column) values.

//prev keeps the old value of dp[i - 1] from the previous row.

//temp saves the current dp[i] before it's updated, so it can be used as prev in the next iteration.
//Time & Space:
//Time Complexity: O(m × n)

//Space Complexity: O(min(m, n)) — using just one vector!
