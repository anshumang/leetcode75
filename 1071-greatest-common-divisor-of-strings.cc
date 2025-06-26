class Solution {
public:
    // Approach 1: Mathematical GCD approach (Most efficient)
    string gcdOfStrings(string str1, string str2) {
        // Check if concatenation in both orders gives same result
        // This is necessary condition for GCD to exist
        if (str1 + str2 != str2 + str1) {
            return "";
        }
        
        // If GCD exists, its length is GCD of string lengths
        int gcdLen = gcd(str1.length(), str2.length());
        return str1.substr(0, gcdLen);
    }
    
    // Helper function to calculate GCD of two numbers
    int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }
    
    // Approach 2: Iterative checking from largest possible divisor
    string gcdOfStringsIterative(string str1, string str2) {
        int minLen = min(str1.length(), str2.length());
        
        // Check from largest possible length down to 1
        for (int len = minLen; len >= 1; len--) {
            if (str1.length() % len == 0 && str2.length() % len == 0) {
                string candidate = str1.substr(0, len);
                if (isDivisor(candidate, str1) && isDivisor(candidate, str2)) {
                    return candidate;
                }
            }
        }
        
        return "";
    }
    
    // Helper function to check if pattern divides target string
    bool isDivisor(const string& pattern, const string& target) {
        if (target.length() % pattern.length() != 0) {
            return false;
        }
        
        int repetitions = target.length() / pattern.length();
        string constructed = "";
        
        for (int i = 0; i < repetitions; i++) {
            constructed += pattern;
        }
        
        return constructed == target;
    }
    
    // Approach 3: Recursive approach (similar to Euclidean algorithm)
    string gcdOfStringsRecursive(string str1, string str2) {
        // Base case: one string is empty
        if (str1.empty()) return str2;
        if (str2.empty()) return str1;
        
        // Make sure str1 is the longer string
        if (str1.length() < str2.length()) {
            return gcdOfStringsRecursive(str2, str1);
        }
        
        // Check if str2 is prefix of str1
        if (str1.substr(0, str2.length()) != str2) {
            return "";
        }
        
        // Recursively find GCD of str2 and remainder
        return gcdOfStringsRecursive(str2, str1.substr(str2.length()));
    }
    
    // Approach 4: Brute force with all possible divisors
    string gcdOfStringsBruteForce(string str1, string str2) {
        string result = "";
        int minLen = min(str1.length(), str2.length());
        
        for (int len = 1; len <= minLen; len++) {
            string candidate = str1.substr(0, len);
            
            // Check if candidate divides both strings
            if (canDivide(candidate, str1) && canDivide(candidate, str2)) {
                result = candidate; // Keep updating to get the longest
            }
        }
        
        return result;
    }
    
    // Helper function for brute force approach
    bool canDivide(const string& divisor, const string& target) {
        if (target.length() % divisor.length() != 0) {
            return false;
        }
        
        for (int i = 0; i < target.length(); i += divisor.length()) {
            if (target.substr(i, divisor.length()) != divisor) {
                return false;
            }
        }
        
        return true;
    }
};

// Test and demonstration class
class GCDStringDemo {
public:
    void demonstrateAlgorithm(string str1, string str2) {
        cout << "Finding GCD of strings:\n";
        cout << "str1 = \"" << str1 << "\"\n";
        cout << "str2 = \"" << str2 << "\"\n\n";
        
        // Check concatenation property
        string concat1 = str1 + str2;
        string concat2 = str2 + str1;
        
        cout << "str1 + str2 = \"" << concat1 << "\"\n";
        cout << "str2 + str1 = \"" << concat2 << "\"\n";
        cout << "Are they equal? " << (concat1 == concat2 ? "Yes" : "No") << "\n\n";
        
        if (concat1 != concat2) {
            cout << "No GCD exists because concatenations are different.\n";
            return;
        }
        
        // Calculate GCD of lengths
        int len1 = str1.length();
        int len2 = str2.length();
        int gcdLen = gcd(len1, len2);
        
        cout << "Length of str1: " << len1 << "\n";
        cout << "Length of str2: " << len2 << "\n";
        cout << "GCD of lengths: " << gcdLen << "\n\n";
        
        string result = str1.substr(0, gcdLen);
        cout << "GCD string: \"" << result << "\"\n";
        
        // Verify the result
        cout << "\nVerification:\n";
        cout << "str1 can be formed by repeating \"" << result << "\" " 
             << len1/gcdLen << " times\n";
        cout << "str2 can be formed by repeating \"" << result << "\" " 
             << len2/gcdLen << " times\n";
    }
    
private:
    int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }
};
