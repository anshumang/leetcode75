Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. The guards have gone and will come back in h hours.

Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile of bananas and eats k bananas from that pile. If the pile has less than k bananas, she
  eats all of them instead and will not eat any more bananas during this hour.

Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.

Return the minimum integer k such that she can eat all the bananas within h hours.

 

Example 1:

Input: piles = [3,6,7,11], h = 8
Output: 4
Example 2:

Input: piles = [30,11,23,4,20], h = 5
Output: 30
Example 3:

Input: piles = [30,11,23,4,20], h = 6
Output: 23
 

Constraints:

1 <= piles.length <= 104
piles.length <= h <= 109
1 <= piles[i] <= 109

This is a classic optimization problem that can be solved efficiently using binary search. Here's a detailed breakdown of the logic and the solution.

Problem Analysis
The core of the problem is to find the minimum value k (bananas-per-hour) that satisfies a condition (finishing all bananas within h hours).

Let's analyze the relationship between the eating speed k and the time it takes to finish.

If Koko eats at a speed k, and it's enough to finish in time, then any speed greater than k (k+1, k+2, etc.) will also be sufficient.
If Koko eats at a speed k, and it's not enough to finish in time, then any speed less than k (k-1, k-2, etc.) will also be insufficient.
This creates a monotonic property. If we were to check every possible k, the results would look like [False, False, ..., False, True, True, ..., True]. We are looking for the
first True in this sequence. This is a perfect scenario for Binary Search.

The Strategy: Binary Search on the Answer
We can binary search for the answer k within a defined range.

Define the Search Space:

Lower Bound (low): The absolute minimum speed Koko can have is 1 banana per hour. So, low = 1.
Upper Bound (high): The maximum necessary speed would be eating the largest pile in a single hour. Any speed higher than that is redundant because she can only eat from one pile
per hour. So, high = max(piles).
The check function: We need a helper function that, given a potential speed k, determines if it's possible to eat all bananas within h hours. Let's call it canFinish(k).

For a given k, the time to finish a pile of p bananas is ceil(p / k).
In integer arithmetic, ceil(a / b) can be calculated as (a + b - 1) / b.
The canFinish(k) function will calculate the total hours needed for speed k by summing the hours for each pile. If the total_hours <= h, it returns true.
The Binary Search Algorithm:

Set low = 1 and high = max(piles).
While low <= high:
Calculate mid = low + (high - low) / 2. This is our trial speed k.
Check if canFinish(mid) is true.
If true, it means mid is a possible answer. But we want the minimum possible k, so we try to find a smaller valid speed. We store mid as a potential answer and shrink our search
space to the lower half: high = mid - 1.
If false, it means our speed mid is too slow. We must eat faster. We shrink our search space to the upper half: low = mid + 1.
The loop will continue until low and high cross. The last valid speed we stored will be the minimum possible speed.

C++ Solution
#include <vector>
#include <numeric>   // For std::accumulate
#include <algorithm> // For std::max_element
#include <cmath>     // For std::ceil

class Solution {
public:
    /**
     * @brief Checks if Koko can finish all bananas within h hours at speed k.
     * @param piles The vector of banana piles.
     * @param h The total hours available.
     * @param k The eating speed to test.
     * @return True if she can finish, false otherwise.
     */
    bool canFinish(const std::vector<int>& piles, int h, int k) {
        // Use long long for hours to prevent overflow, as h and piles[i] can be large.
        long long hours_needed = 0;
        for (int p : piles) {
            // hours for one pile is ceil(p / k)
            // In integer math, this is (p + k - 1) / k
            hours_needed += (p + k - 1) / k;
        }
        return hours_needed <= h;
    }

    int minEatingSpeed(std::vector<int>& piles, int h) {
        // The search space for k is [1, max(piles)]
        // low = 1 is the minimum possible speed.
        // high = max(piles) is the maximum necessary speed.
        int low = 1;
        int high = *std::max_element(piles.begin(), piles.end());
        
        int result = high; // Initialize result with a known valid speed.

        while (low <= high) {
            // Prevent overflow by using this form of mid calculation.
            // Using long long for mid in case high is very large (e.g., 10^9).
            long long mid_long = low + (long long)(high - low) / 2;
            int mid = (int)mid_long;

            if (mid == 0) { // Safety check, though low starts at 1.
                 low = 1;
                 continue;
            }

            if (canFinish(piles, h, mid)) {
                // This speed is valid. It's a potential answer.
                // Try to find a smaller valid speed.
                result = mid;
                high = mid - 1;
            } else {
                // This speed is too slow. Koko must eat faster.
                low = mid + 1;
            }
        }
        
        return result;
    }
};
