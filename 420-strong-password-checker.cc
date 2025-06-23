A password is considered strong if the below conditions are all met:

It has at least 6 characters and at most 20 characters.
It contains at least one lowercase letter, at least one uppercase letter, and at least one digit.
It does not contain three repeating characters in a row (i.e., "Baaabb0" is weak, but "Baaba0" is strong).
Given a string password, return the minimum number of steps required to make password strong. if password is already strong, return 0.

In one step, you can:

Insert one character to password,
Delete one character from password, or
Replace one character of password with another character.
 

Example 1:

Input: password = "a"
Output: 5
Example 2:

Input: password = "aA1"
Output: 3
Example 3:

Input: password = "1337C0d3"
Output: 0
 

Constraints:

1 <= password.length <= 50
password consists of letters, digits, dot '.' or exclamation mark '!'.

Accepted
49,036/335.2K
Acceptance Rate
14.6%

Topics
String
Greedy
Heap (Priority Queue)

Similar Questions
Strong Password Checker II

The difficulty lies in the fact that the different conditions for a strong password (length, character types, repeating characters) are interconnected, and a single operation can often help satisfy multiple
criteria.

Here is a complete, well-commented C++ solution that breaks the problem down into three main cases based on the password's length. I've focused on making the logic, especially for the most complex case (when
  the password is too long), clear and easy to follow.
Explanation of the Logic
Count Initial Problems: The code first checks for the three basic character types (lowercase, uppercase, digit) to see how many are missing.

Case 1: Password is too short (n < 6)

The primary goal is to add 6 - n characters.

Each insertion can also be used to add a missing character type.

Therefore, the total number of required operations is the greater of the two needs: the number of insertions required to reach length 6, or the number of missing character types.

Case 2: Password is the right length (6 <= n <= 20)

No insertions or deletions are needed for length. We only need to perform replacements.

One replacement can fix a repeating sequence (e.g., changing the middle 'a' in "aaa") and also satisfy a missing character type (e.g., changing it to 'B').

The answer is the maximum of the number of replacements needed for repeating characters (length / 3) and the number of missing character types.

Case 3: Password is too long (n > 20)

This is the most complex case. We have a fixed cost of n - 20 deletions.

The key insight is to use these mandatory deletions as effectively as possible to also reduce the number of replacements needed for repeating sequences.

A deletion is most effective on a sequence whose length is a multiple of 3 (e.g., "aaaaaa"). Deleting one character leaves "aaaaa", which reduces the required replacements from 2 to 1. This is a "1-for-1" trade.

The code greedily applies the n - 20 deletions to the sequences that give the best return (i.e., save the most future replacements).

After the deletions are accounted for, the problem becomes similar to Case 2 on a 20-character string. The final answer is the n - 20 deletions plus the number of operations (max(remaining_replacements,
missing_types)) needed on the resulting string.

#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
public:
    int strongPasswordChecker(std::string password) {
        int n = password.length();

        // Step 1: Count missing character types (lowercase, uppercase, digit)
        bool has_lower = false;
        bool has_upper = false;
        bool has_digit = false;

        for (char c : password) {
            if (islower(c)) has_lower = true;
            if (isupper(c)) has_upper = true;
            if (isdigit(c)) has_digit = true;
        }
        int missing_types = (!has_lower) + (!has_upper) + (!has_digit);

        // --- Case 1: Password length is less than 6 ---
        if (n < 6) {
            // In this case, we must perform insertions.
            // An insertion can simultaneously fix a missing character type.
            // Therefore, the number of operations is the maximum of the
            // required insertions (to reach length 6) and the number of
            // missing character types. The repeating character rule is less
            // critical as insertions naturally break up sequences.
            return std::max(6 - n, missing_types);
        }

        // Step 2 for n >= 6: Find all sequences of 3 or more repeating characters.
        // `repeats` stores the length of each repeating sequence.
        // `replacements` counts how many replacements are needed to fix them.
        std::vector<int> repeats;
        int replacements = 0;
        for (int i = 0; i < n; ) {
            int j = i;
            while (j < n && password[i] == password[j]) {
                j++;
            }
            if (j - i >= 3) {
                repeats.push_back(j - i);
                replacements += (j - i) / 3;
            }
            i = j;
        }

        // --- Case 2: Password length is between 6 and 20 (inclusive) ---
        if (n >= 6 && n <= 20) {
            // We only need to perform replacements.
            // One replacement can fix a repeating sequence AND a missing type.
            // So, the answer is the maximum of the needs for each category.
            return std::max(replacements, missing_types);
        }
        
        // --- Case 3: Password length is greater than 20 ---
        int deletions = n - 20;

        // We must perform `deletions` deletions. The key is to use these
        // deletions optimally to also reduce the number of `replacements` needed.
        // A deletion is most effective on sequences where `length % 3` is smallest.
        // - Deleting 1 char from a `len % 3 == 0` sequence saves 1 replacement.
        // - Deleting 2 chars from a `len % 3 == 1` sequence saves 1 replacement.
        // - Deleting 3 chars from any sequence saves 1 replacement.

        // Greedily apply deletions to the most "valuable" sequences first.
        int deletions_left = deletions;
        
        // Priority 1: Use 1 deletion on sequences where len % 3 == 0
        for (size_t i = 0; i < repeats.size() && deletions_left > 0; ++i) {
            if (repeats[i] % 3 == 0) {
                // This sequence is a candidate for a 1-char deletion.
                repeats[i]--;
                replacements--;
                deletions_left--;
            }
        }
        
        // Priority 2: Use 2 deletions on sequences where len % 3 == 1
        // We must sort to apply this to the shortest `mod 1` sequences first.
        // However, a simpler approach is to iterate and decrement.
        // A temporary copy is used to avoid invalidating the logic while changing lengths.
        std::vector<int> temp_repeats;
        for(int len : repeats) {
             if (len % 3 == 1) temp_repeats.push_back(len);
        }
        // Applying 2 deletions is better than using them on mod 2 sequences.
        for(size_t i = 0; i < temp_repeats.size() && deletions_left >= 2; ++i) {
             replacements--;
             deletions_left -= 2;
        }


        // After priority deletions, the remaining deletions can be applied
        // in groups of 3 to any long sequence. Each group of 3 saves one replacement.
        replacements = std::max(0, replacements - (deletions_left / 3));

        // The total operations are the mandatory deletions plus the number of
        // modifications (replacements or insertions for types) needed for the
        // resulting 20-character string.
        return deletions + std::max(replacements, missing_types);
    }
};

// --- Example Usage ---
int main() {
    Solution sol;
    std::cout << "Input: \"a\", Output: " << sol.strongPasswordChecker("a") << std::endl; // Expected: 5
    std::cout << "Input: \"aA1\", Output: " << sol.strongPasswordChecker("aA1") << std::endl; // Expected: 3
    std::cout << "Input: \"1337C0d3\", Output: " << sol.strongPasswordChecker("1337C0d3") << std::endl; // Expected: 0
    std::cout << "Input: \"aaaabbbbaaaabbbbaaaabbbbaaaabbbb\", Output: " << sol.strongPasswordChecker("aaaabbbbaaaabbbbaaaabbbbaaaabbbb") << std::endl; // Expected: 12
    std::cout << "Input: \"aaaaa\", Output: " << sol.strongPasswordChecker("aaaaa") << std::endl; // Expected: 2
    std::cout << "Input: \"aaaaaaaaaaaaaaaaaaaaa\", Output: " << sol.strongPasswordChecker("aaaaaaaaaaaaaaaaaaaaa") << std::endl; // Expected: 8
    return 0;
}
