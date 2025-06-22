Given an array of integers temperatures represents the daily temperatures, return an array answer such that answer[i] is the number of days you have to wait after the ith day to get a warmer temperature. If there is no future day for which this is possible, keep answer[i] == 0 instead.

 

Example 1:

Input: temperatures = [73,74,75,71,69,72,76,73]
Output: [1,1,4,2,1,1,0,0]
Example 2:

Input: temperatures = [30,40,50,60]
Output: [1,1,1,0]
Example 3:

Input: temperatures = [30,60,90]
Output: [1,1,0]
 

Constraints:

1 <= temperatures.length <= 105
30 <= temperatures[i] <= 100

Finding the Next Warmer Day: A Monotonic Stack Approach
To efficiently solve the "Daily Temperatures" problem, where we need to find the number of days to wait for a warmer temperature, a specialized data structure known as a
monotonic stack provides an elegant and optimal solution. This method avoids the performance pitfalls of a brute-force search by processing the temperatures in a single pass.

The core idea is to maintain a stack of indices corresponding to days with temperatures that are waiting for a future warmer day. This stack is kept in a "monotonic decreasing"
order of temperatures. That is, from the bottom to the top of the stack, the temperatures for the stored indices will always be decreasing or equal.

Here is a step-by-step breakdown of the algorithm:

Initialization:

Create an answer array of the same size as the temperatures array, and initialize all its elements to 0. This handles the default case where no warmer future day exists.
Initialize an empty stack. This stack will not store the temperatures themselves, but rather the indices of the days.
Iterate Through Temperatures: Traverse the temperatures array from left to right, examining each day's temperature at index i.

Process the Stack: For the current day i, look at the index at the top of the stack.

While the stack is not empty and the temperature of the day indexed by the top of the stack is less than the current day's temperature:
This means the current day i is the first warmer day found for the day at the top of the stack.
Get the index from the top of the stack: prev_index = stack.top().
Pop the index from the stack.
Calculate the waiting period: days_to_wait = i - prev_index.
Store this result in the answer array: answer[prev_index] = days_to_wait.
Repeat this process, as the current day might be the warmer day for multiple previous days in the stack.
Push the Current Index: After the while loop finishes, push the current index i onto the stack. This index now waits for its own future warmer day, and its addition maintains the
monotonic decreasing nature of the stack.

Final Result: After iterating through all the temperatures, any indices remaining in the stack have no future warmer days. Since the answer array was initialized to zeros, these
  entries are already correct. The answer array is now complete and can be returned.

Example Walkthrough
Let's trace the algorithm with temperatures = [73, 74, 75, 71, 69, 72, 76, 73].

| Day (i) | Temp | Stack (indices) | answer Array | Action |
| :--- | :--: | :---: | :---: | :--- |
| 0 | 73 | [0] | [0,0,0,0,0,0,0,0] | 73 is cooler than nothing. Push index 0. |
| 1 | 74 | [1] | [1,0,0,0,0,0,0,0] | 74 > 73 (at index 0). Pop 0. answer[0] = 1-0=1. Push index 1. |
| 2 | 75 | [2] | [1,1,0,0,0,0,0,0] | 75 > 74 (at index 1). Pop 1. answer[1] = 2-1=1. Push index 2. |
| 3 | 71 | [2, 3] | [1,1,0,0,0,0,0,0] | 71 &lt; 75 (at index 2). Push index 3. |
| 4 | 69 | [2, 3, 4] | [1,1,0,0,0,0,0,0] | 69 &lt; 71 (at index 3). Push index 4. |
| 5 | 72 | [2, 5] | [1,1,0,2,1,0,0,0] | 72 > 69 (at index 4). Pop 4. answer[4] = 5-4=1. &lt;br> 72 > 71 (at index 3). Pop 3. answer[3] = 5-3=2. &lt;br> 72 &lt; 75 (at index 2).
  Stop. Push index 5. |
| 6 | 76 | [6] | [1,1,4,2,1,1,0,0] | 76 > 72 (at index 5). Pop 5. answer[5] = 6-5=1. &lt;br> 76 > 75 (at index 2). Pop 2. answer[2] = 6-2=4. &lt;br> Stack is empty. Push index 6. |
| 7 | 73 | [6, 7] | [1,1,4,2,1,1,0,0] | 73 &lt; 76 (at index 6). Push index 7. |

