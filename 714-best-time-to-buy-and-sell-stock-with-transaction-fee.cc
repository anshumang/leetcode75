You are given an array prices where prices[i] is the price of a given stock on the ith day, and an integer fee representing a transaction fee.

Find the maximum profit you can achieve. You may complete as many transactions as you like, but you need to pay the transaction fee for each transaction.

Note:

You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).
The transaction fee is only charged once for each stock purchase and sale.
 

Example 1:

Input: prices = [1,3,2,8,4,9], fee = 2
Output: 8
Explanation: The maximum profit can be achieved by:
- Buying at prices[0] = 1
- Selling at prices[3] = 8
- Buying at prices[4] = 4
- Selling at prices[5] = 9
The total profit is ((8 - 1) - 2) + ((9 - 4) - 2) = 8.
Example 2:

Input: prices = [1,3,7,5,10,3], fee = 3
Output: 6
 

Constraints:

1 <= prices.length <= 5 * 104
1 <= prices[i] < 5 * 104
0 <= fee < 5 * 104

An elegant and efficient solution to this problem involves dynamic programming. We can determine the maximum profit by iterating through the stock prices just once, keeping track of the maximum profit we could have in two states: holding a stock, and not holding a stock.

Approach: Dynamic Programming
Let's define two variables to represent the maximum profit achievable at the end of each day i:

hold[i]: The maximum profit on day i if we are currently holding a share of the stock.
free[i]: The maximum profit on day i if we are currently not holding any shares (we are "free" to buy).
Our goal is to find the maximum value of free on the last day, as we must sell any stock to realize the profit.

Recurrence Relations
We can define how to calculate these values for day i based on the values from day i-1:

hold[i]: To be holding a stock on day i, we could have either:

Been holding the stock on day i-1 and decided to continue holding it. The profit remains hold[i-1].
Been "free" on day i-1 and decided to buy the stock on day i. The profit would be free[i-1] - prices[i].
Therefore, the maximum profit while holding on day i is the maximum of these two possibilities:
hold[i]=max(hold[i−1],free[i−1]−prices[i])

free[i]: To be "free" (not holding a stock) on day i, we could have either:

Been "free" on day i-1 and decided to do nothing. The profit remains free[i-1].
Been holding the stock on day i-1 and decided to sell it on day i. The profit would be hold[i-1] + prices[i] - fee. The transaction fee is applied at the time of sale.
Therefore, the maximum profit while "free" on day i is the maximum of these two possibilities:
free[i]=max(free[i−1],hold[i−1]+prices[i]−fee)

Optimization
Notice that the calculation for day i only depends on the values from day i-1. This means we don't need to store the entire hold and free arrays. We can optimize our space complexity to O(1) by using two variables to keep track of the latest hold and free profits.

The Algorithm
Initialize two variables:

hold: Represents the maximum profit if we end the day holding a stock. Initialize it to -prices[0] (the cost of buying the stock on the first day).
free: Represents the maximum profit if we end the day without a stock. Initialize it to 0.
Iterate through the prices array starting from the second day (index 1). For each day i:
a.  Store the previous day's hold value in a temporary variable, let's call it prev_hold.
b.  Update hold: hold = max(hold, free - prices[i]).
c.  Update free: free = max(free, prev_hold + prices[i] - fee).

After iterating through all the prices, the final answer is the value in free, as we must sell any stock to lock in the profit.

Example Walkthrough
Let's trace the algorithm with the first example: prices = [1, 3, 2, 8, 4, 9], fee = 2.

Day (i)	prices[i]	prev_hold	hold = max(hold, free - prices[i])	free = max(free, prev_hold + prices[i] - fee)
Initial			hold = -1	free = 0
1	3	-1	max(-1, 0 - 3) = -1	max(0, -1 + 3 - 2) = 0
2	2	-1	max(-1, 0 - 2) = -1	max(0, -1 + 2 - 2) = -1
3	8	-1	max(-1, -1 - 8) = -1	max(-1, -1 + 8 - 2) = 5
4	4	-1	max(-1, 5 - 4) = 1	max(5, -1 + 4 - 2) = 5
5	9	1	max(1, 5 - 9) = 1	max(5, 1 + 9 - 2) = 8

An elegant and efficient solution to this problem involves dynamic programming. We can determine the maximum profit by iterating through the stock prices just once, keeping track of the maximum profit we could have in two states: holding a stock, and not holding a stock.

Approach: Dynamic Programming
Let's define two variables to represent the maximum profit achievable at the end of each day i:

hold[i]: The maximum profit on day i if we are currently holding a share of the stock.
free[i]: The maximum profit on day i if we are currently not holding any shares (we are "free" to buy).
Our goal is to find the maximum value of free on the last day, as we must sell any stock to realize the profit.

Recurrence Relations
We can define how to calculate these values for day i based on the values from day i-1:

hold[i]: To be holding a stock on day i, we could have either:

Been holding the stock on day i-1 and decided to continue holding it. The profit remains hold[i-1].
Been "free" on day i-1 and decided to buy the stock on day i. The profit would be free[i-1] - prices[i].
Therefore, the maximum profit while holding on day i is the maximum of these two possibilities:
hold[i]=max(hold[i−1],free[i−1]−prices[i])

free[i]: To be "free" (not holding a stock) on day i, we could have either:

