//✅ Efficient Approach: Sort + Binary Search
//Sort the products lexicographically.

//For each prefix of searchWord, binary search to find the starting index.

//Collect up to 3 matching products from that point.
vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
    sort(products.begin(), products.end());
    vector<vector<string>> result;
    string prefix;

    for (char ch : searchWord) {
        prefix += ch;

        // lower_bound finds first product not less than prefix
        auto it = lower_bound(products.begin(), products.end(), prefix);
        vector<string> suggestions;

        for (int i = 0; i < 3 && it + i != products.end(); ++i) {
            if ((*(it + i)).find(prefix) == 0)
                suggestions.push_back(*(it + i));
            else
                break;
        }

        result.push_back(suggestions);
    }

    return result;
}
//🔹 Time & Space Complexity:
//Time:

//Sorting: O(n log n)

//For each character of searchWord → Binary search + 3 suggestions → O(m log n + 3m)

//Overall: O(n log n + m log n) where n = products.size(), m = searchWord.size()

//Space: O(1) extra (not counting output)
// A Trie-based solution is ideal for problems involving prefix searches like this. It improves efficiency by avoiding repeated binary searches and reducing unnecessary string comparisons.
// 🔹 Key Idea:
//Build a Trie of all products.

//At each node, store a sorted list of up to 3 suggestions for that prefix.

//Then, for each prefix of searchWord, traverse the Trie and collect suggestions.
struct TrieNode {
    TrieNode* children[26] = {};
    vector<string> suggestions;
};

class Solution {
    TrieNode* root = new TrieNode();
    
    void insert(const string& product) {
        TrieNode* node = root;
        for (char c : product) {
            int idx = c - 'a';
            if (!node->children[idx])
                node->children[idx] = new TrieNode();
            node = node->children[idx];

            // Keep only top 3 lexicographically smallest suggestions
            if (node->suggestions.size() < 3)
                node->suggestions.push_back(product);
        }
    }

public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        sort(products.begin(), products.end());  // Important for lexicographic order

        // Build Trie
        for (const string& product : products)
            insert(product);

        // Search
        vector<vector<string>> result;
        TrieNode* node = root;
        for (char c : searchWord) {
            if (node)
                node = node->children[c - 'a'];
            if (node)
                result.push_back(node->suggestions);
            else
                result.push_back({});  // No suggestions for this prefix
        }

        return result;
    }
};
//🔹 Time and Space Complexity:
//Time:

//Trie Build: O(N × L) where N = number of products, L = max length of product.

//Query: O(M) where M = length of searchWord.

//Space:

//Trie storage: depends on unique prefixes, max 26^L worst case, but practically far smaller.

//Suggestion storage: Up to 3 suggestions per node.
//✅ Benefits over Binary Search:
//Trie avoids scanning unrelated prefixes.

//Very efficient for many prefix queries over a large dictionary.
