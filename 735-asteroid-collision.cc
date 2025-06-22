We are given an array asteroids of integers representing asteroids in a row.

For each asteroid, the absolute value represents its size, and the sign represents its direction (positive meaning right, negative meaning left). Each asteroid moves at the same speed.

Find out the state of the asteroids after all collisions. If two asteroids meet, the smaller one will explode. If both are the same size, both will explode. Two asteroids moving in the same direction will never meet.

 

Example 1:

Input: asteroids = [5,10,-5]
Output: [5,10]
Explanation: The 10 and -5 collide resulting in 10. The 5 and 10 never collide.
Example 2:

Input: asteroids = [8,-8]
Output: []
Explanation: The 8 and -8 collide exploding each other.
Example 3:

Input: asteroids = [10,2,-5]
Output: [10]
Explanation: The 2 and -5 collide resulting in -5. The 10 and -5 collide resulting in 10.
 

Constraints:

2 <= asteroids.length <= 104
-1000 <= asteroids[i] <= 1000
asteroids[i] != 0

Navigating the Cosmos: How to Determine the Aftermath of Asteroid Collisions
To determine the final state of a row of asteroids, each with a specific size and direction, an elegant and efficient solution involves simulating the collisions using a stack data structure.
  This approach correctly handles the chain reactions of collisions in a straightforward manner.

The fundamental principle of the collisions is that they only occur when an asteroid moving to the right is followed by one moving to the left.
  Asteroids moving in the same direction will never meet. The simulation processes the asteroids one by one, using a stack to keep track of the asteroids that have survived all previous encounters.

The process unfolds as follows:

Initialize a Stack: An empty stack is created to store the asteroids that are currently stable or have survived collisions.

Iterate Through Asteroids: Each asteroid from the input array is examined in order.

Handle Right-Moving Asteroids: If an asteroid is positive (moving to the right), it cannot collide with any asteroids already in the stack (as they are to its left and moving in the same or opposite direction away from it).
Therefore, it is pushed directly onto the stack.

Handle Left-Moving Asteroids: If an asteroid is negative (moving to the left), it has the potential to collide with any right-moving asteroids at the top of the stack.
  A series of checks ensues:

Collision Check: While the stack is not empty and its top element is a right-moving asteroid (positive), a collision is imminent.
Size Comparison: The absolute sizes of the current left-moving asteroid and the right-moving asteroid at the top of the stack are compared.
If the right-moving asteroid on the stack is smaller, it explodes and is popped from the stack.
  The left-moving asteroid continues its journey inward, prompting another check with the new top of the stack.
If both asteroids are of equal size, they both explode. The right-moving asteroid is popped from the stack, and the current left-moving asteroid is discarded.
If the right-moving asteroid on the stack is larger, the current left-moving asteroid explodes and is discarded.
  The right-moving asteroid on the stack remains intact, and the process for the current left-moving asteroid ends.
No Collision: If the loop concludes without the left-moving asteroid being destroyed (either because the stack became empty or the top of the stack is also a left-moving asteroid),
the current left-moving asteroid has survived and is pushed onto the stack.
Final State: After iterating through all the asteroids, the stack will contain the asteroids that have survived all collisions, in their final order.

Example Walkthroughs:
Example 1: asteroids = [5, 10, -5]

5: Positive, push to stack. Stack: [5]
10: Positive, push to stack. Stack: [5, 10]
-5: Negative. The top of the stack is 10 (positive).
abs(-5) is 5, and the top of the stack is 10. Since 5 < 10, the -5 asteroid explodes. The stack remains unchanged. Final Result: [5, 10]
Example 2: asteroids = [8, -8]

8: Positive, push to stack. Stack: [8]
-8: Negative. The top of the stack is 8 (positive).
abs(-8) is 8, and the top of the stack is 8. Since they are equal, both explode. The 8 is popped from the stack, and the -8 is discarded. Final Result: []
Example 3: asteroids = [10, 2, -5]

10: Positive, push to stack. Stack: [10]
2: Positive, push to stack. Stack: [10, 2]
-5: Negative. The top of the stack is 2 (positive).
abs(-5) is 5, and the top of the stack is 2. Since 5 > 2, the 2 on the stack explodes and is popped. Stack: [10]
The -5 continues and now checks against the new top, 10.
abs(-5) is 5, and the top of the stack is 10. Since 5 < 10, the -5 asteroid explodes and is discarded. Final Result: [10]
This stack-based simulation ensures that each asteroid is processed in a "last-in, first-out" manner appropriate for the collision dynamics, providing a time-efficient solution
with a linear time complexity of O(n), where n is the number of asteroids.

