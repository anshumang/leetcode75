In the world of Dota2, there are two parties: the Radiant and the Dire.

The Dota2 senate consists of senators coming from two parties. Now the Senate wants to decide on a change in the Dota2 game.
The voting for this change is a round-based procedure. In each round, each senator can exercise one of the two rights:

Ban one senator's right: A senator can make another senator lose all his rights in this and all the following rounds.
Announce the victory: If this senator found the senators who still have rights to vote are all from the same party, he can announce the victory and decide on the change in the game.
Given a string senate representing each senator's party belonging. The character 'R' and 'D' represent the Radiant party and the Dire party.
  Then if there are n senators, the size of the given string will be n.

The round-based procedure starts from the first senator to the last senator in the given order. This procedure will last until the end of voting.
All the senators who have lost their rights will be skipped during the procedure.

Suppose every senator is smart enough and will play the best strategy for his own party. Predict which party will finally announce the victory and change the Dota2 game.
The output should be "Radiant" or "Dire".

 

Example 1:

Input: senate = "RD"
Output: "Radiant"
Explanation: 
The first senator comes from Radiant and he can just ban the next senator's right in round 1. 
And the second senator can't exercise any rights anymore since his right has been banned. 
And in round 2, the first senator can just announce the victory since he is the only guy in the senate who can vote.
Example 2:

Input: senate = "RDD"
Output: "Dire"
Explanation: 
The first senator comes from Radiant and he can just ban the next senator's right in round 1. 
And the second senator can't exercise any rights anymore since his right has been banned. 
And the third senator comes from Dire and he can ban the first senator's right in round 1. 
And in round 2, the third senator can just announce the victory since he is the only guy in the senate who can vote.

  The Greedy Strategy
The problem states that every senator is smart and will play the best strategy for their party. Let's analyze what this means.

When it's a senator's turn to vote, their goal is to eliminate an opponent to help their party win. To be most effective, they should eliminate the most immediate threat.
  The most immediate threat from the opposing party is the one who is next in line to vote.
  By banning this next-in-line opponent, a senator ensures that their ban has the maximum immediate impact, preventing that opponent from casting their own ban.

Therefore, the optimal greedy strategy is: Each senator will use their turn to ban the senator from the opposing party who is next in the voting order.

Algorithm: Using Queues
The round-based, circular nature of the voting process makes a queue an ideal data structure.
We can simulate the process using two queues: one for the Radiant senators and one for the Dire senators.
  The queues will store the original indices of the senators to maintain the voting order.

Initialization:

Create two queues, one for Radiant indices (radiant_queue) and one for Dire indices (dire_queue).
Iterate through the input senate string. For each senator at index i, push i into the corresponding party's queue.
Simulation Loop:

Continue the simulation as long as both parties have senators left (i.e., both queues are not empty).

In each step of the loop, we compare the indices at the front of both queues. The senator with the smaller index gets to vote first in the current round.

Let r_idx be the index from the front of the radiant_queue and d_idx be from the dire_queue.
If r_idx < d_idx:

The Radiant senator votes. They ban the next Dire senator (who is at d_idx). We simulate this by simply popping the front of the dire_queue.
The Radiant senator who just voted gets to participate in the next round.
We simulate this by popping them from the front of their queue and immediately pushing them to the back, but with an updated index (r_idx + n, where n is the original number of senators).
Adding n ensures they are correctly placed at the end of the line for the next round.
If d_idx < r_idx:

The Dire senator votes. They ban the next Radiant senator (r_idx). Pop the front of the radiant_queue.
The Dire senator survives for the next round. Pop them from the front and push d_idx + n to the back of the dire_queue.
Announce Victory:

The loop terminates when one of the queues becomes empty.
If the radiant_queue is empty, the Dire party wins.
If the dire_queue is empty, the Radiant party wins.

#include <iostream>
#include <string>
#include <vector>
#include <queue>

class Solution {
public:
    std::string predictPartyVictory(std::string senate) {
        int n = senate.length();
        
        std::queue<int> radiant_queue;
        std::queue<int> dire_queue;

        // Populate the queues with the initial indices of the senators
        for (int i = 0; i < n; ++i) {
            if (senate[i] == 'R') {
                radiant_queue.push(i);
            } else {
                dire_queue.push(i);
            }
        }

        // Simulate the rounds
        while (!radiant_queue.empty() && !dire_queue.empty()) {
            int r_idx = radiant_queue.front();
            radiant_queue.pop();
            
            int d_idx = dire_queue.front();
            dire_queue.pop();

            // The senator with the smaller original index gets to vote and ban the other.
            // The winner gets to vote again in the next round.
            if (r_idx < d_idx) {
                // Radiant senator bans the Dire senator.
                // The Radiant senator is re-queued for the next round.
                radiant_queue.push(r_idx + n);
            } else {
                // Dire senator bans the Radiant senator.
                // The Dire senator is re-queued for the next round.
                dire_queue.push(d_idx + n);
            }
        }

        // The party with senators remaining announces victory.
        return radiant_queue.empty() ? "Dire" : "Radiant";
    }
};

// Helper function to test the solution
int main() {
    Solution sol;
    
    // Example 1
    std::string s1 = "RD";
    std::cout << "Input: " << s1 << std::endl;
    std::cout << "Output: " << sol.predictPartyVictory(s1) << std::endl; // Expected: "Radiant"

    // Example 2
    std::string s2 = "RDD";
    std::cout << "\nInput: " << s2 << std::endl;
    std::cout << "Output: " << sol.predictPartyVictory(s2) << std::endl; // Expected: "Dire"
    
    // Example 3
    std::string s3 = "DDRRR";
    std::cout << "\nInput: " << s3 << std::endl;
    std::cout << "Output: " << sol.predictPartyVictory(s3) << std::endl; // Expected: "Dire"

    return 0;
}
