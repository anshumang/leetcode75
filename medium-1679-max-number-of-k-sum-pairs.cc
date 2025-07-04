🔧 Approach 1: Hash Map
class Solution {
public:
    int maxOperations(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        int operations = 0;

        for (int num : nums) {
            int complement = k - num;

            // If the complement exists, we can form a pair
            if (freq[complement] > 0) {
                operations++;
                freq[complement]--;  // Use one instance of the complement
            } else {
                freq[num]++;  // Save this num to pair later
            }
        }

        return operations;
    }
};

🧑‍💻 C++ Code (Two Pointers):
class Solution {
public:
    int maxOperations(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());  // Sort the array
        int left = 0, right = nums.size() - 1;
        int operations = 0;

        while (left < right) {
            int sum = nums[left] + nums[right];

            if (sum == k) {
                operations++;
                left++;
                right--;
            } else if (sum < k) {
                left++;  // Need a larger sum → move left up
            } else {
                right--;  // Need a smaller sum → move right down
            }
        }

        return operations;
    }
};
