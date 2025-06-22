Given an array of integers nums, calculate the pivot index of this array.

The pivot index is the index where the sum of all the numbers strictly to the left of the index is equal to the sum of all the numbers strictly to the index's right.

If the index is on the left edge of the array, then the left sum is 0 because there are no elements to the left. This also applies to the right edge of the array.

Return the leftmost pivot index. If no such index exists, return -1.

 

Example 1:

Input: nums = [1,7,3,6,5,6]
Output: 3
Explanation:
The pivot index is 3.
Left sum = nums[0] + nums[1] + nums[2] = 1 + 7 + 3 = 11
Right sum = nums[4] + nums[5] = 5 + 6 = 11
Example 2:

Input: nums = [1,2,3]
Output: -1
Explanation:
There is no index that satisfies the conditions in the problem statement.
Example 3:

Input: nums = [2,1,-1]
Output: 0
Explanation:
The pivot index is 0.
Left sum = 0 (no elements to the left of index 0)
Right sum = nums[1] + nums[2] = 1 + -1 = 0
 

Constraints:

1 <= nums.length <= 104
-1000 <= nums[i] <= 1000
 

Note: This question is the same as 1991: https://leetcode.com/problems/find-the-middle-index-in-array/

An efficient way to solve this problem is to iterate through the array while keeping track of the sum of elements to the left and right of the current index. A clever optimization involves pre-calculating the total sum of all numbers in the array.

Approach: Prefix Sum
Calculate Total Sum: First, iterate through the entire array to find the total sum of all its elements.
Iterate and Check: Iterate through the array a second time, from left to right, keeping track of the sum of elements to the left of the current index (let's call it leftSum).
Find the Pivot: At each index i, the sum of the elements to the right can be calculated without another loop. The rightSum is simply totalSum - leftSum - nums[i].
Check for Equality: If leftSum is equal to rightSum at any index i, then i is a pivot index. Since we are looking for the leftmost pivot index, the first one we find is our answer.
Update leftSum: After checking the condition, update leftSum by adding the current element nums[i] to it for the next iteration.
No Pivot Found: If the loop completes and no pivot index is found, it means one doesn't exist, and we should return -1.
Example Walkthrough
Let's trace this approach with nums = [1, 7, 3, 6, 5, 6].

Total Sum: 1 + 7 + 3 + 6 + 5 + 6 = 28.
Initialize: leftSum = 0.
Iterate and Check:
Index i	nums[i]	leftSum before check	rightSum = totalSum - leftSum - nums[i]	leftSum == rightSum?	leftSum after check
0	1	0	28 - 0 - 1 = 27	No	1
1	7	1	28 - 1 - 7 = 20	No	8
2	3	8	28 - 8 - 3 = 17	No	11
3	6	11	28 - 11 - 6 = 11	Yes	17
4	5	17	28 - 17 - 5 = 6	No	22
5	6	22	28 - 22 - 6 = 0	No	28

The first index where leftSum == rightSum is 3. We can immediately return 3 as the answer.

C++ Code
Here is a C++ implementation of this efficient approach.

#include <iostream>
#include <vector>
#include <numeric> // Required for std::accumulate

class Solution {
public:
    /**
     * @brief Finds the leftmost pivot index in an array of integers.
     *
     * The pivot index is where the sum of numbers to the left equals the sum
     * of numbers to the right.
     *
     * @param nums A vector of integers.
     * @return The leftmost pivot index, or -1 if none exists.
     */
    int pivotIndex(const std::vector<int>& nums) {
        // Calculate the total sum of the array.
        int totalSum = 0;
        for (int num : nums) {
            totalSum += num;
        }
        // An alternative way to get the sum using the <numeric> header:
        // int totalSum = std::accumulate(nums.begin(), nums.end(), 0);

        int leftSum = 0;

        // Iterate through the array to find the pivot index.
        for (int i = 0; i < nums.size(); ++i) {
            // Calculate the sum of elements to the right of the current index.
            // rightSum = totalSum - leftSum - nums[i]
            if (leftSum == totalSum - leftSum - nums[i]) {
                return i; // Found the pivot index.
            }
            // Update the leftSum for the next iteration.
            leftSum += nums[i];
        }

        // If the loop completes, no pivot index was found.
        return -1;
    }
};

// Main function to demonstrate the solution.
int main() {
    Solution sol;

    // Example 1
    std::vector<int> nums1 = {1, 7, 3, 6, 5, 6};
    std::cout << "Input: [1, 7, 3, 6, 5, 6]" << std::endl;
    std::cout << "Output: " << sol.pivotIndex(nums1) << std::endl; // Expected: 3
    std::cout << "-----------------------------------" << std::endl;

    // Example 2
    std::vector<int> nums2 = {1, 2, 3};
    std::cout << "Input: [1, 2, 3]" << std::endl;
    std::cout << "Output: " << sol.pivotIndex(nums2) << std::endl; // Expected: -1
    std::cout << "-----------------------------------" << std::endl;

    // Example 3
    std::vector<int> nums3 = {2, 1, -1};
    std::cout << "Input: [2, 1, -1]" << std::endl;
    std::cout << "Output: " << sol.pivotIndex(nums3) << std::endl; // Expected: 0
    std::cout << "-----------------------------------" << std::endl;

    return 0;
}
