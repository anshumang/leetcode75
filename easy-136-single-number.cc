//Optimal Approach: Bit Manipulation (XOR)
//✅ Key Insight:
//a ^ a = 0

//a ^ 0 = a

//XOR is commutative and associative, so all pairs cancel out.
int singleNumber(vector<int>& nums) {
    int result = 0;
    for (int num : nums) {
        result ^= num;
    }
    return result;
}
//Time and Space Complexity:
//Time: O(n)

//Space: O(1)
//Optional Approaches (less optimal):
//Use a hash map to count frequency → O(n) time, O(n) space

//Sort and compare neighbors → O(n log n) time, O(1) or O(n) space

//Great — the extension where every number appears three times except one (which appears once) is a classic variation and a bit trickier.

//This is LeetCode 137. Single Number II.
//🔸 Idea: Bit Counting
//Count the number of 1s at each bit position across all numbers.
//If a bit appears 3*k + 1 times, it must belong to the unique number.
int singleNumber(vector<int>& nums) {
    int result = 0;
    for (int i = 0; i < 32; ++i) {
        int sum = 0;
        for (int num : nums) {
            sum += (num >> i) & 1;
        }
        if (sum % 3 != 0) {
            result |= (1 << i);
        }
    }
    return result;
}
//✅ This handles negative numbers correctly because of how 2's complement is represented.
//🔸 Time & Space:
//Time: O(32 × n) = O(n)

//Space: O(1)
//🔸 Alternative (Advanced): Bitmask Trick (using two variables)
//This version uses clever bitmasking to track bits seen once and twice.
int singleNumber(vector<int>& nums) {
    int ones = 0, twos = 0;
    for (int num : nums) {
        ones = (ones ^ num) & ~twos;
        twos = (twos ^ num) & ~ones;
    }
    return ones;
}
//🧠 This approach is harder to grasp but is still O(n) time, O(1) space and very elegant.
