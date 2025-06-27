string reverseWords(string s) {
    stringstream ss(s);
    string word;
    vector<string> words;

    while (ss >> word) {
        words.push_back(word);
    }

    reverse(words.begin(), words.end());

    string result;
    for (int i = 0; i < words.size(); ++i) {
        result += words[i];
        if (i < words.size() - 1) result += ' ';
    }

    return result;
}
//🔹 Time & Space Complexity:
//Time: O(n)

//Space: O(n) (for storing words)

//🔸 In-place (more advanced) version:
//You can do it in-place by:

//Trim extra spaces.

//Reverse the entire string.

//Reverse each word individually.
//Removes extra spaces (leading, trailing, and multiple in-between),

//Reverses the entire string,

//Reverses each word individually.
class Solution {
public:
    void reverse(string& s, int left, int right) {
        while (left < right)
            swap(s[left++], s[right--]);
    }

    void trimSpaces(string& s) {
        int n = s.size();
        int i = 0, j = 0;

        // Skip leading spaces
        while (i < n && s[i] == ' ') i++;

        while (i < n) {
            // Copy non-space characters
            if (s[i] != ' ') {
                s[j++] = s[i++];
            }
            // Handle a single space between words
            else {
                s[j++] = ' ';
                while (i < n && s[i] == ' ') i++;
            }
        }

        // Remove trailing space if any
        if (j > 0 && s[j - 1] == ' ') j--;

        s.resize(j);  // Trim string to final size
    }

    string reverseWords(string s) {
        trimSpaces(s);  // Step 1: clean up spaces

        reverse(s, 0, s.size() - 1);  // Step 2: reverse the whole string

        int start = 0, end = 0, n = s.size();

        // Step 3: reverse each word
        while (start < n) {
            end = start;
            while (end < n && s[end] != ' ') end++;
            reverse(s, start, end - 1);
            start = end + 1;
        }

        return s;
    }
};
//🔹 Time and Space Complexity:
//Time: O(n)

//Space: O(1) extra (in-place)
