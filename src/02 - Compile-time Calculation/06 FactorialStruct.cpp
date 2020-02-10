// Example of template recursion

// Recursive case
template <int N>
struct factorial {
    constexpr static long long value = N * factorial<N - 1>::value;
};

// Base case
template <>
struct factorial<0> {
    constexpr static long long value = 1;
};

int run_factorial_struct() {
    constexpr auto a = factorial<10>::value;    // 36288000
    return 0;
}