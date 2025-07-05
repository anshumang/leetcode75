🧩 Approach (Dynamic Programming):
Let dp[i] be the maximum money that can be robbed from the first i+1 houses.

We can define:

dp[i] = max(dp[i-1], dp[i-2] + nums[i])

Rob the current house → dp[i-2] + nums[i]

Skip the current house → dp[i-1]

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];

        vector<int> dp(n);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);

        for (int i = 2; i < n; ++i) {
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        }

        return dp[n - 1];
    }
};

🔁 Space Optimization:
We don’t need the entire dp[] array—just the last two values:

class Solution {
public:
    int rob(vector<int>& nums) {
        int prev1 = 0, prev2 = 0;
        for (int num : nums) {
            int temp = prev1;
            prev1 = max(prev2 + num, prev1);
            prev2 = temp;
        }
        return prev1;
    }
};

