//🔹 Approach:
//Convert both arrays into sets to get distinct elements.

//Use set difference operations to find:

//nums1 - nums2

//nums2 - nums1

vector<vector<int>> findDifference(vector<int>& nums1, vector<int>& nums2) {
    unordered_set<int> set1(nums1.begin(), nums1.end());
    unordered_set<int> set2(nums2.begin(), nums2.end());
    
    vector<int> only1, only2;
    
    for (int num : set1) {
        if (!set2.count(num)) only1.push_back(num);
    }
    
    for (int num : set2) {
        if (!set1.count(num)) only2.push_back(num);
    }
    
    return {only1, only2};
}
//🔹 Time and Space Complexity:
//Time: O(n + m), where n and m are the lengths of nums1 and nums2

//Space: O(n + m) for the sets and result

// Here’s a concise C++ STL version using std::set, std::set_difference, and lambda capture
vector<vector<int>> findDifference(vector<int>& nums1, vector<int>& nums2) {
    set<int> s1(nums1.begin(), nums1.end()), s2(nums2.begin(), nums2.end());
    vector<int> diff1, diff2;
    
    set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(diff1));
    set_difference(s2.begin(), s2.end(), s1.begin(), s1.end(), back_inserter(diff2));
    
    return {diff1, diff2};
}

//🔹 Notes:
//set_difference(A, B) copies elements in A that are not in B.

//Requires sorted containers → std::set is perfect.

//back_inserter appends to the result vector.

//🔸 (If you really want a one-liner function body)
vector<vector<int>> findDifference(vector<int>& A, vector<int>& B) {
    auto D = [](set<int>& X, set<int>& Y) { vector<int> r; set_difference(X.begin(), X.end(), Y.begin(), Y.end(), back_inserter(r)); return r; };
    set<int> S1(A.begin(), A.end()), S2(B.begin(), B.end());
    return { D(S1, S2), D(S2, S1) };
}
