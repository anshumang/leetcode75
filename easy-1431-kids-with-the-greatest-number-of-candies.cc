vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
    int maxCandy = *max_element(candies.begin(), candies.end());
    vector<bool> result;

    for (int c : candies) {
        result.push_back(c + extraCandies >= maxCandy);
    }

    return result;
}
//🔹 Time & Space Complexity:
//Time: O(n)

//Space: O(n) (for output array)
vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
    int maxCandy = *max_element(candies.begin(), candies.end());
    vector<bool> result;
    transform(candies.begin(), candies.end(), back_inserter(result),
              [maxCandy, extraCandies](int c) { return c + extraCandies >= maxCandy; });
    return result;
}
//🔹 Explanation:
//transform() applies a lambda to each element of candies.

//back_inserter(result) appends the boolean result of the condition.

//maxCandy is captured by value in the lambda.
#include <ranges>

vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
    int maxCandy = *ranges::max(candies);
    return candies | std::views::transform([=](int c) { return c + extraCandies >= maxCandy; }) 
                   | std::ranges::to<vector<bool>>();
}
//🔹 Explanation:
//ranges::max(candies) returns the maximum candy count.

//std::views::transform(...) applies the lambda to each element.

//std::ranges::to<vector<bool>>() converts the resulting view to a vector<bool>.

//This requires including <ranges> and enabling the ranges adaptor to<>, which is available with certain standard library implementations (like MSVC/STL or libc++). On GCC/libstdc++, ranges::to<> might need
//range-v3 or experimental.
//🔸 Requirements:
//C++20 compiler (e.g., GCC 11+, Clang 12+, MSVC 2019+)

//#include <ranges>, #include <vector>
//✅ C++17 Version (Compact Fallback):
vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
    int maxCandy = *std::max_element(candies.begin(), candies.end());
    vector<bool> result(candies.size());
    std::transform(candies.begin(), candies.end(), result.begin(),
        [=](int c) { return c + extraCandies >= maxCandy; });
    return result;
}
//🔹 Explanation:
//std::max_element finds the current maximum.

//std::transform writes the transformed values directly into result.

//This avoids needing a back_inserter and makes the structure slightly more efficient.  
//✅ C++17 Functional-Style Version:
vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
    const auto maxCandy = *std::max_element(candies.begin(), candies.end());

    auto to_bool = [=](int c) { return c + extraCandies >= maxCandy; };

    vector<bool> result(candies.size());
    std::transform(candies.begin(), candies.end(), result.begin(), to_bool);
    return result;
}
//🔹 Explanation:
//The lambda to_bool captures maxCandy and extraCandies and encapsulates the condition.

//std::transform acts like a "map" operation in functional programming, applying to_bool over the input.
//While true function composition / chaining (like candies | map | filter | to_vector) is not available until C++20 (with <ranges>), this version emulates functional purity within the constraints of C++17.
// ✅ C++17 Version Using std::accumulate (Fully Immutable):
#include <vector>
#include <numeric>
#include <algorithm>

vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
    int maxCandy = *std::max_element(candies.begin(), candies.end());

    return std::accumulate(
        candies.begin(), candies.end(),
        vector<bool>{},  // initial result vector
        [=](vector<bool> acc, int c) {
            acc.push_back(c + extraCandies >= maxCandy);
            return acc;  // always return a new modified vector
        }
    );
}
// 🔹 Explanation:
//accumulate folds over candies, carrying an immutable vector (acc) at each step.

//push_back is called on a copy (not in-place mutation of a shared reference).

//The lambda returns a new vector each time, emulating a pure function pattern.

//🔸 Trade-offs:
//+ Very functional and clean — no mutation of outer scope, no side effects.

//− Slightly less efficient than transform due to repeated copying on each push_back. (For small input like this, it's negligible.)
// ✅ Optimized C++17 std::accumulate with Move Semantics:
#include <vector>
#include <numeric>
#include <algorithm>

