Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.

You have the following three operations permitted on a word:

Insert a character
Delete a character
Replace a character
 

Example 1:

Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation: 
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')
Example 2:

Input: word1 = "intention", word2 = "execution"
Output: 5
Explanation: 
intention -> inention (remove 't')
inention -> enention (replace 'i' with 'e')
enention -> exention (replace 'n' with 'x')
exention -> exection (replace 'n' with 'c')
exection -> execution (insert 'u')
 

Constraints:

0 <= word1.length, word2.length <= 500
word1 and word2 consist of lowercase English letters.

This is a classic algorithmic problem known as the Edit Distance problem. The most common and efficient way to solve it is by using dynamic programming. 
  The algorithm is often referred to as the Wagner-Fischer algorithm, and the distance it computes is called the Levenshtein distance.

Core Concept: Dynamic Programming
The key idea is to build a table (a 2D array) that stores the solutions to subproblems. 
Let dp[i][j] be the minimum number of operations (insert, delete, or replace) required to convert the first i characters of word1 into the first j characters of word2.

Our goal is to find dp[m][n], where m is the length of word1 and n is the length of word2.

Dynamic Programming Formulation
Let word1 have length m and word2 have length n. We'll construct a (m+1) x (n+1) DP table.

Base Cases
The first row and column of the table are for handling the case where one of the strings is empty.

dp[i][0]: The minimum operations to convert the first i characters of word1 to an empty string. This requires i deletions. So, dp[i][0] = i.
dp[0][j]: The minimum operations to convert an empty string to the first j characters of word2. This requires j insertions. So, dp[0][j] = j.
Recurrence Relation
Now, for any dp[i][j], we consider the characters word1[i-1] and word2[j-1] (we use i-1 and j-1 because of 0-based indexing of strings vs. 1-based indexing of our DP table).

If the characters are the same (word1[i-1] == word2[j-1]):
No operation is needed for these characters. The cost is the same as the cost for the strings without these characters.
dp[i][j]=dp[i−1][j−1]

If the characters are different (word1[i-1] != word2[j-1]):
We must perform one operation. We choose the operation that results in the minimum cost from the three possibilities:

Insert: Insert word2[j-1] into word1. The cost is 1 (for the insertion) plus the cost of converting the first i characters of word1 to the first j-1 characters of word2. 
Cost = 1 + dp[i][j-1]
Delete: Delete word1[i-1] from word1. The cost is 1 (for the deletion) plus the cost of converting the first i-1 characters of word1 to the first j characters of word2. 
Cost = 1 + dp[i-1][j]
Replace: Replace word1[i-1] with word2[j-1]. The cost is 1 (for the replacement) plus the cost of converting the first i-1 characters of word1 to the first j-1 characters of word2. 
Cost = 1 + dp[i-1][j-1]

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    /**
     * @brief Calculates the minimum number of operations to convert word1 to word2.
     * @param word1 The source string.
     * @param word2 The target string.
     * @return The minimum number of operations (edit distance).
     */
    int minDistance(std::string word1, std::string word2) {
        int m = word1.length();
        int n = word2.length();

        // Create a DP table to store results of subproblems.
        // dp[i][j] will be the edit distance between the first i chars of word1
        // and the first j chars of word2.
        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));

        // Base Cases: Initialize the DP table.
        // If word2 is empty, we must delete all characters of word1.
        for (int i = 0; i <= m; ++i) {
            dp[i][0] = i;
        }

        // If word1 is empty, we must insert all characters of word2.
        for (int j = 0; j <= n; ++j) {
            dp[0][j] = j;
        }

        // Fill the rest of the DP table.
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                // If the characters are the same, no operation is needed.
                // The cost is the same as the subproblem without these characters.
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    // If characters are different, we take the minimum of the three operations.
                    int insert_cost = dp[i][j - 1];
                    int delete_cost = dp[i - 1][j];
                    int replace_cost = dp[i - 1][j - 1];
                    
                    dp[i][j] = 1 + std::min({insert_cost, delete_cost, replace_cost});
                }
            }
        }

        // The final answer is in the bottom-right cell.
        return dp[m][n];
    }
};

// Main function for demonstration
int main() {
    Solution sol;

    // Example 1
    std::string word1_1 = "horse";
    std::string word2_1 = "ros";
    std::cout << "Input: word1 = \"" << word1_1 << "\", word2 = \"" << word2_1 << "\"" << std::endl;
    std::cout << "Output: " << sol.minDistance(word1_1, word2_1) << std::endl; // Expected: 3
    std::cout << "-----------------------------------" << std::endl;

    // Example 2
    std::string word1_2 = "intention";
    std::string word2_2 = "execution";
    std::cout << "Input: word1 = \"" << word1_2 << "\", word2 = \"" << word2_2 << "\"" << std::endl;
    std::cout << "Output: " << sol.minDistance(word1_2, word2_2) << std::endl; // Expected: 5
    std::cout << "-----------------------------------" << std::endl;

    return 0;
}
