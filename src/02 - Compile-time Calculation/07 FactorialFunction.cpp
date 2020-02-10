// Example of constexpr function recursion (C++14)

// Recursive case
template <int N>
constexpr long long factorial() {
    return N * factorial<N - 1>();
}

// Base case
template <>
constexpr long long factorial<1>() {
    return 1;
}

// Base case
template <>
constexpr long long factorial<0>() {
    return 1;
}

int run_factorial_function() {
    constexpr auto a = factorial<10>();   // 36288000
    return 0;
}