End of loop. Indices 6 and 7 remain in the stack, but their corresponding answer values are already 0.

Final Result: [1, 1, 4, 2, 1, 1, 0, 0]

This approach is highly efficient, with a time complexity of O(n) because each index is pushed onto and popped from the stack at most once. The space complexity is also O(n) in
the worst-case scenario (e.g., a strictly decreasing temperature list).

Here is the C++ code that implements the monotonic stack solution for the "Daily Temperatures" problem.

C++ Implementation
This solution uses std::stack to keep track of the indices of days that are awaiting a warmer day. The code is efficient, processing the entire array in a single pass.

The main function includes all the examples from the problem description to demonstrate that the code works correctly.

#include <iostream>
#include <vector>
#include <stack>

class Solution {
public:
    /**
     * @brief Given a list of daily temperatures, calculates how many days one has to wait
     * until a warmer temperature.
     * @param temperatures A vector of integers representing daily temperatures.
     * @return A vector of integers where each element is the number of waiting days.
     * If no warmer day exists, the value is 0.
     */
    std::vector<int> dailyTemperatures(std::vector<int>& temperatures) {
        int n = temperatures.size();
        // 1. Initialize the answer vector with all 0s.
        std::vector<int> answer(n, 0);
        // Stack will store indices of the temperatures.
        std::stack<int> s;

        // 2. Iterate through the temperatures array.
        for (int i = 0; i < n; ++i) {
            // 3. Check if the current temperature is warmer than the temperature
            //    at the index on top of the stack.
            while (!s.empty() && temperatures[s.top()] < temperatures[i]) {
                // Get the index of the day that was waiting for a warmer day.
                int prev_index = s.top();
                s.pop();

                // Calculate the number of days waited and update the answer.
                answer[prev_index] = i - prev_index;
            }
            // 4. Push the current day's index onto the stack. It now waits
            //    for a future warmer day.
            s.push(i);
        }

        // 5. Any indices left in the stack have no warmer future day.
        //    Their answer remains 0, which was the initial value.
        return answer;
    }
};

// Helper function to print a vector for easy testing
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
    std::vector<int> temps1 = {73, 74, 75, 71, 69, 72, 76, 73};
    std::cout << "Input:  ";
    printVector(temps1);
    std::vector<int> result1 = sol.dailyTemperatures(temps1);
    std::cout << "Output: ";
    printVector(result1); // Expected: [1,1,4,2,1,1,0,0]
    std::cout << "--------------------" << std::endl;

    // Example 2
    std::vector<int> temps2 = {30, 40, 50, 60};
    std::cout << "Input:  ";
    printVector(temps2);
    std::vector<int> result2 = sol.dailyTemperatures(temps2);
    std::cout << "Output: ";
    printVector(result2); // Expected: [1,1,1,0]
    std::cout << "--------------------" << std::endl;

    // Example 3
    std::vector<int> temps3 = {30, 60, 90};
    std::cout << "Input:  ";
    printVector(temps3);
    std::vector<int> result3 = sol.dailyTemperatures(temps3);
    std::cout << "Output: ";
    printVector(result3); // Expected: [1,1,0]
    std::cout << "--------------------" << std::endl;

    return 0;
}

Explanation of the C++ Code:
Headers:

<iostream>: For printing the input and output to the console.
<vector>: For using std::vector to handle the temperature and answer arrays.
<stack>: For using std::stack as our monotonic stack.
dailyTemperatures Function:

It accepts a std::vector<int>& temperatures by reference to avoid making an unnecessary copy.
int n = temperatures.size(); gets the number of days.
std::vector<int> answer(n, 0); creates the result vector and initializes all its elements to 0, fulfilling the requirement for days with no warmer future.
std::stack<int> s; declares the stack that will hold indices.
The Loop:

The for loop iterates from the first day (i = 0) to the last.
The while loop inside is the core of the algorithm. It checks if the stack s has any indices and if the temperature on the current day i is greater than the temperature on the
day indexed by s.top().
If the condition is true, it means i is the answer for the day at s.top(). We record the day difference (i - s.top()) in our answer vector and pop the index from the stack. This
  while loop continues until the current day is no longer warmer than the day at the top of the stack, or the stack becomes empty.
Finally, s.push(i); adds the current day's index to the stack to await its own warmer day.
main Function:

This sets up a Solution object and runs the three examples provided in the problem description, printing the results to verify the correctness of the implementation.