Here is the C++ implementation for solving the asteroid collision problem using the stack-based approach.

C++ Implementation
This solution uses a std::vector as a stack to keep track of the surviving asteroids. The logic follows the simulation process described previously:
right-moving asteroids are pushed onto the stack, while left-moving asteroids can trigger collisions with the top of the stack.

The code is encapsulated within a Solution class, which is a common format on platforms like LeetCode. The main function demonstrates how to use this class
and its asteroidCollision method.

#include <iostream>
#include <vector>
#include <cmath> // For std::abs

class Solution {
public:
    /**
     * @brief Calculates the state of asteroids after all collisions.
     * @param asteroids A vector of integers representing asteroids.
     * Positive values move right, negative values move left.
     * The absolute value is the size.
     * @return A vector of integers representing the final state of the asteroids.
     */
    std::vector<int> asteroidCollision(std::vector<int>& asteroids) {
        std::vector<int> stack; // Use std::vector as a stack

        for (int ast : asteroids) {
            bool destroyed = false;
            // Collision conditions:
            // 1. Current asteroid is moving left (ast < 0).
            // 2. The stack is not empty.
            // 3. The asteroid at the top of the stack is moving right (stack.back() > 0).
            while (!stack.empty() && ast < 0 && stack.back() > 0) {
                // Get the top asteroid from the stack
                int top = stack.back();

                // Case 1: The right-moving asteroid on the stack is smaller.
                // It gets destroyed.
                if (top < std::abs(ast)) {
                    stack.pop_back();
                    continue; // The left-moving asteroid continues.
                } 
                // Case 2: Both asteroids are the same size.
                // Both are destroyed.
                else if (top == std::abs(ast)) {
                    stack.pop_back();
                    destroyed = true;
                    break;
                }
                // Case 3: The right-moving asteroid on the stack is larger.
                // The current left-moving asteroid is destroyed.
                else { // top > std::abs(ast)
                    destroyed = true;
                    break;
                }
            }

            if (!destroyed) {
                stack.push_back(ast);
            }
        }
        return stack;
    }
};

// Helper function to print a vector
void printVector(const std::vector<int>& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << (i == vec.size() - 1 ? "" : ",");
    }
    std::cout << "]" << std::endl;
}

// Example Usage
int main() {
    Solution sol;

    // Example 1
    std::vector<int> asteroids1 = {5, 10, -5};
    std::cout << "Input:  ";
    printVector(asteroids1);
    std::vector<int> result1 = sol.asteroidCollision(asteroids1);
    std::cout << "Output: ";
    printVector(result1); // Expected: [5, 10]
    std::cout << "--------------------" << std::endl;

    // Example 2
    std::vector<int> asteroids2 = {8, -8};
    std::cout << "Input:  ";
    printVector(asteroids2);
    std::vector<int> result2 = sol.asteroidCollision(asteroids2);
    std::cout << "Output: ";
    printVector(result2); // Expected: []
    std::cout << "--------------------" << std::endl;

    // Example 3
    std::vector<int> asteroids3 = {10, 2, -5};
    std::cout << "Input:  ";
    printVector(asteroids3);
    std::vector<int> result3 = sol.asteroidCollision(asteroids3);
    std::cout << "Output: ";
    printVector(result3); // Expected: [10]
    std::cout << "--------------------" << std::endl;

    // Example 4
    std::vector<int> asteroids4 = {-2, -1, 1, 2};
    std::cout << "Input:  ";
    printVector(asteroids4);
    std::vector<int> result4 = sol.asteroidCollision(asteroids4);
    std::cout << "Output: ";
    printVector(result4); // Expected: [-2, -1, 1, 2]
    std::cout << "--------------------" << std::endl;

    return 0;
}

Explanation of the C++ Code:
Headers:

<iostream> is included for printing the results to the console.
<vector> is included for using std::vector, which serves as both the input type and our stack implementation.
<cmath> provides std::abs for getting the absolute value (size) of the asteroids.
asteroidCollision Function:

It takes a std::vector<int>& asteroids as input. Taking it by reference avoids a potentially costly copy of the vector.
A std::vector<int> stack is declared. We use push_back() for pushing elements and pop_back() for popping, effectively treating it as a stack.
The code iterates through each asteroid ast in the input asteroids vector using a range-based for loop.
Collision Logic:

A boolean flag destroyed is used to track whether the current left-moving asteroid has been destroyed in a collision.
A while loop handles the chain of collisions. It continues as long as there's a potential for collision: the stack isn't empty, the current asteroid ast is moving left (< 0),
  and the asteroid at the top of the stack (stack.back()) is moving right (> 0).
