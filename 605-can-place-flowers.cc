#include <iostream>
#include <vector>

class Solution {
public:
    bool canPlaceFlowers(std::vector<int>& flowerbed, int n) {
        if (n == 0) {
            return true;
        }

        int count = 0;
        for (int i = 0; i < flowerbed.size(); ++i) {
            // Check if the current plot is empty and its neighbors are also empty.
            if (flowerbed[i] == 0) {
                // Check left neighbor (or if it's the first plot)
                bool left_is_empty = (i == 0) || (flowerbed[i - 1] == 0);
                
                // Check right neighbor (or if it's the last plot)
                bool right_is_empty = (i == flowerbed.size() - 1) || (flowerbed[i + 1] == 0);

                if (left_is_empty && right_is_empty) {
                    // Plant a flower here
                    flowerbed[i] = 1;
                    count++;

                    // If we've planted enough flowers, we can stop early
                    if (count >= n) {
                        return true;
                    }
                }
            }
        }
        
        // Final check after the loop
        return count >= n;
    }
};

// Helper function to test the solution
int main() {
    Solution sol;
    std::cout << std::boolalpha; // Print "true"/"false" instead of 1/0

    // Example 1
    std::vector<int> fb1 = {1,0,0,0,1};
    int n1 = 1;
    std::cout << "Input: flowerbed = [1,0,0,0,1], n = 1" << std::endl;
    std::cout << "Output: " << sol.canPlaceFlowers(fb1, n1) << std::endl; // Expected: true

    // Example 2
    std::vector<int> fb2 = {1,0,0,0,1};
    int n2 = 2;
    std::cout << "\nInput: flowerbed = [1,0,0,0,1], n = 2" << std::endl;
    std::cout << "Output: " << sol.canPlaceFlowers(fb2, n2) << std::endl; // Expected: false
    
    // Example 3
    std::vector<int> fb3 = {0,0,1,0,1};
    int n3 = 1;
    std::cout << "\nInput: flowerbed = [0,0,1,0,1], n = 1" << std::endl;
    std::cout << "Output: " << sol.canPlaceFlowers(fb3, n3) << std::endl; // Expected: true

    return 0;
}
