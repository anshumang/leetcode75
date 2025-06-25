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
    
    // Approach 2: Brute Force (for comparison) - O(n²) time, O(1) space
    int maxAreaBruteForce(vector<int>& height) {
        int n = height.size();
        int maxWater = 0;
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int width = j - i;
                int currentHeight = min(height[i], height[j]);
                int area = width * currentHeight;
                maxWater = max(maxWater, area);
            }
        }
        
        return maxWater;
    }
    
    // Approach 3: Two Pointers with detailed tracking
    int maxAreaDetailed(vector<int>& height) {
        int left = 0, right = height.size() - 1;
        int maxWater = 0;
        
        while (left < right) {
            int width = right - left;
            int leftHeight = height[left];
            int rightHeight = height[right];
            int containerHeight = min(leftHeight, rightHeight);
            int currentArea = width * containerHeight;
            
            // Update maximum
            if (currentArea > maxWater) {
                maxWater = currentArea;
            }
            
            // Move pointer with smaller height
            // If heights are equal, we can move either (moving left here)
            if (leftHeight <= rightHeight) {
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

using the two-pointer technique.
Problem Analysis:

Given array of heights representing vertical lines
Find two lines that form container with maximum water area
Area = min(height[i], height[j]) * (j - i)
Cannot tilt the container (water level limited by shorter line)

Approach:
Use two pointers starting from both ends and move the pointer with smaller height inward. This greedy approach works because moving the taller line inward can only decrease the area.

Key Insights:

Two-Pointer Strategy: Start from both ends, move inward
Greedy Choice: Always move the pointer with smaller height
Why it works: Moving the taller line can only decrease area since width decreases and height is still limited by the shorter line

Algorithm Logic:

Area = min(height[left], height[right]) × (right - left)
If height[left] < height[right], move left pointer right
If height[right] ≤ height[left], move right pointer left
Track maximum area found

Time Complexity: O(n) - single pass through array
Space Complexity: O(1) - only using a few variables
Example Walkthrough:
height = [1,8,6,2,5,4,8,3,7]
Indices:  0 1 2 3 4 5 6 7 8

Step 1: left=0(1), right=8(7) → area = min(1,7) × 8 = 8
        Move left (height[0]=1 < height[8]=7)
        
Step 2: left=1(8), right=8(7) → area = min(8,7) × 7 = 49
        Move right (height[8]=7 < height[1]=8)
        
Continue until left meets right...
Maximum area = 49
Why the greedy approach works:

When height[left] < height[right], any container using left with a line between left and right will have area ≤ current area
Moving left gives us the only chance to find a larger area
This ensures we never miss the optimal solution

The two-pointer approach is significantly more efficient than the O(n²) brute force solution and is the standard way to solve this problem.