Been "free" on day i-1 and decided to do nothing. The profit remains free[i-1].
Been holding the stock on day i-1 and decided to sell it on day i. The profit would be hold[i-1] + prices[i] - fee. The transaction fee is applied at the time of sale.
Therefore, the maximum profit while "free" on day i is the maximum of these two possibilities:
free[i]=max(free[i−1],hold[i−1]+prices[i]−fee)

Optimization
Notice that the calculation for day i only depends on the values from day i-1. This means we don't need to store the entire hold and free arrays. We can optimize our space complexity to O(1) by using two variables to keep track of the latest hold and free profits.

The Algorithm
Initialize two variables:

hold: Represents the maximum profit if we end the day holding a stock. Initialize it to -prices[0] (the cost of buying the stock on the first day).
free: Represents the maximum profit if we end the day without a stock. Initialize it to 0.
Iterate through the prices array starting from the second day (index 1). For each day i:
a.  Store the previous day's hold value in a temporary variable, let's call it prev_hold.
b.  Update hold: hold = max(hold, free - prices[i]).
c.  Update free: free = max(free, prev_hold + prices[i] - fee).

After iterating through all the prices, the final answer is the value in free, as we must sell any stock to lock in the profit.

Example Walkthrough
Let's trace the algorithm with the first example: prices = [1, 3, 2, 8, 4, 9], fee = 2.

Day (i)	prices[i]	prev_hold	hold = max(hold, free - prices[i])	free = max(free, prev_hold + prices[i] - fee)
Initial			hold = -1	free = 0
1	3	-1	max(-1, 0 - 3) = -1	max(0, -1 + 3 - 2) = 0
2	2	-1	max(-1, 0 - 2) = -1	max(0, -1 + 2 - 2) = -1
3	8	-1	max(-1, -1 - 8) = -1	max(-1, -1 + 8 - 2) = 5
4	4	-1	max(-1, 5 - 4) = 1	max(5, -1 + 4 - 2) = 5
5	9	1	max(1, 5 - 9) = 1	max(5, 1 + 9 - 2) = 8

After the loop, the final free value is 8, which is the maximum profit.

#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    /**
     * @brief Calculates the maximum profit from stock transactions with a fee.
     * * @param prices A vector of integers where prices[i] is the price of the stock on day i.
     * @param fee The transaction fee for each buy-sell transaction.
     * @return The maximum profit that can be achieved.
     */
    int maxProfit(const std::vector<int>& prices, int fee) {
        // If there are no prices, no profit can be made.
        if (prices.empty()) {
            return 0;
        }

        // 'hold' represents the maximum profit if we end the day holding a stock.
        // Initialize by buying on day 0.
        int hold = -prices[0];

        // 'free' represents the maximum profit if we end the day not holding a stock.
        // Initialize to 0 profit.
        int free = 0;

        // Iterate through the prices starting from the second day.
        for (size_t i = 1; i < prices.size(); ++i) {
            // Store the previous 'hold' state before it's updated.
            int prev_hold = hold;

            // The new 'hold' state is the maximum of:
            // 1. Continuing to hold the stock from the previous day (prev_hold).
            // 2. Buying the stock today (previous 'free' state minus today's price).
            hold = std::max(hold, free - prices[i]);

            // The new 'free' state is the maximum of:
            // 1. Staying free from the previous day (previous 'free' state).
            // 2. Selling the stock held from the previous day (prev_hold + today's price - fee).
            free = std::max(free, prev_hold + prices[i] - fee);
        }

        // The final answer is the 'free' state, as we must sell all stock to realize the profit.
        return free;
    }
};

// Main function to test the solution with the examples.
int main() {
    Solution sol;

    // Example 1
    std::vector<int> prices1 = {1, 3, 2, 8, 4, 9};
    int fee1 = 2;
    int result1 = sol.maxProfit(prices1, fee1);
    std::cout << "Example 1 Input: prices = [1,3,2,8,4,9], fee = 2" << std::endl;
    std::cout << "Output: " << result1 << std::endl; // Expected output: 8
    std::cout << "-----------------------------------" << std::endl;

    // Example 2
    std::vector<int> prices2 = {1, 3, 7, 5, 10, 3};
    int fee2 = 3;
    int result2 = sol.maxProfit(prices2, fee2);
    std::cout << "Example 2 Input: prices = [1,3,7,5,10,3], fee = 3" << std::endl;
    std::cout << "Output: " << result2 << std::endl; // Expected output: 6
    std::cout << "-----------------------------------" << std::endl;

    return 0;
}

Explanation of the Code
Headers: The code includes <iostream> for console output, <vector> for using the std::vector container, and <algorithm> for the std::max function.
Solution Class: The logic is encapsulated within a Solution class, which is a common practice in competitive programming.
maxProfit Function:
It takes a constant reference to a vector of integers (const std::vector<int>& prices) to avoid making an unnecessary copy, and an integer fee.
It handles the edge case of an empty prices vector by returning 0.
hold and free variables are initialized as per the algorithm's logic.
A for loop iterates from the second day (i = 1) to the end of the prices.
Inside the loop, prev_hold temporarily saves the value of hold from the previous day. This is crucial because the updated hold value is needed for the same day's free calculation.
std::max is used to apply the recurrence relations we defined.
Finally, the function returns the value of free, which represents the maximum profit after the last day.
main Function: This function demonstrates how to use the maxProfit method. It creates an instance of the Solution class and tests it with the two examples provided in the problem description, printing the results to the console.
