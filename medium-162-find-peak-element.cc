🧩 Problem Summary:
Given: An array nums, where adjacent elements are not equal (nums[i] ≠ nums[i+1]).

A peak element is defined as:

css
Copy
Edit
nums[i] > nums[i - 1] and nums[i] > nums[i + 1]
(For edge elements, we only compare the one neighbor that exists.)

Goal: Return the index of any one peak element.

💡 Constraints:
Time Complexity: O(log n) expected.

The array may have multiple peaks — return any peak index.

✅ Binary Search Solution (Optimal — O(log n)):
int findPeakElement(vector<int>& nums) {
    int left = 0, right = nums.size() - 1;

    while (left < right) {
        int mid = left + (right - left) / 2;

        // If mid element is less than the next, peak is on the right
        if (nums[mid] < nums[mid + 1])
            left = mid + 1;
        else
            right = mid;  // Peak is at mid or to the left
    }

    // left == right is the peak position
    return left;
}
🔍 Intuition:
If nums[mid] < nums[mid + 1], we know the slope is increasing, so a peak must exist on the right.

Otherwise, we are on a downward slope or at a peak, so move to the left.
🔁 Recursive Binary Search Version (C++):
int binarySearch(vector<int>& nums, int left, int right) {
    if (left == right)
        return left;

    int mid = left + (right - left) / 2;

    if (nums[mid] < nums[mid + 1])
        return binarySearch(nums, mid + 1, right);  // Peak on the right
    else
        return binarySearch(nums, left, mid);       // Peak on the left or at mid
}

int findPeakElement(vector<int>& nums) {
    return binarySearch(nums, 0, nums.size() - 1);
}
🔍 Explanation:
Base Case: When left == right, we've narrowed it down to a single peak element.

Recursive Step:

If the mid element is smaller than the next one, go right.

Else, go left (including mid).

Here's a C++20 / functional-style version of findPeakElement, using modern C++ idioms like:

std::function for recursion

Range-based ideas

Structured bindings (where applicable)

🧪 Functional-style C++20 Version:
#include <vector>
#include <functional>

int findPeakElement(const std::vector<int>& nums) {
    std::function<int(int, int)> binarySearch = [&](int left, int right) -> int {
        if (left == right) return left;

        int mid = left + (right - left) / 2;

        return nums[mid] < nums[mid + 1]
            ? binarySearch(mid + 1, right)
            : binarySearch(left, mid);
    };

    return binarySearch(0, static_cast<int>(nums.size()) - 1);
}

✅ Highlights of Modern/Functional Features:
Lambda recursion with std::function: Allows recursive calls without named functions.

Concise ternary logic: Makes the recursive flow expressive like functional languages.

No mutation of state: left and right are passed down instead of modified.