Inside the loop, the sizes are compared (stack.back() vs std::abs(ast)), and the appropriate action is taken:
stack.pop_back(): The asteroid on the stack is destroyed. We continue the loop to check the current ast against the new top.
destroyed = true; break;: The current ast is destroyed (or both are), so we set the flag and break out of the collision-check while loop.
After the while loop, if the destroyed flag is false, it means the current asteroid survived all potential collisions (or there were none), so it's added to the stack via
  stack.push_back(ast).
Return Value:

The function returns the stack vector, which now contains the final configuration of surviving asteroids.
main function:

This function demonstrates how to use the Solution class. It creates several test cases, calls the asteroidCollision method, and uses a helper function printVector to display
the results in a clear format.

Here is the C++ solution for the asteroid collision problem using std::stack as requested.

The core simulation logic remains identical, but we will use the standard std::stack container, which requires using methods like push(), pop(), and top().

One key difference is that std::stack does not allow direct iteration. Since the function must return a std::vector, we need to transfer the contents from the final stack to a
vector at the end. This process naturally reverses the order, so a final reversal of the vector is required to get the correct output.

#include <iostream>
#include <vector>
#include <stack>     // Required for std::stack
#include <cmath>     // For std::abs
#include <algorithm> // For std::reverse

class Solution {
public:
    /**
     * @brief Calculates the state of asteroids after all collisions using std::stack.
     * @param asteroids A vector of integers representing asteroids.
     * Positive values move right, negative values move left.
     * The absolute value is the size.
     * @return A vector of integers representing the final state of the asteroids.
     */
    std::vector<int> asteroidCollision(std::vector<int>& asteroids) {
        std::stack<int> s; // Use the standard stack container

        for (int ast : asteroids) {
            bool destroyed = false;
            // Collision conditions: current asteroid moves left, stack has right-moving asteroids
            while (!s.empty() && ast < 0 && s.top() > 0) {
                // Case 1: The right-moving asteroid on the stack is smaller.
                if (s.top() < std::abs(ast)) {
                    s.pop(); // It gets destroyed.
                    continue; // The left-moving asteroid continues its check.
                }
                // Case 2: Both asteroids are the same size.
                else if (s.top() == std::abs(ast)) {
                    s.pop(); // Both are destroyed.
                    destroyed = true;
                    break;
                }
                // Case 3: The right-moving asteroid on the stack is larger.
                else { // s.top() > std::abs(ast)
                    destroyed = true; // The current left-moving asteroid is destroyed.
                    break;
                }
            }

            if (!destroyed) {
                s.push(ast);
            }
        }

        // Convert the stack to a vector for the return value.
        std::vector<int> result(s.size());
        int i = s.size() - 1;
        while (!s.empty()) {
            result[i--] = s.top(); // Place elements from top of stack to end of vector
            s.pop();
        }

        return result;
    }
};

// Helper function to print a vector
void printVector(const std::vector<int>& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << (i == vec.size() - 1 ? "" : ",");
    }
    std::cout << "]" << std::endl;
}

// Example Usage
int main() {
    Solution sol;

    // Example 1
    std::vector<int> asteroids1 = {5, 10, -5};
    std::cout << "Input:  ";
    printVector(asteroids1);
    std::vector<int> result1 = sol.asteroidCollision(asteroids1);
    std::cout << "Output: ";
    printVector(result1); // Expected: [5, 10]
    std::cout << "--------------------" << std::endl;

    // Example 2
    std::vector<int> asteroids2 = {8, -8};
    std::cout << "Input:  ";
    printVector(asteroids2);
    std::vector<int> result2 = sol.asteroidCollision(asteroids2);
    std::cout << "Output: ";
    printVector(result2); // Expected: []
    std::cout << "--------------------" << std::endl;

    // Example 3
    std::vector<int> asteroids3 = {10, 2, -5};
    std::cout << "Input:  ";
    printVector(asteroids3);
    std::vector<int> result3 = sol.asteroidCollision(asteroids3);
    std::cout << "Output: ";
    printVector(result3); // Expected: [10]
    std::cout << "--------------------" << std::endl;

    return 0;
}

Key Differences from the std::vector Approach
Header: You must include the <stack> header.
Container: We declare std::stack<int> s; instead of std::vector<int> stack;.
Stack Operations:
s.push(value) is used instead of vector.push_back(value).
s.pop() is used instead of vector.pop_back().
s.top() is used to access the top element instead of vector.back().
Final Conversion: The most significant change is at the end. A std::stack cannot be returned directly where a std::vector is expected. The contents must be copied out.
  The process of popping from the stack and filling a vector from the end (result[i--]) correctly reconstructs the final asteroid order without needing a separate call to
std::reverse.
