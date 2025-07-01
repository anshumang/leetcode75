🔍 Key Observations:
You can think of this as finding the longest subarray with at most one zero.

Use a sliding window to maintain a subarray with at most 1 zero.

Since one element must be deleted, if the entire array is 1s, the result is n - 1.

✅ C++ Solution (Sliding Window):

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int left = 0, zeroCount = 0, maxLen = 0;

        for (int right = 0; right < nums.size(); ++right) {
            if (nums[right] == 0) zeroCount++;

            // If more than one zero in window, shrink it
            while (zeroCount > 1) {
                if (nums[left] == 0) zeroCount--;
                left++;
            }

            // Since we must delete one element, the subarray length is (right - left)
            maxLen = max(maxLen, right - left);
        }

        return maxLen;
    }
};
🧠 Idea:
We'll maintain two DP states at each index:

keep[i]: Length of subarray of 1s ending at i without deletion.

deleteOne[i]: Length of subarray of 1s ending at i with one deletion used.

Then we compute the max of all deleteOne[i].

✅ C++ Code (DP Approach):
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int n = nums.size();
        int keep = 0;        // Length ending here with no deletion
        int deleteOne = 0;   // Length ending here with one deletion
        int maxLen = 0;

        for (int i = 0; i < n; ++i) {
            if (nums[i] == 1) {
                keep += 1;
                deleteOne += 1;
            } else {
                deleteOne = keep;  // Use the one allowed deletion here
                keep = 0;
            }
            maxLen = max(maxLen, deleteOne);
        }

        // Handle edge case: all 1s, must delete one
        return (maxLen == n) ? maxLen - 1 : maxLen;
    }
};
🧠 Functional Concept:
Rather than using mutable state, we'll use std::accumulate or a loop with lambda-style logic and treat the state like an accumulator tuple.

But since C++ is not purely functional, we'll simulate it using clean state-tracking and expressive inline logic.
✅ C++ Code (Functional-Inspired):
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int maxLen = 0;

        // prev is the length of 1s streak before the last 0
        // curr is the length of current 1s streak
        int prev = 0, curr = 0;

        for (int num : nums) {
            if (num == 1) {
                curr++;
            } else {
                // When hitting a zero, shift curr to prev and reset curr
                prev = curr;
                curr = 0;
            }
            maxLen = max(maxLen, prev + curr);
        }

        // All 1s? Must delete one
        return (maxLen == nums.size()) ? maxLen - 1 : maxLen;
    }
};
📋 Notes:
We treat each zero as the "deleted" element and calculate the length of the two segments of 1s on either side.

prev + curr gives us the length of the combined 1s around a deleted zero.

This maintains a clean and immutable-style update pattern.

  ✅ C++ Code Using std::accumulate:
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        using State = tuple<int, int, int>;  // (prev, curr, maxLen)

        auto result = accumulate(nums.begin(), nums.end(), State{0, 0, 0},
            [](State state, int num) {
                auto [prev, curr, maxLen] = state;

                if (num == 1) {
                    curr++;
                } else {
                    prev = curr;
                    curr = 0;
                }

                return State{prev, curr, max(maxLen, prev + curr)};
            }
        );

        int prev, curr, maxLen;
        tie(prev, curr, maxLen) = result;

        // Edge case: all 1s, must delete one
        return (maxLen == nums.size()) ? maxLen - 1 : maxLen;
    }
};
🧠 How It Works:
We track prev (previous 1's streak before a 0), curr (current streak), and maxLen.

For each element, we update state via a lambda passed to std::accumulate.

Final result is stored in a tuple (prev, curr, maxLen), and we return the final max.
