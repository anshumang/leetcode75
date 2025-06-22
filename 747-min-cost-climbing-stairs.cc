You are given an integer array cost where cost[i] is the cost of ith step on a staircase. Once you pay the cost, you can either climb one or two steps.

You can either start from the step with index 0, or the step with index 1.

Return the minimum cost to reach the top of the floor.

 

Example 1:

Input: cost = [10,15,20]
Output: 15
Explanation: You will start at index 1.
- Pay 15 and climb two steps to reach the top.
The total cost is 15.
Example 2:

Input: cost = [1,100,1,1,1,100,1,1,100,1]
Output: 6
Explanation: You will start at index 0.
- Pay 1 and climb two steps to reach index 2.
- Pay 1 and climb two steps to reach index 4.
- Pay 1 and climb two steps to reach index 6.
- Pay 1 and climb one step to reach index 7.
- Pay 1 and climb two steps to reach index 9.
- Pay 1 and climb one step to reach the top.
The total cost is 6.
 

Constraints:

2 <= cost.length <= 1000
0 <= cost[i] <= 999


This solution efficiently calculates the minimum cost in a single pass using only two variables to store the state of the previous two steps, resulting in O(1) space complexity.

#include <iostream>
#include <vector>
#include <algorithm> // For std::min

class Solution {
public:
    /**
     * @brief Calculates the minimum cost to reach the top of the floor.
     * @param cost A vector of integers where cost[i] is the cost of the ith step.
     * @return The minimum cost to climb to the top.
     */
    int minCostClimbingStairs(std::vector<int>& cost) {
        int n = cost.size();
        
        // If there are only two steps, the minimum cost is simply the cheaper of the two.
        if (n == 2) {
            return std::min(cost[0], cost[1]);
        }

        // 'first' holds the min cost to reach step i-2
        // 'second' holds the min cost to reach step i-1
        int first = cost[0];
        int second = cost[1];

        // Iterate from the 3rd step (index 2) to the end.
        for (int i = 2; i < n; ++i) {
            // The min cost to reach the current step 'i' is its own cost plus the
            // minimum of the costs to reach the previous two steps.
            int current_cost = cost[i] + std::min(first, second);
            
            // Update the variables for the next iteration.
            // The previous 'second' becomes the new 'first'.
            first = second;
            // The 'current_cost' becomes the new 'second'.
            second = current_cost;
        }

        // To reach the top (one step beyond the last element), we could have
        // come from the last step or the second-to-last step. The costs to
        // reach these steps are now stored in 'first' and 'second'.
        return std::min(first, second);
    }
};

// Helper function to print results
void runTest(Solution& sol, std::vector<int>& cost, int expected) {
    int result = sol.minCostClimbingStairs(cost);
    std::cout << "Input: [";
    for(size_t i = 0; i < cost.size(); ++i) {
        std::cout << cost[i] << (i == cost.size() - 1 ? "" : ",");
    }
    std::cout << "]" << std::endl;
    std::cout << "Output: " << result << " (Expected: " << expected << ")" << std::endl;
    std::cout << "-----------------------------------" << std::endl;
}

// Example Usage
int main() {
    Solution sol;

    // Example 1
    std::vector<int> cost1 = {10, 15, 20};
    runTest(sol, cost1, 15);

    // Example 2
    std::vector<int> cost2 = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
    runTest(sol, cost2, 6);

    return 0;
}

minCostClimbingStairs Function:

It takes the cost vector by reference (&) to avoid making an unnecessary copy.
It initializes two variables, first and second, to hold the minimum costs to reach the first two steps (index 0 and 1). These are our base cases.
The for loop starts at i = 2 because the costs for the first two steps are already our initial values.
Inside the loop, current_cost is calculated. This is the minimum cost to land on the current step i. This cost is cost[i] plus the cheaper of the two paths to get there (from
step i-1 or i-2).
The state is then updated for the next iteration: first = second and second = current_cost. This effectively slides our window of the two previous costs one step to the right.
Finally, the function returns std::min(first, second). After the loop finishes, first holds the total minimum cost to reach the second-to-last step (n-2), and second holds the
total minimum cost to reach the last step (n-1). Since we can take one or two steps to get to the "top," we choose the cheaper of these two final paths.
