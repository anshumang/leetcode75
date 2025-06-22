Design an algorithm that collects daily price quotes for some stock and returns the span of that stock's price for the current day.

The span of the stock's price in one day is the maximum number of consecutive days (starting from that day and going backward) for which the stock price was less than or equal to the price of that day.

For example, if the prices of the stock in the last four days is [7,2,1,2] and the price of the stock today is 2, then the span of today is 4 because starting from today, the price of the stock was less than or equal 2 for 4 consecutive days.
Also, if the prices of the stock in the last four days is [7,34,1,2] and the price of the stock today is 8, then the span of today is 3 because starting from today, the price of the stock was less than or equal 8 for 3 consecutive days.
Implement the StockSpanner class:

StockSpanner() Initializes the object of the class.
int next(int price) Returns the span of the stock's price given that today's price is price.
 

Example 1:

Input
["StockSpanner", "next", "next", "next", "next", "next", "next", "next"]
[[], [100], [80], [60], [70], [60], [75], [85]]
Output
[null, 1, 1, 1, 2, 1, 4, 6]

Explanation
StockSpanner stockSpanner = new StockSpanner();
stockSpanner.next(100); // return 1
stockSpanner.next(80);  // return 1
stockSpanner.next(60);  // return 1
stockSpanner.next(70);  // return 2
stockSpanner.next(60);  // return 1
stockSpanner.next(75);  // return 4, because the last 4 prices (including today's price of 75) were less than or equal to today's price.
stockSpanner.next(85);  // return 6
 

Constraints:

1 <= price <= 105
At most 104 calls will be made to next.

The problem asks us to design a StockSpanner class that calculates the "span" for a given stock price. The span is defined as the maximum number of consecutive days (including
the current day and going backward) for which the stock price was less than or equal to the current day's price.

This problem is a classic application of a monotonic stack. A monotonic stack is a stack that maintains its elements in a strictly increasing or strictly decreasing order. In
this case, we'll use a monotonically decreasing stack to store pairs of (price, span_so_far).

Here's the intuition:

When a new price comes in, we want to find out how many consecutive previous days had prices less than or equal to the current price.

If the stack is empty or the current price is less than the price at the top of the stack:

This means the current price is lower than the most recent higher price. Its span is simply 1 (itself). We push (price, 1) onto the stack.
If the current price is greater than or equal to the price at the top of the stack:

This means the current price can "extend" the span of previous days. We need to pop elements from the stack as long as their prices are less than or equal to the current price.
As we pop an element (prev_price, prev_span), we add prev_span to our current span_count. This is because all days covered by prev_span also had prices less than or equal to
prev_price, and since prev_price <= current_price, those days also satisfy the condition for the current price.
We continue this process until the stack is empty or we find an element on the stack whose price is strictly greater than the current price.
Once the loop finishes, we push (price, span_count) onto the stack.
Let's trace the example [100], [80], [60], [70], [60], [75], [85] with a stack of (price, span) pairs:

next(100):

Stack: []
100 is greater than or equal to nothing.
span_count = 1
Push (100, 1)
Stack: [(100, 1)]
Return 1
next(80):

Stack: [(100, 1)]
80 < 100. No popping.
span_count = 1
Push (80, 1)
Stack: [(100, 1), (80, 1)]
Return 1
next(60):

Stack: [(100, 1), (80, 1)]
60 < 80. No popping.
span_count = 1
Push (60, 1)
Stack: [(100, 1), (80, 1), (60, 1)]
Return 1
next(70):

Stack: [(100, 1), (80, 1), (60, 1)]
70 >= 60: Pop (60, 1). span_count = 1 + 1 = 2.
Stack: [(100, 1), (80, 1)]
70 < 80: Stop popping.
Push (70, 2)
Stack: [(100, 1), (80, 1), (70, 2)]
Return 2
next(60):

Stack: [(100, 1), (80, 1), (70, 2)]
60 < 70. No popping.
span_count = 1
Push (60, 1)
Stack: [(100, 1), (80, 1), (70, 2), (60, 1)]
Return 1
next(75):