vector<bool> kidsWithCandies(const vector<int>& candies, int extraCandies) {
    int maxCandy = *std::max_element(candies.begin(), candies.end());

    return std::accumulate(
        candies.begin(), candies.end(),
        vector<bool>{},  // initial accumulator (moved along)
        [=](vector<bool>&& acc, int c) mutable {
            acc.push_back(c + extraCandies >= maxCandy);
            return std::move(acc);  // move instead of copy
        }
    );
}
//🔹 Key Optimizations:
//acc is passed as an rvalue reference (&&), allowing mutation in-place.

//At the end of each call, std::move(acc) ensures the accumulator is efficiently moved, not copied.

//The lambda itself is marked mutable to allow mutation of acc captured as an rvalue.

//🔸 Benefits:
//Maintains functional purity in structure (no outer mutation).

//Avoids expensive vector copies at each step.

//Still adheres to C++17 standards — no C++20 features used.
✅ Generic map Function in C++17 (Move-Optimized)
template <typename InputIt, typename Func, typename Output = std::vector<std::invoke_result_t<Func, typename std::iterator_traits<InputIt>::value_type>>>
Output fmap(InputIt first, InputIt last, Func func) {
    return std::accumulate(
        first, last,
        Output{},
        [func = std::move(func)](Output&& acc, auto&& val) mutable {
            acc.push_back(func(std::forward<decltype(val)>(val)));
            return std::move(acc);
        }
    );
}
🔹 Explanation:
fmap mimics functional map (like in Haskell or Python) but is:

Generic over iterators,

Move-optimized (returns accumulator with std::move),

Compatible with any output container where push_back is valid (default: std::vector).

Uses std::invoke_result_t to deduce the output type of func.

Accepts any unary function and range.
🧪 Usage Example: Kids With Greatest Candies
vector<bool> kidsWithCandies(const vector<int>& candies, int extraCandies) {
    int maxCandy = *std::max_element(candies.begin(), candies.end());

    return fmap(candies.begin(), candies.end(), [=](int c) {
        return c + extraCandies >= maxCandy;
    });
}
🔸 Bonus: Add fmap overload for containers
template <typename Container, typename Func>
auto fmap(const Container& c, Func func) {
    return fmap(c.begin(), c.end(), std::move(func));
}
Now you can call:
return fmap(candies, [=](int c) { return c + extraCandies >= maxCandy; });

2️⃣ filter: Functional filter with predicate
template <typename InputIt, typename Predicate,
          typename ValueType = typename std::iterator_traits<InputIt>::value_type>
std::vector<ValueType> filter(InputIt first, InputIt last, Predicate pred) {
    return std::accumulate(
        first, last, std::vector<ValueType>{},
        [pred = std::move(pred)](std::vector<ValueType>&& acc, ValueType val) mutable {
            if (pred(val)) acc.push_back(std::move(val));
            return std::move(acc);
        }
    );
}

template <typename Container, typename Predicate>
auto filter(const Container& c, Predicate pred) {
    return filter(c.begin(), c.end(), std::move(pred));
}

3️⃣ fold: Functional reduce (left fold)
template <typename InputIt, typename T, typename BinaryFunc>
T fold(InputIt first, InputIt last, T init, BinaryFunc func) {
    return std::accumulate(first, last, std::move(init), std::move(func));
}

template <typename Container, typename T, typename BinaryFunc>
T fold(const Container& c, T init, BinaryFunc func) {
    return fold(c.begin(), c.end(), std::move(init), std::move(func));
}

🧪 Example Usage
vector<int> nums = {1, 2, 3, 4, 5};

// Double each number
auto doubled = fmap(nums, [](int x) { return x * 2; });

// Keep only even numbers
auto evens = filter(nums, [](int x) { return x % 2 == 0; });

// Sum all numbers
int total = fold(nums, 0, [](int acc, int x) { return acc + x; });

🔹 Summary
Function	Description
fmap	Transform each element
filter	Keep elements satisfying a condition
fold	Aggregate values into a single result
