class Solution {
public:
    // Approach 1: Two Pointers (Optimal) - O(n) time, O(1) space
    int maxArea(vector<int>& height) {
        int left = 0, right = height.size() - 1;
        int maxWater = 0;
        
        while (left < right) {
            // Calculate current area
            int width = right - left;
            int currentHeight = min(height[left], height[right]);
            int currentArea = width * currentHeight;
            
            // Update maximum area
            maxWater = max(maxWater, currentArea);
            
            // Move the pointer with smaller height
            // Moving the taller one can only decrease area
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        
        return maxWater;
    }
};
// Proof of correctness explanation:
/*
Why does the two-pointer approach work?

Key insight: When we have pointers at positions i and j (i < j), 
the area is limited by min(height[i], height[j]) * (j - i).

If height[i] < height[j], moving j leftward can only:
1. Decrease width (j - i becomes smaller)
2. Container height is still limited by height[i] or smaller

So moving the shorter line gives us the only chance to find a larger area.
This greedy choice is optimal because we never miss a better solution.

Time: O(n) - each element visited once
Space: O(1) - only using pointers and variables
*/