Stack: [(100, 1), (80, 1), (70, 2), (60, 1)]
75 >= 60: Pop (60, 1). span_count = 1 + 1 = 2.
Stack: [(100, 1), (80, 1), (70, 2)]
75 >= 70: Pop (70, 2). span_count = 2 + 2 = 4.
Stack: [(100, 1), (80, 1)]
75 < 80: Stop popping.
Push (75, 4)
Stack: [(100, 1), (80, 1), (75, 4)]
Return 4
next(85):

Stack: [(100, 1), (80, 1), (75, 4)]
85 >= 75: Pop (75, 4). span_count = 1 + 4 = 5.
Stack: [(100, 1), (80, 1)]
85 >= 80: Pop (80, 1). span_count = 5 + 1 = 6.
Stack: [(100, 1)]
85 < 100: Stop popping.
Push (85, 6)
Stack: [(100, 1), (85, 6)]
Return 6
This matches the example output.

#include <stack> // Required for std::stack
#include <utility> // Required for std::pair

class StockSpanner {
private:
    // A stack to store pairs of (price, span).
    // The stack will maintain elements in monotonically decreasing order of price.
    // That is, stack.top().first will always be <= than the element below it.
    std::stack<std::pair<int, int>> s;

public:
    StockSpanner() {
        // Constructor: The stack is initially empty.
    }

    int next(int price) {
        int span = 1; // Initialize span for the current day to 1 (at least itself)

        // While the stack is not empty and the price at the top of the stack
        // is less than or equal to the current 'price':
        // This means the current 'price' can "absorb" the span of the top element
        // and its preceding elements that were also less than or equal to it.
        while (!s.empty() && s.top().first <= price) {
            span += s.top().second; // Add the span of the popped element to the current span
            s.pop();                // Remove the element from the stack
        }

        // Push the current price and its calculated span onto the stack.
        s.push({price, span});

        // Return the calculated span for the current day.
        return span;
    }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */

/*
// Example usage (for testing purposes, not part of the class itself):
#include <iostream>
#include <vector>

int main() {
    StockSpanner stockSpanner;

    std::vector<int> prices = {100, 80, 60, 70, 60, 75, 85};
    std::vector<int> expected_spans = {1, 1, 1, 2, 1, 4, 6};

    for (size_t i = 0; i < prices.size(); ++i) {
        int current_price = prices[i];
        int actual_span = stockSpanner.next(current_price);
        std::cout << "next(" << current_price << ") -> " << actual_span
                  << " (Expected: " << expected_spans[i] << ")" << std::endl;
    }

    // Another example: [7,2,1,2] today 2
    // StockSpanner stockSpanner2;
    // std::cout << "--- Custom Example ---" << std::endl;
    // stockSpanner2.next(7); // 1
    // stockSpanner2.next(2); // 1
    // stockSpanner2.next(1); // 1
    // stockSpanner2.next(2); // (pop 1 (span 1), span = 1+1 = 2), (pop 2 (span 2), span = 2+2=4). Push (2,4) -> 4
    // std::cout << "next(7) -> " << stockSpanner2.next(7) << std::endl;
    // std::cout << "next(2) -> " << stockSpanner2.next(2) << std::endl;
    // std::cout << "next(1) -> " << stockSpanner2.next(1) << std::endl;
    // std::cout << "next(2) -> " << stockSpanner2.next(2) << std::endl; // Should be 4 here

    return 0;
}
*/

Time and Space Complexity:

Time Complexity:
StockSpanner(): O(1)
next(price): In the worst case, an element might be pushed onto the stack once and popped from the stack once over the lifetime of the StockSpanner object. While a single next
call might involve multiple pop operations, each element enters and leaves the stack at most once. Therefore, the amortized time complexity for each next call is O(1).
Space Complexity:
O(N), where N is the number of calls to next (up to 10^4). In the worst case (e.g., prices are always decreasing), all prices could be stored in the stack.
