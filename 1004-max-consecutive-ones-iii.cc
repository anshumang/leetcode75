class Solution {
public:
    // Approach 1: Sliding Window (Two Pointers) - Most Optimal
    int longestOnes(vector<int>& nums, int k) {
        int left = 0, zeros = 0, maxLen = 0;
        
        for (int right = 0; right < nums.size(); right++) {
            // Expand window by including nums[right]
            if (nums[right] == 0) {
                zeros++;
            }
            
            // Shrink window if we have too many zeros
            while (zeros > k) {
                if (nums[left] == 0) {
                    zeros--;
                }
                left++;
            }
            
            // Update maximum length
            maxLen = max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
    
    // Approach 2: Optimized Sliding Window (No shrinking, just shifting)
    int longestOnesOptimized(vector<int>& nums, int k) {
        int left = 0, zeros = 0;
        
        for (int right = 0; right < nums.size(); right++) {
            if (nums[right] == 0) {
                zeros++;
            }
            
            // Instead of shrinking, just shift the window
            if (zeros > k) {
                if (nums[left] == 0) {
                    zeros--;
                }
                left++;
            }
        }
        
        // Window size is maintained at maximum valid size
        return nums.size() - left;
    }
    
    // Approach 3: Explicit sliding window with detailed tracking
    int longestOnesDetailed(vector<int>& nums, int k) {
        int n = nums.size();
        int left = 0, right = 0;
        int zeros = 0, maxLen = 0;
        
        while (right < n) {
            // Expand window
            if (nums[right] == 0) {
                zeros++;
            }
            
            // Contract window if invalid
            while (zeros > k) {
                if (nums[left] == 0) {
                    zeros--;
                }
                left++;
            }
            
            // Update result
            maxLen = max(maxLen, right - left + 1);
            right++;
        }
        
        return maxLen;
    }
};
solve the Max Consecutive Ones III problem using the sliding window technique.
Problem Analysis:

Given binary array and k flips allowed
Find maximum length of contiguous subarray containing only 1s after flipping at most k zeros
This is a classic sliding window problem

Approach:
Use two pointers (sliding window) to maintain a valid window where zeros ≤ k:

Expand right pointer to grow window
Count zeros in current window
If zeros > k, shrink window from left
Track maximum window size
Key Insights:

Sliding Window Pattern: Maintain a window [left, right] where zeros ≤ k
Two Pointers: Right expands, left contracts when needed
Invariant: Window always contains at most k zeros

Algorithm Steps:

Expand right pointer and count zeros
If zeros > k, shrink from left until zeros ≤ k
Update maximum window size
Continue until right reaches end

Time Complexity: O(n) - each element visited at most twice
Space Complexity: O(1) - only using a few variables
Example Walkthrough:
nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2

Step by step:
- right=0-2: window=[0,2], zeros=0, len=3
- right=3: window=[0,3], zeros=1, len=4  
- right=4: window=[0,4], zeros=2, len=5
- right=5: zeros=3 > k, shrink left until zeros≤2
- Continue...

Result: Maximum length = 6
Approach Comparison:

Approach 1: Standard sliding window with explicit shrinking
Approach 2: Optimized version that maintains window size instead of shrinking
Approach 3: More detailed implementation showing the process

The first approach is most intuitive and commonly used. The second approach is a clever optimization that avoids unnecessary shrinking operations while maintaining the same time complexity.
