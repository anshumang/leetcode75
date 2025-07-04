class Solution {
public:
    bool closeStrings(string word1, string word2) {
        if (word1.size() != word2.size()) return false;

        unordered_map<char, int> freq1, freq2;
        for (char c : word1) freq1[c]++;
        for (char c : word2) freq2[c]++;

        // Condition 1: Same set of characters
        unordered_set<char> set1, set2;
        for (auto& [ch, _] : freq1) set1.insert(ch);
        for (auto& [ch, _] : freq2) set2.insert(ch);
        if (set1 != set2) return false;

        // Condition 2: Same frequency multiset
        multiset<int> values1, values2;
        for (auto& [_, freq] : freq1) values1.insert(freq);
        for (auto& [_, freq] : freq2) values2.insert(freq);
        return values1 == values2;
    }
};
