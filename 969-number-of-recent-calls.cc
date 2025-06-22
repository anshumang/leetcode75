You have a RecentCounter class which counts the number of recent requests within a certain time frame.

Implement the RecentCounter class:

RecentCounter() Initializes the counter with zero recent requests.
int ping(int t) Adds a new request at time t, where t represents some time in milliseconds, and returns the number of requests that has happened in the past 3000 milliseconds
(including the new request). Specifically, return the number of requests that have happened in the inclusive range [t - 3000, t].
It is guaranteed that every call to ping uses a strictly larger value of t than the previous call.

 

Example 1:

Input
["RecentCounter", "ping", "ping", "ping", "ping"]
[[], [1], [100], [3001], [3002]]
Output
[null, 1, 2, 3, 3]

Explanation
RecentCounter recentCounter = new RecentCounter();
recentCounter.ping(1);     // requests = [1], range is [-2999,1], return 1
recentCounter.ping(100);   // requests = [1, 100], range is [-2900,100], return 2
recentCounter.ping(3001);  // requests = [1, 100, 3001], range is [1,3001], return 3
recentCounter.ping(3002);  // requests = [1, 100, 3001, 3002], range is [2,3002], return 3
 

Constraints:

1 <= t <= 109
Each test case will call ping with strictly increasing values of t.
At most 104 calls will be made to ping.

The problem describes a RecentCounter class that needs to keep track of requests within a 3000ms window. The ping method adds a new request at time t and returns the count of
requests within [t - 3000, t]. The key constraint is that t is strictly increasing with each ping call.

This problem is a classic use case for a queue (specifically, a std::queue in C++ or collections.deque in Python). As new requests come in, we add their timestamps to the back of
the queue. Since t is strictly increasing, the queue will naturally store timestamps in ascending order. When we need to count requests within the [t - 3000, t] range, we can
efficiently remove (dequeue) any requests from the front of the queue that fall outside this window (i.e., are less than t - 3000). The number of remaining elements in the queue
will be our answer.

Here's the C++ code implementation:
#include <queue> // Required for std::queue

class RecentCounter {
private:
    std::queue<int> requests; // Stores the timestamps of recent requests

public:
    RecentCounter() {
        // Constructor: Initializes the counter with zero recent requests.
        // The queue is automatically empty upon creation.
    }

    int ping(int t) {
        // Add the new request time to the back of the queue.
        requests.push(t);

        // Remove requests that are outside the [t - 3000, t] window from the front of the queue.
        // Since 't' is strictly increasing, older requests will be at the front.
        // We only need to check if the front element is less than (t - 3000).
        while (!requests.empty() && requests.front() < (t - 3000)) {
            requests.pop(); // Remove the outdated request
        }

        // The number of remaining elements in the queue is the count of requests
        // within the [t - 3000, t] range.
        return requests.size();
    }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */

// Example usage in main (for testing purposes, not part of the class itself):
/*
#include <iostream>

int main() {
    RecentCounter recentCounter;

    // Example 1:
    // Input: ["RecentCounter", "ping", "ping", "ping", "ping"]
    //        [[], [1], [100], [3001], [3002]]
    // Output: [null, 1, 2, 3, 3]

    std::cout << "ping(1) -> " << recentCounter.ping(1) << std::endl;      // requests = [1], range is [-2999,1], return 1
    std::cout << "ping(100) -> " << recentCounter.ping(100) << std::endl; // requests = [1, 100], range is [-2900,100], return 2
    std::cout << "ping(3001) -> " << recentCounter.ping(3001) << std::endl; // requests = [1, 100, 3001], range is [1,3001], return 3
    std::cout << "ping(3002) -> " << recentCounter.ping(3002) << std::endl; // requests = [1, 100, 3001, 3002], range is [2,3002], return 3

    // You can add more test cases here if needed.

    return 0;
}
*/

Explanation:

std::queue<int> requests;:

This is the core data structure. A std::queue is a container adapter that provides a FIFO (First-In, First-Out) data structure. This is perfect because we want to remove the
oldest requests when they fall out of the time window.
RecentCounter() constructor:

It's empty because a std::queue is initialized as empty by default.
int ping(int t) method:

requests.push(t);: When a new request comes in at time t, we simply add its timestamp to the back of the requests queue.
while (!requests.empty() && requests.front() < (t - 3000)): This is the crucial part for maintaining the 3000ms window.
We loop as long as the queue is not empty AND the timestamp at the front of the queue (requests.front()) is less than t - 3000.
If requests.front() is less than t - 3000, it means this request occurred more than 3000ms ago relative to the current t, so it's no longer considered "recent".
requests.pop();: We remove (dequeue) that outdated request from the front of the queue.
return requests.size();: After the while loop finishes, all requests remaining in the requests queue are guaranteed to be within the [t - 3000, t] inclusive range. We simply
return the current size of the queue.
Time and Space Complexity:

Time Complexity:
RecentCounter(): O(1)
ping(t): In the worst case, every element ever added to the queue might be processed once (pushed and popped). However, each element is pushed once and popped at most once.
  Therefore, the amortized time complexity for each ping call is O(1). While a single ping call might involve multiple pop operations, over a sequence of N ping calls, each
request is pushed once and popped at most once.
Space Complexity:
O(W), where W is the maximum number of requests that can exist within any 3000ms window. In the worst case, if requests come in very rapidly, W could be up to 3000 distinct
  timestamps (if each t is consecutive, e.g., 1, 2, ..., 3000). Given the constraints (t up to 10^9, 10^4 calls), the number of requests stored will be proportional to the
density of pings within the 3000ms window.
