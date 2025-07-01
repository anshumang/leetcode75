#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int maxVowels(string s, int k) {
        unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
        int maxCount = 0, count = 0;

        // Count vowels in the first window
        for (int i = 0; i < k; ++i) {
            if (vowels.count(s[i])) {
                count++;
            }
        }
        maxCount = count;

        // Slide the window
        for (int i = k; i < s.size(); ++i) {
            if (vowels.count(s[i - k])) count--;
            if (vowels.count(s[i])) count++;
            maxCount = max(maxCount, count);
        }

        return maxCount;
    }
};
