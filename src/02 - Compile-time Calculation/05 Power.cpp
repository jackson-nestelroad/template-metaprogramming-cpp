// Example of template recursion

// Recursive case
template <int A, int N>
struct power {
    constexpr static long long value = A * power<A, N - 1>::value;
};

// Base case
template <int A>
struct power<A, 0> {
    constexpr static long long value = 1;
};

int run_power() {
    constexpr int a = power<26, 4>::value;      // 456976
    constexpr int b = power<3, 25>::value;      // 847288609443
    
    return 0;
}