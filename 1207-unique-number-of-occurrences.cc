//Approach:
//Count frequencies of each number.

//Check for uniqueness of these frequencies.
bool uniqueOccurrences(vector<int>& arr) {
    unordered_map<int, int> freq;
    unordered_set<int> seen;

    // Count frequency of each number
    for (int num : arr) {
        freq[num]++;
    }

    // Check if frequencies are unique
    for (auto [_, count] : freq) {
        if (seen.count(count)) return false;
        seen.insert(count);
    }

    return true;
}
//Time and Space Complexity:
//Time: O(n) — for both counting and checking uniqueness.

//Space: O(n) — to store counts and seen frequencies.

//views::values is from C++20
bool uniqueOccurrences(vector<int>& arr) {
    unordered_map<int, int> freq;
    for (int n : arr) ++freq[n];
    return freq.size() == unordered_set<int>(begin(freq) | views::values, end(freq) | views::values).size();
}
// more widely supported STL one-liner version (C++11+)
bool uniqueOccurrences(vector<int>& arr) {
    unordered_map<int, int> freq;
    for (int n : arr) ++freq[n];
    unordered_set<int> counts;
    transform(freq.begin(), freq.end(), inserter(counts, counts.end()), [](auto& p){ return p.second; });
    return freq.size() == counts.size();
}
bool uniqueOccurrences(vector<int>& arr) {
unordered_map<int, int> freq;
unordered_set<int> seen;
return all_of(begin(arr), end(arr), [&](int n){ return ++seen.insert(++freq[n]).second; }) && freq.size() == seen.size();
}
