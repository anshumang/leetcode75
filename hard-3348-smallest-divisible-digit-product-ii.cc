You are given a string num which represents a positive integer, and an integer t.

A number is called zero-free if none of its digits are 0.

Return a string representing the smallest zero-free number greater than or equal to num such that the product of its digits is divisible by t. If no such number exists, return "-1".

 

Example 1:

Input: num = "1234", t = 256

Output: "1488"

Explanation:

The smallest zero-free number that is greater than 1234 and has the product of its digits divisible by 256 is 1488, with the product of its digits equal to 256.

Example 2:

Input: num = "12355", t = 50

Output: "12355"

Explanation:

12355 is already zero-free and has the product of its digits divisible by 50, with the product of its digits equal to 150.

Example 3:

Input: num = "11111", t = 26

Output: "-1"

Explanation:

No number greater than 11111 has the product of its digits divisible by 26.

 

Constraints:

2 <= num.length <= 2 * 105
num consists only of digits in the range ['0', '9'].
num does not contain leading zeros.
1 <= t <= 1014

Accepted
2,833/27K
Acceptance Rate
10.5%
Topics
Math
String
Backtracking
Greedy
Number Theory

Hint 1
t should only have 2, 3, 5 and 7 as prime factors.
Hint 2
Find the shortest suffix that must be changed.
Hint 3
Try to form the string greedily.
Similar Questions
Smallest Number With Given Digit Product

The goal is to find the smallest positive integer p that is not only divisible by a given number n, but whose digits also multiply to n.

This can be modeled as a shortest path problem on a state graph, making Breadth-First Search (BFS) the ideal algorithm. A "state" in our search can be defined by two properties: the remainder of the number
we've built so far (mod n) and the running product of its digits. Since we want the lexicographically smallest number, the BFS will naturally find the solution with the fewest digits first, and by exploring
  digits in increasing order (1 through 9), we ensure the smallest number for a given length.

The main challenge is the potentially huge state space if n is large. The solution I've prepared uses a map to keep track of visited states, which is efficient if the number of reachable states is manageable.

Here is a complete, commented C++ implementation of this BFS-based approach.

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <numeric>
#include <algorithm>
#include <vector>

// This function finds all divisors of 'n' that are "9-smooth", meaning all their
// prime factors are less than or equal to 7 (since digits are 1-9, their prime
// factors can only be 2, 3, 5, 7).
std::vector<long long> get_9_smooth_divisors(long long n) {
    std::vector<long long> divisors;
    // Find all divisors of n first
    for (long long i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            divisors.push_back(i);
            if (i * i != n) {
                divisors.push_back(n / i);
            }
        }
    }

    std::vector<long long> smooth_divisors;
    for (long long div : divisors) {
        long long temp = div;
        if (temp == 0) continue;
        // Check if the divisor is 9-smooth
        for (int prime : {2, 3, 5, 7}) {
            while (temp % prime == 0) {
                temp /= prime;
            }
        }
        if (temp == 1) {
            smooth_divisors.push_back(div);
        }
    }
    std::sort(smooth_divisors.begin(), smooth_divisors.end());
    return smooth_divisors;
}


class Solution {
public:
    // Main function to find the smallest number p such that:
    // 1. p is divisible by n
    // 2. The product of the digits of p is equal to n
    std::string smallestDivisibleDigitProduct(long long n) {
        if (n == 1) {
            return "1";
        }

        // The product of digits can only be formed by digits 1-9. This means the
        // prime factors of n can only be 2, 3, 5, and 7.
        // We find all divisors of n that satisfy this property.
        auto prods = get_9_smooth_divisors(n);
        if (prods.empty() || std::find(prods.begin(), prods.end(), n) == prods.end()) {
             // If n itself is not 9-smooth, no product of digits can equal n.
            long long temp_n = n;
            for (int prime : {2, 3, 5, 7}) {
                 while (temp_n % prime == 0) temp_n /= prime;
            }
            if (temp_n > 1) return "-1"; // Impossible
        }


        // Map product values to integer IDs for smaller state representation.
        std::map<long long, int> prod_to_id;
        for (size_t i = 0; i < prods.size(); ++i) {
            prod_to_id[prods[i]] = i;
        }

        // A BFS state is {remainder_mod_n, product_id}.
        // The queue stores the states to visit.
        std::queue<std::pair<long long, int>> q;

        // The parent map tracks how we reached each state, allowing us to
        // reconstruct the final number. It maps a state to its {previous_state, digit_used}.
        std::map<std::pair<long long, int>, std::pair<std::pair<long long, int>, int>> parent;

        // Initialize BFS with starting digits (1-9).
        // A number cannot start with 0.
        for (int d = 1; d <= 9; ++d) {
            if (prod_to_id.count(d)) {
                long long rem = d % n;
                int prod_id = prod_to_id[d];
                std::pair<long long, int> state = {rem, prod_id};

                if (parent.find(state) == parent.end()) {
                    q.push(state);
                    // The parent of a single-digit number is a fictional {0, 0} state.
                    parent[state] = {{0, 0}, d};
                }
            }
        }
        
        while (!q.empty()) {
            auto [current_rem, current_prod_id] = q.front();
            q.pop();

            long long current_prod = prods[current_prod_id];

            // Check for solution
            if (current_prod == n && current_rem == 0) {
                std::string result = "";
                std::pair<long long, int> state = {current_rem, current_prod_id};
                while (state.first != 0 || state.second != 0) {
                    auto p = parent[state];
                    result += std::to_string(p.second);
                    state = p.first;
                }
                std::reverse(result.begin(), result.end());
                return result;
            }

            // Explore next states by appending digits 0-9
            for (int d = 0; d <= 9; ++d) {
                long long next_prod_val = (d == 0) ? current_prod : current_prod * d;
                
                // The product would exceed n, or is not a valid 9-smooth divisor.
                if(d > 1 && (n < next_prod_val || n % next_prod_val != 0)) {
                    continue;
                }
                
                if (prod_to_id.count(next_prod_val)) {
                    long long next_rem = (current_rem * 10 + d) % n;
                    int next_prod_id = prod_to_id[next_prod_val];
                    
                    std::pair<long long, int> next_state = {next_rem, next_prod_id};
                    if (parent.find(next_state) == parent.end()) {
                        parent[next_state] = {{current_rem, current_prod_id}, d};
                        q.push(next_state);
                    }
                }
            }
        }

        // If queue becomes empty, no solution was found.
        return "-1";
    }
};

// --- Example Usage ---
int main() {
    Solution sol;
    long long n;

    n = 12;
    std::cout << "For n = " << n << ", smallest number is: " << sol.smallestDivisibleDigitProduct(n) << std::endl; // Expected: 216

    n = 1;
    std::cout << "For n = " << n << ", smallest number is: " << sol.smallestDivisibleDigitProduct(n) << std::endl; // Expected: 1
    
    n = 48;
    std::cout << "For n = " << n << ", smallest number is: " << sol.smallestDivisibleDigitProduct(n) << std::endl; // Expected: 68
    
    n = 13;
    std::cout << "For n = " << n << ", smallest number is: " << sol.smallestDivisibleDigitProduct(n) << std::endl; // Expected: -1 (impossible)
    
    n = 100;
    // Note: product of non-zero digits can't be a multiple of 10. But if a digit is 0, product is 0.
    // So this is impossible.
    std::cout << "For n = " << n << ", smallest number is: " << sol.smallestDivisibleDigitProduct(n) << std::endl; // Expected: -1

    return 0;
}
